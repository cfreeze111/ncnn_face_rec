//
// Created by DefTruth on 2021/10/6.
//

#ifndef LITE_AI_TOOLKIT_MNN_CORE_MNN_CORE_H
#define LITE_AI_TOOLKIT_MNN_CORE_MNN_CORE_H

#include "mnn_config.h"
#include "mnn_handler.h"
#include "mnn_types.h"

namespace mnncv {
class MNNNanoDet;                   // [0] * reference: https://github.com/RangiLyu/nanodet
class MNNNanoDetEfficientNetLite;   // [1] * reference: https://github.com/RangiLyu/nanodet
class MNNRobustVideoMatting;   // [2] * reference: https://github.com/PeterL1n/RobustVideoMatting
class MNNYoloX;                // [3] * reference: https://github.com/Megvii-BaseDetection/YOLOX
class MNNYOLOP;                // [4] * reference: https://github.com/hustvl/YOLOP
class MNNYoloV5;               // [5] * reference: https://github.com/ultralytics/yolov5
class MNNYoloX_V_0_1_1;        // [6] * reference: https://github.com/Megvii-BaseDetection/YOLOX
class MNNYoloR;                // [7] * reference: https://github.com/WongKinYiu/yolor
class MNNYoloV5_V_6_0;         // [8] * reference: https://github.com/ultralytics/yolov5
class
  MNNGlintArcFace;   // [9] * reference:
                     // https://github.com/deepinsight/insightface/tree/master/recognition/arcface_torch
class
  MNNGlintCosFace;   // [10] * reference:
                     // https://github.com/deepinsight/insightface/tree/master/recognition/arcface_torch
class
  MNNGlintPartialFC;   // [11] * reference:
                       // https://github.com/deepinsight/insightface/tree/master/recognition/partial_fc
class MNNFaceNet;            // [12] * reference: https://github.com/timesler/facenet-pytorch
class MNNFocalArcFace;       // [13] * reference: https://github.com/ZhaoJ9014/face.evoLVe.PyTorch
class MNNFocalAsiaArcFace;   // [14] * reference: https://github.com/ZhaoJ9014/face.evoLVe.PyTorch
class MNNTencentCurricularFace;   // [15] * reference:
                                  // https://github.com/Tencent/TFace/tree/master/tasks/distfc
class MNNTencentCifpFace;         // [16] * reference:
                                  // https://github.com/Tencent/TFace/tree/master/tasks/cifp
class MNNCenterLossFace;      // [17] * reference: https://github.com/louis-she/center-loss.pytorch
class MNNSphereFace;          // [18] * reference: https://github.com/clcarwin/sphereface_pytorch
class MNNMobileFaceNet;       // [19] * reference: https://github.com/Xiaoccer/MobileFaceNet_Pytorch
class MNNCavaGhostArcFace;    // [20] * reference: https://github.com/cavalleria/cavaface.pytorch
class MNNCavaCombinedFace;    // [21] * reference: https://github.com/cavalleria/cavaface.pytorch
class MNNMobileSEFocalFace;   // [22] * reference:
                              // https://github.com/grib0ed0v/face_recognition.pytorch
class MNNUltraFace;           // [23] * reference:
                      // https://github.com/Linzaer/Ultra-Light-Fast-Generic-Face-Detector-1MB
class MNNRetinaFace;         // [24] * reference: https://github.com/biubug6/Pytorch_Retinaface
class MNNFaceBoxes;          // [25] * reference: https://github.com/zisianw/FaceBoxes.PyTorch
class MNNPFLD;               // [26] * reference: https://github.com/Hsintao/pfld_106_face_landmarks
class MNNPFLD98;             // [27] * reference: https://github.com/polarisZhao/PFLD-pytorch
class MNNMobileNetV268;      // [28] * reference: https://github.com/cunjian/pytorch_face_landmark
class MNNMobileNetV2SE68;    // [29] * reference: https://github.com/cunjian/pytorch_face_landmark
class MNNPFLD68;             // [30] * reference: https://github.com/cunjian/pytorch_face_landmark
class MNNFaceLandmark1000;   // [31] * reference: https://github.com/Single430/FaceLandmark1000
class MNNFSANet;             // [32] * reference: https://github.com/omasaht/headpose-fsanet-pytorch
class
  MNNAgeGoogleNet;   // [33] * reference:
                     // https://github.com/onnx/models/tree/master/vision/body_analysis/age_gender
class
  MNNGenderGoogleNet;   // [34] * reference:
                        // https://github.com/onnx/models/tree/master/vision/body_analysis/age_gender
class
  MNNEmotionFerPlus;   // [35] * reference:
                       // https://github.com/onnx/models/blob/master/vision/body_analysis/emotion_ferplus
class MNNSSRNet;              // [36] * reference: https://github.com/oukohou/SSR_Net_Pytorch
class MNNEfficientEmotion7;   // [37] * reference:
                              // https://github.com/HSE-asavchenko/face-emotion-recognition
class MNNEfficientEmotion8;   // [38] * reference:
                              // https://github.com/HSE-asavchenko/face-emotion-recognition
class MNNMobileEmotion7;      // [39] * reference:
                              // https://github.com/HSE-asavchenko/face-emotion-recognition
class MNNReXNetEmotion7;      // [40] * reference:
                              // https://github.com/HSE-asavchenko/face-emotion-recognition
class
  MNNEfficientNetLite4;   // [41] * reference:
                          // https://github.com/onnx/models/blob/master/vision/classification/efficientnet-lite4
class
  MNNShuffleNetV2;   // [42] * reference:
                     // https://github.com/onnx/models/blob/master/vision/classification/shufflenet
class MNNDenseNet;   // [43] * reference: https://pytorch.org/hub/pytorch_vision_densenet/
class MNNGhostNet;   // [44] * reference：https://pytorch.org/hub/pytorch_vision_ghostnet/
class MNNHdrDNet;    // [45] * reference: https://pytorch.org/hub/pytorch_vision_hardnet/
class MNNIBNNet;     // [46] * reference: https://pytorch.org/hub/pytorch_vision_ibnnet/
class MNNMobileNetV2;   // [47] * reference: https://pytorch.org/hub/pytorch_vision_mobilenet_v2/
class MNNResNet;        // [48] * reference: https://pytorch.org/hub/pytorch_vision_resnet/
class MNNResNeXt;       // [49] * reference: https://pytorch.org/hub/pytorch_vision_resnext/
class
  MNNFastStyleTransfer;   // [50] * reference:
                          // https://github.com/onnx/models/blob/master/vision/style_transfer/fast_neural_style
class MNNColorizer;            // [51] * reference: https://github.com/richzhang/colorization
class MNNSubPixelCNN;          // [52] * reference: https://github.com/niazwazir/SUB_PIXEL_CNN
class MNNDeepLabV3ResNet101;   // [53] * reference:
                               // https://pytorch.org/hub/pytorch_vision_deeplabv3_resnet101/
class MNNFCNResNet101;   // [54] * reference: https://pytorch.org/hub/pytorch_vision_fcn_resnet101/
class MNNMGMatting;      // [55] * reference: https://github.com/yucornetto/MGMatting
class MNNNanoDetPlus;    // [56] * reference: https://github.com/RangiLyu/nanodet
class MNNSCRFD;          // [57] * reference:
                         // https://github.com/deepinsight/insightface/tree/master/detection/scrfd
class MNNYOLO5Face;      // [58] * reference: https://github.com/deepcam-cn/yolov5-face
class MNNFaceBoxesV2;    // [59] * reference: https://github.com/jhb86253817/FaceBoxesV2
class MNNPIPNet19;       // [60] * reference: https://github.com/jhb86253817/PIPNet
class MNNPIPNet29;       // [61] * reference: https://github.com/jhb86253817/PIPNet
class MNNPIPNet68;       // [62] * reference: https://github.com/jhb86253817/PIPNet
class MNNPIPNet98;       // [63] * reference: https://github.com/jhb86253817/PIPNet
class MNNInsectDet;      // [64] * reference: https://github.com/quarrying/quarrying-insect-id
class MNNInsectID;       // [65] * reference: https://github.com/quarrying/quarrying-insect-id
class MNNPlantID;        // [66] * reference: https://github.com/quarrying/quarrying-plant-id
class MNNMODNet;         // [67] * reference: https://github.com/ZHKKKe/MODNet
class MNNBackgroundMattingV2;   // [68] * reference: https://github.com/PeterL1n/BackgroundMattingV2
class MNNYOLOv5BlazeFace;       // [69] * reference: https://github.com/deepcam-cn/yolov5-face
class MNNYoloV5_V_6_1;          // [70] * reference:
                                // https://github.com/ultralytics/yolov5/releases/tag/v6.1
class MNNHeadSeg;               // [71] * reference: https://github.com/minivision-ai/photo2cartoon
class MNNFemalePhoto2Cartoon;   // [72] * reference: https://github.com/minivision-ai/photo2cartoon
class MNNFastPortraitSeg;       // [73] * reference:
                                // https://github.com/YexingWan/Fast-Portrait-Segmentation
class MNNPortraitSegExtremeC3Net;   // [74] * reference:
                                    // https://github.com/clovaai/ext_portrait_segmentation
class MNNPortraitSegSINet;          // [75] * reference:
                                    // https://github.com/clovaai/ext_portrait_segmentation
class MNNFaceHairSeg;               // [76] * reference: https://github.com/kampta/face-seg
class MNNHairSeg;   // [77] * reference: https://github.com/akirasosa/mobile-semantic-segmentation
class MNNMobileHumanMatting;   // [78] * reference:
                               // https://github.com/lizhengwei1992/mobile_phone_human_matting
class MNNYOLOv6;               // [78] * reference: https://github.com/meituan/YOLOv6
class MNNFaceParsingBiSeNet;   // [79] * reference:
                               // https://github.com/zllrunning/face-parsing.PyTorch
class MNNFaceMesh;             // [80] * reference:
                     // https://github.com/google/mediapipe/tree/master/mediapipe/graphs/face_mesh
class
  MNNIrisLandmarks;   // [81] * reference:
                      // https://github.com/google/mediapipe/tree/master/mediapipe/graphs/iris_tracking
}   // namespace mnncv

namespace mnncv {
using mnncore::BasicMNNHandler;
}

namespace mnnnlp {
using mnncore::BasicMNNHandler;
}

namespace mnnasr {
using mnncore::BasicMNNHandler;
}

#endif   // LITE_AI_TOOLKIT_MNN_CORE_MNN_CORE_H
