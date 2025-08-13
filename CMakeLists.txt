cmake_minimum_required(VERSION 3.10)
project(VehicleSimNoDB)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main simulation executable
add_executable(VehicleSim
    main.cpp
    Vehicle.cpp
    Simulation.cpp
)

# Manual tests executable (no gtest, just console output)
add_executable(ManualTests
    ManualTests.cpp
    Vehicle.cpp
    Simulation.cpp
)
