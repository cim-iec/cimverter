import csv

def _readDefaultParameters(path, defaultParametersDct):
    with open(path, 'r') as csvfile:
        saveVec = csv.reader(csvfile, delimiter=',')
        for row in saveVec:
            for count in range(1,len(row)):
                
                parameterName, value = row[count].split('=')
                defaultParametersDct['_'.join([row[0],parameterName])] = value 

def _replaceParameters(path, defaultParametersDct):
    componentsList = []
    with open(path, 'r') as csvfile:
        saveVec = csv.reader(csvfile, delimiter=',')
        for row in saveVec:
            for count in range(0,len(row)):
                if '_default' in row[count]:
                    row[count] = defaultParametersDct['_'.join([row[1],row[count].split('_')[0]])]
            componentsList.append(row)

    with open(path, 'w') as csvfile:
        writer = csv.writer(csvfile)
        for component in componentsList:
            writer.writerow(component)

def replaceDefaultParameters(defaultParametersPath, componentsPath):
    defaultParametersDct = {}
    _readDefaultParameters(defaultParametersPath,defaultParametersDct)
    _replaceParameters(componentsPath,defaultParametersDct)