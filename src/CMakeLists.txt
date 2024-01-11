cmake_minimum_required(VERSION 3.28.1)
project(cpp_3d_renderer VERSION 0.1.0 LANGUAGES C CXX)

find_package(sfml REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} sfml::sfml)