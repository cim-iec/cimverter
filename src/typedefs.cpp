#include "ModelicaWorkshop/ModelicaClass.h"
#ifdef LIB_CGMES
typedef CIMPP::IdentifiedObject* IdentifiedObjectPtr;
typedef CIMPP::BusbarSection* BusBarSectionPtr;
typedef CIMPP::TopologicalNode* TPNodePtr;
typedef CIMPP::ConnectivityNode* ConnectivityNodePtr;
typedef CIMPP::Terminal* TerminalPtr;
typedef CIMPP::Terminal Terminal;
typedef CIMPP::ConductingEquipment* ConductingPtr;
typedef CIMPP::BaseVoltage* BaseVoltagePtr;
typedef CIMPP::ExternalNetworkInjection* ExNIPtr;
typedef CIMPP::ACLineSegment* AcLinePtr;
typedef CIMPP::Breaker* BreakerPtr;
typedef CIMPP::PowerTransformer* PowerTrafoPtr;
typedef CIMPP::PowerTransformerEnd* PowerTransformerEndPtr;
typedef CIMPP::EnergyConsumer* EnergyConsumerPtr;
typedef CIMPP::SynchronousMachine* SynMachinePtr;
typedef CIMPP::GeneratingUnit * GeneratingUnitPtr;
typedef CIMPP::GeneratingUnit  GeneratingUnit;
typedef CIMPP::RotatingMachine * RotatingMachinePtr;
typedef CIMPP::DiagramObject* DiagramObjectPtr;
typedef CIMPP::DiagramObjectPoint* DiagramObjectPointPtr;
typedef CIMPP::DiagramObjectPoint DiagramObjectPoint;
typedef CIMPP::SvPowerFlow* SVPowerFlowPtr;
typedef CIMPP::SvVoltage* SVVoltagePtr;
typedef CIMPP::OperationalLimitSet* OpLimitSetPtr;
typedef CIMPP::CurrentLimit* CurrentLimitPtr;
typedef CIMPP::OperationalLimit* OpLimitPtr;
typedef CIMPP::IdentifiedObject* IdentifiedObjectPtr;
typedef CIMPP::SynchronousMachineTimeConstantReactance * SynMachineDynPtr;
typedef ModPowerSystems::PhasorSinglePhase::Connections::BusBar BusBar;
typedef ModPowerSystems::PhasorSinglePhase::Connections::ConnectivityNode ConnectivityNode;
typedef CIMPP::String String;
#else
#include "IEC61970.hpp"
typedef IEC61970::Base::Core::IdentifiedObject* IdentifiedObjectPtr;
typedef IEC61970::Base::Wires::BusbarSection* BusBarSectionPtr;
typedef IEC61970::Base::Topology::TopologicalNode* TPNodePtr;
typedef IEC61970::Base::Core::ConnectivityNode* ConnectivityNodePtr;
typedef IEC61970::Base::Core::Terminal* TerminalPtr;
typedef IEC61970::Base::Core::Terminal Terminal;
typedef IEC61970::Base::Core::ConductingEquipment* ConductingPtr;
typedef IEC61970::Base::Core::BaseVoltage* BaseVoltagePtr;
typedef IEC61970::Base::Wires::ExternalNetworkInjection* ExNIPtr;
typedef IEC61970::Base::Wires::ACLineSegment* AcLinePtr;
typedef IEC61970::Base::Wires::Breaker* BreakerPtr;
typedef IEC61970::Base::Wires::PowerTransformer* PowerTrafoPtr;
typedef IEC61970::Base::Wires::PowerTransformerEnd* PowerTransformerEndPtr;
typedef IEC61970::Base::Wires::EnergyConsumer* EnergyConsumerPtr;
typedef IEC61970::Base::Wires::SynchronousMachine* SynMachinePtr;
typedef IEC61970::Base::Generation::Production::GeneratingUnit * GeneratingUnitPtr;
typedef IEC61970::Base::Generation::Production::GeneratingUnit  GeneratingUnit;
typedef IEC61970::Base::Wires::RotatingMachine * RotatingMachinePtr;
typedef IEC61970::Base::DiagramLayout::DiagramObject* DiagramObjectPtr;
typedef IEC61970::Base::DiagramLayout::DiagramObjectPoint* DiagramObjectPointPtr;
typedef IEC61970::Base::DiagramLayout::DiagramObjectPoint DiagramObjectPoint;
typedef IEC61970::Base::StateVariables::SvPowerFlow* SVPowerFlowPtr;
typedef IEC61970::Base::StateVariables::SvVoltage* SVVoltagePtr;
typedef IEC61970::Base::OperationalLimits::OperationalLimitSet* OpLimitSetPtr;
typedef IEC61970::Base::OperationalLimits::CurrentLimit* CurrentLimitPtr;
typedef IEC61970::Base::OperationalLimits::OperationalLimit* OpLimitPtr;
typedef IEC61970::Base::Core::IdentifiedObject* IdentifiedObjectPtr;
typedef IEC61970::Dynamics::StandardModels::SynchronousMachineDynamics::SynchronousMachineTimeConstantReactance * SynMachineDynPtr;
typedef ModPowerSystems::PhasorSinglePhase::Connections::BusBar BusBar;
typedef ModPowerSystems::PhasorSinglePhase::Connections::ConnectivityNode ConnectivityNode;
typedef IEC61970::Base::Domain::String String;
#endif

