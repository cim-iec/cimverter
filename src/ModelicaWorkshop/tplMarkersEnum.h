/*
 * tplMarkersList.h
 *
 * It contains all Markers corresponding to the template
 *
 * Author: taojun Li
 */

#ifndef SRC_MODELICAWORKSHOP_TPLMARKERSENUM_H_
#define SRC_MODELICAWORKSHOP_TPLMARKERSENUM_H_

RegisterTemplateFilename(CONNECTIONS_DICT, "CONNECTIONS_DICT");   // defines template

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

//Connection
RegisterTemplateFilename(CONNECTION_TYPE, "CONNECTION_TYPE");
RegisterTemplateFilename(PORT1, "PORT1");
RegisterTemplateFilename(PORT2, "PORT2");
RegisterTemplateFilename(COLOR, "COLOR");
RegisterTemplateFilename(POINTS, "POINTS");

#endif /* SRC_MODELICAWORKSHOP_TPLMARKERSENUM_H_ */
