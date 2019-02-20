# CIMverter
CIMverter is a tool to convert CIM-XML-RDF files into Modelica code.
It was developed and is maintained by  the *Institute for Automation of Complex Power Systems* at *RWTH Aachen University*. 
For further project information, as well as a documentation of the CIM standard, visit *https://www.fein-aachen.org/projects/*

## Licensing
For **non-commercial** use this software is licensed under the terms in the included [LICENSE](LICENSE) file.
In case of **commercial** use you are required to negotiate a proper license model with the *Institute for Automation of Complex Power Systems* at *RWTH Aachen University*. Therefore please write to [acs-sek@eonerc.rwth-aachen.de](mailto:acs-sek@eonerc.rwth-aachen.de).

## Dependencies:
* cmake >=3.5
* clang
* Boost >= 1.60.0
* ctemplate >= 2.3
* libconifg++
* as submodule: libcimpp with arabica
* (Doxygen)


## Getting started

### Installation of depenencies
```bash
sudo apt-get update
sudo apt-get install cmake clang build-essential g++ python-dev autotools-dev libicu-dev build-essential libbz2-dev libboost-all-dev libctemplate-dev doxygen graphviz libconfig++-dev
```
### Get CIMverter
```bash
git clone --recurse-submodules https://github.com/RWTH-ACS/CIMverter.git
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


## Usage

### Sample grid
This will generate a Modelica system model file `CIGRE.mo` which can be simulated based on the [ModPowerSystems](https://git.rwth-aachen.de/acs/public/simulation/modpowersystems) library.
```bash
cd bin
./CIMverter -a ../../samples/CIGRE_MV_Rudion_With_LoadFlow_Results/ -o CIGRE
```

### Help
```bash
./CIMverter --help
``` 

***

***
## For developers:

### How to update the lastest submodule:

    1. cd submodule directory
    2. git checkout master or git checkout release
    3. git pull
    4. git submodule update

### Buid in debug mode:

    cd build/
    cmake -DCMAKE_BUILD_TYPE=Debug ..

### Recommand using clion IDE with cmake build system:

* Makefile will not be used any more because arabica xml parser

### Project Folder may has authority problem on Linux:

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
