# Configuration

CIMverter can be configured using the config.cfg located in src/config.cfg (resp. build/bin/config.cfg).  

At the top level, the configuration file consists of these sections:  
- SV Settings
- Global Settings
- Unit Conversion Options
- File Path Configuration
- System Configuration
- Single Phase 

## SV Settings
### useSVforEnergyConsumer (bool)
specify if the PNom of PQLoads is specified via a SVPowerFlow (true) or directly in the pfixed property (false).

### useSVforGeneratingUnit (bool)
specify if the PGen of GeneratingUnits is specified via a SVPowerFlow (true) or directly in the initialP property (false).


### useSVforExternalNetworkInjection (bool)
specify if the phiV value of the Slack is read from a SVVoltage

## Global Settings
### default_baseKV (float)
defines the base Voltage which is used for Busbars in case there is no specific  BaseVoltage connected.

### tapStepPosition
If set to "original" the tapStepPosition of power transformers is directly read from the xml. Otherwise the tapStepPosition is computed as the xml (value - 1) * 1000.

### make_unique_names (bool)
Append memory addresses to the component names to guarantee unique names. 
This might be needed when the xml file has no unique names for the components.

### ignore_unconnected_components (bool)
Specify if all components should be generated regardless of their connection status (false) or if only components connected to the ExternalNetwork (Slack) should be generated (true). In case the option equals "true" and there is no Slack defined the largest connected component is created.

### add_Vnom_to_PiLine (bool)
Specify if the VNOM should be added to the PiLine.

### source_tool_name = "NEPLAN";
name of the source tool
### apply_Neplan_fix = true; 
specify if neplan fixe should be applied


## Unit Conversion Options
The Unit Conversion Options can be used to specify the unit system that is used in the input.xml to prevent mismatches between input unit system and output unit system.  
### enable (bool)
states if any unit conversion should be applied
### voltage_unit (kV, mV, MV)
States the unit used for voltages in the input.xml. The modelica files uses V as unit.  
For example if we have a PQLoad with VNOM = 1 in the input XMl and voltage_unit = "kV" CIMverter will multiply the VNOM with 1000 so that the modelica file has VNOM = 1000.

### current_unit (kA, mA, MA)
States the Ampere unit used in the input.xml. The modelica files uses A as unit.  
For example if we have a PiLine with IMAX = 1 in the input XMl and current_unit = "kA" CIMverter will multiply the IMAX with 1000 so that the modelica file has IMAX = 1000.

### active_power_unit (kW, mW, MW)
States the Watt unit used in the input.xml. The modelica files uses W as unit.  
For example if we have a PQLoad with PNOM = 1 in the input XMl and active_power_unit = "kW" CIMverter will multiply the PNOM with 1000 so that the modelica file has PNOM = 1000.

### reactive_power_unit (kvar, mvar, Mvar)
States the Volt-ampere unit used in the input.xml. The modelica files uses var as unit.  
For example if we have a PQLoad with QNOM = 1 in the input XMl and ractive_power_unit = "kvar" CIMverter will multiply the QNOM with 1000 so that the modelica file has QNOM = 1000.

### length_unit (m, km)
States if lengths are given in m or km in the input.xml. The unit used in modelica is km.

## File Path Configuration

### input_directory_path No CLUE WHAT THIS IS USED FOR?

### output_directory_path (string:path)="../path/to/my/CIMverter/output/directory"
Specifies the path to which the modelica files are generated starting from "build/bin"

### template_directory_path (string:path)="./path/to/templates"
Specifies the path to the templates that should be used. Starting from "build/bin"

## System Configuration

### enable (bool)

### topology_trans_parameter [a, b, c, d]
defines the parameters for coordinate system conversion.

### coordinate [a, b, c, d]
Specifies the dimensions of the modelica coordinate system.

### label 
```
simMode = "steady";
        init = "steady";
        annotation = {
            extent = [0.0, -30.0, 30.0, 0.0];       //label icon size
            visible = true;
        };
```

### annotation 
Position of the label in the modelica file

### use_TPNodes (bool)
Specify if TPNode model is used (true) or Bus-Breaker model (false)

## single_phase
No clue what this is used for










