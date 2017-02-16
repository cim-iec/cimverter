/*
 * BusBar.cpp
 *
 */

#include "BusBar.h"

namespace ModPowerSystems {
namespace PhasorSinglePhase {
namespace Connections {
BusBar::BusBar()
    : _Vnom(110000) {

}

BusBar::BusBar(const BusBar &rhs):ModBaseClass(rhs) {
  this->_Vnom = rhs._Vnom;
}

BusBar& BusBar::operator=(const BusBar &rhs) {

  if(this == &rhs) return *this;
  ModBaseClass::operator=(rhs);
  this->_Vnom = rhs._Vnom;
  return *this;
}

BusBar::~BusBar() {
}

bool BusBar::set_template_values(ctemplate::TemplateDictionary *dictionary) {

  dictionary->SetFormattedValue(VNOM, "%.3f", this->Vnom());
  dictionary->SetValue(NAME, this->name());
  this->set_template_annotation_values(dictionary);

  return true;
}

} /* namespace Connections */

} /* namespace PhasorSinglePhase */

} /* namespace ModPowerSystems */
