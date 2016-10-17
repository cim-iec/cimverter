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

					int Slack::_count(0);

					std::map<const kSlackEnum, const std::string> Slack::tplKeys = Slack::initial_tplKeys();

					Slack::Slack() : _Vnom(110000)
					{
						++_count;
					}

					Slack::~Slack() {
						--_count;
					}

					bool Slack::set_template_values(ctemplate::TemplateDictionary *dictionary)
					{

						dictionary->SetFormattedValue(tplKeys[kSlackEnum::VNOM],"%.2f",this->Vnom());
						dictionary->SetValue(tplKeys[kSlackEnum::NAME],this->name());
						dictionary->SetValue(tplKeys[kSlackEnum::VNOM_DISPLAYUNIT],(ModelicaUnit[this->Vnom_displayUnit()]));
						dictionary->SetFormattedValue(tplKeys[kSlackEnum::FREQUENCY],"%.1f",this->frequency());
						dictionary->SetValue(tplKeys[kSlackEnum::FREQUENCY_DISPLAYUNIT],(ModelicaUnit[this->frequency_displayUnit()]));
						dictionary->SetFormattedValue(tplKeys[kSlackEnum::PHIV],"%.2f",this->phiV());
						dictionary->SetValue(tplKeys[kSlackEnum::PHIV_DISPLAYUNIT],(ModelicaUnit[this->phiV_displayUnit()]));

						dictionary->SetFormattedValue(tplKeys[kSlackEnum::TRANS_EXTENT_X1],"%.1f",this->annotation.placement.transfomation.extent.first.x);
						dictionary->SetFormattedValue(tplKeys[kSlackEnum::TRANS_EXTENT_Y1],"%.1f",this->annotation.placement.transfomation.extent.first.y);
						dictionary->SetFormattedValue(tplKeys[kSlackEnum::TRANS_EXTENT_X2],"%.1f",this->annotation.placement.transfomation.extent.second.x);
						dictionary->SetFormattedValue(tplKeys[kSlackEnum::TRANS_EXTENT_Y2],"%.1f",this->annotation.placement.transfomation.extent.second.y);
						dictionary->SetFormattedValue(tplKeys[kSlackEnum::ORIGIN_X],"%.1f",this->annotation.placement.transfomation.origin.x);
						dictionary->SetFormattedValue(tplKeys[kSlackEnum::ORIGIN_Y],"%.1f",this->annotation.placement.transfomation.origin.y);
						dictionary->SetIntValue(tplKeys[kSlackEnum::ROTATION],this->annotation.placement.transfomation.rotation);
						dictionary->SetFormattedValue(tplKeys[kSlackEnum::VISIBLE],"%s",this->annotation.placement.visible ? "true":"false");

						return true;
					}

					/**
					 * Initialize the Template Markers map of Slack
					 */
					std::map<const kSlackEnum, const std::string> Slack::initial_tplKeys(){

						auto tmp_tplKeys = std::map<const kSlackEnum, const std::string>();
						tmp_tplKeys.insert(std::make_pair(kSlackEnum::NAME,"NAME"));
						tmp_tplKeys.insert(std::make_pair(kSlackEnum::VNOM,"VNOM"));
						tmp_tplKeys.insert(std::make_pair(kSlackEnum::VNOM_DISPLAYUNIT,"VNOM_DISPLAYUNIT"));
						tmp_tplKeys.insert(std::make_pair(kSlackEnum::FREQUENCY,"FREQUENCY"));
						tmp_tplKeys.insert(std::make_pair(kSlackEnum::FREQUENCY_DISPLAYUNIT,"FREQUENCY_DISPLAYUNIT"));
						tmp_tplKeys.insert(std::make_pair(kSlackEnum::PHIV_DISPLAYUNIT,"PHIV_DISPLAYUNIT"));
						tmp_tplKeys.insert(std::make_pair(kSlackEnum::PHIV,"PHIV"));
						tmp_tplKeys.insert(std::make_pair(kSlackEnum::VISIBLE,"VISIBLE"));
						tmp_tplKeys.insert(std::make_pair(kSlackEnum::TRANS_EXTENT_X1,"TRANS_EXTENT_X1"));
						tmp_tplKeys.insert(std::make_pair(kSlackEnum::TRANS_EXTENT_Y1,"TRANS_EXTENT_Y1"));
						tmp_tplKeys.insert(std::make_pair(kSlackEnum::TRANS_EXTENT_X2,"TRANS_EXTENT_X2"));
						tmp_tplKeys.insert(std::make_pair(kSlackEnum::TRANS_EXTENT_Y2,"TRANS_EXTENT_Y2"));
						tmp_tplKeys.insert(std::make_pair(kSlackEnum::ORIGIN_X,"ORIGIN_X"));
						tmp_tplKeys.insert(std::make_pair(kSlackEnum::ORIGIN_Y,"ORIGIN_Y"));
						tmp_tplKeys.insert(std::make_pair(kSlackEnum::ROTATION,"ROTATION"));

						return tmp_tplKeys;
					}


				} /* namespace Sources */

		} /* namespace SinglePhase */

} /* namespace ModPowerSystems */
