#include "SynchronousMachineDynamics.h"

namespace PowerGrids {


            SynchronousMachineDynamics::SynchronousMachineDynamics() {
                // TODO Auto-generated constructor stub

            }

            SynchronousMachineDynamics::~SynchronousMachineDynamics() {
                // TODO Auto-generated destructor stub
            }

            bool SynchronousMachineDynamics::set_template_values(ctemplate::TemplateDictionary *dictionary) {

                dictionary->SetValue("NAME", this->name());

                this->set_template_annotation_values(dictionary);
                return true;
            }


} /* namespace PowerGrids*/
