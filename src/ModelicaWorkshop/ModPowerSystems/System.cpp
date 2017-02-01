/*
 * System.cpp
 *
 */

#include "System.h"

namespace ModPowerSystems {

System::System() {
  // TODO Auto-generated constructor stub

}

/*
 *Initialize System Label and Coordinate
 */
System::System(double lx, double ly, double rx, double ry)
    : _lx(lx),
      _ly(ly),
      _rx(rx),
      _ry(ry) {

  //initialize System Label
  this->set_name("system");
  this->annotation.placement.transfomation.extent.first.x = 0;
  this->annotation.placement.transfomation.extent.first.y = -30;
  this->annotation.placement.transfomation.extent.second.x = 30;
  this->annotation.placement.transfomation.extent.second.y = 0;
  this->annotation.placement.visible = true;

  //initialize System
  this->annotation.icon.coordinate.extent.first.x = 160;
  this->annotation.icon.coordinate.extent.first.y = -160;
  this->annotation.icon.coordinate.extent.second.x = 180;
  this->annotation.icon.coordinate.extent.second.y = 260;
}

/*
 *  Using SystemSetting parameters from configuration
 */
System::System(const ConfigManager & configManager){

  this->_lx = configManager.ss.coordinate[0];
  this->_ly = configManager.ss.coordinate[1];
  this->_rx = configManager.ss.coordinate[2];
  this->_ry = configManager.ss.coordinate[3];

  //initialize System Label
  this->_name = configManager.ss.label_name;
  this->annotation.placement.transfomation.extent.first.x = configManager.ss.label_extent[0];
  this->annotation.placement.transfomation.extent.first.y = configManager.ss.label_extent[1];
  this->annotation.placement.transfomation.extent.second.x = configManager.ss.label_extent[2];
  this->annotation.placement.transfomation.extent.second.y = configManager.ss.label_extent[3];
  this->annotation.placement.visible = true;

  //initialize System
  this->annotation.icon.coordinate.extent.first.x = configManager.ss.annotation_extent[0];
  this->annotation.icon.coordinate.extent.first.y = configManager.ss.annotation_extent[1];
  this->annotation.icon.coordinate.extent.second.x = configManager.ss.annotation_extent[2];
  this->annotation.icon.coordinate.extent.second.y = configManager.ss.annotation_extent[3];
}

System::~System() {
  // TODO Auto-generated destructor stub
}

/*
 * Output the formatted transformation extent point of modelica
 */
std::string System::output_diagram_extent_points() const {
  std::stringstream stream[4];
  stream[0] << std::fixed << std::setprecision(2) << this->_lx;
  stream[1] << std::fixed << std::setprecision(2) << this->_ly;
  stream[2] << std::fixed << std::setprecision(2) << this->_rx;
  stream[3] << std::fixed << std::setprecision(2) << this->_ry;

  std::string p1 = "{" + stream[0].str() + "," + stream[1].str() + "}";
  std::string p2 = "{" + stream[2].str() + "," + stream[3].str() + "}";

  return "{" + p1 + "," + p2 + "}";
}

/*
 * Output the formatted transformation origin point of modelica
 */
std::string System::output_icon_extent_points() const {
  std::stringstream stream[4];
  stream[0] << std::fixed << std::setprecision(1) << this->annotation.icon.coordinate.extent.first.x;
  stream[1] << std::fixed << std::setprecision(1) << this->annotation.icon.coordinate.extent.first.y;
  stream[2] << std::fixed << std::setprecision(1) << this->annotation.icon.coordinate.extent.second.x;
  stream[3] << std::fixed << std::setprecision(1) << this->annotation.icon.coordinate.extent.second.y;

  std::string p1 = "{" + stream[0].str() + "," + stream[1].str() + "}";
  std::string p2 = "{" + stream[2].str() + "," + stream[3].str() + "}";

  return "{" + p1 + "," + p2 + "}";
}

/*
 * Fill the system setting part of modelica template
 */
bool System::set_system_setting(ctemplate::TemplateDictionary *dictionary) {
  dictionary->SetValue(DIAGRAM_EXTENT_POINTS, this->output_diagram_extent_points());
  dictionary->SetValue(ICON_EXTENT_POINTS, this->output_icon_extent_points());

  return true;
}

/*
 * Fill the system label part of modelica template
 */
bool System::set_system_label(ctemplate::TemplateDictionary *dictionary) {
  dictionary->SetFormattedValue(FNOM, "%.1f", this->f_nom());
  dictionary->SetValue(NAME, this->name());
  dictionary->SetValue(FNOM_DISPLAYUNIT, (ModelicaUnit[this->f_nom_displayUnit()]));
  dictionary->SetValue(SIMMODE, this->simMode());
  dictionary->SetValue(INIT, this->init());

  return true;
}

/*
 * Fill the modelica template for system
 */
bool System::set_template_values(ctemplate::TemplateDictionary *dictionary) {
  this->set_system_setting(dictionary);
  this->set_system_label(dictionary);
  this->set_template_annotation_values(dictionary);

  return true;
}

} /* namespace ModPowerSystems */
