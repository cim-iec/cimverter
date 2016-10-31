/*
 * Connection.h
 *
 */

#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_VIRTUALELEMENTS_CONNECTION_H_
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_VIRTUALELEMENTS_CONNECTION_H_

#include <iomanip>
#include <sstream>
#include "../../ModBaseClass.h"
#include "../../ModelicaClass.h"

typedef ModPowerSystems::SinglePhase::Connections::BusBar BusBarObj;
typedef ModPowerSystems::SinglePhase::Sources::Slack SlackObj;
typedef ModPowerSystems::SinglePhase::Loads::PQLoad PQLoadObj;
typedef ModPowerSystems::SinglePhase::Lines::PiLine PiLineObj;
typedef ModPowerSystems::SinglePhase::Transformers::Transformer TransformerObj;

namespace ModelicaWorkshop {

	typedef struct color{
		int R, G, B;
	} color;

	class Connection: public ModBaseClass {
	public:
		Connection();
		Connection(BusBarObj* BusBar, SlackObj* Slack, int sn);
		Connection(BusBarObj* BusBar, PQLoadObj* PQLoad, int sn);
		Connection(BusBarObj* BusBar, PiLineObj* PiLine, int sn);
		Connection(BusBarObj* BusBar, TransformerObj* Transformer, int sn);
		virtual ~Connection();
	public:
		std::string lineColor(){return "(" + std::to_string(_lineColor.R)+ "," + std::to_string(_lineColor.G) + "," + std::to_string(_lineColor.B) + ")";};

		void cal_middle_points();
		std::string print_points();
		bool draw_connection(ctemplate::TemplateDictionary *dictionary);
		void error_log();

	private:

		std::string _node1, _node2;//node
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

#endif /* SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_VIRTUALELEMENTS_CONNECTION_H_ */
