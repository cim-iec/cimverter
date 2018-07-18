import os
import csv

def _componentsIdConversion(componentsPath, idMappingDct):
    
    print('Converting component ids...')

    componentsList = []

    with open(componentsPath, 'r') as csvfile:
        saveVec = csv.reader(csvfile, delimiter = ',')
        for row in saveVec:
            componentsList.append(row)

    idCounter = 1
    for component in componentsList:
        if component[0] in idMappingDct.keys():
            print("Error: ID %s is not unique!" % component[0])
        else:
            idMappingDct[component[0]] = idCounter
            component[0] = idCounter
            idCounter += 1
    
    with open(componentsPath, 'w') as csvfile:
        writer = csv.writer(csvfile)
        for component in componentsList:
            writer.writerow(component)

def _electricalGridIdConversion(elGridPath, idMappingDct):

    print('Converting electrical grid ids...')

    electricalGridList = []

    with open(elGridPath, 'r') as csvfile:
        saveVec = csv.reader(csvfile, delimiter = ',')
        for row in saveVec:
            electricalGridList.append(row)
    
    for cable in electricalGridList:
        for x in range(0,2):
            if cable[x] in idMappingDct.keys():
                cable[x] = idMappingDct[cable[x]]
            
            else:
                print("Error: ID %s does not relate to any component!" % cable[x])

        if int(cable[1]) < int(cable[0]):
            cable[0],cable[1] = cable[1],cable[0]

    electricalGridList.sort(key=lambda k: k[0])
    
    with open(elGridPath, 'w') as csvfile:
        writer = csv.writer(csvfile)
        for cable in electricalGridList:
            writer.writerow(cable)

def convertIDs(path, idMappingDct):
    _componentsIdConversion('/'.join([path, 'components.csv']),idMappingDct)
    _electricalGridIdConversion('/'.join([path, 'el_grid.csv']), idMappingDct)