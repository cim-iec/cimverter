/*
 * Slack.cpp
 *
 *  Created on: Sep 14, 2016
 *      Author: root
 */

#include "Slack.h"

namespace ModPowerSystems {

		namespace SinglePhase {

				namespace Sources {

					Slack::Slack() : _Vnom(110000)
					{
					}

					Slack::~Slack() {
					}

					bool Slack::set_template_values(ctemplate::TemplateDictionary *dictionary)
					{

						dictionary->SetFormattedValue(VNOM,"%.2f",this->Vnom());
						dictionary->SetValue(NAME,this->name());
						dictionary->SetValue(VNOM_DISPLAYUNIT,(ModelicaUnit[this->Vnom_displayUnit()]));
						dictionary->SetFormattedValue(FREQUENCY,"%.1f",this->frequency());
						dictionary->SetValue(FREQUENCY_DISPLAYUNIT,(ModelicaUnit[this->frequency_displayUnit()]));
						dictionary->SetFormattedValue(PHIV,"%.2f",this->phiV());
						dictionary->SetValue(PHIV_DISPLAYUNIT,(ModelicaUnit[this->phiV_displayUnit()]));

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

				} /* namespace Sources */

		} /* namespace SinglePhase */

} /* namespace ModPowerSystems */
