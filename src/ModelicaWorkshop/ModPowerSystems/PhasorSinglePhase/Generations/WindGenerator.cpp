/*
 * WindGenerator.cpp
 *
 */

#include "WindGenerator.h"

namespace ModPowerSystems {

namespace PhasorSinglePhase {

namespace Generations {

WindGenerator::WindGenerator() {
  // TODO Auto-generated constructor stub

}

WindGenerator::WindGenerator(std::string profileFileName, std::string profileName) : _profileFileName(profileFileName), _profileName(profileName) {


}

WindGenerator::WindGenerator(const WindGenerator &rhs) : ModBaseClass(rhs) {

  this->_Vnom = rhs._Vnom;
  this->_Pnom = rhs._Pnom;
  this->_profileFileName = rhs._profileFileName;
  this->_profileName = rhs._profileName;
  this->_v_s = rhs._v_s;
  this->_v_s = rhs._v_s;
  this->_v_s = rhs._v_s;
  this->_Vnom_displayUnit = rhs._Vnom_displayUnit;
  this->_Pnom_displayUnit = rhs._Pnom_displayUnit;
}

WindGenerator& WindGenerator::operator=(const WindGenerator &rhs) {

  if(this == &rhs) return *this;
  this->_Vnom = rhs._Vnom;
  this->_Pnom = rhs._Pnom;
  this->_profileFileName = rhs._profileFileName;
  this->_profileName = rhs._profileName;
  this->_v_s = rhs._v_s;
  this->_v_s = rhs._v_s;
  this->_v_s = rhs._v_s;
  this->_Vnom_displayUnit = rhs._Vnom_displayUnit;
  this->_Pnom_displayUnit = rhs._Pnom_displayUnit;
  return *this;
}

WindGenerator::~WindGenerator() {
  // TODO Auto-generated destructor stub
}

bool WindGenerator::set_template_values(ctemplate::TemplateDictionary *dictionary) {

  dictionary->SetValue(NAME, this->name());
  dictionary->SetFormattedValue(VNOM, "%.3f", this->Vnom());
  dictionary->SetFormattedValue(PNOM, "%.3f", this->Pnom());
  dictionary->SetValue(PROFILE_NAME, this->profileName());
  dictionary->SetValue(PROFILE_FILENAME, this->profileFileName());
  dictionary->SetFormattedValue(V_S, "%.6f", this->v_s());
  dictionary->SetFormattedValue(V_R, "%.6f", this->v_r());
  dictionary->SetFormattedValue(V_C, "%.6f", this->v_s());


  this->set_template_annotation_values(dictionary);

  return true;
}

} /* namespace Generations */

} /* namespace PhasorSinglePhase */

} /* namespace ModPowerSystems */
