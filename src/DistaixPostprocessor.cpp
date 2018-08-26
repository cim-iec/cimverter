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

std::string DistaixPostprocessor::convertInputFile(std::string output_file_name){
    std::string oldfilename =  output_file_name + ".mo";
    std::string newfilename =  output_file_name + ".csv";

    rename(oldfilename.c_str(),newfilename.c_str());

    return newfilename;
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
        // Set first element to the smaller of both IDs
        if(std::stoi(cable[1]) < std::stoi(cable[0])) {
            std::string temp = cable[0];
            cable[0] = cable[1];
            cable[1] = temp;
        }
    }
    // Sort cable entries by first ID in ascending order
    std::sort(std::next(el_grid.begin()), el_grid.end(),
                [](const std::vector<std::string> &vec1, const std::vector<std::string> &vec2) {
                    return(std::stoi(vec1[0]) < std::stoi(vec2[0]));
                });
}

void DistaixPostprocessor::writeCSVFile(std::vector<std::vector<std::string> > dictionary) {
    // Open file
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
        // For each row, stored in the dictionary
        for (auto &parameter : entry) {
           
            if (!entry.empty()){
                // Write all values into csv, with respective delimiter "," or endline...
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
    // Close file
    csvfile.close();

}

void DistaixPostprocessor::setDefaultParameters(){

    // Read in default_parameters.csv
    std::ifstream file("default_parameters.csv");
    std::string line = "";

    while(getline(file,line))
    {        
        std::vector<std::string> vec;
        boost::algorithm::split(vec, line, boost::is_any_of(","));
 
        // Store all default parameters with "ComponentType_parameterName" as key
        for (auto it = std::next(vec.begin()); it != vec.end(); ++it) {
            std::string key = it->substr(0, it->find("="));
            defaultParameterConversionMap[vec[0] + "_" + key] = it->substr(key.length() + 1, it->find(","));

        }
    }

    // Replace parameters
    bool first = true;

    for (auto &entry : components) {
        // Skip first element
        if (first) {
            first = false;
            continue;
        }
        
        for (auto &element : entry) {
            // Check if one of the elements of a components includes the keyword "default", indicating a default parameter placeholder
            std::size_t found = element.find("default");
            if (found != std::string::npos) {
                // Check if a corresponding value was read and strored
                auto searchIt = defaultParameterConversionMap.find(entry[1] + "_" + element);
                if (searchIt != defaultParameterConversionMap.end()) {
                    //std::cout << "Replace " << "\"" << element << "\" with \"" << defaultParameterConversionMap[entry[1] + "_" + element] << "\"" << std::endl;
                    element = defaultParameterConversionMap[entry[1] + "_" + element];
                }
                else {
                    #ifdef DEBUG
                    std::cout << "No default parameter for " << entry[1] << ": \"" + element + "\" found..." << std::endl;
                    #endif
                }
            }
        }
    }
}



void DistaixPostprocessor::postprocess(std::string output_file_name) {
    std::cout << output_file_name << std::endl;
    // Convert and split modelica file
    std::string newFileName = DistaixPostprocessor::convertInputFile(output_file_name);
    DistaixPostprocessor::splitCSVFile(newFileName);
    // Convert IDs
    DistaixPostprocessor::convertComponentIDs();
    DistaixPostprocessor::convertElGridIDs();
    // Replace default parameters
    DistaixPostprocessor::setDefaultParameters();
    // Write new CSV Files
    DistaixPostprocessor::writeCSVFile(components);
    DistaixPostprocessor::writeCSVFile(el_grid);
}