//
// Created by DefTruth on 2021/10/17.
//

#ifndef LITE_AI_TOOLKIT_TNN_CORE_TNN_CORE_H
#define LITE_AI_TOOLKIT_TNN_CORE_TNN_CORE_H

#include "tnn_config.h"
#include "tnn_handler.h"
#include "tnn_types.h"

namespace tnncv {
class TNNNanoDet;                   // [0] * reference: https://github.com/RangiLyu/nanodet
class TNNNanoDetEfficientNetLite;   // [1] * reference: https://github.com/RangiLyu/nanodet
class TNNRobustVideoMatting;   // [2] * reference: https://github.com/PeterL1n/RobustVideoMatting
class TNNYoloX;                // [3] * reference: https://github.com/Megvii-BaseDetection/YOLOX
class TNNYOLOP;                // [4] * reference: https://github.com/hustvl/YOLOP
class TNNYoloV5;               // [5] * reference: https://github.com/ultralytics/yolov5
class TNNYoloX_V_0_1_1;        // [6] * reference: https://github.com/Megvii-BaseDetection/YOLOX
class TNNYoloR;                // [7] * reference: https://github.com/WongKinYiu/yolor
class TNNYoloV5_V_6_0;         // [8] * reference: https://github.com/ultralytics/yolov5
class
  TNNGlintArcFace;   // [9] * reference:
                     // https://github.com/deepinsight/insightface/tree/master/recognition/arcface_torch
class
  TNNGlintCosFace;   // [10] * reference:
                     // https://github.com/deepinsight/insightface/tree/master/recognition/arcface_torch
class
  TNNGlintPartialFC;   // [11] * reference:
                       // https://github.com/deepinsight/insightface/tree/master/recognition/partial_fc
class TNNFaceNet;            // [12] * reference: https://github.com/timesler/facenet-pytorch
class TNNFocalArcFace;       // [13] * reference: https://github.com/ZhaoJ9014/face.evoLVe.PyTorch
class TNNFocalAsiaArcFace;   // [14] * reference: https://github.com/ZhaoJ9014/face.evoLVe.PyTorch
class TNNTencentCurricularFace;   // [15] * reference:
                                  // https://github.com/Tencent/TFace/tree/master/tasks/distfc
class TNNTencentCifpFace;         // [16] * reference:
                                  // https://github.com/Tencent/TFace/tree/master/tasks/cifp
class TNNCenterLossFace;      // [17] * reference: https://github.com/louis-she/center-loss.pytorch
class TNNSphereFace;          // [18] * reference: https://github.com/clcarwin/sphereface_pytorch
class TNNMobileFaceNet;       // [19] * reference: https://github.com/Xiaoccer/MobileFaceNet_Pytorch
class TNNCavaGhostArcFace;    // [20] * reference: https://github.com/cavalleria/cavaface.pytorch
class TNNCavaCombinedFace;    // [21] * reference: https://github.com/cavalleria/cavaface.pytorch
class TNNMobileSEFocalFace;   // [22] * reference:
                              // https://github.com/grib0ed0v/face_recognition.pytorch
class TNNUltraFace;           // [23] * reference:
                      // https://github.com/Linzaer/Ultra-Light-Fast-Generic-Face-Detector-1MB
class TNNRetinaFace;         // [24] * reference: https://github.com/biubug6/Pytorch_Retinaface
class TNNFaceBoxes;          // [25] * reference: https://github.com/zisianw/FaceBoxes.PyTorch
class TNNPFLD;               // [26] * reference: https://github.com/Hsintao/pfld_106_face_landmarks
class TNNPFLD98;             // [27] * reference: https://github.com/polarisZhao/PFLD-pytorch
class TNNMobileNetV268;      // [28] * reference: https://github.com/cunjian/pytorch_face_landmark
class TNNMobileNetV2SE68;    // [29] * reference: https://github.com/cunjian/pytorch_face_landmark
class TNNPFLD68;             // [30] * reference: https://github.com/cunjian/pytorch_face_landmark
class TNNFaceLandmark1000;   // [31] * reference: https://github.com/Single430/FaceLandmark1000
class TNNFSANet;             // [32] * reference: https://github.com/omasaht/headpose-fsanet-pytorch
class
  TNNAgeGoogleNet;   // [33] * reference:
                     // https://github.com/onnx/models/tree/master/vision/body_analysis/age_gender
class
  TNNGenderGoogleNet;   // [34] * reference:
                        // https://github.com/onnx/models/tree/master/vision/body_analysis/age_gender
class
  TNNEmotionFerPlus;   // [35] * reference:
                       // https://github.com/onnx/models/blob/master/vision/body_analysis/emotion_ferplus
class TNNSSRNet;              // [36] * reference: https://github.com/oukohou/SSR_Net_Pytorch
class TNNEfficientEmotion7;   // [37] * reference:
                              // https://github.com/HSE-asavchenko/face-emotion-recognition
class TNNEfficientEmotion8;   // [38] * reference:
                              // https://github.com/HSE-asavchenko/face-emotion-recognition
class TNNMobileEmotion7;      // [39] * reference:
                              // https://github.com/HSE-asavchenko/face-emotion-recognition
class TNNReXNetEmotion7;      // [40] * reference:
                              // https://github.com/HSE-asavchenko/face-emotion-recognition
class
  TNNEfficientNetLite4;   // [41] * reference:
                          // https://github.com/onnx/models/blob/master/vision/classification/efficientnet-lite4
class
  TNNShuffleNetV2;   // [42] * reference:
                     // https://github.com/onnx/models/blob/master/vision/classification/shufflenet
class TNNDenseNet;   // [43] * reference: https://pytorch.org/hub/pytorch_vision_densenet/
class TNNGhostNet;   // [44] * reference：https://pytorch.org/hub/pytorch_vision_ghostnet/
class TNNHdrDNet;    // [45] * reference: https://pytorch.org/hub/pytorch_vision_hardnet/
class TNNIBNNet;     // [46] * reference: https://pytorch.org/hub/pytorch_vision_ibnnet/
class TNNMobileNetV2;   // [47] * reference: https://pytorch.org/hub/pytorch_vision_mobilenet_v2/
class TNNResNet;        // [48] * reference: https://pytorch.org/hub/pytorch_vision_resnet/
class TNNResNeXt;       // [49] * reference: https://pytorch.org/hub/pytorch_vision_resnext/
class
  TNNFastStyleTransfer;   // [50] * reference:
                          // https://github.com/onnx/models/blob/master/vision/style_transfer/fast_neural_style
class TNNColorizer;            // [51] * reference: https://github.com/richzhang/colorization
class TNNSubPixelCNN;          // [52] * reference: https://github.com/niazwazir/SUB_PIXEL_CNN
class TNNDeepLabV3ResNet101;   // [53] * reference:
                               // https://pytorch.org/hub/pytorch_vision_deeplabv3_resnet101/
class TNNFCNResNet101;   // [54] * reference: https://pytorch.org/hub/pytorch_vision_fcn_resnet101/
class TNNMGMatting;      // [55] * reference: https://github.com/yucornetto/MGMatting
class TNNNanoDetPlus;    // [56] * reference: https://github.com/RangiLyu/nanodet
class TNNSCRFD;          // [57] * reference:
                         // https://github.com/deepinsight/insightface/tree/master/detection/scrfd
class TNNYOLO5Face;      // [58] * reference: https://github.com/deepcam-cn/yolov5-face
class TNNFaceBoxesV2;    // [59] * reference: https://github.com/jhb86253817/FaceBoxesV2
class TNNPIPNet19;       // [60] * reference: https://github.com/jhb86253817/PIPNet
class TNNPIPNet29;       // [61] * reference: https://github.com/jhb86253817/PIPNet
class TNNPIPNet68;       // [62] * reference: https://github.com/jhb86253817/PIPNet
class TNNPIPNet98;       // [63] * reference: https://github.com/jhb86253817/PIPNet
class TNNInsectDet;      // [64] * reference: https://github.com/quarrying/quarrying-insect-id
class TNNInsectID;       // [65] * reference: https://github.com/quarrying/quarrying-insect-id
class TNNPlantID;        // [66] * reference: https://github.com/quarrying/quarrying-plant-id
class TNNMODNet;         // [67] * reference: https://github.com/ZHKKKe/MODNet
class TNNBackgroundMattingV2;   // [68] * reference: https://github.com/PeterL1n/BackgroundMattingV2
class TNNHeadSeg;               // [69] * reference: https://github.com/minivision-ai/photo2cartoon
class TNNFemalePhoto2Cartoon;   // [70] * reference: https://github.com/minivision-ai/photo2cartoon
class TNNYOLOv6;                // [71] * reference: https://github.com/meituan/YOLOv6
class TNNFaceParsingBiSeNet;    // [72] * reference:
                                // https://github.com/zllrunning/face-parsing.PyTorch
}   // namespace tnncv

namespace tnncv {
using tnncore::BasicTNNHandler;
}

namespace tnnnlp {
using tnncore::BasicTNNHandler;
}

namespace tnnasr {
using tnncore::BasicTNNHandler;
}

#endif   // LITE_AI_TOOLKIT_TNN_CORE_TNN_CORE_H
