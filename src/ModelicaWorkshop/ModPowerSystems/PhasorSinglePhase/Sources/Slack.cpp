/*
 * Slack.cpp
 *
 *  Created on: Sep 14, 2016
 *      Author: root
 */

#include "Slack.h"

namespace ModPowerSystems {

namespace PhasorSinglePhase {

namespace Sources {

Slack::Slack()
    : _Vnom(0),_frequency(50),_phiV(0) {
}

Slack::Slack(const Slack &rhs):ModBaseClass(rhs) {

  this->_Vnom = rhs._Vnom;
  this->_frequency = rhs._frequency;
  this->_phiV = rhs._phiV;
  this->_Vnom_displayUnit = rhs._Vnom_displayUnit;
  this->_frequency_displayUnit = rhs._frequency_displayUnit;
}

Slack& Slack::operator=(const Slack &rhs) {

  if(this == &rhs) return *this;
  ModBaseClass::operator=(rhs);
  this->_Vnom = rhs._Vnom;
  this->_frequency = rhs._frequency;
  this->_phiV = rhs._phiV;
  this->_Vnom_displayUnit = rhs._Vnom_displayUnit;
  this->_frequency_displayUnit = rhs._frequency_displayUnit;
  return *this;
}

Slack::~Slack() {
}

bool Slack::set_template_values(ctemplate::TemplateDictionary *dictionary) {

  dictionary->SetFormattedValue(VNOM, "%.2f", this->Vnom());
  dictionary->SetValue(NAME, this->name());
  dictionary->SetValue(VNOM_DISPLAYUNIT, (ModelicaUnit[this->Vnom_displayUnit()]));
  dictionary->SetFormattedValue(FREQUENCY, "%.1f", this->frequency());
  dictionary->SetValue(FREQUENCY_DISPLAYUNIT, (ModelicaUnit[this->frequency_displayUnit()]));
  dictionary->SetFormattedValue(PHIV, "%.2f", this->phiV());
  dictionary->SetValue(PHIV_DISPLAYUNIT, (ModelicaUnit[this->phiV_displayUnit()]));

  this->set_template_annotation_values(dictionary);

  return true;
}

} /* namespace Sources */

} /* namespace PhasorSinglePhase */

} /* namespace ModPowerSystems */
