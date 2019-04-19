
#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_PHASORSINGLEPHASE_GENERATIONS
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_PHASORSINGLEPHASE_GENERATIONS
#include "../../../ModBaseClass.h"

namespace ModPowerSystems {

    namespace PhasorSinglePhase {

        namespace Generations {

            class PVNode: public ModBaseClass {
            public:
                PVNode();
                virtual ~PVNode();

                bool set_template_values(ctemplate::TemplateDictionary *dictionary) override;
            };

        } /* namespace Generations */

    } /* namespace PhasorSinglePhase */

} /* namespace ModPowerSystems */

#endif //SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_PHASORSINGLEPHASE_GENERATIONS _PVNODE_H
