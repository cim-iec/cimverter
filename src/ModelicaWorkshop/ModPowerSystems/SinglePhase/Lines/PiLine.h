/*
 * PiLine.h
 *
 */

#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_LINES_PILINE_H_
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_LINES_PILINE_H_

#include "../../../ModBaseClass.h"

using namespace ModelicaWorkshop;

namespace ModPowerSystems {

namespace SinglePhase {

namespace Lines {

class PiLine : public ModelicaWorkshop::ModBaseClass {
 public:
  PiLine();
  PiLine(const PiLine &);
  virtual ~PiLine();

  void set_length(double length) {
    this->_length = length;
  };
  double length() const {
    return _length;
  };

  void set_r(double r) {
    this->_r = r;
  };
  double r() const {
    return _r;
  };

  void set_x(double x) {
    this->_x = x;
  };
  double x() const {
    return _x;
  };

  void set_b(double b) {
    this->_b = b;
  };
  double b() const {
    return _b;
  };

  void set_g(double g) {
    this->_g = g;
  };
  double g() const {
    return _g;
  };

  void set_Sr(double Sr) {
    this->_Sr = Sr;
  };
  double Sr() const {
    return _Sr;
  };

  void set_Imax(double Imax) {
    this->_Imax = Imax;
  };
  double Imax() const {
    return _Imax;
  };

  void set_Imax_displayUnit(modelicaUnit Imax_displayUnit) {
    this->_Imax_displayUnit = Imax_displayUnit;
  }
  ;
  modelicaUnit Imax_displayUnit() const {
    return _Imax_displayUnit;
  };

  void set_Sr_displayUnit(modelicaUnit Sr_displayUnit) {
    this->_Sr_displayUnit = Sr_displayUnit;
  };
  modelicaUnit Sr_displayUnit() const {
    return _Sr_displayUnit;
  };

  void set_g_displayUnit(modelicaUnit g_displayUnit) {
    this->_g_displayUnit = g_displayUnit;
  };
  modelicaUnit g_displayUnit() const {
    return _g_displayUnit;
  };

  void set_b_displayUnit(modelicaUnit b_displayUnit) {
    this->_b_displayUnit = b_displayUnit;
  };
  modelicaUnit b_displayUnit() const {
    return _b_displayUnit;
  };

  void set_r_displayUnit(modelicaUnit r_displayUnit) {
    this->_r_displayUnit = r_displayUnit;
  };
  modelicaUnit r_displayUnit() const {
    return _r_displayUnit;
  };

  void set_x_displayUnit(modelicaUnit x_displayUnit) {
    this->_x_displayUnit = x_displayUnit;
  };
  modelicaUnit x_displayUnit() const {
    return _x_displayUnit;
  };

  bool set_template_values(ctemplate::TemplateDictionary *dictionary) override;

 private:

  //Parameters
  double _length = 20;  //Length of line in km
  double _r;  //Series Resistance per km
  double _x;  //Series Reactance per km
  double _b = 0.000172411;  //Shunt Susceptance per km
  double _g = 0;  //Shunt Conductance per km
  double _Sr = 1;  //rated apparent power
  double _Imax = 100;  //maximal current

  modelicaUnit _Imax_displayUnit = modelicaUnit::A;
  modelicaUnit _Sr_displayUnit = modelicaUnit::W;
  modelicaUnit _g_displayUnit = modelicaUnit::S;
  modelicaUnit _b_displayUnit = modelicaUnit::S;
  modelicaUnit _r_displayUnit = modelicaUnit::Ohm;
  modelicaUnit _x_displayUnit = modelicaUnit::Ohm;
};

} /* namespace Lines */

} /* namespace SinglePhase */

} /* namespace ModPowerSystems */

#endif /* SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_LINES_PILINE_H_ */
