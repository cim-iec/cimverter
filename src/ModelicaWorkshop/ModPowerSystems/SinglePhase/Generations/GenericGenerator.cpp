/*
 * GenericGenerator.cpp
 *
 */

#include "GenericGenerator.h"

namespace ModPowerSystems {

		namespace SinglePhase {

			namespace Generations {

				GenericGenerator::GenericGenerator()
				{
						// TODO Auto-generated constructor stub

				}

				GenericGenerator::~GenericGenerator()
				{
						// TODO Auto-generated destructor stub
				}

				bool GenericGenerator::set_template_values(ctemplate::TemplateDictionary *dictionary){

					dictionary->SetValue(NAME,this->name());
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

			} /* namespace Generations */

		} /* namespace SinglePhase */

} /* namespace ModPowerSystems */
