/*
 * PiLine.cpp
 *
 */

#include "PiLine.h"

namespace ModPowerSystems {

namespace PhasorSinglePhase {

namespace Lines {

PiLine::PiLine() {
  // TODO Auto-generated constructor stub

}

PiLine::PiLine(const PiLine &rhs):ModBaseClass(rhs) {

  this->_length = rhs._length;
  this->_r = rhs._r;
  this->_x = rhs._x;
  this->_b = rhs._b;
  this->_g = rhs._g;
  this->_Sr = rhs._Sr;
  this->_Imax = rhs._Imax;
  this->_Imax_displayUnit = rhs._Imax_displayUnit;
  this->_Sr_displayUnit = rhs._Sr_displayUnit;
  this->_g_displayUnit = rhs._g_displayUnit;
  this->_b_displayUnit = rhs._b_displayUnit;
  this->_r_displayUnit = rhs._r_displayUnit;
  this->_x_displayUnit = rhs._x_displayUnit;
}

PiLine & PiLine::operator=(const PiLine &rhs) {

  if(this == &rhs) return *this;
  ModBaseClass::operator=(rhs);
  this->_length = rhs._length;
  this->_r = rhs._r;
  this->_x = rhs._x;
  this->_b = rhs._b;
  this->_g = rhs._g;
  this->_Sr = rhs._Sr;
  this->_Imax = rhs._Imax;
  this->_Imax_displayUnit = rhs._Imax_displayUnit;
  this->_Sr_displayUnit = rhs._Sr_displayUnit;
  this->_g_displayUnit = rhs._g_displayUnit;
  this->_b_displayUnit = rhs._b_displayUnit;
  this->_r_displayUnit = rhs._r_displayUnit;
  this->_x_displayUnit = rhs._x_displayUnit;

  return *this;
}


PiLine::~PiLine() {
  // TODO Auto-generated destructor stub
}

bool PiLine::set_template_values(ctemplate::TemplateDictionary *dictionary) {

  dictionary->SetValue("NAME", this->name());
  dictionary->SetFormattedValue("LENGTH_KM", "%.6f", this->length());
  dictionary->SetFormattedValue("LENGTH_M", "%.6f", this->length() * 1000);
  dictionary->SetFormattedValue("IMAX", "%.3f", this->Imax());
  dictionary->SetFormattedValue("R", "%.6f", this->r());
  dictionary->SetFormattedValue("X", "%.6f", this->x());
  dictionary->SetFormattedValue("B", "%.10f", this->b());
  dictionary->SetFormattedValue("G", "%.6f", this->g());
  dictionary->SetFormattedValue("SR", "%.6f", this->Sr());
  dictionary->SetValue("IMAX_DISPLAYUNIT", (ModelicaUnit[this->Imax_displayUnit()]));
  dictionary->SetValue("SR_DISPLAYUNIT", (ModelicaUnit[this->Sr_displayUnit()]));

  this->set_template_annotation_values(dictionary);

  return true;
}

} /* namespace Lines */

} /* namespace PhasorSinglePhase */

} /* namespace ModPowerSystems */
