cmake_minimum_required(VERSION 2.8)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

project(cm5UP)
set (SOURCES "main.cpp"
    "atomdata.cpp"
    "moldata.cpp")

include_directories(.)
add_executable(${PROJECT_NAME} ${SOURCES})
