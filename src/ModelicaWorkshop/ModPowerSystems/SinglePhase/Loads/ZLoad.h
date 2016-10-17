/*
 * ZLoad.h
 *
 */

#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_LOADS_ZLOAD_H_
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_LOADS_ZLOAD_H_

#include "../../../ModBaseClass.h"

namespace ModPowerSystems {

		namespace SinglePhase {

				namespace Loads {

					class ZLoad: public ModelicaWorkshop::ModBaseClass {
					public:
						ZLoad();
						virtual ~ZLoad();
					};

				} /* namespace Loads */

		} /* namespace SinglePhase */

} /* namespace ModPowerSystems */

#endif /* SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_LOADS_ZLOAD_H_ */
