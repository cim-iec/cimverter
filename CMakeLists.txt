cmake_minimum_required(VERSION 3.5)
PROJECT(CIM2Mod)

set(CIM2Mod_MAJOR_VERSION 0)
set(CIM2Mod_MINOR_VERSION 1)
set(CIM2Mod_PATCH_VERSION 0)
set(CIM2Mod_VERSION ${CIM2Mod_MAJOR_VERSION}.${CIM2Mod_MINOR_VERSION}.${CIM2Mod_PATCH_VERSION})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Find CIMParser
find_package(CIMParser REQUIRED)
include_directories( ${CIMParser_INCLUDE_DIR} )

# Find Boost
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")
find_package(Boost REQUIRED)
include_directories( ${Boost_INCLUDE_DIR} )

# Find CTemplate
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")
find_package(CTemplate REQUIRED)
include_directories( ${CTemplate_INCLUDE_DIR} )

# Add link flags
set(BOOST_LINKER_FLAGS "-lboost_filesystem -lboost_system")
set(CTEMPLATE_LINKER_FLAGS "--lctemplate")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${BOOST_LINKER_FLAGS} ${CTEMPLATE_LINKER_FLAGS}" )

# Add combile flag to aviod warnings with C++11
set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wno-inconsistent-missing-override")

#include_directories(src)
file(GLOB_RECURSE SRC src/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SRC})
target_include_directories(${PROJECT_NAME} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)
target_include_directories(${PROJECT_NAME} PUBLIC ${CIMParser_INCLUDE_DIR} ${Boost_INCLUDE_DIR} ${CTemplate_INCLUDE_DIR})

add_executable(CIM2Mod ${CMAKE_CURRENT_LIST_DIR}/../src/main.cpp)
target_link_libraries(CIM2Mod CIMParser Boost CTemplate)
