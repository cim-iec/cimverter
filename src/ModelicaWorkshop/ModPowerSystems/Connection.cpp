/*
 * Connection.cpp
 *
 */

#include "Connection.h"

namespace ModelicaWorkshop {

	Connection::Connection(const BusBar* busbar, int sn): _sequenceNumber(sn)
	{
		_port1 = busbar->name();
		_terminalId1 = "T";
		_port1.append(".");
		_port1.append(_terminalId1);
		_p1.x = busbar->annotation.placement.transfomation.origin.x;
		_p1.y = busbar->annotation.placement.transfomation.origin.y;

	}

	Connection::Connection(const BusBar* busbar, const Slack* slack, int sn): Connection(busbar, sn)
	{
		_port2 = slack->name();
		_terminalId2 = "T";
		_port2.append(".");
		_port2.append(_terminalId2);
		_p2.x = slack->annotation.placement.transfomation.origin.x;
		_p2.y = slack->annotation.placement.transfomation.origin.y;
		this->cal_middle_points(slack);
	}

	Connection::Connection(const BusBar* busbar, const PQLoad* pq_load, int sn): Connection(busbar, sn)
	{

		//connection point's position auto adjust.
		if(pq_load->annotation.placement.transfomation.rotation == 0 || pq_load->annotation.placement.transfomation.rotation == 359 || pq_load->annotation.placement.transfomation.rotation == 360){
			_p2.x = pq_load->annotation.placement.transfomation.origin.x;
			_p2.y = pq_load->annotation.placement.transfomation.origin.y + pq_load->annotation.placement.transfomation.extent.second.y;
		} else if (pq_load->annotation.placement.transfomation.rotation == 90 || pq_load->annotation.placement.transfomation.rotation == -270 ){
			_p2.x = pq_load->annotation.placement.transfomation.origin.x + pq_load->annotation.placement.transfomation.extent.second.x;
			_p2.y = pq_load->annotation.placement.transfomation.origin.y;
		} else if (pq_load->annotation.placement.transfomation.rotation == 180 || pq_load->annotation.placement.transfomation.rotation == -180 ){
			_p2.x = pq_load->annotation.placement.transfomation.origin.x;
			_p2.y = pq_load->annotation.placement.transfomation.origin.y + pq_load->annotation.placement.transfomation.extent.first.y;
		} else  if (pq_load->annotation.placement.transfomation.rotation == -90 || pq_load->annotation.placement.transfomation.rotation == 270 ){
			_p2.x = pq_load->annotation.placement.transfomation.origin.x + pq_load->annotation.placement.transfomation.extent.first.x;
			_p2.y = pq_load->annotation.placement.transfomation.origin.y;
		}

		_port2 = pq_load->name();
		_terminalId2 = "T";
		_port2.append(".");
		_port2.append(_terminalId2);

		this->cal_middle_points(pq_load);
	}

	Connection::Connection(const BusBar* busbar, const ConnectivityNode* connectivity_node, int sn): Connection(busbar, sn)
	{
	  _port2 = connectivity_node->name();
	  _terminalId2 = "T";
	  _port2.append(".");
	  _port2.append(_terminalId2);
	  _p2.x = connectivity_node->annotation.placement.transfomation.origin.x;
	  _p2.y = connectivity_node->annotation.placement.transfomation.origin.y;
	   this->cal_middle_points(connectivity_node);
	 }

	Connection::Connection(const BusBar* busbar, const PiLine* pi_line, int sn): Connection(busbar, sn)
	{

		if(_sequenceNumber == 0 || _sequenceNumber == 1){
			_terminalId2 = "T1";
			if(pi_line->annotation.placement.transfomation.rotation == 90 || pi_line->annotation.placement.transfomation.rotation == -90 ){
				_p2.x = pi_line->annotation.placement.transfomation.origin.x;
				_p2.y = pi_line->annotation.placement.transfomation.origin.y + pi_line->annotation.placement.transfomation.extent.first.y;
			} else {
				_p2.x = pi_line->annotation.placement.transfomation.origin.x + pi_line->annotation.placement.transfomation.extent.first.x;
				_p2.y = pi_line->annotation.placement.transfomation.origin.y;
			}
		} else if(_sequenceNumber == 2 ){
			_terminalId2 = "T2";
			if(busbar->annotation.placement.transfomation.rotation == 90 || pi_line->annotation.placement.transfomation.rotation == -90 ){
				_p2.x = pi_line->annotation.placement.transfomation.origin.x;
				_p2.y = pi_line->annotation.placement.transfomation.origin.y + pi_line->annotation.placement.transfomation.extent.second.y;
			} else {
				_p2.x = pi_line->annotation.placement.transfomation.origin.x + pi_line->annotation.placement.transfomation.extent.second.x;
				_p2.y = pi_line->annotation.placement.transfomation.origin.y;
			}
		}
		_port2 = pi_line->name();
		_port2.append(".");
		_port2.append(_terminalId2);

		this->cal_middle_points(pi_line);
	}

	Connection::Connection(const BusBar* busbar, const Transformer* transformer, int sn): Connection(busbar, sn)
	{

		if(_sequenceNumber == 0 || _sequenceNumber == 1){
			_terminalId2 = "T1";
			if(transformer->annotation.placement.transfomation.rotation == 90 || transformer->annotation.placement.transfomation.rotation == -90 ){
				_p2.x = transformer->annotation.placement.transfomation.origin.x;
				_p2.y = transformer->annotation.placement.transfomation.origin.y + transformer->annotation.placement.transfomation.extent.first.y;
			} else {
				_p2.x = transformer->annotation.placement.transfomation.origin.x + transformer->annotation.placement.transfomation.extent.first.x;
				_p2.y = transformer->annotation.placement.transfomation.origin.y;
			}
		} else if(_sequenceNumber == 2 ){
			_terminalId2 = "T2";
			if(transformer->annotation.placement.transfomation.rotation == 90 || transformer->annotation.placement.transfomation.rotation == -90 ){
				_p2.x = transformer->annotation.placement.transfomation.origin.x;
				_p2.y = transformer->annotation.placement.transfomation.origin.y + transformer->annotation.placement.transfomation.extent.second.y;
			} else {
				_p2.x = transformer->annotation.placement.transfomation.origin.x + transformer->annotation.placement.transfomation.extent.second.x;
				_p2.y = transformer->annotation.placement.transfomation.origin.y;
			}
		}
		_port2 = transformer->name();
		_port2.append(".");
		_port2.append(_terminalId2);

		this->cal_middle_points(transformer);
	}

	Connection::Connection(const BusBar* busbar, const GenericGenerator* generic_generator, int sn): Connection(busbar, sn)
	{
		_port2 = generic_generator->name();
		_terminalId2 = "T";
		_port2.append(".");
		_port2.append(_terminalId2);
		_p2.x = generic_generator->annotation.placement.transfomation.origin.x;
		_p2.y = generic_generator->annotation.placement.transfomation.origin.y;
		this->cal_middle_points(generic_generator);

	}

	Connection::~Connection()
	{
		// TODO Auto-generated destructor stub
	}

	template <typename T>
	void Connection::cal_middle_points(T *Componet)
	{
		if(_p1.x == _p2.x || _p1.y == _p2.y)
		{
			_points.push_back(_p1);
			_points.push_back(_p2);

		} else {

		  if(std::abs(_p1.x - _p2.x) <= std::abs(Componet->annotation.placement.transfomation.extent.first.x) || std::abs(_p1.x - _p2.x) <= std::abs(Componet->annotation.placement.transfomation.extent.first.y)){
		    Point _mp1 = {_p1.x,_p2.y};
		    _points.push_back(_p1);
		    _points.push_back(_mp1);
		    _points.push_back(_p2);

		  } else if (std::abs(_p1.y - _p2.y) <= std::abs(Componet->annotation.placement.transfomation.extent.first.x) || std::abs(_p1.y - _p2.y) <= std::abs(Componet->annotation.placement.transfomation.extent.first.y)){
		    Point _mp1 = {_p2.x,_p1.y};
		    _points.push_back(_p1);
		    _points.push_back(_mp1);
		    _points.push_back(_p2);

		  } else {
        Point _mp1 = {_p1.x,(_p1.y+_p2.y)/2};
        Point _mp2 = {_p2.x,(_p1.y+_p2.y)/2};

        _points.push_back(_p1);
        _points.push_back(_mp1);
        _points.push_back(_mp2);
        _points.push_back(_p2);
		  }
		}
	}

	/*
	 * Output the formatted points of modelica
	 */
	std::string Connection::output_points() const
	{

		if(_points.size() == 2){

			std::stringstream stream[4];
			stream[0] << std::fixed << std::setprecision(2) << _points[0].x;
			stream[1] << std::fixed << std::setprecision(2) << _points[0].y;
			stream[2] << std::fixed << std::setprecision(2) << _points[1].x;
			stream[3] << std::fixed << std::setprecision(2) << _points[1].y;

			std::string p1 = "{" + stream[0].str() + "," + stream[1].str() + "}";
			std::string p2 = "{" + stream[2].str() + "," + stream[3].str() + "}";

			return "{" + p1 + "," + p2 + "}";

		} else if (_points.size() == 3){

		  std::stringstream stream[6];
		  stream[0] << std::fixed << std::setprecision(2) << _points[0].x;
		  stream[1] << std::fixed << std::setprecision(2) << _points[0].y;
		  stream[2] << std::fixed << std::setprecision(2) << _points[1].x;
		  stream[3] << std::fixed << std::setprecision(2) << _points[1].y;
		  stream[4] << std::fixed << std::setprecision(2) << _points[2].x;
		  stream[5] << std::fixed << std::setprecision(2) << _points[2].y;

		  std::string p1 = "{" + stream[0].str() + "," + stream[1].str() + "}";
		  std::string p2 = "{" + stream[2].str() + "," + stream[3].str() + "}";
		  std::string p3 = "{" + stream[4].str() + "," + stream[5].str() + "}";

		  return "{" + p1 + "," + p2 + "," + p3 + "}";

		} else if (_points.size() == 4){

			std::stringstream stream[8];
			stream[0] << std::fixed << std::setprecision(2) << _points[0].x;
			stream[1] << std::fixed << std::setprecision(2) << _points[0].y;
			stream[2] << std::fixed << std::setprecision(2) << _points[1].x;
			stream[3] << std::fixed << std::setprecision(2) << _points[1].y;
			stream[4] << std::fixed << std::setprecision(2) << _points[2].x;
			stream[5] << std::fixed << std::setprecision(2) << _points[2].y;
			stream[6] << std::fixed << std::setprecision(2) << _points[3].x;
			stream[7] << std::fixed << std::setprecision(2) << _points[3].y;

			std::string p1 = "{" + stream[0].str() + "," + stream[1].str() + "}";
			std::string p2 = "{" + stream[2].str() + "," + stream[3].str() + "}";
			std::string p3 = "{" + stream[4].str() + "," + stream[5].str() + "}";
			std::string p4 = "{" + stream[6].str() + "," + stream[7].str() + "}";

			return "{" + p1 + "," + p2 + "," + p3 + "," + p4 + "}";
		}
	}

	void Connection::draw_connection(ctemplate::TemplateDictionary *dictionary)
	{
		dictionary->SetValue(CONNECTION_TYPE, _connection_type);
		dictionary->SetValue(PORT1,_port1);
		dictionary->SetValue(PORT2,_port2);
		dictionary->SetValue(COLOR,this->lineColor());
		dictionary->SetValue(POINTS,this->output_points());

	}

	void Connection::error_log()
	{
		std::cout << "Connection cannot create! ";

	}


} /* namespace ModelicaWorkshop */
