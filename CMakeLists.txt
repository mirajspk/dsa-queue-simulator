cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

include_directories(${CMAKE_SOURCE_DIR}/src/header)

set(SOURCES
    src/simulator.cpp
    src/traffic_generator.cpp
    src/VehicleClass.cpp
)

add_executable(simulator ${SOURCES})
target_compile_features(simulator PRIVATE cxx_std_17)
target_link_libraries(simulator PRIVATE SFML::Graphics SFML::Window)