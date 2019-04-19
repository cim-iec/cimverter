# CIM2DistAIX
An extension of CIM2Mod to enable conversion from CIM-XML-RDF files into DistAIX format.

## Usage
To convert into DistAIX format, simply change the used templates to ``DistAIX_templates``, using the parameter ``-t``, when executing CIM2Mod.
E.g.:
```
cd build/bin
./CIM2Mod -t "DistAIX_templates" -a <Path>
```
The output will differ from standard CIM2Mod:
- ``default_output_name.mo`` -> ``default_output_name.csv`` : Modified output file in CSV-format.
- ``components.csv``: Holds all components used in the DistAIX Simulator.
- ``el_grid.csv``: Holds all cables used in the DistAIX Simulator.

To replace all parameters, needed for the simulation, that can not be retrieved from the CIM files additional default parameter flags are set by the templates. By default, for each possible component there already exists a parameter-value pair for all corresponding parameters in ``/resource/DistAIX_templates/default_parameters.csv``. Those can be modified before execution. Each row represents one type of component and has to follow the following structure:

```
ComponentType,parameter_flag1=value,parameter_flag2=value,...
```

## Structure
- ``DistAIX_templates``: Folder containing all templates, the default_parameters.csv file as well as a README.
    - ``BusBar.tpl``: Used to model nodes
    - ``Connections.tpl``: Used to model lossless cables
    - ``PiLine.tpl``: Used to model lossy cables
    - ``PQLoad.tpl``: Used to model Load components
    - ``Slack.tpl``: Used as Slack
    - ``Transformer.tpl``: Used as Transformer
    - ``SolarGenerator.tpl``: Used to model PV components
    - ``WindGenerator.tpl``: Used to model Wind components
    <br></br>
    - ``distaix.tpl``: Defines the structure of the output file before postprocessing


## DistAIXPostprocessor
In addition to the new templates, the DistAIXPostprocessor class is needed to assure output files in the correct format.
- ``void postprocess(...)``: Public function used to initiate postprocessing.
<br></br>
- ``void convertInputFile(...)``: Converts modelica output file into CSV-file.
- ``void splitCSVFile(...)``: Splits resulting CSV-file into two separate files at the corresponding flags.
- ``void orderComponents(...)``: Traverses the grid in a depth-first sense to ensure proper ordering.
- ``void convertComponentIDs(...)``: Converts component string IDs into ascending integer IDs.
- ``void convertElGridIDs(...)``: Converts component string IDs into ascending integer IDs.
- ``void setDefaultParameters(...)``: Reads in default parameters from CSV-file and replaces occuring placeholders with their corresponding value. 
- ``void writeCSVFile(...)``: Writes CSV-file from vector.
