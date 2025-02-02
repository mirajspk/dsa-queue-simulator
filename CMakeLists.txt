cmake_minimum_required(VERSION 3.28)
project(simulator LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

include_directories(${CMAKE_SOURCE_DIR}/src/header)

file(GLOB SOURCES src/*.cpp)
add_executable(simulator ${SOURCES})
target_compile_features(simulator PRIVATE cxx_std_17)
target_link_libraries(simulator PRIVATE sfml-graphics sfml-window)