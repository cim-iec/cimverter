/*
 * SolarGenerator.cpp
 *
 *  Created on: 2016年11月23日
 *      Author: root
 */

#include "SolarGenerator.h"

namespace ModPowerSystems {
namespace PhasorSinglePhase {
namespace Generations {

SolarGenerator::SolarGenerator() {
  // TODO Auto-generated constructor stub

}

SolarGenerator::SolarGenerator(std::string profileFileName, std::string profileName) : _profileFileName(profileFileName), _profileName(profileName) {


}

SolarGenerator::SolarGenerator(const SolarGenerator &rhs) : ModBaseClass(rhs) {

  this->_Vnom = rhs._Vnom;
  this->_Pnom = rhs._Pnom;
  this->_StatusOn = rhs._StatusOn;
  this->_enableOutputPsolar = rhs._enableOutputPsolar;
  this->_enableInputPload = rhs._enableInputPload;
  this->_profileFileName = rhs._profileFileName;
  this->_profileName = rhs._profileName;
  this->_ControllerType = rhs._ControllerType;
  this->_W_total = rhs._W_total;
  this->_W_total = rhs._W_total;
  this->_Vnom_displayUnit = rhs._Vnom_displayUnit;
  this->_Pnom_displayUnit = rhs._Pnom_displayUnit;
}

SolarGenerator& SolarGenerator::operator=(const SolarGenerator &rhs) {

  if(this == &rhs) return *this;
  this->_Vnom = rhs._Vnom;
  this->_Pnom = rhs._Pnom;
  this->_StatusOn = rhs._StatusOn;
  this->_enableOutputPsolar = rhs._enableOutputPsolar;
  this->_enableInputPload = rhs._enableInputPload;
  this->_profileFileName = rhs._profileFileName;
  this->_profileName = rhs._profileName;
  this->_ControllerType = rhs._ControllerType;
  this->_W_total = rhs._W_total;
  this->_W_total = rhs._W_total;
  this->_Vnom_displayUnit = rhs._Vnom_displayUnit;
  this->_Pnom_displayUnit = rhs._Pnom_displayUnit;
  return *this;
}

SolarGenerator::~SolarGenerator() {
  // TODO Auto-generated destructor stub
}

bool SolarGenerator::set_template_values(ctemplate::TemplateDictionary *dictionary) {

  dictionary->SetValue("NAME", this->name());
  dictionary->SetValue("PROFILE_NAME", this->profileName());
  dictionary->SetValue("PROFILE_FILENAME", this->profileFileName());
  dictionary->SetFormattedValue("VNOM", "%.3f", this->Vnom());
  dictionary->SetFormattedValue("PNOM", "%.3f", this->Pnom());
  dictionary->SetValue("STATUS_ON", this->StatusOn());
  dictionary->SetValue("ENABLE_INPUT_PLOAD", this->enableInputPload());
  dictionary->SetValue("ENABLE_OUTPUT_PSOLAR", this->enableOutputPsolar());
  dictionary->SetFormattedValue("CURTAIL_LIMIT", "%.6f", this->CurtailLimit());
  dictionary->SetIntValue("CONTROLLER_TYPE", this->ControllerType());
  dictionary->SetFormattedValue("W_LOSS", "%.6f", this->W_loss());
  dictionary->SetFormattedValue("W_TOTAL", "%.6f", this->W_total());
  dictionary->SetValue("VNOM_DISPLAYUNIT", (ModelicaUnit[this->Vnom_displayUnit()]));
  dictionary->SetValue("PNOM_DISPLAYUNIT", (ModelicaUnit[this->Pnom_displayUnit()]));

  this->set_template_annotation_values(dictionary);

  return true;
}

} /* namespace Generations */
} /* namespace PhasorSinglePhase */
} /* namespace ModPowerSystems */
