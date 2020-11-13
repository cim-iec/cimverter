#!/bin/bash

# pass the argument a or f to CIMverter to indicate if the xml is in a folder or just a single file
type=$1
fileName=$2
cimVersion=$3
currDir=$(pwd)
cd ../build/bin

if [ $type == 'a' ]
    then
    cp $currDir/xml/$fileName/config.cfg config.cfg
    ./CIMverter -a $currDir/xml/$fileName/ -o $fileName
    mv $fileName.mo $currDir/outputs/$cimVersion/$fileName.mo
elif [ $type == 'f' ]
    then 
    ./CIMverter -f $currDir/xml/$fileName -o $fileName
    mv $fileName.mo $currDir/outputs/$cimVersion/$fileName.mo
fi
