/*
 * Transformer.h
 *
 */

#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_TRANSFORMERS_TRANSFORMER_H_
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_TRANSFORMERS_TRANSFORMER_H_

#include "../../../ModBaseClass.h"

namespace ModPowerSystems {

	namespace SinglePhase {

		namespace Transformers {

			class Transformer: public ModelicaWorkshop::ModBaseClass {
			public:
				Transformer();
				virtual ~Transformer();
				bool set_template_values(ctemplate::TemplateDictionary *dictionary) override;
			};

		} /* namespace Transformers */

	} /* namespace SinglePhase */

} /* namespace ModPowerSystems */

#endif /* SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SINGLEPHASE_TRANSFORMERS_TRANSFORMER_H_ */
