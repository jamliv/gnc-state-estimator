cmake_minimum_required(VERSION 3.10)

project(gnc_state_estimator)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(gnc_state_estimator
    src/main.cpp
)