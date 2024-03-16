cmake_minimum_required(VERSION 3.28.1)
project(cpp_3d_renderer VERSION 0.1.0 LANGUAGES C CXX)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "/Ox")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "-O3")
else()
    message(SEND_ERROR "Only GCC and MSVC are supported, proceed at your own risk.")
endif()


find_package(sfml REQUIRED)
find_package(Eigen3 REQUIRED)

include_directories(${Eigen3_INCLUDE_DIR})

add_executable(${PROJECT_NAME} main.cpp Renderer.cpp RGBA32Image.cpp RGBA32Color.cpp DisplayUtils.cpp Triangle.cpp Camera.cpp ShapeBuilder.cpp Application.cpp)
target_link_libraries(${PROJECT_NAME} sfml::sfml Eigen3::Eigen)
