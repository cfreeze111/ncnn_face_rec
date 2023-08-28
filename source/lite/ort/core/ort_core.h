//
// Created by DefTruth on 2021/3/18.
//

#ifndef LITE_AI_ORT_ORT_CORE_H
#define LITE_AI_ORT_ORT_CORE_H

#include "ort_config.h"
#include "ort_handler.h"
#include "ort_types.h"

namespace ortcv {
class FSANet;         // [0] * reference: https://github.com/omasaht/headpose-fsanet-pytorch
class PFLD;           // [1] * reference: https://github.com/Hsintao/pfld_106_face_landmarks
class UltraFace;      // [2] * reference:
                      // https://github.com/Linzaer/Ultra-Light-Fast-Generic-Face-Detector-1MB
class AgeGoogleNet;   // [3] * reference:
                      // https://github.com/onnx/models/tree/master/vision/body_analysis/age_gender
class
  GenderGoogleNet;   // [4] * reference:
                     // https://github.com/onnx/models/tree/master/vision/body_analysis/age_gender
class
  EmotionFerPlus;   // [5] * reference:
                    // https://github.com/onnx/models/blob/master/vision/body_analysis/emotion_ferplus
class VGG16Age;      // [6] * reference:
                     // https://github.com/onnx/models/tree/master/vision/body_analysis/age_gender
class VGG16Gender;   // [7] * reference:
                     // https://github.com/onnx/models/tree/master/vision/body_analysis/age_gender
class SSRNet;        // [8] * reference: https://github.com/oukohou/SSR_Net_Pytorch
class
  FastStyleTransfer;   // [9] * reference:
                       // https://github.com/onnx/models/blob/master/vision/style_transfer/fast_neural_style
class
  GlintArcFace;   // [10] * reference:
                  // https://github.com/deepinsight/insightface/tree/master/recognition/arcface_torch
class Colorizer;     // [11] * reference: https://github.com/richzhang/colorization
class SubPixelCNN;   // [12] * reference: https://github.com/niazwazir/SUB_PIXEL_CNN
class YoloV4;        // [13] * reference: https://github.com/argusswift/YOLOv4-pytorch
class YoloV5;        // [14] * reference: https://github.com/ultralytics/yolov5
class
  YoloV3;   // [15] * reference:
            // https://github.com/onnx/models/blob/master/vision/object_detection_segmentation/yolov3
class
  EfficientNetLite4;   // [16] * reference:
                       // https://github.com/onnx/models/blob/master/vision/classification/efficientnet-lite4
class ShuffleNetV2;   // [17] * reference:
                      // https://github.com/onnx/models/blob/master/vision/classification/shufflenet
class
  TinyYoloV3;   // [18] * reference:
                // https://github.com/onnx/models/blob/master/vision/object_detection_segmentation/tiny-yolov3
class SSD;   // [19] * reference:
             // https://github.com/onnx/models/blob/master/vision/object_detection_segmentation/ssd
class
  SSDMobileNetV1;   // [20] * reference:
                    // https://github.com/onnx/models/blob/master/vision/object_detection_segmentation/ssd-mobilenetv1
class DeepLabV3ResNet101;   // [21] * reference:
                            // https://pytorch.org/hub/pytorch_vision_deeplabv3_resnet101/
class DenseNet;             // [22] * reference: https://pytorch.org/hub/pytorch_vision_densenet/
class FCNResNet101;   // [23] * reference: https://pytorch.org/hub/pytorch_vision_fcn_resnet101/
class GhostNet;       // [24] * reference：https://pytorch.org/hub/pytorch_vision_ghostnet/
class HdrDNet;        // [25] * reference: https://pytorch.org/hub/pytorch_vision_hardnet/
class IBNNet;         // [26] * reference: https://pytorch.org/hub/pytorch_vision_ibnnet/
class MobileNetV2;    // [27] * reference: https://pytorch.org/hub/pytorch_vision_mobilenet_v2/
class ResNet;         // [28] * reference: https://pytorch.org/hub/pytorch_vision_resnet/
class ResNeXt;        // [29] * reference: https://pytorch.org/hub/pytorch_vision_resnext/
class
  GlintCosFace;   // [30] * reference:
                  // https://github.com/deepinsight/insightface/tree/master/recognition/arcface_torch
class
  GlintPartialFC;   // [31] * reference:
                    // https://github.com/deepinsight/insightface/tree/master/recognition/partial_fc
class FaceNet;      // [32] * reference: https://github.com/timesler/facenet-pytorch
class FocalArcFace;            // [33] * reference: https://github.com/ZhaoJ9014/face.evoLVe.PyTorch
class FocalAsiaArcFace;        // [34] * reference: https://github.com/ZhaoJ9014/face.evoLVe.PyTorch
class TencentCurricularFace;   // [35] * reference:
                               // https://github.com/Tencent/TFace/tree/master/tasks/distfc
class TencentCifpFace;         // [36] * reference:
                               // https://github.com/Tencent/TFace/tree/master/tasks/cifp
class CenterLossFace;          // [37] * reference: https://github.com/louis-she/center-loss.pytorch
class SphereFace;              // [38] * reference: https://github.com/clcarwin/sphereface_pytorch
class PoseRobustFace;          // [39] * reference: https://github.com/penincillin/DREAM
class NaivePoseRobustFace;     // [40] * reference: https://github.com/penincillin/DREAM
class MobileFaceNet;        // [41] * reference: https://github.com/Xiaoccer/MobileFaceNet_Pytorch
class CavaGhostArcFace;     // [42] * reference: https://github.com/cavalleria/cavaface.pytorch
class CavaCombinedFace;     // [43] * reference: https://github.com/cavalleria/cavaface.pytorch
class MobileSEFocalFace;    // [44] * reference:
                            // https://github.com/grib0ed0v/face_recognition.pytorch
class EfficientEmotion7;    // [45] * reference:
                            // https://github.com/HSE-asavchenko/face-emotion-recognition
class EfficientEmotion8;    // [46] * reference:
                            // https://github.com/HSE-asavchenko/face-emotion-recognition
class MobileEmotion7;       // [47] * reference:
                            // https://github.com/HSE-asavchenko/face-emotion-recognition
class ReXNetEmotion7;       // [48] * reference:
                            // https://github.com/HSE-asavchenko/face-emotion-recognition
class PFLD98;               // [49] * reference: https://github.com/polarisZhao/PFLD-pytorch
class MobileNetV268;        // [50] * reference: https://github.com/cunjian/pytorch_face_landmark
class MobileNetV2SE68;      // [51] * reference: https://github.com/cunjian/pytorch_face_landmark
class PFLD68;               // [52] * reference: https://github.com/cunjian/pytorch_face_landmark
class FaceLandmark1000;     // [53] * reference: https://github.com/Single430/FaceLandmark1000
class RetinaFace;           // [54] * reference: https://github.com/biubug6/Pytorch_Retinaface
class FaceBoxes;            // [55] * reference: https://github.com/zisianw/FaceBoxes.PyTorch
class YoloX;                // [56] * reference: https://github.com/Megvii-BaseDetection/YOLOX
class TinyYoloV4VOC;        // [57] * reference: https://github.com/bubbliiiing/yolov4-tiny-pytorch
class TinyYoloV4COCO;       // [58] * reference: https://github.com/bubbliiiing/yolov4-tiny-pytorch
class YoloR;                // [59] * reference: https://github.com/WongKinYiu/yolor
class ScaledYoloV4;         // [60] * reference: https://github.com/WongKinYiu/ScaledYOLOv4
class EfficientDet;         // [61] * reference:
                            // https://github.com/zylo117/Yet-Another-EfficientDet-Pytorch
class EfficientDetD7;       // [62] * reference:
                            // https://github.com/zylo117/Yet-Another-EfficientDet-Pytorch
class EfficientDetD8;       // [63] * reference:
                            // https://github.com/zylo117/Yet-Another-EfficientDet-Pytorch
class YOLOP;                // [64] * reference: https://github.com/hustvl/YOLOP
class RobustVideoMatting;   // [65] * reference: https://github.com/PeterL1n/RobustVideoMatting
class NanoDet;              // [66] * reference: https://github.com/RangiLyu/nanodet
class NanoDetEfficientNetLite;   // [67] * reference: https://github.com/RangiLyu/nanodet
class YoloX_V_0_1_1;             // [68] * reference: https://github.com/Megvii-BaseDetection/YOLOX
class YoloV5_V_6_0;              // [69] * reference: https://github.com/ultralytics/yolov5
class MGMatting;                 // [70] * reference: https://github.com/yucornetto/MGMatting
class NanoDetPlus;               // [71] * reference: https://github.com/RangiLyu/nanodet
class SCRFD;                     // [72] * reference:
               // https://github.com/deepinsight/insightface/tree/master/detection/scrfd
class YOLO5Face;     // [73] * reference: https://github.com/deepcam-cn/yolov5-face
class FaceBoxesV2;   // [74] * reference: https://github.com/jhb86253817/FaceBoxesV2
class PIPNet19;      // [75] * reference: https://github.com/jhb86253817/PIPNet
class PIPNet29;      // [76] * reference: https://github.com/jhb86253817/PIPNet
class PIPNet68;      // [77] * reference: https://github.com/jhb86253817/PIPNet
class PIPNet98;      // [78] * reference: https://github.com/jhb86253817/PIPNet
class InsectDet;     // [79] * reference: https://github.com/quarrying/quarrying-insect-id
class InsectID;      // [80] * reference: https://github.com/quarrying/quarrying-insect-id
class PlantID;       // [81] * reference: https://github.com/quarrying/quarrying-plant-id
class MODNet;        // [82] * reference: https://github.com/ZHKKKe/MODNet
class MODNetDyn;   // [83] * reference: https://github.com/ZHKKKe/MODNet (With Dynamic Input Shape)
class BackgroundMattingV2;      // [84] * reference: https://github.com/PeterL1n/BackgroundMattingV2
class BackgroundMattingV2Dyn;   // [85] * reference: https://github.com/PeterL1n/BackgroundMattingV2
                                // (With Dynamic Input Shape)
class YOLOv5BlazeFace;          // [86] * reference: https://github.com/deepcam-cn/yolov5-face
class YoloV5_V_6_1;   // [87] * reference: https://github.com/ultralytics/yolov5/releases/tag/v6.1
class HeadSeg;        // [88] * reference: https://github.com/minivision-ai/photo2cartoon
class FemalePhoto2Cartoon;       // [89] * reference: https://github.com/minivision-ai/photo2cartoon
class FastPortraitSeg;           // [90] * reference:
                                 // https://github.com/YexingWan/Fast-Portrait-Segmentation
class PortraitSegExtremeC3Net;   // [91] * reference:
                                 // https://github.com/clovaai/ext_portrait_segmentation
class PortraitSegSINet;   // [92] * reference: https://github.com/clovaai/ext_portrait_segmentation
class FaceHairSeg;        // [93] * reference: https://github.com/kampta/face-seg
class HairSeg;   // [94] * reference: https://github.com/akirasosa/mobile-semantic-segmentation
class MobileHumanMatting;   // [95] * reference:
                            // https://github.com/lizhengwei1992/mobile_phone_human_matting
class MobileHairSeg;        // [96] * reference:
                            // https://github.com/wonbeomjang/mobile-hair-segmentation-pytorch
class RealSR;               // [97] * reference: https://github.com/jixiaozhong/RealSR
class BSRGAN;               // [98] * reference: https://github.com/cszn/BSRGAN
class SCUNet;               // [99] * reference: https://github.com/cszn/SCUNet
class MobileHumanPose3D;    // [100] * reference:
                            // https://github.com/ibaiGorordo/ONNX-Mobile-Human-Pose-3D
class FaceParsingBiSeNet;   // [101] * reference: https://github.com/zllrunning/face-parsing.PyTorch
class FaceParsingBiSeNetDyn;   // [102] * reference:
                               // https://github.com/zllrunning/face-parsing.PyTorch
class YOLOv6;                  // [103] * reference: https://github.com/meituan/YOLOv6
class FaceMesh;                // [104] * reference:
                  // https://github.com/google/mediapipe/tree/master/mediapipe/graphs/face_mesh
class
  IrisLandmarks;   // [105] * reference:
                   // https://github.com/google/mediapipe/tree/master/mediapipe/graphs/iris_tracking
}   // namespace ortcv

namespace ortnlp {
class TextCNN;          // todo
class ChineseBert;      // todo
class ChineseOCRLite;   // todo
}   // namespace ortnlp

namespace ortcv {
using core::BasicOrtHandler;
using core::BasicMultiOrtHandler;
}   // namespace ortcv
namespace ortnlp {
using core::BasicOrtHandler;
using core::BasicMultiOrtHandler;
}   // namespace ortnlp
namespace ortasr {
using core::BasicOrtHandler;
using core::BasicMultiOrtHandler;
}   // namespace ortasr
#endif   // LITE_AI_ORT_ORT_CORE_H
