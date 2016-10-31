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

			BusBar::BusBar() :_Vnom(110000)
			{
				this->annotation.placement.transfomation.extent.first.x = -10;
				this->annotation.placement.transfomation.extent.first.y = -10;
				this->annotation.placement.transfomation.extent.second.x = 10;
				this->annotation.placement.transfomation.extent.second.y = 10;
			}

			BusBar::BusBar(const BusBar &rhs)
			{
				this->_Vnom = rhs._Vnom;
			}

			BusBar::~BusBar()
			{
			}

			bool BusBar::set_template_values(ctemplate::TemplateDictionary *dictionary){

				dictionary->SetFormattedValue(VNOM,"%.f",this->Vnom());
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


		} /* namespace Connections */

	} /* namespace SinglePhase */

} /* namespace ModPowerSystems */
