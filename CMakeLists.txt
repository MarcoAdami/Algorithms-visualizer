cmake_minimum_required(VERSION 3.27.8)

# Project setup
project(CMakeSFMLProject LANGUAGES CXX)

# Set output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include FetchContent module
include(FetchContent)

# Fetch and configure SFML
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
)
FetchContent_MakeAvailable(SFML)

# Add the executable
add_executable(main
    src/main.cpp 
    src/Algorithm.cpp
    src/StatusBar.cpp
    src/Blocks.cpp
)

# Link SFML libraries
target_link_libraries(main PRIVATE sfml-graphics)

# Set C++ standard
target_compile_features(main PRIVATE cxx_std_17)


