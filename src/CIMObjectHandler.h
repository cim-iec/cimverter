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
typedef IEC61970::Base::Core::ConnectivityNode*  ConnectivityNodePtr;
typedef IEC61970::Base::Core::Terminal* TerminalPtr;
typedef IEC61970::Base::Wires::ExternalNetworkInjection* ExNIPtr;
typedef IEC61970::Base::Wires::ACLineSegment* AcLinePtr;
typedef IEC61970::Base::Wires::PowerTransformer* PowerTrafoPtr;
typedef IEC61970::Base::Wires::EnergyConsumer* EnergyConsumerPtr;
typedef IEC61970::Base::Wires::SynchronousMachine* SynMachinePtr;
typedef IEC61970::Base::DiagramLayout::DiagramObject* DiagramObjectPtr;
typedef IEC61970::Base::DiagramLayout::DiagramObjectPoint* DiagramObjectPointPtr;
typedef IEC61970::Base::DiagramLayout::DiagramObjectPoint DiagramObjectPoint;

using namespace ModelicaWorkshop;

/*
 * Handle the CIMObject
 */
class CIMObjectHandler {

public:
  CIMObjectHandler()= delete;
	CIMObjectHandler(std::vector<BaseClass*>&& CIMObjects);
	virtual ~CIMObjectHandler();

	bool ModelicaCodeGenerator(const std::string filename);
	bool SystemSettingsHandler(const std::string filename, ctemplate::TemplateDictionary* dict);
	BusBar TopologicalNodeHandler(const TPNodePtr tp_node, ctemplate::TemplateDictionary* dict);
	ConnectivityNode ConnectiviyNodeHandler(const TPNodePtr tp_node, const TerminalPtr terminal, const ConnectivityNodePtr connectivity_node, ctemplate::TemplateDictionary* dict);
	Slack ExternalNIHandler(const TPNodePtr tp_node, const TerminalPtr terminal, const ExNIPtr externalNI, ctemplate::TemplateDictionary* dict);
	PiLine ACLineSegmentHandler(const TPNodePtr tp_node,  const TerminalPtr terminal, const AcLinePtr ac_line, ctemplate::TemplateDictionary* dict);
	Transformer PowerTransformerHandler(const TPNodePtr tp_node, const TerminalPtr terminal, const PowerTrafoPtr power_trafo, ctemplate::TemplateDictionary* dict);
	PQLoad EnergyConsumerHandler(const TPNodePtr tp_node, const TerminalPtr terminal, const EnergyConsumerPtr energy_consumer, ctemplate::TemplateDictionary* dict);
	GenericGenerator SynchronousMachineHandler(const TPNodePtr tp_node, const TerminalPtr terminal, const SynMachinePtr syn_machine, ctemplate::TemplateDictionary* dict);
	bool ConnectionHandler(ctemplate::TemplateDictionary* dict);

	static std::string name_in_modelica(std::string orginal_name);
  static DiagramObjectPoint convert_coordinate(IEC61970::Base::Domain::Float x, IEC61970::Base::Domain::Float y);

private:
	std::vector<BaseClass*> _CIMObjects;
	std::queue<Connection> connectionQueue;

  std::list<TerminalPtr>::iterator terminal_it;
	std::list<DiagramObjectPtr>::iterator diagram_it;
	std::list<DiagramObjectPointPtr>::iterator points_it;
};

#endif /* SRC_CIMOBJECTHANDLER_H_ */
