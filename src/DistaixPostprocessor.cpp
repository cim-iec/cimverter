/*
 * DistaixPostprocessor.cpp
 *
 */

#include "DistaixPostprocessor.h"

DistaixPostprocessor::DistaixPostprocessor(){
    std::vector<std::string> vec;
    
    // Add corresponding names to vectors
    vec.push_back("components");
    components.push_back(vec);

    vec[0] = "el_grid";
    el_grid.push_back(vec);
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

    bool first = true;
    for(auto &component : components){
        if (first) {
            first = false;
            continue;
        }

        auto searchIt = idConversionMap.find(component[0]);

        if (searchIt == idConversionMap.end()) {
            idConversionMap[component[0]] = counter;
            component[0] = std::to_string(counter);
        }
        else {
            std::cout << "ERROR: ID " << component[0] << " is not unique!" << std::endl;
        }

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
    bool first = true;

    for (auto &cable : el_grid) {
        // Skip first element containing the name
        if (first){
            first = false;
            continue;
        }
        // For first and second element of component:
        for (auto i = 0; i <= 1; ++i) {
            auto searchIt = idConversionMap.find(cable[i]);
            if (searchIt != idConversionMap.end()) {
                cable[i] = std::to_string(idConversionMap[cable[i]]);
                
            }
            else {
                std::cout << "Error: ID " << cable[i] << " is no valid ID!" << std::endl;
            }
        }
    }
}

void DistaixPostprocessor::writeCSVFile(std::vector<std::vector<std::string> > dictionary) {
    std::ofstream csvfile;

    std::string name = dictionary[0][0] + ".csv";

    csvfile.open(name.c_str());

    bool first = true;

    for (auto &entry : dictionary) {
        // Skip name entry
        if (first) {
            first = false;
            continue;
        }
        for (auto &parameter : entry) {
           
            if (!entry.empty()){
    
                csvfile << parameter.c_str();
                 
                if (&parameter == &entry.back()) {
                    csvfile << std::endl;
                }
                else {
                    csvfile << ",";
                }
            }
        }

    }

    csvfile.close();

}

void DistaixPostprocessor::convertIDs(){
    DistaixPostprocessor::convertComponentIDs();
    DistaixPostprocessor::convertElGridIDs();

    DistaixPostprocessor::writeCSVFile(components);
    DistaixPostprocessor::writeCSVFile(el_grid);
}