/*
 * CIMObjectHandler.cpp
 *
 */

#include "CIMObjectHandler.h"
#include "ModelicaWorkshop/ModPowerSystems/Connection.h"

/**\brief Macro for transformation.extent setting
 */
#define  SET_TRANS_EXTENT(component, type_str)                                                  \
                      component.annotation.placement.transformation.extent.first.x =            \
                      configManager.type_str##_parameters.annotation.transformation_extent[0];  \
                      component.annotation.placement.transformation.extent.first.y =            \
                      configManager.type_str##_parameters.annotation.transformation_extent[1];  \
                      component.annotation.placement.transformation.extent.second.x =           \
                      configManager.type_str##_parameters.annotation.transformation_extent[2];  \
                      component.annotation.placement.transformation.extent.second.y =           \
                      configManager.type_str##_parameters.annotation.transformation_extent[3];  \

/**\brief Macro for NEPLAN Voltage unit fix
 */
#define FIX_NEPLAN_VOLTAGE(component)                                                           \
                    if(this->configManager.us.voltage_unit == "V"){                             \
                    component.set_Vnom(component.Vnom());                                       \
                    } else if (this->configManager.us.voltage_unit == "kV") {                   \
                    component.set_Vnom(component.Vnom()*1000);                                  \
                    } else if(this->configManager.us.voltage_unit == "mV") {                    \
                    component.set_Vnom(component.Vnom()*0.001);                                 \
                    } else if(this->configManager.us.voltage_unit == "MV"){                     \
                    component.set_Vnom(component.Vnom()*1000000);                               \
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

/**
 * frist searching loop
 * to find I_max of ACLineSegment, SvPowerFlow of Terminal for PQLoad
 * using hashmap
 */
bool CIMObjectHandler::pre_process() {
  ///pre searching loop
  if(this->configManager.gs.apply_Neplan_fix == true){
      ///find OperationLimitSet for AClineSegment, stored in hashmap
      for (BaseClass *Object : this->_CIMObjects) {
          if (auto *op_limitset = dynamic_cast<OpLimitSetPtr>(Object)) {
              if (auto *ac_line = dynamic_cast<AcLinePtr>(op_limitset->Equipment)) {
                  OpLimitMap.insert({ac_line, op_limitset}); //hashmap
              }
          }
      }
  }
    if(this->configManager.svSettings.useSVforEnergyConsumer == true
       or this->configManager.svSettings.useSVforGeneratingUnit == true
       or this->configManager.svSettings.useSVforExternalNetworkInjection == true  ){
        for (BaseClass *Object : this->_CIMObjects) {
            ///find terminal's svPowerFlow
            if (auto *sv_powerflow = dynamic_cast<SVPowerFlowPtr>(Object)) {
                svPowerFlowMap.insert({sv_powerflow->Terminal,sv_powerflow}); //hashmap
            }else if ( auto *sv_voltage = dynamic_cast<SVVoltagePtr>(Object)){
                svVoltageMap.insert({sv_voltage->TopologicalNode, sv_voltage});
            }
        }
  }
  return true;
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

  ///frist searching loop, to find I_max of ACLineSegment, SvPowerFlow of Terminal for PQLoad
  this->pre_process();

  ///main searching loop
  for (BaseClass *Object : this->_CIMObjects) {


    if (auto *tp_node = dynamic_cast<TPNodePtr>(Object)) {

      BusBar busbar = this->TopologicalNodeHandler(tp_node, dict);

      if (this->configManager.household_parameters.use_households == true ) {
        this->HouseholdComponetsHandler(tp_node, dict);
      }

      std::list<TerminalPtr>::iterator terminal_it;

      for (terminal_it = tp_node->Terminal.begin(); terminal_it!=tp_node->Terminal.end(); ++terminal_it) {

        //ConnectivityNode no use for NEPLAN
        if (auto *connectivity_node = dynamic_cast<ConnectivityNodePtr>((*terminal_it)->ConnectivityNode)) {

          ConnectivityNode connectivity_Node = this->ConnectivityNodeHandler(tp_node, (*terminal_it),
                                                                            connectivity_node, dict);
          Connection conn(&busbar, &connectivity_Node);
          connectionQueue.push(conn);
        }

        if (auto *externalNI = dynamic_cast<ExNIPtr>((*terminal_it)->ConductingEquipment)) {
          Slack slack = this->ExternalNIHandler(tp_node, (*terminal_it), externalNI, dict);
          Connection conn(&busbar, &slack);
          connectionQueue.push(conn);

        } else if (auto *power_trafo = dynamic_cast<PowerTrafoPtr>((*terminal_it)->ConductingEquipment)) {
          Transformer trafo = this->PowerTransformerHandler(tp_node, (*terminal_it), power_trafo, dict);
          Connection conn(&busbar, &trafo);
          connectionQueue.push(conn);

        } else if (auto *ac_line = dynamic_cast<AcLinePtr>((*terminal_it)->ConductingEquipment)) {
         
          if(template_folder == "DistAIX_templates"){
            /* Changed implementation to enable creation of lossy cables for DistAIX format.
            * Instead of creating "connections", the name of the busbar is stored when visited for the first time.
            * When visiting the pi_line for the second time, the name of the current busbar, as well as the name of the busbbar
            * stored during the first visit are passed as optional arguments to the ACLineSegmentHandler.
            * This handler was modified in such a way, that those additional arguments are stores as dictionary values
            * used in the DistAIX templates.
            */

            auto searchIt = piLineIdMap.find(ac_line);
            if(searchIt != piLineIdMap.end()) {
            
              PiLine pi_line = this->ACLineSegmentHandler(tp_node, (*terminal_it), ac_line, dict, piLineIdMap[ac_line], busbar.name());

            }
            else {

              piLineIdMap[ac_line] = busbar.name();
              
            }
          }
          else {
            PiLine pi_line = this->ACLineSegmentHandler(tp_node, (*terminal_it), ac_line, dict);
            Connection conn(&busbar, &pi_line);
            connectionQueue.push(conn);
          }
          
        } else if (auto *energy_consumer = dynamic_cast<EnergyConsumerPtr>((*terminal_it)->ConductingEquipment)) {

          if (this->configManager.household_parameters.use_households == false ) {
            PQLoad pqload = this->EnergyConsumerHandler(tp_node, (*terminal_it), energy_consumer, dict);
            Connection conn(&busbar, &pqload);
            connectionQueue.push(conn);
          }

        } else if (auto *synchronous_machine = dynamic_cast<SynMachinePtr >((*terminal_it)->ConductingEquipment)) {
            for (BaseClass *Object : this->_CIMObjects) {

                ///TopologicalNode, convert to BusBar
                if(auto *generatingUnit= dynamic_cast<GeneratingUnitPtr >(Object)){
                    for(rotatingMachine_it = generatingUnit->RotatingMachine.begin();
                        rotatingMachine_it!= generatingUnit->RotatingMachine.end();
                        ++rotatingMachine_it){
                        if((*rotatingMachine_it) == synchronous_machine){
                            if (this->configManager.household_parameters.use_households == false ) {
                                PVNode pv_node= this->GeneratingUnitHandler(tp_node, (*terminal_it),
                                                                            generatingUnit, dict);
                                Connection conn(&busbar, &pv_node);
                                connectionQueue.push(conn);
                            }
                        }
                    }
                }


          }
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

          Connection conn(&busbar, &this->householdQueue.front());
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
          Connection conn(&busbar, &pqloadQueue.front());
          connectionQueue.push(conn);
          pqloadQueue.pop();
        }
        while (!this->solarGeneratorQueue.empty()) {

          ctemplate::TemplateDictionary *solar_generator_dict = dict->AddIncludeDictionary(
              "SOLARGENERATOR_DICT");
          solar_generator_dict->SetFilename(
              this->configManager.ts.directory_path + "resource/" + template_folder + "/SolarGenerator.tpl");
          solarGeneratorQueue.front().set_template_values(solar_generator_dict);
          Connection conn(&busbar, &solarGeneratorQueue.front());
          connectionQueue.push(conn);
          solarGeneratorQueue.pop();
        }
          while (!this->pvNodeQueue.empty()) {

              ctemplate::TemplateDictionary *pv_node_dict = dict->AddIncludeDictionary(
                      "PVNODE_DICT");
              pv_node_dict->SetFilename(
                      this->configManager.ts.directory_path + "resource/" + template_folder + "/PVNode.tpl");
              pvNodeQueue.front().set_template_values(pv_node_dict);
              Connection conn(&busbar, &pvNodeQueue.front());
              connectionQueue.push(conn);
              pvNodeQueue.pop();
          }
      }
    }
  }
    std::cout << "before connection handle "<< std::endl;
  this->ConnectionHandler(dict);
    std::cout << "after connection handle "<< std::endl;
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
BusBar CIMObjectHandler::TopologicalNodeHandler(const TPNodePtr tp_node, ctemplate::TemplateDictionary *dict) {
  BusBar busbar;
  busbar.set_name(name_in_modelica(tp_node->name));
  busbar.annotation.placement.visible = true;
  busbar.set_Vnom(tp_node->BaseVoltage->nominalVoltage.value);

  if(this->configManager.us.enable){
    FIX_NEPLAN_VOLTAGE(busbar);
  }

  if (this->configManager.busbar_parameters.enable) {
    SET_TRANS_EXTENT(busbar,busbar);//Macro
    busbar.annotation.placement.visible = configManager.busbar_parameters.annotation.visible;
  }
  busbar.set_Vnom_displayUnit(busbar.Vnom_displayUnit());
  // std::list<DiagramObjectPtr>::iterator diagram_it is class member!
    if (tp_node->DiagramObjects.begin() == tp_node->DiagramObjects.end()){
        std::cerr << "Missing Diagram Object for TpNode:  " << tp_node->name << " Default Position 0,0 \n";

        busbar.annotation.placement.transformation.origin.x = 0;
        busbar.annotation.placement.transformation.origin.y = 0;
        busbar.annotation.placement.transformation.rotation = 0;

        ctemplate::TemplateDictionary *busbar_dict = dict->AddIncludeDictionary("BUSBAR_DICT");
        busbar_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/BusBar.tpl");
        busbar.set_template_values(busbar_dict);
    }
  for (diagram_it = tp_node->DiagramObjects.begin(); diagram_it!=tp_node->DiagramObjects.end(); ++diagram_it) {
    _t_points = this->calculate_average_position();
    busbar.annotation.placement.transformation.origin.x = _t_points.xPosition;
    busbar.annotation.placement.transformation.origin.y = _t_points.yPosition;
    busbar.annotation.placement.transformation.rotation = (*diagram_it)->rotation.value;

    ctemplate::TemplateDictionary *busbar_dict = dict->AddIncludeDictionary("BUSBAR_DICT");
    busbar_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/BusBar.tpl");
    busbar.set_template_values(busbar_dict);
  }

  //BusBarSection used in Cimphony
//  std::list<TerminalPtr>::iterator terminal_it;
//  for (terminal_it = tp_node->Terminal.begin(); terminal_it!=tp_node->Terminal.end(); ++terminal_it) {
//    if (auto *busbar_section = dynamic_cast<BusBarSectionPtr>((*terminal_it)->ConductingEquipment)) {
//      this->BusBarSectionHandler(busbar_section, busbar, dict);
//    }
//  }

  return busbar;
}

/**
 * In the TopologicalNode to
 * find PQLoad in type1
 * find PQLoad, SolarGenerator, Battery which form HouseHold type2
 */
bool CIMObjectHandler::HouseholdComponetsHandler(const TPNodePtr tp_node, ctemplate::TemplateDictionary *dict) {

  std::list<TerminalPtr>::iterator terminal_it;
  if(this->configManager.household_parameters.type == "type1" ){

    for (terminal_it = tp_node->Terminal.begin(); terminal_it != tp_node->Terminal.end(); ++terminal_it) {

      if (auto *energy_consumer = dynamic_cast<EnergyConsumerPtr>((*terminal_it)->ConductingEquipment)) {

        PQLoad pqload = this->EnergyConsumerHandler(tp_node, (*terminal_it), energy_consumer, dict);
        Household household(pqload);
        if (this->configManager.household_parameters.enable) {
          SET_TRANS_EXTENT(household,household);
          household.annotation.placement.visible = configManager.household_parameters.annotation.visible;
        }

        this->householdQueue.push(household);
      }
    }
  } else if (this->configManager.household_parameters.type == "type2"){
    for (terminal_it = tp_node->Terminal.begin(); terminal_it != tp_node->Terminal.end(); ++terminal_it) {

      if (auto *energy_consumer = dynamic_cast<EnergyConsumerPtr>((*terminal_it)->ConductingEquipment)) {
        PQLoad pqload = this->EnergyConsumerHandler(tp_node, (*terminal_it), energy_consumer, dict);
        this->pqloadQueue.push(pqload);
      }else if (auto *synchronous_machine = dynamic_cast<SynMachinePtr >((*terminal_it)->ConductingEquipment)) {
          for (BaseClass *Object : this->_CIMObjects) {

              ///TopologicalNode, convert to BusBar
              if (auto *generatingUnit = dynamic_cast<GeneratingUnitPtr >(Object)) {
                  for (rotatingMachine_it = generatingUnit->RotatingMachine.begin();
                       rotatingMachine_it != generatingUnit->RotatingMachine.end();
                       ++rotatingMachine_it) {
                      if ((*rotatingMachine_it) == synchronous_machine) {
                          if (this->configManager.household_parameters.use_households == false) {
                              PVNode pv_node = this->GeneratingUnitHandler(tp_node, (*terminal_it),
                                                                           generatingUnit, dict);
                              this->pvNodeQueue.push(pv_node);

                          }
                      }
                  }
              }
          }
      }


      if (this->pqloadQueue.size()==1 && this->solarGeneratorQueue.size()==1) {

        Household household(this->pqloadQueue.front(), this->solarGeneratorQueue.front());  //type2

        if (this->configManager.household_parameters.enable) {
          SET_TRANS_EXTENT(household,household);
          household.annotation.placement.visible = configManager.household_parameters.annotation.visible;
        }

        this->householdQueue.push(household);
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
  }

  for (diagram_it = busbar_section->DiagramObjects.begin();
       diagram_it!=busbar_section->DiagramObjects.end();
       ++diagram_it) {
    _t_points = this->calculate_average_position();

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
 */
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

/**
 * ConductingEquipment of Terminal
 * ConductingEquipment cast to ExternalNetworkInjection
 * Convert to slack in Modelica
 */
Slack CIMObjectHandler::ExternalNIHandler(const TPNodePtr tp_node, const TerminalPtr terminal, const ExNIPtr externalNI,
                                          ctemplate::TemplateDictionary *dict) {
  Slack slack;

  slack.set_name(name_in_modelica(externalNI->name));
  slack.set_sequenceNumber(terminal->sequenceNumber);
  slack.set_connected(terminal->connected);
  slack.annotation.placement.visible = true;

  slack.set_Vnom(tp_node->BaseVoltage->nominalVoltage.value);
    if(this->configManager.svSettings.useSVforEnergyConsumer == true && svVoltageMap[tp_node]){
        slack.set_phiV(svVoltageMap[tp_node]->angle.value);
    }


  if(this->configManager.us.enable){
    FIX_NEPLAN_VOLTAGE(slack);
  }

  if (this->configManager.slack_parameters.enable) {
    SET_TRANS_EXTENT(slack,slack);
    slack.annotation.placement.visible = configManager.slack_parameters.annotation.visible;
  }
  if (externalNI->DiagramObjects.begin() == externalNI->DiagramObjects.end()){
      std::cerr << "Missing Diagram Object for ExternalNIHandler: " << externalNI->name << " Default Position 0,0 \n";
      slack.annotation.placement.transformation.origin.x = 0;
      slack.annotation.placement.transformation.origin.y = 0;
      slack.annotation.placement.transformation.rotation = 0;

      if (slack.sequenceNumber()==0 || slack.sequenceNumber()==1) {
          ctemplate::TemplateDictionary *slack_dict = dict->AddIncludeDictionary("SLACK_DICT");
          slack_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/Slack.tpl");
          slack.set_template_values(slack_dict);
      }
  }

  for (diagram_it = externalNI->DiagramObjects.begin(); diagram_it!=externalNI->DiagramObjects.end(); ++diagram_it) {

    _t_points = this->calculate_average_position();
    slack.annotation.placement.transformation.origin.x = _t_points.xPosition;
    slack.annotation.placement.transformation.origin.y = _t_points.yPosition;
    slack.annotation.placement.transformation.rotation = (*diagram_it)->rotation.value - 90;

    if (slack.sequenceNumber()==0 || slack.sequenceNumber()==1) {
      ctemplate::TemplateDictionary *slack_dict = dict->AddIncludeDictionary("SLACK_DICT");
      slack_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/Slack.tpl");
      slack.set_template_values(slack_dict);
    }
  }

  return slack;
}

/**
 * ConductingEquipment of Terminal
 * ConductingEquipment cast to ACLineSegment
 * Convert to Pi_line in Modelica
 */
PiLine
CIMObjectHandler::ACLineSegmentHandler(const TPNodePtr tp_node, const TerminalPtr terminal, const AcLinePtr ac_line,
                                       ctemplate::TemplateDictionary *dict, std::string node1Name /* = "" */, std::string node2Name /* = "" */) {
  PiLine piline;
  piline.set_name(name_in_modelica(ac_line->name));
  piline.set_length(ac_line->length.value);
  piline.set_r(ac_line->r.value/ac_line->length.value);
  piline.set_x(ac_line->x.value/ac_line->length.value);
  piline.set_b(ac_line->bch.value/ac_line->length.value);
  piline.set_g(ac_line->gch.value/ac_line->length.value);

  if (this->configManager.gs.create_distaix_format == true && !node1Name.empty() && !node2Name.empty()) {
    piline.set_node1(node1Name);
    piline.set_node2(node2Name);
  }

  //find I_Max
  if(OpLimitMap[ac_line]){
    for(OpLimitPtr op_limit: OpLimitMap[ac_line]->OperationalLimitValue){
      if(auto current_limit = dynamic_cast<CurrentLimitPtr>(op_limit)){
        if(current_limit->name == "Normal")
          piline.set_Imax(current_limit->value.value);
      }
    }
  }
  if(this->configManager.us.enable){
    if(this->configManager.us.current_unit == "A"){
      piline.set_Imax(piline.Imax());
    } else if(this->configManager.us.current_unit == "kA"){
        piline.set_Imax(piline.Imax()*1000);
    } else if(this->configManager.us.current_unit == "mA"){
      piline.set_Imax(piline.Imax()*0.001);
    } else if(this->configManager.us.current_unit == "MA"){
      piline.set_Imax(piline.Imax()*1000000);
    }
  }

  piline.set_sequenceNumber(terminal->sequenceNumber);
  piline.set_connected(terminal->connected);
  piline.annotation.placement.visible = true;

  if (this->configManager.piline_parameters.enable) {

    SET_TRANS_EXTENT(piline,piline);
    piline.annotation.placement.visible = configManager.piline_parameters.annotation.visible;
  }

  if (ac_line->DiagramObjects.begin() == ac_line->DiagramObjects.end()){
      std::cerr << "Missing Diagram Object for acLine: " << ac_line->name << " Default Position 0,0 \n";
      piline.annotation.placement.transformation.origin.x = 0;
      piline.annotation.placement.transformation.origin.y = 0;
      piline.annotation.placement.transformation.rotation = 0;

      if (piline.sequenceNumber()==0 || piline.sequenceNumber()==1) {
          ctemplate::TemplateDictionary *piLine_dict = dict->AddIncludeDictionary("PILINE_DICT");
          piLine_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/PiLine.tpl");
          piline.set_template_values(piLine_dict);
      }
  }

  for (diagram_it = ac_line->DiagramObjects.begin(); diagram_it!=ac_line->DiagramObjects.end(); ++diagram_it) {

    _t_points = this->calculate_average_position();
    piline.annotation.placement.transformation.origin.x = _t_points.xPosition;
    piline.annotation.placement.transformation.origin.y = _t_points.yPosition;
    piline.annotation.placement.transformation.rotation = (*diagram_it)->rotation.value - 90;

    if (piline.sequenceNumber()==0 || piline.sequenceNumber()==1 || (template_folder == "DistAIX_templates" && piline.sequenceNumber() == 2) /* last term needed */) {
      ctemplate::TemplateDictionary *piLine_dict = dict->AddIncludeDictionary("PILINE_DICT");
      piLine_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/PiLine.tpl");
      piline.set_template_values(piLine_dict);
    }
  }

  return piline;
}

/**
 * ConductingEquipment of Terminal
 * ConductingEquipment cast to PowerTransformer
 * Convert to Transformer in Modelica
 */
Transformer CIMObjectHandler::PowerTransformerHandler(const TPNodePtr tp_node, const TerminalPtr terminal,
                                                      const PowerTrafoPtr power_trafo,
                                                      ctemplate::TemplateDictionary *dict) {

  Transformer trafo;
  trafo.set_name(name_in_modelica(power_trafo->name));
  trafo.set_sequenceNumber(terminal->sequenceNumber);
  trafo.set_connected(terminal->connected);
  trafo.annotation.placement.visible = true;

  std::list<PowerTransformerEndPtr>::iterator transformer_end_it;
  for (transformer_end_it = power_trafo->PowerTransformerEnd.begin();
       transformer_end_it!=power_trafo->PowerTransformerEnd.end();
       ++transformer_end_it) {
    if ((*transformer_end_it)->endNumber==1) {

      trafo.set_Sr((*transformer_end_it)->ratedS.value*1000000); // Lukas FIXME TODO: Hier muss wohl configManager.us.active_power_unit ausgewertet werden!
      trafo.set_r((*transformer_end_it)->r.value);
      trafo.set_x((*transformer_end_it)->x.value);
      trafo.set_b((*transformer_end_it)->b.value);

      trafo.set_tap_pos( ((*transformer_end_it)->RatioTapChanger->step - 1) * 1000);

      if(this->configManager.us.enable) {
        if (this->configManager.us.voltage_unit == "V") {
          trafo.set_Vnom1((*transformer_end_it)->ratedU.value);
        } else if (this->configManager.us.voltage_unit == "kV") {
          trafo.set_Vnom1((*transformer_end_it)->ratedU.value*1000);
        } else if (this->configManager.us.voltage_unit == "mV") {
          trafo.set_Vnom1((*transformer_end_it)->ratedU.value*0.001);
        } else if (this->configManager.us.voltage_unit == "MV") {
          trafo.set_Vnom1((*transformer_end_it)->ratedU.value*1000000);
        }
      }

      trafo.calc_URr();
      trafo.calc_Ukr();
      
      /*
      using namespace std;
      cerr << "DEBUG: trafo._Sr = " << trafo.Sr() << endl;
      cerr << "DEBUG: trafo._r = " << trafo.r() << endl;
      cerr << "DEBUG: trafo._x = " << trafo.x() << endl;
      cerr << "DEBUG: trafo._z = " << trafo.z() << endl;
      cerr << "DEBUG: trafo._Vnom1 = " << trafo.Vnom1() << endl;
      cerr << "DEBUG: trafo._URr = " << trafo.URr() << endl;
      cerr << "DEBUG: trafo._Ukr = " << trafo.Ukr() << endl;
      */
    
    } else if ((*transformer_end_it)->endNumber==2) {

      if(this->configManager.us.enable) {
        if (this->configManager.us.voltage_unit == "V") {
          trafo.set_Vnom2((*transformer_end_it)->ratedU.value);
        } else if (this->configManager.us.voltage_unit == "kV") {
          trafo.set_Vnom2((*transformer_end_it)->ratedU.value*1000);
        } else if (this->configManager.us.voltage_unit == "mV") {
          trafo.set_Vnom2((*transformer_end_it)->ratedU.value*0.001);
        } else if (this->configManager.us.voltage_unit == "MV") {
          trafo.set_Vnom2((*transformer_end_it)->ratedU.value*1000000);
        }
      }
    }
  }

  if (this->configManager.trafo_parameters.enable) {

    SET_TRANS_EXTENT(trafo,trafo);
    trafo.annotation.placement.visible = configManager.trafo_parameters.annotation.visible;
  }

  if(power_trafo->DiagramObjects.begin() == power_trafo->DiagramObjects.end()){
      std::cerr << "Missing Diagram Object for PowerTrafo: " << power_trafo->name << " Default Position 0,0 \n";
      trafo.annotation.placement.transformation.origin.x = 0;
      trafo.annotation.placement.transformation.origin.y = 0;
      trafo.annotation.placement.transformation.rotation = 0;

      if (trafo.sequenceNumber()==0 || trafo.sequenceNumber()==1) {
          ctemplate::TemplateDictionary *powerTrafo_dict = dict->AddIncludeDictionary("TRANSFORMER_DICT");
          powerTrafo_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/Transformer.tpl");
          trafo.set_template_values(powerTrafo_dict);
      }
  }

  for (diagram_it = power_trafo->DiagramObjects.begin();
       diagram_it!=power_trafo->DiagramObjects.end();
       ++diagram_it) {

    _t_points = this->calculate_average_position();
    trafo.annotation.placement.transformation.origin.x = _t_points.xPosition;
    trafo.annotation.placement.transformation.origin.y = _t_points.yPosition;
    trafo.annotation.placement.transformation.rotation = (*diagram_it)->rotation.value - 90;

    if (trafo.sequenceNumber()==0 || trafo.sequenceNumber()==1) {
      ctemplate::TemplateDictionary *powerTrafo_dict = dict->AddIncludeDictionary("TRANSFORMER_DICT");
      powerTrafo_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/Transformer.tpl");
      trafo.set_template_values(powerTrafo_dict);
    }
  }

  return trafo;
}

/**
 * ConductingEquipment of Terminal
 * ConductingEquipment cast to energy_consumer
 * Convert to pqload in Modelica
 */
PQLoad CIMObjectHandler::EnergyConsumerHandler(const TPNodePtr tp_node, const TerminalPtr terminal,
                                               const EnergyConsumerPtr energy_consumer,
                                               ctemplate::TemplateDictionary *dict) {

  PQLoad pqload;

  if (this->configManager.pqload_parameters.type == 1 ) {

    pqload.set_PQLoadType(PQLoadType::Standard);

  } else if(this->configManager.pqload_parameters.type == 2){

      pqload.set_PQLoadType(PQLoadType::Profile);

  } else if(this->configManager.pqload_parameters.type == 3){

    pqload.set_PQLoadType(PQLoadType::NormProfile);
  }

  if(this->configManager.svSettings.useSVforEnergyConsumer == true && svPowerFlowMap[terminal]){
    pqload.set_Pnom(svPowerFlowMap[terminal]->p.value);
    pqload.set_Qnom(svPowerFlowMap[terminal]->q.value);
  }else{
      pqload.set_Pnom(energy_consumer->p.value);
      pqload.set_Qnom(energy_consumer->q.value);
  }

  pqload.set_name(name_in_modelica(energy_consumer->name));
  pqload.set_Vnom(tp_node->BaseVoltage->nominalVoltage.value);
  if(this->configManager.us.enable){
    FIX_NEPLAN_VOLTAGE(pqload);

    if(this->configManager.us.active_power_unit == "W"){
      pqload.set_Pnom(pqload.Pnom());
    } else if(this->configManager.us.active_power_unit == "kW"){
      pqload.set_Pnom(pqload.Pnom()*1000);
    } else if(this->configManager.us.active_power_unit == "mW"){
      pqload.set_Pnom(pqload.Pnom()*0.001);
    } else if(this->configManager.us.active_power_unit == "MW"){
      pqload.set_Pnom(pqload.Pnom()*1000000);
    }

    if(this->configManager.us.reactive_power_unit == "var"){
      pqload.set_Qnom(pqload.Qnom());
    } else if(this->configManager.us.reactive_power_unit == "kvar"){
      pqload.set_Qnom(pqload.Qnom()*1000);
    } else if(this->configManager.us.reactive_power_unit == "mvar"){
      pqload.set_Qnom(pqload.Qnom()*0.001);
    } else if(this->configManager.us.reactive_power_unit == "Mvar"){
      pqload.set_Qnom(pqload.Qnom()*1000000);
    }

  }

  pqload.set_name(name_in_modelica(energy_consumer->name));
  pqload.set_sequenceNumber(terminal->sequenceNumber);
  pqload.set_connected(terminal->connected);
  pqload.annotation.placement.visible = true;

  if (this->configManager.pqload_parameters.enable) {

    SET_TRANS_EXTENT(pqload,pqload);
    pqload.annotation.placement.visible = configManager.pqload_parameters.annotation.visible;
    pqload.set_profileName(configManager.pqload_parameters.profile_name);
    pqload.set_profileFileName(configManager.pqload_parameters.profile_filename);
  }

  if(energy_consumer->DiagramObjects.begin() == energy_consumer->DiagramObjects.end()){
      std::cerr << "Missing Diagram Object for EnergyConsumer: " << energy_consumer->name << " Default Position 0,0 \n";
      pqload.annotation.placement.transformation.origin.x = 0;
      pqload.annotation.placement.transformation.origin.y = 0;
      pqload.annotation.placement.transformation.rotation = 0;

      if(this->configManager.household_parameters.use_households == false){
          if (pqload.sequenceNumber() == 0 || pqload.sequenceNumber() == 1) {

              if (this->configManager.pqload_parameters.type == 1 && pqload.PQLoadType() == PQLoadType::Standard) {
                  ctemplate::TemplateDictionary *pqLoad_dict = dict->AddIncludeDictionary("PQLOAD_DICT");
                  pqLoad_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/PQLoad.tpl");
                  pqload.set_template_values(pqLoad_dict);

              } else if(this->configManager.pqload_parameters.type == 2 && pqload.PQLoadType() == PQLoadType::Profile){
                  ctemplate::TemplateDictionary *pqLoad_dict = dict->AddIncludeDictionary("PQLOAD_PROFILE_DICT");
                  pqLoad_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/PQLoadProfile.tpl");
                  pqload.set_template_values(pqLoad_dict);

              } else if(this->configManager.pqload_parameters.type == 3 && pqload.PQLoadType() == PQLoadType::NormProfile){
                  ctemplate::TemplateDictionary *pqLoad_dict = dict->AddIncludeDictionary("PQLOAD_NORM_PROFILE_DICT");
                  pqLoad_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/PQLoadNormProfile.tpl");
                  pqload.set_template_values(pqLoad_dict);
              }
          }
      }
  }

  for (diagram_it = energy_consumer->DiagramObjects.begin(); diagram_it!=energy_consumer->DiagramObjects.end();
           ++diagram_it) {

    _t_points = this->calculate_average_position();
    pqload.annotation.placement.transformation.origin.x = _t_points.xPosition;
    pqload.annotation.placement.transformation.origin.y = _t_points.yPosition;
    pqload.annotation.placement.transformation.rotation = (*diagram_it)->rotation.value;

    if(this->configManager.household_parameters.use_households == false){
      if (pqload.sequenceNumber() == 0 || pqload.sequenceNumber() == 1) {

        if (this->configManager.pqload_parameters.type == 1 && pqload.PQLoadType() == PQLoadType::Standard) {
          ctemplate::TemplateDictionary *pqLoad_dict = dict->AddIncludeDictionary("PQLOAD_DICT");
          pqLoad_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/PQLoad.tpl");
          pqload.set_template_values(pqLoad_dict);

        } else if(this->configManager.pqload_parameters.type == 2 && pqload.PQLoadType() == PQLoadType::Profile){
          ctemplate::TemplateDictionary *pqLoad_dict = dict->AddIncludeDictionary("PQLOAD_PROFILE_DICT");
          pqLoad_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/PQLoadProfile.tpl");
          pqload.set_template_values(pqLoad_dict);

        } else if(this->configManager.pqload_parameters.type == 3 && pqload.PQLoadType() == PQLoadType::NormProfile){
          ctemplate::TemplateDictionary *pqLoad_dict = dict->AddIncludeDictionary("PQLOAD_NORM_PROFILE_DICT");
          pqLoad_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/PQLoadNormProfile.tpl");
          pqload.set_template_values(pqLoad_dict);
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
SolarGenerator CIMObjectHandler::SynchronousMachineHandlerType2(const TPNodePtr tp_node, const TerminalPtr terminal,
                                                                const SynMachinePtr syn_machine,
                                                                ctemplate::TemplateDictionary *dict) {
  SolarGenerator solar_generator;

  solar_generator.set_name(name_in_modelica(syn_machine->name));
  solar_generator.annotation.placement.visible = true;
  solar_generator.set_connected(terminal->connected);
  solar_generator.set_sequenceNumber(terminal->sequenceNumber);

  if (this->configManager.solar_gen_parameters.enable) {
    SET_TRANS_EXTENT(solar_generator,solar_gen);
    solar_generator.annotation.placement.visible = configManager.solar_gen_parameters.annotation.visible;
  }
  if(syn_machine->DiagramObjects.begin() == syn_machine->DiagramObjects.end()){
      std::cerr << "Missing Diagram Object for SyncronousMachine2: " << syn_machine->name << " Default Position 0,0 \n";
      solar_generator.annotation.placement.transformation.origin.x = 0;
      solar_generator.annotation.placement.transformation.origin.y = 0;
      solar_generator.annotation.placement.transformation.rotation = 0;

      if (this->configManager.solar_gen_parameters.enable) {
          if (this->configManager.household_parameters.use_households == false) {

              if (solar_generator.sequenceNumber()==0 || solar_generator.sequenceNumber()==1) {
                  ctemplate::TemplateDictionary *solar_generator_dict = dict->AddIncludeDictionary(
                          "SOLARGENERATOR_DICT");
                  solar_generator_dict->SetFilename(
                          this->configManager.ts.directory_path + "resource/" + template_folder + "/SolarGenerator.tpl");
                  solar_generator.set_template_values(solar_generator_dict);
              }
          }
      }
  }
  for (diagram_it = syn_machine->DiagramObjects.begin();
       diagram_it!=syn_machine->DiagramObjects.end();
       ++diagram_it) {
    _t_points = this->calculate_average_position();
    solar_generator.annotation.placement.transformation.origin.x = _t_points.xPosition;
    solar_generator.annotation.placement.transformation.origin.y = _t_points.yPosition;
    solar_generator.annotation.placement.transformation.rotation = (*diagram_it)->rotation.value;

    if (this->configManager.solar_gen_parameters.enable) {
      if (this->configManager.household_parameters.use_households == false) {

        if (solar_generator.sequenceNumber()==0 || solar_generator.sequenceNumber()==1) {
          ctemplate::TemplateDictionary *solar_generator_dict = dict->AddIncludeDictionary(
              "SOLARGENERATOR_DICT");
          solar_generator_dict->SetFilename(
              this->configManager.ts.directory_path + "resource/" + template_folder + "/SolarGenerator.tpl");
          solar_generator.set_template_values(solar_generator_dict);
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
WindGenerator CIMObjectHandler::SynchronousMachineHandlerType1(const TPNodePtr tp_node, const TerminalPtr terminal,
                                                               const SynMachinePtr syn_machine,
                                                               ctemplate::TemplateDictionary *dict) {
    WindGenerator wind_generator;

    wind_generator.set_name(name_in_modelica(syn_machine->name));
    wind_generator.set_sequenceNumber(terminal->sequenceNumber);
    wind_generator.set_connected(terminal->connected);
    wind_generator.annotation.placement.visible = true;

    if (this->configManager.wind_gen_parameters.enable) {
        SET_TRANS_EXTENT(wind_generator,wind_gen);
        wind_generator.annotation.placement.visible = configManager.wind_gen_parameters.annotation.visible;
    }

    if(syn_machine->DiagramObjects.begin() == syn_machine->DiagramObjects.end()){
        std::cerr << "Missing Diagram Object for SynchronousMachine: " << syn_machine->name << " Default Position 0,0 \n";
        wind_generator.annotation.placement.transformation.origin.x = 0;
        wind_generator.annotation.placement.transformation.origin.y = 0;
        wind_generator.annotation.placement.transformation.rotation = 0;

        if (wind_generator.sequenceNumber()==0 || wind_generator.sequenceNumber()==1) {
            ctemplate::TemplateDictionary *wind_generator_dict = dict->AddIncludeDictionary("WINDGENERATOR_DICT");
            wind_generator_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/WindGenerator.tpl");
            wind_generator.set_template_values(wind_generator_dict);
        }
    }

    for (diagram_it = syn_machine->DiagramObjects.begin();
         diagram_it!=syn_machine->DiagramObjects.end();
         ++diagram_it) {
        _t_points = this->calculate_average_position();
        wind_generator.annotation.placement.transformation.origin.x = _t_points.xPosition;
        wind_generator.annotation.placement.transformation.origin.y = _t_points.yPosition;
        wind_generator.annotation.placement.transformation.rotation = (*diagram_it)->rotation.value;

        if (wind_generator.sequenceNumber()==0 || wind_generator.sequenceNumber()==1) {
            ctemplate::TemplateDictionary *wind_generator_dict = dict->AddIncludeDictionary("WINDGENERATOR_DICT");
            wind_generator_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/WindGenerator.tpl");
            wind_generator.set_template_values(wind_generator_dict);
        }
    }

    return wind_generator;
}


/**
 * ConductingEquipment of Terminal
 * ConductingEquipment cast to SynchronousMachine
 * Convert to PVNode in Modelica
 */
PVNode CIMObjectHandler::GeneratingUnitHandler(const TPNodePtr tp_node, const TerminalPtr terminal,
                                                               const GeneratingUnitPtr generatingUnit,
                                                               ctemplate::TemplateDictionary *dict) {
    PVNode pv_node;
    pv_node.set_name(name_in_modelica(generatingUnit->name));
    pv_node.set_sequenceNumber(terminal->sequenceNumber);
    pv_node.set_connected(terminal->connected);
    pv_node.annotation.placement.visible = true;

    if(this->configManager.svSettings.useSVforGeneratingUnit == true && svPowerFlowMap[terminal] && svVoltageMap[tp_node]){
        std::cout << "something" << std::endl;
        pv_node.setPgen(svPowerFlowMap[terminal]->p.value);
            pv_node.setVabs(svVoltageMap[tp_node]->v.value);
    }else{
        for(rotatingMachine_it1 = generatingUnit->RotatingMachine.begin();
            rotatingMachine_it1!= generatingUnit->RotatingMachine.end();
            ++rotatingMachine_it1){
            pv_node.setVabs((*rotatingMachine_it1)->RegulatingControl->targetValue);
        }
        pv_node.setPgen(generatingUnit->initialP.value);
    }

    for(rotatingMachine_it1 = generatingUnit->RotatingMachine.begin();
        rotatingMachine_it1!= generatingUnit->RotatingMachine.end();
        ++rotatingMachine_it1){
        pv_node.setVnom((*rotatingMachine_it1)->ratedU.value);
    }


    if(generatingUnit->DiagramObjects.begin() == generatingUnit->DiagramObjects.end()){
        std::cerr << "Missing Diagram Object for SynchronousMachine: " << generatingUnit->name << " Default Position 0,0 \n";
        pv_node.annotation.placement.transformation.origin.x = 0;
        pv_node.annotation.placement.transformation.origin.y = 0;
        pv_node.annotation.placement.transformation.rotation = 0;

        if (pv_node.sequenceNumber()==0 || pv_node.sequenceNumber()==1) {
            ctemplate::TemplateDictionary *pv_node_dict = dict->AddIncludeDictionary("PVNODE_DICT");
            pv_node_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/PVNode.tpl");
            pv_node.set_template_values(pv_node_dict);
        }
    }

    for (diagram_it = generatingUnit->DiagramObjects.begin();
         diagram_it!= generatingUnit->DiagramObjects.end();
         ++diagram_it) {
        _t_points = this->calculate_average_position();
        pv_node.annotation.placement.transformation.origin.x = _t_points.xPosition;
        pv_node.annotation.placement.transformation.origin.y = _t_points.yPosition;
        pv_node.annotation.placement.transformation.rotation = (*diagram_it)->rotation.value;

        if (pv_node.sequenceNumber()==0 || pv_node.sequenceNumber()==1) {
            ctemplate::TemplateDictionary *pv_node_dict = dict->AddIncludeDictionary("PVNODE_DICT");
            pv_node_dict->SetFilename(this->configManager.ts.directory_path + "resource/" + template_folder + "/PVNode.tpl");
            pv_node.set_template_values(pv_node_dict);
        }
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
