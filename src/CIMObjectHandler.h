/*
* CIMObjectHandler.h
* Handle the CIMObject
*/

#ifndef SRC_CIMOBJECTHANDLER_H_
#define SRC_CIMOBJECTHANDLER_H_


#include <queue>
#include <map>
#include <list>
#include <boost/lexical_cast.hpp>
#include "IEC61970.hpp"
#include "ConfigManager.h"
#include "CIMModel.hpp"
#include <ctemplate/template.h>
#include "ModelicaWorkshop/ModelicaClass.h"
#include "typedefs.cpp"
#ifdef SINERGIEN
typedef Sinergien::EnergyGrid::EnergyStorage::BatteryStorage* BatteryStoragePtr;
#endif

void static print_separator() {
    std::string prefix_deco(200, '-');
    std::cout << prefix_deco << std::endl;
}
/** \brief Handle the CIMObject,
 * every model component has its handle function,
 * esing mappling rules
*/
class CIMObjectHandler {


public:
    CIMObjectHandler() = delete;
    CIMObjectHandler(std::vector<BaseClass*>&& CIMObjects);
    CIMObjectHandler(const CIMObjectHandler&) = delete;
    CIMObjectHandler& operator=(const CIMObjectHandler&) = delete;
    virtual ~CIMObjectHandler();

    void prepareTerminalList();
    bool ModelicaCodeGenerator(std::string output_file_name, int verbose_flag);
    bool SystemSettingsHandler(const std::string filename, ctemplate::TemplateDictionary* dict);
    BusBar* TopologicalNodeHandler(const TPNodePtr tp_node, ctemplate::TemplateDictionary* dict);
    ModSlack* ExternalNIHandler( BaseClass* tp_node, const TerminalPtr terminal, const ExNIPtr externalNI, ctemplate::TemplateDictionary* dict);
    ModPQLoad* EnergyConsumerHandler(BaseClass* tp_node, const TerminalPtr terminal, const EnergyConsumerPtr energy_consumer, ctemplate::TemplateDictionary* dict);
    ModPVNode * SynchronousMachineHandlerType0(BaseClass* node, const TerminalPtr terminal, const SynMachinePtr syn_machine, ctemplate::TemplateDictionary* dict);
    SynMachineDyn *   synMachineDynHandler  (BaseClass* node, const TerminalPtr terminal, const SynMachineDynPtr syn_machine, ctemplate::TemplateDictionary* dict);
    BusBar* ConnectivityNodeHandler(const ConnectivityNodePtr connectivity_node, ctemplate::TemplateDictionary* dict);
    bool HouseholdComponetsHandler( BaseClass* node, ctemplate::TemplateDictionary* dict);  //to find household Componets

    bool BusBarSectionHandler(const BusBarSectionPtr busbar_section, BusBar &busbar, ctemplate::TemplateDictionary* dict);

    ModPiLine* ACLineSegmentHandler(BaseClass* tp_node, BusBar* busbar, const TerminalPtr terminal, const AcLinePtr ac_line, ctemplate::TemplateDictionary* dict, std::string node1Name = "", std::string node2Name = "");
    ModTransformer* PowerTransformerHandler(BusBar* busbar, const TerminalPtr terminal, const PowerTrafoPtr power_trafo, ctemplate::TemplateDictionary* dict);
    ModWindGenerator* SynchronousMachineHandlerType1(const TerminalPtr terminal, const SynMachinePtr syn_machine, ctemplate::TemplateDictionary* dict);
    ModSolarGenerator* SynchronousMachineHandlerType2(const TerminalPtr terminal, const SynMachinePtr syn_machine,ctemplate::TemplateDictionary* dict);
    ModBreaker* BreakerHandler(BusBar* busbar, const TerminalPtr terminal, const BreakerPtr breaker,ctemplate::TemplateDictionary* dict);
#ifdef SINERGIEN
    Battery BatteryStorageHandler(const TPNodePtr tp_node, const TerminalPtr terminal, const BatteryStoragePtr battery_storge, ctemplate::TemplateDictionary* dict);
#endif

    bool ConnectionHandler(ctemplate::TemplateDictionary* dict);

    void remove_non_alnums(IdentifiedObjectPtr identified_obj);
    void add_mem_address(IdentifiedObjectPtr identified_obj);
    bool pre_process(); ///first loop
    void remove_unconnected_components();
    void get_config(std::string templates);  /// Get congiurations from config.cfg
    void print_RTTI(BaseClass *Object);  /// Print component information
    static std::string name_in_modelica(std::string orginal_name);/// Modify illega modelica name
    static DiagramObjectPoint convert_coordinate(double x, double y, const ConfigManager & configManager);/// Tranfer the modelica components' coordinate
    int get_exit_code(){return exit_code;};
    void set_exit_code(int i){this->exit_code = i;};
private:
    int exit_code = 0;
    std::string template_folder;
    BusBar* currBusbar;
    BaseClass* currNode;
    ConfigManager configManager;
    DiagramObjectPoint _t_points;
    std::vector<BaseClass*> _CIMObjects;
    std::queue<ModPQLoad> pqloadQueue;
    std::queue<ModBattery> batteryQueue;
    std::queue<ModSolarGenerator> solarGeneratorQueue;
    std::queue<ModPVNode> pvNodeQueue;
    std::queue<ModHousehold> householdQueue;
    std::queue<Connection> connectionQueue;
    std::unordered_map<BaseClass*, ModBaseClass*> _UsedObjects;
    std::unordered_map<RotatingMachinePtr,GeneratingUnitPtr> generatorMap;
    std::unordered_map<ConductingPtr ,BaseVoltagePtr> baseVoltageMap;
    std::unordered_map<TerminalPtr, SVPowerFlowPtr> svPowerFlowMap;
    std::unordered_map<BaseClass*,SVVoltagePtr> svVoltageMap;
    std::unordered_map<AcLinePtr,OpLimitSetPtr> OpLimitMap;
    std::unordered_map<BaseClass*, std::list<TerminalPtr> > terminalList;
    std::unordered_map<SynMachinePtr, SynMachineDynPtr> SynMachineMap;
    std::unordered_map<AcLinePtr, std::vector<TerminalPtr> > PiLineMap;

    std::list<DiagramObjectPtr>::iterator diagram_it;
    std::list<RotatingMachinePtr>::iterator rotatingMachine_it;
    DiagramObjectPoint calculate_average_position();//using this->diagram_it

    std::map<AcLinePtr,std::string> piLineIdMap;

};

#endif /* SRC_CIMOBJECTHANDLER_H_ */
