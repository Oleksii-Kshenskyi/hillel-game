cmake_minimum_required(VERSION 3.26.0)
project(hillel-game)

set(GAME_DIR src)
set(GAME_SRC ${GAME_DIR}/main.cpp)

include(${CMAKE_SOURCE_DIR}/conan_toolchain.cmake)

include_directories(${GAME_DIR})

add_executable(${PROJECT_NAME} ${GAME_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES
                                            CXX_STANDARD 20
                                            CXX_STANDARD_REQUIRED ON)