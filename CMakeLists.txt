cmake_minimum_required(VERSION 3.16)
project(algoshield2_reference LANGUAGES C)

include("${CMAKE_SOURCE_DIR}/scripts/CMake/config.cmake")

add_subdirectory("src")

if (EXISTS "${CMAKE_SOURCE_DIR}/scripts/CMake/toolchain/${TOOLCHAIN}.cmake")
    include("${CMAKE_SOURCE_DIR}/scripts/CMake/toolchain/${TOOLCHAIN}.cmake")
else ()
    message(FATAL_ERROR "Toolchain \"${TOOLCHAIN}\" not recognized.")
endif ()

