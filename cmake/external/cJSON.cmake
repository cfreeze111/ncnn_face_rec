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
set(CJSON_PREFIX_DIR ${THIRD_PARTY_SOURCE_PATH}/cJSON)
set(CJSON_INSTALL_DIR ${THIRD_PARTY_INSTALL_PATH}/install/cJSON)
set(CJSON_INCLUDE_DIR
    "${CJSON_INSTALL_DIR}/include"
    CACHE PATH "cJSON include directory." FORCE)

set(CJSON_LIBRARIES
    "${CJSON_INSTALL_DIR}/lib/libcjson.a"
    CACHE FILEPATH "cjson library." FORCE)

include_directories(${CJSON_INCLUDE_DIR})

ExternalProject_Add(
  extern_cJSON
  SOURCE_DIR ${CJSON_PREFIX_DIR}
  UPDATE_COMMAND ""
  CMAKE_ARGS -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
             -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
             -DCMAKE_CXX_FLAGS=${CJSON_CMAKE_CXX_FLAGS}
             -DCMAKE_CXX_FLAGS_RELEASE=${CMAKE_CXX_FLAGS_RELEASE}
             -DCMAKE_CXX_FLAGS_DEBUG=${CMAKE_CXX_FLAGS_DEBUG}
             -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
             -DCMAKE_C_FLAGS_DEBUG=${CMAKE_C_FLAGS_DEBUG}
             -DCMAKE_C_FLAGS_RELEASE=${CMAKE_C_FLAGS_RELEASE}
             -DCMAKE_INSTALL_PREFIX=${CJSON_INSTALL_DIR}
             -DCMAKE_INSTALL_LIBDIR=${CJSON_INSTALL_DIR}/lib
             -DCMAKE_POSITION_INDEPENDENT_CODE=ON
             -DCMAKE_BUILD_TYPE=${THIRD_PARTY_BUILD_TYPE}
             -DENABLE_CJSON_TEST=OFF
             -DBUILD_SHARED_AND_STATIC_LIBS=ON
             ${EXTERNAL_OPTIONAL_ARGS}
  CMAKE_CACHE_ARGS
    -DCMAKE_INSTALL_PREFIX:PATH=${CJSON_INSTALL_DIR}
    -DCMAKE_INSTALL_LIBDIR:PATH=${CJSON_INSTALL_DIR}/lib
    -DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=ON
    -DCMAKE_BUILD_TYPE:STRING=${THIRD_PARTY_BUILD_TYPE}
  BUILD_BYPRODUCTS ${CJSON_LIBRARIES})

add_library(cJSON STATIC IMPORTED GLOBAL)
set_property(TARGET cJSON PROPERTY IMPORTED_LOCATION ${CJSON_LIBRARIES})
add_dependencies(cJSON extern_cJSON)