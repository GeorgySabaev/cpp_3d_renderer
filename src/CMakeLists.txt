cmake_minimum_required(VERSION 3.28.1)
project(cpp_3d_renderer VERSION 0.1.0 LANGUAGES C CXX)
set( CMAKE_CXX_STANDARD 20)
set( CMAKE_CXX_STANDARD_REQUIRED True )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
set( CMAKE_TOOLCHAIN_FILE conan_toolchain.cmake )

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "/Ox /EHsc")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "-O3")
else()
    message("Only GCC and MSVC add optimisation flags, proceed at your own risk.")
endif()

list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
find_package(SFML REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(tinyobjloader REQUIRED) 

include_directories(${Eigen3_INCLUDE_DIR})
include_directories(${tinyobjloader_INCLUDE_DIR})

add_executable(${PROJECT_NAME} main.cpp Renderer.cpp RGBA32Image.cpp RGBA32Color.cpp Triangle.cpp Camera.cpp ShapeBuilder.cpp Application.cpp Model.cpp)
target_link_libraries(${PROJECT_NAME} sfml::sfml Eigen3::Eigen tinyobjloader::tinyobjloader)
 