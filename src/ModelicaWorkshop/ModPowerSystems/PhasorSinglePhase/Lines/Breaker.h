#ifndef CIMVERTER_BREAKER_H
#define CIMVERTER_BREAKER_H
#include "../../../ModBaseClass.h"
#include "../Connections/BusBar.h"
typedef ModPowerSystems::PhasorSinglePhase::Connections::BusBar BusBar;

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

                BusBar* getBus1()const {
                    return this->bus1;

                }
                BusBar* getBus2()const {
                    return this->bus2;

                }
                void setBus1(BusBar* bus){
                    this->bus1 = bus;
                    bus1Initialized = true;
                }
                void setBus2(BusBar* bus){
                    this->bus2 = bus;
                    bus2Initialized = true;
                }

                void setBus(BusBar* bus){
                    if(this->bus1Initialized == false){
                        setBus1(bus);
                        bus1Initialized = true;
                    }else{
                        setBus2(bus);
                        bus2Initialized = true;
                    }
                }

            private:;
                //Parameters
                BusBar* bus1;
                bool bus1Initialized = false;
                BusBar* bus2;
                bool bus2Initialized = false;
                bool _is_closed = false;
            };

        } /* namespace Lines */

    } /* namespace PhasorSinglePhase */
}/* namespace ModPowerSystems */


#endif //CIMVERTER_BREAKER_H
