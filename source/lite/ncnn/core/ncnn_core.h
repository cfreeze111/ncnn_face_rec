//
// Created by DefTruth on 2021/10/7.
//

#ifndef LITE_AI_TOOLKIT_NCNN_CORE_NCNN_CORE_H
#define LITE_AI_TOOLKIT_NCNN_CORE_NCNN_CORE_H

#include "ncnn_config.h"
#include "ncnn_custom.h"
#include "ncnn_handler.h"
#include "ncnn_types.h"

namespace ncnncv {
class NCNNNanoDet;                   // [0] * reference: https://github.com/RangiLyu/nanodet
class NCNNNanoDetEfficientNetLite;   // [1] * reference: https://github.com/RangiLyu/nanodet
class NCNNNanoDetDepreciated;        // [2] * reference: https://github.com/RangiLyu/nanodet
class NCNNNanoDetEfficientNetLiteDepreciated;   // [3] * reference:
                                                // https://github.com/RangiLyu/nanodet
class NCNNRobustVideoMatting;   // [4] * reference: https://github.com/PeterL1n/RobustVideoMatting
class NCNNYoloX;                // [5] * reference: https://github.com/Megvii-BaseDetection/YOLOX
class NCNNYOLOP;                // [6] * reference: https://github.com/hustvl/YOLOP
class NCNNYoloV5;               // [7] * reference: https://github.com/ultralytics/yolov5
class NCNNYoloX_V_0_1_1;        // [8] * reference: https://github.com/Megvii-BaseDetection/YOLOX
class NCNNYoloR;                // [9] * reference: https://github.com/WongKinYiu/yolor
class NCNNYoloRssss;            // [10] * reference: https://github.com/WongKinYiu/yolor
class NCNNYoloV5_V_6_0;         // [11] * reference: https://github.com/ultralytics/yolov5
class NCNNYoloV5_V_6_0_P6;      // [12] * reference: https://github.com/ultralytics/yolov5
class
  NCNNGlintArcFace;   // [13] * reference:
                      // https://github.com/deepinsight/insightface/tree/master/recognition/arcface_torch
class
  NCNNGlintCosFace;   // [14] * reference:
                      // https://github.com/deepinsight/insightface/tree/master/recognition/arcface_torch
class
  NCNNGlintPartialFC;   // [15] * reference:
                        // https://github.com/deepinsight/insightface/tree/master/recognition/partial_fc
class NCNNFaceNet;            // [16] * reference: https://github.com/timesler/facenet-pytorch
class NCNNFocalArcFace;       // [17] * reference: https://github.com/ZhaoJ9014/face.evoLVe.PyTorch
class NCNNFocalAsiaArcFace;   // [18] * reference: https://github.com/ZhaoJ9014/face.evoLVe.PyTorch
class NCNNTencentCurricularFace;   // [19] * reference:
                                   // https://github.com/Tencent/TFace/tree/master/tasks/distfc
class NCNNTencentCifpFace;         // [20] * reference:
                                   // https://github.com/Tencent/TFace/tree/master/tasks/cifp
class NCNNCenterLossFace;     // [21] * reference: https://github.com/louis-she/center-loss.pytorch
class NCNNSphereFace;         // [22] * reference: https://github.com/clcarwin/sphereface_pytorch
class NCNNMobileFaceNet;      // [23] * reference: https://github.com/Xiaoccer/MobileFaceNet_Pytorch
class NCNNCavaGhostArcFace;   // [24] * reference: https://github.com/cavalleria/cavaface.pytorch
class NCNNCavaCombinedFace;   // [25] * reference: https://github.com/cavalleria/cavaface.pytorch
class NCNNMobileSEFocalFace;   // [26] * reference:
                               // https://github.com/grib0ed0v/face_recognition.pytorch
class NCNNUltraFace;           // [27] * reference:
                       // https://github.com/Linzaer/Ultra-Light-Fast-Generic-Face-Detector-1MB
class NCNNRetinaFace;        // [28] * reference: https://github.com/biubug6/Pytorch_Retinaface
class NCNNFaceBoxes;         // [29] * reference: https://github.com/zisianw/FaceBoxes.PyTorch
class NCNNPFLD;              // [30] * reference: https://github.com/Hsintao/pfld_106_face_landmarks
class NCNNPFLD98;            // [31] * reference: https://github.com/polarisZhao/PFLD-pytorch
class NCNNMobileNetV268;     // [32] * reference: https://github.com/cunjian/pytorch_face_landmark
class NCNNMobileNetV2SE68;   // [33] * reference: https://github.com/cunjian/pytorch_face_landmark
class NCNNPFLD68;            // [34] * reference: https://github.com/cunjian/pytorch_face_landmark
class NCNNFaceLandmark1000;   // [35] * reference: https://github.com/Single430/FaceLandmark1000
class
  NCNNAgeGoogleNet;   // [36] * reference:
                      // https://github.com/onnx/models/tree/master/vision/body_analysis/age_gender
class
  NCNNGenderGoogleNet;   // [37] * reference:
                         // https://github.com/onnx/models/tree/master/vision/body_analysis/age_gender
class
  NCNNEmotionFerPlus;   // [38] * reference:
                        // https://github.com/onnx/models/blob/master/vision/body_analysis/emotion_ferplus
class NCNNEfficientEmotion7;   // [39] * reference:
                               // https://github.com/HSE-asavchenko/face-emotion-recognition
class NCNNEfficientEmotion8;   // [40] * reference:
                               // https://github.com/HSE-asavchenko/face-emotion-recognition
class NCNNMobileEmotion7;      // [41] * reference:
                               // https://github.com/HSE-asavchenko/face-emotion-recognition
class
  NCNNEfficientNetLite4;   // [42] * reference:
                           // https://github.com/onnx/models/blob/master/vision/classification/efficientnet-lite4
class
  NCNNShuffleNetV2;   // [43] * reference:
                      // https://github.com/onnx/models/blob/master/vision/classification/shufflenet
class NCNNDenseNet;   // [44] * reference: https://pytorch.org/hub/pytorch_vision_densenet/
class NCNNGhostNet;   // [45] * reference：https://pytorch.org/hub/pytorch_vision_ghostnet/
class NCNNHdrDNet;    // [46] * reference: https://pytorch.org/hub/pytorch_vision_hardnet/
class NCNNIBNNet;     // [47] * reference: https://pytorch.org/hub/pytorch_vision_ibnnet/
class NCNNMobileNetV2;   // [48] * reference: https://pytorch.org/hub/pytorch_vision_mobilenet_v2/
class NCNNResNet;        // [49] * reference: https://pytorch.org/hub/pytorch_vision_resnet/
class NCNNResNeXt;       // [50] * reference: https://pytorch.org/hub/pytorch_vision_resnext/
class
  NCNNFastStyleTransfer;   // [51] * reference:
                           // https://github.com/onnx/models/blob/master/vision/style_transfer/fast_neural_style
class NCNNColorizer;            // [52] * reference: https://github.com/richzhang/colorization
class NCNNSubPixelCNN;          // [53] * reference: https://github.com/niazwazir/SUB_PIXEL_CNN
class NCNNDeepLabV3ResNet101;   // [54] * reference:
                                // https://pytorch.org/hub/pytorch_vision_deeplabv3_resnet101/
class NCNNFCNResNet101;   // [55] * reference: https://pytorch.org/hub/pytorch_vision_fcn_resnet101/
class NCNNNanoDetPlus;    // [56] * reference: https://github.com/RangiLyu/nanodet
class NCNNSCRFD;          // [57] * reference:
                          // https://github.com/deepinsight/insightface/tree/master/detection/scrfd
class NCNNYOLO5Face;      // [58] * reference: https://github.com/deepcam-cn/yolov5-face
class NCNNFaceBoxesV2;    // [59] * reference: https://github.com/jhb86253817/FaceBoxesV2
class NCNNPIPNet19;       // [60] * reference: https://github.com/jhb86253817/PIPNet
class NCNNPIPNet29;       // [61] * reference: https://github.com/jhb86253817/PIPNet
class NCNNPIPNet68;       // [62] * reference: https://github.com/jhb86253817/PIPNet
class NCNNPIPNet98;       // [63] * reference: https://github.com/jhb86253817/PIPNet
class NCNNInsectID;       // [64] * reference: https://github.com/quarrying/quarrying-insect-id
class NCNNPlantID;        // [65] * reference: https://github.com/quarrying/quarrying-plant-id
class NCNNMODNet;         // [66] * reference: https://github.com/ZHKKKe/MODNet
class NCNNFemalePhoto2Cartoon;   // [67] * reference: https://github.com/minivision-ai/photo2cartoon
class NCNNYOLOv6;                // [68] * reference: https://github.com/meituan/YOLOv6
class NCNNFaceParsingBiSeNet;    // [69] * reference:
                                 // https://github.com/zllrunning/face-parsing.PyTorch
}   // namespace ncnncv

namespace ncnncv {
using ncnncore::BasicNCNNHandler;
}

namespace ncnnnlp {
using ncnncore::BasicNCNNHandler;
}

namespace ncnnasr {
using ncnncore::BasicNCNNHandler;
}

#endif   // LITE_AI_TOOLKIT_NCNN_CORE_NCNN_CORE_H
