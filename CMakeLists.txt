cmake_minimum_required(VERSION 3.15)
project(DataCenterManager)

set(CMAKE_CXX_STANDARD 11)
set(GCC_COVERAGE_COMPILE_FLAGS " -g")
add_executable(DataCenterManager AVLTree.h Auxiliaries.h DataCenterManager.h DataCenter.h library1.h library1.cpp
        main1.cpp )
