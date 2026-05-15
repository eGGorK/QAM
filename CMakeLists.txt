cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(QAM)

set(SOURCES main.cpp AWGNgenerator.cpp QAM.cpp)

add_definitions(-DPROJECT_ROOT="${CMAKE_SOURCE_DIR}")
add_executable(QAM ${SOURCES})