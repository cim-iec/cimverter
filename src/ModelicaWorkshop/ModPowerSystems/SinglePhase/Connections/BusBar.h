/*
 * BusBar.h
 *
 */

#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_CONNECTIONS_BUSBAR_H_
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_CONNECTIONS_BUSBAR_H_

#include "../../../ModBaseClass.h"

using namespace ModelicaWorkshop;

namespace ModPowerSystems {
namespace SinglePhase {
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

  bool set_template_values(ctemplate::TemplateDictionary *dictionary) override;

 private:
  double _Vnom;
};

}/* namespace Connections */

}/* namespace SinglePhase */

} /* namespace ModPowersystems */

#endif /* SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_CONNECTIONS_H_ */
