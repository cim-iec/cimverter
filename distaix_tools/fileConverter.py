import os
import csv
from shutil import copyfile

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
