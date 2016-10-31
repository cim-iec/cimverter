/*
 * PiLine.cpp
 *
 *  Created on: Sep 14, 2016
 *      Author: root
 */

#include "PiLine.h"

namespace ModPowerSystems {

	namespace SinglePhase {

		namespace Lines {

			PiLine::PiLine() {
				// TODO Auto-generated constructor stub

			}

			PiLine::~PiLine() {
				// TODO Auto-generated destructor stub
			}

			bool PiLine::set_template_values(ctemplate::TemplateDictionary *dictionary)
			{

				dictionary->SetValue(NAME,this->name());
				dictionary->SetFormattedValue(LENGTH,"%.2f",this->length());
				dictionary->SetFormattedValue(IMAX,"%.2f",this->Imax());
				dictionary->SetFormattedValue(R,"%.2f",this->r());
				dictionary->SetFormattedValue(X,"%.2f",this->x());
				dictionary->SetFormattedValue(B,"%.2f",this->b());
				dictionary->SetFormattedValue(G,"%.f",this->g());
				dictionary->SetFormattedValue(SR,"%.f",this->Sr());
				dictionary->SetValue(IMAX_DISPLAYUNIT,(ModelicaUnit[this->Imax_displayUnit()]));
				dictionary->SetValue(SR_DISPLAYUNIT,(ModelicaUnit[this->Sr_displayUnit()]));

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

		} /* namespace Lines */

	} /* namespace SinglePhase */

} /* namespace ModPowerSystems */
