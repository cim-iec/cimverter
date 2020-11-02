#!/bin/bash

# pass the argument a or f to CIMverter to indicate if the xml is in a folder or just a single file
fileName=$1
diff --suppress-common-lines --side-by-side <(sort outputs/$fileName) <(sort modelica/$fileName)


