#!/bin/bash

# pass the argument 
scriptName=$1
echo $scriptName
output=$(omc $scriptName)
if [[ $output == *"false"* ]]; then
  echo "Error!" $output
  exit 125
else
  echo $output
fi
