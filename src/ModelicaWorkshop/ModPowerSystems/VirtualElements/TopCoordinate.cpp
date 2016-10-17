/*
 * TopCoordinate.cpp
 *
 */

#include "TopCoordinate.h"

namespace ModPowerSystems {

		namespace VirtualElements {

			TopCoordinate::TopCoordinate() {
				// TODO Auto-generated constructor stub

			}

			TopCoordinate::TopCoordinate(double lx, double ly, double rx, double ry):_lx(lx),_ly(ly),_rx(rx),_ry(ry) {
					// TODO Auto-generated constructor stub
			}

			TopCoordinate::~TopCoordinate() {
				// TODO Auto-generated destructor stub
			}

			bool TopCoordinate::set_template_values(ctemplate::TemplateDictionary *dictionary){

					dictionary->SetFormattedValue("DIAGRAM_EXTENT_X1", "%.2f", this->_lx);
					dictionary->SetFormattedValue("DIAGRAM_EXTENT_Y1", "%.2f", this->_ly);
					dictionary->SetFormattedValue("DIAGRAM_EXTENT_X2", "%.2f", this->_rx);
					dictionary->SetFormattedValue("DIAGRAM_EXTENT_Y2", "%.2f", this->_ry);

					return true;
			}

		} /* namespace VirtualElements */

} /* namespace ModPowerSystems */
