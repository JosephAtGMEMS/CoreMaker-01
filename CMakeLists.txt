# Copyright (c) 2021 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.19.0)

set(MBED_PATH ${CMAKE_CURRENT_SOURCE_DIR}/mbed-os CACHE INTERNAL "")
set(MBED_CONFIG_PATH ${CMAKE_CURRENT_BINARY_DIR} CACHE INTERNAL "")
#set(APP_TARGET FACTORY)
set(APP_TARGET HELLOWORLD)

include(${MBED_PATH}/tools/cmake/app.cmake)

project(${APP_TARGET} VERSION 1.0)

add_compile_options(-Wno-unused-variable)
add_compile_options(-w)
add_subdirectory(TARGET_AIOT2101)
add_subdirectory(${MBED_PATH})
#add_subdirectory(APP_FACTORY)
add_subdirectory(APP_HELLOWORLD)
