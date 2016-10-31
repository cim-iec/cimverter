/*
 * Connection.cpp
 *
 *  Created on: Oct 26, 2016
 *      Author: root
 */

#include "Connection.h"

namespace ModelicaWorkshop {

	Connection::Connection()
	{
		// TODO Auto-generated constructor stub

	}

	Connection::Connection(BusBarObj* BusBar, SlackObj* Slack, int sn): _sequenceNumber(sn)
	{
		_node1 = BusBar->name();
		_terminalId1 = "T";
		_node1.append(".");
		_node1.append(_terminalId1);
		_p1.x = BusBar->annotation.placement.transfomation.origin.x;
		_p1.y = BusBar->annotation.placement.transfomation.origin.y;

		_node2 = Slack->name();
		_terminalId2 = "T";
		_node2.append(".");
		_node2.append(_terminalId2);
		_p2.x = Slack->annotation.placement.transfomation.origin.x;
		_p2.y = Slack->annotation.placement.transfomation.origin.y;
		this->cal_middle_points();
	}

	Connection::Connection(BusBarObj* BusBar, PQLoadObj* PQLoad, int sn): _sequenceNumber(sn)
	{
		_node1 = BusBar->name();
		_terminalId1 = "T";
		_node1.append(".");
		_node1.append(_terminalId1);
		_p1.x = BusBar->annotation.placement.transfomation.origin.x;
		_p1.y = BusBar->annotation.placement.transfomation.origin.y;

		_node2 = PQLoad->name();
		_terminalId2 = "T";
		_node2.append(".");
		_node2.append(_terminalId2);
		_p2.x = PQLoad->annotation.placement.transfomation.origin.x;
		_p2.y = PQLoad->annotation.placement.transfomation.origin.y;
		this->cal_middle_points();
	}

	Connection::Connection(BusBarObj* BusBar, PiLineObj* PiLine, int sn): _sequenceNumber(sn)
	{
		_node1 = BusBar->name();
		_terminalId1 = "T";
		_node1.append(".");
		_node1.append(_terminalId1);
		_p1.x = BusBar->annotation.placement.transfomation.origin.x;
		_p1.y = BusBar->annotation.placement.transfomation.origin.y;

		if(_sequenceNumber == 0 || _sequenceNumber == 1){
			_terminalId2 = "T1";
		} else if(_sequenceNumber == 2 ){
			_terminalId2 = "T2";
		}
		_node2 = PiLine->name();
		_node2.append(".");
		_node2.append(_terminalId2);
		_p2.x = PiLine->annotation.placement.transfomation.origin.x;
		_p2.y = PiLine->annotation.placement.transfomation.origin.y;
		this->cal_middle_points();
	}

	Connection::Connection(BusBarObj* BusBar, TransformerObj* Transformer, int sn): _sequenceNumber(sn)
	{
		_node1 = BusBar->name();
		_terminalId1 = "T";
		_node1.append(".");
		_node1.append(_terminalId1);
		_p1.x = BusBar->annotation.placement.transfomation.origin.x;
		_p1.y = BusBar->annotation.placement.transfomation.origin.y;

		if(_sequenceNumber == 0 || _sequenceNumber == 1){
			_terminalId2 = "T1";
		} else if(_sequenceNumber == 2 ){
			_terminalId2 = "T2";
		}
		_node2 = Transformer->name();
		_node2.append(".");
		_node2.append(_terminalId2);
		_p2.x = Transformer->annotation.placement.transfomation.origin.x;
		_p2.y = Transformer->annotation.placement.transfomation.origin.y;
		this->cal_middle_points();
	}

	Connection::~Connection()
	{
		// TODO Auto-generated destructor stub
	}

	void Connection::cal_middle_points()
	{
		if(_p1.x == _p2.x || _p1.y == _p2.y)
		{
			points.push_back(_p1);
			points.push_back(_p2);

		} else {
			Point _mp1 = {_p1.x,(_p1.y+_p2.y)/2};
			Point _mp2 = {_p2.x,(_p1.y+_p2.y)/2};

			points.push_back(_p1);
			points.push_back(_mp1);
			points.push_back(_mp2);
			points.push_back(_p2);
		}

	}
	/*
	 * Print the formatted points
	 */

	std::string Connection::print_points()
	{

		if(points.size() == 2){

			std::stringstream stream[4];
			stream[0] << std::fixed << std::setprecision(2) << points[0].x;
			stream[1] << std::fixed << std::setprecision(2) << points[0].y;
			stream[2] << std::fixed << std::setprecision(2) << points[1].x;
			stream[3] << std::fixed << std::setprecision(2) << points[1].y;

			std::string p1 = "{" + stream[0].str() + "," + stream[1].str() + "}";
			std::string p2 = "{" + stream[2].str() + "," + stream[3].str() + "}";

			return p1 + "," + p2;

		} else if (points.size() == 4){

			std::stringstream stream[8];
			stream[0] << std::fixed << std::setprecision(2) << points[0].x;
			stream[1] << std::fixed << std::setprecision(2) << points[0].y;
			stream[2] << std::fixed << std::setprecision(2) << points[1].x;
			stream[3] << std::fixed << std::setprecision(2) << points[1].y;
			stream[4] << std::fixed << std::setprecision(2) << points[2].x;
			stream[5] << std::fixed << std::setprecision(2) << points[2].y;
			stream[6] << std::fixed << std::setprecision(2) << points[3].x;
			stream[7] << std::fixed << std::setprecision(2) << points[3].y;

			std::string p1 = "{" + stream[0].str() + "," + stream[1].str() + "}";
			std::string p2 = "{" + stream[2].str() + "," + stream[3].str() + "}";
			std::string p3 = "{" + stream[4].str() + "," + stream[5].str() + "}";
			std::string p4 = "{" + stream[6].str() + "," + stream[7].str() + "}";

			return p1 + "," + p2 + "," + p3 + "," + p4;
		}
	}

	bool Connection::draw_connection(ctemplate::TemplateDictionary *dictionary)
	{

		dictionary->SetValue("CONNECTION_TYPE", _connection_type);
		dictionary->SetValue("NODE1",_node1);
		dictionary->SetValue("NODE2",_node2);
		dictionary->SetValue("COLOR",this->lineColor());
		dictionary->SetValue("POINTS",this->print_points());

		return true;
	}

	void Connection::error_log()
	{
		std::cout << "Connection cannot create! ";

	}


} /* namespace ModelicaWorkshop */
