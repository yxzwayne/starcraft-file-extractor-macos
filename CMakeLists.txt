cmake_minimum_required(VERSION 3.10)
project(SCAudioExtractor)

# Change from C++11 to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add CascLib subdirectory to build it
add_subdirectory(src/CascLib)

# Add the executable
add_executable(extract_audio src/extract_audio.cpp)

# Include directories for CascLib
target_include_directories(extract_audio PRIVATE src/CascLib/src)

# Link against CascLib
target_link_libraries(extract_audio PRIVATE casc)