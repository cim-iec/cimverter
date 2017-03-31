/*
 * ZLoad.cpp
 *
 */

#include "ZLoad.h"

namespace ModPowerSystems {

namespace PhasorSinglePhase {

namespace Loads {

ZLoad::ZLoad() {
  // TODO Auto-generated constructor stub

}

ZLoad::ZLoad(enum ZLoadType Type):_Type(Type) {


}

ZLoad::ZLoad(enum ZLoadType Type, std::string profileFileName, std::string profileName): _Type(Type), _profileFileName(profileFileName), _profileName(profileName) {

}


ZLoad::ZLoad(const ZLoad &rhs):ModBaseClass(rhs) {

  this->_Pnom = rhs._Pnom;
  this->_Qnom = rhs._Qnom;
  this->_Vnom = rhs._Vnom;
  this->_Pnom_displayUnit = rhs._Pnom_displayUnit;
  this->_Qnom_displayUnit = rhs._Qnom_displayUnit;
  this->_Vnom_displayUnit = rhs._Vnom_displayUnit;

  if(this->_Type == ZLoadType::Profile) {

    this->_smoothnessSetting = rhs._smoothnessSetting;
    this->_profileFileName = rhs._profileFileName;
    this->_profileName = rhs._profileName;
  }

}

ZLoad& ZLoad::operator=(const ZLoad &rhs) {

  if(this == &rhs) return *this;
  ModBaseClass::operator=(rhs);
  this->_Vnom = rhs._Vnom;
  this->_Pnom = rhs._Pnom;
  this->_Qnom = rhs._Qnom;
  this->_Vnom_displayUnit = rhs._Vnom_displayUnit;
  this->_Qnom_displayUnit = rhs._Qnom_displayUnit;
  this->_Vnom_displayUnit = rhs._Vnom_displayUnit;

  if(this->_Type == ZLoadType::Profile) {

    this->_smoothnessSetting = rhs._smoothnessSetting;
    this->_profileFileName = rhs._profileFileName;
    this->_profileName = rhs._profileName;
  }
  return *this;
}


ZLoad::~ZLoad() {
  // TODO Auto-generated destructor stub
}

bool ZLoad::set_template_values(ctemplate::TemplateDictionary *dictionary) {

  dictionary->SetValue("NAME", this->name());
  dictionary->SetFormattedValue("PNOM", "%.3f", this->Pnom());
  dictionary->SetFormattedValue("QNOM", "%.3f", this->Qnom());
  dictionary->SetFormattedValue("VNOM", "%.3f", this->Vnom());
  dictionary->SetValue("PNOM_DISPLAYUNIT", (ModelicaUnit[this->Pnom_displayUnit()]));
  dictionary->SetValue("QNOM_DISPLAYUNIT", (ModelicaUnit[this->Qnom_displayUnit()]));
  dictionary->SetValue("VNOM_DISPLAYUNIT", (ModelicaUnit[this->Vnom_displayUnit()]));

  if(this->_Type == ZLoadType::Profile) {

    dictionary->SetValue("NAME", this->name());
    dictionary->SetValue("PROFILE_NAME", this->profileName());
    dictionary->SetValue("PROFILE_FILENAME", this->profileFileName());
    dictionary->SetValue("SMOOTHNESS", (Smoothness[this->smoothness()]));
  }

  this->set_template_annotation_values(dictionary);

  return true;
}

} /* namespace Loads */

} /* namespace PhasorSinglePhase */

} /* namespace ModPowerSystems */
