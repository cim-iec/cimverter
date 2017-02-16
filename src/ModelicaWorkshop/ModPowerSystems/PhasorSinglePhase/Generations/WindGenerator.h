/*
 * WindGenerator.h
 *
 */

#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_PHASORSINGLEPHASE_GENERATIONS_WINDGENERATOR_H_
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_PHASORSINGLEPHASE_GENERATIONS_WINDGENERATOR_H_

#include "../../../ModBaseClass.h"

using namespace ModelicaWorkshop;

namespace ModPowerSystems {

namespace PhasorSinglePhase {

namespace Generations {

class WindGenerator : public ModBaseClass {
 public:
  WindGenerator();
  WindGenerator(std::string profileFileName, std::string profileName);
  WindGenerator(const WindGenerator &);
  WindGenerator& operator=(const WindGenerator &);
  virtual ~WindGenerator();

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
  void set_v_s(double v_s) {
    this->_v_s = v_s;
  };
  double v_s() const {
    return _v_s;
  };
  void set_v_r(double v_r) {
    this->_v_r = v_r;
  };
  double v_r() const {
    return _v_r;
  };
  void set_v_c(double v_c) {
    this->_v_c = v_c;
  };
  double v_c() const {
    return _v_c;
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
  double _Pnom = 500000; //peak power
  std::string _profileFileName = "NoName";//file where matrix is stored
  std::string _profileName = "NoName"; //table name on file
  double _v_s = 5;//start wind speed
  double _v_r = 10;//rated wind speed
  double _v_c = 17;//cut wind speed

  modelicaUnit _Vnom_displayUnit = modelicaUnit::V;
  modelicaUnit _Pnom_displayUnit = modelicaUnit::W;
};

} /* namespace Generations */

} /* namespace PhasorSinglePhase */

} /* namespace ModPowerSystems */

#endif /* SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_PHASORSINGLEPHASE_GENERATIONS_WINDGENERATOR_H_ */
