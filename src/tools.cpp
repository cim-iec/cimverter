#include "tools.h"

Tools::Tools(){

}

Tools::~Tools(){

}

IEC61970::Base::DiagramLayout::DiagramObjectPoint Tools::convert_coordinate(IEC61970::Base::Domain::Float x, IEC61970::Base::Domain::Float y, float a, float b, float c, float d)
{
	IEC61970::Base::DiagramLayout::DiagramObjectPoint new_Position;
	new_Position.xPosition= a*x+b;
	new_Position.yPosition = c*y+d;
	return new_Position;
}

std::string Tools::name_in_modelica(std::string original_name)
{
	std::string new_name = original_name;
	std::size_t i = new_name.find("-");
	if (i < new_name.size())
		new_name = "CIM_" + new_name.replace(i,1,"_");
	return new_name;
}
