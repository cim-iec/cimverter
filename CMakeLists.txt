cmake_minimum_required(VERSION 3.5)
project(CIM2Mod)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# Find CIMParser
find_package(CIMParser REQUIRED)

# Find Boost
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")
find_package(BOOST)

# Add combile flag to aviod warnings with C++11
set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} -Wno-inconsistent-missing-override")

#include_directories(src)
file(GLOB_RECURSE SRC src/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SRC})

target_link_libraries(CIM2Mod CIMParser)

