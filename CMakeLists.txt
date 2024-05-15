cmake_minimum_required(VERSION 3.10)
project(SCAudioExtractor)

set(CMAKE_CXX_STANDARD 11)

# Add the executable
add_executable(extract_audio src/extract_audio.cpp)

# Include directories for CascLib
include_directories(src/CascLib/src)

# Add the CascLib source files
file(GLOB CASCLIB_SOURCES "src/CascLib/src/*.cpp")

# Add the CascLib library
add_library(CascLib ${CASCLIB_SOURCES})

# Link CascLib library to the executable
find_library(CASC_LIB NAMES casc PATHS src/CascLib/casc.framework)
if(CASC_LIB)
    target_link_libraries(extract_audio ${CASC_LIB})
else()
    message(FATAL_ERROR "casc library not found")
endif()

set_property(TARGET extract_audio PROPERTY CXX_STANDARD 11)
set_property(TARGET extract_audio PROPERTY CXX_STANDARD_REQUIRED ON)
