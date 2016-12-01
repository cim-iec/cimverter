/*
 * ZLoad.h
 * Constant impedance load
 */

#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_LOADS_ZLOAD_H_
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_LOADS_ZLOAD_H_

#include "../../../ModBaseClass.h"

using namespace ModelicaWorkshop;

/*
 * ZLoad Type
 * Standard : Constant Impedance Load
 * Profile : Constant Impedance Load
 * Profile_sinus : Constant Impedance Load
 */
enum class ZLoadType {
  Standard, Profile, Profile_sinus
};

enum smoothnessEnum {
  LinearSegments,
  ContinuousDerivative,
  ConstantSegments,
  MonotoneContinuousDerivative1,
  MonotoneContinuousDerivative2
};

static std::map<const smoothnessEnum, const std::string> Smoothness {
  { smoothnessEnum::LinearSegments, "Modelica.Blocks.Types.Smoothness.LinearSegments" },
  { smoothnessEnum::ContinuousDerivative, "Modelica.Blocks.Types.Smoothness.ContinuousDerivative" },
  { smoothnessEnum::ConstantSegments, "Modelica.Blocks.Types.Smoothness.ConstantSegments" },
  { smoothnessEnum::MonotoneContinuousDerivative1, "Modelica.Blocks.Types.Smoothness.MonotoneContinuousDerivative1" },
  { smoothnessEnum::MonotoneContinuousDerivative2, "Modelica.Blocks.Types.Smoothness.MonotoneContinuousDerivative2" },
};

namespace ModPowerSystems {

namespace SinglePhase {

namespace Loads {

class ZLoad : public ModBaseClass {
 public:
  ZLoad();
  ZLoad(enum ZLoadType Type);
  ZLoad(enum ZLoadType Type, std::string profileFileName, std::string profileName);
  ZLoad(std::string profileFileName, std::string profileName);
  ZLoad(const ZLoad &);
  ZLoad& operator=(const ZLoad &);

  virtual ~ZLoad();

  void ZLoadType(enum ZLoadType Type) {
    this->_Type = Type;
  };
  enum ZLoadType ZLoadType() const {
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
  void set_smoothnessSetting(smoothnessEnum smoothnessSetting) {
    this->_smoothnessSetting = smoothnessSetting;
  };
  smoothnessEnum smoothness() const {
    return _smoothnessSetting;
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

  bool set_template_values(ctemplate::TemplateDictionary *dictionary) override;

 private:

  enum ZLoadType _Type = ZLoadType::Standard;

  //Parameters
  double _Pnom = 110000;  //active power per phase
  double _Qnom;  //reactive power per phase
  double _Vnom;  //nominal voltage level

  //ZLoadProfile Parameters
  std::string _profileFileName = "NoName"; //File where matrix is stored
  std::string _profileName ="NoName"; //Table name on file
  smoothnessEnum _smoothnessSetting = LinearSegments; //Smoothness of table interpolation

  modelicaUnit _Pnom_displayUnit = modelicaUnit::W;
  modelicaUnit _Qnom_displayUnit = modelicaUnit::var;
  modelicaUnit _Vnom_displayUnit = modelicaUnit::V;

};

} /* namespace Loads */

} /* namespace SinglePhase */

} /* namespace ModPowerSystems */

#endif /* SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_LOADS_ZLOAD_H_ */
