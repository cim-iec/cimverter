/*
 * System.cpp
 *
 */

#include "System.h"

namespace ModPowerSystems {

	System::System()
	{
		// TODO Auto-generated constructor stub

	}
	/*initialize System Label and Coordinate
	 *
	 */

	System::System(double lx, double ly, double rx, double ry):_lx(lx),_ly(ly),_rx(rx),_ry(ry) {

		//initialize System Label
		this->set_name("system");
		this->annotation.placement.transfomation.extent.first.x = 0;
		this->annotation.placement.transfomation.extent.first.y = -30;
		this->annotation.placement.transfomation.extent.second.x = 30;
		this->annotation.placement.transfomation.extent.second.y = 0;
		this->annotation.placement.visible = true;

		//initialize System
		this->annotation.icon.coordinate.extent.first.x = 160;
		this->annotation.icon.coordinate.extent.first.y = -160;
		this->annotation.icon.coordinate.extent.second.x = 180;
		this->annotation.icon.coordinate.extent.second.y = 260;
	}

	System::~System()
	{
		// TODO Auto-generated destructor stub
	}

	bool System::set_system_setting(ctemplate::TemplateDictionary *dictionary)
	{

		dictionary->SetValue(NAME,this->name());
		dictionary->SetFormattedValue(ICON_EXTENT_X1, "%.2f", this->annotation.icon.coordinate.extent.first.x);
		dictionary->SetFormattedValue(ICON_EXTENT_Y1, "%.2f", this->annotation.icon.coordinate.extent.first.y);
		dictionary->SetFormattedValue(ICON_EXTENT_X2, "%.2f", this->annotation.icon.coordinate.extent.second.x);
		dictionary->SetFormattedValue(ICON_EXTENT_Y2, "%.2f", this->annotation.icon.coordinate.extent.second.y);

		dictionary->SetFormattedValue(DIAGRAM_EXTENT_X1, "%.2f", this->_lx);
		dictionary->SetFormattedValue(DIAGRAM_EXTENT_Y1, "%.2f", this->_ly);
		dictionary->SetFormattedValue(DIAGRAM_EXTENT_X2, "%.2f", this->_rx);
		dictionary->SetFormattedValue(DIAGRAM_EXTENT_Y2, "%.2f", this->_ry);

		return true;
	}

	bool System::set_system_label(ctemplate::TemplateDictionary *dictionary)
	{
		dictionary->SetFormattedValue(FNOM,"%.1f",this->f_nom());
		dictionary->SetValue(NAME,this->name());
		dictionary->SetValue(FNOM_DISPLAYUNIT,(ModelicaUnit[this->f_nom_displayUnit()]));
		dictionary->SetValue(SIMMODE,this->simMode());
		dictionary->SetValue(INIT,this->init());

		dictionary->SetFormattedValue(TRANS_EXTENT_X1,"%.1f",this->annotation.placement.transfomation.extent.first.x);
		dictionary->SetFormattedValue(TRANS_EXTENT_Y1,"%.1f",this->annotation.placement.transfomation.extent.first.y);
		dictionary->SetFormattedValue(TRANS_EXTENT_X2,"%.1f",this->annotation.placement.transfomation.extent.second.x);
		dictionary->SetFormattedValue(TRANS_EXTENT_Y2,"%.1f",this->annotation.placement.transfomation.extent.second.y);
		dictionary->SetIntValue(ROTATION,this->annotation.placement.transfomation.rotation);
		dictionary->SetFormattedValue(VISIBLE,"%s",this->annotation.placement.visible ? "true":"false");

		return true;
	}

	bool System::set_template_values(ctemplate::TemplateDictionary *dictionary)
	{

		this->set_system_setting(dictionary);
		this->set_system_label(dictionary);
		return true;
	}

} /* namespace ModPowerSystems */
