/*
 * PQLoad.h
 * Constant Power Load
 */

#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_LOADS_PQLOAD_H_
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_LOADS_PQLOAD_H_

#include "../../../ModBaseClass.h"

using namespace ModelicaWorkshop;

namespace ModPowerSystems {

		namespace SinglePhase {

				namespace Loads {

					class PQLoad: public ModBaseClass {
					public:
						PQLoad();
						virtual ~PQLoad();

						void set_Pnom(double Pnom){ this->_Pnom = Pnom; };
						double Pnom() const { return _Pnom; };

						void set_Qnom(double Qnom){ this->_Qnom = Qnom; };
						double Qnom() const { return _Qnom; };

						void set_Vnom(double Vnom){ this->_Vnom = Vnom; };
						double Vnom() const { return _Vnom; };


						void set_Pnom_displayUnit(modelicaUnit Pnom_displayUnit){ this->_Pnom_displayUnit = Pnom_displayUnit; };
						modelicaUnit Pnom_displayUnit() const { return _Pnom_displayUnit; };

						void set_Qnom_displayUnit(modelicaUnit Qnom_displayUnit){ this->_Qnom_displayUnit = Qnom_displayUnit; };
						modelicaUnit Qnom_displayUnit() const { return _Qnom_displayUnit; };

						void set_Vnom_displayUnit(modelicaUnit Vnom_displayUnit){ this->_Vnom_displayUnit = Vnom_displayUnit; };
						modelicaUnit Vnom_displayUnit() const { return _Vnom_displayUnit; };


						bool set_template_values(ctemplate::TemplateDictionary *dictionary) override;

						static int count() { return PQLoad::_count; };

					private:
						static int _count;

						//Parameters
						double _Pnom = 110000; //active power per phase
						double _Qnom; //reactive power per phase
						double _Vnom; //nominal voltage level

						modelicaUnit _Pnom_displayUnit = modelicaUnit::W;
						modelicaUnit _Qnom_displayUnit = modelicaUnit::var;
						modelicaUnit _Vnom_displayUnit = modelicaUnit::V;

					};

				} /* namespace Loads */

		} /* namespace SinglePhase */

} /* namespace ModPowerSystems */

#endif /* SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_LOADS_PQLOAD_H_ */
