/*
 * GenericGenerator.h
 *
 */

#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_GENERATIONS_GENERICGENERATOR_H_
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_GENERATIONS_GENERICGENERATOR_H_

#include "../../../ModBaseClass.h"

using namespace ModelicaWorkshop;

namespace ModPowerSystems {

namespace SinglePhase {

namespace Generations {

class GenericGenerator : public ModBaseClass {
 public:
  GenericGenerator();
  virtual ~GenericGenerator();

  bool set_template_values(ctemplate::TemplateDictionary *dictionary) override;
};

} /* namespace Generations */

} /* namespace SinglePhase */

} /* namespace ModPowerSystems */

#endif /* SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_GENERATIONS_GENERICGENERATOR_H_ */
