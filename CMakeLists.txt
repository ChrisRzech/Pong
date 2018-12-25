cmake_minimum_required(VERSION 3.7)
project(Pong)

set(CMAKE_CXX_STANDARD 14)

#SFML stuff
set(SFML_ROOT "C:/SFML-2.4.2")
set(CMAKE_MODULE_PATH "C:/SFML-2.4.2/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML COMPONENTS graphics window system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

#header files
set(HEADERS
        source/PongLib/PongLib.hpp)

#source files
set(SOURCES
        source/main.cpp
        source/randDirection.cpp
        source/PongLib/Paddle/Paddle.cpp
        source/PongLib/Ball/Ball.cpp)

#add files to executable
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
