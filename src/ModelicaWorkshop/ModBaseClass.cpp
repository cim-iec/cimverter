/*
 * ModBaseClass.cpp
 *
 */

#include "ModBaseClass.h"

namespace ModelicaWorkshop {


	ModBaseClass::ModBaseClass()
	{

	}

	ModBaseClass::~ModBaseClass()
	{
		// TODO Auto-generated destructor stub
	}

	bool ModBaseClass::set_template_values(ctemplate::TemplateDictionary *dictionary)
	{

		for(const auto &w: this->ready_to_fill_templates){
			dictionary->SetFormattedValue(w.first, w.second.c_str());
		}
		return true;
	}

} /* namespace ModelicaWorkshop */
