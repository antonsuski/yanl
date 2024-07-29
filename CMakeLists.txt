cmake_minimum_required(VERSION 3.20)
project(YANL)

add_library(yanl STATIC src/yanl.cxx)
target_include_directories(yanl PRIVATE include)
target_include_directories(yanl INTERFACE {PROJECT_SOURCE_DIR}/include)
