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
                dictionary->SetFormattedValue("PGEN", "%.3f", this->Pgen());
                dictionary->SetFormattedValue("VABS", "%.3f", this->Vabs());
                dictionary->SetFormattedValue("VNOM", "%.3f", this->Vnom());

                this->set_template_annotation_values(dictionary);
                return true;
            }

        } /* namespace Generations */

    } /* namespace PhasorSinglePhase */

} /* namespace ModPowerSystems */
