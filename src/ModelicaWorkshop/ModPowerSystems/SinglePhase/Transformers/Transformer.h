/*
 * Transformer.h
 *
 */

#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_TRANSFORMERS_TRANSFORMER_H_
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_TRANSFORMERS_TRANSFORMER_H_

#include "../../../ModBaseClass.h"
#include <cmath>

using namespace ModelicaWorkshop;

namespace ModPowerSystems {

namespace SinglePhase {

namespace Transformers {

class Transformer : public ModelicaWorkshop::ModBaseClass {
 public:
  Transformer();
  Transformer(const Transformer &);
  virtual ~Transformer();

  void set_Vnom1(double Vnom1) {
    this->_Vnom1 = Vnom1;
  };
  double Vnom1() const {
    return _Vnom1;
  };

  void set_Vnom2(double Vnom2) {
    this->_Vnom2 = Vnom2;
  };
  double Vnom2() const {
    return _Vnom2;
  };

  void set_Sr(double Sr) {
    this->_Sr = Sr;
  };
  double Sr() const {
    return _Sr;
  };

  void set_URr(double URr) {
    this->_URr = URr;
  };
  double URr() const {
    return _URr;
  };
  void calc_URr() {
    _URr = _r*(_Sr*100)/(_Vnom1*_Vnom1);
  };

  void set_Ukr(double Ukr) {
    this->_Ukr = Ukr;
  };
  double Ukr() const {
    return _Ukr;
  };
  void calc_Ukr() {
    this->calc_z();
    _Ukr = _z*(_Sr*100)/(_Vnom1*_Vnom1);
  };

  void set_Vnom1_displayUnit(modelicaUnit Vnom1_displayUnit) {
    this->_Vnom1_displayUnit = Vnom1_displayUnit;
  }
  ;
  modelicaUnit Vnom1_displayUnit() const {
    return _Vnom1_displayUnit;
  };

  void set_Vnom2_displayUnit(modelicaUnit Vnom2_displayUnit) {
    this->_Vnom2_displayUnit = Vnom2_displayUnit;
  };
  modelicaUnit Vnom2_displayUnit() const {
    return _Vnom2_displayUnit;
  };

  void set_Sr_displayUnit(modelicaUnit Sr_displayUnit) {
    this->_Sr_displayUnit = Sr_displayUnit;
  };
  modelicaUnit Sr_displayUnit() const {
    return _Sr_displayUnit;
  };

  void set_z(double z) {
    this->_z = z;
  };
  double z() const {
    return _z;
  };
  void calc_z() {
    _z = sqrt(_x*_x + _r*_r);
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

  bool set_template_values(ctemplate::TemplateDictionary *dictionary) override;


 private:

  double _Vnom1 = 110000;  //primary voltage level
  double _Vnom2 = 20000;  //secondary voltage level
  double _Sr = 40000;  //rated apparent power
  double _URr = 0.31;  //copper losses
  double _Ukr = 12.04;  //short circuit voltage

  double _z = 1;
  double _r = 0;
  double _x = 0;
  double _b = 0;
  double _g = 0;

  modelicaUnit _Vnom1_displayUnit = modelicaUnit::V;
  modelicaUnit _Vnom2_displayUnit = modelicaUnit::V;
  modelicaUnit _Sr_displayUnit = modelicaUnit::W;
};

} /* namespace Transformers */

} /* namespace SinglePhase */

} /* namespace ModPowerSystems */

#endif /* SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_TRANSFORMERS_TRANSFORMER_H_ */
