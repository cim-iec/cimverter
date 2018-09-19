#!/bin/bash

# pass the argument a or f to CIMverter to indicate if the xml is in a folder or just a single file
type=$1
target_directory=$2
fileName=$3
currDir=$(pwd)
cd ../build/bin

if [ $type == 'a' ]
    then
    ./CIMverter -a $currDir/xml/$target_directory/ -o $fileName
    mv $fileName.mo $currDir/outputs/$fileName.mo
elif [ $type == 'f' ]
    then ./CIMverter -f $currDir/xml/$fileName -o $fileName
    mv $fileName.mo $currDir/outputs/$fileName.mo
fi
