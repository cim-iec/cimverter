/*
 * TopCoordinate.h
 *
 */

#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_VIRTUALELEMENTS_TOPCOORDINATE_H_
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_VIRTUALELEMENTS_TOPCOORDINATE_H_

#include "../../ModBaseClass.h"

namespace ModPowerSystems {

		namespace VirtualElements {

			class TopCoordinate: public ModelicaWorkshop::ModBaseClass {
			public:
				TopCoordinate();
				TopCoordinate(double lx, double ly, double rx, double ry);
				virtual ~TopCoordinate();
				bool set_template_values(ctemplate::TemplateDictionary *dictionary) override;

			private:
				double _lx = 0;
				double _ly = 0;
				double _rx = 0;
				double _ry = 0;
			};

		} /* namespace VirtualElements */

} /* namespace ModPowerSystems */

#endif /* SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_VIRTUALELEMENTS_TOPCOORDINATE_H_ */
