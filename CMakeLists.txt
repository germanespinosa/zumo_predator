cmake_minimum_required(VERSION 3.3)

project(zumo_predator)
find_package(LibPixy2)
find_package(GComm CONFIG QUIET)

add_executable( zumo_predator
        src/predator.cpp
        src/preyfinder.cpp
        include/preyfinder.h)

target_include_directories( zumo_predator PUBLIC ${PIXY2_INCLUDE_DIRS} include)

target_link_libraries( zumo_predator
        PUBLIC
        ${PIXY2_LIBRARIES}
        gcomm)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")