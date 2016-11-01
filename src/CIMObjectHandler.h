/*
 * CIMObjectHandler.h
 *
 */

#ifndef SRC_CIMOBJECTHANDLER_H_
#define SRC_CIMOBJECTHANDLER_H_

#include "ModelicaWorkshop/ModelicaClass.h"
#include <stdlib.h>
#include <boost/lexical_cast.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include "IEC61970.h"
#include "CIMParser.h"
#include <ctemplate/template.h>

typedef IEC61970::Base::Topology::TopologicalNode*  TPNodePtr;
typedef IEC61970::Base::Core::Terminal* TerminalPtr;
typedef IEC61970::Base::Wires::ExternalNetworkInjection* ExNIPtr;
typedef IEC61970::Base::Wires::ACLineSegment* AcLinePtr;
typedef IEC61970::Base::Wires::PowerTransformer* TrafoPtr;
typedef IEC61970::Base::Wires::EnergyConsumer* EnergyConsumerPtr;
typedef IEC61970::Base::Wires::SynchronousMachine* SynMachinePtr;

class CIMObjectHandler {

public:

	CIMObjectHandler();
	CIMObjectHandler(std::vector<BaseClass*>&& CIMObjects);
	virtual ~CIMObjectHandler();

	bool generate_modelica_code(const std::string filename);
	bool handle_SystemSettings(const std::string filename, ctemplate::TemplateDictionary* dict);
	BusBarObj handle_TopologicalNode(const TPNodePtr tpNode, ctemplate::TemplateDictionary* dict);
	SlackObj handle_ExternalNI(const TPNodePtr tpNode, const TerminalPtr terminal, const ExNIPtr externalNI, ctemplate::TemplateDictionary* dict);
	PiLineObj handle_ACLineSegment(const TPNodePtr tpNode,  const TerminalPtr terminal, const AcLinePtr acLine, ctemplate::TemplateDictionary* dict);
	TransformerObj handle_PowerTransformer(const TPNodePtr tpNode, const TerminalPtr terminal, const TrafoPtr powerTrafo, ctemplate::TemplateDictionary* dict);
	PQLoadObj handle_EnergyConsumer(const TPNodePtr tpNode, const TerminalPtr terminal, const EnergyConsumerPtr energyConsumer, ctemplate::TemplateDictionary* dict);
	GenericGeneratorObj handle_SynchronousMachine(const TPNodePtr tpNode, const TerminalPtr terminal, const SynMachinePtr synMachine, ctemplate::TemplateDictionary* dict);
	bool handle_Connection(ctemplate::TemplateDictionary* dict);

	static std::string name_in_modelica(std::string orginal_name);


private:
	std::vector<BaseClass*> _CIMObjects;
	std::queue<Connection> connectionQueue;
	static IEC61970::Base::DiagramLayout::DiagramObjectPoint convert_coordinate(IEC61970::Base::Domain::Float x, IEC61970::Base::Domain::Float y);
};

#endif /* SRC_CIMOBJECTHANDLER_H_ */
