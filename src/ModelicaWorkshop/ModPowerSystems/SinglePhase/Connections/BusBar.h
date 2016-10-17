/*
 * BusBar.h
 *
 */

#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_CONNECTIONS_BUSBAR_H_
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_CONNECTIONS_BUSBAR_H_

#include "../../../ModBaseClass.h"

namespace ModPowerSystems
{
	namespace SinglePhase
	{
		namespace Connections
		{

			class BusBar:public ModelicaWorkshop::ModBaseClass
			{

			public:
				BusBar();
				virtual ~BusBar();

				void set_Vnom(double Vnom){ this->_Vnom = Vnom; };
				double Vnom() const { return _Vnom; };

				bool set_template_values(ctemplate::TemplateDictionary *dictionary) override;
				static int count() { return BusBar::_count; };

			private:
				static int _count;
				double _Vnom;

				static std::map<const kBusBarEnum, const std::string> tplKeys;
				static std::map<const kBusBarEnum, const std::string> initial_tplKeys();

			};

		}/* namespace Connections */

	}/* namespace SinglePhase */

} /* namespace ModPowersystems */

#endif /* SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_CONNECTIONS_H_ */
