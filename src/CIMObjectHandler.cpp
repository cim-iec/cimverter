/*
 * CIMObjectHandler.cpp
 *
 */

#include "CIMObjectHandler.h"

/**
 * Constructor
 * rvalue reference
 */
CIMObjectHandler::CIMObjectHandler(std::vector<BaseClass*>&& CIMObjects)
    : _CIMObjects(CIMObjects) {
  _t_points.xPosition = 0;
  _t_points.yPosition = 0;
}

CIMObjectHandler::~CIMObjectHandler() {
  // TODO Auto-generated destructor stub
}

/**
 * Generate the modelica code
 * by parsering the _CIMObjects
 */
bool CIMObjectHandler::ModelicaCodeGenerator(const std::string filename) {
  ctemplate::TemplateDictionary* dict = new ctemplate::TemplateDictionary("MODELICA");
  this->SystemSettingsHandler(filename, dict);

  for (BaseClass* Object : this->_CIMObjects) {

    //TopologicalNode, convert to BusBar
    if (auto *tp_node = dynamic_cast<TPNodePtr>(Object)) {

        BusBar busbar = this->TopologicalNodeHandler(tp_node, dict);

      for (terminal_it = tp_node->Terminal.begin(); terminal_it != tp_node->Terminal.end(); ++terminal_it) {

        if (auto *connectivity_node = dynamic_cast<ConnectivityNodePtr>((*terminal_it)->ConnectivityNode)) {

          ConnectivityNode connectivity_Node = this->ConnectiviyNodeHandler(tp_node, (*terminal_it), connectivity_node, dict);
          if ((*terminal_it)->connected == true) {
            Connection conn(&busbar, &connectivity_Node, (*terminal_it)->sequenceNumber);
            connectionQueue.push(conn);
          }
        }

        if (auto *externalNI = dynamic_cast<ExNIPtr>((*terminal_it)->ConductingEquipment)) {

          Slack slack = this->ExternalNIHandler(tp_node, (*terminal_it), externalNI, dict);
          if ((*terminal_it)->connected == true) {
            Connection conn(&busbar, &slack, (*terminal_it)->sequenceNumber);
            connectionQueue.push(conn);
          }

        } else if (auto *power_trafo = dynamic_cast<PowerTrafoPtr>((*terminal_it)->ConductingEquipment)) {
          Transformer trafo = this->PowerTransformerHandler(tp_node, (*terminal_it), power_trafo, dict);
          if ((*terminal_it)->connected == true) {
            Connection conn(&busbar, &trafo, (*terminal_it)->sequenceNumber);
            connectionQueue.push(conn);
          }

        } else if (auto *ac_line = dynamic_cast<AcLinePtr>((*terminal_it)->ConductingEquipment)) {
          PiLine pi_line = this->ACLineSegmentHandler(tp_node, (*terminal_it), ac_line, dict);
          if ((*terminal_it)->connected == true) {
            Connection conn(&busbar, &pi_line, (*terminal_it)->sequenceNumber);
            connectionQueue.push(conn);
          }

        } else if (auto *energy_consumer = dynamic_cast<EnergyConsumerPtr>((*terminal_it)->ConductingEquipment)) {
          PQLoad pqload = this->EnergyConsumerHandler(tp_node, (*terminal_it), energy_consumer, dict);
          if ((*terminal_it)->connected == true) {
            Connection conn(&busbar, &pqload, (*terminal_it)->sequenceNumber);
            connectionQueue.push(conn);
          }

        } else if (auto *syn_machine = dynamic_cast<SynMachinePtr>((*terminal_it)->ConductingEquipment)) {

          GenericGenerator generic_generator = this->SynchronousMachineHandler(tp_node, (*terminal_it), syn_machine, dict);
          if ((*terminal_it)->connected == true) {
            Connection conn(&busbar, &generic_generator, (*terminal_it)->sequenceNumber);
            connectionQueue.push(conn);
          }
        }
      }
    }
  }

  this->ConnectionHandler(dict);

  std::string modelica_output;
  ctemplate::ExpandTemplate("./resource/modelica.tpl", ctemplate::STRIP_BLANK_LINES, dict, &modelica_output);
  std::cout << modelica_output;
  // Write to file
  std::ofstream file;
  file.open("./" + filename + ".mo", std::fstream::trunc);
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
bool CIMObjectHandler::SystemSettingsHandler(const std::string filename, ctemplate::TemplateDictionary* dict) {
  //Modelica_Header
  dict->AddSectionDictionary("HEADER_FOOTER_SECTION");
  dict->SetValue("GRID_NAME", filename);

  //Global Settings
  dict->AddSectionDictionary("SYSTEM_SETTINGS_SECTION");

  auto *system = new ModPowerSystems::System(0, 0, 400, -400);
  system->set_template_values(dict);

  delete system;
  return true;
}

/**
 * TopologicalNode
 * Convert to busbar in Modelica
 */
BusBar CIMObjectHandler::TopologicalNodeHandler(const TPNodePtr tp_node, ctemplate::TemplateDictionary* dict) {
  BusBar busbar;

  if (tp_node->BaseVoltage->name.find("LV") != std::string::npos) {
    busbar.set_Vnom(tp_node->BaseVoltage->nominalVoltage.value);
  } else if (tp_node->BaseVoltage->name.find("V") != std::string::npos) {
    busbar.set_Vnom(tp_node->BaseVoltage->nominalVoltage.value * 1000);
  } else {
    busbar.set_Vnom(tp_node->BaseVoltage->nominalVoltage.value * 1000);
  }

  busbar.set_name(name_in_modelica(tp_node->name));
  busbar.annotation.placement.visible = true;

  for (diagram_it = tp_node->DiagramObjects.begin(); diagram_it != tp_node->DiagramObjects.end(); ++diagram_it) {
    _t_points = this->calculate_average_position();
    busbar.annotation.placement.transfomation.origin.x = _t_points.xPosition;
    busbar.annotation.placement.transfomation.origin.y = _t_points.yPosition;
    busbar.annotation.placement.transfomation.rotation = (*diagram_it)->rotation.value;

    ctemplate::TemplateDictionary* busbar_dict = dict->AddIncludeDictionary("BUSBAR_DICT");
    busbar_dict->SetFilename("./resource/BusBar.tpl");
    busbar.set_template_values(busbar_dict);
  }

  //BusBarSection used in Cimphony
  for (terminal_it = tp_node->Terminal.begin(); terminal_it != tp_node->Terminal.end(); ++terminal_it) {
     if (auto *busbar_section = dynamic_cast<BusBarSectionPtr>((*terminal_it)->ConductingEquipment)) {
       this->BusBarSectionHandler(busbar_section, busbar, dict);
     }
  }

  return busbar;
}

/**
 * compensate for busbar in Modelica
 * used in Cimphony
 */
bool CIMObjectHandler::BusBarSectionHandler(const BusBarSectionPtr busbar_section, BusBar &busbar, ctemplate::TemplateDictionary* dict) {

    for (diagram_it = busbar_section->DiagramObjects.begin(); diagram_it != busbar_section->DiagramObjects.end(); ++diagram_it) {
      _t_points = this->calculate_average_position();

      busbar.annotation.placement.transfomation.origin.x = _t_points.xPosition;
      busbar.annotation.placement.transfomation.origin.y = _t_points.yPosition;
      busbar.annotation.placement.transfomation.rotation = (*diagram_it)->rotation.value;

      ctemplate::TemplateDictionary* busbar_dict = dict->AddIncludeDictionary("BUSBAR_DICT");
      busbar_dict->SetFilename("./resource/BusBar.tpl");
      busbar.set_template_values(busbar_dict);
    }
    return true;
}


/**
 * ConnectiviyNode
 * Convert to ConnectiviyNode in Modelica
 */
ConnectivityNode CIMObjectHandler::ConnectiviyNodeHandler(const TPNodePtr tp_node, const TerminalPtr terminal, const ConnectivityNodePtr connectivity_node, ctemplate::TemplateDictionary* dict) {
  ConnectivityNode conn_node;
  conn_node.set_Vnom(tp_node->BaseVoltage->nominalVoltage.value);
  conn_node.set_name(name_in_modelica(connectivity_node->name));
  conn_node.annotation.placement.visible = true;

  for (diagram_it = connectivity_node->DiagramObjects.begin(); diagram_it != connectivity_node->DiagramObjects.end();
      ++diagram_it) {
    _t_points = this->calculate_average_position();
    conn_node.annotation.placement.transfomation.origin.x = _t_points.xPosition;
    conn_node.annotation.placement.transfomation.origin.y = _t_points.yPosition;
    conn_node.annotation.placement.transfomation.rotation = (*diagram_it)->rotation.value - 90;

    if (terminal->sequenceNumber == 0 || terminal->sequenceNumber == 1) {
      ctemplate::TemplateDictionary* conn_node_dict = dict->AddIncludeDictionary("CONNECTIVITYNODE_DICT");
      conn_node_dict->SetFilename("./resource/ConnectiviyNode.tpl");
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

Slack CIMObjectHandler::ExternalNIHandler(const TPNodePtr tp_node, const TerminalPtr terminal, const ExNIPtr externalNI, ctemplate::TemplateDictionary* dict) {
  Slack slack;
  slack.set_Vnom(tp_node->BaseVoltage->nominalVoltage.value);
  slack.set_name(name_in_modelica(externalNI->name));
  slack.annotation.placement.visible = true;

  for (diagram_it = externalNI->DiagramObjects.begin(); diagram_it != externalNI->DiagramObjects.end(); ++diagram_it) {

    _t_points = this->calculate_average_position();
    slack.annotation.placement.transfomation.origin.x = _t_points.xPosition;
    slack.annotation.placement.transfomation.origin.y = _t_points.yPosition;
    slack.annotation.placement.transfomation.rotation = (*diagram_it)->rotation.value - 90;

    if (terminal->sequenceNumber == 0 || terminal->sequenceNumber == 1) {
      ctemplate::TemplateDictionary* slack_dict = dict->AddIncludeDictionary("SLACK_DICT");
      slack_dict->SetFilename("./resource/Slack.tpl");
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
PiLine CIMObjectHandler::ACLineSegmentHandler(const TPNodePtr tp_node, const TerminalPtr terminal, const AcLinePtr ac_line, ctemplate::TemplateDictionary* dict) {
  PiLine Pi_line;
  Pi_line.set_name(name_in_modelica(ac_line->name));
  Pi_line.set_r(ac_line->r.value);
  Pi_line.set_x(ac_line->x.value);
  Pi_line.set_b(ac_line->bch.value);
  Pi_line.set_g(ac_line->gch.value);
  Pi_line.set_length(ac_line->length.value);
  Pi_line.annotation.placement.visible = true;

  for (diagram_it = ac_line->DiagramObjects.begin(); diagram_it != ac_line->DiagramObjects.end(); ++diagram_it) {

    _t_points = this->calculate_average_position();
    Pi_line.annotation.placement.transfomation.origin.x = _t_points.xPosition;
    Pi_line.annotation.placement.transfomation.origin.y = _t_points.yPosition;
    Pi_line.annotation.placement.transfomation.rotation = (*diagram_it)->rotation.value - 90;

    if (terminal->sequenceNumber == 0 || terminal->sequenceNumber == 1) {
      ctemplate::TemplateDictionary* piLine_dict = dict->AddIncludeDictionary("PILINE_DICT");
      piLine_dict->SetFilename("./resource/PiLine.tpl");
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

Transformer CIMObjectHandler::PowerTransformerHandler(const TPNodePtr tp_node, const TerminalPtr terminal, const PowerTrafoPtr power_trafo, ctemplate::TemplateDictionary* dict) {

  Transformer Trafo;
  Trafo.set_name(name_in_modelica(power_trafo->name));

  Trafo.annotation.placement.visible = true;

  for(transformer_end_it = power_trafo->PowerTransformerEnd.begin();transformer_end_it != power_trafo->PowerTransformerEnd.end(); ++transformer_end_it){
    if((*transformer_end_it)->endNumber == 1){
      Trafo.set_Vnom1((*transformer_end_it)->BaseVoltage->nominalVoltage.value*1000);
      Trafo.set_Sr((*transformer_end_it)->ratedS.value * 1000000);
      Trafo.set_r((*transformer_end_it)->r.value);
      Trafo.set_x((*transformer_end_it)->x.value);
      Trafo.set_b((*transformer_end_it)->b.value);
      Trafo.calc_URr();
      Trafo.calc_Ukr();
    } else if ((*transformer_end_it)->endNumber == 2){
      Trafo.set_Vnom2((*transformer_end_it)->BaseVoltage->nominalVoltage.value*1000);
    }
  }

  for (diagram_it = power_trafo->DiagramObjects.begin(); diagram_it != power_trafo->DiagramObjects.end(); ++diagram_it) {

    _t_points = this->calculate_average_position();
    Trafo.annotation.placement.transfomation.origin.x = _t_points.xPosition;
    Trafo.annotation.placement.transfomation.origin.y = _t_points.yPosition;
    Trafo.annotation.placement.transfomation.rotation = (*diagram_it)->rotation.value - 90;

    if (terminal->sequenceNumber == 0 || terminal->sequenceNumber == 1) {
      ctemplate::TemplateDictionary* powerTrafo_dict = dict->AddIncludeDictionary("TRANSFORMER_DICT");
      powerTrafo_dict->SetFilename("./resource/Transformer.tpl");
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
PQLoad CIMObjectHandler::EnergyConsumerHandler(const TPNodePtr tp_node, const TerminalPtr terminal, const EnergyConsumerPtr energy_consumer, ctemplate::TemplateDictionary* dict) {
  PQLoad pqload;

  pqload.set_name(name_in_modelica(energy_consumer->name));
  pqload.set_Pnom(energy_consumer->p.value);
  pqload.set_Qnom(energy_consumer->q.value);
  pqload.set_Vnom(tp_node->BaseVoltage->nominalVoltage.value);
  pqload.annotation.placement.visible = true;

  for (diagram_it = energy_consumer->DiagramObjects.begin(); diagram_it != energy_consumer->DiagramObjects.end();
      ++diagram_it) {

    _t_points = this->calculate_average_position();
    pqload.annotation.placement.transfomation.origin.x = _t_points.xPosition;
    pqload.annotation.placement.transfomation.origin.y = _t_points.yPosition;
    pqload.annotation.placement.transfomation.rotation = (*diagram_it)->rotation.value;

    if (terminal->sequenceNumber == 0 || terminal->sequenceNumber == 1) {
      ctemplate::TemplateDictionary* pqLoad_dict = dict->AddIncludeDictionary("PQLOAD_DICT");
      pqLoad_dict->SetFilename("./resource/PQLoad.tpl");
      pqload.set_template_values(pqLoad_dict);
    }

  }

  return pqload;
}

/**
 * ConductingEquipment of Terminal
 * ConductingEquipment cast to SynchronousMachine
 * Convert to generic_generator in Modelica
 */
GenericGenerator CIMObjectHandler::SynchronousMachineHandler(const TPNodePtr tp_node, const TerminalPtr terminal, const SynMachinePtr syn_machine, ctemplate::TemplateDictionary* dict) {
  GenericGenerator generic_generator;

  generic_generator.set_name(name_in_modelica(syn_machine->name));
  generic_generator.annotation.placement.visible = true;

  for (diagram_it = syn_machine->DiagramObjects.begin(); diagram_it != syn_machine->DiagramObjects.end();
      ++diagram_it) {
    _t_points = this->calculate_average_position();
    generic_generator.annotation.placement.transfomation.origin.x = _t_points.xPosition;
    generic_generator.annotation.placement.transfomation.origin.y = _t_points.yPosition;
    generic_generator.annotation.placement.transfomation.rotation = (*diagram_it)->rotation.value;

    if (terminal->sequenceNumber == 0 || terminal->sequenceNumber == 1) {
      ctemplate::TemplateDictionary* genericGenerator_dict = dict->AddIncludeDictionary("GENERICGENERATOR_DICT");
      genericGenerator_dict->SetFilename("./resource/GenericGenerator.tpl");
      generic_generator.set_template_values(genericGenerator_dict);
    }
  }

  return generic_generator;
}

/**
 * Create Connection
 */
bool CIMObjectHandler::ConnectionHandler(ctemplate::TemplateDictionary* dict) {
  unsigned int size;
  size = connectionQueue.size();
  std::cout << "connectionQueue size: " << size << std::endl;
  while (!connectionQueue.empty()) {
    ctemplate::TemplateDictionary* connection_dict = dict->AddIncludeDictionary(CONNECTIONS_DICT);
    connection_dict->SetFilename("./resource/Connections.tpl");
    connectionQueue.front().draw_connection(connection_dict);
    connectionQueue.pop();
  }

  return true;
}

/**
 * every component from NEPLAN has two position
 *  calculate the average position
 */
DiagramObjectPoint CIMObjectHandler::calculate_average_position() {
  DiagramObjectPoint t_points;
  t_points.xPosition = 0;
  t_points.yPosition = 0;

  for (points_it = (*diagram_it)->DiagramObjectPoints.begin(); points_it != (*diagram_it)->DiagramObjectPoints.end();
      ++points_it) {
    t_points.xPosition += (*points_it)->xPosition;
    t_points.yPosition += (*points_it)->yPosition;
  }

  std::size_t size = (*diagram_it)->DiagramObjectPoints.size();

#ifdef DEBUG
#pragma message("DEBUG macro activated!")
  std::cout << "the size of DiagramObjectPoints is: " << size << std::endl;
#endif
  t_points = convert_coordinate(t_points.xPosition / size, t_points.yPosition / size);

  return t_points;
}

/**
 * convert the coordinate system between different software
 */
DiagramObjectPoint CIMObjectHandler::convert_coordinate(double x, double y) {
  double trans_para[4] = { 1, 0, -1, 0 };
  DiagramObjectPoint t_points;

  t_points.xPosition = trans_para[0] * x + trans_para[1];
  t_points.yPosition = trans_para[2] * y + trans_para[3];

  return t_points;
}

/**
 * convert name adapt to the format in modelica
 */
std::string CIMObjectHandler::name_in_modelica(std::string original_name) {
  std::string t_name = "CIM_" + original_name;
  for(std::string::iterator it = t_name.begin(); it != t_name.end(); ++it) {
    if((*it == ' ') || (*it == '-') || (*it == '.') ) {
        *it = '_';
    }
  }

  return t_name;
}
