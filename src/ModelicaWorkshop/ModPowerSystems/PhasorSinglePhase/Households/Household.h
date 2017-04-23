/*
 * Household.h
 *
 */

#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_PHASORSINGLEPHASE_HOUSEHOLDS_HOUSEHOLD_H_
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_PHASORSINGLEPHASE_HOUSEHOLDS_HOUSEHOLD_H_

#include "../../../ModBaseClass.h"
#include "../Loads/PQLoad.h"
#include "../Generations/SolarGenerator.h"
#include <string>

using namespace ModelicaWorkshop;

/*
 * Household Type
 * Type1 : Household with specific load profile
 * Type2 : Household with load and solar generation
 * Type3a : Household with battery storage - Maximizing self-consumption
 * Type3ba : Household with battery storage - Static Peak-Shaving at Plant
 * Type3bb : Household with battery storage - Static Peak-Shaving at PCC
 * Type3ca : Household with load, solar generation and battery storage, Topology for Model Predictive Control of Pbat (open-loop)
 * Type3cb : Household with load, solar generation and battery storage, Topology for Model Predictive Control of Pbat (disturbance measurement)
 * Type3cc : Household with load, solar generation and battery storage, Topology for Model Predictive Control of Ppcc (open-loop)
 * Type3cd : Household with load, solar generation and battery storage, Topology for Model Predictive Control of Ppcc (state measurement)
 * Type3ce : Household with load, solar generation and battery storage, Topology for Model Predictive Control of Ppcc (state + disturbance measurement)
 */
enum class HouseholdType {
  Type1, Type2,
  Type3a, Type3ba, Type3bb,
  Type3ca, Type3cb, Type3cc, Type3cd, Type3ce
};

namespace ModPowerSystems {
namespace PhasorSinglePhase {
namespace Households {

class Household : public ModBaseClass {
 public:
  Household();
  //HouseHoldType Constructor with profile
  Household(enum HouseholdType Type);
  //HouseHoldType1 Constructor with profile
  Household(const Loads::PQLoad pq_load);
  Household(enum HouseholdType Type, std::string load_profileFileName, std::string load_profileName);
  //HouseHoldType2 Constructor
  Household(const Loads::PQLoad pq_load, const Generations::SolarGenerator solar_generator);
  Household(enum HouseholdType Type, std::string load_profileFileName, std::string load_profileName, std::string pv_profileFileName, std::string pv_profileName);
  Household(const Household &);
  Household& operator=(const Household &);
  virtual ~Household();

  void set_HouseholdType(enum HouseholdType Type) {
    this->_Type = Type;
  };
  enum HouseholdType HouseholdType() const {
    return _Type;
  };
  void set_Load_Pnom(double Load_Pnom) {
    this->_Load_Pnom = Load_Pnom;
  };
  double Load_Pnom() const {
    return _Load_Pnom;
  };
  void set_Load_Qnom(double Load_Qnom) {
    this->_Load_Qnom = Load_Qnom;
  };
  double Load_Qnom() const {
    return _Load_Qnom;
  };
  void set_Load_ProfileFileName(std::string Load_ProfileFileName) {
      this->_Load_ProfileFileName = Load_ProfileFileName;
  };
  std::string Load_ProfileFileName() const {
      return _Load_ProfileFileName;
  };
  void set_Load_ProfileName(std::string Load_ProfileName) {
      this->_Load_ProfileName = Load_ProfileName;
  };
  std::string Load_ProfileName() const {
      return _Load_ProfileName;
  };
  void set_PV_Pnom(double PV_Pnom) {
    this->_PV_Pnom = PV_Pnom;
  };
  double PV_Pnom() const {
    return _PV_Pnom;
  };
  void set_PV_ProfileFileName(std::string PV_ProfileFileName) {
      this->_PV_ProfileFileName = PV_ProfileFileName;
  };
  std::string PV_ProfileFileName() const {
      return _PV_ProfileFileName;
  };
  void set_PV_ProfileName(std::string PV_ProfileName) {
      this->_PV_ProfileName = PV_ProfileName;
  };
  std::string PV_ProfileName() const {
      return _PV_ProfileName;
  };
  void set_PV_Controller(int PV_Controller) {
    this->_PV_Controller = PV_Controller;
  };
  int PV_Controller() const {
    return _PV_Controller;
  };
  void set_PV_SystemOn(bool PV_SystemOn) {
      this->_PV_SystemOn = PV_SystemOn;
  };
  std::string PV_SystemOn() const {
    if(_PV_SystemOn)
      return "true";
    else
      return "false";
  };
  void set_PV_CurtailmentLimit(double PV_CurtailmentLimit) {
    this->_PV_CurtailmentLimit = PV_CurtailmentLimit;
  };
  double PV_CurtailmentLimit() const {
      return _PV_CurtailmentLimit;
  };
  void set_Load_Pnom_displayUnit(modelicaUnit Load_Pnom_displayUnit) {
    this->_Load_Pnom_displayUnit = Load_Pnom_displayUnit;
  };
  modelicaUnit Load_Pnom_displayUnit() const {
    return _Load_Pnom_displayUnit;
  };
  void set_Load_Qnom_displayUnit(modelicaUnit Load_Qnom_displayUnit) {
    this->_Load_Qnom_displayUnit = Load_Qnom_displayUnit;
  };
  modelicaUnit Load_Qnom_displayUnit() const {
    return _Load_Qnom_displayUnit;
  };
  void set_PV_Pnom_displayUnit(modelicaUnit PV_Pnom_displayUnit) {
    this->_PV_Pnom_displayUnit = PV_Pnom_displayUnit;
  };
  modelicaUnit PV_Pnom_displayUnit() const {
    return _PV_Pnom_displayUnit;
  };

  bool set_template_values(ctemplate::TemplateDictionary *dictionary) override;

 private:
  enum HouseholdType _Type;

  //Type0 Parameters
  double _Load_Pnom = 2000;//nominal active power of PQ load
  double _Load_Qnom = 0.0;//nominal reactive power of PQ load

  modelicaUnit _Load_Pnom_displayUnit = modelicaUnit::W;
  modelicaUnit _Load_Qnom_displayUnit = modelicaUnit::var;
  //from now, Type1 Parameters...
  std::string _Load_ProfileFileName = "NoName";//File where load profile is stored
  std::string _Load_ProfileName = "NoName";//Table name on load profile file

  //from now, Type2 Parameters...
  double _PV_Pnom = 5000; //nominal power of pv system;
  std::string _PV_ProfileFileName = "NoName";//file where matrix is stored
  std::string _PV_ProfileName = "NoName";//table name on file
  int _PV_Controller = 0;//0 = None, 1 = Q provision, 2 = P curtailment at plant, 3 = P curtailment at PCC
  bool _PV_SystemOn = true; //PV system on/off
  double _PV_CurtailmentLimit = 70.0; //only effective for controller type 2 and 3

  modelicaUnit _PV_Pnom_displayUnit = modelicaUnit::W;

};

} /* namespace Households */
} /* namespace PhasorSinglePhase */
} /* namespace ModPowerSystems */

#endif /* SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_PHASORSINGLEPHASE_HOUSEHOLDS_HOUSEHOLD_H_ */
