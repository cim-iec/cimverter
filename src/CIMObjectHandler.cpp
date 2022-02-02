#include <CIMExceptions.hpp>
#include "CIMObjectHandler.h"
#include "ModelicaWorkshop/ModPowerSystems/Connection.h"
/**\brief Macro for transformation.extent setting
 */
#define  SET_TRANS_EXTENT(component, type_str)                                                  \
                      component->annotation.placement.transformation.extent.first.x =            \
                      configManager.type_str##_parameters.annotation.transformation_extent[0];  \
                      component->annotation.placement.transformation.extent.first.y =            \
                      configManager.type_str##_parameters.annotation.transformation_extent[1];  \
                      component->annotation.placement.transformation.extent.second.x =           \
                      configManager.type_str##_parameters.annotation.transformation_extent[2];  \
                      component->annotation.placement.transformation.extent.second.y =           \
                      configManager.type_str##_parameters.annotation.transformation_extent[3];  \

/**\brief Macro for NEPLAN Voltage unit fix
 */
#define FIX_NEPLAN_VOLTAGE(component)                                                           \
                    if(this->configManager.us.voltage_unit == "V"){                             \
                    component->set_Vnom(component->Vnom());                                       \
                    } else if (this->configManager.us.voltage_unit == "kV") {                   \
                    component->set_Vnom(component->Vnom()*1000);                                  \
                    } else if(this->configManager.us.voltage_unit == "mV") {                    \
                    component->set_Vnom(component->Vnom()*0.001);                                 \
                    } else if(this->configManager.us.voltage_unit == "MV"){                     \
                    component->set_Vnom(component->Vnom()*1000000);                               \
                    }                                                                           \


/**
 * Constructor
 * rvalue reference
 */
CIMObjectHandler::CIMObjectHandler(std::vector<BaseClass *> &&CIMObjects)
        : _CIMObjects(CIMObjects) {

    _t_points.xPosition = 0;
    _t_points.yPosition = 0;
}

CIMObjectHandler::~CIMObjectHandler() {

    auto sv_it = svPowerFlowMap.begin();
    auto Opl_it = OpLimitMap.begin();
    auto svVolt_it = svVoltageMap.begin();
    auto used_it = _UsedObjects.begin();
    auto generator_it = generatorMap.begin();
    auto terminalList_it = terminalList.begin();
    auto SynMachineMap_it = SynMachineMap.begin();
    auto PiLineMap_it = PiLineMap.begin();

    while (used_it != _UsedObjects.end())
    {
        delete used_it->second;
        _UsedObjects.erase(used_it++);
    }
    while (generator_it != generatorMap.end())
    {
        generatorMap.erase(generator_it++);
    }

    while (sv_it != svPowerFlowMap.end())
    {
        svPowerFlowMap.erase(sv_it++);
    }

    while (svVolt_it != svVoltageMap.end())
    {
        svVoltageMap.erase(svVolt_it++);
    }

    while (Opl_it != OpLimitMap.end())
    {
        OpLimitMap.erase(Opl_it++);
    }
    while (terminalList_it != terminalList.end())
    {
        terminalList.erase(terminalList_it++);
    }
    while (SynMachineMap_it != SynMachineMap.end())
    {
        SynMachineMap.erase(SynMachineMap_it++);
    }
    while (PiLineMap_it != PiLineMap.end())
    {
        PiLineMap.erase(PiLineMap_it++);
    }
}

/**
 * Get all settings from config.cfg.
 */
void CIMObjectHandler::get_config(std::string templates) {

    template_folder = templates;
    print_separator();
    std::cout << "reading config files..." << std::endl;
    this->configManager.getAllSettings();
    std::cout << "using templates: " << templates <<"\n";
    configManager.template_folder = templates;
    this->configManager.getConnectionConfigFiles();
    this->configManager.getConnectionNames();
    Connection::setConfigManager(&this->configManager);
    print_separator();
}

/**
 * Print the object name or RTTI name
 */
void CIMObjectHandler::print_RTTI(BaseClass *Object) {

    std::cout << "The following CIM model is not used:" << std::endl;
    if (auto *io = dynamic_cast<IdentifiedObjectPtr>(Object)) {
        std::cout << "IdentifiedObject.name: " << io->name << std::endl;
    }
    const std::type_info &info = typeid(*Object);
    std::cout << "RTTI name: " << info.name() << std::endl;
    std::cout << std::endl;
}


/*
 * Funtion that removes non alphabetic or numeric characters and replaces them by their hex value
 * Terminal(1) will be converted to Terminal_xy_1_yx
 */
void CIMObjectHandler::remove_non_alnums(IdentifiedObjectPtr identified_obj){
    auto name = identified_obj->name;
    String new_name;
    for(auto el : name){
        if( !(std::isalnum(el) || el == '_' || el == '-')){
            char output[2];
            sprintf((char*)(output),"%02X", el);
            if(el == name[-1]){
                new_name = new_name + '_'+ output[0] + output[1];
            }else{
                new_name = new_name + '_'+ output[0] + output[1] + '_';
            }

        }else{
            new_name = new_name + el;
        }
    }
    identified_obj->name = new_name;
}

/**
 * Add mem address to object name to achieve unique naming
 */
void CIMObjectHandler::add_mem_address(IdentifiedObjectPtr identified_obj){
    std::stringstream ss;
    ss << static_cast<const void*>(identified_obj);
    std::string addrStr = ss.str();
    identified_obj->name = identified_obj->name + '_' + addrStr;
}

/**
 * frist searching loop
 * to find I_max of ACLineSegment, SvPowerFlow of Terminal for PQLoad
 * using hashmap
 */
bool CIMObjectHandler::pre_process() {
    ///pre searching loop
    std::list<TerminalPtr>::iterator terminal_it;
    std::list<ConductingPtr >::iterator conducting_it;
    for (BaseClass *Object : this->_CIMObjects) {

        if(auto identified_obj = dynamic_cast<IdentifiedObjectPtr >(Object)){
            this->remove_non_alnums(identified_obj);
            if(this->configManager.gs.make_unique_names == true)
                this->add_mem_address(identified_obj);
        }
        if (this->configManager.gs.apply_Neplan_fix == true) {
            ///find OperationLimitSet for AClineSegment, stored in hashmap
            if (auto *op_limitset = dynamic_cast<OpLimitSetPtr>(Object)) {
                if (auto *ac_line = dynamic_cast<AcLinePtr>(op_limitset->Equipment)) {
                    OpLimitMap.insert({ac_line, op_limitset}); //hashmap
                }else{
                    for (BaseClass *Object1 : this->_CIMObjects) {
                        if(auto *terminal = dynamic_cast<TerminalPtr> (Object1)){
                            if(terminal->mRID == op_limitset->Terminal->mRID){
                                if (auto *ac_line = dynamic_cast<AcLinePtr>(terminal->ConductingEquipment)) {
                                    OpLimitMap.insert({ac_line, op_limitset});
                                    break;
                                }
                            }

                        }
                    }
                }
            }
        }
        if (this->configManager.svSettings.useSVforEnergyConsumer == true
            or this->configManager.svSettings.useSVforGeneratingUnit == true
            or this->configManager.svSettings.useSVforExternalNetworkInjection == true) {
            ///find terminal's svPowerFlow
            if (auto *sv_powerflow = dynamic_cast<SVPowerFlowPtr>(Object)) {
                svPowerFlowMap.insert({sv_powerflow->Terminal, sv_powerflow}); //hashmap
            } else if (auto *sv_voltage = dynamic_cast<SVVoltagePtr>(Object)) {
                svVoltageMap.insert({ (sv_voltage->TopologicalNode), sv_voltage});
            }
        }
        if (auto *generatingUnit = dynamic_cast<GeneratingUnitPtr > (Object)) {
            for (rotatingMachine_it = generatingUnit->RotatingMachine.begin();
                 rotatingMachine_it != generatingUnit->RotatingMachine.end();
                 ++rotatingMachine_it) {
                generatorMap.insert({(*rotatingMachine_it), generatingUnit});
            }
        }
        if (auto *base_voltage = dynamic_cast<BaseVoltagePtr >(Object)) {
            for( conducting_it = base_voltage->ConductingEquipment.begin();
                 conducting_it != base_voltage->ConductingEquipment.end();
                 conducting_it ++){
                baseVoltageMap.insert({*conducting_it, base_voltage});
            }
        }
        if(auto *syn_machine_dyn = dynamic_cast<SynMachineDynPtr> (Object)){
            SynMachineMap.insert({syn_machine_dyn->SynchronousMachine, syn_machine_dyn});
        }
        if (this->configManager.ss.use_TPNodes == true) {
            if (auto *tp_node = dynamic_cast<TPNodePtr>(Object)) {
                for (terminal_it = tp_node->Terminal.begin(); terminal_it != tp_node->Terminal.end(); ++terminal_it) {
                    terminalList[tp_node].push_back(*terminal_it);
                    if(auto *ac_line = dynamic_cast<AcLinePtr>((*terminal_it)->ConductingEquipment )){
                        PiLineMap[ac_line].push_back(*terminal_it);
                    }
                }
            }
        } else {
            if (auto *terminal = dynamic_cast<TerminalPtr>(Object)) {
                terminalList[terminal->ConnectivityNode].push_back(terminal);
                if(terminal->ConnectivityNode == nullptr)
                    this->set_exit_code(3);
                    std::cerr<< "Terminal " << terminal << " has no connectivity node connected. You might use the wrong topological model."
                             << " Verify that the use_TPNodes option is set correctly." << std::endl;
            }
        }

    }
    if(configManager.gs.ignore_unconnected_components == true){
        remove_unconnected_components();
    }

    return true;
}


/**
 *  Function that removes all components that are not connected to a Slack,
 *  or in case that there is no Slack only creates the larges component
 */
void  CIMObjectHandler::remove_unconnected_components() {
    // TODO Code cleanup: create fct that returns tpNode of extNW
    // TODO Create fct that for a given start node returns a list of connected tpNodes
    // find external network tpNode
    std::vector<BaseClass *> tpNodeList;
    BaseClass *externalNW_TPNode = nullptr;
    std::unordered_map<BaseClass *, std::list<BaseClass *> > obj2TPNodeMap;

    // check if the connected property of terminals is initalized somewhere
    bool connected_terminal_exists = false;
    for (auto object_it = terminalList.begin(); object_it != terminalList.end(); object_it++) {
        BaseClass *tp_node = (*object_it).first;
        std::list<TerminalPtr> terminals = (*object_it).second;
        tpNodeList.push_back(tp_node);
        for (auto terminal : terminals) {
            try{
                bool connected = terminal->connected;
                if (connected == true){
                    obj2TPNodeMap[terminal->ConductingEquipment].push_back(tp_node);
                    connected_terminal_exists = true;
                }

                if (auto *externalNetwork = dynamic_cast<ExNIPtr >((terminal)->ConductingEquipment)) {
                    externalNW_TPNode = tp_node;
                }
            }catch(ReadingUninitializedField* e){
                std::cerr << "Uninitalized connected property for Terminal " << terminal->name << std::endl;
                this->set_exit_code(3);
                continue;
            }

        }
    }
    if( connected_terminal_exists == false){
        this->set_exit_code(3);
        std::cerr << "There exists no terminal with the connected property set to true."
                " This might be due to uninitalized values. \n"
                  << "We change the ignore_unconnected_components option to false." << std::endl;
        this->configManager.gs.ignore_unconnected_components = false;

        return;
    }

    // helper fct that for a given start node returns all connected nodes (the component)
    auto get_component = [&](std::unordered_map<BaseClass *, std::list<BaseClass *> > _obj2TPNodeMap,
                                BaseClass *_start_node){
        std::queue<BaseClass*> qq;
        qq.push(_start_node);
        BaseClass* currTPNode;
        std::vector<BaseClass* > component;
        while(!qq.empty()){
            currTPNode = qq.front();
            qq.pop();
            if(std::find(component.begin(), component.end(), currTPNode)
               != component.end())
                continue;
            else
                component.push_back(currTPNode);
            for(auto terminal : this->terminalList[currTPNode]){
                try{
                    bool connected = terminal->connected;

                    if(connected == true){
                        for(auto tp_node : _obj2TPNodeMap[terminal->ConductingEquipment]){
                            if (tp_node != currTPNode)
                                qq.push(tp_node);
                        }
                    }
                }catch(ReadingUninitializedField* e) {
                    this->set_exit_code(3);
                    std::cerr << "Uninitalized connected property for Terminal " << terminal->name << std::endl;
                    continue;
                }
            }
        }
        return component;
    };

    // if there is no slack create largest connected component
    // otherwise create component connected to the slack
    std::vector<BaseClass*> component;
    if (externalNW_TPNode == nullptr){
        std::cerr << "The ignore_unconnected_components option in the options.cfg is set to true but there is no Slack in the given network. "
                "Creating the largest connected component." << std::endl;
        while(tpNodeList.size() > 0 ){
            auto curr_component = get_component(obj2TPNodeMap, *(tpNodeList.begin()));
            if(curr_component.size() > component.size()){
                std::cout << "found new largest compnent of size: " << curr_component.size()
                          <<" before "<<component.size() <<std::endl;
                component = curr_component;
            }
            for(auto el : curr_component){
                auto pos = std::find(tpNodeList.begin(), tpNodeList.end(), el);
                if(pos != tpNodeList.end())
                    tpNodeList.erase(pos);
            }
        }
    }else{
        component = get_component(obj2TPNodeMap, externalNW_TPNode);
    }


    // remove tpNodes that are not connected to external network
    std::vector<BaseClass * > removal_list;
    for(auto el : terminalList){
        if(std::find(component.begin(), component.end(), el.first) == component.end())
            removal_list.push_back(el.first);
    }
    for(auto el : removal_list){
        terminalList.erase(el);
    }

}


/**
 * Generate the modelica code
 * by parsering the _CIMObjects
 */
bool CIMObjectHandler::ModelicaCodeGenerator(std::string output_file_name, int verbose_flag) {
    const std::string filename = output_file_name;
    ctemplate::TemplateDictionary *dict = new ctemplate::TemplateDictionary("MODELICA");///set the main tpl file

    // TODO: Not sure if the dictionary should be changed to DISTAIX?
    // ctemplate::TemplateDictionary *dict;
    // if(this->configManager.gs.create_distaix_format == true) {
    //   dict = new ctemplate::TemplateDictionary("DISTAIX");///set the main tpl file for distaix format
    // } else {
    //   dict = new ctemplate::TemplateDictionary("MODELICA");///set the main tpl file for modelica format
    // }


    this->SystemSettingsHandler(filename, dict);

    ///first searching loop, to find I_max of ACLineSegment, SvPowerFlow of Terminal for PQLoad
    this->pre_process();
    std::unordered_map<BaseClass*, ModBaseClass*> copy;



    std::list<TerminalPtr>::iterator terminal_it;
    /// Each iteration takes one TopologicalNode creates a Busbar for it and creates and connects all objects
    /// that are connected to the TopologicalNode to the Busbar

    for(auto object_it = terminalList.begin(); object_it!= terminalList.end(); object_it++) {

        BaseClass * Object = (*object_it).first;
        std::list<TerminalPtr> terminals = (*object_it).second;


        if(this->configManager.ss.use_TPNodes == true){//useTP == true
            auto *tp_node = dynamic_cast<TPNodePtr>(Object) ;
            this->currBusbar = this->TopologicalNodeHandler(tp_node, dict);

            if (this->configManager.household_parameters.use_households == true ) {
                this->HouseholdComponetsHandler(tp_node, dict);
            }
            this->currNode = tp_node;
        }else{
            if(auto *conn_node = dynamic_cast<ConnectivityNodePtr>(Object)){
                this->currBusbar = this->ConnectivityNodeHandler(conn_node, dict);

                if (this->configManager.household_parameters.use_households == true) {
                    this->HouseholdComponetsHandler(conn_node, dict);
                }
                this->currNode = conn_node;
            }else{
                std::cerr<< "The object is not a connectivity node. You might use the wrong topological model."
                         << " Verify that the use_TPNodes option is set correctly." << std::endl;

            }
        }
        BusBar* busbar = this->currBusbar;
        BaseClass* tp_node = this->currNode;
        // ignore terminals that are not connected

        // create all objects that are connected to the TopologicalNode and connect it to the BusBar
        for (TerminalPtr terminal : terminals ) {
            if(this->configManager.gs.ignore_unconnected_components == true)
                if(terminal->connected == false)
                    continue;
            //ConnectivityNode no use for NEPLAN
            /*if (auto *connectivity_node = dynamic_cast<ConnectivityNodePtr>((*terminal_it)->ConnectivityNode)) {

              ConnectivityNode connectivity_Node = this->ConnectivityNodeHandler(tp_node, (*terminal_it),
                                                                                connectivity_node, dict);
              Connection conn(&busbar, &connectivity_Node);
              connectionQueue.push(conn);
            }*/

            if (auto *externalNI = dynamic_cast<ExNIPtr>((terminal)->ConductingEquipment)) {
                if(_UsedObjects.find(externalNI) != _UsedObjects.end()) {
                }else{
                    ModSlack* slack = this->ExternalNIHandler(tp_node, (terminal), externalNI, dict);
                    _UsedObjects.insert({externalNI, slack});
                }
                Connection conn(busbar, (ModSlack* )_UsedObjects[externalNI]);
                connectionQueue.push(conn);

            } else if (auto *power_trafo = dynamic_cast<PowerTrafoPtr>((terminal)->ConductingEquipment)) {
                if(_UsedObjects.find(power_trafo) != _UsedObjects.end()) {
                    ((ModTransformer* )_UsedObjects[power_trafo])->setBus(busbar);
                }else{
                    ModTransformer* trafo = this->PowerTransformerHandler(busbar, (terminal), power_trafo, dict);
                    _UsedObjects.insert({power_trafo, trafo});
                }
                Connection conn(busbar, (ModTransformer* )_UsedObjects[power_trafo]);
                connectionQueue.push(conn);

            } else if (auto *ac_line = dynamic_cast<AcLinePtr>((terminal)->ConductingEquipment)) {
                if(configManager.gs.ignore_unconnected_components == true){
                    bool all_terminals_connected = true;
                    for(auto piTerminal : PiLineMap[ac_line]){
                        if(piTerminal->connected == false)
                            all_terminals_connected = false;
                    }
                    if(all_terminals_connected != true)
                        continue;
                }
                if(_UsedObjects.find(ac_line) != _UsedObjects.end()) {
                    ((ModPiLine* )_UsedObjects[ac_line])->setBus(busbar);
                }else {
                    if (template_folder == "DistAIX_templates") {
                        /* Changed implementation to enable creation of lossy cables for DistAIX format.
                        * Instead of creating "connections", the name of the busbar is stored when visited for the first time.
                        * When visiting the pi_line for the second time, the name of the current busbar, as well as the name of the busbbar
                        * stored during the first visit are passed as optional arguments to the ACLineSegmentHandler.
                        * This handler was modified in such a way, that those additional arguments are stores as dictionary values
                        * used in the DistAIX templates.
                        */

                        auto searchIt = piLineIdMap.find(ac_line);
                        if (searchIt != piLineIdMap.end()) {

                            ModPiLine* pi_line = this->ACLineSegmentHandler(tp_node, busbar, (terminal), ac_line, dict,
                                                                         piLineIdMap[ac_line], busbar->name());
                            _UsedObjects.insert({ac_line, pi_line});
                        } else {

                            piLineIdMap[ac_line] = busbar->name();

                        }
                    } else {

                        ModPiLine* pi_line = this->ACLineSegmentHandler(tp_node, busbar, (terminal), ac_line, dict);
                        _UsedObjects.insert({ac_line, pi_line});
                    }
                }
                Connection conn(busbar, ((ModPiLine*)_UsedObjects[ac_line]));
                connectionQueue.push(conn);
            } else if (auto *energy_consumer = dynamic_cast<EnergyConsumerPtr>((terminal)->ConductingEquipment)) {
                if(_UsedObjects.find(energy_consumer) != _UsedObjects.end()) {

                }else {

                    if (this->configManager.household_parameters.use_households == false) {
                        ModPQLoad* pqload = this->EnergyConsumerHandler(tp_node,(terminal), energy_consumer, dict);
                        _UsedObjects.insert({energy_consumer, pqload});
                    }
                }
                Connection conn(busbar, (ModPQLoad*)_UsedObjects[energy_consumer]);
                connectionQueue.push(conn);
            } else if (auto *synchronous_machine = dynamic_cast<SynMachinePtr >((terminal)->ConductingEquipment)) {
                if(_UsedObjects.find(synchronous_machine) != _UsedObjects.end()) {

                }else {
                    if(SynMachineMap.find(synchronous_machine) != SynMachineMap.end()){
                        SynMachineDyn *synMachineDyn = this->synMachineDynHandler(tp_node, terminal,
                                                                                  SynMachineMap[synchronous_machine], dict);
                        _UsedObjects.insert({synchronous_machine, synMachineDyn});

                    }else{
                        if (this->configManager.household_parameters.use_households == false) {
                            ModPVNode * pv_node = this->SynchronousMachineHandlerType0(tp_node, (terminal),
                                                                                    synchronous_machine, dict);
                            _UsedObjects.insert({synchronous_machine,pv_node});

                        }
                    }
                }
                Connection conn(busbar, (ModPVNode* )_UsedObjects[synchronous_machine]);
                connectionQueue.push(conn);

                // THIS IS WRONG SYNMACHINEDYNAMICS IS NO CONDUCTING EQUIPMENT
                // TODO ADD THE CONNECTION CONSTRUCTOR
                // Connection conn(busbar, (SynMachineDyn *) _UsedObjects[synchronous_machine]);
                // connectionQueue.push(conn);
            }else if (auto *cim_breaker = dynamic_cast<BreakerPtr> ((terminal)->ConductingEquipment)){
                if(_UsedObjects.find(cim_breaker) != _UsedObjects.end()) {
                    ModBreaker* someBreaker = ((ModBreaker* )_UsedObjects[cim_breaker]);
                    someBreaker->setBus(busbar);
                }
                else{
                    ModBreaker * breaker = this->BreakerHandler(busbar,(terminal), cim_breaker , dict);
                    _UsedObjects.insert({cim_breaker, breaker});
                }
                Connection conn(busbar, (ModBreaker* )_UsedObjects[cim_breaker]);
                connectionQueue.push(conn);

            }
#ifdef SINERGIEN
                else if (auto *battery_storage = dynamic_cast<BatteryStoragePtr>((*terminal_it)->ConductingEquipment)){
            Battery battery = this->BatteryStorageHandler(tp_node, (*terminal_it), battery_storage, dict);
            Connection conn(&busbar, &battery);
            connectionQueue.push(conn);

        }
#endif
            else {

                if(verbose_flag == 1) {
                    print_RTTI((*terminal_it)->ConductingEquipment); /// In verbose module to show the no used object information
                }
            }
        }
        if (this->configManager.household_parameters.use_households == true ) {

            while (!this->householdQueue.empty()) {

                switch (this->householdQueue.front().HouseholdType()) {
                    case (HouseholdType::Type1):
                        if (this->householdQueue.front().sequenceNumber() == 0
                            || this->householdQueue.front().sequenceNumber() == 1) {
                            ctemplate::TemplateDictionary *household_dict = dict->AddIncludeDictionary(
                                    "HOUSEHOLD_TYPE1_DICT");
                            household_dict->SetFilename(
                                    this->configManager.ts.directory_path + "resource/" + template_folder + "/HouseholdType1.tpl");
                            this->householdQueue.front().set_template_values(household_dict);
                        }
                        break;
                    case (HouseholdType::Type2):
                        if (this->householdQueue.front().sequenceNumber() == 0
                            || this->householdQueue.front().sequenceNumber() == 1) {
                            ctemplate::TemplateDictionary *household_dict = dict->AddIncludeDictionary(
                                    "HOUSEHOLD_TYPE2_DICT");
                            household_dict->SetFilename(
                                    this->configManager.ts.directory_path + "resource/" + template_folder + "/HouseholdType2.tpl");
                            this->householdQueue.front().set_template_values(household_dict);
                        }
                        break;
                    default:break;
                }
                Connection conn(busbar, &this->householdQueue.front());
                connectionQueue.push(conn);

                this->householdQueue.pop();
            }
            while (!this->pqloadQueue.empty()) {
                if (this->configManager.pqload_parameters.type == 1 && pqloadQueue.front().PQLoadType() == PQLoadType::Standard) {
                    ctemplate::TemplateDictionary *pqLoad_dict = dict->AddIncludeDictionary("PQLOAD_DICT");
                    pqLoad_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/PQLoad.tpl");
                    pqloadQueue.front().set_template_values(pqLoad_dict);
                } else if (this->configManager.pqload_parameters.type == 2 && pqloadQueue.front().PQLoadType() == PQLoadType::Profile) {
                    ctemplate::TemplateDictionary *pqLoad_dict = dict->AddIncludeDictionary("PQLOAD_PROFILE_DICT");
                    pqLoad_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/PQLoadProfile.tpl");
                    pqloadQueue.front().set_template_values(pqLoad_dict);
                } else if(this->configManager.pqload_parameters.type == 3 && pqloadQueue.front().PQLoadType() == PQLoadType::NormProfile){
                    ctemplate::TemplateDictionary *pqLoad_dict = dict->AddIncludeDictionary("PQLOAD_NORM_PROFILE_DICT");
                    pqLoad_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/PQLoadNormProfile.tpl");
                    pqloadQueue.front().set_template_values(pqLoad_dict);
                }
                Connection conn(busbar, &pqloadQueue.front());
                connectionQueue.push(conn);
                pqloadQueue.pop();
            }
            while (!this->solarGeneratorQueue.empty()) {

                ctemplate::TemplateDictionary *solar_generator_dict = dict->AddIncludeDictionary(
                        "SOLARGENERATOR_DICT");
                solar_generator_dict->SetFilename(
                        this->configManager.ts.directory_path + "resource/" + template_folder + "/SolarGenerator.tpl");
                solarGeneratorQueue.front().set_template_values(solar_generator_dict);
                Connection conn(busbar, &solarGeneratorQueue.front());
                connectionQueue.push(conn);
                solarGeneratorQueue.pop();
            }
            while (!this->pvNodeQueue.empty()) {

                ctemplate::TemplateDictionary *pv_node_dict = dict->AddIncludeDictionary(
                        "PVNODE_DICT");
                pv_node_dict->SetFilename(
                        this->configManager.ts.directory_path + "resource/" + template_folder + "/PVNode.tpl");
                pvNodeQueue.front().set_template_values(pv_node_dict);
                Connection conn(busbar, &pvNodeQueue.front());
                connectionQueue.push(conn);
                pvNodeQueue.pop();
            }
        }
    }

    this->ConnectionHandler(dict);

    std::string modelica_output;

    if(template_folder == "DistAIX_templates") {
        this->configManager.gs.create_distaix_format = true;
        ctemplate::ExpandTemplate(this->configManager.ts.directory_path + "resource/" + template_folder + "/distaix.tpl",
                                  ctemplate::STRIP_BLANK_LINES, dict, &modelica_output);
    } else {
        ctemplate::ExpandTemplate(this->configManager.ts.directory_path + "resource/" + template_folder + "/modelica.tpl",
                                  ctemplate::STRIP_BLANK_LINES, dict, &modelica_output);
    }

#ifdef DEBUG
    #pragma message("DEBUG model activated!")
  std::cout << modelica_output;
#endif
    std::cout << this->configManager.fs.output_path << std::endl;
    // Write to file
    std::ofstream file;
    file.open(this->configManager.fs.output_path + filename + ".mo", std::fstream::trunc);
    if (file.good())
        file << modelica_output;
    file.close();
    modelica_output.clear();

    return true;
}

/**
 * TopologicalNode
 * Convert to busbar in Modelica
 */
bool CIMObjectHandler::SystemSettingsHandler(const std::string filename, ctemplate::TemplateDictionary *dict) {
    //Modelica_Header
    dict->AddSectionDictionary("HEADER_FOOTER_SECTION");
    dict->SetValue("GRID_NAME", filename);

    //Global Settings
    dict->AddSectionDictionary("SYSTEM_SETTINGS_SECTION");

    if (configManager.ss.enable) {
        auto *system = new ModPowerSystems::System(configManager);
        std::cout << "Using SystemSetting parameters from configuration!" << std::endl;
        system->set_template_values(dict);
        delete system;
    } else {
        auto *system = new ModPowerSystems::System(0, 0, 400, -400);
        system->set_name(filename);
        system->set_template_values(dict);
        delete system;
    }

    return true;
}

/**
 * TopologicalNode
 * Convert to busbar in Modelica
 */
BusBar* CIMObjectHandler::TopologicalNodeHandler(const TPNodePtr tp_node, ctemplate::TemplateDictionary *dict) {
    BusBar* busbar = new BusBar();
    busbar->set_name(name_in_modelica(tp_node->name));
    busbar->annotation.placement.visible = true;
    busbar->set_Vnom(tp_node->BaseVoltage->nominalVoltage.value);

    if(this->configManager.us.enable){
        FIX_NEPLAN_VOLTAGE(busbar);
    }

    if (this->configManager.busbar_parameters.enable) {
        SET_TRANS_EXTENT(busbar,busbar);//Macro
        busbar->annotation.placement.visible = configManager.busbar_parameters.annotation.visible;
    }
    busbar->set_Vnom_displayUnit(busbar->Vnom_displayUnit());
    // std::list<DiagramObjectPtr>::iterator diagram_it is class member!
    int counter = 0;
    float currX = 0;
    float currY = 0;
    if (tp_node->DiagramObjects.begin() == tp_node->DiagramObjects.end()){
        std::cerr << "Missing Diagram Object for TpNode:  " << tp_node->name << " Taking average Terminal Position \n";

        for(std::list<TerminalPtr >::iterator terminal_it = tp_node->Terminal.begin();
            terminal_it != tp_node->Terminal.end(); terminal_it++) {
            if ((*terminal_it)->DiagramObjects.begin() != (*terminal_it)->DiagramObjects.end()) {

                for(diagram_it = (*terminal_it)->DiagramObjects.begin();
                    diagram_it!=(*terminal_it)->DiagramObjects.end(); ++diagram_it){
                    _t_points = this->calculate_average_position();
                    currX += _t_points.xPosition;
                    currY += _t_points.yPosition;
                    counter += 1;
                }

            }
        }
        if(counter == 0){
            busbar->annotation.placement.transformation.origin.x = 0;
            busbar->annotation.placement.transformation.origin.y = 0;

        }else{
            busbar->annotation.placement.transformation.origin.x = currX / counter;
            busbar->annotation.placement.transformation.origin.y = currY / counter;
        }
        busbar->annotation.placement.transformation.rotation = 0;
        ctemplate::TemplateDictionary *busbar_dict = dict->AddIncludeDictionary("BUSBAR_DICT");
        busbar_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/BusBar.tpl");
        busbar->set_template_values(busbar_dict);

    }else {
        for (diagram_it = tp_node->DiagramObjects.begin(); diagram_it != tp_node->DiagramObjects.end(); ++diagram_it) {
            _t_points = this->calculate_average_position();
            currX += _t_points.xPosition;
            currY += _t_points.yPosition;
            counter += 1;
            try{
                busbar->annotation.placement.transformation.rotation = (*diagram_it)->rotation.value;
            }catch(ReadingUninitializedField* e){
                busbar->annotation.placement.transformation.rotation = 0;
                std::cerr <<"Missing rotation for diagram obj "<< busbar->name()<< std::endl;
                this->set_exit_code(3);

            }

        }
        busbar->annotation.placement.transformation.origin.x = currX / counter;
        busbar->annotation.placement.transformation.origin.y = currY / counter;
        ctemplate::TemplateDictionary *busbar_dict = dict->AddIncludeDictionary("BUSBAR_DICT");
        busbar_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/BusBar.tpl");
        busbar->set_template_values(busbar_dict);


        //BusBarSection used in Cimphony
//  std::list<TerminalPtr>::iterator terminal_it;
//  for (terminal_it = tp_node->Terminal.begin(); terminal_it!=tp_node->Terminal.end(); ++terminal_it) {
//    if (auto *busbar_section = dynamic_cast<BusBarSectionPtr>((*terminal_it)->ConductingEquipment)) {
//      this->BusBarSectionHandler(busbar_section, busbar, dict);
//    }
//  }
    }
    return busbar;
}


/**
 * Create a Busbar for the respective ConnectivityNode
 */
BusBar* CIMObjectHandler::ConnectivityNodeHandler(const ConnectivityNodePtr con_node, ctemplate::TemplateDictionary *dict) {
    BusBar* busbar = new BusBar();
    busbar->set_name(name_in_modelica(con_node->name));
    busbar->annotation.placement.visible = true;
    bool is_set = false;

    // ConnectivityNodes don't have a BaseVoltage in CIM. Therefore, we use the BaseVoltage
    // of the first ConductingEquipment found which is connected to the ConnectivityNode
    // If there is no ConductingEquipment with BaseVoltage connected we print an error
    // and use a default BaseVoltage
    std::list<TerminalPtr>::iterator terminal_it = terminalList[con_node].begin();
    while (is_set == false){
        if(baseVoltageMap.find((*terminal_it)->ConductingEquipment) != baseVoltageMap.end()){
            busbar->set_Vnom(baseVoltageMap[(*terminal_it)->ConductingEquipment]->nominalVoltage.value);
            is_set = true;
        }
        terminal_it ++;
        if(terminal_it == terminalList[con_node].end()){
            std::cerr << "No BaseVoltage connected to ConnectivityNode " << con_node->name << " using default value from cfg" <<std::endl;
            busbar->set_Vnom(this->configManager.gs.default_baseKV);
            break;
        }
    }
    if(this->configManager.us.enable){
        FIX_NEPLAN_VOLTAGE(busbar);
    }

    if (this->configManager.busbar_parameters.enable) {
        SET_TRANS_EXTENT(busbar,busbar);//Macro
        busbar->annotation.placement.visible = configManager.busbar_parameters.annotation.visible;
    }
    busbar->set_Vnom_displayUnit(busbar->Vnom_displayUnit());
    // std::list<DiagramObjectPtr>::iterator diagram_it is class member!
    int counter = 0;
    float currX = 0;
    float currY = 0;

    std::cerr << "Connectivity Node has no Diagram Object:  " << con_node->name << " Taking average Terminal Position \n";

    for(std::list<TerminalPtr >::iterator terminal_it = terminalList[con_node].begin();
        terminal_it != terminalList[con_node].end(); terminal_it++) {
        if ((*terminal_it)->DiagramObjects.begin() != (*terminal_it)->DiagramObjects.end()) {

            for(diagram_it = (*terminal_it)->DiagramObjects.begin();
                diagram_it!=(*terminal_it)->DiagramObjects.end(); ++diagram_it){
                _t_points = this->calculate_average_position();
                currX += _t_points.xPosition;
                currY += _t_points.yPosition;
                counter += 1;
            }

        }
    }
    if(counter == 0){
        busbar->annotation.placement.transformation.origin.x = 0;
        busbar->annotation.placement.transformation.origin.y = 0;

    }else{
        busbar->annotation.placement.transformation.origin.x = currX / counter;
        busbar->annotation.placement.transformation.origin.y = currY / counter;
    }
    busbar->annotation.placement.transformation.rotation = 0;
    ctemplate::TemplateDictionary *busbar_dict = dict->AddIncludeDictionary("BUSBAR_DICT");
    busbar_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/BusBar.tpl");
    busbar->set_template_values(busbar_dict);

    return busbar;
}

/**
 * In the TopologicalNode to
 * find PQLoad in type1
 * find PQLoad, SolarGenerator, Battery which form HouseHold type2
 */
bool CIMObjectHandler::HouseholdComponetsHandler(BaseClass* tp_node, ctemplate::TemplateDictionary *dict) {

    std::list<TerminalPtr>::iterator terminal_it;
    if(this->configManager.household_parameters.type == "type1" ){

        for (terminal_it = terminalList[tp_node].begin(); terminal_it != terminalList[tp_node].end(); ++terminal_it) {

            if (auto *energy_consumer = dynamic_cast<EnergyConsumerPtr>((*terminal_it)->ConductingEquipment)) {

                ModPQLoad* pqload = this->EnergyConsumerHandler(tp_node, (*terminal_it), energy_consumer, dict);
                ModHousehold* household = new ModHousehold(*pqload);
                if (this->configManager.household_parameters.enable) {
                    SET_TRANS_EXTENT(household,household);
                    household->annotation.placement.visible = configManager.household_parameters.annotation.visible;
                }

                this->householdQueue.push(*household);
            }
        }
    } else if (this->configManager.household_parameters.type == "type2"){
        for (terminal_it = terminalList[tp_node].begin(); terminal_it != terminalList[tp_node].end(); ++terminal_it) {

            if (auto *energy_consumer = dynamic_cast<EnergyConsumerPtr>((*terminal_it)->ConductingEquipment)) {
                ModPQLoad* pqload = this->EnergyConsumerHandler(tp_node, (*terminal_it), energy_consumer, dict);
                this->pqloadQueue.push(*pqload);
            }else if (auto *synchronous_machine = dynamic_cast<SynMachinePtr >((*terminal_it)->ConductingEquipment)) {

                if (this->configManager.household_parameters.use_households == false) {
                    ModPVNode* pv_node = this->SynchronousMachineHandlerType0(tp_node, (*terminal_it),
                                                                           synchronous_machine, dict);
                    this->pvNodeQueue.push(*pv_node);

                }


            }

            if (this->pqloadQueue.size()==1 && this->solarGeneratorQueue.size()==1) {

                ModHousehold* household = new ModHousehold(this->pqloadQueue.front(), this->solarGeneratorQueue.front());  //type2

                if (this->configManager.household_parameters.enable) {
                    SET_TRANS_EXTENT(household,household);
                    household->annotation.placement.visible = configManager.household_parameters.annotation.visible;
                }

                this->householdQueue.push(*household);
                this->pqloadQueue.pop();
                this->solarGeneratorQueue.pop();
            }
        }
    }
    return !this->householdQueue.empty();
}

/**
 * compensate for busbar in Modelica
 * used in Cimphony
 */
bool CIMObjectHandler::BusBarSectionHandler(const BusBarSectionPtr busbar_section, BusBar &busbar,
                                            ctemplate::TemplateDictionary *dict) {

    if(busbar_section->DiagramObjects.begin() == busbar_section->DiagramObjects.end()){
        std::cerr << "Missing Diagram Object for Bus: " << busbar_section->name << " Default Position 0,0 \n";
        busbar.annotation.placement.transformation.origin.x = 0;
        busbar.annotation.placement.transformation.origin.y = 0;
        busbar.annotation.placement.transformation.rotation = 0;

        ctemplate::TemplateDictionary *busbar_dict = dict->AddIncludeDictionary("BUSBAR_DICT");
        busbar_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/BusBar.tpl");
        busbar.set_template_values(busbar_dict);
    }else{

        int counter = 0;
        float currX = 0;
        float currY = 0;
        for (diagram_it = busbar_section->DiagramObjects.begin();
             diagram_it!=busbar_section->DiagramObjects.end();
             ++diagram_it) {
            _t_points = this->calculate_average_position();
            currX += _t_points.xPosition;
            currY += _t_points.yPosition;
            counter += 1;
            busbar.annotation.placement.transformation.rotation = (*diagram_it)->rotation.value;
        }
        busbar.annotation.placement.transformation.origin.x = currX / counter;
        busbar.annotation.placement.transformation.origin.y = currY / counter;

        busbar.annotation.placement.transformation.origin.x = _t_points.xPosition;
        busbar.annotation.placement.transformation.origin.y = _t_points.yPosition;
        busbar.annotation.placement.transformation.rotation = (*diagram_it)->rotation.value;

        ctemplate::TemplateDictionary *busbar_dict = dict->AddIncludeDictionary("BUSBAR_DICT");
        busbar_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/BusBar.tpl");
        busbar.set_template_values(busbar_dict);
    }
    return true;
}

/**
 * ConnectivityNode
 * Convert to ConnectivityNode in Modelica
 *//*
ConnectivityNode CIMObjectHandler::ConnectivityNodeHandler(const TPNodePtr tp_node, const TerminalPtr terminal,
                                                          const ConnectivityNodePtr connectivity_node,
                                                          ctemplate::TemplateDictionary *dict) {
  ConnectivityNode conn_node;
  conn_node.set_Vnom(tp_node->BaseVoltage->nominalVoltage.value);
  if(this->configManager.us.enable){
    FIX_NEPLAN_VOLTAGE(conn_node);
  }
  conn_node.set_name(name_in_modelica(connectivity_node->name));
  conn_node.annotation.placement.visible = true;
  conn_node.set_sequenceNumber(terminal->sequenceNumber);
  conn_node.set_connected(terminal->connected);

  if(connectivity_node->DiagramObjects.begin() == connectivity_node->DiagramObjects.end()){
      std::cerr << "Missing Diagram Object for Connectivity Node: " << connectivity_node->name << " Default Position 0,0 \n";
      conn_node.annotation.placement.transformation.origin.x = 0;
      conn_node.annotation.placement.transformation.origin.y = 0;
      conn_node.annotation.placement.transformation.rotation = 0;

      if (conn_node.sequenceNumber()==0 || conn_node.sequenceNumber()==1) {
          ctemplate::TemplateDictionary *conn_node_dict = dict->AddIncludeDictionary("CONNECTIVITYNODE_DICT");
          conn_node_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/ConnectivityNode.tpl");
          conn_node.set_template_values(conn_node_dict);
      }
  }
  for (diagram_it = connectivity_node->DiagramObjects.begin();
       diagram_it!=connectivity_node->DiagramObjects.end();
       ++diagram_it) {
    _t_points = this->calculate_average_position();
    conn_node.annotation.placement.transformation.origin.x = _t_points.xPosition;
    conn_node.annotation.placement.transformation.origin.y = _t_points.yPosition;
    conn_node.annotation.placement.transformation.rotation = (*diagram_it)->rotation.value - 90;

    if (conn_node.sequenceNumber()==0 || conn_node.sequenceNumber()==1) {
      ctemplate::TemplateDictionary *conn_node_dict = dict->AddIncludeDictionary("CONNECTIVITYNODE_DICT");
      conn_node_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/ConnectivityNode.tpl");
      conn_node.set_template_values(conn_node_dict);
    }
  }

  return conn_node;
}
*/
/**
 * ConductingEquipment of Terminal
 * ConductingEquipment cast to ExternalNetworkInjection
 * Convert to slack in Modelica
 */
ModSlack* CIMObjectHandler::ExternalNIHandler(BaseClass* tp_node, const TerminalPtr terminal, const ExNIPtr externalNI,
                                           ctemplate::TemplateDictionary *dict) {
    ModSlack* slack = new ModSlack();

    slack->set_name(name_in_modelica(externalNI->name));
    try{
        slack->set_sequenceNumber(terminal->sequenceNumber);
    }catch(ReadingUninitializedField* e){
        slack->set_sequenceNumber(0);
        this->set_exit_code(3);
        std::cerr <<"Missing sequence number in terminal sequence number " << terminal->name << std::endl;
    }
    slack->set_sequenceNumber(terminal->sequenceNumber);
    try{
        slack->set_connected(terminal->connected);
    }catch(ReadingUninitializedField* e){
        slack->set_connected(1);
        std::cerr <<"Missing connected property for terminal  " << terminal->name << std::endl;
    }
    slack->annotation.placement.visible = true;
    if (baseVoltageMap.find(externalNI) != baseVoltageMap.end()){
        slack->set_Vnom(baseVoltageMap[externalNI]->nominalVoltage.value);
    }else{
        slack->set_Vnom(((TPNodePtr)tp_node)->BaseVoltage->nominalVoltage.value);
        std::cerr <<"No BaseVoltage for ExternalNetworkInjection taking TPNode Voltage: " << std::endl;
    }



    if(this->configManager.svSettings.useSVforExternalNetworkInjection == true &&
       this->configManager.ss.use_TPNodes== true){
        slack->set_phiV(svVoltageMap[tp_node]->angle.value);
    }


    if(this->configManager.us.enable){
        FIX_NEPLAN_VOLTAGE(slack);
    }

    if (this->configManager.slack_parameters.enable) {
        SET_TRANS_EXTENT(slack,slack);
        slack->annotation.placement.visible = configManager.slack_parameters.annotation.visible;
    }
    if (externalNI->DiagramObjects.begin() == externalNI->DiagramObjects.end()){
        std::cerr << "Missing Diagram Object for ExternalNIHandler: " << externalNI->name << " Default Position 0,0 \n";
        slack->annotation.placement.transformation.origin.x = 0;
        slack->annotation.placement.transformation.origin.y = 0;
        slack->annotation.placement.transformation.rotation = 0;

        ctemplate::TemplateDictionary *slack_dict = dict->AddIncludeDictionary("SLACK_DICT");
        slack_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/Slack.tpl");
        slack->set_template_values(slack_dict);
    }else{
        int counter = 0;
        float currX = 0;
        float currY = 0;

        for (diagram_it = externalNI->DiagramObjects.begin(); diagram_it!=externalNI->DiagramObjects.end(); ++diagram_it) {
            _t_points = this->calculate_average_position();
            currX += _t_points.xPosition;
            currY += _t_points.yPosition;
            counter += 1;
        }
        slack->annotation.placement.transformation.origin.x = currX / counter;
        slack->annotation.placement.transformation.origin.y = currY / counter;


        ctemplate::TemplateDictionary *slack_dict = dict->AddIncludeDictionary("SLACK_DICT");
        slack_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/Slack.tpl");
        slack->set_template_values(slack_dict);
    }

    return slack;
}

/**
 * ConductingEquipment of Terminal
 * ConductingEquipment cast to ACLineSegment
 * Convert to Pi_line in Modelica
 */
ModPiLine *
CIMObjectHandler::ACLineSegmentHandler(BaseClass* tp_node, BusBar* busbar, const TerminalPtr terminal, const AcLinePtr ac_line,
                                       ctemplate::TemplateDictionary *dict, std::string node1Name /* = "" */, std::string node2Name /* = "" */) {

    ModPiLine * piline = new ModPiLine();
    piline->set_name(name_in_modelica(ac_line->name));
    float length = ac_line->length.value;

    // CIM unit length should be km but some files may have there lengths in m
    if(this->configManager.us.length_unit == "m"){
        length = length / 1000;
    }else if(this->configManager.us.length_unit == "km"){
    }

    piline->set_length(length);


    try{
        piline->set_r(ac_line->r.value/length);
    }catch(ReadingUninitializedField* e){
        piline->set_length(length);
        this->set_exit_code(3);
        std::cerr<<"Missing r value " << ac_line->name<< std::endl;
    }


    try{
        piline->set_x(ac_line->x.value/length);
    }catch(ReadingUninitializedField* e){
        piline->set_x(length);
        this->set_exit_code(3);
        std::cerr<<"Missing x value "<<ac_line->name << std::endl;
    }

    try{
        piline->set_b(ac_line->bch.value/length);
    }catch(ReadingUninitializedField* e){
        piline->set_b(length);
        this->set_exit_code(3);
        std::cerr<<"Missing bch value"<<ac_line->name  << std::endl;
    }


    try{
        piline->set_g(ac_line->gch.value);///ac_line->length.value);
    }catch(ReadingUninitializedField* e){
        piline->set_g(0);
        this->set_exit_code(3);
        std::cerr<<"Missing gch value"<<ac_line->name  << std::endl;
    }
    try{
        if(terminal->sequenceNumber == 2) {
            piline->setBus2(busbar);
        }else{
            piline->setBus1(busbar);
        }
    }catch(ReadingUninitializedField* e){
        piline->setBus1(busbar);
        this->set_exit_code(3);
        std::cerr<<"Missing terminal seqNR" << terminal->name<< std::endl;
    }

    if(configManager.gs.add_Vnom_to_PiLine == true && configManager.ss.use_TPNodes == true){
        try{
            double vnom = ((TPNodePtr)tp_node)->BaseVoltage->nominalVoltage.value;
            if(this->configManager.us.enable) {
                if (this->configManager.us.voltage_unit == "V") {
                    piline->set_Vnom(vnom);
                } else if (this->configManager.us.voltage_unit == "kV") {
                    piline->set_Vnom(vnom * 1000);
                } else if (this->configManager.us.voltage_unit == "mV") {
                    piline->set_Vnom(vnom * 0.001);
                } else if (this->configManager.us.voltage_unit == "MV") {
                    piline->set_Vnom(vnom * 1000000);
                }
                // TODO SET DISPLAY UNIT
            }else{
                piline->set_Vnom(vnom);
            }

            //std::cout <<"Adding TPNode Voltage to PiLine: " << piline->name() << std::endl;
        }catch(ReadingUninitializedField* e){
            piline->set_Vnom(-1); // TODO find default value
            this->set_exit_code(3);
            std::cerr<<"No Base Voltage at corresponding TPNode for PiLine " << piline->name() << std::endl;
        }
    }else{
        piline->set_Vnom(-1);
    }



    if (this->configManager.gs.create_distaix_format == true && !node1Name.empty() && !node2Name.empty()) {
        piline->set_node1(node1Name);
        piline->set_node2(node2Name);
    }

    //find I_Max
    if(OpLimitMap[ac_line]){
        for(OpLimitPtr op_limit: OpLimitMap[ac_line]->OperationalLimitValue){
            if(auto current_limit = dynamic_cast<CurrentLimitPtr>(op_limit)){
                //if(current_limit->name == "Normal")
                piline->set_Imax(current_limit->value.value);
                /*else{
                    std::cout << "name of Current Limit is not Normal "<<piline->name() << std::endl;
                }*/
            }else{
                std::cerr << "missing current Limit for PiLine "<<piline->name() << std::endl;
                this->set_exit_code(3);
            }
        }
    }
    if(this->configManager.us.enable){
        if(this->configManager.us.current_unit == "A"){
            piline->set_Imax(piline->Imax());
        } else if(this->configManager.us.current_unit == "kA"){
            piline->set_Imax(piline->Imax()*1000);
        } else if(this->configManager.us.current_unit == "mA"){
            piline->set_Imax(piline->Imax()*0.001);
        } else if(this->configManager.us.current_unit == "MA"){
            piline->set_Imax(piline->Imax()*1000000);
        }
    }


    try{
        piline->set_connected(terminal->connected);
    }catch(ReadingUninitializedField* e){
        piline->set_connected(1);
        this->set_exit_code(3);
        std::cerr<<"Missing connection info in terminal " << terminal << std::endl;
    }
    piline->annotation.placement.visible = true;

    if (this->configManager.piline_parameters.enable) {

        SET_TRANS_EXTENT(piline,piline);
        piline->annotation.placement.visible = configManager.piline_parameters.annotation.visible;
    }

    if (ac_line->DiagramObjects.begin() == ac_line->DiagramObjects.end()){
        std::cerr << "Missing Diagram Object for acLine: " << ac_line->name << " Default Position 0,0 \n";
        this->set_exit_code(3);
        piline->annotation.placement.transformation.origin.x = 0;
        piline->annotation.placement.transformation.origin.y = 0;
        piline->annotation.placement.transformation.rotation = 0;

        ctemplate::TemplateDictionary *piLine_dict = dict->AddIncludeDictionary("PILINE_DICT");
        piLine_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/PiLine.tpl");
        if(configManager.gs.add_Vnom_to_PiLine == true) {
            piLine_dict->AddSectionDictionary("PILINE_VNOM");
        }
        piline->set_template_values(piLine_dict);
    }else {
        int counter = 0;
        float currX = 0;
        float currY = 0;
        for (diagram_it = ac_line->DiagramObjects.begin(); diagram_it != ac_line->DiagramObjects.end(); ++diagram_it) {
            _t_points = this->calculate_average_position();
            currX += _t_points.xPosition;
            currY += _t_points.yPosition;
            counter += 1;
            try{
                piline->annotation.placement.transformation.rotation = (*diagram_it)->rotation.value - 90;
            }catch(ReadingUninitializedField* e){
                piline->annotation.placement.transformation.rotation = 0;
                this->set_exit_code(3);
                std::cerr <<"Missing rotation for diagram object " << piline->name() << std::endl;
            }
        }
        piline->annotation.placement.transformation.origin.x = currX/counter;
        piline->annotation.placement.transformation.origin.y = currY/counter;

        ctemplate::TemplateDictionary *piLine_dict = dict->AddIncludeDictionary("PILINE_DICT");
        piLine_dict->SetFilename(
                this->configManager.ts.directory_path + "resource/" + template_folder + "/PiLine.tpl");
        if(configManager.gs.add_Vnom_to_PiLine == true) {
            piLine_dict->AddSectionDictionary("PILINE_VNOM");
        }
        piline->set_template_values(piLine_dict);

    }
    return piline;
}

/**
 * ConductingEquipment of Terminal
 * ConductingEquipment cast to PowerTransformer
 * Convert to Transformer in Modelica
 */
ModTransformer* CIMObjectHandler::PowerTransformerHandler(BusBar* busbar, const TerminalPtr terminal,
                                                       const PowerTrafoPtr power_trafo,
                                                       ctemplate::TemplateDictionary *dict) {

    ModTransformer* trafo = new ModTransformer();
    trafo->set_name(name_in_modelica(power_trafo->name));
    try{
        if(terminal->sequenceNumber == 2) {
            trafo->setBus2(busbar);
        }else{
            trafo->setBus1(busbar);
        }
    }catch(ReadingUninitializedField* e){
        trafo->setBus1(busbar);
        this->set_exit_code(3);
        std::cerr <<"Missing sequence number in terminal sequence number " << terminal->name << std::endl;
    }

    try{
        trafo->set_connected(terminal->connected);
    }catch(ReadingUninitializedField* e){
        trafo->set_connected(1);
        this->set_exit_code(3);
        std::cerr <<"Missing connected property in terminal " << terminal->name << std::endl;
    }

    trafo->annotation.placement.visible = true;

    std::list<PowerTransformerEndPtr>::iterator transformer_end_it;
    for (transformer_end_it = power_trafo->PowerTransformerEnd.begin();
         transformer_end_it!=power_trafo->PowerTransformerEnd.end();
         ++transformer_end_it) {
        if ((*transformer_end_it)->endNumber==1) {

            trafo->set_Sr((*transformer_end_it)->ratedS.value*1000000); // Lukas FIXME TODO: Hier muss wohl configManager.us.active_power_unit ausgewertet werden!
            trafo->set_r((*transformer_end_it)->r.value);
            trafo->set_x((*transformer_end_it)->x.value);
            trafo->set_b((*transformer_end_it)->b.value);

            if((*transformer_end_it)->RatioTapChanger != nullptr){
                if(configManager.gs.tapStepPos == "original"){
                    trafo->set_tap_pos( (*transformer_end_it)->RatioTapChanger->step);
                }else{
                    trafo->set_tap_pos( ((*transformer_end_it)->RatioTapChanger->step - 1) * 1000);
                }

            }

            if(this->configManager.us.enable) {
                if (this->configManager.us.voltage_unit == "V") {
                    trafo->set_Vnom1((*transformer_end_it)->ratedU.value);
                } else if (this->configManager.us.voltage_unit == "kV") {
                    trafo->set_Vnom1((*transformer_end_it)->ratedU.value*1000);
                } else if (this->configManager.us.voltage_unit == "mV") {
                    trafo->set_Vnom1((*transformer_end_it)->ratedU.value*0.001);
                } else if (this->configManager.us.voltage_unit == "MV") {
                    trafo->set_Vnom1((*transformer_end_it)->ratedU.value*1000000);
                }
            }

            trafo->calc_URr();
            trafo->calc_Ukr();


        } else if ((*transformer_end_it)->endNumber==2) {

            if(this->configManager.us.enable) {
                if (this->configManager.us.voltage_unit == "V") {
                    trafo->set_Vnom2((*transformer_end_it)->ratedU.value);
                } else if (this->configManager.us.voltage_unit == "kV") {
                    trafo->set_Vnom2((*transformer_end_it)->ratedU.value*1000);
                } else if (this->configManager.us.voltage_unit == "mV") {
                    trafo->set_Vnom2((*transformer_end_it)->ratedU.value*0.001);
                } else if (this->configManager.us.voltage_unit == "MV") {
                    trafo->set_Vnom2((*transformer_end_it)->ratedU.value*1000000);
                }
            }
        }
    }

    if (this->configManager.trafo_parameters.enable) {

        SET_TRANS_EXTENT(trafo,trafo);
        trafo->annotation.placement.visible = configManager.trafo_parameters.annotation.visible;
    }

    if(power_trafo->DiagramObjects.begin() == power_trafo->DiagramObjects.end()){
        std::cerr << "Missing Diagram Object for PowerTrafo: " << power_trafo->name << " Default Position 0,0 \n";
        this->set_exit_code(3);
        trafo->annotation.placement.transformation.origin.x = 0;
        trafo->annotation.placement.transformation.origin.y = 0;
        trafo->annotation.placement.transformation.rotation = 0;

        ctemplate::TemplateDictionary *powerTrafo_dict = dict->AddIncludeDictionary("TRANSFORMER_DICT");
        powerTrafo_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/Transformer.tpl");
        trafo->set_template_values(powerTrafo_dict);
    }else {
        int counter = 0;
        float currX = 0;
        float currY = 0;

        for (diagram_it = power_trafo->DiagramObjects.begin();
             diagram_it != power_trafo->DiagramObjects.end();
             ++diagram_it) {
            _t_points = this->calculate_average_position();
            currX += _t_points.xPosition;
            currY += _t_points.yPosition;
            counter += 1;
            try{
                trafo->annotation.placement.transformation.rotation = (*diagram_it)->rotation.value - 90;
            }catch(ReadingUninitializedField* e){
                trafo->annotation.placement.transformation.rotation = 0;
                this->set_exit_code(3);
                std::cerr <<"Missing rotation for diagram obj" << trafo->name() << std::endl;

            }


        }
        trafo->annotation.placement.transformation.origin.x = currX/counter;
        trafo->annotation.placement.transformation.origin.y = currY/counter;

        ctemplate::TemplateDictionary *powerTrafo_dict = dict->AddIncludeDictionary("TRANSFORMER_DICT");
        powerTrafo_dict->SetFilename(
                this->configManager.ts.directory_path + "resource/" + template_folder + "/Transformer.tpl");
        trafo->set_template_values(powerTrafo_dict);

    }
    return trafo;
}

/**
 * ConductingEquipment of Terminal
 * ConductingEquipment cast to energy_consumer
 * Convert to pqload in Modelica
 */
ModPQLoad* CIMObjectHandler::EnergyConsumerHandler(BaseClass* tp_node, const TerminalPtr terminal,
                                                const EnergyConsumerPtr energy_consumer,
                                                ctemplate::TemplateDictionary *dict) {

    ModPQLoad* pqload = new ModPQLoad();

    if (this->configManager.pqload_parameters.type == 1 ) {

        pqload->set_PQLoadType(PQLoadType::Standard);

    } else if(this->configManager.pqload_parameters.type == 2){

        pqload->set_PQLoadType(PQLoadType::Profile);

    } else if(this->configManager.pqload_parameters.type == 3){

        pqload->set_PQLoadType(PQLoadType::NormProfile);
    }

    if(this->configManager.svSettings.useSVforEnergyConsumer == true){// && svPowerFlowMap[terminal] ) {
        try{
            pqload->set_Pnom(svPowerFlowMap[terminal]->p.value);
        }catch(ReadingUninitializedField* e1){
            std::cerr <<"Missing entry in PowerFlow Map for terminal: " << terminal->name << std::endl;
            this->set_exit_code(3);
            pqload->set_Pnom(1);
        }
        try{
            pqload->set_Qnom(svPowerFlowMap[terminal]->q.value);
        }catch(ReadingUninitializedField* e1){
            std::cerr <<"Missing entry in PowerFlow Map for terminal: " << terminal->name << std::endl;
            this->set_exit_code(3);
            pqload->set_Qnom(1);
        }

    }else{
        try{
            pqload->set_Pnom(energy_consumer->pfixed.value);
        }catch(ReadingUninitializedField* e){
            try{
                pqload->set_Pnom(energy_consumer->p.value);
            }catch(ReadingUninitializedField* e1){
                std::cerr <<"Reading unititalized Pnom for PQLoad: " << std::endl;
                this->set_exit_code(3);
                pqload->set_Pnom(1);
            }
        }

        try{
            pqload->set_Qnom(energy_consumer->qfixed.value);
        }catch(ReadingUninitializedField* e){
            try{
                pqload->set_Qnom(energy_consumer->q.value);
            }catch(ReadingUninitializedField* e1){
                std::cerr <<"Reading unititalized Qnom for PQLoad: " << std::endl;
                this->set_exit_code(3);
                pqload->set_Qnom(1);
            }
        }
    }

    pqload->set_name(name_in_modelica(energy_consumer->name));
    if (baseVoltageMap.find(energy_consumer) != baseVoltageMap.end()){
        double vnom = baseVoltageMap[energy_consumer]->nominalVoltage.value;
        if(this->configManager.us.enable) {
            if (this->configManager.us.voltage_unit == "V") {
                pqload->set_Vnom(vnom);
            } else if (this->configManager.us.voltage_unit == "kV") {
                pqload->set_Vnom(vnom * 1000);
            } else if (this->configManager.us.voltage_unit == "mV") {
                pqload->set_Vnom(vnom * 0.001);
            } else if (this->configManager.us.voltage_unit == "MV") {
                pqload->set_Vnom(vnom * 1000000);
            }
            // TODO SET DISPLAY UNIT
        }else{
            pqload->set_Vnom(vnom);
        }
    }else{
        double vnom = (((TPNodePtr)tp_node)->BaseVoltage->nominalVoltage.value);
        pqload->set_Vnom(vnom);
        std::cerr <<"No BaseVoltage for EnergyConsumer taking TPNode Voltage: " << std::endl;
    }
    if(this->configManager.us.enable){
        FIX_NEPLAN_VOLTAGE(pqload);

        if(this->configManager.us.active_power_unit == "W"){
            pqload->set_Pnom(pqload->Pnom());
        } else if(this->configManager.us.active_power_unit == "kW"){
            pqload->set_Pnom(pqload->Pnom()*1000);
        } else if(this->configManager.us.active_power_unit == "mW"){
            pqload->set_Pnom(pqload->Pnom()*0.001);
        } else if(this->configManager.us.active_power_unit == "MW"){
            pqload->set_Pnom(pqload->Pnom()*1000000);
        }

        if(this->configManager.us.reactive_power_unit == "var"){
            pqload->set_Qnom(pqload->Qnom());
        } else if(this->configManager.us.reactive_power_unit == "kvar"){
            pqload->set_Qnom(pqload->Qnom()*1000);
        } else if(this->configManager.us.reactive_power_unit == "mvar"){
            pqload->set_Qnom(pqload->Qnom()*0.001);
        } else if(this->configManager.us.reactive_power_unit == "Mvar"){
            pqload->set_Qnom(pqload->Qnom()*1000000);
        }
    }

    pqload->set_name(name_in_modelica(energy_consumer->name));
    try{
        pqload->set_sequenceNumber(terminal->sequenceNumber);
    }catch(ReadingUninitializedField* e){
        pqload->set_sequenceNumber(0);
        this->set_exit_code(3);
        std::cerr <<"Missing sequence number in terminal sequence number " << terminal->name << std::endl;
    }
    try{
        pqload->set_connected(terminal->connected);
    }catch(ReadingUninitializedField* e){
        pqload->set_connected(0);
        this->set_exit_code(3);
        std::cerr <<"Missing connection info in terminal sequence number " << terminal->name << std::endl;
    }
    pqload->annotation.placement.visible = true;

    if (this->configManager.pqload_parameters.enable) {

        SET_TRANS_EXTENT(pqload,pqload);
        pqload->annotation.placement.visible = configManager.pqload_parameters.annotation.visible;
        pqload->set_profileName(configManager.pqload_parameters.profile_name);
        pqload->set_profileFileName(configManager.pqload_parameters.profile_filename);
    }

    if(energy_consumer->DiagramObjects.begin() == energy_consumer->DiagramObjects.end()){
        std::cerr << "Missing Diagram Object for EnergyConsumer: " << energy_consumer->name << " Default Position 0,0 \n";
        pqload->annotation.placement.transformation.origin.x = 0;
        pqload->annotation.placement.transformation.origin.y = 0;
        pqload->annotation.placement.transformation.rotation = 0;

        if(this->configManager.household_parameters.use_households == false){
            if (pqload->sequenceNumber() == 0 || pqload->sequenceNumber() == 1) {

                if (this->configManager.pqload_parameters.type == 1 && pqload->PQLoadType() == PQLoadType::Standard) {
                    ctemplate::TemplateDictionary *pqLoad_dict = dict->AddIncludeDictionary("PQLOAD_DICT");
                    pqLoad_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/PQLoad.tpl");
                    pqload->set_template_values(pqLoad_dict);

                } else if(this->configManager.pqload_parameters.type == 2 && pqload->PQLoadType() == PQLoadType::Profile){
                    ctemplate::TemplateDictionary *pqLoad_dict = dict->AddIncludeDictionary("PQLOAD_PROFILE_DICT");
                    pqLoad_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/PQLoadProfile.tpl");
                    pqload->set_template_values(pqLoad_dict);

                } else if(this->configManager.pqload_parameters.type == 3 && pqload->PQLoadType() == PQLoadType::NormProfile){
                    ctemplate::TemplateDictionary *pqLoad_dict = dict->AddIncludeDictionary("PQLOAD_NORM_PROFILE_DICT");
                    pqLoad_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/PQLoadNormProfile.tpl");
                    pqload->set_template_values(pqLoad_dict);
                }
            }
        }
    }else{
        int counter = 0;
        float currX = 0;
        float currY = 0;

        for (diagram_it = energy_consumer->DiagramObjects.begin(); diagram_it!=energy_consumer->DiagramObjects.end();
             ++diagram_it) {
            _t_points = this->calculate_average_position();
            currX += _t_points.xPosition;
            currY += _t_points.yPosition;
            counter += 1;
            try{
                pqload->annotation.placement.transformation.rotation = (*diagram_it)->rotation.value;
            }catch(ReadingUninitializedField* e){
                pqload->annotation.placement.transformation.rotation = 0;
                this->set_exit_code(3);
                std::cerr <<"Missing rotation for diagram obj of pq load"<< energy_consumer->name << std::endl;
            }

        }

        pqload->annotation.placement.transformation.origin.x = currX /counter;
        pqload->annotation.placement.transformation.origin.y = currY /counter;


        if(this->configManager.household_parameters.use_households == false){
            if (pqload->sequenceNumber() == 0 || pqload->sequenceNumber() == 1) {

                if (this->configManager.pqload_parameters.type == 1 && pqload->PQLoadType() == PQLoadType::Standard) {
                    ctemplate::TemplateDictionary *pqLoad_dict = dict->AddIncludeDictionary("PQLOAD_DICT");
                    pqLoad_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/PQLoad.tpl");
                    pqload->set_template_values(pqLoad_dict);

                } else if(this->configManager.pqload_parameters.type == 2 && pqload->PQLoadType() == PQLoadType::Profile){
                    ctemplate::TemplateDictionary *pqLoad_dict = dict->AddIncludeDictionary("PQLOAD_PROFILE_DICT");
                    pqLoad_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/PQLoadProfile.tpl");
                    pqload->set_template_values(pqLoad_dict);

                } else if(this->configManager.pqload_parameters.type == 3 && pqload->PQLoadType() == PQLoadType::NormProfile){
                    ctemplate::TemplateDictionary *pqLoad_dict = dict->AddIncludeDictionary("PQLOAD_NORM_PROFILE_DICT");
                    pqLoad_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/PQLoadNormProfile.tpl");
                    pqload->set_template_values(pqLoad_dict);
                }
            }
        }
    }
    return pqload;
}

/**
* ConductingEquipment of Terminal
* ConductingEquipment cast to SynchronousMachine
* Convert to SolarGenerator in Modelica
*/
ModSolarGenerator* CIMObjectHandler::SynchronousMachineHandlerType2(const TerminalPtr terminal,
                                                                 const SynMachinePtr syn_machine,
                                                                 ctemplate::TemplateDictionary *dict) {
    ModSolarGenerator* solar_generator = new ModSolarGenerator();

    solar_generator->set_name(name_in_modelica(syn_machine->name));
    solar_generator->annotation.placement.visible = true;
    solar_generator->set_connected(terminal->connected);

    try{
        solar_generator->set_sequenceNumber(terminal->sequenceNumber);
    }catch(ReadingUninitializedField* e){
        solar_generator->set_sequenceNumber(0);
        this->set_exit_code(3);
        std::cerr <<"Missing sequence number in terminal sequence number " << terminal << std::endl;
    }

    if (this->configManager.solar_gen_parameters.enable) {
        SET_TRANS_EXTENT(solar_generator,solar_gen);
        solar_generator->annotation.placement.visible = configManager.solar_gen_parameters.annotation.visible;
    }
    if(syn_machine->DiagramObjects.begin() == syn_machine->DiagramObjects.end()){
        std::cerr << "Missing Diagram Object for SyncronousMachine2: " << syn_machine->name << " Default Position 0,0 \n";
        this->set_exit_code(3);
        solar_generator->annotation.placement.transformation.origin.x = 0;
        solar_generator->annotation.placement.transformation.origin.y = 0;
        solar_generator->annotation.placement.transformation.rotation = 0;

        if (this->configManager.solar_gen_parameters.enable) {
            if (this->configManager.household_parameters.use_households == false) {

                if (solar_generator->sequenceNumber()==0 || solar_generator->sequenceNumber()==1) {
                    ctemplate::TemplateDictionary *solar_generator_dict = dict->AddIncludeDictionary(
                            "SOLARGENERATOR_DICT");
                    solar_generator_dict->SetFilename(
                            this->configManager.ts.directory_path + "resource/" + template_folder + "/SolarGenerator.tpl");
                    solar_generator->set_template_values(solar_generator_dict);
                }
            }
        }
    }
    for (diagram_it = syn_machine->DiagramObjects.begin();
         diagram_it!=syn_machine->DiagramObjects.end();
         ++diagram_it) {
        _t_points = this->calculate_average_position();
        solar_generator->annotation.placement.transformation.origin.x = _t_points.xPosition;
        solar_generator->annotation.placement.transformation.origin.y = _t_points.yPosition;
        solar_generator->annotation.placement.transformation.rotation = (*diagram_it)->rotation.value;

        if (this->configManager.solar_gen_parameters.enable) {
            if (this->configManager.household_parameters.use_households == false) {

                if (solar_generator->sequenceNumber()==0 || solar_generator->sequenceNumber()==1) {
                    ctemplate::TemplateDictionary *solar_generator_dict = dict->AddIncludeDictionary(
                            "SOLARGENERATOR_DICT");
                    solar_generator_dict->SetFilename(
                            this->configManager.ts.directory_path + "resource/" + template_folder + "/SolarGenerator.tpl");
                    solar_generator->set_template_values(solar_generator_dict);
                }
            }
        }
    }

    return solar_generator;
}

/**
 * ConductingEquipment of Terminal
 * ConductingEquipment cast to SynchronousMachine
 * Convert to WindGenerator in Modelica
 */
ModWindGenerator* CIMObjectHandler::SynchronousMachineHandlerType1(const TerminalPtr terminal,
                                                                const SynMachinePtr syn_machine,
                                                                ctemplate::TemplateDictionary *dict) {
    ModWindGenerator* wind_generator = new ModWindGenerator();

    wind_generator->set_name(name_in_modelica(syn_machine->name));
    try{
        wind_generator->set_sequenceNumber(terminal->sequenceNumber);
    }catch(ReadingUninitializedField* e){
        wind_generator->set_sequenceNumber(0);
        std::cerr <<"Missing sequence number in terminal sequence number " << terminal << std::endl;
        this->set_exit_code(3);
    }
    wind_generator->set_connected(terminal->connected);
    wind_generator->annotation.placement.visible = true;

    if (this->configManager.wind_gen_parameters.enable) {
        SET_TRANS_EXTENT(wind_generator,wind_gen);
        wind_generator->annotation.placement.visible = configManager.wind_gen_parameters.annotation.visible;
    }

    if(syn_machine->DiagramObjects.begin() == syn_machine->DiagramObjects.end()){
        std::cerr << "Missing Diagram Object for SynchronousMachine: " << syn_machine->name << " Default Position 0,0 \n";
        this->set_exit_code(3);
        wind_generator->annotation.placement.transformation.origin.x = 0;
        wind_generator->annotation.placement.transformation.origin.y = 0;
        wind_generator->annotation.placement.transformation.rotation = 0;

        if (wind_generator->sequenceNumber()==0 || wind_generator->sequenceNumber()==1) {
            ctemplate::TemplateDictionary *wind_generator_dict = dict->AddIncludeDictionary("WINDGENERATOR_DICT");
            wind_generator_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/WindGenerator.tpl");
            wind_generator->set_template_values(wind_generator_dict);
        }
    }

    for (diagram_it = syn_machine->DiagramObjects.begin();
         diagram_it!=syn_machine->DiagramObjects.end();
         ++diagram_it) {
        _t_points = this->calculate_average_position();
        wind_generator->annotation.placement.transformation.origin.x = _t_points.xPosition;
        wind_generator->annotation.placement.transformation.origin.y = _t_points.yPosition;
        wind_generator->annotation.placement.transformation.rotation = (*diagram_it)->rotation.value;

        if (wind_generator->sequenceNumber()==0 || wind_generator->sequenceNumber()==1) {
            ctemplate::TemplateDictionary *wind_generator_dict = dict->AddIncludeDictionary("WINDGENERATOR_DICT");
            wind_generator_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/WindGenerator.tpl");
            wind_generator->set_template_values(wind_generator_dict);
        }
    }

    return wind_generator;
}

ModBreaker* CIMObjectHandler::BreakerHandler(BusBar* busbar, const TerminalPtr terminal, const BreakerPtr cim_breaker,ctemplate::TemplateDictionary* dict){
    ModBreaker* breaker = new ModBreaker();
    breaker->set_name(name_in_modelica(cim_breaker->name));
    breaker->set_is_closed(!cim_breaker->normalOpen);
    // TODO set Vnom
    try{
        breaker->set_connected(terminal->connected);
    }catch(ReadingUninitializedField* e){
        breaker->set_connected(0);
        this->set_exit_code(3);
        std::cerr <<"Missing connected state in terminal sequence number " << terminal << std::endl;
    }
    try{
        if(terminal->sequenceNumber == 2) {
            breaker->setBus2(busbar);
        }else{
            breaker->setBus1(busbar);
        }
    }catch(ReadingUninitializedField* e){
        breaker->setBus1(busbar);
        this->set_exit_code(3);
        std::cerr <<"Missing sequence number in terminal sequence number " << terminal << std::endl;
    }

    if(cim_breaker->DiagramObjects.begin() == cim_breaker->DiagramObjects.end()){
        std::cerr << "Missing Diagram Object for Switch: " << cim_breaker->name << " Default Position 0,0 \n";
        this->set_exit_code(3);
        breaker->annotation.placement.transformation.origin.x = 0;
        breaker->annotation.placement.transformation.origin.y = 0;
        breaker->annotation.placement.transformation.rotation = 0;

        ctemplate::TemplateDictionary *breaker_dict = dict->AddIncludeDictionary("BREAKER_DICT");
        breaker_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/Breaker.tpl");
        breaker->set_template_values(breaker_dict);
    }else{
        int counter = 0;
        float currX = 0;
        float currY = 0;
        for (diagram_it = cim_breaker->DiagramObjects.begin();
             diagram_it!= cim_breaker->DiagramObjects.end();
             ++diagram_it) {            _t_points = this->calculate_average_position();
            currX += _t_points.xPosition;
            currY += _t_points.yPosition;
            counter += 1;

        }
        try{
            breaker->annotation.placement.transformation.rotation = (*cim_breaker->DiagramObjects.begin())->rotation.value;
        }catch(ReadingUninitializedField* e){
            breaker->annotation.placement.transformation.rotation = 0;
            this->set_exit_code(3);
            std::cerr <<"Missing rotation for diagram obj" << breaker->name()<< std::endl;
        }
        breaker->annotation.placement.transformation.origin.x = currX /counter;
        breaker->annotation.placement.transformation.origin.y = currY /counter;


        ctemplate::TemplateDictionary *breaker_dict = dict->AddIncludeDictionary("BREAKER_DICT");
        breaker_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/Breaker.tpl");
        breaker->set_template_values(breaker_dict);

    }
    return breaker;
}


/**
 * ConductingEquipment of Terminal
 * ConductingEquipment cast to SynchronousMachineDynamic
 * Convert to synchMachineDynamic in Modelica
 */

SynMachineDyn * CIMObjectHandler::synMachineDynHandler(BaseClass* node, const TerminalPtr terminal,
                                                       const SynMachineDynPtr syn_machine,
                                                       ctemplate::TemplateDictionary* dict){

    SynMachineDyn * synMachineDyn = new SynMachineDyn();
    synMachineDyn->set_name(name_in_modelica(syn_machine->name));

    try{
        synMachineDyn->set_sequenceNumber(terminal->sequenceNumber);
    }catch(ReadingUninitializedField* e){
        synMachineDyn->set_sequenceNumber(0);
        this->set_exit_code(3);
        std::cerr <<"Missing sequence number in terminal sequence number " << terminal->name << std::endl;
    }
    try{
        synMachineDyn->set_connected(terminal->connected);
    }catch(ReadingUninitializedField* e){
        synMachineDyn->set_connected(1);
        this->set_exit_code(3);
        std::cerr <<"Missing connected property in terminal " << terminal->name << std::endl;
    }
    synMachineDyn->annotation.placement.visible = true;

    double v_unit_conversion=1;
    double s_unit_conversion=1;
    if(this->configManager.us.active_power_unit == "W"){
        s_unit_conversion = 1;
    } else if(this->configManager.us.active_power_unit == "kW"){
        s_unit_conversion =  1000;
    } else if(this->configManager.us.active_power_unit == "mW"){
        s_unit_conversion =  0.001;
    } else if(this->configManager.us.active_power_unit == "MW"){
        s_unit_conversion =  1000000;
    }
    if(this->configManager.us.voltage_unit == "V"){
        v_unit_conversion = 1;
    } else if(this->configManager.us.voltage_unit == "kV"){
        v_unit_conversion =  1000;
    } else if(this->configManager.us.voltage_unit == "mV"){
        v_unit_conversion =  0.001;
    } else if(this->configManager.us.voltage_unit == "MV"){
        v_unit_conversion =  1000000;
    }

    synMachineDyn->set_raPu((syn_machine)->statorResistance.value);
    synMachineDyn->set_xdPU(syn_machine->xDirectSync.value);
    synMachineDyn->set_xlPu(syn_machine->statorLeakageReactance.value);
    synMachineDyn->set_xpdPu(syn_machine->xDirectTrans.value);
    synMachineDyn->set_xppdPu(syn_machine->xDirectSubtrans.value);
    synMachineDyn->set_xppqPu(syn_machine->xQuadSubtrans.value);
    synMachineDyn->set_xpqPu(syn_machine->xQuadTrans.value);
    synMachineDyn->set_xqPu(syn_machine->xQuadSync.value);
    synMachineDyn->set_Tpd0(syn_machine->tpdo.value);
    synMachineDyn->set_Tppd0(syn_machine->tppdo.value);
    synMachineDyn->set_Tppq0(syn_machine->tppqo.value);
    synMachineDyn->set_Tpq0(syn_machine->tpqo.value);
    // TODO: change hard-coded unit conversion
    synMachineDyn->set_SNom(syn_machine->SynchronousMachine->ratedS.value * s_unit_conversion);
    synMachineDyn->set_VNom(syn_machine->SynchronousMachine->ratedU.value * v_unit_conversion);
    synMachineDyn->set_inertia(syn_machine->inertia.value);

    // TODO MBY NEW SVVOLTAGE/PWRFLOW OPTION
    if(this->configManager.svSettings.useSVforGeneratingUnit == true ) {//&& svPowerFlowMap[terminal] && svVoltageMap[tp_node]){


        try {
            // TODO CONVERSION TO RADIANS
            // Junjie: No need, I updated conversion inside templates
            synMachineDyn->set_UPhaseStart( svVoltageMap[node]->angle.value);
        } catch (ReadingUninitializedField *e) {
            this->set_exit_code(3);
            std::cerr << "No SVVoltage at TPNode for SynMachineDyn " << syn_machine->name << std::endl;
        }
        try {
            synMachineDyn->set_UStart(svVoltageMap[node]->v.value * v_unit_conversion);
        }
        catch (ReadingUninitializedField *e)
        {
            this->set_exit_code(3);
            std::cerr << "No SVVoltage at TPNode for SynMachineDyn " << syn_machine->name << std::endl;
        }

        try {
            synMachineDyn->set_QStart(svPowerFlowMap[terminal]->q.value * s_unit_conversion);
        } catch (ReadingUninitializedField *e) {
            this->set_exit_code(3);
            std::cerr << "No SVPowerFlow at terminal for SynMachineDyn " << syn_machine->name << std::endl;
        }
        try {
            synMachineDyn->set_PStart(svPowerFlowMap[terminal]->p.value * s_unit_conversion);
        } catch (ReadingUninitializedField *e) {
            this->set_exit_code(3);
            std::cerr << "No SVPowerFlow at terminal for SynMachineDyn " << syn_machine->name << std::endl;
        }

    }
    auto syn_machine_stat=syn_machine->SynchronousMachine;
    if(syn_machine_stat->DiagramObjects.begin() == syn_machine_stat->DiagramObjects.end()){
        std::cerr << "Missing Diagram Object for SynchronousMachine: " << syn_machine->name << " Default Position 0,0 \n";
        this->set_exit_code(3);
        synMachineDyn->annotation.placement.transformation.origin.x = 0;
        synMachineDyn->annotation.placement.transformation.origin.y = 0;
        synMachineDyn->annotation.placement.transformation.rotation = 0;

        ctemplate::TemplateDictionary *synMachineDyn_dict = dict->AddIncludeDictionary("SynchronousMachine4Windings_DICT");
        synMachineDyn_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/SynchronousMachine4Windings.tpl");
        synMachineDyn->set_template_values(synMachineDyn_dict);
    }else{
        int counter = 0;
        float currX = 0;
        float currY = 0;
        for (diagram_it = syn_machine_stat->DiagramObjects.begin();
             diagram_it!= syn_machine_stat->DiagramObjects.end();
             ++diagram_it) {            _t_points = this->calculate_average_position();
            currX += _t_points.xPosition;
            currY += _t_points.yPosition;
            counter += 1;

            try{
                synMachineDyn->annotation.placement.transformation.rotation = (*diagram_it)->rotation.value;
            }catch(ReadingUninitializedField* e){
                synMachineDyn->annotation.placement.transformation.rotation = 0;
                this->set_exit_code(3);
                std::cerr <<"Missing rotation for diagram obj" << synMachineDyn->name()<< std::endl;

            }
        }

        synMachineDyn->annotation.placement.transformation.origin.x = currX /counter;
        synMachineDyn->annotation.placement.transformation.origin.y = currY /counter;


        ctemplate::TemplateDictionary *synMachineDyn_dict = dict->AddIncludeDictionary("SynchronousMachine4Windings_DICT");
        synMachineDyn_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/SynchronousMachine4Windings.tpl");
        synMachineDyn->set_template_values(synMachineDyn_dict);

    }

    return synMachineDyn;



}


/**
 * ConductingEquipment of Terminal
 * ConductingEquipment cast to SynchronousMachine
 * Convert to PVNode in Modelica
 */

ModPVNode * CIMObjectHandler::SynchronousMachineHandlerType0(BaseClass* tp_node, const TerminalPtr terminal,
                                                          const SynMachinePtr syn_machine,
                                                          ctemplate::TemplateDictionary *dict) {
    ModPVNode* pv_node = new ModPVNode();
    pv_node->set_name(name_in_modelica(syn_machine->name));
    try{
        pv_node->set_sequenceNumber(terminal->sequenceNumber);
    }catch(ReadingUninitializedField* e){
        pv_node->set_sequenceNumber(0);
        this->set_exit_code(3);
        std::cerr <<"Missing sequence number in terminal sequence number " << terminal->name << std::endl;
    }
    try{
        pv_node->set_connected(terminal->connected);
    }catch(ReadingUninitializedField* e){
        pv_node->set_connected(1);
        this->set_exit_code(3);
        std::cerr <<"Missing connected property in terminal " << terminal->name << std::endl;
    }
    pv_node->annotation.placement.visible = true;

    if(this->configManager.us.enable){
        try {
            if(this->configManager.us.voltage_unit == "V"){
                pv_node->setVnom((syn_machine)->ratedU.value);
            } else if(this->configManager.us.voltage_unit == "kV"){
                pv_node->setVnom((syn_machine)->ratedU.value * 1000);
            } else if(this->configManager.us.voltage_unit == "mV"){
                pv_node->setVnom((syn_machine)->ratedU.value * 0.001);
            } else if(this->configManager.us.voltage_unit == "MV"){
                pv_node->setVnom((syn_machine)->ratedU.value * 1000000);
            }
        }catch(ReadingUninitializedField* e) {
            if(baseVoltageMap.find(syn_machine)!= baseVoltageMap.end()){
                if (this->configManager.us.voltage_unit == "V") {
                    pv_node->setVnom(baseVoltageMap[syn_machine]->nominalVoltage.value);
                } else if (this->configManager.us.voltage_unit == "kV") {
                    pv_node->setVnom(baseVoltageMap[syn_machine]->nominalVoltage.value * 1000);
                } else if (this->configManager.us.voltage_unit == "mV") {
                    pv_node->setVnom(baseVoltageMap[syn_machine]->nominalVoltage.value * 0.001);
                } else if (this->configManager.us.voltage_unit == "MV") {
                    pv_node->setVnom(baseVoltageMap[syn_machine]->nominalVoltage.value * 1000000);
                }
                this->set_exit_code(3);
                std::cerr << "Unitialized ratedU for Synchronous Machine taking TopologicalNode BaseVoltage " << syn_machine->name
                          << std::endl;
            }
            else{
                this->set_exit_code(3);
                std::cerr << "Synchronous Machine without ratedU and without BaseVoltage at corresponding TPNode" << syn_machine->name
                          << std::endl;
            }
        }

    }

    if(this->configManager.svSettings.useSVforGeneratingUnit == true ){//&& svPowerFlowMap[terminal] && svVoltageMap[tp_node]){

        if(this->configManager.us.enable){
            if(this->configManager.us.active_power_unit == "W"){
                pv_node->setPgen(-svPowerFlowMap[terminal]->p.value);
            } else if(this->configManager.us.active_power_unit == "kW"){
                pv_node->setPgen(-svPowerFlowMap[terminal]->p.value * 1000);
            } else if(this->configManager.us.active_power_unit == "mW"){
                pv_node->setPgen(-svPowerFlowMap[terminal]->p.value * 0.001);
            } else if(this->configManager.us.active_power_unit == "MW"){
                pv_node->setPgen(-svPowerFlowMap[terminal]->p.value * 1000000);
            }
            if(this->configManager.ss.use_TPNodes == true){
                if(this->configManager.us.voltage_unit == "V"){
                    pv_node->setVabs(svVoltageMap[tp_node]->v.value);
                } else if(this->configManager.us.voltage_unit == "kV"){
                    pv_node->setVabs(svVoltageMap[tp_node]->v.value * 1000);
                } else if(this->configManager.us.voltage_unit == "mV"){
                    pv_node->setVabs(svVoltageMap[tp_node]->v.value * 0.001);
                } else if(this->configManager.us.voltage_unit == "MV"){
                    pv_node->setVabs(svVoltageMap[tp_node]->v.value * 1000000);
                }
            }else if(syn_machine->RegulatingControl != nullptr){
                if(this->configManager.us.voltage_unit == "V"){
                    pv_node->setVabs((syn_machine)->RegulatingControl->targetValue);
                } else if(this->configManager.us.voltage_unit == "kV"){
                    pv_node->setVabs((syn_machine)->RegulatingControl->targetValue * 1000);
                } else if(this->configManager.us.voltage_unit == "mV"){
                    pv_node->setVabs((syn_machine)->RegulatingControl->targetValue * 0.001);
                } else if(this->configManager.us.voltage_unit == "MV"){
                    pv_node->setVabs((syn_machine)->RegulatingControl->targetValue * 1000000);
                }
            }else{
                pv_node->setVabs(pv_node->Vnom());
            }


        }


    }else{

        if(this->configManager.us.enable) {
            if (this->configManager.us.active_power_unit == "W") {
                pv_node->setPgen(generatorMap[syn_machine]->initialP.value);
            } else if (this->configManager.us.active_power_unit == "kW") {
                pv_node->setPgen(generatorMap[syn_machine]->initialP.value * 1000);
            } else if (this->configManager.us.active_power_unit == "mW") {
                pv_node->setPgen(generatorMap[syn_machine]->initialP.value * 0.001);
            } else if (this->configManager.us.active_power_unit == "MW") {
                pv_node->setPgen(generatorMap[syn_machine]->initialP.value * 1000000);
            }
            if(syn_machine->RegulatingControl != nullptr){
                if(this->configManager.us.voltage_unit == "V"){
                    pv_node->setVabs((syn_machine)->RegulatingControl->targetValue);
                } else if(this->configManager.us.voltage_unit == "kV"){
                    pv_node->setVabs((syn_machine)->RegulatingControl->targetValue * 1000);
                } else if(this->configManager.us.voltage_unit == "mV"){
                    pv_node->setVabs((syn_machine)->RegulatingControl->targetValue * 0.001);
                } else if(this->configManager.us.voltage_unit == "MV"){
                    pv_node->setVabs((syn_machine)->RegulatingControl->targetValue * 1000000);
                }
            }else{
                pv_node->setVabs(pv_node->Vnom());
            }
        }

    }

    if(syn_machine->DiagramObjects.begin() == syn_machine->DiagramObjects.end()){
        std::cerr << "Missing Diagram Object for SynchronousMachine: " << syn_machine->name << " Default Position 0,0 \n";
        this->set_exit_code(3);
        pv_node->annotation.placement.transformation.origin.x = 0;
        pv_node->annotation.placement.transformation.origin.y = 0;
        pv_node->annotation.placement.transformation.rotation = 0;

        ctemplate::TemplateDictionary *pv_node_dict = dict->AddIncludeDictionary("PVNODE_DICT");
        pv_node_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/PVNode.tpl");
        pv_node->set_template_values(pv_node_dict);
    }else{
        int counter = 0;
        float currX = 0;
        float currY = 0;
        for (diagram_it = syn_machine->DiagramObjects.begin();
             diagram_it!= syn_machine->DiagramObjects.end();
             ++diagram_it) {            _t_points = this->calculate_average_position();
            currX += _t_points.xPosition;
            currY += _t_points.yPosition;
            counter += 1;

            try{
                pv_node->annotation.placement.transformation.rotation = (*diagram_it)->rotation.value;
            }catch(ReadingUninitializedField* e){
                pv_node->annotation.placement.transformation.rotation = 0;
                this->set_exit_code(3);
                std::cerr <<"Missing rotation for diagram obj" << pv_node->name()<< std::endl;

            }
        }

        pv_node->annotation.placement.transformation.origin.x = currX /counter;
        pv_node->annotation.placement.transformation.origin.y = currY /counter;

        ctemplate::TemplateDictionary *pv_node_dict = dict->AddIncludeDictionary("PVNODE_DICT");
        pv_node_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/PVNode.tpl");
        pv_node->set_template_values(pv_node_dict);

    }

    return pv_node;
}


#ifdef SINERGIEN
Battery CIMObjectHandler::BatteryStorageHandler(const TPNodePtr tp_node, const TerminalPtr terminal, const BatteryStoragePtr battery_storge,
                                                ctemplate::TemplateDictionary* dict){

  Battery battery;

  if (this->configManager.pqload_parameters.type == 0 ){
    battery.set_BatteryType(BatteryType::Type0);
  } else if(this->configManager.pqload_parameters.type == 1){
    battery.set_BatteryType(BatteryType::Type1);
  }
  battery.set_name(name_in_modelica(battery_storge->name));
  battery.set_sequenceNumber(terminal->sequenceNumber);
  battery.set_connected(terminal->connected);
  battery.set_Cnom(battery_storge->capacity.value);

  if (this->configManager.battery_parameters.enable) {
    SET_TRANS_EXTENT(battery,battery);
    battery.annotation.placement.visible = configManager.battery_parameters.annotation.visible;
  }

    if (battery_storge->DiagramObjects.begin() == battery_storge->DiagramObjects.end()) {

        std::cerr << "Missing Diagram Object for BatteryStorage: " << battery_storge->name << " Default Position 0,0 \n";
        battery.annotation.placement.transformation.origin.x = 0;
        battery.annotation.placement.transformation.origin.y = 0;
        battery.annotation.placement.transformation.rotation = 0;

        if (battery.sequenceNumber() == 0 || battery.sequenceNumber() == 1) {
            if (this->configManager.pqload_parameters.type == 0 && battery.BatteryType() == BatteryType::Type0) {
                ctemplate::TemplateDictionary *battery_dict = dict->AddIncludeDictionary("BATTERY_TYPE0_DICT");
                battery_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/BatteryType0.tpl");
                battery.set_template_values(battery_dict);

            } else if (this->configManager.pqload_parameters.type == 1 && battery.BatteryType() == BatteryType::Type1) {
                ctemplate::TemplateDictionary *battery_dict = dict->AddIncludeDictionary("BATTERY_TYPE1_DICT");
                battery_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/BatteryType1.tpl");
                battery.set_template_values(battery_dict);
            }
        }
    }
  for (diagram_it = battery_storge->DiagramObjects.begin();
       diagram_it != battery_storge->DiagramObjects.end();
       ++diagram_it) {

    _t_points = this->calculate_average_position();
    battery.annotation.placement.transformation.origin.x = _t_points.xPosition;
    battery.annotation.placement.transformation.origin.y = _t_points.yPosition;
    battery.annotation.placement.transformation.rotation = (*diagram_it)->rotation.value;

    if (battery.sequenceNumber()==0 || battery.sequenceNumber()==1) {
      if (this->configManager.pqload_parameters.type == 0 && battery.BatteryType() == BatteryType::Type0) {
        ctemplate::TemplateDictionary *battery_dict = dict->AddIncludeDictionary("BATTERY_TYPE0_DICT");
        battery_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/BatteryType0.tpl");
        battery.set_template_values(battery_dict);

      } else if(this->configManager.pqload_parameters.type == 1 && battery.BatteryType() == BatteryType::Type1){
        ctemplate::TemplateDictionary *battery_dict = dict->AddIncludeDictionary("BATTERY_TYPE1_DICT");
        battery_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/BatteryType1.tpl");
        battery.set_template_values(battery_dict);
      }
    }
  }

  return battery;

}
#endif


/**
 * Create Connection
 */
bool CIMObjectHandler::ConnectionHandler(ctemplate::TemplateDictionary *dict) {

    unsigned int size;
    size = connectionQueue.size();

    while (!connectionQueue.empty()) {
        ctemplate::TemplateDictionary *connection_dict = dict->AddIncludeDictionary("CONNECTIONS_DICT");
        connection_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/Connections.tpl");
        if (connectionQueue.front().is_connected()) {
            connection_dict->AddSectionDictionary("CONNECTED_SECTION");
        } else {
            connection_dict->AddSectionDictionary("UNCONNECTED_SECTION");
        }

        connectionQueue.front().draw_connection(connection_dict);

        connectionQueue.pop();
    }

    return true;
}

/**
 *  every component from NEPLAN has two position
 *  calculate the average position
 *  td::list<DiagramObjectPtr>::iterator diagram_it is class member!
 */
DiagramObjectPoint CIMObjectHandler::calculate_average_position() {
    DiagramObjectPoint t_points;
    t_points.xPosition = 0;
    t_points.yPosition = 0;

    std::list<DiagramObjectPointPtr>::iterator points_it;
    for (points_it = (*diagram_it)->DiagramObjectPoints.begin();
         points_it!= (*diagram_it)->DiagramObjectPoints.end();
         ++points_it) {
        t_points.xPosition = (*points_it)->xPosition + t_points.xPosition;
        t_points.yPosition = (*points_it)->yPosition + t_points.yPosition;
    }


    std::size_t size = (*diagram_it)->DiagramObjectPoints.size();
    t_points = convert_coordinate(t_points.xPosition/size, t_points.yPosition/size, this->configManager);
    return t_points;
}

/**
 * convert the coordinate system between different software
 */
DiagramObjectPoint CIMObjectHandler::convert_coordinate(double x, double y, const ConfigManager &configManager) {

    double trans_para[4] = {1, 0, -1, 0};
    if (configManager.ss.enable) {
        for (int i = 0; i < 4; ++i)
            trans_para[i] = configManager.ss.topology_trans_parameter[i];
    }
    DiagramObjectPoint t_points;
    t_points.xPosition = trans_para[0]*x + trans_para[1];
    t_points.yPosition = trans_para[2]*y + trans_para[3];
    return t_points;
}

/**
 * convert name adapt to the format in modelica
 */
std::string CIMObjectHandler::name_in_modelica(std::string original_name) {
    std::string t_name = "CIM_" + original_name; ///some names illegal in modelica!
    for (std::string::iterator it = t_name.begin(); it!=t_name.end(); ++it) {
        if ((*it==' ') || (*it=='-') || (*it=='.')) {
            *it = '_';
        }
    }

    return t_name;
}
