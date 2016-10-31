/*
 * Connection.h
 *	Manager Connections in Modelica
 */

#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_CONNECTION_H_
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_CONNECTION_H_

#include "../ModBaseClass.h"
#include "../ModelicaClass.h"
#include <iomanip>
#include <sstream>

typedef ModPowerSystems::SinglePhase::Connections::BusBar BusBarObj;
typedef ModPowerSystems::SinglePhase::Sources::Slack SlackObj;
typedef ModPowerSystems::SinglePhase::Loads::PQLoad PQLoadObj;
typedef ModPowerSystems::SinglePhase::Lines::PiLine PiLineObj;
typedef ModPowerSystems::SinglePhase::Transformers::Transformer TransformerObj;
typedef ModPowerSystems::SinglePhase::Generations::GenericGenerator GenericGeneratorObj;
typedef ModPowerSystems::SinglePhase::Generations::WindGenerator WindGeneratorObj;

namespace ModelicaWorkshop {

	typedef struct color{
		int R, G, B;
	} color;

	class Connection: public ModBaseClass {
	public:
		Connection();
		Connection(const BusBarObj* BusBar, const SlackObj* Slack, int sn);
		Connection(const BusBarObj* BusBar, const PQLoadObj* PQLoad, int sn);
		Connection(const BusBarObj* BusBar, const PiLineObj* PiLine, int sn);
		Connection(const BusBarObj* BusBar, const TransformerObj* Transformer, int sn);
		Connection(const BusBarObj* BusBar, const GenericGeneratorObj* GenericGenerator, int sn);
		virtual ~Connection();
	public:
		std::string lineColor(){return "(" + std::to_string(_lineColor.R)+ "," + std::to_string(_lineColor.G) + "," + std::to_string(_lineColor.B) + ")";};

		void cal_middle_points();
		std::string print_points();
		bool draw_connection(ctemplate::TemplateDictionary *dictionary);
		void error_log();

	private:

		std::string _port1, _port2;//port
		std::string _terminalId1, _terminalId2;//terminal
		int _sequenceNumber;
		Point _p1, _p2;

		std::string _connection_type = "Line";
		color _lineColor = {0,0,0};

		bool is_connected = true;
		static std::map<std::string, std::string> connections_list;
		std::vector<Point> points;
	};

} /* namespace ModelicaWorkshop */

#endif /* SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_CONNECTION_H_ */
