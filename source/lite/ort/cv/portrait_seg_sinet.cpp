//
// Created by DefTruth on 2022/6/19.
//
#include "portrait_seg_sinet.h"
#include "lite/ort/core/ort_utils.h"
#include "lite/utils.h"

using ortcv::PortraitSegSINet;

Ort::Value PortraitSegSINet::transform(const cv::Mat &mat_rs)
{
  return ortcv::utils::transform::create_tensor(
      ortcv::utils::transform::normalize(mat_rs, mean_vals, scale_vals),
      input_node_dims, memory_info_handler, input_values_handler,
      ortcv::utils::transform::CHW); // e.g (1,3,224,224)
}

void PortraitSegSINet::resize_unscale(const cv::Mat &mat, cv::Mat &mat_rs,
                                      int target_height, int target_width,
                                      PortraitSegSINetScaleParams &scale_params)
{
  if (mat.empty()) return;
  int img_height = static_cast<int>(mat.rows);
  int img_width = static_cast<int>(mat.cols);

  mat_rs = cv::Mat(target_height, target_width, CV_8UC3,
                   cv::Scalar(0, 0, 0));
  // scale ratio (new / old) new_shape(h,w)
  float w_r = (float) target_width / (float) img_width;
  float h_r = (float) target_height / (float) img_height;
  float r = std::min(w_r, h_r);
  // compute padding
  int new_unpad_w = static_cast<int>((float) img_width * r); // floor
  int new_unpad_h = static_cast<int>((float) img_height * r); // floor
  int pad_w = target_width - new_unpad_w; // >=0
  int pad_h = target_height - new_unpad_h; // >=0

  int dw = pad_w / 2;
  int dh = pad_h / 2;

  // resize with unscaling
  cv::Mat new_unpad_mat;
  // cv::Mat new_unpad_mat = mat.clone(); // may not need clone.
  cv::resize(mat, new_unpad_mat, cv::Size(new_unpad_w, new_unpad_h));
  new_unpad_mat.copyTo(mat_rs(cv::Rect(dw, dh, new_unpad_w, new_unpad_h)));

  // record scale params.
  scale_params.r = r;
  scale_params.dw = dw;
  scale_params.dh = dh;
  scale_params.new_unpad_w = new_unpad_w;
  scale_params.new_unpad_h = new_unpad_h;
  scale_params.flag = true;
}

void PortraitSegSINet::detect(const cv::Mat &mat, types::PortraitSegContent &content,
                              float score_threshold, bool remove_noise)
{
  if (mat.empty()) return;
  const int input_height = input_node_dims.at(2);
  const int input_width = input_node_dims.at(3);

  // resize & unscale
  cv::Mat mat_rs;
  PortraitSegSINetScaleParams scale_params;
  this->resize_unscale(mat, mat_rs, input_height, input_width, scale_params);

  // 1. make input tensor
  Ort::Value input_tensor = this->transform(mat_rs);
  // 2. inference
  auto output_tensors = ort_session->Run(
      Ort::RunOptions{nullptr}, input_node_names.data(),
      &input_tensor, 1, output_node_names.data(), num_outputs
  );
  // 3. generate mask
  this->generate_mask(scale_params, output_tensors, mat, content, score_threshold, remove_noise);
}

static inline void softmax_inplace(float *mutable_ptr_bgr, float *mutable_ptr_fgr)
{
  const float bgr_exp = std::exp(*mutable_ptr_bgr);
  const float fgr_exp = std::exp(*mutable_ptr_fgr);
  *mutable_ptr_bgr = bgr_exp / (bgr_exp + fgr_exp + 1e-10f);
  *mutable_ptr_fgr = 1.f - *mutable_ptr_bgr;
}

static inline void zero_if_small_inplace(float *mutable_ptr, float &score)
{ if ((*mutable_ptr) < score) *mutable_ptr = 0.f; }

void PortraitSegSINet::generate_mask(const PortraitSegSINetScaleParams &scale_params,
                                     std::vector<Ort::Value> &output_tensors,
                                     const cv::Mat &mat, types::PortraitSegContent &content,
                                     float score_threshold, bool remove_noise)
{
  Ort::Value &output = output_tensors.at(0); // e.g (1,2,224,224)
  const unsigned int h = mat.rows;
  const unsigned int w = mat.cols;
  auto output_dims = output.GetTypeInfo().GetTensorTypeAndShapeInfo().GetShape();
  const unsigned int out_h = output_dims.at(2); // e.g 224
  const unsigned int out_w = output_dims.at(3); // e.g 224
  const unsigned int channel_step = out_h * out_w;

  float *output_ptr = output.GetTensorMutableData<float>();

  // softmax
  for (unsigned int i = 0; i < channel_step; ++i)
    softmax_inplace(output_ptr + i, output_ptr + i + channel_step); // bgr & fgr

  // remove small values
  if (score_threshold > 0.001f)
    for (unsigned int i = 0; i < channel_step; ++i)
      zero_if_small_inplace(output_ptr + channel_step + i, score_threshold);

  // fetch foreground score
  const int dw = scale_params.dw;
  const int dh = scale_params.dh;
  const int nw = scale_params.new_unpad_w;
  const int nh = scale_params.new_unpad_h;

  cv::Mat alpha_pred(out_h, out_w, CV_32FC1, output_ptr + channel_step); // only need prob of fgr
  cv::Mat mask = alpha_pred(cv::Rect(dw, dh, nw, nh)); // 0. ~ 1.
  if (remove_noise) lite::utils::remove_small_connected_area(mask, 0.05f);
  // already allocated a new continuous memory after resize.
  if (nh != h || nw != w) cv::resize(mask, mask, cv::Size(w, h));
    // need clone to allocate a new continuous memory if not performed resize.
    // The memory elements point to will release after return.
  else mask = mask.clone();

  content.mask = mask; // auto handle the memory inside ocv with smart ref.
  content.flag = true;
}

