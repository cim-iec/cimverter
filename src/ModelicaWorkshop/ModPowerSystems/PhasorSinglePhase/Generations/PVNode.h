
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

                void setPgen_displayUnit(modelicaUnit Pgen_displayUnit){
                    this->_Pgen_displayUnit = Pgen_displayUnit;
                }
                modelicaUnit getPgen_displayUnit(){
                    return this->_Pgen_displayUnit;
                }

                void setVabs_displayUnit(modelicaUnit Vabs_displayUnit){
                    this->_Vabs_displayUnit = Vabs_displayUnit;
                }
                modelicaUnit getVabs_displayUnit(){
                    return this->_Vabs_displayUnit;
                }

                void setVnom_displayUnit(modelicaUnit Vnom_displayUnit){
                    this->_Vnom_displayUnit = Vnom_displayUnit;
                }
                modelicaUnit getVnom_displayUnit(){
                    return this->_Vnom_displayUnit;
                }

            private:;
                modelicaUnit _Pgen_displayUnit = modelicaUnit::W;
                modelicaUnit _Vabs_displayUnit = modelicaUnit::V;
                modelicaUnit _Vnom_displayUnit = modelicaUnit::V;

                double _Pgen = 0;
                double _Vabs = 0;
                double _Vnom = 0;
            };

        } /* namespace Generations */

    } /* namespace PhasorSinglePhase */

} /* namespace ModPowerSystems */

#endif //SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_PHASORSINGLEPHASE_GENERATIONS _PVNODE_H
