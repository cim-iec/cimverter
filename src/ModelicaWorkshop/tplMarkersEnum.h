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
RegisterTemplateFilename(DIAGRAM_EXTENT_X1, "DIAGRAM_EXTENT_X1");
RegisterTemplateFilename(DIAGRAM_EXTENT_Y1, "DIAGRAM_EXTENT_Y1");
RegisterTemplateFilename(DIAGRAM_EXTENT_X2, "DIAGRAM_EXTENT_X2");
RegisterTemplateFilename(DIAGRAM_EXTENT_Y2, "DIAGRAM_EXTENT_Y2");
RegisterTemplateFilename(ROTATION, "ROTATION");
RegisterTemplateFilename(ICON_EXTENT_X1, "ICON_EXTENT_X1");
RegisterTemplateFilename(ICON_EXTENT_Y1, "ICON_EXTENT_Y1");
RegisterTemplateFilename(ICON_EXTENT_X2, "ICON_EXTENT_X2");
RegisterTemplateFilename(ICON_EXTENT_Y2, "ICON_EXTENT_Y2");

// Corresponding Markers of the Slack Section in Template
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


RegisterTemplateFilename(VISIBLE, "VISIBLE");
RegisterTemplateFilename(TRANS_EXTENT_X1, "TRANS_EXTENT_X1");
RegisterTemplateFilename(TRANS_EXTENT_Y1, "TRANS_EXTENT_Y1");
RegisterTemplateFilename(TRANS_EXTENT_X2, "TRANS_EXTENT_X2");
RegisterTemplateFilename(TRANS_EXTENT_Y2, "TRANS_EXTENT_Y2");
RegisterTemplateFilename(ORIGIN_X, "ORIGIN_X");
RegisterTemplateFilename(ORIGIN_Y, "ORIGIN_Y");

/*
 * corresponding Markers of the ConnectivityNode Section in Template
 */
enum class kConnectivityNodeEnum {
	NAME, VNOM, VPP_FIXED,VPP_START,FREQUENCY,
	VISIBLE, TRANS_EXTENT_X1, TRANS_EXTENT_Y1, TRANS_EXTENT_X2, TRANS_EXTENT_Y2, ORIGIN_X, ORIGIN_Y,
	ROTATION
};

/*
 * corresponding Markers of the RxLine Section in  Template
 */
enum class kRxLineEnum {
	NAME, VNOM, VPP_FIXED,VPP_START,FREQUENCY,
	VISIBLE, TRANS_EXTENT_X1, TRANS_EXTENT_Y1, TRANS_EXTENT_X2, TRANS_EXTENT_Y2, ORIGIN_X, ORIGIN_Y,
	ROTATION
};

/*
 * corresponding Markers of the ZLoad Section in Template
 */
enum class kZLoadEnum {
	NAME, VNOM, VPP_FIXED,VPP_START,FREQUENCY,
	VISIBLE, TRANS_EXTENT_X1, TRANS_EXTENT_Y1, TRANS_EXTENT_X2, TRANS_EXTENT_Y2, ORIGIN_X, ORIGIN_Y,
	ROTATION
};

#endif /* SRC_MODELICAWORKSHOP_TPLMARKERSENUM_H_ */
