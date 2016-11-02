__author__ = 'taojun'
# -*- coding: utf-8 -*-
import sys
import os
import glob

""" This is an python programm
    linking all the xml files from the folder
"""
class CIM_XML_Combinator():

    def __init__(self):
        self.xml_folder_path = ''
        self.output_filename = ''

    def linking(self):
        read_files = glob.glob(os.path.join(self.xml_folder_path, '*.xml'))
        output_file = self.xml_folder_path + self.output_filename + ".xml"
        with open(output_file, "wb") as outfile:
            for f in read_files:
                with open(f, "rb") as infile:
                    outfile.write(infile.read())
                    print('files combining...')

        outfile.close()
        print('combination finished.')

if __name__ == '__main__':

    cimCombinator = CIM_XML_Combinator()
    if len(sys.argv) <= 2:
        cimCombinator.xml_folder_path = sys.argv[1]
        cimCombinator.output_filename = sys.argv[1].split("/")[-2]
    else:
        cimCombinator.xml_folder_path = sys.argv[1]
        cimCombinator.output_filename = sys.argv[2]
    cimCombinator.linking()