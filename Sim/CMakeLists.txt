cmake_minimum_required(VERSION 3.28.3)
project(SimSubsystems LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Your main sources (excluding main.cpp for library)
set(SIM_SOURCES
    Vehicles/VehicleBase.cpp
    Vehicles/Drone.cpp
    Vehicles/Target.cpp
)

# Create a library for testable code
add_library(SimLib ${SIM_SOURCES})
target_include_directories(SimLib PUBLIC ${CMAKE_SOURCE_DIR})

# Main executable
add_executable(SimSubsystems main.cpp)
target_link_libraries(SimSubsystems PRIVATE SimLib)

# --- Google Test ---
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Test executable
add_executable(SimTests tests/test_vehicles.cpp)
target_link_libraries(SimTests PRIVATE SimLib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(SimTests)
