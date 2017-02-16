/*
 * GenericGenerator.h
 *
 */

#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_PHASORSINGLEPHASE_GENERATIONS_GENERICGENERATOR_H_
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_PHASORSINGLEPHASE_GENERATIONS_GENERICGENERATOR_H_

#include "../../../ModBaseClass.h"

using namespace ModelicaWorkshop;

namespace ModPowerSystems {

namespace PhasorSinglePhase {

namespace Generations {

class GenericGenerator : public ModBaseClass {
 public:
  GenericGenerator();
  virtual ~GenericGenerator();

  bool set_template_values(ctemplate::TemplateDictionary *dictionary) override;
};

} /* namespace Generations */

} /* namespace PhasorSinglePhase */

} /* namespace ModPowerSystems */

#endif /* SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_PHASORSINGLEPHASE_GENERATIONS_GENERICGENERATOR_H_ */
