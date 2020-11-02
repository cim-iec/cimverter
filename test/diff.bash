#!/bin/bash

# pass the argument a or f to CIMverter to indicate if the xml is in a folder or just a single file
fileName=$1
comm -3 <(sort outputs/$fileName) <(sort modelica/$fileName)


