#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "lite/lite.h"
#include "lite/types.h"

#include <glog/logging.h>

#include <QMainWindow>

#include <mutex>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <string>
#include <thread>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = 0);

  ~MainWindow();

private slots:
  void onBtnRequestClicked();

  void onBtnStartCaptureClicked();

  void onBtnStopCaptureClicked();

  void onCaptureTimerTimeout();

private:
  Ui::MainWindow*  _ui;
  cv::VideoCapture _capture;
  QTimer*          _capture_timer;

public:
  bool detect(cv::Mat& frame, cv::Mat& vis, lite::types::FaceContent& face_content);

  int getClassroomId() { return _classroom_id; }

  std::string& getResonseMsg() { return _response_msg; }

private:
  typedef struct DetectModelConfig
  {
    std::string path;
    float       conf_thres;   // 置信度阈值
    float       iou_thres;    // IOU阈值
    int         topk;         // 保留box数
    int         width;
    int         height;

    void print()
    {
      LOG(INFO) << "===========Detect Model Config==========";
      LOG(INFO) << "Model Path: " << path;
      LOG(INFO) << "Confidence Threshold: " << conf_thres;
      LOG(INFO) << "IOU Threshold: " << iou_thres;
      LOG(INFO) << "TopK: " << topk;
      LOG(INFO) << "Width: " << width;
      LOG(INFO) << "Height: " << height;
      LOG(INFO) << "========================================";
    }
  } DetectModelConfig;   // 人脸检测模型配置

  typedef struct RecognizeModelConfig
  {
    std::string path;
    int         width;
    int         height;
    float       sim_threshold;   // 相似度阈值
    void        print()
    {
      LOG(INFO) << "=========Recognize Model Config=========";
      LOG(INFO) << "Model Path: " << path;
      LOG(INFO) << "Width: " << width;
      LOG(INFO) << "Height: " << height;
      LOG(INFO) << "Similarity Threshold: " << sim_threshold;
      LOG(INFO) << "========================================";
    }
  } RecognizeModelConfig;   // 人脸识别模型配置

  void loadConfig(const std::string& config_path);

  void initFaceDetectModel(const int thread_nums);

  void initFaceRecognizeModel(const int thread_nums);

  void requestUpdateAttendenceStatus(const lite::types::FaceContent& face_content);

private:
  uint8_t _cap_device_id;

  uint32_t _classroom_id;

  lite::ncnn::cv::face::detect::RetinaFace* _face_detect_model = nullptr;

  lite::ncnn::cv::faceid::MobileFaceNet* _face_recognize_model = nullptr;

  std::string _response_msg;

  std::string _base_url;

  RecognizeModelConfig _recognize_model_config;

  DetectModelConfig _detect_model_config;

  std::mutex _qt_mtx;

  std::mutex _face_content_mtx;

  lite::types::FaceContent _face_content;
};

#endif   // MAINWINDOW_H
