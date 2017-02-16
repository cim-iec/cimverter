/*
 * CIMObjectHandler.cpp
 *
 */

#include "CIMObjectHandler.h"

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
  // TODO Auto-generated destructor stub
}

/**
 * Get all settings from config.cfg.
 */
void CIMObjectHandler::get_config() {

  print_separator();
  std::cout << "reading config files..." << std::endl;
  this->configManager.getAllSettings();
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
 * Generate the modelica code
 * by parsering the _CIMObjects
 */
bool CIMObjectHandler::ModelicaCodeGenerator(std::vector<std::string> args) {
  const std::string filename = args[0];
  ctemplate::TemplateDictionary *dict = new ctemplate::TemplateDictionary("MODELICA");
  this->SystemSettingsHandler(filename, dict);

  for (BaseClass *Object : this->_CIMObjects) {

    //TopologicalNode, convert to BusBar
    if (auto *tp_node = dynamic_cast<TPNodePtr>(Object)) {

      BusBar busbar = this->TopologicalNodeHandler(tp_node, dict);

      if (this->configManager.household_parameters.use_households==true) {
        this->HouseholdComponetsHandler(tp_node, dict);
      }

      std::list<TerminalPtr>::iterator terminal_it;

      for (terminal_it = tp_node->Terminal.begin(); terminal_it!=tp_node->Terminal.end(); ++terminal_it) {

        if (auto *connectivity_node = dynamic_cast<ConnectivityNodePtr>((*terminal_it)->ConnectivityNode)) {

          ConnectivityNode connectivity_Node = this->ConnectiviyNodeHandler(tp_node, (*terminal_it),
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
          PiLine pi_line = this->ACLineSegmentHandler(tp_node, (*terminal_it), ac_line, dict);
          Connection conn(&busbar, &pi_line);
          connectionQueue.push(conn);

        } else if (auto *energy_consumer = dynamic_cast<EnergyConsumerPtr>((*terminal_it)->ConductingEquipment)) {

          if (this->configManager.household_parameters.use_households==false) {
            PQLoad pqload = this->EnergyConsumerHandler(tp_node, (*terminal_it), energy_consumer, dict);
            Connection conn(&busbar, &pqload);
            connectionQueue.push(conn);
          }

        } else if (auto *syn_machine = dynamic_cast<SynMachinePtr>((*terminal_it)->ConductingEquipment)) {
          if (this->configManager.household_parameters.use_households==false) {
            SolarGenerator solar_generator = this->SynchronousMachineHandlerType2(tp_node, (*terminal_it),
                                                                                  syn_machine, dict);
            Connection conn(&busbar, &solar_generator);
            connectionQueue.push(conn);
          }
        } else {
          if(args.size() == 2 && strcmp(args[1].c_str(), "--verbose") == 0) {
            print_RTTI((*terminal_it)->ConductingEquipment); /// In verbose module to show the no used object information
          }
        }
      }

      if (this->configManager.household_parameters.use_households==true) {

        while (!this->householdQueue.empty()) {

          switch (this->householdQueue.front().HouseholdType()) {
            case (HouseholdType::Type0):
              if (this->householdQueue.front().sequenceNumber()==0
                  || this->householdQueue.front().sequenceNumber()==1) {
                ctemplate::TemplateDictionary *household_dict = dict->AddIncludeDictionary(
                    "HOUSEHOLD_TYPE0_DICT");
                household_dict->SetFilename(
                    this->configManager.ts.directory_path + "resource/HouseholdType0.tpl");
                this->householdQueue.front().set_template_values(household_dict);
              }
              break;
            case (HouseholdType::Type1):
              if (this->householdQueue.front().sequenceNumber()==0
                  || this->householdQueue.front().sequenceNumber()==1) {
                ctemplate::TemplateDictionary *household_dict = dict->AddIncludeDictionary(
                    "HOUSEHOLD_TYPE1_DICT");
                household_dict->SetFilename(
                    this->configManager.ts.directory_path + "resource/HouseholdType1.tpl");
                this->householdQueue.front().set_template_values(household_dict);
              }
              break;
            case (HouseholdType::Type2):
              if (this->householdQueue.front().sequenceNumber()==0
                  || this->householdQueue.front().sequenceNumber()==1) {
                ctemplate::TemplateDictionary *household_dict = dict->AddIncludeDictionary(
                    "HOUSEHOLD_TYPE2_DICT");
                household_dict->SetFilename(
                    this->configManager.ts.directory_path + "resource/HouseholdType2.tpl");
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
          if (this->configManager.pqload_parameters.use_profiles==false) {
            ctemplate::TemplateDictionary *pqLoad_dict = dict->AddIncludeDictionary("PQLOAD_DICT");
            pqLoad_dict->SetFilename(this->configManager.ts.directory_path + "resource/PQLoad.tpl");
            pqloadQueue.front().set_template_values(pqLoad_dict);
          } else if (this->configManager.pqload_parameters.use_profiles==true) {
            ctemplate::TemplateDictionary *pqLoad_dict = dict->AddIncludeDictionary("PQLOADPROFILE_DICT");
            pqLoad_dict->SetFilename(this->configManager.ts.directory_path + "resource/PQLoadProfile.tpl");
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
              this->configManager.ts.directory_path + "resource/SolarGenerator.tpl");
          solarGeneratorQueue.front().set_template_values(solar_generator_dict);
          Connection conn(&busbar, &solarGeneratorQueue.front());
          connectionQueue.push(conn);
          solarGeneratorQueue.pop();
        }
      }
    }
  }

  this->ConnectionHandler(dict);

  std::string modelica_output;
  ctemplate::ExpandTemplate(this->configManager.ts.directory_path + "resource/modelica.tpl",
                            ctemplate::STRIP_BLANK_LINES, dict, &modelica_output);
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
  dict->SetValue(GRID_NAME, filename);

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

  if (tp_node->BaseVoltage->name.find("LV")!=std::string::npos) {
    busbar.set_Vnom(tp_node->BaseVoltage->nominalVoltage.value);
  } else if (tp_node->BaseVoltage->name.find("V")!=std::string::npos) {
    busbar.set_Vnom(tp_node->BaseVoltage->nominalVoltage.value*1000);
  } else {
    busbar.set_Vnom(tp_node->BaseVoltage->nominalVoltage.value*1000);
  }

  busbar.set_name(name_in_modelica(tp_node->name));
  busbar.annotation.placement.visible = true;

  if (this->configManager.busbar_parameters.enable) {

    busbar.annotation.placement.transfomation.extent.first.x =
        configManager.busbar_parameters.annotation.transformation_extent[0];
    busbar.annotation.placement.transfomation.extent.first.y =
        configManager.busbar_parameters.annotation.transformation_extent[1];
    busbar.annotation.placement.transfomation.extent.second.x =
        configManager.busbar_parameters.annotation.transformation_extent[2];
    busbar.annotation.placement.transfomation.extent.second.y =
        configManager.busbar_parameters.annotation.transformation_extent[3];
    busbar.annotation.placement.visible = configManager.busbar_parameters.annotation.visible;
  }

  // std::list<DiagramObjectPtr>::iterator diagram_it is class member!
  for (diagram_it = tp_node->DiagramObjects.begin(); diagram_it!=tp_node->DiagramObjects.end(); ++diagram_it) {
    _t_points = this->calculate_average_position();
    busbar.annotation.placement.transfomation.origin.x = _t_points.xPosition;
    busbar.annotation.placement.transfomation.origin.y = _t_points.yPosition;
    busbar.annotation.placement.transfomation.rotation = (*diagram_it)->rotation.value;

    ctemplate::TemplateDictionary *busbar_dict = dict->AddIncludeDictionary("BUSBAR_DICT");
    busbar_dict->SetFilename(this->configManager.ts.directory_path + "resource/BusBar.tpl");
    busbar.set_template_values(busbar_dict);
  }

  //BusBarSection used in Cimphony
  std::list<TerminalPtr>::iterator terminal_it;
  for (terminal_it = tp_node->Terminal.begin(); terminal_it!=tp_node->Terminal.end(); ++terminal_it) {
    if (auto *busbar_section = dynamic_cast<BusBarSectionPtr>((*terminal_it)->ConductingEquipment)) {
      this->BusBarSectionHandler(busbar_section, busbar, dict);
    }
  }

  return busbar;
}

/**
 * In the TopologicalNode to
 * find PQLoad, SolarGenerator, Battery which form HouseHold type2
 */
bool CIMObjectHandler::HouseholdComponetsHandler(const TPNodePtr tp_node, ctemplate::TemplateDictionary *dict) {

  std::list<TerminalPtr>::iterator terminal_it;
  for (terminal_it = tp_node->Terminal.begin(); terminal_it != tp_node->Terminal.end(); ++terminal_it) {

    if (auto *energy_consumer = dynamic_cast<EnergyConsumerPtr>((*terminal_it)->ConductingEquipment)) {
      PQLoad pqload = this->EnergyConsumerHandler(tp_node, (*terminal_it), energy_consumer, dict);
      this->pqloadQueue.push(pqload);
    } else if (auto *syn_machine = dynamic_cast<SynMachinePtr>((*terminal_it)->ConductingEquipment)) {
      SolarGenerator solar_generator = this->SynchronousMachineHandlerType2(tp_node, (*terminal_it), syn_machine,
                                                                            dict);
      this->solarGeneratorQueue.push(solar_generator);
    }

    if (this->pqloadQueue.size()==1 && this->solarGeneratorQueue.size()==1) {

      Household household(this->pqloadQueue.front(), this->solarGeneratorQueue.front());  //type2

      if (this->configManager.household_parameters.enable) {

        household.annotation.placement.transfomation.extent.first.x =
            configManager.household_parameters.annotation.transformation_extent[0];
        household.annotation.placement.transfomation.extent.first.y =
            configManager.household_parameters.annotation.transformation_extent[1];
        household.annotation.placement.transfomation.extent.second.x =
            configManager.household_parameters.annotation.transformation_extent[2];
        household.annotation.placement.transfomation.extent.second.y =
            configManager.household_parameters.annotation.transformation_extent[3];
        household.annotation.placement.visible = configManager.household_parameters.annotation.visible;
      }

      this->householdQueue.push(household);
      this->pqloadQueue.pop();
      this->solarGeneratorQueue.pop();
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

  for (diagram_it = busbar_section->DiagramObjects.begin();
       diagram_it!=busbar_section->DiagramObjects.end();
       ++diagram_it) {
    _t_points = this->calculate_average_position();

    busbar.annotation.placement.transfomation.origin.x = _t_points.xPosition;
    busbar.annotation.placement.transfomation.origin.y = _t_points.yPosition;
    busbar.annotation.placement.transfomation.rotation = (*diagram_it)->rotation.value;

    ctemplate::TemplateDictionary *busbar_dict = dict->AddIncludeDictionary("BUSBAR_DICT");
    busbar_dict->SetFilename(this->configManager.ts.directory_path + "resource/BusBar.tpl");
    busbar.set_template_values(busbar_dict);
  }
  return true;
}

/**
 * ConnectiviyNode
 * Convert to ConnectiviyNode in Modelica
 */
ConnectivityNode CIMObjectHandler::ConnectiviyNodeHandler(const TPNodePtr tp_node, const TerminalPtr terminal,
                                                          const ConnectivityNodePtr connectivity_node,
                                                          ctemplate::TemplateDictionary *dict) {
  ConnectivityNode conn_node;
  conn_node.set_Vnom(tp_node->BaseVoltage->nominalVoltage.value);
  conn_node.set_name(name_in_modelica(connectivity_node->name));
  conn_node.annotation.placement.visible = true;
  conn_node.set_sequenceNumber(terminal->sequenceNumber);
  conn_node.set_connected(terminal->connected);

  for (diagram_it = connectivity_node->DiagramObjects.begin();
       diagram_it!=connectivity_node->DiagramObjects.end();
       ++diagram_it) {
    _t_points = this->calculate_average_position();
    conn_node.annotation.placement.transfomation.origin.x = _t_points.xPosition;
    conn_node.annotation.placement.transfomation.origin.y = _t_points.yPosition;
    conn_node.annotation.placement.transfomation.rotation = (*diagram_it)->rotation.value - 90;

    if (conn_node.sequenceNumber()==0 || conn_node.sequenceNumber()==1) {
      ctemplate::TemplateDictionary *conn_node_dict = dict->AddIncludeDictionary("CONNECTIVITYNODE_DICT");
      conn_node_dict->SetFilename(this->configManager.ts.directory_path + "resource/ConnectiviyNode.tpl");
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
  slack.set_Vnom(tp_node->BaseVoltage->nominalVoltage.value);
  slack.set_name(name_in_modelica(externalNI->name));
  slack.set_sequenceNumber(terminal->sequenceNumber);
  slack.set_connected(terminal->connected);
  slack.annotation.placement.visible = true;

  if (this->configManager.slack_parameters.enable) {

    slack.annotation.placement.transfomation.extent.first.x =
        configManager.slack_parameters.annotation.transformation_extent[0];
    slack.annotation.placement.transfomation.extent.first.y =
        configManager.slack_parameters.annotation.transformation_extent[1];
    slack.annotation.placement.transfomation.extent.second.x =
        configManager.slack_parameters.annotation.transformation_extent[2];
    slack.annotation.placement.transfomation.extent.second.y =
        configManager.slack_parameters.annotation.transformation_extent[3];
    slack.annotation.placement.visible = configManager.slack_parameters.annotation.visible;
  }

  for (diagram_it = externalNI->DiagramObjects.begin(); diagram_it!=externalNI->DiagramObjects.end(); ++diagram_it) {

    _t_points = this->calculate_average_position();
    slack.annotation.placement.transfomation.origin.x = _t_points.xPosition;
    slack.annotation.placement.transfomation.origin.y = _t_points.yPosition;
    slack.annotation.placement.transfomation.rotation = (*diagram_it)->rotation.value - 90;

    if (slack.sequenceNumber()==0 || slack.sequenceNumber()==1) {
      ctemplate::TemplateDictionary *slack_dict = dict->AddIncludeDictionary("SLACK_DICT");
      slack_dict->SetFilename(this->configManager.ts.directory_path + "resource/Slack.tpl");
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
                                       ctemplate::TemplateDictionary *dict) {
  PiLine Pi_line;
  Pi_line.set_name(name_in_modelica(ac_line->name));
  Pi_line.set_length(ac_line->length.value);
  Pi_line.set_r(ac_line->r.value/ac_line->length.value);
  Pi_line.set_x(ac_line->x.value/ac_line->length.value);
  Pi_line.set_b(ac_line->bch.value/ac_line->length.value);
  Pi_line.set_g(ac_line->gch.value/ac_line->length.value);
  Pi_line.set_sequenceNumber(terminal->sequenceNumber);
  Pi_line.set_connected(terminal->connected);
  Pi_line.annotation.placement.visible = true;

  if (this->configManager.piline_parameters.enable) {

    Pi_line.annotation.placement.transfomation.extent.first.x =
        configManager.piline_parameters.annotation.transformation_extent[0];
    Pi_line.annotation.placement.transfomation.extent.first.y =
        configManager.piline_parameters.annotation.transformation_extent[1];
    Pi_line.annotation.placement.transfomation.extent.second.x =
        configManager.piline_parameters.annotation.transformation_extent[2];
    Pi_line.annotation.placement.transfomation.extent.second.y =
        configManager.piline_parameters.annotation.transformation_extent[3];
    Pi_line.annotation.placement.visible = configManager.piline_parameters.annotation.visible;
  }

  for (diagram_it = ac_line->DiagramObjects.begin(); diagram_it!=ac_line->DiagramObjects.end(); ++diagram_it) {

    _t_points = this->calculate_average_position();
    Pi_line.annotation.placement.transfomation.origin.x = _t_points.xPosition;
    Pi_line.annotation.placement.transfomation.origin.y = _t_points.yPosition;
    Pi_line.annotation.placement.transfomation.rotation = (*diagram_it)->rotation.value - 90;

    if (Pi_line.sequenceNumber()==0 || Pi_line.sequenceNumber()==1) {
      ctemplate::TemplateDictionary *piLine_dict = dict->AddIncludeDictionary("PILINE_DICT");
      piLine_dict->SetFilename(this->configManager.ts.directory_path + "resource/PiLine.tpl");
      Pi_line.set_template_values(piLine_dict);
    }
  }

  return Pi_line;
}

/**
 * ConductingEquipment of Terminal
 * ConductingEquipment cast to PowerTransformer
 * Convert to Transformer in Modelica
 */
Transformer CIMObjectHandler::PowerTransformerHandler(const TPNodePtr tp_node, const TerminalPtr terminal,
                                                      const PowerTrafoPtr power_trafo,
                                                      ctemplate::TemplateDictionary *dict) {

  Transformer Trafo;
  Trafo.set_name(name_in_modelica(power_trafo->name));
  Trafo.set_sequenceNumber(terminal->sequenceNumber);
  Trafo.set_connected(terminal->connected);
  Trafo.annotation.placement.visible = true;

  std::list<PowerTransformerEndPtr>::iterator transformer_end_it;
  for (transformer_end_it = power_trafo->PowerTransformerEnd.begin();
       transformer_end_it!=power_trafo->PowerTransformerEnd.end();
       ++transformer_end_it) {
    if ((*transformer_end_it)->endNumber==1) {
      Trafo.set_Vnom1((*transformer_end_it)->BaseVoltage->nominalVoltage.value*1000);
      Trafo.set_Sr((*transformer_end_it)->ratedS.value*1000000);
      Trafo.set_r((*transformer_end_it)->r.value);
      Trafo.set_x((*transformer_end_it)->x.value);
      Trafo.set_b((*transformer_end_it)->b.value);
      Trafo.calc_URr();
      Trafo.calc_Ukr();
    } else if ((*transformer_end_it)->endNumber==2) {
      Trafo.set_Vnom2((*transformer_end_it)->BaseVoltage->nominalVoltage.value*1000);
    }
  }

  if (this->configManager.trafo_parameters.enable) {

    Trafo.annotation.placement.transfomation.extent.first.x =
        configManager.trafo_parameters.annotation.transformation_extent[0];
    Trafo.annotation.placement.transfomation.extent.first.y =
        configManager.trafo_parameters.annotation.transformation_extent[1];
    Trafo.annotation.placement.transfomation.extent.second.x =
        configManager.trafo_parameters.annotation.transformation_extent[2];
    Trafo.annotation.placement.transfomation.extent.second.y =
        configManager.trafo_parameters.annotation.transformation_extent[3];
    Trafo.annotation.placement.visible = configManager.trafo_parameters.annotation.visible;
  }

  for (diagram_it = power_trafo->DiagramObjects.begin();
       diagram_it!=power_trafo->DiagramObjects.end();
       ++diagram_it) {

    _t_points = this->calculate_average_position();
    Trafo.annotation.placement.transfomation.origin.x = _t_points.xPosition;
    Trafo.annotation.placement.transfomation.origin.y = _t_points.yPosition;
    Trafo.annotation.placement.transfomation.rotation = (*diagram_it)->rotation.value - 90;

    if (Trafo.sequenceNumber()==0 || Trafo.sequenceNumber()==1) {
      ctemplate::TemplateDictionary *powerTrafo_dict = dict->AddIncludeDictionary("TRANSFORMER_DICT");
      powerTrafo_dict->SetFilename(this->configManager.ts.directory_path + "resource/Transformer.tpl");
      Trafo.set_template_values(powerTrafo_dict);
    }
  }

  return Trafo;
}

/**
 * ConductingEquipment of Terminal
 * ConductingEquipment cast to energy_consumer
 * Convert to pqload in Modelica
 */
PQLoad CIMObjectHandler::EnergyConsumerHandler(const TPNodePtr tp_node, const TerminalPtr terminal,
                                               const EnergyConsumerPtr energy_consumer,
                                               ctemplate::TemplateDictionary *dict) {

  if (this->configManager.pqload_parameters.use_profiles==false) {

    PQLoad pqload(PQLoadType::Standard);

    pqload.set_name(name_in_modelica(energy_consumer->name));
    pqload.set_Pnom(energy_consumer->p.value);
    pqload.set_Qnom(energy_consumer->q.value);
    pqload.set_Vnom(tp_node->BaseVoltage->nominalVoltage.value);
    pqload.set_sequenceNumber(terminal->sequenceNumber);
    pqload.set_connected(terminal->connected);
    pqload.annotation.placement.visible = true;

    if (this->configManager.pqload_parameters.enable) {

      pqload.annotation.placement.transfomation.extent.first.x =
          configManager.pqload_parameters.annotation.transformation_extent[0];
      pqload.annotation.placement.transfomation.extent.first.y =
          configManager.pqload_parameters.annotation.transformation_extent[1];
      pqload.annotation.placement.transfomation.extent.second.x =
          configManager.pqload_parameters.annotation.transformation_extent[2];
      pqload.annotation.placement.transfomation.extent.second.y =
          configManager.pqload_parameters.annotation.transformation_extent[3];
      pqload.annotation.placement.visible = configManager.pqload_parameters.annotation.visible;
    }

    for (diagram_it = energy_consumer->DiagramObjects.begin();
         diagram_it!=energy_consumer->DiagramObjects.end();
         ++diagram_it) {

      _t_points = this->calculate_average_position();
      pqload.annotation.placement.transfomation.origin.x = _t_points.xPosition;
      pqload.annotation.placement.transfomation.origin.y = _t_points.yPosition;
      pqload.annotation.placement.transfomation.rotation = (*diagram_it)->rotation.value;

      if (this->configManager.household_parameters.use_households==false) {

        if (pqload.sequenceNumber()==0 || pqload.sequenceNumber()==1) {
          ctemplate::TemplateDictionary *pqLoad_dict = dict->AddIncludeDictionary("PQLOAD_DICT");
          pqLoad_dict->SetFilename(this->configManager.ts.directory_path + "resource/PQLoad.tpl");
          pqload.set_template_values(pqLoad_dict);
        }
      }
    }

    return pqload;

  } else {

    PQLoad pqload(PQLoadType::Profile);
    pqload.set_name(name_in_modelica(energy_consumer->name));
    pqload.set_Vnom(tp_node->BaseVoltage->nominalVoltage.value);
    pqload.set_sequenceNumber(terminal->sequenceNumber);
    pqload.set_connected(terminal->connected);
    pqload.annotation.placement.visible = true;

    if (this->configManager.pqload_parameters.enable) {

      pqload.annotation.placement.transfomation.extent.first.x =
          configManager.pqload_parameters.annotation.transformation_extent[0];
      pqload.annotation.placement.transfomation.extent.first.y =
          configManager.pqload_parameters.annotation.transformation_extent[1];
      pqload.annotation.placement.transfomation.extent.second.x =
          configManager.pqload_parameters.annotation.transformation_extent[2];
      pqload.annotation.placement.transfomation.extent.second.y =
          configManager.pqload_parameters.annotation.transformation_extent[3];
      pqload.annotation.placement.visible = configManager.pqload_parameters.annotation.visible;
      pqload.set_profileName(configManager.pqload_parameters.profile_name);
      pqload.set_profileFileName(configManager.pqload_parameters.profile_filename);
    }

    for (diagram_it = energy_consumer->DiagramObjects.begin();
         diagram_it!=energy_consumer->DiagramObjects.end();
         ++diagram_it) {

      _t_points = this->calculate_average_position();
      pqload.annotation.placement.transfomation.origin.x = _t_points.xPosition;
      pqload.annotation.placement.transfomation.origin.y = _t_points.yPosition;
      pqload.annotation.placement.transfomation.rotation = (*diagram_it)->rotation.value;

      if (this->configManager.household_parameters.use_households==false) {
        if (pqload.sequenceNumber()==0 || pqload.sequenceNumber()==1) {
          ctemplate::TemplateDictionary *pqLoad_dict = dict->AddIncludeDictionary("PQLOADPROFILE_DICT");
          pqLoad_dict->SetFilename(this->configManager.ts.directory_path + "resource/PQLoadProfile.tpl");
          pqload.set_template_values(pqLoad_dict);
        }
      }
    }

    return pqload;
  }
}

/**
 * ConductingEquipment of Terminal
 * ConductingEquipment cast to energy_consumer
 * Convert to households in Modelica
 */
//Household CIMObjectHandler::HouseholdHandler(const TPNodePtr tp_node, const TerminalPtr terminal, const EnergyConsumerPtr energy_consumer, ctemplate::TemplateDictionary* dict) {
//
//  Household household(HouseholdType::Type1);
//
//  household.set_name(name_in_modelica(energy_consumer->name));
//  household.set_Load_Pnom(energy_consumer->p.value);
//  //household.set_Load_Qnom(energy_consumer->q.value);
//  household.set_sequenceNumber(terminal->sequenceNumber);
//  household.annotation.placement.visible = true;
//
//  for (diagram_it = energy_consumer->DiagramObjects.begin(); diagram_it != energy_consumer->DiagramObjects.end();
//        ++diagram_it) {
//
//    _t_points = this->calculate_average_position();
//    household.annotation.placement.transfomation.origin.x = _t_points.xPosition;
//    household.annotation.placement.transfomation.origin.y = _t_points.yPosition;
//    household.annotation.placement.transfomation.rotation = (*diagram_it)->rotation.value;
//
//    if (household.sequenceNumber() == 0 || household.sequenceNumber() == 1) {
//
//      if(household.HouseholdType() == HouseholdType::Type0){
//        ctemplate::TemplateDictionary* household_dict = dict->AddIncludeDictionary("HOUSEHOLD_TYPE0_DICT");
//        household_dict->SetFilename(this->configManager.ts.directory_path + "resource/HouseholdType0.tpl");
//        household.set_template_values(household_dict);
//
//      } else if (household.HouseholdType() == HouseholdType::Type1) {
//
//        ctemplate::TemplateDictionary* household_dict = dict->AddIncludeDictionary("HOUSEHOLD_TYPE1_DICT");
//        household_dict->SetFilename(this->configManager.ts.directory_path + "resource/HouseholdType1.tpl");
//        household.set_template_values(household_dict);
//      }
//    }
//  }
//
//  return household;
//}
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

    wind_generator.annotation.placement.transfomation.extent.first.x =
        configManager.wind_gen_parameters.annotation.transformation_extent[0];
    wind_generator.annotation.placement.transfomation.extent.first.y =
        configManager.wind_gen_parameters.annotation.transformation_extent[1];
    wind_generator.annotation.placement.transfomation.extent.second.x =
        configManager.wind_gen_parameters.annotation.transformation_extent[2];
    wind_generator.annotation.placement.transfomation.extent.second.y =
        configManager.wind_gen_parameters.annotation.transformation_extent[3];
    wind_generator.annotation.placement.visible = configManager.wind_gen_parameters.annotation.visible;
  }

  for (diagram_it = syn_machine->DiagramObjects.begin();
       diagram_it!=syn_machine->DiagramObjects.end();
       ++diagram_it) {
    _t_points = this->calculate_average_position();
    wind_generator.annotation.placement.transfomation.origin.x = _t_points.xPosition;
    wind_generator.annotation.placement.transfomation.origin.y = _t_points.yPosition;
    wind_generator.annotation.placement.transfomation.rotation = (*diagram_it)->rotation.value;

    if (wind_generator.sequenceNumber()==0 || wind_generator.sequenceNumber()==1) {
      ctemplate::TemplateDictionary *wind_generator_dict = dict->AddIncludeDictionary("WINDGENERATOR_DICT");
      wind_generator_dict->SetFilename(this->configManager.ts.directory_path + "resource/WindGenerator.tpl");
      wind_generator.set_template_values(wind_generator_dict);
    }
  }

  return wind_generator;
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

  if (this->configManager.wind_gen_parameters.enable) {

    solar_generator.annotation.placement.transfomation.extent.first.x =
        configManager.wind_gen_parameters.annotation.transformation_extent[0];
    solar_generator.annotation.placement.transfomation.extent.first.y =
        configManager.wind_gen_parameters.annotation.transformation_extent[1];
    solar_generator.annotation.placement.transfomation.extent.second.x =
        configManager.wind_gen_parameters.annotation.transformation_extent[2];
    solar_generator.annotation.placement.transfomation.extent.second.y =
        configManager.wind_gen_parameters.annotation.transformation_extent[3];
    solar_generator.annotation.placement.visible = configManager.wind_gen_parameters.annotation.visible;
  }

  for (diagram_it = syn_machine->DiagramObjects.begin();
       diagram_it!=syn_machine->DiagramObjects.end();
       ++diagram_it) {
    _t_points = this->calculate_average_position();
    solar_generator.annotation.placement.transfomation.origin.x = _t_points.xPosition;
    solar_generator.annotation.placement.transfomation.origin.y = _t_points.yPosition;
    solar_generator.annotation.placement.transfomation.rotation = (*diagram_it)->rotation.value;

    if (this->configManager.wind_gen_parameters.enable) {
      if (this->configManager.household_parameters.use_households==false) {

        if (solar_generator.sequenceNumber()==0 || solar_generator.sequenceNumber()==1) {
          ctemplate::TemplateDictionary *solar_generator_dict = dict->AddIncludeDictionary(
              "SOLARGENERATOR_DICT");
          solar_generator_dict->SetFilename(
              this->configManager.ts.directory_path + "resource/SolarGenerator.tpl");
          solar_generator.set_template_values(solar_generator_dict);
        }
      }
    }
  }

  return solar_generator;
}

/**
 * Create Connection
 */
bool CIMObjectHandler::ConnectionHandler(ctemplate::TemplateDictionary *dict) {

  unsigned int size;
  size = connectionQueue.size();
  std::cout << "connectionQueue size: " << size << std::endl;
  while (!connectionQueue.empty()) {
    ctemplate::TemplateDictionary *connection_dict = dict->AddIncludeDictionary(CONNECTIONS_DICT);
    connection_dict->SetFilename(this->configManager.ts.directory_path + "resource/Connections.tpl");
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
       points_it!=(*diagram_it)->DiagramObjectPoints.end();
       ++points_it) {
    t_points.xPosition += (*points_it)->xPosition;
    t_points.yPosition += (*points_it)->yPosition;
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
