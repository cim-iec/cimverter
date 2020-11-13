/*
 * Connection.h
 *	Manager Connections in Modelica
 */

#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_CONNECTION_H_
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_CONNECTION_H_

#include "../ModBaseClass.h"
#include "../ModelicaClass.h"
//#include "../../ConfigManager.h"

#include <cmath>

typedef ModPowerSystems::PhasorSinglePhase::Connections::BusBar ModBusBar;
typedef ModPowerSystems::PhasorSinglePhase::Connections::ConnectivityNode ModConnectivityNode;
typedef ModPowerSystems::PhasorSinglePhase::Sources::Slack ModSlack;
typedef ModPowerSystems::PhasorSinglePhase::Loads::PQLoad ModPQLoad;
typedef ModPowerSystems::PhasorSinglePhase::Loads::ZLoad ModZLoad;
typedef ModPowerSystems::PhasorSinglePhase::Lines::PiLine ModPiLine;
typedef ModPowerSystems::PhasorSinglePhase::Lines::RxLine ModRxLine;
typedef ModPowerSystems::PhasorSinglePhase::Lines::Breaker ModBreaker;
typedef ModPowerSystems::PhasorSinglePhase::Transformers::Transformer ModTransformer;
typedef ModPowerSystems::PhasorSinglePhase::Generations::GenericGenerator ModGenericGenerator;
typedef ModPowerSystems::PhasorSinglePhase::Generations::WindGenerator ModWindGenerator;
typedef ModPowerSystems::PhasorSinglePhase::Generations::PVNode ModPVNode;
typedef ModPowerSystems::PhasorSinglePhase::Generations::SolarGenerator ModSolarGenerator;
typedef ModPowerSystems::PhasorSinglePhase::Storage::Battery ModBattery;
typedef ModPowerSystems::PhasorSinglePhase::Households::Household ModHousehold;
typedef PowerGrids::SynchronousMachineDynamics SynMachineDyn;




namespace ModelicaWorkshop {

typedef struct color {
  int R, G, B;
} color;

class Connection : public ModBaseClass {
 public:
  Connection(const BusBar* busbar);  //Delegate Constructor
  Connection(const BusBar* busbar, const ModConnectivityNode* connectivity_node);
  Connection(const BusBar* busbar, const ModSlack* slack);
  Connection(const BusBar* busbar, const ModPQLoad* pq_load);
  Connection(const BusBar* busbar, const ModBreaker* breaker);
  Connection(const BusBar* busbar, const ModHousehold* household);
  Connection(const BusBar* busbar, const ModPVNode* pvNode);
  Connection(const BusBar* busbar, const ModPiLine* pi_line);
  Connection(const BusBar* busbar, const ModTransformer* transformer);
  Connection(const BusBar* busbar, const ModWindGenerator* wind_generator);
  Connection(const BusBar* busbar, const ModSolarGenerator* solar_generator);
  Connection(const BusBar* busbar, const ModBattery* battery);

  virtual ~Connection();

 public:
  static void setConfigManager(ConfigManager* manager);
  template<typename T> void cal_middle_points(T *Componet);
  std::string output_points() const;
  void set_lineColor(color lineColor) {
    this->_lineColor = lineColor;
  };
  std::string lineColor() {
    return "{" + std::to_string(_lineColor.R) + "," + std::to_string(_lineColor.G) + "," + std::to_string(_lineColor.B) + "}";
  };
  void draw_connection(ctemplate::TemplateDictionary *dictionary);
  void error_log();

 private:
  static ConfigManager *configManager;
  std::string _port1, _port2, _port1Short, _port2Short;  //port (Short versions used for distaix templates)

  Point _p1, _p2;
  std::string _terminalId1, _terminalId2;  //terminal

  std::string _connection_type = "Line";
  color _lineColor = { 0, 0, 0 };
  std::vector<Point> _points;
};

} /* namespace ModelicaWorkshop */

#endif /* SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_CONNECTION_H_ */
