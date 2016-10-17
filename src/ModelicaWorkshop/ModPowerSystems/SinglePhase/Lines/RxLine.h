/*
 * RxLine.h
 *
 *  Created on: Sep 14, 2016
 *      Author: root
 */

#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_LINES_RXLINE_H_
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_LINES_RXLINE_H_

#include "../../../ModBaseClass.h"

namespace ModPowerSystems {

		namespace SinglePhase {

			namespace Lines {

				class RxLine: public ModelicaWorkshop::ModBaseClass {
				public:
					RxLine();
					virtual ~RxLine();
				};

			} /* namespace Lines */

		} /* namespace SinglePhase */

} /* namespace ModPowerSystems */

#endif /* SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_LINES_RXLINE_H_ */
