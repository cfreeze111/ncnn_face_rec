# Copyright (c) 2016 PaddlePaddle Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License. You may obtain a copy of
# the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations under
# the License.

include(ExternalProject)

set(NCNN_PREFIX_DIR ${THIRD_PARTY_SOURCE_PATH}/ncnn)
set(NCNN_INSTALL_DIR ${THIRD_PARTY_INSTALL_PATH}/install/ncnn)
set(NCNN_INCLUDE_DIR
    "${NCNN_INSTALL_DIR}/include"
    CACHE PATH "ncnn include directory." FORCE)

set(NCNN_LIBRARIES
    "${NCNN_INSTALL_DIR}/lib/libncnn.a"
    CACHE FILEPATH "ncnn library." FORCE)

include_directories(${NCNN_INCLUDE_DIR})


ExternalProject_Add(
  extern_ncnn
  SOURCE_DIR ${NCNN_PREFIX_DIR}
  UPDATE_COMMAND ""
  BUILD_COMMAND ${BUILD_COMMAND}
  INSTALL_COMMAND ${INSTALL_COMMAND}
  CMAKE_ARGS -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
             -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
             -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
             -DCMAKE_CXX_FLAGS_RELEASE=${CMAKE_CXX_FLAGS_RELEASE}
             -DCMAKE_CXX_FLAGS_DEBUG=${CMAKE_CXX_FLAGS_DEBUG}
             -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
             -DCMAKE_C_FLAGS_DEBUG=${CMAKE_C_FLAGS_DEBUG}
             -DCMAKE_C_FLAGS_RELEASE=${CMAKE_C_FLAGS_RELEASE}
             -DCMAKE_INSTALL_PREFIX=${NCNN_INSTALL_DIR}
             -DCMAKE_POSITION_INDEPENDENT_CODE=ON
             -DCMAKE_BUILD_TYPE=${THIRD_PARTY_BUILD_TYPE}
             -DCMAKE_OSX_ARCHITECTURES=arm64
             -DNCNN_VULKAN=OFF
             -DNCNN_OPENMP=OFF
             -DNCNN_BUILD_TOOLS=ON
             -DNCNN_BENCHMARK=OFF
             -DNCNN_BUILD_EXAMPLES=OFF
             ${EXTERNAL_OPTIONAL_ARGS}
  CMAKE_CACHE_ARGS
    -DCMAKE_INSTALL_PREFIX:PATH=${NCNN_INSTALL_DIR}
    -DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=ON
    -DCMAKE_BUILD_TYPE:STRING=${THIRD_PARTY_BUILD_TYPE}
  BUILD_BYPRODUCTS ${NCNN_LIBRARIES})

add_library(ncnn STATIC IMPORTED GLOBAL)
set_property(TARGET ncnn PROPERTY IMPORTED_LOCATION ${NCNN_LIBRARIES})
add_dependencies(ncnn extern_ncnn)
