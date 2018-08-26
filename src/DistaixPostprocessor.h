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

        void postprocess(std::string output_file_name);

    private:
        void convertComponentIDs();
        void convertElGridIDs();
        void writeCSVFile(std::vector<std::vector<std::string> > dictionary);
        std::string convertInputFile(std::string output_file_name);
        void splitCSVFile(std::string filepath);
        void setDefaultParameters();
        
        std::vector<std::vector<std::string> > components;
        std::vector<std::vector<std::string> > el_grid;

        std::map<std::string, unsigned int> idConversionMap;
        std::map<std::string, std::string> defaultParameterConversionMap;

};

#endif