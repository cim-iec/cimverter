/*
 * PQLoad.h
 * Constant Power Load
 */

#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_PHASORSINGLEPHASE_LOADS_PQLOAD_H_
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_PHASORSINGLEPHASE_LOADS_PQLOAD_H_

#include "../../../ModBaseClass.h"

using namespace ModelicaWorkshop;

/*
 * PQLoad Type
 * Standard : Constant Power Load
 * Profile : Constant Power Load
 * Profile_Data_In : Constant Power Load
 * NormProfile : Constant Power Load
 */
enum class PQLoadType {
  Standard, Profile, Profile_Data_In, NormProfile
};

namespace ModPowerSystems {

namespace PhasorSinglePhase {

namespace Loads {

class PQLoad : public ModBaseClass {
 public:
  PQLoad();
  PQLoad(enum PQLoadType Type);
  PQLoad(enum PQLoadType Type, std::string profileFileName, std::string profileName);//PQLoadProfile
  PQLoad(const PQLoad &);
  PQLoad& operator=(const PQLoad &);
  virtual ~PQLoad();

  void set_PQLoadType(enum PQLoadType Type) {
    this->_Type = Type;
  };
  enum PQLoadType PQLoadType() const {
    return _Type;
  };
  void set_Pnom(double Pnom) {
    this->_Pnom = Pnom;
  };
  double Pnom() const {
    return _Pnom;
  };
  void set_Qnom(double Qnom) {
    this->_Qnom = Qnom;
  };
  double Qnom() const {
    return _Qnom;
  };
  void set_Vnom(double Vnom) {
    this->_Vnom = Vnom;
  };
  double Vnom() const {
    return _Vnom;
  };

  void set_Pnom_displayUnit(modelicaUnit Pnom_displayUnit) {
    this->_Pnom_displayUnit = Pnom_displayUnit;
  };
  modelicaUnit Pnom_displayUnit() const {
    return _Pnom_displayUnit;
  };
  void set_Qnom_displayUnit(modelicaUnit Qnom_displayUnit) {
    this->_Qnom_displayUnit = Qnom_displayUnit;
  };
  modelicaUnit Qnom_displayUnit() const {
    return _Qnom_displayUnit;
  };
  void set_Vnom_displayUnit(modelicaUnit Vnom_displayUnit) {
    this->_Vnom_displayUnit = Vnom_displayUnit;
  };
  modelicaUnit Vnom_displayUnit() const {
    return _Vnom_displayUnit;
  };

  void set_profileFileName(std::string profileFileName) {
      this->_profileFileName = profileFileName;
  };
  std::string profileFileName() const {
      return _profileFileName;
  };
  void set_profileName(std::string profileName) {
      this->_profileName = profileName;
  };
  std::string profileName() const {
      return _profileName;
  };
  void set_enableOutputPload(bool enableOutputPload) {
      this->_enableOutputPload = enableOutputPload;
  };
  std::string enableOutputPload() const {
    if(_enableOutputPload)
      return "true";
    else
       return "false";
  };

  bool set_template_values(ctemplate::TemplateDictionary *dictionary) override;

 private:

  enum PQLoadType _Type = PQLoadType::Standard;

  //Parameters
  double _Pnom = 0;  //active power per phase
  double _Qnom = 0;  //reactive power per phase
  double _Vnom = 0;  //nominal voltage level

  modelicaUnit _Pnom_displayUnit = modelicaUnit::W;
  modelicaUnit _Qnom_displayUnit = modelicaUnit::var;
  modelicaUnit _Vnom_displayUnit = modelicaUnit::V;

  //PQLoadProfile Parameters
  bool _enableOutputPload = true;
  std::string _profileFileName = "NoName"; //File where matrix is stored
  std::string _profileName ="NoName"; //Table name on file

};

} /* namespace Loads */

} /* namespace PhasorSinglePhase */

} /* namespace ModPowerSystems */

#endif /* SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_PHASORSINGLEPHASE_LOADS_PQLOAD_H_ */
