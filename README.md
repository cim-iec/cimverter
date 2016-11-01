# CIM2Mod

This tool is used to convert CIM-XML-RDF files into Modelica code.

### Dependencies:
* Boost >= 1.60.0
* ctemplate >= 2.3
* libconifg++
* CIMParser


#### To build the CIM2Mod using cmake by following steps:

##### 1. Create build directory

    mkdir build

##### 2. Change into build directory and run cmake (with -DCMAKE_INSTALL_PREFIX=<PREFIX> for installation under <PREFIX> directory instead of the default '/usr/local')

    cd build/
    cmake .. -DCMAKE_INSTALL_PREFIX=<PREFIX>


##### 3. Compile CIM2Mod library

    make -j4


##### 4. [optional] Generate doxygen documentation

    make doc


#### Usage:
    ./CIM2Mod example.xml example.mo

  The tool generates the file: `example.mo`
