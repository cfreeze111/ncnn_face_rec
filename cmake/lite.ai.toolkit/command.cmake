# config lite.ai shared lib.
function(add_lite_ai_toolkit_static_library)
    configure_file(
            "${CMAKE_SOURCE_DIR}/source/lite/config.h.in"
            "${CMAKE_SOURCE_DIR}/source/lite/config.h"
    )

    # 2. glob headers files
    file(GLOB LITE_HEAD ${CMAKE_SOURCE_DIR}/source/lite/*.h)

    # 3. glob sources files
    file(GLOB LITE_SRCS ${CMAKE_SOURCE_DIR}/source/lite/*.cpp)

    if (ENABLE_ONNXRUNTIME)
        include(lite.ai.toolkit/onnxruntime)
        set(LITE_SRCS ${LITE_SRCS} ${ORT_SRCS})
        # set(LITE_DEPENDENCIES ${LITE_DEPENDENCIES} onnxruntime)
    endif ()

    if (ENABLE_MNN)
        include(lite.ai.toolkit/MNN)
        set(LITE_SRCS ${LITE_SRCS} ${MNN_SRCS})
        # set(LITE_DEPENDENCIES ${LITE_DEPENDENCIES} MNN)
    endif ()

    if (ENABLE_NCNN)
        include(lite.ai.toolkit/ncnn)
        set(LITE_SRCS ${LITE_SRCS} ${NCNN_SRCS})
        # set(LITE_DEPENDENCIES ${LITE_DEPENDENCIES} ncnn)
    endif ()

    if (ENABLE_TNN)
        include(lite.ai.toolkit/TNN)
        set(LITE_SRCS ${LITE_SRCS} ${TNN_SRCS})
        # set(LITE_DEPENDENCIES ${LITE_DEPENDENCIES} TNN)
    endif ()

    # 4. static library
    add_library(lite.ai.toolkit STATIC ${LITE_SRCS})
    # target_link_libraries(lite.ai.toolkit ${LITE_DEPENDENCIES})
    # set_target_properties(lite.ai.toolkit PROPERTIES VERSION ${version} SOVERSION ${soversion})

endfunction()