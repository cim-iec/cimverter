/*
 * ConnectivityNode.h
 *
 *  Created on: Sep 14, 2016
 *      Author: root
 */

#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_CONNECTIONS_CONNECTIVITYNODE_H_
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_CONNECTIONS_CONNECTIVITYNODE_H_

#include "../../../ModBaseClass.h"

namespace ModPowerSystems {

		namespace SinglePhase {

			namespace Connections {

				class ConnectivityNode:public ModelicaWorkshop::ModBaseClass
				{

				public:
					ConnectivityNode();
					virtual ~ConnectivityNode();
				};

			} /* namespace Connections */

		} /* namespace SinglePhase */

} /* namespace ModPowerSystems */

#endif /* SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_CONNECTIONS_CONNECTIVITYNODE_H_ */
