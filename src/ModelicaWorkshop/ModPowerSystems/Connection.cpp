/*
 * Connection.cpp
 *
 */

#include "Connection.h"

namespace ModelicaWorkshop {
    
  ConfigManager *Connection::configManager = nullptr;

    /** \brief Connection to BusBar
 *
 * All model components connect BusBar(TopologyNode)!
*/
Connection::Connection(const BusBar* busbar):_port1(busbar->name()),_terminalId1(configManager->cs.BusBarName),_p1(Point{busbar->annotation.placement.transformation.origin.x,
                                                                                           busbar->annotation.placement.transformation.origin.y}) ,_p2(Point{0,0}){
  _port1Short = _port1;
  _port1.append(".");
  _port1.append(_terminalId1);
}

/** \brief Connection between BusBar and Slack
 *
 * Delegate BusBar constructors
*/
Connection::Connection(const BusBar* busbar, const Slack* slack): Connection(busbar) {

  this->set_connected(slack->is_connected());//electrical connected?

  _port2 = slack->name();
  _terminalId2 = Connection::configManager->cs.SlackName;
  _port2Short = _port2;

  _port2.append(".");
  _port2.append(_terminalId2);
  _p2.x = slack->annotation.placement.transformation.origin.x;
  _p2.y = slack->annotation.placement.transformation.origin.y;
  this->cal_middle_points(slack);
}


/** \brief Connection between BusBar and PQLoad
 *
 * Delegate BusBar constructors
*/
Connection::Connection(const BusBar* busbar, const PQLoad* pq_load): Connection(busbar) {

  this->set_connected(pq_load->is_connected());//electrical connected?

  //connection point's position auto adjust.
  if (pq_load->annotation.placement.transformation.rotation == 0 || pq_load->annotation.placement.transformation.rotation == 359
        || pq_load->annotation.placement.transformation.rotation == 360) {
      _p2.x = pq_load->annotation.placement.transformation.origin.x;
      _p2.y = pq_load->annotation.placement.transformation.origin.y + pq_load->annotation.placement.transformation.extent.second.y;
  } else if (pq_load->annotation.placement.transformation.rotation == 90 || pq_load->annotation.placement.transformation.rotation == -270) {
      _p2.x = pq_load->annotation.placement.transformation.origin.x + pq_load->annotation.placement.transformation.extent.second.x;
      _p2.y = pq_load->annotation.placement.transformation.origin.y;
  } else if (pq_load->annotation.placement.transformation.rotation == 180 || pq_load->annotation.placement.transformation.rotation == -180) {
      _p2.x = pq_load->annotation.placement.transformation.origin.x;
      _p2.y = pq_load->annotation.placement.transformation.origin.y + pq_load->annotation.placement.transformation.extent.first.y;
  } else if (pq_load->annotation.placement.transformation.rotation == -90 || pq_load->annotation.placement.transformation.rotation == 270) {
      _p2.x = pq_load->annotation.placement.transformation.origin.x + pq_load->annotation.placement.transformation.extent.first.x;
      _p2.y = pq_load->annotation.placement.transformation.origin.y;
  }

  _port2 = pq_load->name();
  _terminalId2 = Connection::configManager->cs.PQLoadName;
  _port2Short = _port2;

  _port2.append(".");
  _port2.append(_terminalId2);

  this->cal_middle_points(pq_load);
}

/** \brief Connection between BusBar and Household
 *
 * Delegate BusBar constructors
*/
Connection::Connection(const BusBar* busbar, const Household* household): Connection(busbar) {

  this->set_connected(household->is_connected());//electrical connected?

  //connection point's position could be automatically adjusted.
  if (household->annotation.placement.transformation.rotation == 0 || household->annotation.placement.transformation.rotation == 359
          || household->annotation.placement.transformation.rotation == 360) {
    _p2.x = household->annotation.placement.transformation.origin.x;
    _p2.y = household->annotation.placement.transformation.origin.y + household->annotation.placement.transformation.extent.second.y;
  } else if (household->annotation.placement.transformation.rotation == 90 || household->annotation.placement.transformation.rotation == -270) {
    _p2.x = household->annotation.placement.transformation.origin.x + household->annotation.placement.transformation.extent.second.x;
    _p2.y = household->annotation.placement.transformation.origin.y;
  } else if (household->annotation.placement.transformation.rotation == 180 || household->annotation.placement.transformation.rotation == -180) {
    _p2.x = household->annotation.placement.transformation.origin.x;
    _p2.y = household->annotation.placement.transformation.origin.y + household->annotation.placement.transformation.extent.first.y;
  } else if (household->annotation.placement.transformation.rotation == -90 || household->annotation.placement.transformation.rotation == 270) {
    _p2.x = household->annotation.placement.transformation.origin.x + household->annotation.placement.transformation.extent.first.x;
    _p2.y = household->annotation.placement.transformation.origin.y;
  }

  _port2 = household->name();
  _terminalId2 = Connection::configManager->cs.HouseholdName;
  _port2Short = _port2;

  _port2.append(".");
  _port2.append(_terminalId2);

  this->cal_middle_points(household);

}

/** \brief Connection between BusBar and ConnectivityNode
 *
 * Delegate BusBar constructors
*/
Connection::Connection(const BusBar* busbar, const ConnectivityNode* connectivity_node): Connection(busbar) {

  this->set_connected(connectivity_node->is_connected());//electrical connected?

  _port2 = connectivity_node->name();
  _terminalId2 = this->configManager->cs.ConnectivityNodeName;
  _port2Short = _port2;

  _port2.append(".");
  _port2.append(_terminalId2);
  _p2.x = connectivity_node->annotation.placement.transformation.origin.x;
  _p2.y = connectivity_node->annotation.placement.transformation.origin.y;
  this->cal_middle_points(connectivity_node);
}

/** \brief Connection between BusBar and PiLine
 *
 * Delegate BusBar constructors
*/
Connection::Connection(const BusBar* busbar, const PiLine* pi_line): Connection(busbar) {

  this->set_connected(pi_line->is_connected());//electrical connected?
  if (pi_line->sequenceNumber() == 0 || pi_line->sequenceNumber() == 1) {
    _terminalId2 = this->configManager->cs.PiLineName + configManager->cs.PiLineSuffix1;
    if (pi_line->annotation.placement.transformation.rotation == 90 || pi_line->annotation.placement.transformation.rotation == -90) {
      _p2.x = pi_line->annotation.placement.transformation.origin.x;
      _p2.y = pi_line->annotation.placement.transformation.origin.y + pi_line->annotation.placement.transformation.extent.first.y;
    } else {
      _p2.x = pi_line->annotation.placement.transformation.origin.x + pi_line->annotation.placement.transformation.extent.first.x;
      _p2.y = pi_line->annotation.placement.transformation.origin.y;
    }
  } else if (pi_line->sequenceNumber() == 2) {
    _terminalId2 = this->configManager->cs.PiLineName + configManager->cs.PiLineSuffix2;
    if (busbar->annotation.placement.transformation.rotation == 90 || pi_line->annotation.placement.transformation.rotation == -90) {
      _p2.x = pi_line->annotation.placement.transformation.origin.x;
      _p2.y = pi_line->annotation.placement.transformation.origin.y + pi_line->annotation.placement.transformation.extent.second.y;
    } else {
      _p2.x = pi_line->annotation.placement.transformation.origin.x + pi_line->annotation.placement.transformation.extent.second.x;
      _p2.y = pi_line->annotation.placement.transformation.origin.y;
    }
  } else {
    _terminalId2 = this->configManager->cs.PiLineName + configManager->cs.PiLineSuffix1;
  }
  _port2 = pi_line->name();
  _port2Short = _port2;
  _port2.append(".");
  _port2.append(_terminalId2);

  this->cal_middle_points(pi_line);
}

/** \brief Connection between BusBar and Transformer
 *
 * Delegate BusBar constructors
*/
Connection::Connection(const BusBar* busbar, const Transformer* transformer): Connection(busbar) {

  this->set_connected(transformer->is_connected());//electrical connected?
  if (transformer->sequenceNumber() == 0 || transformer->sequenceNumber() == 1) {
    _terminalId2 = this->configManager->cs.TransformerName + configManager->cs.TransformerSuffix1;
    if (transformer->annotation.placement.transformation.rotation == 90 || transformer->annotation.placement.transformation.rotation == -90) {
      _p2.x = transformer->annotation.placement.transformation.origin.x;
      _p2.y = transformer->annotation.placement.transformation.origin.y + transformer->annotation.placement.transformation.extent.first.y;
    } else {
      _p2.x = transformer->annotation.placement.transformation.origin.x + transformer->annotation.placement.transformation.extent.first.x;
      _p2.y = transformer->annotation.placement.transformation.origin.y;
    }
  } else if (transformer->sequenceNumber() == 2) {
    _terminalId2 = this->configManager->cs.TransformerName + configManager->cs.TransformerSuffix2;
    if (transformer->annotation.placement.transformation.rotation == 90 || transformer->annotation.placement.transformation.rotation == -90) {
      _p2.x = transformer->annotation.placement.transformation.origin.x;
      _p2.y = transformer->annotation.placement.transformation.origin.y + transformer->annotation.placement.transformation.extent.second.y;
    } else {
      _p2.x = transformer->annotation.placement.transformation.origin.x + transformer->annotation.placement.transformation.extent.second.x;
      _p2.y = transformer->annotation.placement.transformation.origin.y;
    }
  } else {
    _terminalId2 = this->configManager->cs.TransformerName + configManager->cs.TransformerSuffix1;
  }
  _port2 = transformer->name();
  _port2Short = _port2;
  _port2.append(".");
  _port2.append(_terminalId2);

  this->cal_middle_points(transformer);
}

/** \brief Connection between BusBar and WindGenerator
 *
 * Delegate BusBar constructors
*/
Connection::Connection(const BusBar* busbar, const WindGenerator* wind_generator): Connection(busbar) {

  this->set_connected(wind_generator->is_connected());//electrical connected?

  _port2 = wind_generator->name();
  _terminalId2 = this->configManager->cs.WindGeneratorName;
  _port2Short = _port2;

  _port2.append(".");
  _port2.append(_terminalId2);
  _p2.x = wind_generator->annotation.placement.transformation.origin.x;
  _p2.y = wind_generator->annotation.placement.transformation.origin.y;
  this->cal_middle_points(wind_generator);

}

/** \brief Connection between BusBar and SolarGenerator
 *
 * Delegate BusBar constructors
*/
Connection::Connection(const BusBar* busbar, const SolarGenerator* solar_generator): Connection(busbar) {

  this->set_connected(solar_generator->is_connected());//electrical connected?

  _port2 = solar_generator->name();
  _terminalId2 = this->configManager->cs.SolarGeneratorName;
  _port2Short = _port2;
  
  _port2.append(".");
  _port2.append(_terminalId2);
  _p2.x = solar_generator->annotation.placement.transformation.origin.x;
  _p2.y = solar_generator->annotation.placement.transformation.origin.y;
  this->cal_middle_points(solar_generator);

}

/** \brief Connection between BusBar and PVNode
 *
 * Delegate BusBar constructors
*/
Connection::Connection(const BusBar* busbar, const PVNode* pv_node): Connection(busbar) {

  this->set_connected(pv_node->is_connected());//electrical connected?
  _port2 = pv_node->name();
  _terminalId2 = this->configManager->cs.PVNodeName;
  _port2Short = _port2;

  _port2.append(".");
  _port2.append(_terminalId2);
  _p2.x = pv_node->annotation.placement.transformation.origin.x;
  _p2.y = pv_node->annotation.placement.transformation.origin.y;
  this->cal_middle_points(pv_node);

}

/** \brief Connection between BusBar and Battery
 *
 * Delegate BusBar constructors
*/
Connection::Connection(const BusBar* busbar, const Battery* battery): Connection(busbar) {

  this->set_connected(battery->is_connected());//electrical connected?

  _port2 = battery->name();
  _terminalId2 = this->configManager->cs.BatteryName;
  _port2Short = _port2;
 
  _port2.append(".");
  _port2.append(_terminalId2);
  _p2.x = battery->annotation.placement.transformation.origin.x;
  _p2.y = battery->annotation.placement.transformation.origin.y;
  this->cal_middle_points(battery);

}

Connection::~Connection() {
  // TODO Auto-generated destructor stub
}

/** \brief Calculate the middle points
 *  4 position cases
*/
template<typename T>
void Connection::cal_middle_points(T *Componet) { // Lukas: TODO FIXME: component statt Componet!
  if (_p1.x == _p2.x || _p1.y == _p2.y) {
    _points.push_back(_p1);
    _points.push_back(_p2);

  } else {

    if (std::abs(_p1.x - _p2.x) <= std::abs(Componet->annotation.placement.transformation.extent.first.x)
        || std::abs(_p1.x - _p2.x) <= std::abs(Componet->annotation.placement.transformation.extent.first.y)) {
      Point _mp1 = { _p1.x, _p2.y };
      _points.push_back(_p1);
      _points.push_back(_mp1);
      _points.push_back(_p2);

    } else if (std::abs(_p1.y - _p2.y) <= std::abs(Componet->annotation.placement.transformation.extent.first.x)
        || std::abs(_p1.y - _p2.y) <= std::abs(Componet->annotation.placement.transformation.extent.first.y)) {
      Point _mp1 = { _p2.x, _p1.y };
      _points.push_back(_p1);
      _points.push_back(_mp1);
      _points.push_back(_p2);

    } else {
      Point _mp1 = { _p1.x, (_p1.y + _p2.y) / 2 };
      Point _mp2 = { _p2.x, (_p1.y + _p2.y) / 2 };

      _points.push_back(_p1);
      _points.push_back(_mp1);
      _points.push_back(_mp2);
      _points.push_back(_p2);
    }
  }
}

/** \brief Output the formatted points of modelica
 *
*/
std::string Connection::output_points() const {

  if (_points.size() == 2) {

    std::stringstream stream[4];
    stream[0] << std::fixed << std::setprecision(2) << _points[0].x;
    stream[1] << std::fixed << std::setprecision(2) << _points[0].y;
    stream[2] << std::fixed << std::setprecision(2) << _points[1].x;
    stream[3] << std::fixed << std::setprecision(2) << _points[1].y;

    std::string p1 = "{" + stream[0].str() + "," + stream[1].str() + "}";
    std::string p2 = "{" + stream[2].str() + "," + stream[3].str() + "}";

    return "{" + p1 + "," + p2 + "}";

  } else if (_points.size() == 3) {

    std::stringstream stream[6];
    stream[0] << std::fixed << std::setprecision(2) << _points[0].x;
    stream[1] << std::fixed << std::setprecision(2) << _points[0].y;
    stream[2] << std::fixed << std::setprecision(2) << _points[1].x;
    stream[3] << std::fixed << std::setprecision(2) << _points[1].y;
    stream[4] << std::fixed << std::setprecision(2) << _points[2].x;
    stream[5] << std::fixed << std::setprecision(2) << _points[2].y;

    std::string p1 = "{" + stream[0].str() + "," + stream[1].str() + "}";
    std::string p2 = "{" + stream[2].str() + "," + stream[3].str() + "}";
    std::string p3 = "{" + stream[4].str() + "," + stream[5].str() + "}";

    return "{" + p1 + "," + p2 + "," + p3 + "}";

  } else if (_points.size() == 4) {

    std::stringstream stream[8];
    stream[0] << std::fixed << std::setprecision(2) << _points[0].x;
    stream[1] << std::fixed << std::setprecision(2) << _points[0].y;
    stream[2] << std::fixed << std::setprecision(2) << _points[1].x;
    stream[3] << std::fixed << std::setprecision(2) << _points[1].y;
    stream[4] << std::fixed << std::setprecision(2) << _points[2].x;
    stream[5] << std::fixed << std::setprecision(2) << _points[2].y;
    stream[6] << std::fixed << std::setprecision(2) << _points[3].x;
    stream[7] << std::fixed << std::setprecision(2) << _points[3].y;

    std::string p1 = "{" + stream[0].str() + "," + stream[1].str() + "}";
    std::string p2 = "{" + stream[2].str() + "," + stream[3].str() + "}";
    std::string p3 = "{" + stream[4].str() + "," + stream[5].str() + "}";
    std::string p4 = "{" + stream[6].str() + "," + stream[7].str() + "}";

    return "{" + p1 + "," + p2 + "," + p3 + "," + p4 + "}";
  }

  return "{}";
}

void Connection::draw_connection(ctemplate::TemplateDictionary *dictionary) {

  dictionary->SetValue("PORT1", _port1);
  dictionary->SetValue("PORT2", _port2);
  dictionary->SetValue("PORT1SHORT", _port1Short);
  dictionary->SetValue("PORT2SHORT", _port2Short);

  if(this->is_connected()) {
    dictionary->SetValue("CONNECTION_TYPE", _connection_type);
    dictionary->SetValue("COLOR", this->lineColor());
    dictionary->SetValue("POINTS", this->output_points());
  }

}

void Connection::error_log() {
  std::cerr << "Connection cannot be created! ";

}

void Connection::setConfigManager(ConfigManager *manager){
    Connection::configManager = manager;
}


} /* namespace ModelicaWorkshop */
