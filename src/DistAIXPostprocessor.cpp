
/*
 * DistAIXPostprocessor.cpp
 *
 */

#include "DistAIXPostprocessor.h"
#include <typeinfo>

/**
 * Constructor 
 */
DistAIXPostprocessor::DistAIXPostprocessor(std::string template_folder){
    std::vector<std::string> vec;
    
    // Add corresponding names to vectors
    vec.push_back("components");
    components.push_back(vec);
    componentsOrdered.push_back(vec);

    vec[0] = "el_grid";
    el_grid.push_back(vec);

    // Set template folder
    this->template_folder = template_folder;

};

/**
 * Destructor 
 */
DistAIXPostprocessor::~DistAIXPostprocessor(){
};

/**
 * Converts modelica file into CSV-file by renaming. 
 */
std::string DistAIXPostprocessor::convertInputFile(std::string output_file_name){
    std::string oldfilename =  output_file_name + ".mo";
    std::string newfilename =  output_file_name + ".csv";

    rename(oldfilename.c_str(),newfilename.c_str());

    return newfilename;
}

/**
 * Splits CSV-file into components and el_grid
 */
void DistAIXPostprocessor::splitCSVFile(std::string filepath){
    
    std::ifstream file(filepath);
    std::string line = "";

    bool is_component = true;

    // Process file row-wise
    while(getline(file,line))
    {   
        // If components flag is read, set destination vector to components        
        if (!strcmp(line.data(),"components.csv")){
            is_component = true;
        }
        // If el_grid flag is read, set destination vector to components
        else if (!strcmp(line.data(), "el_grid.csv")){
            is_component = false;
        }
        // If no flag, i.e. normal component/cable is read - split elements and store
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

/**
 * Orders the components from slack to leaves in a depth-first sense, needed for proper id conversion.
 */
void DistAIXPostprocessor::orderComponents(std::vector<std::string> component, std::string transformerId) {
    
    std::string id = component[0];
    std::string searchId;
    std::string currentTransformerId = transformerId;

    bool cableFound = false;

    // For all cables check if they are connected to current regarded node
    for (auto cable : el_grid) {
        if (cable[0] == id) {
            searchId = cable[1];
            cableFound = true;
        }
        else if (cable[1] == id) {
            searchId = cable[0];
            cableFound = true;
        }
        // If cable that connects regarded node is found
        if (cableFound) {
            cableFound = false;
            // Search component/node that is connected to it
            for (auto component : components) {
                if(component[0] == searchId) {
                    // If found component is a topology node, i.e. Node, Slack or Trafo
                    if (component[1] == "Node" || component[1] == "Slack" || component[1] == "Transformer"){
                        
                        if(component[1] == "Transformer"){
                            currentTransformerId = component[0];
                        }
                        else if(component[1] == "Node"){
                            component[2] = currentTransformerId;
                        }

                        // Add component to ordered topology vector, if it was not added earlier
                        // Nodes might have experienced changes in parameter indicating the corresponding transformer, thus std::find() can not be used here...
                        bool componentFound = false;
                        for(auto orderedComponent : componentsOrdered){
                            if (orderedComponent[0] == component[0]){
                                componentFound = true;
                            }
                        }
                        if(!componentFound){
                            componentsOrdered.push_back(component);

                            // Recursively call order function on found component
                            DistAIXPostprocessor::orderComponents(component, currentTransformerId);
                        }
                    }
                    // Else add found component to vector holding nontopology components, if not already added
                    else {
                        if (!(std::find(nonTopologyComponents.begin(), nonTopologyComponents.end(), component)!= nonTopologyComponents.end())){
                            nonTopologyComponents.push_back(component);
                            // Recursively call order function on found component
                            DistAIXPostprocessor::orderComponents(component, currentTransformerId);
                        }                         
                    }
                // If component was found, break for loop to avoid looking at all remaining components
                break;
                }
            }
        }       
    }   
}

/**
 * Converts component IDs to match DistAIX naming conventions
 */
void DistAIXPostprocessor::convertComponentIDs(){
    int counter = 1;

    bool first = true;
    for(auto &component : components){
        // Skip first element
        if (first) {
            first = false;
            continue;
        }
        // Check if ID already stored
        auto searchIt = idConversionMap.find(component[0]);

        if (searchIt == idConversionMap.end()) {
            // Replace ID with increasing int variable and store value in corresp. map
            idConversionMap[component[0]] = counter;
            component[0] = std::to_string(counter);
        }
        else {
            std::cout << "ERROR: ID " << component[0] << " is not unique!" << std::endl;
        }

        // For nodes, the third parameter indicating the corresponding transformer has to be changed as well
        if(component[1] == "Node"){
            searchIt = idConversionMap.find(component[2]);

            if (searchIt == idConversionMap.end()){
                std::cout << "ERROR: " << component[2] << " is no valid transformer ID!" << std::endl;
            }
            else {
                component[2] = std::to_string(idConversionMap[component[2]]); 
            }
        }

        #ifdef DEBUG
            for (auto item : component) {
                std::cout << item << " ";
            }
            std::cout << std::endl;
        #endif

        counter++;
    }
}

/**
 * Converts electrical grid IDs to match DistAIX naming conventions
 */
void DistAIXPostprocessor::convertElGridIDs(){

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

/**
 * Write resulting CSV-file 
 */
void DistAIXPostprocessor::writeCSVFile(std::vector<std::vector<std::string> > dictionary) {
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

/**
 * Read in default parameters from CSV-file and replace all occurencies in stored values
 * Parameters are read from "default_parameters.csv".
 * "default_parameters.csv" has following structure:
 * 
 * ComponentType,parametername1=val,parametername2=val
 * 
 * e.g. Load,subtype_default=SFH,S_r_default=232323
 */
void DistAIXPostprocessor::setDefaultParameters(){

    // Read in default_parameters.csv
    std::string filepath = "resource/" + template_folder + "/default_parameters.csv";
    std::ifstream file(filepath);
    std::string line = "";

    // If default_parameters.csv does not exist return
    if (!file.is_open()) {
        std::cout << "resource/" << template_folder << "/default_parameters.csv was not found! Parameter replacement is skipped..." << std::endl; 
        return;
    }

    // Read default_parameters.csv row-wise
    while(getline(file,line))
    {   
        // Split elements at delimiter ","
        std::vector<std::string> vec;
        boost::algorithm::split(vec, line, boost::is_any_of(","));
 
        // Store all default parameters with "ComponentType_parameterName" as key
        for (auto it = std::next(vec.begin()); it != vec.end(); ++it) {
            std::string key = it->substr(0, it->find("="));
            defaultParameterConversionMap[vec[0] + "_" + key] = it->substr(key.length() + 1, it->find(","));

            #ifdef DEBUG
            std::cout << vec[0] + "_" + key << " = " << defaultParameterConversionMap[vec[0] + "_" + key] << std::endl;
            #endif
        }
    }

    // Replace default_parameters for components
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
                // Check if a corresponding value was read and stored
                auto searchIt = defaultParameterConversionMap.find(entry[1] + "_" + element);
                if (searchIt != defaultParameterConversionMap.end()) {
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

    // Replace default_parameters for el_grid

    first = true;

    for (auto &entry : el_grid) {
        // Skip first element
        if (first) {
            first =false;
            continue;
        }

        for (auto &element : entry) {
            // Check if one of the elements of a components includes the keyword "default", indicating a default parameter placeholder
            std::size_t found = element.find("default");
            if (found != std::string::npos) {
                // Check if corresponding values was read and stored
                // Care: In comparison to components, cables have no "identifier" at vec[0]! (e.g. "Load")
                // --> Here only element is used as key
                auto searchIt = defaultParameterConversionMap.find(element);
                if (searchIt != defaultParameterConversionMap.end()) {
                    element = defaultParameterConversionMap[element];
                }
                else {
                    #ifdef DEBUG
                    std::cout << "No default parameter for " << element << " found..." << std::endl;
                    #endif
                }
            }
        }
    }
}

/**
 * Postprocess files to match DistAIX convetions 
 */
void DistAIXPostprocessor::postprocess(std::string output_file_name) {

    // Convert and split modelica file
    std::string newFileName = DistAIXPostprocessor::convertInputFile(output_file_name);
    DistAIXPostprocessor::splitCSVFile(newFileName);
    
    // Add slack to ordered components vector and start recursive DFS graph traversing
    componentsOrdered.push_back(components[1]);
    DistAIXPostprocessor::orderComponents(components[1], components[1][0]);

    // Add non-topology components to ordered components
    for (auto entry : nonTopologyComponents) {
        componentsOrdered.push_back(entry);
    }

    #ifdef DEBUG
    std::cout << "COMPONENTS ORDERED:" << std::endl;
    for (auto component :componentsOrdered) {
        for (auto entry : component) {
            std::cout << entry << ",";
        }
        std::cout << std::endl;
    }
    #endif

    components = componentsOrdered;
    // Convert IDs
    DistAIXPostprocessor::convertComponentIDs();
    DistAIXPostprocessor::convertElGridIDs();
    // Replace default parameters
    DistAIXPostprocessor::setDefaultParameters();
    // Write new CSV Files
    DistAIXPostprocessor::writeCSVFile(components);
    DistAIXPostprocessor::writeCSVFile(el_grid);
}