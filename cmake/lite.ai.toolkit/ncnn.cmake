############################## Source Files of LiteHub Based on NCNN #################################
# 1. glob sources files
file(GLOB NCNN_CORE_SRCS ${CMAKE_SOURCE_DIR}/source/lite/ncnn/core/*.cpp)
file(GLOB NCNN_CV_SRCS ${CMAKE_SOURCE_DIR}/source/lite/ncnn/cv/*.cpp)
file(GLOB NCNN_NLP_SRCS ${CMAKE_SOURCE_DIR}/source/lite/ncnn/nlp/*.cpp)
file(GLOB NCNN_ASR_SRCS ${CMAKE_SOURCE_DIR}/source/lite/ncnn/asr/*.cpp)
# 2. glob headers files
file(GLOB NCNN_CORE_HEAD ${CMAKE_SOURCE_DIR}/source/lite/ncnn/core/*.h)
file(GLOB NCNN_CV_HEAD ${CMAKE_SOURCE_DIR}/source/lite/ncnn/cv/*.h)
file(GLOB NCNN_NLP_HEAD ${CMAKE_SOURCE_DIR}/source/lite/ncnn/nlp/*.h)
file(GLOB NCNN_ASR_HEAD ${CMAKE_SOURCE_DIR}/source/lite/ncnn/asr/*.h)

set(NCNN_SRCS
        ${NCNN_CV_SRCS}
        ${NCNN_NLP_SRCS}
        ${NCNN_ASR_SRCS}
        ${NCNN_CORE_SRCS})

