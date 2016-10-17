/*
 * PiLine.h
 *
 */

#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_LINES_PILINE_H_
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_LINES_PILINE_H_

#include "../../../ModBaseClass.h"

namespace ModPowerSystems {

	namespace SinglePhase {

		namespace Lines {

			class PiLine: public ModelicaWorkshop::ModBaseClass {
			public:
				PiLine();
				virtual ~PiLine();
			};

		} /* namespace Lines */

	} /* namespace SinglePhase */

} /* namespace ModPowerSystems */

#endif /* SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_LINES_PILINE_H_ */
