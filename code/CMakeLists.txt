cmake_minimum_required(VERSION 3.20)

# Set the project name
project(cpp)

set(PROJECT_LIB ${PROJECT_NAME}_Lib)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ensure the bin directory exists
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add source and include directories
include_directories(${PROJECT_SOURCE_DIR}/inc)

# # Add subdirectory for TinyXML2
# add_subdirectory(${CMAKE_SOURCE_DIR}/external/tinyxml2)

# Find SDL2 and CURL
# find_package(SDL2 REQUIRED)
# find_package(CURL REQUIRED)

# # Include SDL2 and CURL directories
# include_directories(${SDL2_INCLUDE_DIRS})
# include_directories(${CURL_INCLUDE_DIRS})

# recursively find all source files
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Create a library from the source files
add_library(${PROJECT_LIB} STATIC ${SRC_FILES})

# # Link libraries against own library
# target_link_libraries(${PROJECT_LIB} PRIVATE tinyxml2 ${CURL_LIBRARIES} ${SDL2_LIBRARIES})

# Define executable for main application
add_executable(${PROJECT_NAME} src/main.cpp)

# Link libraries against application
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_LIB})

# Option to enable debug mode
option(ENABLE_DEBUG "Enable debug mode" ON)

if(ENABLE_DEBUG)
    # Set build type to Debug if not already set
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Debug)
    endif()
    # Add debug flags
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
endif()
