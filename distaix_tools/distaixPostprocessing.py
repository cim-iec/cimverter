# This script is used for postprocessing modelica files from CIM2Distaix project.

import fileConverter
import idConverter
import parameterReplacer

idMappingDct = {}

fileConverter.convertFile('./default_output_name.mo')
idConverter.convertIDs('.',idMappingDct)
parameterReplacer.replaceDefaultParameters('./default_parameters.csv','./components.csv')
