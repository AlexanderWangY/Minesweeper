cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(minesweeper)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "/lib/cmake/SFML")
set(ASSET_DIR ${CMAKE_SOURCE_DIR}/src/files)

file(COPY ${ASSET_DIR} DESTINATION ${CMAKE_BINARY_DIR})
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)
add_executable(minesweeper ${SOURCE_FILES})
target_link_libraries(minesweeper sfml-system sfml-window sfml-graphics sfml-audio pthread)
