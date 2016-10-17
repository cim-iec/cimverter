#ifndef TOOLS_H
#define TOOLS_H
#include "IEC61970.h"


class Tools
{
public:
	Tools();
	~Tools();
public:

	/**
	 * convert the coordinate system between different software
	 */
	static IEC61970::Base::DiagramLayout::DiagramObjectPoint convert_coordinate(IEC61970::Base::Domain::Float x, IEC61970::Base::Domain::Float y, float a, float b, float c, float d);
	/**
	 * convert name adapt to the format in modelica
	*/
	static std::string name_in_modelica(std::string orginal_name);

private:


};


#endif //TOOLS_H
