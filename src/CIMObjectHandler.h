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
#include "CIMParser.h"
#include <ctemplate/template.h>
#include "ModelicaWorkshop/ModelicaClass.h"

typedef IEC61970::Base::Topology::TopologicalNode*  tpNodePtr;
typedef IEC61970::Base::Core::Terminal* terminalPtr;
typedef IEC61970::Base::Wires::ExternalNetworkInjection* ExNIPtr;
typedef IEC61970::Base::Wires::ACLineSegment* acLinePtr;
typedef IEC61970::Base::Wires::PowerTransformer* trafoPtr;
typedef IEC61970::Base::Wires::EnergyConsumer* energyConsumerPtr;

class CIMObjectHandler {

public:

	CIMObjectHandler();
	CIMObjectHandler(std::vector<BaseClass*>&& CIMObjects);
	virtual ~CIMObjectHandler();

	bool generate_modelica_code(const std::string filename);
	bool handle_SystemSettings(const std::string filename, ctemplate::TemplateDictionary* dict);
	SlackObj handle_ExternalNI(const tpNodePtr tpNode, const terminalPtr terminal, const ExNIPtr externalNI, ctemplate::TemplateDictionary* dict);
	BusBarObj handle_TopologicalNode(const tpNodePtr tpNode, ctemplate::TemplateDictionary* dict);
	PiLineObj handle_ACLineSegment(const tpNodePtr tpNode,  const terminalPtr terminal, const acLinePtr acLine, ctemplate::TemplateDictionary* dict);
	TransformerObj handle_PowerTransformer(const tpNodePtr tpNode, const terminalPtr terminal, const trafoPtr powerTrafo, ctemplate::TemplateDictionary* dict);
	PQLoadObj handle_EnergyConsumer(const tpNodePtr tpNode, const terminalPtr terminal, const energyConsumerPtr energyConsumer, ctemplate::TemplateDictionary* dict);
	bool handle_Connection(ctemplate::TemplateDictionary* dict);

	static std::string name_in_modelica(std::string orginal_name);


private:
	std::vector<BaseClass*> _CIMObjects;
	std::queue<Connection> connectionQueue;
	static::IEC61970::Base::DiagramLayout::DiagramObjectPoint convert_coordinate(IEC61970::Base::Domain::Float x, IEC61970::Base::Domain::Float y);
};

#endif /* SRC_CIMOBJECTHANDLER_H_ */
