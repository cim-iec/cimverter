#!/bin/bash

# pass the argument a or f to CIMverter to indicate if the xml is in a folder or just a single file
fileName=$1
cimVersion=$2
comm -3 <(sort outputs/$cimVersion/$fileName) <(sort modelica/$fileName)


