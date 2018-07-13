# This script is used for postprocessing modelica files from CIM2Distaix project.

import os
import csv

###############################################################################################
## Helper Functions                                                                          ##
###############################################################################################

def modelicaToCSVConversion(path):
    root = os.path.splitext(path)[0]
    os.rename(path, root + ".csv")

    return root + ".csv"

def splitCSVFile(path):

    print('Splitting csv file...')

    componentsLst = []
    electricalGridLst = []

    with open(path, 'r') as csvfile:
        saveVec = csv.reader(csvfile, delimiter=',')
        for row in saveVec:
            print(len(row))
            if not row:
                pass
            elif row[0] == 'components.csv':
                currentLst = componentsLst
            elif row[0] == 'el_grid.csv':
                currentLst = electricalGridLst
            else:
                currentLst.append(row)
        
    with open('components.csv', 'w') as csvfile:
        writer = csv.writer(csvfile)
        for component in componentsLst:
            writer.writerow(component)

    with open('el_grid.csv', 'w') as csvfile:
        writer = csv.writer(csvfile)
        for cable in electricalGridLst:
            writer.writerow(cable)

def componentsIdConversion()

###############################################################################################
## Main Routine                                                                              ##
###############################################################################################

splitCSVFile(modelicaToCSVConversion("./test.mo"))
