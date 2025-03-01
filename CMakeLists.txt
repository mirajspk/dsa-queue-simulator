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

add_executable(traffic_generator 
    src/traffic_generator.cpp 
    src/VehicleClass.cpp
)
target_compile_features(traffic_generator PRIVATE cxx_std_14)
target_link_libraries(traffic_generator PRIVATE sfml-graphics sfml-window sfml-network)

add_executable(simulator 
    src/simulator.cpp 
    src/VehicleClass.cpp 
    src/LightQueue.cpp 
    src/LaneTrigger.cpp 
    src/VehicleQueue.cpp 
    src/TrafficControl.cpp
)
target_compile_features(simulator PRIVATE cxx_std_14)
target_link_libraries(simulator PRIVATE sfml-graphics sfml-window sfml-network)