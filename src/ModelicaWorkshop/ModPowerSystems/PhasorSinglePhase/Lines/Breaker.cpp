#include "Breaker.h"

namespace ModPowerSystems {

    namespace PhasorSinglePhase {

        namespace Lines {

            Breaker::Breaker() {
                // TODO Auto-generated constructor stub

            }

            Breaker::~Breaker() {
                // TODO Auto-generated destructor stub
            }

            bool Breaker::set_template_values(ctemplate::TemplateDictionary *dictionary) {
                dictionary->SetValue("NAME", this->name());
                dictionary->SetIntValue("ISCLOSED", this->isClosed());
                this->set_template_annotation_values(dictionary);
                return true;
            }

        } /* namespace Lines */

    } /* namespace PhasorSinglePhase */

} /* namespace ModPowerSystems */
