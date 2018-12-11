# What is CIMverter
CIMverter is a tool to convert CIM-XML-RDF files into Modelica code.
It was developed and is maintained by  the *Institute for Automation of Complex Power Systems* at *RWTH Aachen University*. 
For further project information, as well as a documentation of the CIM standard, visit *https://www.fein-aachen.org/projects/*

For **non-commercial** use this software is licensed under the terms in the included [LICENSE](LICENSE) file.
In case of **commercial** use you are required to negotiate a proper license model with the *Institute for Automation of Complex Power Systems* at *RWTH Aachen University*. Therefore please write to [acs-sek@eonerc.rwth-aachen.de](mailto:acs-sek@eonerc.rwth-aachen.de).

## Getting started 
CIMverter needs the following dependencies to work properly:
* cmake >=3.5
* clang
* Boost >= 1.60.0
* ctemplate >= 2.3
* libconifg++
* as submodule: libcimpp with arabica
* (Doxygen)

To use CIMverter on a Ubuntu Linux system first install the needed dependencies.

    sudo apt-get update
    sudo apt-get install cmake clang build-essential g++ python-dev autotools-dev libicu-dev build-essential libbz2-dev libboost-all-dev libctemplate-dev doxygen graphviz libconfig++-dev

After installing the dependencies, the simple steps to get and build CIMverter are: 

    git clone https://github.com/RWTH-ACS/CIMverter.git
    cd CIMverter
    git submodule update --init --recursive --remote
    mkdir build
    cd build/
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make -j4

The binary will be placed in `/build/bin`

Optionally, one can create the documentation of the project by entering `/build` and typing:

    make document
    
    
To use CIMverter, go to `/build/bin` and type `./CIMverter --help` to get the latest usage informations. 
***

***
## For developers:

To update the latest submodules enter the respective submodule directory pull the needed version:

    1. cd submodule directory
    2. git checkout master or git checkout release
    3. git pull
    4. git submodule update


To use CIMverter in Debug mode, change the build version to Debug:

    cd build/
    cmake -DCMAKE_BUILD_TYPE=Debug ..

We recommend using clion IDE with cmake build system:

* Makefile will not be used any more because arabica xml parser

## Known Errors
### Authority problems
If your project Folder has authority problems, change the owner of it:

    sudo chown -R [your account username] CIMverter/
    
### setDependencyCheckOff() should be added right now before bug fixed of the CIM Parser
    see line 133 in main.cpp
    
### Solve Eclipse CDT indexer unresolve inclusion problem:

* Right click Project-> Properties-> Paths and Symbols -> Includes in GNU c++:

  * add GeneratedCode Path ../GeneratedCode and ../GeneratedCode/IEC61970
  * add glib-2.0 Path /usr/include/glib-2.0
  * add glibmm-2.4 Path /usr/include/glibmm-2.4

* If Eclipse CDT indexer does not know c++11 containers, try:
  * http://stackoverflow.com/questions/17131745/eclipse-cdt-indexer-does-not-know-c12-containers
