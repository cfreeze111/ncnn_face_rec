cmake_minimum_required(VERSION 3.20)

project(edge_face_recognize VERSION 0.0.0 LANGUAGES CXX)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")


cmake_policy(SET CMP0077 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

option(WITH_TESTING "with unit test" OFF)

# inference engines setups: config.h.in -> config.h
option(ENABLE_DEBUG_STRING "enable DEBUG string or not" ON)
option(ENABLE_ONNXRUNTIME "enable ONNXRuntime engine" OFF)
option(ENABLE_MNN "enable MNN engine" OFF)  # unstable now, DON'T use
option(ENABLE_NCNN "enable NCNN engine" ON) # unstable now, DON'T use
option(ENABLE_TNN "enable TNN engine" OFF) # unstable now, DON'T use
# cuda provider setups: config.h.in -> config.h (only for onnxruntime)
option(ENABLE_ONNXRUNTIME_CUDA "enable ONNXRuntime engine with CUDA provider" OFF)
# openmp/opengl/vulkan/cuda setups: config.h.in -> config.h (for future use)
option(ENABLE_LITE_OPENMP "enable OPENMP accelerate for some post processes" OFF)  # for future use, DON'T use NOW!
option(ENABLE_LITE_OPENGL "enable OPENGL accelerate for some post processes" OFF)  # for future use, DON'T use NOW!
option(ENABLE_LITE_VULKAN "enable VULKAN accelerate for some post processes" OFF)  # for future use, DON'T use NOW!
option(ENABLE_LITE_CUDA "enable CUDA accelerate for some post processes" OFF)  # for future use, DON'T use NOW!
# videoio interface setups, for future use
option(ENABLE_OPENCV_VIDEOIO "enable opencv videoio modules for detect_video apis" OFF) # now, ON only
# inference engines backend setups for lite.ai.toolkit
option(BACKEND_ONNXRUNTIME "set ONNXRuntime as the main backend of lite.ai.toolkit" OFF)
option(BACKEND_MNN "set MNN as the main backend of lite.ai.toolkit" OFF)  # now, OFF only
option(BACKEND_NCNN "set NCNN as the main backend of lite.ai.toolkit" ON)  # now, OFF only
option(BACKEND_TNN "set TNN as the main backend of lite.ai.toolkit" OFF)  # now, OFF only
# dummy option
option(INSTALL_PATH "dummy option, for configure_file" on)

# dependencies path 
set(QT_PREFIX_PATH "${CMAKE_SOURCE_DIR}/third_party/qtbase-release")

# target name
set(TARGET_NAME "edge-face-recognize")

set(CMAKE_PREFIX_PATH
    ${CMAKE_PREFIX_PATH}
    ${QT_PREFIX_PATH}
    ${OpenCV_PREFIX_PATH})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)
find_package(OpenCV REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# http request header
set(HTTPREQUEST_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/third_party/HTTPRequest/include")

# header file path 
include_directories(
    ${CMAKE_SOURCE_DIR}/source
    ${HTTPREQUEST_INCLUDE_DIR} 
    ${OpenCV_INCLUDE_DIRS}
)

include(generic)
include(omp)
include(third_party)
include(lite.ai.toolkit/command)

add_subdirectory(source)

install(TARGETS ${TARGET_NAME} DESTINATION bin COMPONENT binaries)

# copy config file
install(FILES 
    ${CMAKE_SOURCE_DIR}/resource/config.json
    DESTINATION conf)

# copy model files
install(FILES 
    ${CMAKE_SOURCE_DIR}/resource/models/mobile_facenet.opt.bin
    ${CMAKE_SOURCE_DIR}/resource/models/mobile_facenet.opt.param
    ${CMAKE_SOURCE_DIR}/resource/models/retinaface_mobile0.25-640-640.opt.bin
    ${CMAKE_SOURCE_DIR}/resource/models/retinaface_mobile0.25-640-640.opt.param
    DESTINATION models)
