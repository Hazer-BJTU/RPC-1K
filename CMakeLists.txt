cmake_minimum_required(VERSION 3.20)

project(RPC-1K VERSION 0.1)

include(CheckCXXCompilerFlag)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(COMPILER_OPTION_FLAGS "-g" "-rdynamic" "-O3")

message(STATUS "Global option flags used: ${COMPILER_OPTION_FLAGS}")
add_compile_options(${COMPILER_OPTION_FLAGS})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

include_directories(
    "${PROJECT_SOURCE_DIR}/putils/include"
    "${PROJECT_SOURCE_DIR}/core/include"
)

add_subdirectory(putils)
add_subdirectory(core)
