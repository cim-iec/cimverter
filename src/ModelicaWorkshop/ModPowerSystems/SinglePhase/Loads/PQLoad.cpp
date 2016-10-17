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

					std::map<const kPQLoadEnum, const std::string> PQLoad::tplKeys = PQLoad::initial_tplKeys();

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

						dictionary->SetValue(tplKeys[kPQLoadEnum::NAME],this->name());
						dictionary->SetFormattedValue(tplKeys[kPQLoadEnum::PNOM],"%.2f",this->Pnom());
						dictionary->SetFormattedValue(tplKeys[kPQLoadEnum::QNOM],"%.2f",this->Qnom());
						dictionary->SetFormattedValue(tplKeys[kPQLoadEnum::VNOM],"%.2f",this->Vnom());

						dictionary->SetValue(tplKeys[kPQLoadEnum::PNOM_DISPLAYUNIT],(ModelicaUnit[this->Pnom_displayUnit()]));
						dictionary->SetValue(tplKeys[kPQLoadEnum::QNOM_DISPLAYUNIT],(ModelicaUnit[this->Qnom_displayUnit()]));
						dictionary->SetValue(tplKeys[kPQLoadEnum::VNOM_DISPLAYUNIT],(ModelicaUnit[this->Vnom_displayUnit()]));

						dictionary->SetFormattedValue(tplKeys[kPQLoadEnum::TRANS_EXTENT_X1],"%.1f",this->annotation.placement.transfomation.extent.first.x);
						dictionary->SetFormattedValue(tplKeys[kPQLoadEnum::TRANS_EXTENT_Y1],"%.1f",this->annotation.placement.transfomation.extent.first.y);
						dictionary->SetFormattedValue(tplKeys[kPQLoadEnum::TRANS_EXTENT_X2],"%.1f",this->annotation.placement.transfomation.extent.second.x);
						dictionary->SetFormattedValue(tplKeys[kPQLoadEnum::TRANS_EXTENT_Y2],"%.1f",this->annotation.placement.transfomation.extent.second.y);
						dictionary->SetFormattedValue(tplKeys[kPQLoadEnum::ORIGIN_X],"%.1f",this->annotation.placement.transfomation.origin.x);
						dictionary->SetFormattedValue(tplKeys[kPQLoadEnum::ORIGIN_Y],"%.1f",this->annotation.placement.transfomation.origin.y);
						dictionary->SetIntValue(tplKeys[kPQLoadEnum::ROTATION],this->annotation.placement.transfomation.rotation);
						dictionary->SetFormattedValue(tplKeys[kPQLoadEnum::VISIBLE],"%s",this->annotation.placement.visible ? "true":"false");

						return true;
					}

					/**
					 * Initialize the Template Markers map of PQLoad
					*/
					std::map<const kPQLoadEnum, const std::string> PQLoad::initial_tplKeys(){

						auto tmp_tplKeys = std::map<const kPQLoadEnum, const std::string>();
						tmp_tplKeys.insert(std::make_pair(kPQLoadEnum::NAME,"NAME"));
						tmp_tplKeys.insert(std::make_pair(kPQLoadEnum::PNOM,"PNOM"));
						tmp_tplKeys.insert(std::make_pair(kPQLoadEnum::QNOM,"QNOM"));
						tmp_tplKeys.insert(std::make_pair(kPQLoadEnum::VNOM,"VNOM"));
						tmp_tplKeys.insert(std::make_pair(kPQLoadEnum::PNOM_DISPLAYUNIT,"PNOM_DISPLAYUNIT"));
						tmp_tplKeys.insert(std::make_pair(kPQLoadEnum::QNOM_DISPLAYUNIT,"QNOM_DISPLAYUNIT"));
						tmp_tplKeys.insert(std::make_pair(kPQLoadEnum::VNOM_DISPLAYUNIT,"VNOM_DISPLAYUNIT"));

						tmp_tplKeys.insert(std::make_pair(kPQLoadEnum::VISIBLE,"VISIBLE"));
						tmp_tplKeys.insert(std::make_pair(kPQLoadEnum::TRANS_EXTENT_X1,"TRANS_EXTENT_X1"));
						tmp_tplKeys.insert(std::make_pair(kPQLoadEnum::TRANS_EXTENT_Y1,"TRANS_EXTENT_Y1"));
						tmp_tplKeys.insert(std::make_pair(kPQLoadEnum::TRANS_EXTENT_X2,"TRANS_EXTENT_X2"));
						tmp_tplKeys.insert(std::make_pair(kPQLoadEnum::TRANS_EXTENT_Y2,"TRANS_EXTENT_Y2"));
						tmp_tplKeys.insert(std::make_pair(kPQLoadEnum::ORIGIN_X,"ORIGIN_X"));
						tmp_tplKeys.insert(std::make_pair(kPQLoadEnum::ORIGIN_Y,"ORIGIN_Y"));
						tmp_tplKeys.insert(std::make_pair(kPQLoadEnum::ROTATION,"ROTATION"));

						return tmp_tplKeys;
					}


				} /* namespace Loads */

		} /* namespace SinglePhase */

} /* namespace ModPowerSystems */
