# Build
CIMverter uses the [libcimpp](https://github.com/CIM-IEC/libcimpp) library for deserialization.
Libcimpp is available in different versions. By default CIMverter uses the **IEC61970_17v23_IEC61968_13v11** version. 
If you want to use another libcimpp version you can specify it during the build process.  
To build CIMverter a build directory is created.  
```bash
mkdir build
cd build/
```
The libcimpp version can be configured by using cmake command line arguments.  
```bash
cmake .. -DUSE_CIM_VERSION=CGMES_2.4.15_27JAN2020
make -j4
```
If one wants to use the default libcimpp version one can build CIMverter by typing:  
```bash
cmake ..
make -j4
```


