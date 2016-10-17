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

int CIMObjectHandler::terminal_count = 0;

bool CIMObjectHandler::generate_modelica_code(const std::string filename)
{
		std::map<IEC61970::Base::Core::ConductingEquipment*, IEC61970::Base::Core::Terminal*> tpmap;

		ctemplate::TemplateDictionary* dict = new ctemplate::TemplateDictionary("MODELICA");

		this->handle_GlobalSettings(filename, dict);

		for (BaseClass* Object : this->_CIMObjects)
		{
			//TopologicalNode, convert to BusBar
			if(auto *tpNode = dynamic_cast<IEC61970::Base::Topology::TopologicalNode*>(Object))
			{
				ctemplate::TemplateDictionary* busBar_dict = dict->AddIncludeDictionary("BUSBAR_DICT");
				busBar_dict->SetFilename("build/resource/BusBar.tpl");
				this->handle_TopologicalNode(tpNode, busBar_dict);

				std::list<IEC61970::Base::Core::Terminal*>::iterator terminal_itor;
				for(terminal_itor = tpNode->Terminal.begin();terminal_itor != tpNode->Terminal.end(); ++terminal_itor)
				{
					if(auto *externalNI = dynamic_cast<IEC61970::Base::Wires::ExternalNetworkInjection*>((*terminal_itor)->ConductingEquipment))
					{
						ctemplate::TemplateDictionary* slack_dict = dict->AddIncludeDictionary("SLACK_DICT");
						slack_dict->SetFilename("build/resource/Slack.tpl");
						this->handle_ExternalNI(tpNode, externalNI, slack_dict);
					}

					else if(auto *powerTrafo = dynamic_cast<IEC61970::Base::Wires::PowerTransformer*>((*terminal_itor)->ConductingEquipment))
					{
						ctemplate::TemplateDictionary* powerTrafo_dict = dict->AddIncludeDictionary("TRANSFORMER_DICT");
						powerTrafo_dict->SetFilename("build/resource/Transformer.tpl");
						this->handle_PowerTransformer(powerTrafo, powerTrafo_dict);
					}

					else if(auto *acLine = dynamic_cast<IEC61970::Base::Wires::ACLineSegment*>((*terminal_itor)->ConductingEquipment))
					{
						ctemplate::TemplateDictionary* piLine_dict = dict->AddIncludeDictionary("PILINE_DICT");
						piLine_dict->SetFilename("build/resource/PiLine.tpl");
						this->handle_ACLineSegment(acLine,piLine_dict);
					}

					else if(auto *energyConsumer = dynamic_cast<IEC61970::Base::Wires::EnergyConsumer*>((*terminal_itor)->ConductingEquipment))
					{
						ctemplate::TemplateDictionary* pqLoad_dict = dict->AddIncludeDictionary("PQLOAD_DICT");
						pqLoad_dict->SetFilename("build/resource/PQLoad.tpl");
						this->handle_EnergyConsumer(tpNode, (*terminal_itor), energyConsumer, pqLoad_dict);
					}
				}
			}

		}

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
bool CIMObjectHandler::handle_GlobalSettings(const std::string filename, ctemplate::TemplateDictionary* dict)
{
	//Modelica_Header
	dict->AddSectionDictionary("HEADER_FOOTER_SECTION");
	dict->SetValue("GRID_NAME", filename);

	//Global Settings
	dict->AddSectionDictionary("GLOBAL_SETTINGS_SECTION");
	ModPowerSystems::VirtualElements::TopCoordinate GlobalSetting(1,1,300,-300);
	GlobalSetting.set_template_values(dict);

	return true;
}


/**
* TopologicalNode
* Convert to BusBar in Modelica
*/
bool CIMObjectHandler::handle_TopologicalNode(IEC61970::Base::Topology::TopologicalNode* tpNode, ctemplate::TemplateDictionary* sub_dict)
{
	auto *BusBar = new ModPowerSystems::SinglePhase::Connections::BusBar();

	double trans_para[4] = {1,0,-1,0};
	IEC61970::Base::DiagramLayout::DiagramObjectPoint tmp_points;

	if(tpNode->BaseVoltage->name.find("LV")){
		BusBar->set_Vnom(tpNode->BaseVoltage->nominalVoltage.value);
	} else if (tpNode->BaseVoltage->name.find("HV")){
		BusBar->set_Vnom(tpNode->BaseVoltage->nominalVoltage.value*1000);
	}

	BusBar->set_name(Tools::name_in_modelica(tpNode->name));
	BusBar->annotation.placement.visible = true;

	std::list<IEC61970::Base::DiagramLayout::DiagramObject*>::iterator diagram_itor;
	std::list<IEC61970::Base::DiagramLayout::DiagramObjectPoint*>::iterator points_itor;

	for(diagram_itor = tpNode->DiagramObjects.begin(); diagram_itor != tpNode->DiagramObjects.end(); ++diagram_itor)
	{
		BusBar->annotation.placement.transfomation.rotation = (*diagram_itor)->rotation.value;

		for(points_itor=(*diagram_itor)->DiagramObjectPoints.begin(); points_itor != (*diagram_itor)->DiagramObjectPoints.end(); ++points_itor)
		{
			tmp_points = Tools::convert_coordinate((*points_itor)->xPosition,(*points_itor)->yPosition,trans_para[0],trans_para[1],trans_para[2],trans_para[3]);
			BusBar->annotation.placement.transfomation.origin.x = tmp_points.xPosition;
			BusBar->annotation.placement.transfomation.origin.y = tmp_points.yPosition;

			BusBar->set_template_values(sub_dict);
		}
	}

	delete BusBar;

	return true;
}



bool CIMObjectHandler::handle_Terminal(IEC61970::Base::Core::Terminal* terminal, ctemplate::TemplateDictionary* sub_dict)
{
	return true;
}

/**
* ConductingEquipment of Terminal
* ConductingEquipment cast to ExternalNetworkInjection
* Convert to Slack in Modelica
*/
bool CIMObjectHandler::handle_ExternalNI(IEC61970::Base::Topology::TopologicalNode* tpNode, IEC61970::Base::Wires::ExternalNetworkInjection* externalNI, ctemplate::TemplateDictionary* sub_dict)
{
	auto * Slack = new ModPowerSystems::SinglePhase::Sources::Slack();

	double trans_para[4] = {1,0,-1,0};
	IEC61970::Base::DiagramLayout::DiagramObjectPoint tmp_points;

	Slack->set_Vnom(tpNode->BaseVoltage->nominalVoltage.value);
	Slack->set_name(Tools::name_in_modelica(externalNI->name));
	Slack->set_Vnom_displayUnit(cast_unit(tpNode->BaseVoltage->nominalVoltage.multiplier, tpNode->BaseVoltage->nominalVoltage.unit));
	Slack->annotation.placement.visible = true;

	std::list<IEC61970::Base::DiagramLayout::DiagramObject*>::iterator diagram_itor;
	std::list<IEC61970::Base::DiagramLayout::DiagramObjectPoint*>::iterator points_itor;

	for(diagram_itor = externalNI->DiagramObjects.begin(); diagram_itor != externalNI->DiagramObjects.end(); ++diagram_itor)
	{
		Slack->annotation.placement.transfomation.rotation = (*diagram_itor)->rotation.value - 90;

		for(points_itor=(*diagram_itor)->DiagramObjectPoints.begin(); points_itor != (*diagram_itor)->DiagramObjectPoints.end(); ++points_itor)
		{
			tmp_points = Tools::convert_coordinate((*points_itor)->xPosition,(*points_itor)->yPosition,trans_para[0],trans_para[1],trans_para[2],trans_para[3]);
			Slack->annotation.placement.transfomation.origin.x = tmp_points.xPosition;
			Slack->annotation.placement.transfomation.origin.y = tmp_points.yPosition;
			Slack->set_template_values(sub_dict);
		}
	}

	delete Slack;

	return true;
}

/**
* ConductingEquipment of Terminal
* ConductingEquipment cast to ACLineSegment
* Convert to PiLine in Modelica
*/
bool CIMObjectHandler::handle_ACLineSegment(IEC61970::Base::Wires::ACLineSegment* acLine, ctemplate::TemplateDictionary* sub_dict)
{
	auto *Piline = new IEC61970::Base::Wires::ACLineSegment();

	double trans_para[4] = {1,0,-1,0};
	IEC61970::Base::DiagramLayout::DiagramObjectPoint tmp_points;

	delete Piline;

	return true;
}


/**
* ConductingEquipment of Terminal
* ConductingEquipment cast to PowerTransformer
* Convert to Transformer in Modelica
*/
bool CIMObjectHandler::handle_PowerTransformer(IEC61970::Base::Wires::PowerTransformer* powerTrafo, ctemplate::TemplateDictionary* sub_dict)
{
	return true;
}


/**
* ConductingEquipment of Terminal
* ConductingEquipment cast to EnergyConsumer
* Convert to PQLoad in Modelica
*/
bool CIMObjectHandler::handle_EnergyConsumer(IEC61970::Base::Topology::TopologicalNode* tpNode, IEC61970::Base::Core::Terminal* terminal, IEC61970::Base::Wires::EnergyConsumer* energyConsumer, ctemplate::TemplateDictionary* sub_dict)
{
	auto *PQLoad = new ModPowerSystems::SinglePhase::Loads::PQLoad();

	std::cout << "hello "<<std::endl;
	double trans_para[4] = {1,0,-1,0};
	IEC61970::Base::DiagramLayout::DiagramObjectPoint tmp_points;

	PQLoad->set_name(Tools::name_in_modelica(energyConsumer->name));
	PQLoad->set_Pnom(energyConsumer->p.value);
	PQLoad->set_Pnom_displayUnit(cast_unit(energyConsumer->p.multiplier, energyConsumer->p.unit));
	PQLoad->set_Qnom(energyConsumer->q.value);
	PQLoad->set_Qnom_displayUnit(cast_unit(energyConsumer->q.multiplier, energyConsumer->q.unit));
	PQLoad->set_Vnom(tpNode->BaseVoltage->nominalVoltage.value);
	PQLoad->set_Vnom_displayUnit(cast_unit(tpNode->BaseVoltage->nominalVoltage.multiplier, tpNode->BaseVoltage->nominalVoltage.unit));
	PQLoad->annotation.placement.visible = true;

	std::list<IEC61970::Base::DiagramLayout::DiagramObject*>::iterator diagram_itor;
	std::list<IEC61970::Base::DiagramLayout::DiagramObjectPoint*>::iterator points_itor;

	if(terminal->sequenceNumber == 0 || terminal->sequenceNumber == 1 ){
		for(diagram_itor=energyConsumer->DiagramObjects.begin();diagram_itor != energyConsumer->DiagramObjects.end(); ++diagram_itor){

			for(points_itor=(*diagram_itor)->DiagramObjectPoints.begin(); points_itor != (*diagram_itor)->DiagramObjectPoints.end(); ++points_itor) {

				tmp_points = Tools::convert_coordinate((*points_itor)->xPosition,(*points_itor)->yPosition,trans_para[0],trans_para[1],trans_para[2],trans_para[3]);
				PQLoad->annotation.placement.transfomation.origin.x = tmp_points.xPosition;
				PQLoad->annotation.placement.transfomation.origin.y = tmp_points.yPosition;

				PQLoad->set_template_values(sub_dict);

			}
		}
	} else if (terminal->sequenceNumber == 2){

	}

	return true;
}
