configure_file(config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h)

file(
  GLOB_RECURSE UTILS_SRCS
  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
  utils/*.cpp
)

# utils library
add_library(utils STATIC ${UTILS_SRCS})

file(
  GLOB_RECURSE REQUEST_SRCS
  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
  request/*.cpp
)

# request library
add_library(request STATIC ${REQUEST_SRCS})
add_dependencies(request glog cJSON)

# lite.ai.toolkit library
add_lite_ai_toolkit_static_library()
add_dependencies(lite.ai.toolkit ncnn)

add_executable(${TARGET_NAME} main.cpp mainwindow.cpp mainwindow.ui)
add_dependencies(${TARGET_NAME} third_party)

target_link_libraries(
    ${TARGET_NAME}
    
    # static library
    lite.ai.toolkit
    request
    utils

    # third-party
    ncnn
    cJSON
    glog
    gflags

    # qt
    Qt6::Widgets
    Qt6::Core

    # opencv
    ${OpenCV_LIBRARIES}

    # pthread
    pthread
)