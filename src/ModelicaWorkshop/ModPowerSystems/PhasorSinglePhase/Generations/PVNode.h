
#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_PHASORSINGLEPHASE_GENERATIONS
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_PHASORSINGLEPHASE_GENERATIONS
#include "../../../ModBaseClass.h"

using namespace ModelicaWorkshop;
namespace ModPowerSystems {

    namespace PhasorSinglePhase {

        namespace Generations {

            class PVNode: public ModBaseClass {
            public:
                PVNode();
                virtual ~PVNode();

                double Pgen(){
                    return this->_Pgen;
                }

                double Vabs(){
                    return  this->_Vabs;
                }

                double  Vnom(){
                    return this->_Vnom;
                }

                void setVnom(double Vnom){
                    this->_Vnom = Vnom;
                }

                void setPgen(double Pgen){
                    this->_Pgen = Pgen;
                }

                void setVabs(double Vabs){
                    this->_Vabs = Vabs;
                }

                bool set_template_values(ctemplate::TemplateDictionary *dictionary) override;

            private:;
                double _Pgen = 0;
                double _Vabs = 0;
                double _Vnom = 0;
            };

        } /* namespace Generations */

    } /* namespace PhasorSinglePhase */

} /* namespace ModPowerSystems */

#endif //SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_PHASORSINGLEPHASE_GENERATIONS _PVNODE_H
