/*
 * Connection.h
 *	Manager Connections in Modelica
 */

#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_CONNECTION_H_
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_CONNECTION_H_

#include "../ModBaseClass.h"
#include "../ModelicaClass.h"

#include <cmath>

typedef ModPowerSystems::PhasorSinglePhase::Connections::BusBar BusBar;
typedef ModPowerSystems::PhasorSinglePhase::Connections::ConnectivityNode ConnectivityNode;
typedef ModPowerSystems::PhasorSinglePhase::Sources::Slack Slack;
typedef ModPowerSystems::PhasorSinglePhase::Loads::PQLoad PQLoad;
typedef ModPowerSystems::PhasorSinglePhase::Loads::ZLoad ZLoad;
typedef ModPowerSystems::PhasorSinglePhase::Lines::PiLine PiLine;
typedef ModPowerSystems::PhasorSinglePhase::Lines::RxLine RxLine;
typedef ModPowerSystems::PhasorSinglePhase::Transformers::Transformer Transformer;
typedef ModPowerSystems::PhasorSinglePhase::Generations::GenericGenerator GenericGenerator;
typedef ModPowerSystems::PhasorSinglePhase::Generations::WindGenerator WindGenerator;
typedef ModPowerSystems::PhasorSinglePhase::Generations::SolarGenerator SolarGenerator;
typedef ModPowerSystems::PhasorSinglePhase::Storage::Battery Battery;
typedef ModPowerSystems::PhasorSinglePhase::Households::Household Household;

namespace ModelicaWorkshop {

typedef struct color {
  int R, G, B;
} color;

class Connection : public ModBaseClass {
 public:
  Connection(const BusBar* busbar);  //Delegate Constructor
  Connection(const BusBar* busbar, const ConnectivityNode* connectivity_node);
  Connection(const BusBar* busbar, const Slack* slack);
  Connection(const BusBar* busbar, const PQLoad* pq_load);
  Connection(const BusBar* busbar, const Household* household);
  Connection(const BusBar* busbar, const PiLine* pi_line);
  Connection(const BusBar* busbar, const Transformer* transformer);
  Connection(const BusBar* busbar, const WindGenerator* wind_generator);
  Connection(const BusBar* busbar, const SolarGenerator* solar_generator);
  Connection(const BusBar* busbar, const Battery* battery);

  virtual ~Connection();

 public:
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
  std::string _port1, _port2, _port1Short, _port2Short;  //port (Short versions used for distaix templates)
  Point _p1, _p2;
  std::string _terminalId1, _terminalId2;  //terminal

  std::string _connection_type = "Line";
  color _lineColor = { 0, 0, 0 };
  std::vector<Point> _points;
};

} /* namespace ModelicaWorkshop */

#endif /* SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_CONNECTION_H_ */
