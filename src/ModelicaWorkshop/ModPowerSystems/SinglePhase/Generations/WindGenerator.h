/*
 * WindGenerator.h
 *
 */

#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_GENERATIONS_WINDGENERATOR_H_
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_GENERATIONS_WINDGENERATOR_H_

#include "../../../ModBaseClass.h"

namespace ModPowerSystems {

namespace SinglePhase {

namespace Generations {

class WindGenerator : public ModelicaWorkshop::ModBaseClass {
 public:
  WindGenerator();
  virtual ~WindGenerator();
};

} /* namespace Generations */

} /* namespace SinglePhase */

} /* namespace ModPowerSystems */

#endif /* SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_GENERATIONS_WINDGENERATOR_H_ */
