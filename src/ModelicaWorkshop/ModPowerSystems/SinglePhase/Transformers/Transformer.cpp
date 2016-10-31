/*
 * Transformer.cpp
 */

#include "Transformer.h"

namespace ModPowerSystems {

		namespace SinglePhase {

			namespace Transformers {

				Transformer::Transformer() {
					// TODO Auto-generated constructor stub

				}

				Transformer::~Transformer() {
					// TODO Auto-generated destructor stub
				}

				bool Transformer::set_template_values(ctemplate::TemplateDictionary *dictionary) {

					dictionary->SetValue(NAME,this->name());
					dictionary->SetFormattedValue(VNOM1,"%.2f",this->Vnom1());
					dictionary->SetValue(VNOM1_DISPLAYUNIT,(ModelicaUnit[this->Vnom1_displayUnit()]));
					dictionary->SetFormattedValue(VNOM2,"%.2f",this->Vnom2());
					dictionary->SetValue(VNOM2_DISPLAYUNIT,(ModelicaUnit[this->Vnom2_displayUnit()]));
					dictionary->SetFormattedValue(SR,"%.f",this->Sr());
					dictionary->SetValue(SR_DISPLAYUNIT,(ModelicaUnit[this->Sr_displayUnit()]));
					dictionary->SetFormattedValue(URR,"%.2f",this->URr());
					dictionary->SetFormattedValue(UKR,"%.2f",this->Ukr());

					dictionary->SetFormattedValue(TRANS_EXTENT_X1,"%.1f",this->annotation.placement.transfomation.extent.first.x);
					dictionary->SetFormattedValue(TRANS_EXTENT_Y1,"%.1f",this->annotation.placement.transfomation.extent.first.y);
					dictionary->SetFormattedValue(TRANS_EXTENT_X2,"%.1f",this->annotation.placement.transfomation.extent.second.x);
					dictionary->SetFormattedValue(TRANS_EXTENT_Y2,"%.1f",this->annotation.placement.transfomation.extent.second.y);
					dictionary->SetFormattedValue(ORIGIN_X,"%.1f",this->annotation.placement.transfomation.origin.x);
					dictionary->SetFormattedValue(ORIGIN_Y,"%.1f",this->annotation.placement.transfomation.origin.y);
					dictionary->SetIntValue(ROTATION,this->annotation.placement.transfomation.rotation);
					dictionary->SetFormattedValue(VISIBLE,"%s",this->annotation.placement.visible ? "true":"false");

					return true;
				}


			} /* namespace Transformers */

		} /* namespace SinglePhase */

} /* namespace ModPowerSystems */
