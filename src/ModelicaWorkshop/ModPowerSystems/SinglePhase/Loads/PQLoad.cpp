/*
 * PQLoad.cpp
 *
 *  Created on: Sep 14, 2016
 *      Author: root
 */

#include "PQLoad.h"

namespace ModPowerSystems {

		namespace SinglePhase {

				namespace Loads {

					int PQLoad::_count(0);

					PQLoad::PQLoad()
					{
						++_count;
					}

					PQLoad::~PQLoad()
					{
						--_count;
					}

					bool PQLoad::set_template_values(ctemplate::TemplateDictionary *dictionary)
					{

						dictionary->SetValue(NAME,this->name());
						dictionary->SetFormattedValue(PNOM,"%.2f",this->Pnom());
						dictionary->SetFormattedValue(QNOM,"%.2f",this->Qnom());
						dictionary->SetFormattedValue(VNOM,"%.2f",this->Vnom());

						dictionary->SetValue(PNOM_DISPLAYUNIT,(ModelicaUnit[this->Pnom_displayUnit()]));
						dictionary->SetValue(QNOM_DISPLAYUNIT,(ModelicaUnit[this->Qnom_displayUnit()]));
						dictionary->SetValue(VNOM_DISPLAYUNIT,(ModelicaUnit[this->Vnom_displayUnit()]));
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

				} /* namespace Loads */

		} /* namespace SinglePhase */

} /* namespace ModPowerSystems */
