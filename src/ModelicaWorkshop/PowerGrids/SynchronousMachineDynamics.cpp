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

                //UNom = {{VNOM}},

                dictionary->SetFormattedValue("VNOM", "%.3f", this->get_VNom());
                dictionary->SetFormattedValue("VSTART", "%.3f", this->get_UStart());
                dictionary->SetFormattedValue("PGEN", "%.3f", this->get_PStart());
                dictionary->SetFormattedValue("QGEN", "%.3f", this->get_QStart());
                dictionary->SetFormattedValue("SNOM", "%.3f", this->get_SNom());
                dictionary->SetFormattedValue("TPDO", "%.3f", this->get_Tpd0());
                dictionary->SetFormattedValue("TPPDO", "%.3f", this->get_Tppd0());
                dictionary->SetFormattedValue("TPPQO", "%.3f", this->get_Tppq0());
                dictionary->SetFormattedValue("TPQO", "%.3f", this->get_Tpq0());

                dictionary->SetFormattedValue("VANGLE", "%.3f", this->get_UPhaseStart());
                dictionary->SetFormattedValue("RAPU", "%.3f", this->get_raPu());
                dictionary->SetFormattedValue("XDPU", "%.3f", this->get_xdPu());
                dictionary->SetFormattedValue("XLPU", "%.3f", this->get_xIPu());
                dictionary->SetFormattedValue("XPDPU", "%.3f", this->get_xpdPu());
                dictionary->SetFormattedValue("XPPDPU", "%.3f", this->get_xppdPu());
                dictionary->SetFormattedValue("XPPQPU", "%.3f", this->get_xppqPu());
                dictionary->SetFormattedValue("XPPQPU", "%.3f", this->get_xppqPu());
                dictionary->SetFormattedValue("XPQPU", "%.3f", this->get_xpqPu());
                dictionary->SetFormattedValue("XQPU", "%.3f", this->get_xqPu());

                this->set_template_annotation_values(dictionary);
                return true;
            }


} /* namespace PowerGrids*/
