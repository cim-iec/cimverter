/*
 * PQLoad.cpp
 *
 *  Created on: Sep 14, 2016
 *      Author: root
 */

#include "PQLoad.h"

namespace ModPowerSystems {

namespace SinglePhase {

namespace Loads {

PQLoad::PQLoad() {
}

PQLoad::PQLoad(const PQLoad &rhs):ModBaseClass(rhs) {

  this->_Pnom = rhs._Pnom;
  this->_Qnom = rhs._Qnom;
  this->_Vnom = rhs._Vnom;

  this->_Pnom_displayUnit = rhs._Pnom_displayUnit;
  this->_Qnom_displayUnit = rhs._Qnom_displayUnit;
  this->_Vnom_displayUnit = rhs._Vnom_displayUnit;
}

PQLoad::~PQLoad() {
}

bool PQLoad::set_template_values(ctemplate::TemplateDictionary *dictionary) {
  dictionary->SetValue(NAME, this->name());
  dictionary->SetFormattedValue(PNOM, "%.2f", this->Pnom());
  dictionary->SetFormattedValue(QNOM, "%.2f", this->Qnom());
  dictionary->SetFormattedValue(VNOM, "%.2f", this->Vnom());
  dictionary->SetValue(PNOM_DISPLAYUNIT, (ModelicaUnit[this->Pnom_displayUnit()]));
  dictionary->SetValue(QNOM_DISPLAYUNIT, (ModelicaUnit[this->Qnom_displayUnit()]));
  dictionary->SetValue(VNOM_DISPLAYUNIT, (ModelicaUnit[this->Vnom_displayUnit()]));

  this->set_template_annotation_values(dictionary);

  return true;
}

} /* namespace Loads */

} /* namespace SinglePhase */

} /* namespace ModPowerSystems */
