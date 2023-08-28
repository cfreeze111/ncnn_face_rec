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

set(GFLAGS_PREFIX_DIR ${THIRD_PARTY_SOURCE_PATH}/gflags)
set(GFLAGS_INSTALL_DIR ${THIRD_PARTY_INSTALL_PATH}/install/gflags)
set(GFLAGS_INCLUDE_DIR
    "${GFLAGS_INSTALL_DIR}/include"
    CACHE PATH "gflags include directory." FORCE)

if(WIN32)
  set(GFLAGS_LIBRARIES
      "${GFLAGS_INSTALL_DIR}/lib/gflags_static.lib"
      CACHE FILEPATH "GFLAGS_LIBRARIES" FORCE)
else()
  set(GFLAGS_LIBRARIES
      "${GFLAGS_INSTALL_DIR}/lib/libgflags.a"
      CACHE FILEPATH "GFLAGS_LIBRARIES" FORCE)
  set(BUILD_COMMAND ${CMAKE_COMMAND} --build .)
  set(INSTALL_COMMAND ${CMAKE_COMMAND} --build . --target install)
endif()
    
include_directories(${GFLAGS_INCLUDE_DIR})

ExternalProject_Add(
  extern_gflags
  SOURCE_DIR ${GFLAGS_PREFIX_DIR}
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
             -DBUILD_STATIC_LIBS=ON
             -DCMAKE_INSTALL_PREFIX=${GFLAGS_INSTALL_DIR}
             -DCMAKE_POSITION_INDEPENDENT_CODE=ON
             -DBUILD_TESTING=OFF
             -DCMAKE_BUILD_TYPE=${THIRD_PARTY_BUILD_TYPE}
             ${EXTERNAL_OPTIONAL_ARGS}
  CMAKE_CACHE_ARGS
    -DCMAKE_INSTALL_PREFIX:PATH=${GFLAGS_INSTALL_DIR}
    -DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=ON
    -DCMAKE_BUILD_TYPE:STRING=${THIRD_PARTY_BUILD_TYPE}
  BUILD_BYPRODUCTS ${GFLAGS_LIBRARIES})

add_library(gflags STATIC IMPORTED GLOBAL)
set_property(TARGET gflags PROPERTY IMPORTED_LOCATION ${GFLAGS_LIBRARIES})
add_dependencies(gflags extern_gflags)
