/*
 * Battery.h
 *
 */

#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_PHASORSINGLEPHASE_STORAGE_BATTERY_H_
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_PHASORSINGLEPHASE_STORAGE_BATTERY_H_

#include "../../../ModBaseClass.h"
#include <string>

using namespace ModelicaWorkshop;

/*
 * Battery Type
 * Type0 : Ideal battery storage with no losses
 * Type1 : Battery storage including losses due to charging efficiency and self-discharge
 *
 */
enum class BatteryType {
  Type0, Type1
};

namespace ModPowerSystems {
namespace PhasorSinglePhase {
namespace Storage {

class Battery : public ModBaseClass {
 public:
  Battery();
  Battery(enum BatteryType Type);
  Battery(const Battery &);
  Battery & operator=(const Battery &);
  virtual ~Battery();

  void set_BatteryType(enum BatteryType Type) {
    this->_Type = Type;
  };
  enum BatteryType BatteryType() const {
    return _Type;
  };
  void set_Vnom(double Vnom) {
    this->_Vnom = Vnom;
  };
  double Vnom() const {
    return _Vnom;
  };
  void set_Cnom(double Cnom) {
    this->_Cnom = Cnom;
  };
  double Cnom() const {
    return _Cnom;
  };
  void set_SOC_start(double SOC_start) {
    this->_SOC_start = SOC_start;
  };
  double SOC_start() const {
    return _SOC_start;
  };
  void set_enableOutputWbat(bool enableOutputWbat) {
    this->_enableOutputWbat = enableOutputWbat;
  };
  std::string enableOutputWbat() const {
    if(this->_enableOutputWbat)
      return "true";
    else
      return "false";
  };
  void set_eta_ch(double eta_ch) {
    this->_eta_ch = eta_ch;
  };
  double eta_ch() const {
    return _eta_ch;
  };
  void set_eta_disch(double eta_disch) {
    this->_eta_disch = eta_disch;
  };
  double eta_disch() const {
    return _eta_disch;
  };
  void set_Vnom_displayUnit(modelicaUnit Vnom_displayUnit) {
    this->_Vnom_displayUnit = Vnom_displayUnit;
  };
  modelicaUnit Vnom_displayUnit() const {
    return _Vnom_displayUnit;
  };
  void set_Cnom_displayUnit(modelicaUnit Cnom_displayUnit) {
    this->_Cnom_displayUnit = Cnom_displayUnit;
  };
  modelicaUnit Cnom_displayUnit() const {
    return _Cnom_displayUnit;
  };
  void set_SOC_displayUnit(modelicaUnit SOC_displayUnit) {
    this->_SOC_displayUnit = SOC_displayUnit;
  };
  modelicaUnit SOC_displayUnit() const {
    return _SOC_displayUnit;
  };

  bool set_template_values(ctemplate::TemplateDictionary *dictionary) override;

 private:

  enum BatteryType _Type = BatteryType::Type0;
  //Type0
  double _Cnom = 5000; //usable battery capacity in Wh;
  bool _enableOutputWbat = false;
  double _Vnom = 0;//battery charging power;
  double _SOC_start = 0;//state of charge

  //Type1
  double _eta_ch = 0.9;//charging efficiency
  double _eta_disch = 0.9;//discharging efficiency

  modelicaUnit _Vnom_displayUnit = modelicaUnit::W;
  modelicaUnit _Cnom_displayUnit = modelicaUnit::Wh;
  modelicaUnit _SOC_displayUnit = modelicaUnit::Wh;
};

} /* namespace Storage */
} /* namespace PhasorSinglePhase */
} /* namespace ModPowerSystems */

#endif /* SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_PHASORSINGLEPHASE_STORAGE_BATTERY_H_ */
