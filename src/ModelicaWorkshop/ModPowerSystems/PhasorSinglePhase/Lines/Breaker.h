#ifndef CIMVERTER_BREAKER_H
#define CIMVERTER_BREAKER_H
#include "../../../ModBaseClass.h"

using namespace ModelicaWorkshop;

namespace ModPowerSystems {

    namespace PhasorSinglePhase {

        namespace Lines {

            class Breaker: public ModelicaWorkshop::ModBaseClass{
            public:
                Breaker();
                virtual ~Breaker();

                int  isClosed(){
                    return this->_is_closed;
                }

                void set_is_closed(bool is_closed){
                    this->_is_closed = is_closed;
                }
                bool set_template_values(ctemplate::TemplateDictionary *dictionary) override;
            private:;

                int _is_closed = 0;
            };

        } /* namespace Lines */

    } /* namespace PhasorSinglePhase */
}/* namespace ModPowerSystems */


#endif //CIMVERTER_BREAKER_H
