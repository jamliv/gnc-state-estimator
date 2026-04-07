cmake_minimum_required(VERSION 3.10)

project(gnc_state_estimator)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(sim
    src/main.cpp
    src/truth_model.cpp
    src/gps_sensor.cpp
    src/constellation.cpp
    src/kalman_filter.cpp
)

add_custom_target(run 
    COMMAND ./sim
)