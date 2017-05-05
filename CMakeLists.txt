cmake_minimum_required(VERSION 3.5)
project(CIM2Mod CXX)

set(CIM2Mod_MAJOR_VERSION 2)
set(CIM2Mod_MINOR_VERSION 3)
set(CIM2Mod_PATCH_VERSION 1)
set(CIM2Mod_VERSION ${CIM2Mod_MAJOR_VERSION}.${CIM2Mod_MINOR_VERSION}.${CIM2Mod_PATCH_VERSION})

# Find CIMParser
add_subdirectory(${PROJECT_SOURCE_DIR}/CIM-XML-Parser ${PROJECT_SOURCE_DIR}/build/CIMParser)
# find_package(CIMParser REQUIRED)
# include_directories( ${PROJECT_SOURCE_DIR}/build/CIMParser/ )

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

# Add combined flag to avoid warnings with C++11
set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wno-inconsistent-missing-override")

# copy directories
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/bin/resource)
file(COPY ${PROJECT_SOURCE_DIR}/modelica_templates/ DESTINATION ${PROJECT_BINARY_DIR}/bin/resource)
file(COPY ${PROJECT_SOURCE_DIR}/src/config.cfg DESTINATION ${PROJECT_BINARY_DIR}/bin)
file(COPY ${PROJECT_SOURCE_DIR}/src/task_alias.csv ${PROJECT_SOURCE_DIR}/src/assignment_alias.csv DESTINATION ${PROJECT_BINARY_DIR}/bin)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# include_directories
file(GLOB_RECURSE SRC_LIST ${PROJECT_SOURCE_DIR}/src/*.cpp)

# compile and link
set(CMAKE_CXX_COMPILER "clang++")
add_executable(${PROJECT_NAME} ${SRC_LIST} src/main.cpp)
target_link_libraries(CIM2Mod CIMParser ${Boost_LIBRARIES} ${CTEMPLATE_LIBRARIES} ${CONFIG++_LIBRARY})
target_compile_features(CIM2Mod PUBLIC cxx_range_for)

# Configure Doxyfile
find_package(Doxygen)
if(DOXYGEN_FOUND)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(document ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif(DOXYGEN_FOUND)
