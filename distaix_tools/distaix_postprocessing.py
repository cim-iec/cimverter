# This script is used for postprocessing modelica files from CIM2Distaix project.

import os
import csv
from shutil import copyfile

###############################################################################################
## Helper Functions                                                                          ##
###############################################################################################

def modelicaToCSVConversion(path):
    root = os.path.splitext(path)[0]
    #os.rename(path, root + ".csv")
    copyfile(path,root + ".csv")

    return root + ".csv"

def splitCSVFile(path):

    print('Splitting csv file...')

    componentsList = []
    electricalGridList = []

    with open(path, 'r') as csvfile:
        saveVec = csv.reader(csvfile, delimiter = ',')
        for row in saveVec:

            if not row:
                pass
            elif row[0] == 'components.csv':
                currentList = componentsList
            elif row[0] == 'el_grid.csv':
                currentList = electricalGridList
            else:
                currentList.append(row)
        
    with open('components.csv', 'w') as csvfile:
        writer = csv.writer(csvfile)
        for component in componentsList:
            writer.writerow(component)

    with open('el_grid.csv', 'w') as csvfile:
        writer = csv.writer(csvfile)
        for cable in electricalGridList:
            writer.writerow(cable)

def convertFile(path):
    tempCSV = modelicaToCSVConversion(path)
    splitCSVFile(tempCSV)
    os.remove(tempCSV)

def componentsIdConversion(componentsPath, idMappingDct):
    
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

def electricalGridIdConversion(elGridPath, idMappingDct):

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

###############################################################################################
## Main Routine                                                                              ##
###############################################################################################
idMappingDct = {}

convertFile('./default_output_name.mo')
componentsIdConversion('./components.csv', idMappingDct)
electricalGridIdConversion('./el_grid.csv', idMappingDct)
