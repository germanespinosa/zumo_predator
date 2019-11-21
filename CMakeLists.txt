cmake_minimum_required(VERSION 3.3)

project(prey)
find_package(LibPixy2)
find_package(GComm CONFIG QUIET)

add_executable( prey src/prey.cpp include/prey.h)

target_include_directories( prey PUBLIC ${PIXY2_INCLUDE_DIRS} include)

target_link_libraries(prey
        PUBLIC
        ${PIXY2_LIBRARIES}
        gcomm)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")