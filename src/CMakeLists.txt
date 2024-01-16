cmake_minimum_required(VERSION 3.28.1)
project(cpp_3d_renderer VERSION 0.1.0 LANGUAGES C CXX)

find_package(sfml REQUIRED)

include_directories(${GLM_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.cpp Renderer.cpp RGBA32Image.cpp Vector3.cpp DisplayUtils.cpp LinAlg.cpp)
target_link_libraries(${PROJECT_NAME} sfml::sfml)
