/*
 * Connection.h
 *	Manager Connections in Modelica
 */

#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_CONNECTION_H_
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_CONNECTION_H_

#include "../ModBaseClass.h"
#include "../ModelicaClass.h"

#include <cmath>

typedef ModPowerSystems::SinglePhase::Connections::BusBar BusBar;
typedef ModPowerSystems::SinglePhase::Connections::ConnectivityNode ConnectivityNode;
typedef ModPowerSystems::SinglePhase::Sources::Slack Slack;
typedef ModPowerSystems::SinglePhase::Loads::PQLoad PQLoad;
typedef ModPowerSystems::SinglePhase::Lines::PiLine PiLine;
typedef ModPowerSystems::SinglePhase::Transformers::Transformer Transformer;
typedef ModPowerSystems::SinglePhase::Generations::GenericGenerator GenericGenerator;
typedef ModPowerSystems::SinglePhase::Generations::WindGenerator WindGenerator;

namespace ModelicaWorkshop {

typedef struct color {
  int R, G, B;
} color;

class Connection : public ModBaseClass {
 public:
  Connection(const BusBar* busbar, int sn);  //Delegate Constructor
  Connection(const BusBar* busbar, const ConnectivityNode* ConnectivityNode, int sn);
  Connection(const BusBar* busbar, const Slack* slack, int sn);
  Connection(const BusBar* busbar, const PQLoad* pq_load, int sn);
  Connection(const BusBar* busbar, const PiLine* PiLine, int sn);
  Connection(const BusBar* busbar, const Transformer* transformer, int sn);
  Connection(const BusBar* busbar, const GenericGenerator* GenericGenerator, int sn);
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
  bool is_connected = true;

 private:
  std::string _port1, _port2;  //port
  Point _p1, _p2;
  std::string _terminalId1, _terminalId2;  //terminal
  int _sequenceNumber;

  std::string _connection_type = "Line";
  color _lineColor = { 0, 0, 0 };
  std::vector<Point> _points;
};

} /* namespace ModelicaWorkshop */

#endif /* SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_CONNECTION_H_ */
