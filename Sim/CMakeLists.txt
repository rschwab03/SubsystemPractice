
# The Two-Step CMake Workflow                                                                                                                                  
#   CMake separates configuration (generating build files) from building (actually compiling). You do this  
#   once from your project root (/home/ryan-schwab/Simulations/Cpp Scripts/Sim/):                             
                                                                                                          
#   Step 1: Configure (one time, or when CMakeLists.txt changes)                                              
                                                                                                          
#   cmake --preset default                                                                                    
                                                                                                          
#   This reads CMakeLists.txt, downloads Google Test, and generates Makefiles inside the build/ directory. The
#    preset default is defined in CMakePresets.json — it sets the build type to Debug and puts all build    
#   output in build/.                                                                                         
                                                                                                          
#   You only need to re-run this if you change CMakeLists.txt (e.g., add a new source file).                  
   
#   Step 2: Build                                                                                             
                                                                                                          
#   cmake --build build

#   This compiles everything. It produces:                                                                    
#   - build/SimSubsystems — your main executable
#   - build/SimTests — your test executable                                                                   
                                                                                                          
#   ---                                                                                                       
#   Running Things                                                                                          
                
#   Run the simulation:
#   ./build/SimSubsystems                                                                                     
                       
#   Run the tests:                                                                                            
#   cd build && ctest                                                                                         
#   Or run the test binary directly for more verbose output:                                                  
#   ./build/SimTests                                                                                          
                                                                                                            
#   ---                                                                                                       
#   Day-to-Day Workflow                                                                                       
                                                                                                          
#   Once configured, your typical loop is just:
                                                                                                            
#   1. Edit a .cpp or .hpp file
#   2. cmake --build build                                                                                    
#   3. ./build/SimSubsystems or ./build/SimTests                                                              
                                                                                                            
#   CMake is smart about incremental builds — it only recompiles files that changed.                          
                                                                                                            
#   ---                                                                                                       
#   Adding New Source Files                                                                                 
                                                                                                            
#   When you add a new .cpp file to the project, you need to add it to CMakeLists.txt:8-12 in the SIM_SOURCES
#   list, then re-run cmake --preset default once.


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
