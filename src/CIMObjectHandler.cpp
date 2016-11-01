/*
 * CIMObjectHandler.cpp
 *
 */

#include "CIMObjectHandler.h"

using namespace ModelicaWorkshop;

CIMObjectHandler::CIMObjectHandler()
{
	// TODO Auto-generated constructor stub
}

CIMObjectHandler::CIMObjectHandler(std::vector<BaseClass*>&& CIMObjects):_CIMObjects(CIMObjects)
{

}

CIMObjectHandler::~CIMObjectHandler()
{
	// TODO Auto-generated destructor stub
}

bool CIMObjectHandler::generate_modelica_code(const std::string filename)
{
		ctemplate::TemplateDictionary* dict = new ctemplate::TemplateDictionary("MODELICA");

		this->handle_SystemSettings(filename, dict);

		for (BaseClass* Object : this->_CIMObjects)
		{
			//TopologicalNode, convert to BusBar
			if(auto *tpNode = dynamic_cast<IEC61970::Base::Topology::TopologicalNode*>(Object)){
				BusBarObj busBar = this->handle_TopologicalNode(tpNode, dict);

				std::list<IEC61970::Base::Core::Terminal*>::iterator terminal_itor;
				for(terminal_itor = tpNode->Terminal.begin();terminal_itor != tpNode->Terminal.end(); ++terminal_itor){

					if(auto *externalNI = dynamic_cast<IEC61970::Base::Wires::ExternalNetworkInjection*>((*terminal_itor)->ConductingEquipment)){

						SlackObj slack = this->handle_ExternalNI(tpNode, (*terminal_itor), externalNI, dict);

						if((*terminal_itor)->connected == true){
							Connection conn(&busBar, &slack, (*terminal_itor)->sequenceNumber);
							connectionQueue.push(conn);
						}

					} else if(auto *powerTrafo = dynamic_cast<IEC61970::Base::Wires::PowerTransformer*>((*terminal_itor)->ConductingEquipment)) {

						auto trafo = this->handle_PowerTransformer(tpNode, (*terminal_itor), powerTrafo, dict);

						if((*terminal_itor)->connected == true){
							Connection conn(&busBar, &trafo, (*terminal_itor)->sequenceNumber);
							connectionQueue.push(conn);
						}

					} else if(auto *acLine = dynamic_cast<IEC61970::Base::Wires::ACLineSegment*>((*terminal_itor)->ConductingEquipment)){

						auto piLine = this->handle_ACLineSegment(tpNode, (*terminal_itor), acLine, dict);

						if((*terminal_itor)->connected == true){
							Connection conn(&busBar, &piLine, (*terminal_itor)->sequenceNumber);
							connectionQueue.push(conn);
						}

					} else if(auto *energyConsumer = dynamic_cast<IEC61970::Base::Wires::EnergyConsumer*>((*terminal_itor)->ConductingEquipment)) {

						auto pqLoad = this->handle_EnergyConsumer(tpNode, (*terminal_itor), energyConsumer, dict);

						if((*terminal_itor)->connected == true){
							Connection conn(&busBar, &pqLoad, (*terminal_itor)->sequenceNumber);
							connectionQueue.push(conn);
						}

					} else if(auto *synMachine = dynamic_cast<IEC61970::Base::Wires::SynchronousMachine*>((*terminal_itor)->ConductingEquipment)) {

						auto genericGenerator = this->handle_SynchronousMachine(tpNode, (*terminal_itor), synMachine, dict);

						if((*terminal_itor)->connected == true){
							Connection conn(&busBar, &genericGenerator, (*terminal_itor)->sequenceNumber);
							connectionQueue.push(conn);
						}

					}
				}
			}

		}

		this->handle_Connection(dict);

		std::string modelica_output;
		ctemplate::ExpandTemplate("build/resource/modelica.tpl", ctemplate::STRIP_BLANK_LINES, dict, &modelica_output);
		std::cout << modelica_output;
		// Write to file
		std::ofstream file;
		file.open("test/" + filename + ".mo", std::fstream::trunc);
		if(file.good())
			file << modelica_output;
		file.close();
		modelica_output.clear();

		return true;
}


/**
* TopologicalNode
* Convert to BusBar in Modelica
*/
bool CIMObjectHandler::handle_SystemSettings(const std::string filename, ctemplate::TemplateDictionary* dict)
{
	//Modelica_Header
	dict->AddSectionDictionary("HEADER_FOOTER_SECTION");
	dict->SetValue("GRID_NAME", filename);

	//Global Settings
	dict->AddSectionDictionary("SYSTEM_SETTINGS_SECTION");

	auto *System = new ModPowerSystems::System(0,0,400,-400);
	System->set_template_values(dict);

	delete System;

	return true;
}


/**
* TopologicalNode
* Convert to BusBar in Modelica
*/
BusBarObj CIMObjectHandler::handle_TopologicalNode(const TPNodePtr tpNode, ctemplate::TemplateDictionary* dict)
{
	BusBarObj BusBar;

	if(tpNode->BaseVoltage->name.find("LV") != std::string::npos){
		BusBar.set_Vnom(tpNode->BaseVoltage->nominalVoltage.value);
	} else if(tpNode->BaseVoltage->name.find("V") != std::string::npos){
		BusBar.set_Vnom(tpNode->BaseVoltage->nominalVoltage.value*1000);
	} else {
		BusBar.set_Vnom(tpNode->BaseVoltage->nominalVoltage.value*1000);
	}


	BusBar.set_name(name_in_modelica(tpNode->name));
	BusBar.annotation.placement.visible = true;

	std::list<IEC61970::Base::DiagramLayout::DiagramObject*>::iterator diagram_itor;
	std::list<IEC61970::Base::DiagramLayout::DiagramObjectPoint*>::iterator points_itor;
	IEC61970::Base::DiagramLayout::DiagramObjectPoint tmp_points;

	for(diagram_itor = tpNode->DiagramObjects.begin(); diagram_itor != tpNode->DiagramObjects.end(); ++diagram_itor)
	{
		BusBar.annotation.placement.transfomation.rotation = (*diagram_itor)->rotation.value;

		for(points_itor=(*diagram_itor)->DiagramObjectPoints.begin(); points_itor != (*diagram_itor)->DiagramObjectPoints.end(); ++points_itor)
		{
			tmp_points.xPosition += (*points_itor)->xPosition;
			tmp_points.yPosition += (*points_itor)->yPosition;
		}

		std::size_t size = (*diagram_itor)->DiagramObjectPoints.size();
		tmp_points = convert_coordinate(tmp_points.xPosition/size,tmp_points.yPosition/size);//Get the average middle position of Graph
		BusBar.annotation.placement.transfomation.origin.x = tmp_points.xPosition;
		BusBar.annotation.placement.transfomation.origin.y = tmp_points.yPosition;

		ctemplate::TemplateDictionary* busBar_dict = dict->AddIncludeDictionary("BUSBAR_DICT");
		busBar_dict->SetFilename("build/resource/BusBar.tpl");
		BusBar.set_template_values(busBar_dict);
	}

	return BusBar;
}

/**
* ConductingEquipment of Terminal
* ConductingEquipment cast to ExternalNetworkInjection
* Convert to Slack in Modelica
*/

SlackObj CIMObjectHandler::handle_ExternalNI(const TPNodePtr tpNode, const TerminalPtr terminal, const ExNIPtr externalNI, ctemplate::TemplateDictionary* dict)
{
	SlackObj Slack;

	Slack.set_Vnom(tpNode->BaseVoltage->nominalVoltage.value);
	Slack.set_name(name_in_modelica(externalNI->name));
	Slack.annotation.placement.visible = true;

	std::list<IEC61970::Base::DiagramLayout::DiagramObject*>::iterator diagram_itor;
	std::list<IEC61970::Base::DiagramLayout::DiagramObjectPoint*>::iterator points_itor;
	IEC61970::Base::DiagramLayout::DiagramObjectPoint tmp_points;
	tmp_points.xPosition = 0;
	tmp_points.yPosition = 0;

	for(diagram_itor = externalNI->DiagramObjects.begin(); diagram_itor != externalNI->DiagramObjects.end(); ++diagram_itor)
	{
		Slack.annotation.placement.transfomation.rotation = (*diagram_itor)->rotation.value - 90;

		for(points_itor=(*diagram_itor)->DiagramObjectPoints.begin(); points_itor != (*diagram_itor)->DiagramObjectPoints.end(); ++points_itor)
		{
			tmp_points.xPosition += (*points_itor)->xPosition;
			tmp_points.yPosition += (*points_itor)->yPosition;
		}

		std::size_t size = (*diagram_itor)->DiagramObjectPoints.size();
		tmp_points = convert_coordinate(tmp_points.xPosition/size,tmp_points.yPosition/size);
		Slack.annotation.placement.transfomation.origin.x = tmp_points.xPosition;
		Slack.annotation.placement.transfomation.origin.y = tmp_points.yPosition;

		if(terminal->sequenceNumber == 0 || terminal->sequenceNumber == 1){
			ctemplate::TemplateDictionary* slack_dict = dict->AddIncludeDictionary("SLACK_DICT");
			slack_dict->SetFilename("build/resource/Slack.tpl");
			Slack.set_template_values(slack_dict);
		}
	}

	return Slack;
}

/**
* ConductingEquipment of Terminal
* ConductingEquipment cast to ACLineSegment
* Convert to PiLine in Modelica
*/
PiLineObj CIMObjectHandler::handle_ACLineSegment(const TPNodePtr tpNode, const TerminalPtr terminal, const AcLinePtr acLine, ctemplate::TemplateDictionary* dict)
{
	PiLineObj Piline;

	Piline.set_name(name_in_modelica(acLine->name));
	Piline.set_r(acLine->r.value);
	Piline.set_x(acLine->x.value);

	Piline.annotation.placement.visible = true;

	std::list<IEC61970::Base::DiagramLayout::DiagramObject*>::iterator diagram_itor;
	std::list<IEC61970::Base::DiagramLayout::DiagramObjectPoint*>::iterator points_itor;
	IEC61970::Base::DiagramLayout::DiagramObjectPoint tmp_points;
	tmp_points.xPosition = 0;
	tmp_points.yPosition = 0;

	for(diagram_itor=acLine->DiagramObjects.begin();diagram_itor != acLine->DiagramObjects.end(); ++diagram_itor){

		Piline.annotation.placement.transfomation.rotation = (*diagram_itor)->rotation.value - 90;

		for(points_itor=(*diagram_itor)->DiagramObjectPoints.begin(); points_itor != (*diagram_itor)->DiagramObjectPoints.end(); ++points_itor) {

			tmp_points.xPosition += (*points_itor)->xPosition;
			tmp_points.yPosition += (*points_itor)->yPosition;
		}

		std::size_t size = (*diagram_itor)->DiagramObjectPoints.size();
		tmp_points = convert_coordinate(tmp_points.xPosition/size,tmp_points.yPosition/size);
		Piline.annotation.placement.transfomation.origin.x = tmp_points.xPosition;
		Piline.annotation.placement.transfomation.origin.y = tmp_points.yPosition;

		if(terminal->sequenceNumber == 0 || terminal->sequenceNumber == 1){
			ctemplate::TemplateDictionary* piLine_dict = dict->AddIncludeDictionary("PILINE_DICT");
			piLine_dict->SetFilename("build/resource/PiLine.tpl");
			Piline.set_template_values(piLine_dict);
		}
	}

	return Piline;
}


/**
* ConductingEquipment of Terminal
* ConductingEquipment cast to PowerTransformer
* Convert to Transformer in Modelica
*/

TransformerObj CIMObjectHandler::handle_PowerTransformer(const TPNodePtr tpNode, const TerminalPtr terminal, const TrafoPtr powerTrafo, ctemplate::TemplateDictionary* dict)
{

	TransformerObj Trafo;

	Trafo.set_name(name_in_modelica(powerTrafo->name));
	Trafo.set_Vnom1(tpNode->BaseVoltage->nominalVoltage.value);
	Trafo.set_Vnom1(tpNode->BaseVoltage->nominalVoltage.value);
	Trafo.annotation.placement.visible = true;

	std::list<IEC61970::Base::DiagramLayout::DiagramObject*>::iterator diagram_itor;
	std::list<IEC61970::Base::DiagramLayout::DiagramObjectPoint*>::iterator points_itor;
	IEC61970::Base::DiagramLayout::DiagramObjectPoint tmp_points;
	tmp_points.xPosition = 0;
	tmp_points.yPosition = 0;

	for(diagram_itor=powerTrafo->DiagramObjects.begin(); diagram_itor != powerTrafo->DiagramObjects.end(); ++diagram_itor){

		Trafo.annotation.placement.transfomation.rotation = (*diagram_itor)->rotation.value - 90;

		//calculate the middle points of the position.
		for(points_itor=(*diagram_itor)->DiagramObjectPoints.begin(); points_itor != (*diagram_itor)->DiagramObjectPoints.end(); ++points_itor) {

			tmp_points.xPosition += (*points_itor)->xPosition;
			tmp_points.yPosition += (*points_itor)->yPosition;
		}

		std::size_t size = (*diagram_itor)->DiagramObjectPoints.size();
		tmp_points = convert_coordinate(tmp_points.xPosition/size,tmp_points.yPosition/size);
		Trafo.annotation.placement.transfomation.origin.x = tmp_points.xPosition;
		Trafo.annotation.placement.transfomation.origin.y = tmp_points.yPosition;

		if(terminal->sequenceNumber == 0 || terminal->sequenceNumber == 1){
			ctemplate::TemplateDictionary* powerTrafo_dict = dict->AddIncludeDictionary("TRANSFORMER_DICT");
			powerTrafo_dict->SetFilename("build/resource/Transformer.tpl");
			Trafo.set_template_values(powerTrafo_dict);
		}
	}

	return Trafo;
}

/**
* ConductingEquipment of Terminal
* ConductingEquipment cast to EnergyConsumer
* Convert to PQLoad in Modelica
*/
PQLoadObj  CIMObjectHandler::handle_EnergyConsumer(const TPNodePtr tpNode, const TerminalPtr terminal, const EnergyConsumerPtr energyConsumer, ctemplate::TemplateDictionary* dict)
{
	PQLoadObj PQLoad;

	PQLoad.set_name(name_in_modelica(energyConsumer->name));
	PQLoad.set_Pnom(energyConsumer->p.value);
	PQLoad.set_Pnom_displayUnit(cast_unit(energyConsumer->p.multiplier, energyConsumer->p.unit));
	PQLoad.set_Qnom(energyConsumer->q.value);
	PQLoad.set_Qnom_displayUnit(cast_unit(energyConsumer->q.multiplier, energyConsumer->q.unit));
	PQLoad.set_Vnom(tpNode->BaseVoltage->nominalVoltage.value);
	PQLoad.set_Vnom_displayUnit(cast_unit(tpNode->BaseVoltage->nominalVoltage.multiplier, tpNode->BaseVoltage->nominalVoltage.unit));
	PQLoad.annotation.placement.visible = true;

	std::list<IEC61970::Base::DiagramLayout::DiagramObject*>::iterator diagram_itor;
	std::list<IEC61970::Base::DiagramLayout::DiagramObjectPoint*>::iterator points_itor;

	IEC61970::Base::DiagramLayout::DiagramObjectPoint tmp_points;
	tmp_points.xPosition = 0;
	tmp_points.yPosition = 0;

	for(diagram_itor=energyConsumer->DiagramObjects.begin();diagram_itor != energyConsumer->DiagramObjects.end(); ++diagram_itor){

		PQLoad.annotation.placement.transfomation.rotation = (*diagram_itor)->rotation.value;

		for(points_itor=(*diagram_itor)->DiagramObjectPoints.begin(); points_itor != (*diagram_itor)->DiagramObjectPoints.end(); ++points_itor) {

			tmp_points.xPosition += (*points_itor)->xPosition;
			tmp_points.yPosition += (*points_itor)->yPosition;
		}

		std::size_t size = (*diagram_itor)->DiagramObjectPoints.size();
		tmp_points = convert_coordinate(tmp_points.xPosition/size,tmp_points.yPosition/size);
		PQLoad.annotation.placement.transfomation.origin.x = tmp_points.xPosition;
		PQLoad.annotation.placement.transfomation.origin.y = tmp_points.yPosition;

		if(terminal->sequenceNumber == 0 || terminal->sequenceNumber == 1){
			ctemplate::TemplateDictionary* pqLoad_dict = dict->AddIncludeDictionary("PQLOAD_DICT");
			pqLoad_dict->SetFilename("build/resource/PQLoad.tpl");
			PQLoad.set_template_values(pqLoad_dict);
		}

	}

	return PQLoad;
}

/**
* ConductingEquipment of Terminal
* ConductingEquipment cast to SynchronousMachine
* Convert to GenericGenerator in Modelica
*/
GenericGeneratorObj CIMObjectHandler::handle_SynchronousMachine(const TPNodePtr tpNode, const TerminalPtr terminal, const SynMachinePtr synMachine, ctemplate::TemplateDictionary* dict)
{
	GenericGeneratorObj GenericGenerator;

	GenericGenerator.set_name(name_in_modelica(synMachine->name));
	GenericGenerator.annotation.placement.visible = true;

	std::list<IEC61970::Base::DiagramLayout::DiagramObject*>::iterator diagram_itor;
	std::list<IEC61970::Base::DiagramLayout::DiagramObjectPoint*>::iterator points_itor;
	IEC61970::Base::DiagramLayout::DiagramObjectPoint tmp_points;
	tmp_points.xPosition = 0;
	tmp_points.yPosition = 0;

	for(diagram_itor = synMachine->DiagramObjects.begin(); diagram_itor != synMachine->DiagramObjects.end(); ++diagram_itor)
	{
		GenericGenerator.annotation.placement.transfomation.rotation = (*diagram_itor)->rotation.value;

		for(points_itor=(*diagram_itor)->DiagramObjectPoints.begin(); points_itor != (*diagram_itor)->DiagramObjectPoints.end(); ++points_itor)
			{
			tmp_points.xPosition += (*points_itor)->xPosition;
			tmp_points.yPosition += (*points_itor)->yPosition;
		}

		std::size_t size = (*diagram_itor)->DiagramObjectPoints.size();
		tmp_points = convert_coordinate(tmp_points.xPosition/size,tmp_points.yPosition/size);
		GenericGenerator.annotation.placement.transfomation.origin.x = tmp_points.xPosition;
		GenericGenerator.annotation.placement.transfomation.origin.y = tmp_points.yPosition;

		if(terminal->sequenceNumber == 0 || terminal->sequenceNumber == 1){
			ctemplate::TemplateDictionary* genericGenerator_dict = dict->AddIncludeDictionary("GENERICGENERATOR_DICT");
			genericGenerator_dict->SetFilename("build/resource/GenericGenerator.tpl");
			GenericGenerator.set_template_values(genericGenerator_dict);
		}
	}

	return GenericGenerator;

}


/**
* Create Connection
*/
bool CIMObjectHandler::handle_Connection(ctemplate::TemplateDictionary* dict){

	unsigned int size;
	size = connectionQueue.size();
	std::cout << "connectionQueue size: " << size << std::endl;
	while(!connectionQueue.empty())
	{
		ctemplate::TemplateDictionary* connection_dict = dict->AddIncludeDictionary(CONNECTIONS_DICT);
		connection_dict->SetFilename("build/resource/Connections.tpl");
		connectionQueue.front().draw_connection(connection_dict);
		connectionQueue.pop();
	}

	return true;
}

/**
* convert the coordinate system between different software
*/
IEC61970::Base::DiagramLayout::DiagramObjectPoint CIMObjectHandler::convert_coordinate(IEC61970::Base::Domain::Float x, IEC61970::Base::Domain::Float y)
{
	double trans_para[4] = {1,0,-1,0};
	IEC61970::Base::DiagramLayout::DiagramObjectPoint new_point;

	new_point.xPosition= trans_para[0]*x+trans_para[1];
	new_point.yPosition = trans_para[2]*y+trans_para[3];
	return new_point;
}

/**
* convert name adapt to the format in modelica
*/
std::string CIMObjectHandler::name_in_modelica(std::string original_name)
{
	std::string new_name = original_name;
	std::size_t i = new_name.find("-");
	std::size_t j = new_name.find(".");
	if (i < new_name.size())
		new_name = "CIM_" + new_name.replace(i,1,"_");
	if (j < new_name.size())
		new_name = "CIM_" + new_name.replace(j,1,"_");
	return new_name;
}
