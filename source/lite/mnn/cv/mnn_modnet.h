//
// Created by DefTruth on 2022/3/27.
//

#ifndef LITE_AI_TOOLKIT_MNN_CV_MNN_MODNET_H
#define LITE_AI_TOOLKIT_MNN_CV_MNN_MODNET_H

#include "lite/mnn/core/mnn_core.h"

namespace mnncv {
class MNNMODNet : public BasicMNNHandler
{
public:
  explicit MNNMODNet(const std::string& _mnn_path, unsigned int _num_threads = 1);   //
  ~MNNMODNet() override = default;

private:
  const float mean_vals[3] = {127.5f, 127.5f, 127.5f};
  const float norm_vals[3] = {1.f / 127.5f, 1.f / 127.5f, 1.f / 127.5f};

private:
  void initialize_pretreat();

  void transform(const cv::Mat& mat) override;   // resize & normalize.

  void generate_matting(const std::map<std::string, MNN::Tensor*>& output_tensors,
                        const cv::Mat& mat, types::MattingContent& content,
                        bool remove_noise = false, bool minimum_post_process = false);

public:
  void detect(const cv::Mat& mat, types::MattingContent& content, bool remove_noise = false,
              bool minimum_post_process = false);
};
}   // namespace mnncv

#endif   // LITE_AI_TOOLKIT_MNN_CV_MNN_MODNET_H
