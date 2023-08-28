############################## Source Files of LiteHub Based on MNN #################################
# 1. glob sources files
file(GLOB MNN_CORE_SRCS ${CMAKE_SOURCE_DIR}/source/lite/mnn/core/*.cpp)
file(GLOB MNN_CV_SRCS ${CMAKE_SOURCE_DIR}/source/lite/mnn/cv/*.cpp)
file(GLOB MNN_NLP_SRCS ${CMAKE_SOURCE_DIR}/source/lite/mnn/nlp/*.cpp)
file(GLOB MNN_ASR_SRCS ${CMAKE_SOURCE_DIR}/source/lite/mnn/asr/*.cpp)
# 2. glob headers files
file(GLOB MNN_CORE_HEAD ${CMAKE_SOURCE_DIR}/source/lite/mnn/core/*.h)
file(GLOB MNN_CV_HEAD ${CMAKE_SOURCE_DIR}/source/lite/mnn/cv/*.h)
file(GLOB MNN_NLP_HEAD ${CMAKE_SOURCE_DIR}/source/lite/mnn/nlp/*.h)
file(GLOB MNN_ASR_HEAD ${CMAKE_SOURCE_DIR}/source/lite/mnn/asr/*.h)

set(MNN_SRCS
        ${MNN_CV_SRCS}
        ${MNN_NLP_SRCS}
        ${MNN_ASR_SRCS}
        ${MNN_CORE_SRCS})
