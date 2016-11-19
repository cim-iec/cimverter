/*
 * Slack.h
 *
 * The slack node represents the rest of the grid with higher voltage levels. It is
 assumed that the slack node is an infinite source of power.
 */

#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_SOURCES_SLACK_H_
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_SOURCES_SLACK_H_

#include "../../../ModBaseClass.h"

using namespace ModelicaWorkshop;

namespace ModPowerSystems {

namespace SinglePhase {

namespace Sources {

class Slack : public ModBaseClass {
 public:

  Slack();
  Slack(const Slack &);
  virtual ~Slack();

  void set_Vnom(double Vnom) {
    this->_Vnom = Vnom;
  };
  double Vnom() const {
    return _Vnom;
  };

  void set_frequency(double frequency) {
    this->_frequency = frequency;
  };
  double frequency() const {
    return _frequency;
  };

  void set_phiV(double phiV) {
    this->_phiV = phiV;
  };
  double phiV() const {
    return _phiV;
  };

  void set_Vnom_displayUnit(modelicaUnit Vnom_displayUnit) {
    this->_Vnom_displayUnit = Vnom_displayUnit;
  };
  modelicaUnit Vnom_displayUnit() const {
    return _Vnom_displayUnit;
  };

  void set_frequency_displayUnit(modelicaUnit frequency_displayUnit) {
    this->_frequency_displayUnit = frequency_displayUnit;
  };
  modelicaUnit frequency_displayUnit() const {
    return _frequency_displayUnit;
  };

  void set_phiV_displayUnit(modelicaUnit phiV_displayUnit) {
    this->_phiV_displayUnit = phiV_displayUnit;
  };
  modelicaUnit phiV_displayUnit() const {
    return _phiV_displayUnit;
  };

  bool set_template_values(ctemplate::TemplateDictionary *dictionary) override;

 private:

  double _Vnom;
  double _frequency = 50;  //Frequency
  double _phiV = 0;  //Initial Voltage Angle
  modelicaUnit _Vnom_displayUnit = modelicaUnit::V;
  modelicaUnit _frequency_displayUnit = modelicaUnit::Hz;
  modelicaUnit _phiV_displayUnit = modelicaUnit::rad;

};

} /* namespace Sources */

} /* namespace SinglePhase */

} /* namespace ModPowerSystems */

#endif /* SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_SOURCES_SLACK_H_ */
