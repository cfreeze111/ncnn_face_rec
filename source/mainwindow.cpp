#include "mainwindow.h"
#include "config.h"
#include "lite/types.h"
#include "lite/utils.h"
#include "request/request.h"
#include "status_code.h"
#include "ui_mainwindow.h"
#include "utils/base64.h"
#include "utils/utils.h"

#include <algorithm>

#include <QDateTime>
#include <QDebug>
#include <QImage>
#include <QMessageBox>
#include <QPushButton>
#include <QTimer>
#include <QWidget>

#include <cjson/cJSON.h>
#include <cstddef>
#include <glog/logging.h>
#include <iostream>
#include <mutex>
#include <opencv2/core/types.hpp>
#include <opencv2/videoio.hpp>
#include <qpushbutton.h>
#include <qtimer.h>
#include <string>
#include <thread>


static bool detectBoxSortBySize(const lite::types::Boxf& box1, const lite::types::Boxf& box2)
{
  return box1.area() > box2.area();
}

static std::string formatEmbedding(const std::vector<float>& embedding)
{
  std::string s("");
  for (size_t i = 0; i < embedding.size(); i++) {
    if (i != embedding.size()) {
      s += std::to_string(embedding[i]) + ",";
    }
    else {
      s += std::to_string(embedding[i]);
    }
  }

  return s;
}

static std::string getFormatDate()
{
  time_t     now;
  struct tm* tm_now;
  char       datetime[200];

  time(&now);
  tm_now = localtime(&now);
  strftime(datetime, 200, "%Y-%m-%d %H:%M:%S", tm_now);

  return std::string(datetime);
  // return std::string("2023-05-29 9:24:00");
}

// Mat转成QImage
static QImage MatImageToQt(const cv::Mat& src)
{
  // CV_8UC1 8位无符号的单通道---灰度图片
  if (src.type() == CV_8UC1) {
    // 使用给定的大小和格式构造图像
    // QImage(int width, int height, Format format)
    cv::Mat dst(cv::Size(640, 480), CV_8UC3);
    cvtColor(src, dst, cv::COLOR_GRAY2RGB);
    QImage qImage((const uchar*)dst.data, dst.cols, dst.rows, QImage::Format_RGB888);
    return qImage.rgbSwapped();
  }
  // 为3通道的彩色图片
  else if (src.type() == CV_8UC3) {
    // 得到图像的的首地址
    const uchar* pSrc = (const uchar*)src.data;
    // 以src构造图片
    QImage qImage(pSrc, src.cols, src.rows, src.step, QImage::Format_RGB888);
    // 在不改变实际图像数据的条件下，交换红蓝通道
    return qImage.rgbSwapped();
  }
  // 四通道图片，带Alpha通道的RGB彩色图像
  else if (src.type() == CV_8UC4) {
    const uchar* pSrc = (const uchar*)src.data;
    QImage       qImage(pSrc, src.cols, src.rows, src.step, QImage::Format_ARGB32);
    // 返回图像的子区域作为一个新图像
    return qImage.copy();
  }
  else {
    return QImage();
  }
}

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , _ui(new Ui::MainWindow)
{
  _ui->setupUi(this);

  const int threads = 1;

  std::string detect_model_path, recognize_model_path;
  std::string config_path = INSTALL_PATH "/conf/config.json";
  std::cout << config_path << std::endl;
  loadConfig(config_path);

  LOG(INFO) << "========================================";
  LOG(INFO) << "Initing face detect model";
  initFaceDetectModel(threads);
  LOG(INFO) << "Face detect model init success!";
  LOG(INFO) << "========================================";


  LOG(INFO) << "========================================";
  LOG(INFO) << "Initing face recognize model";
  initFaceRecognizeModel(threads);
  LOG(INFO) << "Face recognize model init success!";
  LOG(INFO) << "========================================";

  LOG(INFO) << "===========GUI Init Success!============";

  _capture_timer = new QTimer(this);

  connect(_ui->btnStartCapture, &QPushButton::clicked, this, &MainWindow::onBtnStartCaptureClicked);
  connect(_ui->btnStopCapture, &QPushButton::clicked, this, &MainWindow::onBtnStopCaptureClicked);
  connect(_ui->btnRequest, &QPushButton::clicked, this, &MainWindow::onBtnRequestClicked);
  connect(_capture_timer, &QTimer::timeout, this, &MainWindow::onCaptureTimerTimeout);
}

MainWindow::~MainWindow()
{
  if (_capture.isOpened()) {
    _capture.release();
  }
  if (_face_detect_model) {
    delete _face_detect_model;
    _face_detect_model = nullptr;
  }
  if (_face_recognize_model) {
    delete _face_recognize_model;
    _face_recognize_model = nullptr;
  }
}

void MainWindow::onBtnRequestClicked()
{
  lite::types::FaceContent face_content;
  {
    std::unique_lock<std::mutex> lock(_face_content_mtx);
    face_content = _face_content;
  }

  for (int i = 0; i < face_content.dim; i++) {
    std::cout << face_content.embedding[i] << ",";
  }
  std::cout << std::endl;

  std::thread t(&MainWindow::requestUpdateAttendenceStatus, this, face_content);
  t.detach();
}

void MainWindow::onBtnStopCaptureClicked()
{
  _capture_timer->stop();

  _ui->lblImage->clear();
  _ui->lblCapStatus->setText("关闭");
  _capture.release();

  LOG(INFO) << "cam is closed";
}

void MainWindow::onBtnStartCaptureClicked()
{
  if (_capture.open(_cap_device_id) && _capture.set(cv::CAP_PROP_FPS, 30) &&
      _capture.set(cv::CAP_PROP_FRAME_WIDTH, 640) && _capture.set(cv::CAP_PROP_FRAME_HEIGHT, 480)) {
    LOG(INFO) << "cam is opened";
    _ui->lblCapStatus->setText("开启");

    _capture_timer->start(33);
  }
  else {
    LOG(INFO) << "cam is not opened";

    cv::Mat frame;
    QImage  qimage;
    if (!_capture.isOpened()) {
      QMessageBox::critical(NULL, "error", "not open camera", QMessageBox::Yes, QMessageBox::Yes);
      return;
    }
  }

  return;
}


void MainWindow::onCaptureTimerTimeout()
{
  cv::Mat frame;
  _capture >> frame;

  if (frame.empty()) {
    LOG(WARNING) << "frame is empty";
  }
  else {
    if (!detect(frame, frame, _face_content)) {
      // not detect face -> return directly
      QImage qimage = MatImageToQt(frame);
      _ui->lblImage->setPixmap(QPixmap::fromImage(qimage));

      return;
    };

    QImage qimage = MatImageToQt(frame);
    _ui->lblImage->setPixmap(QPixmap::fromImage(qimage));
  }
}

void MainWindow::loadConfig(const std::string& config_path)
{
  char* txt = utils::readFile(config_path);

  cJSON* root = cJSON_Parse(txt);

  if (root == NULL) {
    LOG(ERROR) << "Read config.json failed!";
    exit(EXIT_CONFIG_LOAD_FAIL);
  }

  cJSON* detect_model_node    = cJSON_GetObjectItem(root, "detect_model");
  cJSON* recognize_model_node = cJSON_GetObjectItem(root, "recognize_model");
  cJSON* classroom_id_node    = cJSON_GetObjectItem(root, "classroom_id");
  cJSON* base_url_node        = cJSON_GetObjectItem(root, "base_url");
  cJSON* cap_device_id_node   = cJSON_GetObjectItem(root, "cap_device_id");

  _detect_model_config.path =
    std::string(cJSON_GetObjectItem(detect_model_node, "path")->valuestring);
  _detect_model_config.conf_thres =
    cJSON_GetObjectItem(detect_model_node, "conf_thres")->valuedouble;
  _detect_model_config.iou_thres = cJSON_GetObjectItem(detect_model_node, "iou_thres")->valuedouble;
  _detect_model_config.topk      = cJSON_GetObjectItem(detect_model_node, "topk")->valueint;
  _detect_model_config.width     = cJSON_GetObjectItem(detect_model_node, "width")->valueint;
  _detect_model_config.height    = cJSON_GetObjectItem(detect_model_node, "height")->valueint;

  _recognize_model_config.path =
    std::string(cJSON_GetObjectItem(recognize_model_node, "path")->valuestring);
  _recognize_model_config.width  = cJSON_GetObjectItem(recognize_model_node, "width")->valueint;
  _recognize_model_config.height = cJSON_GetObjectItem(recognize_model_node, "height")->valueint;
  _recognize_model_config.sim_threshold =
    cJSON_GetObjectItem(recognize_model_node, "sim_threshold")->valuedouble;

  _classroom_id  = classroom_id_node->valueint;
  _base_url      = std::string(base_url_node->valuestring);
  _cap_device_id = cap_device_id_node->valueint;

  _detect_model_config.print();
  _recognize_model_config.print();

  cJSON_Delete(root);
  root = nullptr;

  free(txt);
  txt = nullptr;
}

void MainWindow::initFaceDetectModel(const int threads)
{
  std::string param_path = _detect_model_config.path + ".param";
  std::string bin_path   = _detect_model_config.path + ".bin";

  std::string install_path = INSTALL_PATH;

  _face_detect_model = new lite::ncnn::cv::face::detect::RetinaFace(install_path + param_path,
                                                                    install_path + bin_path,
                                                                    threads,
                                                                    _detect_model_config.width,
                                                                    _detect_model_config.height);
}

void MainWindow::initFaceRecognizeModel(const int threads)
{
  std::string param_path = _recognize_model_config.path + ".param";
  std::string bin_path   = _recognize_model_config.path + ".bin";

  std::string install_path = INSTALL_PATH;

  _face_recognize_model = new lite::ncnn::cv::faceid::MobileFaceNet(
    install_path + param_path, install_path + bin_path, threads);
}

void MainWindow::requestUpdateAttendenceStatus(const lite::types::FaceContent& face_content)
{
  const std::string url = "/attendance/update";

  LOG(INFO) << "===========Requesting============";

  std::vector<std::string> base64_face_contents;

  const std::string formatedEmbedding = formatEmbedding(face_content.embedding);
  // 将embedding进行base64编码
  std::string base64_face_content =
    base64_encode(reinterpret_cast<const unsigned char*>(formatedEmbedding.c_str()),
                  formatedEmbedding.length(),
                  false);

  LOG(INFO) << "base64: " << base64_face_content;

  std::string now = getFormatDate();
  LOG(INFO) << "Request Date: " << now;

  cJSON* root = cJSON_CreateObject();
  cJSON_AddStringToObject(root, "faceId", base64_face_content.c_str());
  cJSON_AddStringToObject(root, "date", now.c_str());
  cJSON_AddNumberToObject(root, "classroomId", _classroom_id);
  cJSON_AddNumberToObject(root, "threshold", _recognize_model_config.sim_threshold);

  std::string result = request::post(_base_url + "/attendance/update", root);
  // free params
  cJSON_Delete(root);

  cJSON* result_json = cJSON_Parse(result.c_str());

  std::string statusCode = cJSON_GetObjectItem(result_json, "code")->valuestring;
  if (statusCode != "200") {   // request failed
    _response_msg = std::string(cJSON_GetObjectItem(result_json, "msg")->valuestring);
    LOG(ERROR) << "Request failed, error message: "
               << cJSON_GetObjectItem(result_json, "msg")->valuestring;

    cJSON_Delete(result_json);

    std::unique_lock<std::mutex> lock(_qt_mtx);
    _ui->lblResponseMsg->setText(QString::fromStdString(_response_msg));
    _ui->lblSignStatus->setText(QString::fromStdString(""));
    _ui->lblStudentName->setText(QString::fromStdString(""));

    return;
  }

  cJSON* data = cJSON_GetObjectItem(result_json, "data");

  _response_msg                 = "请求成功";
  std::string student_name      = cJSON_GetObjectItem(data, "name")->valuestring;
  std::string attendence_status = cJSON_GetObjectItem(data, "status")->valuestring;

  cJSON_Delete(result_json);

  std::unique_lock<std::mutex> lock(_qt_mtx);
  _ui->lblResponseMsg->setText(QString::fromStdString(_response_msg));
  _ui->lblSignStatus->setText(QString::fromStdString(attendence_status));
  _ui->lblStudentName->setText(QString::fromStdString(student_name));
}

bool MainWindow::detect(cv::Mat& frame, cv::Mat& vis, lite::types::FaceContent& face_content)
{
  if (&frame != &vis) {
    vis = frame.clone();
  }

  std::vector<lite::types::Boxf> detected_boxes;

  LOG(INFO) << "Detecting face...";
  _face_detect_model->detect(frame,
                             detected_boxes,
                             _detect_model_config.conf_thres,
                             _detect_model_config.iou_thres,
                             _detect_model_config.topk);

  if (detected_boxes.size() == 0) {   // 检测人脸
    LOG(WARNING) << "Not detected face !";

    return false;
  }

  LOG(INFO) << "Retinaface Detected Face Num: " << detected_boxes.size();

  // sort by face area from max to min
  std::sort(detected_boxes.begin(), detected_boxes.end(), detectBoxSortBySize);

  auto box = detected_boxes[0];

  LOG(INFO) << "Encoding face...";
  cv::Rect rect = box.rect();

  int x1 = rect.tl().x < 0 ? 0 : rect.tl().x;
  int y1 = rect.tl().y < 0 ? 0 : rect.tl().y;

  int x2 = rect.br().x >= frame.cols ? frame.cols - 1 : rect.br().x;
  int y2 = rect.br().y >= frame.rows ? frame.rows - 1 : rect.br().y;

  cv::Rect roi(cv::Point(x1, y1), cv::Point(x2, y2));

  cv::Mat face = frame(roi);
  _face_recognize_model->detect(face, face_content);

  // draw face detect result
  if (&frame != &vis) {
    vis = lite::utils::draw_boxes(frame, detected_boxes);
  }
  else {
    lite::utils::draw_boxes_inplace(frame, detected_boxes);
  }

  return true;
}
