//
// Created by DefTruth on 2021/4/4.
//

#ifndef LITE_AI_ORT_CV_VGG16_AGE_H
#define LITE_AI_ORT_CV_VGG16_AGE_H

#include "lite/ort/core/ort_core.h"

namespace ortcv {
class VGG16Age : public BasicOrtHandler
{
public:
  explicit VGG16Age(const std::string& _onnx_path, unsigned int _num_threads = 1)
    : BasicOrtHandler(_onnx_path, _num_threads){};

  ~VGG16Age() override = default;

private:
  Ort::Value transform(const cv::Mat& mat) override;

public:
  void detect(const cv::Mat& mat, types::Age& age);
};
}   // namespace ortcv

#endif   // LITE_AI_ORT_CV_VGG16_AGE_H
