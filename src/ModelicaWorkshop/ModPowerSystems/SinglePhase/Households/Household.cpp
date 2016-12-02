/*
 * Household.cpp
 *
 */

#include "Household.h"

namespace ModPowerSystems {
namespace SinglePhase {
namespace Households {

Household::Household():_Type(HouseholdType::Type0) {
  // TODO Auto-generated constructor stub

}

Household::Household(enum HouseholdType Type):_Type(Type) {
  // TODO Auto-generated constructor stub

}

Household::Household(const Loads::PQLoad pq_load,const Generations::SolarGenerator solar_generator):_Type(HouseholdType::Type2) {

  this->set_name(pq_load.name());
  this->set_Load_Pnom(pq_load.Pnom());
  this->set_sequenceNumber(pq_load.sequenceNumber());
  this->set_connected(pq_load.is_connected());
  this->annotation.placement.visible = true;
  this->annotation.placement.transfomation.origin.x = pq_load.annotation.placement.transfomation.origin.x;
  this->annotation.placement.transfomation.origin.y = pq_load.annotation.placement.transfomation.origin.y;
  this->annotation.placement.transfomation.rotation = 0;
}

Household::Household(enum HouseholdType Type, std::string load_profileFileName, std::string load_profileName): _Type(Type),
    _Load_ProfileFileName(load_profileFileName), _Load_ProfileName(load_profileName) {


}

Household::Household(enum HouseholdType Type, std::string load_profileFileName, std::string load_profileName,
              std::string pv_profileFileName, std::string pv_profileName):_Type(Type), _Load_ProfileFileName(load_profileFileName), _Load_ProfileName(load_profileName),
                  _PV_ProfileFileName(pv_profileFileName), _PV_ProfileName(pv_profileName){



}


Household::Household(const Household &rhs) : ModBaseClass(rhs) {

  this->_Type = rhs._Type;
  this->_Load_Pnom = rhs._Load_Pnom;
  this->_Load_Qnom = rhs._Load_Pnom;

  this->_Load_Pnom_displayUnit = rhs._Load_Pnom_displayUnit;
  this->_Load_Qnom_displayUnit = rhs._Load_Qnom_displayUnit;

  if((this->_Type == HouseholdType::Type1) || (this->_Type == HouseholdType::Type2)) {

    this->_Load_ProfileFileName = rhs._Load_ProfileFileName;
    this->_Load_ProfileName = rhs._Load_ProfileFileName;
  }

  if(this->_Type == HouseholdType::Type2) {

    this->_PV_Pnom = rhs._PV_Pnom;
    this->_PV_ProfileFileName = rhs._PV_ProfileFileName;
    this->_PV_ProfileName = rhs._PV_ProfileName;
    this->_PV_Controller = rhs._PV_Controller;
    this->_PV_SystemOn = rhs._PV_SystemOn;
    this->_PV_CurtailmentLimit = rhs._PV_CurtailmentLimit;
    this->_PV_Pnom_displayUnit = rhs._PV_Pnom_displayUnit;
  }
}

Household& Household::operator=(const Household &rhs) {

  if(this == &rhs) return *this;

  this->_Type = rhs._Type;
  this->_Load_Pnom = rhs._Load_Pnom;
  this->_Load_Qnom = rhs._Load_Pnom;

  this->_Load_Pnom_displayUnit = rhs._Load_Pnom_displayUnit;
  this->_Load_Qnom_displayUnit = rhs._Load_Qnom_displayUnit;

  if((this->_Type == HouseholdType::Type1) || (this->_Type == HouseholdType::Type2)) {

    this->_Load_ProfileFileName = rhs._Load_ProfileFileName;
    this->_Load_ProfileName = rhs._Load_ProfileFileName;
  }

  if(this->_Type == HouseholdType::Type2) {

    this->_PV_Pnom = rhs._PV_Pnom;
    this->_PV_ProfileFileName = rhs._PV_ProfileFileName;
    this->_PV_ProfileName = rhs._PV_ProfileName;
    this->_PV_Controller = rhs._PV_Controller;
    this->_PV_SystemOn = rhs._PV_SystemOn;
    this->_PV_CurtailmentLimit = rhs._PV_CurtailmentLimit;
    this->_PV_Pnom_displayUnit = rhs._PV_Pnom_displayUnit;
  }
  return *this;
}

Household::~Household() {
  // TODO Auto-generated destructor stub
}

bool Household::set_template_values(ctemplate::TemplateDictionary *dictionary) {

  if(this->_Type == HouseholdType::Type0) {

    dictionary->SetValue(NAME, this->name());
    dictionary->SetFormattedValue(LOAD_PNOM, "%.2f", this->Load_Pnom());
    dictionary->SetFormattedValue(LOAD_QNOM, "%.2f", this->Load_Qnom());

  } else if(this->_Type == HouseholdType::Type1) {

    dictionary->SetValue(NAME, this->name());
    dictionary->SetFormattedValue(LOAD_PNOM, "%.2f", this->Load_Pnom());
    dictionary->SetFormattedValue(LOAD_QNOM, "%.2f", this->Load_Qnom());
    dictionary->SetValue(LOAD_PROFILE_NAME, this->Load_ProfileName());
    dictionary->SetValue(LOAD_PROFILE_FILENAME, this->Load_ProfileFileName());

  } else if(this->_Type == HouseholdType::Type2) {

    dictionary->SetValue(NAME, this->name());
    dictionary->SetFormattedValue(LOAD_PNOM, "%.2f", this->Load_Pnom());
    dictionary->SetFormattedValue(LOAD_QNOM, "%.2f", this->Load_Qnom());
    dictionary->SetValue(LOAD_PROFILE_NAME, this->Load_ProfileName());
    dictionary->SetValue(LOAD_PROFILE_FILENAME, this->Load_ProfileFileName());

    dictionary->SetFormattedValue(PV_PNOM, "%.2f", this->PV_Pnom());
    dictionary->SetValue(PV_PROFILE_NAME, this->PV_ProfileName());
    dictionary->SetValue(PV_PROFILE_FILENAME, this->PV_ProfileFileName());
    dictionary->SetIntValue(PV_CONTROLLER, this->PV_Controller());
    dictionary->SetValue(PV_SYSTEMON, this->PV_SystemOn());
    dictionary->SetIntValue(PV_CURTAILMENT_LIMIT, this->PV_CurtailmentLimit());

  }

  this->set_template_annotation_values(dictionary);

  return true;
}

} /* namespace Households */
} /* namespace SinglePhase */
} /* namespace ModPowerSystems */
