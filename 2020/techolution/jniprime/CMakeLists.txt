cmake_minimum_required(VERSION 3.9)
project(com_techolution_jni VERSION 1.0.1 DESCRIPTION "Primality test in C++")
set(CMAKE_BUILD_TYPE Release)
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS}
	            "com")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES com/com_techolution.cpp)
add_library(com_techolution_jni SHARED ${SOURCE_FILES})
