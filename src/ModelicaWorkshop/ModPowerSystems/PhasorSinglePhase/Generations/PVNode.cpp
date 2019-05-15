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
                dictionary->SetValue("PGEN_DISPLAYUNIT", (ModelicaUnit[this->getPgen_displayUnit()]));
                dictionary->SetValue("VNOM_DISPLAYUNIT", (ModelicaUnit[this->getVnom_displayUnit()]));
                dictionary->SetValue("VABS_DISPLAYUNIT", (ModelicaUnit[this->getVabs_displayUnit()]));

                this->set_template_annotation_values(dictionary);
                return true;
            }

        } /* namespace Generations */

    } /* namespace PhasorSinglePhase */

} /* namespace ModPowerSystems */
