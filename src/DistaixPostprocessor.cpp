/*
 * DistaixPostprocessor.cpp
 *
 */

#include "DistaixPostprocessor.h"

DistaixPostprocessor::DistaixPostprocessor(){

};

DistaixPostprocessor::~DistaixPostprocessor(){

};

void DistaixPostprocessor::convertInputFile(std::string filename){
    std::string oldfilename =  filename + ".mo";
    std::string newfilename =  filename + ".csv";

    rename(oldfilename.c_str(),newfilename.c_str());
}

void DistaixPostprocessor::splitCSVFile(std::string filepath){
    
    std::ifstream file(filepath);
    std::string line = "";

    bool is_component = true;

    while(getline(file,line))
    {        
        if (!strcmp(line.data(),"components.csv")){
            is_component = true;
        }
        else if (!strcmp(line.data(), "el_grid.csv")){
            is_component = false;
        }
        else {
            if (is_component) {
                std::vector<std::string> vec;
                boost::algorithm::split(vec, line, boost::is_any_of(","));
                components.push_back(vec);
            }
            else {
                std::vector<std::string> vec;
                boost::algorithm::split(vec, line, boost::is_any_of(","));
                el_grid.push_back(vec);
            }
        }
        #ifdef DEBUG
            std::cout << "Components:" << std::endl;
            for(auto i = components.begin(); i != components.end(); ++i){
                for (auto item : *i) {
                    std::cout << item << " ";
                }
                std::cout << std::endl;
            }

            std::cout << "El_grid:" << std::endl;
            for(auto i = el_grid.begin(); i != el_grid.end(); ++i){
                for (auto item : *i) {
                    std::cout << item << " ";
                }
                std::cout << std::endl;
            }
        #endif
    }

}

void DistaixPostprocessor::convertComponentIDs(){
    int counter = 1;

    for(auto component : components){
        component[0] = std::to_string(counter);

        // TODO: Store ID in Dict/Map
        // TODO: Check if ID unique!

        #ifdef DEBUG
            for (auto item : component) {
                std::cout << item << " ";
            }
            std::cout << std::endl;
        #endif
        counter++;
    }
}

void DistaixPostprocessor::convertElGridIDs(){
    // TODO: 
    // For First and Second Element:
    //  ID in map? --> Replace
    //  Else --> Return Error
}

void DistaixPostprocessor::convertIDs(){
    DistaixPostprocessor::convertComponentIDs();
}