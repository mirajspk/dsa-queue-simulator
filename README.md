# Traffic Simulation System

## Overview

A **Traffic Simulation System** developed for the COMP 202 course at the Department of Computer Science and Engineering, Kathmandu University. It simulates vehicle movement through a 4-way intersection with adaptive traffic lights, using **C++**, **SFML**, and  **queue data structure**.

## Demonstration

Below is a GIF demonstrating the simulation in action, showing vehicles navigating the intersection with adaptive traffic lights:

![Simulation GIF](assets/Clip.gif)

## Run the Simulation

### Prerequisites
- **C++ Compiler**: Ensure you have a C++ compiler installed.
- **CMake**: Required to generate the build system and automatically fetch SFML during the build process.

**Note**: The program was developed and tested on macOS. To run on Linux or Windows systems, you may need to extend the current `CMakeLists.txt` to support your system.

### Steps
1. **Clone and Build**:
   ```bash
   git clone https://github.com/mirajspk/dsa-queue-simulator.git
   cd dsa-queue-simulator
   cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
   cmake --build build

2. **Run each program**:
    ```bash
    ./build/bin/traffic_generator
    ./build/bin/simulator
 ## Report
 Check out the detailed report [here](docs/Report.pdf)