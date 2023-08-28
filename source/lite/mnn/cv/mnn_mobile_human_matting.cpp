//
// Created by DefTruth on 2022/6/20.
//

#include "mnn_mobile_human_matting.h"
#include "lite/utils.h"

using mnncv::MNNMobileHumanMatting;

MNNMobileHumanMatting::MNNMobileHumanMatting(const std::string &_mnn_path, unsigned int _num_threads)
    : BasicMNNHandler(_mnn_path, _num_threads)
{
  initialize_pretreat();
}

inline void MNNMobileHumanMatting::initialize_pretreat()
{
  pretreat = std::shared_ptr<MNN::CV::ImageProcess>(
      MNN::CV::ImageProcess::create(
          MNN::CV::BGR,
          MNN::CV::BGR,
          mean_vals, 3,
          norm_vals, 3
      )
  );
}

void MNNMobileHumanMatting::transform(const cv::Mat &mat)
{
  cv::Mat canvas;
  cv::resize(mat, canvas, cv::Size(input_width, input_height));
  // (1,3,256,256) deepcopy inside
  pretreat->convert(canvas.data, input_width, input_height, canvas.step[0], input_tensor);
}

void MNNMobileHumanMatting::detect(const cv::Mat &mat, types::MattingContent &content,
                                   bool remove_noise, bool minimum_post_process)
{
  if (mat.empty()) return;
  // 1. make input tensor
  this->transform(mat);
  // 2. inference
  mnn_interpreter->runSession(mnn_session);
  auto output_tensors = mnn_interpreter->getSessionOutputAll(mnn_session);
  // 3. generate matting
  this->generate_matting(output_tensors, mat, content, remove_noise, minimum_post_process);
}

void MNNMobileHumanMatting::generate_matting(const std::map<std::string, MNN::Tensor *> &output_tensors,
                                             const cv::Mat &mat, types::MattingContent &content,
                                             bool remove_noise, bool minimum_post_process)
{
  auto device_output_ptr = output_tensors.at("alpha"); // e.g (1,1,256,256)
  MNN::Tensor host_output_tensor(device_output_ptr, device_output_ptr->getDimensionType());
  device_output_ptr->copyToHostTensor(&host_output_tensor);
  const unsigned int h = mat.rows;
  const unsigned int w = mat.cols;

  auto output_dims = host_output_tensor.shape();
  const unsigned int out_h = output_dims.at(2);
  const unsigned int out_w = output_dims.at(3);

  float *output_ptr = host_output_tensor.host<float>();

  cv::Mat alpha_pred(out_h, out_w, CV_32FC1, output_ptr);
  if (remove_noise) lite::utils::remove_small_connected_area(alpha_pred, 0.05f);
  // resize alpha
  if (out_h != h || out_w != w)
    // already allocated a new continuous memory after resize.
    cv::resize(alpha_pred, alpha_pred, cv::Size(w, h));
    // need clone to allocate a new continuous memory if not performed resize.
    // The memory elements point to will release after return.
  else alpha_pred = alpha_pred.clone();

  cv::Mat pmat = alpha_pred; // ref
  content.pha_mat = pmat; // auto handle the memory inside ocv with smart ref.

  if (!minimum_post_process)
  {
    // MobileHumanMatting only predict Alpha, no fgr. So,
    // the fake fgr and merge mat may not need,
    // let the fgr mat and merge mat empty to
    // Speed up the post processes.
    cv::Mat mat_copy;
    mat.convertTo(mat_copy, CV_32FC3);
    // merge mat and fgr mat may not need
    std::vector<cv::Mat> mat_channels;
    cv::split(mat_copy, mat_channels);
    cv::Mat bmat = mat_channels.at(0);
    cv::Mat gmat = mat_channels.at(1);
    cv::Mat rmat = mat_channels.at(2); // ref only, zero-copy.
    bmat = bmat.mul(pmat);
    gmat = gmat.mul(pmat);
    rmat = rmat.mul(pmat);
    cv::Mat rest = 1.f - pmat;
    cv::Mat mbmat = bmat.mul(pmat) + rest * 153.f;
    cv::Mat mgmat = gmat.mul(pmat) + rest * 255.f;
    cv::Mat mrmat = rmat.mul(pmat) + rest * 120.f;
    std::vector<cv::Mat> fgr_channel_mats, merge_channel_mats;
    fgr_channel_mats.push_back(bmat);
    fgr_channel_mats.push_back(gmat);
    fgr_channel_mats.push_back(rmat);
    merge_channel_mats.push_back(mbmat);
    merge_channel_mats.push_back(mgmat);
    merge_channel_mats.push_back(mrmat);

    cv::merge(fgr_channel_mats, content.fgr_mat);
    cv::merge(merge_channel_mats, content.merge_mat);

    content.fgr_mat.convertTo(content.fgr_mat, CV_8UC3);
    content.merge_mat.convertTo(content.merge_mat, CV_8UC3);
  }

  content.flag = true;
}