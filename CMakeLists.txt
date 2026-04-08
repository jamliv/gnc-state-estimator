cmake_minimum_required(VERSION 3.10)

project(gnc_state_estimator)

set(CMAKE_CXX_STANDARD 17)

set_directory_properties(PROPERTIES
    ADDITIONAL_MAKE_CLEAN_FILES
    "${CMAKE_SOURCE_DIR}/data/SIM_LOG.txt;${CMAKE_SOURCE_DIR}/data/SIM_RUN_DATA.csv"
)

include_directories(include)

add_executable(sim
    src/main.cpp
    src/truth_model.cpp
    src/gps_sensor.cpp
    src/constellation.cpp
    src/kalman_filter.cpp
    src/logger.cpp
)

add_custom_target(cleanlogs
    COMMAND ${CMAKE_COMMAND} -E remove -f
    ${CMAKE_SOURCE_DIR}/data/SIM_LOG.txt
    ${CMAKE_SOURCE_DIR}/data/SIM_RUN_DATA.csv
)

add_custom_target(run 
    COMMAND ./sim
)