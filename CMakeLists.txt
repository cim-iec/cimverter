cmake_minimum_required(VERSION 3.5)
project(CIMverter CXX)

set(CIMverter_MAJOR_VERSION 2)
set(CIMverter_MINOR_VERSION 3)
set(CIMverter_PATCH_VERSION 1)
set(CIMverter_VERSION ${CIMverter_MAJOR_VERSION}.${CIMverter_MINOR_VERSION}.${CIMverter_PATCH_VERSION})

set(USE_CIM_VERSION "IEC61970_17v23_IEC61968_13v11" CACHE STRING "Define CIM Version")
message(STATUS "Building ${PROJECT_NAME} with USE_CIM_VERSION=${USE_CIM_VERSION}")
if(USE_CIM_VERSION STREQUAL "IEC61970_16v29a_SINERGIEN")
 add_definitions(-DSINERGIEN)
endif()

# Find libcimpp
add_subdirectory(${PROJECT_SOURCE_DIR}/libcimpp ${PROJECT_SOURCE_DIR}/build/libcimpp)
# find_package(libcimpp REQUIRED)
# include_directories( ${PROJECT_SOURCE_DIR}/build/libcimpp/ )

# Find Boost
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")
find_package(Boost 1.58 REQUIRED)
include_directories( ${Boost_INCLUDE_DIR} )

# Find Ctemplate
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)
find_package(Ctemplate REQUIRED)
include_directories( ${CTEMPLATE_INCLUDE_DIR} )

# Find libconfig++
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)
find_package(Config++ REQUIRED)
include_directories( ${CONFIG++_INCLUDE_DIR} )

# Add link flags
set(BOOST_LINKER_FLAGS "-lboost_filesystem -lboost_system")
set(CTEMPLATE_LINKER_FLAGS "-lctemplate")
set(CONFIG++_LINKER_FLAGS "-lconfig++")
set(CMAKE_SHARED_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${BOOST_LINKER_FLAGS} ${CTEMPLATE_LINKER_FLAGS} ${CONFIG++_LINKER_FLAGS} " )
set(USE_CIM_TEMPLATE "ModPowerSystems_templates" CACHE STRING "User-specified template")

# Add combined flag to avoid warnings with C++11
set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wno-inconsistent-missing-override")



# copy directories

file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/bin/resource)
file(COPY ${PROJECT_SOURCE_DIR}/ModPowerSystems_templates/ DESTINATION 
${PROJECT_BINARY_DIR}/bin/resource/ModPowerSystems_templates)
file(COPY ${PROJECT_SOURCE_DIR}/PowerGrids_templates/ DESTINATION 
${PROJECT_BINARY_DIR}/bin/resource/PowerGrids_templates)
file(COPY ${PROJECT_SOURCE_DIR}/PowerSystems_templates/ DESTINATION 
${PROJECT_BINARY_DIR}/bin/resource/PowerSystems_templates)
file(COPY ${PROJECT_SOURCE_DIR}/DistAIX_templates/ DESTINATION
${PROJECT_BINARY_DIR}/bin/resource/DistAIX_templates)
file(COPY ${PROJECT_SOURCE_DIR}/src/config.cfg DESTINATION ${PROJECT_BINARY_DIR}/bin)
file(COPY ${PROJECT_SOURCE_DIR}/src/task_alias.csv ${PROJECT_SOURCE_DIR}/src/assignment_alias.csv DESTINATION ${PROJECT_BINARY_DIR}/bin)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# include_directories
file(GLOB_RECURSE SRC_LIST ${PROJECT_SOURCE_DIR}/src/*.cpp)

# compile and link
set(CMAKE_CXX_COMPILER "clang++")
add_executable(${PROJECT_NAME} ${SRC_LIST} src/main.cpp)
target_link_libraries(CIMverter libcimpp ${Boost_LIBRARIES} ${CTEMPLATE_LIBRARIES} ${CONFIG++_LIBRARY})
target_compile_features(CIMverter PUBLIC cxx_range_for)


# Configure Doxyfile
find_package(Doxygen)
if(DOXYGEN_FOUND)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(document ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif(DOXYGEN_FOUND)
