# Usage 
CIMverter takes an CIM-XML-RDF file as input and outputs an modelica file which can be simulated based on the [ModPowerSystems](https://git.rwth-aachen.de/acs/public/simulation/modpowersystems) library.
To use CIMverter, one must be located in the 'build/bin' directory.
You can run the executable from the command-line, specifying a xml file and certain options. For instance:  
```bash
./CIMverter -f /path/to/my/xml/file.xml -o outputName 
```

### Options
	-f		path to a single xml file  
	-a		path to a folder which contains one or multiple xml files  
	-o		name of the output file  
	-t		specify the template that should be used. The default template is ModPowerSystems
	--help	show usage options
	--verbose display additional information

You can run CIMverter from outside 'build/bin' by exporting the path to the executable. For instance:  
```bash
export CIMVERTER_HOME=your/path/to/build/bin/
./bin/CIMverter -f /path/to/my/xml/file.xml -o outputName 
```




