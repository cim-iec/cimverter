/*
 * DistaixPostprocessor.h
 * Postprocesses output file to fit distaix format
 */

#ifndef SRC_DISTAIXPOSTPROCESSOR_H_
#define SRC_DISTAIXPOSTPROCESSOR_H_

#include <stdio.h>
#include <cstring>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>


class DistaixPostprocessor{
    
    public:
        DistaixPostprocessor();
        virtual ~DistaixPostprocessor();

        void convertInputFile(std::string filename);
        void splitCSVFile(std::string filepath);
        void convertIDs();

    private:
        void convertComponentIDs();
        void convertElGridIDs();
        void writeCSVFile(std::vector<std::vector<std::string> > dictionary);

        std::vector<std::vector<std::string> > components;
        std::vector<std::vector<std::string> > el_grid;

        std::map<std::string, unsigned int> idConversionMap;

};

#endif