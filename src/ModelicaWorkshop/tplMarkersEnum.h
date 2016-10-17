/*
 * tplMarkersList.h
 *
 * It contains all Markers corresponding to the template
 *
 * Author: taojun Li
 */

#ifndef SRC_MODELICAWORKSHOP_TPLMARKERSENUM_H_
#define SRC_MODELICAWORKSHOP_TPLMARKERSENUM_H_

/*
 * all corresponding Markers of Global Template
 */
enum class kGlobalEnum {
	GRID_NAME, HEADER_FOOTER_SECTION, DIAGRAM_EXTENT_X1, DIAGRAM_EXTENT_Y1, DIAGRAM_EXTENT_X2,DIAGRAM_EXTENT_Y2, ROTATION, PAR,
	ICON_EXTENT_X1, ICON_EXTENT_Y1, ICON_EXTENT_X2, ICON_EXTENT_Y2
};

/*
 * corresponding Markers of the Slack Section in Template
 */
enum class kSlackEnum {
	NAME, VNOM, VNOM_DISPLAYUNIT, FREQUENCY, FREQUENCY_DISPLAYUNIT, PHIV_DISPLAYUNIT, PHIV,
	VISIBLE, TRANS_EXTENT_X1, TRANS_EXTENT_Y1, TRANS_EXTENT_X2, TRANS_EXTENT_Y2, ORIGIN_X, ORIGIN_Y,
	ROTATION

};

/*
 * corresponding Markers of the BusBar Section in Template
 */
enum class kBusBarEnum {
	NAME, VNOM, VPP_FIXED,VPP_START,FREQUENCY,
	VISIBLE, TRANS_EXTENT_X1, TRANS_EXTENT_Y1, TRANS_EXTENT_X2, TRANS_EXTENT_Y2, ORIGIN_X, ORIGIN_Y,
	ROTATION
};

/*
 * corresponding Markers of the ConnectivityNode Section in Template
 */
enum class kConnectivityNodeEnum {
	NAME, VNOM, VPP_FIXED,VPP_START,FREQUENCY,
	VISIBLE, TRANS_EXTENT_X1, TRANS_EXTENT_Y1, TRANS_EXTENT_X2, TRANS_EXTENT_Y2, ORIGIN_X, ORIGIN_Y,
	ROTATION
};

/*
 * corresponding Markers of the PiLine Section in Template
 */
enum class kPiLineEnum {
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
 * corresponding Markers of the PQLoad Section in Template
 */
enum class kPQLoadEnum {
	NAME, PNOM, QNOM, VNOM, PNOM_DISPLAYUNIT, QNOM_DISPLAYUNIT, VNOM_DISPLAYUNIT,
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

/*
 * corresponding Markers of the Transformer Section in Template
 */
enum class kTransformerEnum {
	NAME, VNOM, VPP_FIXED,VPP_START,FREQUENCY,
	VISIBLE, TRANS_EXTENT_X1, TRANS_EXTENT_Y1, TRANS_EXTENT_X2, TRANS_EXTENT_Y2, ORIGIN_X, ORIGIN_Y,
	ROTATION
};

//static std::map<const kGlobalEnum, const std::string> tplKeys = {{kGlobalEnum::ROTATION,"ROTATION"},{kGlobalEnum::PAR,"PAR"},
//		{kGlobalEnum::DIAGRAM_EXTENT_X1,"DIAGRAM_EXTENT_X1"},{kGlobalEnum::DIAGRAM_EXTENT_Y1,"DIAGRAM_EXTENT_Y1"},
//		{kGlobalEnum::DIAGRAM_EXTENT_X2,"DIAGRAM_EXTENT_X2"},{kGlobalEnum::DIAGRAM_EXTENT_Y2,"DIAGRAM_EXTENT_Y2"},
//		{kGlobalEnum::DIAGRAM_EXTENT_X1,"DIAGRAM_EXTENT_X1"},{kGlobalEnum::DIAGRAM_EXTENT_Y1,"DIAGRAM_EXTENT_Y1"},
//		{kGlobalEnum::DIAGRAM_EXTENT_X2,"DIAGRAM_EXTENT_X2"},{kGlobalEnum::DIAGRAM_EXTENT_Y2,"DIAGRAM_EXTENT_Y2"},
//};


#endif /* SRC_MODELICAWORKSHOP_TPLMARKERSENUM_H_ */
