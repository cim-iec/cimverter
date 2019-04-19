#include "PVNode.h"

namespace ModPowerSystems {

    namespace PhasorSinglePhase {

        namespace Generations {

            PVNode::PVNode() {
                // TODO Auto-generated constructor stub

            }

            PVNode::~PVNode() {
                // TODO Auto-generated destructor stub
            }

            bool PVNode::set_template_values(ctemplate::TemplateDictionary *dictionary) {

                dictionary->SetValue("NAME", this->name());
                this->set_template_annotation_values(dictionary);

                return true;
            }

        } /* namespace Generations */

    } /* namespace PhasorSinglePhase */

} /* namespace ModPowerSystems */
