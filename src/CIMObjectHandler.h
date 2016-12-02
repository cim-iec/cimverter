/*
 * CIMObjectHandler.h
 * Handle the CIMObject
 */

#ifndef SRC_CIMOBJECTHANDLER_H_
#define SRC_CIMOBJECTHANDLER_H_

#include <boost/lexical_cast.hpp>
#include "IEC61970.h"
#include "CIMParser.h"
#include "ConfigManager.h"
#include <ctemplate/template.h>
#include "ModelicaWorkshop/ModelicaClass.h"

typedef IEC61970::Base::Wires::BusbarSection* BusBarSectionPtr;
typedef IEC61970::Base::Topology::TopologicalNode* TPNodePtr;
typedef IEC61970::Base::Core::ConnectivityNode* ConnectivityNodePtr;
typedef IEC61970::Base::Core::Terminal* TerminalPtr;
typedef IEC61970::Base::Wires::ExternalNetworkInjection* ExNIPtr;
typedef IEC61970::Base::Wires::ACLineSegment* AcLinePtr;
typedef IEC61970::Base::Wires::PowerTransformer* PowerTrafoPtr;
typedef IEC61970::Base::Wires::EnergyConsumer* EnergyConsumerPtr;
typedef IEC61970::Base::Wires::SynchronousMachine* SynMachinePtr;
typedef IEC61970::Base::DiagramLayout::DiagramObject* DiagramObjectPtr;
typedef IEC61970::Base::DiagramLayout::DiagramObjectPoint* DiagramObjectPointPtr;
typedef IEC61970::Base::DiagramLayout::DiagramObjectPoint DiagramObjectPoint;

void static print_separator() {
  std::string prefix_deco(200, '-');
  std::cout << prefix_deco << std::endl;
}

using namespace ModelicaWorkshop;
using namespace libconfig;

/// \brief Handle the CIMObject
///
///
class CIMObjectHandler {

 public:
  CIMObjectHandler() = delete;
  CIMObjectHandler(std::vector<BaseClass*>&& CIMObjects);
  CIMObjectHandler(const CIMObjectHandler&) = delete;
  CIMObjectHandler& operator=(const CIMObjectHandler&) = delete;
  virtual ~CIMObjectHandler();

  bool ModelicaCodeGenerator(const std::string filename);
  bool SystemSettingsHandler(const std::string filename, ctemplate::TemplateDictionary* dict);
  BusBar TopologicalNodeHandler(const TPNodePtr tp_node, ctemplate::TemplateDictionary* dict);
  bool BusBarSectionHandler(const BusBarSectionPtr busbar_section, BusBar &busbar, ctemplate::TemplateDictionary* dict);
  ConnectivityNode ConnectiviyNodeHandler(const TPNodePtr tp_node, const TerminalPtr terminal, const ConnectivityNodePtr connectivity_node, ctemplate::TemplateDictionary* dict);
  Slack ExternalNIHandler(const TPNodePtr tp_node, const TerminalPtr terminal, const ExNIPtr externalNI, ctemplate::TemplateDictionary* dict);
  PiLine ACLineSegmentHandler(const TPNodePtr tp_node, const TerminalPtr terminal, const AcLinePtr ac_line, ctemplate::TemplateDictionary* dict);
  Transformer PowerTransformerHandler(const TPNodePtr tp_node, const TerminalPtr terminal, const PowerTrafoPtr power_trafo, ctemplate::TemplateDictionary* dict);
  PQLoad EnergyConsumerHandler(const TPNodePtr tp_node, const TerminalPtr terminal, const EnergyConsumerPtr energy_consumer, ctemplate::TemplateDictionary* dict);
  WindGenerator SynchronousMachineHandlerType1(const TPNodePtr tp_node, const TerminalPtr terminal, const SynMachinePtr syn_machine, ctemplate::TemplateDictionary* dict);
  SolarGenerator SynchronousMachineHandlerType2(const TPNodePtr tp_node, const TerminalPtr terminal, const SynMachinePtr syn_machine,ctemplate::TemplateDictionary* dict);
  bool HouseholdComponetsHandler(const TPNodePtr tp_node, ctemplate::TemplateDictionary* dict);  ///to find household Componets
  bool ConnectionHandler(ctemplate::TemplateDictionary* dict);

  void get_config();  ///get congiuration from config.cfg
  static std::string name_in_modelica(std::string orginal_name);
  static DiagramObjectPoint convert_coordinate(double x, double y, const ConfigManager & configManager);

 private:
  ConfigManager configManager;
  DiagramObjectPoint _t_points;
  std::vector<BaseClass*> _CIMObjects;
  std::queue<PQLoad> pqloadQueue;
  std::queue<Battery> batteryQueue;
  std::queue<SolarGenerator> solarGeneratorQueue;
  std::queue<Household> householdQueue;
  std::queue<Connection> connectionQueue;

  std::list<TerminalPtr>::iterator terminal_it;
  std::list<DiagramObjectPtr>::iterator diagram_it;
  std::list<DiagramObjectPointPtr>::iterator points_it;
  std::list<IEC61970::Base::Wires::PowerTransformerEnd*>::iterator transformer_end_it;

  DiagramObjectPoint calculate_average_position();

};

#endif /* SRC_CIMOBJECTHANDLER_H_ */
