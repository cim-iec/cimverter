# CIMverter
CIMverter is a tool for converting power grid topology files based on CIM-XML-RDF into Modelica system models.

## Dependencies:
* cmake >=3.5
* clang
* Boost >= 1.60.0
* ctemplate >= 2.3
* libconifg++
* as submodule: libcimpp with arabica
* (Doxygen)

## Installation

### Installation of depenencies
```bash
sudo apt-get update
sudo apt-get install cmake clang build-essential g++ python-dev autotools-dev libicu-dev build-essential libbz2-dev libboost-all-dev libctemplate-dev doxygen graphviz libconfig++-dev
```
### Get CIMverter
```bash
git clone --recurse-submodules <CIMverter's Git URL>
```

### Build CIMverter with all submodules
```bash
mkdir build
cd build/
cmake ..
make -j4
```

### Generate doxygen documentation (optional)
```bash
make document
```

### Usage
There are two possibilitys to execute CIMverter. 
First:
```bash
cd bin
./CIMverter --help
``` 
Second: 
```bash
export CIMVERTER_HOME=your/path/to/build/bin/
./bin/CIMverter --help
``` 


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
