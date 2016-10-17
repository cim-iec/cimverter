/*
 * CIMObjectHandler.h
 *
 */

#ifndef SRC_CIMOBJECTHANDLER_H_
#define SRC_CIMOBJECTHANDLER_H_

#include <stdlib.h>
#include <boost/lexical_cast.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include "IEC61970.h"
#include "tools.h"
#include "CIMParser.h"
#include <ctemplate/template.h>
#include "ModelicaWorkshop/ModelicaClass.h"


class CIMObjectHandler {

public:

	static int terminal_count;

	CIMObjectHandler();
	CIMObjectHandler(std::vector<BaseClass*>&& CIMObjects);
	virtual ~CIMObjectHandler();

	bool generate_modelica_code(const std::string filename);
	bool handle_GlobalSettings(const std::string filename, ctemplate::TemplateDictionary* dict);

	bool handle_ExternalNI(IEC61970::Base::Topology::TopologicalNode* tpNode, IEC61970::Base::Wires::ExternalNetworkInjection* externalNI, ctemplate::TemplateDictionary* sub_dict);
	bool handle_TopologicalNode(IEC61970::Base::Topology::TopologicalNode* tpNode, ctemplate::TemplateDictionary* sub_dict);
	bool handle_Terminal(IEC61970::Base::Core::Terminal* terminal, ctemplate::TemplateDictionary* sub_dict);
	bool handle_ACLineSegment(IEC61970::Base::Wires::ACLineSegment* acLine, ctemplate::TemplateDictionary* sub_dict);
	bool handle_PowerTransformer(IEC61970::Base::Wires::PowerTransformer* powerTrafo, ctemplate::TemplateDictionary* sub_dict);
	bool handle_EnergyConsumer(IEC61970::Base::Topology::TopologicalNode* tpNode, IEC61970::Base::Core::Terminal* terminal, IEC61970::Base::Wires::EnergyConsumer* energyConsumer, ctemplate::TemplateDictionary* sub_dict);

private:
	std::vector<BaseClass*> _CIMObjects;
};



#endif /* SRC_CIMOBJECTHANDLER_H_ */
