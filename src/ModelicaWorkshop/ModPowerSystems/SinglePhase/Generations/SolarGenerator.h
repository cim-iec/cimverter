/*
 * SolarGenerator.h
 *
 */

#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_GENERATIONS_SOLARGENERATOR_H_
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_GENERATIONS_SOLARGENERATOR_H_

#include "../../../ModBaseClass.h"
#include <string>

using namespace ModelicaWorkshop;

namespace ModPowerSystems {
namespace SinglePhase {
namespace Generations {

class SolarGenerator : public ModBaseClass {
 public:
  SolarGenerator();
  SolarGenerator(std::string profileFileName, std::string profileName);
  SolarGenerator(const SolarGenerator &);
  SolarGenerator& operator=(const SolarGenerator &);
  virtual ~SolarGenerator();

  void set_Vnom(double Vnom) {
    this->_Vnom = Vnom;
  };
  double Vnom() const {
    return _Vnom;
  };
  void set_Pnom(double Pnom) {
    this->_Pnom = Pnom;
  };
  double Pnom() const {
    return _Pnom;
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
  void set_StatusOn(bool StatusOn) {
      this->_StatusOn = StatusOn;
  };
  std::string StatusOn() const {
    if(_StatusOn)
      return "true";
    else
      return "false";
  };
  void set_enableOutputPsolar(bool enableOutputPsolar) {
      this->_enableOutputPsolar = enableOutputPsolar;
  };
  std::string enableOutputPsolar() const {
    if(_enableOutputPsolar)
      return "true";
    else
      return "false";
  };
  void set__enableInputPload(bool enableInputPload) {
      this->_enableInputPload = enableInputPload;
  };
  std::string enableInputPload() const {
    if(_enableInputPload)
      return "true";
    else
      return "false";
  };
  void set_ControllerType(int ControllerType) {
    this->_ControllerType = ControllerType;
  };
  int ControllerType() const {
    return _ControllerType;
  };
  void set_CurtailLimit(double CurtailLimit) {
    this->_CurtailLimit = CurtailLimit;
  };
  double CurtailLimit() const {
      return _CurtailLimit;
  };
  void set_W_total(double W_total) {
    this->_W_total = W_total;
  };
  double W_total() const {
      return _W_total;
  };
  void set_W_loss(double W_loss) {
    this->_W_loss = W_loss;
  };
  double W_loss() const {
      return _W_loss;
  };
  void set_Vnom_displayUnit(modelicaUnit Vnom_displayUnit) {
    this->_Vnom_displayUnit = Vnom_displayUnit;
  };
  modelicaUnit Vnom_displayUnit() const {
    return _Vnom_displayUnit;
  };
  void set_Pnom_displayUnit(modelicaUnit Pnom_displayUnit) {
    this->_Pnom_displayUnit = Pnom_displayUnit;
  };
  modelicaUnit Pnom_displayUnit() const {
    return _Pnom_displayUnit;
  };

  bool set_template_values(ctemplate::TemplateDictionary *dictionary) override;

 private:
  // Parameters for entire array
  double _Vnom = 110000; //nominal Voltage
  double _Pnom = 500000; //nominal power
  std::string _profileFileName = "NoName";//file where matrix is stored
  std::string _profileName = "NoName"; //table name on file
  bool _StatusOn = true; //generator on/off
  bool _enableOutputPsolar = false;
  bool _enableInputPload = false;
  int _ControllerType = 0;//0 = No control, 1 = Q provision, 2 = P curtailment at plant, 3 = P curtailment at PCC
  double _CurtailLimit = 70.0; //curtailment limit for active power (only effective for controller types 2 and 3;
  double _W_total = 0;
  double _W_loss = 0;

  modelicaUnit _Vnom_displayUnit = modelicaUnit::V;
  modelicaUnit _Pnom_displayUnit = modelicaUnit::W;
};

} /* namespace Generations */
} /* namespace SinglePhase */
} /* namespace ModPowerSystems */

#endif /* SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_GENERATIONS_SOLARGENERATOR_H_ */
