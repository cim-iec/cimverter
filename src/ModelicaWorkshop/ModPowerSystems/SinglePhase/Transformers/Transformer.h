/*
 * Transformer.h
 *
 */

#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_TRANSFORMERS_TRANSFORMER_H_
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_TRANSFORMERS_TRANSFORMER_H_

#include "../../../ModBaseClass.h"

using namespace ModelicaWorkshop;

namespace ModPowerSystems {

namespace SinglePhase {

namespace Transformers {

class Transformer : public ModelicaWorkshop::ModBaseClass {
 public:
  Transformer();
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

  void set_Ukr(double Ukr) {
    this->_Ukr = Ukr;
  };
  double Ukr() const {
    return _Ukr;
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

  bool set_template_values(ctemplate::TemplateDictionary *dictionary) override;

  static int count() {
    return Transformer::_count;
  };

 private:
  static int _count;

  double _Vnom1 = 110000;  //primary voltage level
  double _Vnom2 = 20000;  //secondary voltage level
  double _Sr = 40000000;  //rated apparent power
  double _URr = 0.31;  //copper losses
  double _Ukr = 12.04;  //short circuit voltage

  modelicaUnit _Vnom1_displayUnit = modelicaUnit::V;
  modelicaUnit _Vnom2_displayUnit = modelicaUnit::V;
  modelicaUnit _Sr_displayUnit = modelicaUnit::W;
};

} /* namespace Transformers */

} /* namespace SinglePhase */

} /* namespace ModPowerSystems */

#endif /* SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_TRANSFORMERS_TRANSFORMER_H_ */
