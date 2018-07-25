# This module is used to replace unset parameters by default paramters.
# Default parameters are read from a file, given by "defaultParametersPath".
# Each default parameter will be stored by name in a dictionary.
# During replacement, all unset parameters (indicated by parametername"_default"), will be replaced by the stored value.
#
# File strucutre:
# >> default_parameters.csv
# typeName, defaultparameter1 = value, defaultparameter2 = value2, ...

import csv

def _readDefaultParameters(path, defaultParametersDct):
    with open(path, 'r') as csvfile:
        saveVec = csv.reader(csvfile, delimiter=',')
        for row in saveVec:
            for count in range(1,len(row)):
                
                parameterName, value = row[count].split('=')
                defaultParametersDct['_'.join([row[0],parameterName]).replace(" ","")] = value

def _replaceParameters(path, defaultParametersDct):
    componentsList = []
    with open(path, 'r') as csvfile:
        saveVec = csv.reader(csvfile, delimiter=',')
        for row in saveVec:
            for count in range(0,len(row)):
                if '_default' in row[count]:
                    row[count] = defaultParametersDct['_'.join([row[1],row[count].split('_default')[0]])].replace(" ","")
            componentsList.append(row)

    with open(path, 'w') as csvfile:
        writer = csv.writer(csvfile)
        for component in componentsList:
            writer.writerow(component)

def replaceDefaultParameters(defaultParametersPath, componentsPath):
    defaultParametersDct = {}
    _readDefaultParameters(defaultParametersPath,defaultParametersDct)
    print(defaultParametersDct)
    _replaceParameters(componentsPath,defaultParametersDct)