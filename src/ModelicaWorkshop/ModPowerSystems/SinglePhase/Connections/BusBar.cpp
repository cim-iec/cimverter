/*
 * BusBar.cpp
 *
 */

#include "BusBar.h"

namespace ModPowerSystems
{
	namespace SinglePhase
	{
		namespace Connections
		{
			int BusBar::_count(0);

			std::map<const kBusBarEnum, const std::string> BusBar::tplKeys = BusBar::initial_tplKeys();


			BusBar::BusBar() :_Vnom(110000)
			{
				++_count;
			}

			BusBar::~BusBar()
			{
				--_count;
			}

			bool BusBar::set_template_values(ctemplate::TemplateDictionary *dictionary){

				dictionary->SetFormattedValue(tplKeys[kBusBarEnum::VNOM],"%.2f",this->Vnom());
				dictionary->SetValue(tplKeys[kBusBarEnum::NAME],this->name());
				dictionary->SetFormattedValue(tplKeys[kBusBarEnum::TRANS_EXTENT_X1],"%.1f",this->annotation.placement.transfomation.extent.first.x);
				dictionary->SetFormattedValue(tplKeys[kBusBarEnum::TRANS_EXTENT_Y1],"%.1f",this->annotation.placement.transfomation.extent.first.y);
				dictionary->SetFormattedValue(tplKeys[kBusBarEnum::TRANS_EXTENT_X2],"%.1f",this->annotation.placement.transfomation.extent.second.x);
				dictionary->SetFormattedValue(tplKeys[kBusBarEnum::TRANS_EXTENT_Y2],"%.1f",this->annotation.placement.transfomation.extent.second.y);
				dictionary->SetFormattedValue(tplKeys[kBusBarEnum::ORIGIN_X],"%.1f",this->annotation.placement.transfomation.origin.x);
				dictionary->SetFormattedValue(tplKeys[kBusBarEnum::ORIGIN_Y],"%.1f",this->annotation.placement.transfomation.origin.y);
				dictionary->SetIntValue(tplKeys[kBusBarEnum::ROTATION],this->annotation.placement.transfomation.rotation);
				dictionary->SetFormattedValue(tplKeys[kBusBarEnum::VISIBLE],"%s",this->annotation.placement.visible ? "true":"false");

				return true;
			}

			/**
			* Initialize the Template Markers map of BusBar
			*/
			std::map<const kBusBarEnum, const std::string> BusBar::initial_tplKeys(){

				auto tmp_tplKeys = std::map<const kBusBarEnum, const std::string>();
				tmp_tplKeys.insert(std::make_pair(kBusBarEnum::NAME,"NAME"));
				tmp_tplKeys.insert(std::make_pair(kBusBarEnum::VNOM,"VNOM"));
				tmp_tplKeys.insert(std::make_pair(kBusBarEnum::VISIBLE,"VISIBLE"));
				tmp_tplKeys.insert(std::make_pair(kBusBarEnum::TRANS_EXTENT_X1,"TRANS_EXTENT_X1"));
				tmp_tplKeys.insert(std::make_pair(kBusBarEnum::TRANS_EXTENT_Y1,"TRANS_EXTENT_Y1"));
				tmp_tplKeys.insert(std::make_pair(kBusBarEnum::TRANS_EXTENT_X2,"TRANS_EXTENT_X2"));
				tmp_tplKeys.insert(std::make_pair(kBusBarEnum::TRANS_EXTENT_Y2,"TRANS_EXTENT_Y2"));
				tmp_tplKeys.insert(std::make_pair(kBusBarEnum::ORIGIN_X,"ORIGIN_X"));
				tmp_tplKeys.insert(std::make_pair(kBusBarEnum::ORIGIN_Y,"ORIGIN_Y"));
				tmp_tplKeys.insert(std::make_pair(kBusBarEnum::ROTATION,"ROTATION"));

				return tmp_tplKeys;
			}

		} /* namespace Connections */

	} /* namespace SinglePhase */

} /* namespace ModPowerSystems */
