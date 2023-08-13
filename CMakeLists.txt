project(testTask)
cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(${INCLUDE_DIR})
add_executable(${PROJECT_NAME} main.cpp ${SRC_DIR}/client.cpp ${SRC_DIR}/loadBalancer.cpp ${SRC_DIR}/server.cpp ${SRC_DIR}/settingsParser.cpp)