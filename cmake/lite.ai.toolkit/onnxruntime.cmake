############################## Source Files of LiteHub Based on ONNXRuntime #################################
# 1. glob sources files
file(GLOB ONNXRUNTIME_CORE_SRCS ${CMAKE_SOURCE_DIR}/source/lite/ort/core/*.cpp)
file(GLOB ONNXRUNTIME_CV_SRCS ${CMAKE_SOURCE_DIR}/source/lite/ort/cv/*.cpp)
file(GLOB ONNXRUNTIME_NLP_SRCS ${CMAKE_SOURCE_DIR}/source/lite/ort/nlp/*.cpp)
file(GLOB ONNXRUNTIME_ASR_SRCS ${CMAKE_SOURCE_DIR}/source/lite/ort/asr/*.cpp)
# 2. glob headers files
file(GLOB ONNXRUNTIME_CORE_HEAD ${CMAKE_SOURCE_DIR}/source/lite/ort/core/*.h)
file(GLOB ONNXRUNTIME_CV_HEAD ${CMAKE_SOURCE_DIR}/source/lite/ort/cv/*.h)
file(GLOB ONNXRUNTIME_NLP_HEAD ${CMAKE_SOURCE_DIR}/source/lite/ort/nlp/*.h)
file(GLOB ONNXRUNTIME_ASR_HEAD ${CMAKE_SOURCE_DIR}/source/lite/ort/asr/*.h)

set(ORT_SRCS
        ${ONNXRUNTIME_CV_SRCS}
        ${ONNXRUNTIME_NLP_SRCS}
        ${ONNXRUNTIME_ASR_SRCS}
        ${ONNXRUNTIME_CORE_SRCS})
