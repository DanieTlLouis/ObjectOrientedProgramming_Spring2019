
cmake_minimum_required(VERSION 3.8)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/./cmake")

set(CMAKE_CXX_FLAGS "-std=c++14")

find_package(SFML COMPONENTS graphics window system)
include_directories(${SFML_INCLUDE_DIR})

add_executable(bejewled main.cpp)
target_link_libraries(bejewled ${SFML_LIBRARIES})
