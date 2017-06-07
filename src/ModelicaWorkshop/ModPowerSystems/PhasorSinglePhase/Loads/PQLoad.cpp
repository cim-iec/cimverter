/*
 * PQLoad.cpp
 *
 */

#include "PQLoad.h"

namespace ModPowerSystems {

namespace PhasorSinglePhase {

namespace Loads {

PQLoad::PQLoad():_Type(PQLoadType::Standard) {

}

PQLoad::PQLoad(enum PQLoadType Type):_Type(Type) {


}

PQLoad::PQLoad(enum PQLoadType Type, std::string profileFileName, std::string profileName): _Type(Type), _profileFileName(profileFileName), _profileName(profileName) {

}

PQLoad::PQLoad(const PQLoad &rhs):ModBaseClass(rhs) {

  this->_Type = rhs._Type;
  this->_Vnom = rhs._Vnom;
  this->_Vnom_displayUnit = rhs._Vnom_displayUnit;

  if(this->_Type == PQLoadType::Standard){
    this->_Pnom = rhs._Pnom;
    this->_Qnom = rhs._Qnom;
    this->_Pnom_displayUnit = rhs._Pnom_displayUnit;
    this->_Qnom_displayUnit = rhs._Qnom_displayUnit;

  } else if(this->_Type == PQLoadType::Profile) {
    this->_Pnom = rhs._Pnom;
    this->_Qnom = rhs._Qnom;
    this->_Pnom_displayUnit = rhs._Pnom_displayUnit;
    this->_Qnom_displayUnit = rhs._Qnom_displayUnit;
    this->_enableOutputPload = rhs._enableOutputPload;
    this->_profileFileName = rhs._profileFileName;
    this->_profileName = rhs._profileName;

  } else if (this->_Type == PQLoadType::NormProfile) {
    this->_Pnom = rhs._Pnom;
    this->_Qnom = rhs._Qnom;
    this->_Pnom_displayUnit = rhs._Pnom_displayUnit;
    this->_Qnom_displayUnit = rhs._Qnom_displayUnit;
    this->_enableOutputPload = rhs._enableOutputPload;
    this->_profileFileName = rhs._profileFileName;
    this->_profileName = rhs._profileName;
  }
}

PQLoad& PQLoad::operator=(const PQLoad &rhs) {

  if(this == &rhs) return *this;
  ModBaseClass::operator=(rhs);

  this->_Type = rhs._Type;
  this->_Vnom = rhs._Vnom;
  this->_Vnom_displayUnit = rhs._Vnom_displayUnit;

  if(this->_Type == PQLoadType::Standard){
    this->_Pnom = rhs._Pnom;
    this->_Qnom = rhs._Qnom;
    this->_Pnom_displayUnit = rhs._Pnom_displayUnit;
    this->_Qnom_displayUnit = rhs._Qnom_displayUnit;

  } else if(this->_Type == PQLoadType::Profile) {
    this->_Pnom = rhs._Pnom;
    this->_Qnom = rhs._Qnom;
    this->_Pnom_displayUnit = rhs._Pnom_displayUnit;
    this->_Qnom_displayUnit = rhs._Qnom_displayUnit;
    this->_enableOutputPload = rhs._enableOutputPload;
    this->_profileFileName = rhs._profileFileName;
    this->_profileName = rhs._profileName;

  } else if (this->_Type == PQLoadType::NormProfile) {
    this->_Pnom = rhs._Pnom;
    this->_Qnom = rhs._Qnom;
    this->_Pnom_displayUnit = rhs._Pnom_displayUnit;
    this->_Qnom_displayUnit = rhs._Qnom_displayUnit;
    this->_enableOutputPload = rhs._enableOutputPload;
    this->_profileFileName = rhs._profileFileName;
    this->_profileName = rhs._profileName;
  }

  return *this;
}


PQLoad::~PQLoad() {
}

bool PQLoad::set_template_values(ctemplate::TemplateDictionary *dictionary) {

  if(this->_Type == PQLoadType::Standard) {

    dictionary->SetValue("NAME", this->name());
    dictionary->SetFormattedValue("PNOM", "%.3f", this->Pnom());
    dictionary->SetFormattedValue("QNOM", "%.3f", this->Qnom());
    dictionary->SetFormattedValue("VNOM", "%.3f", this->Vnom());
    dictionary->SetValue("PNOM_DISPLAYUNIT", (ModelicaUnit[this->Pnom_displayUnit()]));
    dictionary->SetValue("QNOM_DISPLAYUNIT", (ModelicaUnit[this->Qnom_displayUnit()]));
    dictionary->SetValue("VNOM_DISPLAYUNIT", (ModelicaUnit[this->Vnom_displayUnit()]));
  } else if(this->_Type == PQLoadType::Profile) {

    dictionary->SetValue("NAME", this->name());
    dictionary->SetValue("PROFILE_NAME", this->profileName());
    dictionary->SetValue("PROFILE_FILENAME", this->profileFileName());
    dictionary->SetValue("ENABLE_OUTPUT_PLOAD", this->enableOutputPload());
    dictionary->SetFormattedValue("VNOM", "%.3f", this->Vnom());
    dictionary->SetValue("VNOM_DISPLAYUNIT", (ModelicaUnit[this->Vnom_displayUnit()]));
  } else if(this->_Type == PQLoadType::NormProfile) {

    dictionary->SetValue("NAME", this->name());
    dictionary->SetFormattedValue("PNOM", "%.3f", this->Pnom());
    dictionary->SetFormattedValue("QNOM", "%.3f", this->Qnom());
    dictionary->SetValue("PROFILE_NAME", this->profileName());
    dictionary->SetValue("PROFILE_FILENAME", this->profileFileName());
    dictionary->SetValue("ENABLE_OUTPUT_PLOAD", this->enableOutputPload());
    dictionary->SetFormattedValue("VNOM", "%.3f", this->Vnom());
    dictionary->SetValue("PNOM_DISPLAYUNIT", (ModelicaUnit[this->Pnom_displayUnit()]));
    dictionary->SetValue("QNOM_DISPLAYUNIT", (ModelicaUnit[this->Qnom_displayUnit()]));
    dictionary->SetValue("VNOM_DISPLAYUNIT", (ModelicaUnit[this->Vnom_displayUnit()]));
}

  this->set_template_annotation_values(dictionary);

  return true;
}

} /* namespace Loads */

} /* namespace PhasorSinglePhase */

} /* namespace ModPowerSystems */
