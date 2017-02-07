/*
 * RxLine.h
 *
 */

#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_LINES_RXLINE_H_
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_LINES_RXLINE_H_

#include "../../../ModBaseClass.h"

using namespace ModelicaWorkshop;

namespace ModPowerSystems {

namespace SinglePhase {

namespace Lines {

class RxLine : public ModelicaWorkshop::ModBaseClass {
 public:
  RxLine();
  RxLine(const RxLine &);
  RxLine& operator=(const RxLine &);
  virtual ~RxLine();

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
    double _length = 0;  //Length of line in km
    double _r = 0;  //Series Resistance per km
    double _x = 0;  //Series Reactance per km

    modelicaUnit _r_displayUnit = modelicaUnit::Ohm;
    modelicaUnit _x_displayUnit = modelicaUnit::Ohm;
};

} /* namespace Lines */

} /* namespace SinglePhase */

} /* namespace ModPowerSystems */

#endif /* SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_LINES_RXLINE_H_ */
