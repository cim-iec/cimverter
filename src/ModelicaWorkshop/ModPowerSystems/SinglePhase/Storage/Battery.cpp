/*
 * Battery.cpp
 *
 */

#include "Battery.h"

namespace ModPowerSystems {
namespace SinglePhase {
namespace Storage {

Battery::Battery() {
  // TODO Auto-generated constructor stub

}

Battery::Battery(enum BatteryType Type):_Type(Type) {
  // TODO Auto-generated constructor stub

}

Battery::Battery(const Battery &rhs) : ModBaseClass(rhs) {

  this->_Vnom = rhs._Vnom;
  this->_Cnom = rhs._Cnom;
  this->_SOC_start = rhs._SOC_start;
  this->_enableOutputWbat = rhs._enableOutputWbat;
  this->_Vnom_displayUnit = rhs._Vnom_displayUnit;
  this->_Cnom_displayUnit = rhs._Cnom_displayUnit;
  this->_SOC_displayUnit = rhs._SOC_displayUnit;
  if(_Type == BatteryType::Type1) {
    this->_eta_ch = rhs._eta_ch;
    this->_eta_disch = rhs._eta_disch;
  }
}

Battery& Battery::operator=(const Battery &rhs) {

  if(this == &rhs) return *this;
  ModBaseClass::operator=(rhs);
  this->_Vnom = rhs._Vnom;
  this->_Cnom = rhs._Cnom;
  this->_SOC_start = rhs._SOC_start;
  this->_enableOutputWbat = rhs._enableOutputWbat;
  this->_Vnom_displayUnit = rhs._Vnom_displayUnit;
  this->_Cnom_displayUnit = rhs._Cnom_displayUnit;
  this->_SOC_displayUnit = rhs._SOC_displayUnit;
  if(_Type == BatteryType::Type1) {
    this->_eta_ch = rhs._eta_ch;
    this->_eta_disch = rhs._eta_disch;
  }
  return *this;
}

Battery::~Battery() {
  // TODO Auto-generated destructor stub
}

bool Battery::set_template_values(ctemplate::TemplateDictionary *dictionary) {

  dictionary->SetValue(NAME, this->name());
  dictionary->SetFormattedValue(VNOM, "%.2f", this->Vnom());
  dictionary->SetFormattedValue(CNOM, "%.2f", this->Cnom());
  dictionary->SetFormattedValue(SOC_START, "%.2f", this->SOC_start());
  dictionary->SetValue(ENABLE_OUTPUT_WBAT, this->enableOutputWbat());
  dictionary->SetValue(VNOM_DISPLAYUNIT, (ModelicaUnit[this->Vnom_displayUnit()]));
  dictionary->SetValue(CNOM_DISPLAYUNIT, (ModelicaUnit[this->Cnom_displayUnit()]));

  if(_Type == BatteryType::Type1) {
    dictionary->SetFormattedValue(ETA_CH, "%.2f", this->eta_ch());
    dictionary->SetFormattedValue(ETA_DISCH, "%.2f", this->eta_disch());
  }

  this->set_template_annotation_values(dictionary);
  return true;
}

} /* namespace Storage */
} /* namespace SinglePhase */
} /* namespace ModPowerSystems */
