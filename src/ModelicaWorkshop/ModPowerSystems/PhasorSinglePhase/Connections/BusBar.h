/*
 * BusBar.h
 *
 */

#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_PHASORSINGLEPHASE_CONNECTIONS_BUSBAR_H_
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_PHASORSINGLEPHASE_CONNECTIONS_BUSBAR_H_

#include "../../../ModBaseClass.h"

using namespace ModelicaWorkshop;

namespace ModPowerSystems {
namespace PhasorSinglePhase {
namespace Connections {

class BusBar : public ModBaseClass {
 public:
  BusBar();
  BusBar(const BusBar &);
  BusBar& operator=(const BusBar &);
  virtual ~BusBar();

  void set_Vnom(double Vnom) {
    this->_Vnom = Vnom;
  };
  double Vnom() const {
    return _Vnom;
  };
  void set_Vnom_displayUnit(modelicaUnit Vnom_displayUnit) {
    this->_Vnom_displayUnit = Vnom_displayUnit;
  };
  modelicaUnit Vnom_displayUnit() const {
    return _Vnom_displayUnit;
  };

  bool set_template_values(ctemplate::TemplateDictionary *dictionary) override;

 private:
  double _Vnom = 0;//nominal Voltage
  modelicaUnit _Vnom_displayUnit = modelicaUnit::V;

};

}/* namespace Connections */

}/* namespace PhasorSinglePhase */

} /* namespace ModPowersystems */

#endif /* SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_PHASORSINGLEPHASE_CONNECTIONS_H_ */
