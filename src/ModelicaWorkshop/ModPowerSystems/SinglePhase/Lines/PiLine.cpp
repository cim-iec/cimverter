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

        this->set_template_annotation_values(dictionary);


				return true;
			}

		} /* namespace Lines */

	} /* namespace SinglePhase */

} /* namespace ModPowerSystems */
