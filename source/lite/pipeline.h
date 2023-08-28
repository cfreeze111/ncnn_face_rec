//
// Created by DefTruth on 2021/8/8.
//

#ifndef LITE_AI_PIPELINE_H
#define LITE_AI_PIPELINE_H

#include "models.h"


// Pipeline namespace
namespace lite {
namespace cv {
namespace pipeline {
// VideoPipeline: video demos for general models, such Face Detection
// + Face landmarks Detection | Face Attributes Analysis.
class VideoPipeline;

// FaceTracker: Face tracking using face detection and IoU.
class FaceTracker;

// ObjectTracker: Face tracking using object detection and IoU | DeepSort.
class ObjectTracker;

// FaceRecognizer: Face ID recognition using face detection.
// face alignment and recognition.
class FaceRecognizer;

// FaceAttributesAnalyser: Face Attributes Analysis using face detection,
// Face Attributes estimation.
class FaceAttributesAnalyser;

// VideoStyleTransfer: Style transfer for video demo.
class VideoStyleTransfer;

// VideoColorizer: colorization for video demo.
class VideoColorizer;
}   // namespace pipeline
}   // namespace cv
}   // namespace lite

namespace lite {
namespace cv {
namespace pipeline {
enum MODEL
{
  FSANet          = 0,
  PFLD            = 1,
  UltraFace       = 2,
  AgeGoogleNet    = 3,
  GenderGoogleNet = 4
};

}
}   // namespace cv
}   // namespace lite


#endif   // LITE_AI_PIPELINE_H
