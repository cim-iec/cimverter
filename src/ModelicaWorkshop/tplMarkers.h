/*
 * tplMarkersList.h
 *
 * It contains all Markers corresponding to the template
 *
 */

#ifndef SRC_MODELICAWORKSHOP_TPLMARKERS_H_
#define SRC_MODELICAWORKSHOP_TPLMARKERS_H_

// defines template dictionary and section name markers
RegisterTemplateFilename(CONNECTIONS_DICT, "CONNECTIONS_DICT");

// Global Setting
RegisterTemplateFilename(FNOM, "FNOM");
RegisterTemplateFilename(FNOM_DISPLAYUNIT, "FNOM_DISPLAYUNIT");
RegisterTemplateFilename(INIT, "INIT");
RegisterTemplateFilename(SIMMODE, "SIMMODE");

RegisterTemplateFilename(PAR, "PAR");
RegisterTemplateFilename(GRID_NAME, "GRID_NAME");
RegisterTemplateFilename(HEADER_FOOTER_SECTION, "HEADER_FOOTER_SECTION");
RegisterTemplateFilename(DIAGRAM_EXTENT_POINTS, "DIAGRAM_EXTENT_POINTS");
RegisterTemplateFilename(ICON_EXTENT_POINTS, "ICON_EXTENT_POINTS");

//Annotation
RegisterTemplateFilename(VISIBLE, "VISIBLE");
RegisterTemplateFilename(ORIGIN_POINT, "ORIGIN_POINT");
RegisterTemplateFilename(TRANS_EXTENT_POINTS, "TRANS_EXTENT_POINTS");
RegisterTemplateFilename(ROTATION, "ROTATION");

//Slack
RegisterTemplateFilename(NAME, "NAME");
RegisterTemplateFilename(VNOM, "VNOM");
RegisterTemplateFilename(VNOM_DISPLAYUNIT, "VNOM_DISPLAYUNIT");
RegisterTemplateFilename(FREQUENCY, "FREQUENCY");
RegisterTemplateFilename(FREQUENCY_DISPLAYUNIT, "FREQUENCY_DISPLAYUNIT");
RegisterTemplateFilename(PHIV_DISPLAYUNIT, "PHIV_DISPLAYUNIT");
RegisterTemplateFilename(PHIV, "PHIV");

//BusBar
RegisterTemplateFilename(VPP_FIXED, "VPP_FIXED");
RegisterTemplateFilename(PNOM, "PNOM");
RegisterTemplateFilename(QNOM, "QNOM");
RegisterTemplateFilename(PNOM_DISPLAYUNIT, "PNOM_DISPLAYUNIT");
RegisterTemplateFilename(QNOM_DISPLAYUNIT, "QNOM_DISPLAYUNIT");

//PQLoadProfile
RegisterTemplateFilename(PROFILE_FILENAME, "PROFILE_FILENAME");
RegisterTemplateFilename(PROFILE_NAME, "PROFILE_NAME");
RegisterTemplateFilename(ENABLE_OUTPUT_PLOAD, "ENABLE_OUTPUT_PLOAD");

//ZLoadProfile
RegisterTemplateFilename(SMOOTHNESS, "smoothnessSetting");

//PiLine
RegisterTemplateFilename(LENGTH, "LENGTH");
RegisterTemplateFilename(R, "R");
RegisterTemplateFilename(X, "X");
RegisterTemplateFilename(B, "B");
RegisterTemplateFilename(G, "G");
RegisterTemplateFilename(IMAX, "IMAX");
RegisterTemplateFilename(IMAX_DISPLAYUNIT, "IMAX_DISPLAYUNIT");
RegisterTemplateFilename(SR, "SR");
RegisterTemplateFilename(SR_DISPLAYUNIT, "SR_DISPLAYUNIT");

//Transformer
RegisterTemplateFilename(VNOM1, "VNOM1");
RegisterTemplateFilename(VNOM2, "VNOM2");
RegisterTemplateFilename(VNOM1_DISPLAYUNIT, "VNOM1_DISPLAYUNIT");
RegisterTemplateFilename(VNOM2_DISPLAYUNIT, "VNOM2_DISPLAYUNIT");
RegisterTemplateFilename(URR, "UKR");
RegisterTemplateFilename(UKR, "URR");

//BatteryType0
RegisterTemplateFilename(CNOM, "CNOM");
RegisterTemplateFilename(SOC_START, "SOC_START");
RegisterTemplateFilename(ENABLE_OUTPUT_WBAT, "ENABLE_OUTPUT_WBAT");
RegisterTemplateFilename(CNOM_DISPLAYUNIT, "CNOM_DISPLAYUNIT");

//BatteryType1
RegisterTemplateFilename(ETA_CH, "ETA_CH");
RegisterTemplateFilename(ETA_DISCH, "ETA_DISCH");

//Windgenerator
RegisterTemplateFilename(V_C, "V_C");
RegisterTemplateFilename(V_R, "V_R");
RegisterTemplateFilename(V_S, "V_S");

//SolarGenerator
RegisterTemplateFilename(CONTROLLER_TYPE, "CONTROLLER_TYPE");
RegisterTemplateFilename(CURTAIL_LIMIT, "CURTAIL_LIMIT");
RegisterTemplateFilename(STATUS_ON, "STATUS_ON");
RegisterTemplateFilename(W_LOSS, "W_LOSS");
RegisterTemplateFilename(W_TOTAL, "W_TOTAL");
RegisterTemplateFilename(ENABLE_INPUT_PLOAD, "ENABLE_INPUT_PLOAD");
RegisterTemplateFilename(ENABLE_OUTPUT_PSOLAR, "ENABLE_OUTPUT_PSOLAR");

//HousholdsType0
RegisterTemplateFilename(LOAD_PNOM, "LOAD_PNOM");
RegisterTemplateFilename(LOAD_QNOM, "LOAD_QNOM");
RegisterTemplateFilename(LOAD_PNOM_DISPLAYUNIT, "LOAD_PNOM_DISPLAYUNIT");
RegisterTemplateFilename(LOAD_QNOM_DISPLAYUNIT, "LOAD_QNOM_DISPLAYUNIT");

//HousholdsType1
RegisterTemplateFilename(LOAD_PROFILE_NAME, "LOAD_PROFILE_NAME");
RegisterTemplateFilename(LOAD_PROFILE_FILENAME, "LOAD_PROFILE_FILENAME");

//HousholdsType2
RegisterTemplateFilename(PV_PNOM, "PV_PNOM");
RegisterTemplateFilename(PV_PROFILE_NAME, "PV_PROFILE_NAME");
RegisterTemplateFilename(PV_PROFILE_FILENAME, "PV_PROFILE_FILENAME");
RegisterTemplateFilename(PV_CONTROLLER, "PV_CONTROLLER");
RegisterTemplateFilename(PV_SYSTEMON, "PV_SYSTEMON");
RegisterTemplateFilename(PV_CURTAILMENT_LIMIT, "PV_CURTAILMENT_LIMIT");
RegisterTemplateFilename(PV_PNOM_DISPLAYUNIT, "PV_PNOM_DISPLAYUNIT");

//Connection
RegisterTemplateFilename(CONNECTION_TYPE, "CONNECTION_TYPE");
RegisterTemplateFilename(PORT1, "PORT1");
RegisterTemplateFilename(PORT2, "PORT2");
RegisterTemplateFilename(COLOR, "COLOR");
RegisterTemplateFilename(POINTS, "POINTS");

#endif /* SRC_MODELICAWORKSHOP_TPLMARKERS_H_ */
