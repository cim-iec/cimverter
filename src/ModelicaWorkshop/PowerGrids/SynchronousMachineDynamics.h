
#ifndef POWERGRIDS_SynchronousMachineDynamics
#define POWERGRIDS_SynchronousMachineDynamics
#include "../ModBaseClass.h"

using namespace ModelicaWorkshop;
namespace PowerGrids {
        class SynchronousMachineDynamics: public ModBaseClass {
        public:
            SynchronousMachineDynamics();
            virtual ~SynchronousMachineDynamics();
            bool set_template_values(ctemplate::TemplateDictionary *dictionary) override;
            void set_raPu(double rapu){
                this->raPu = rapu;
            }
            double get_raPu(){ return this->raPu;};

        private:
            double raPu;
            double xdPu;
            double xpdPu;
            double xppdPu;
            double xppqPu;
            double xpqPu;
            double xqPu;
            double Tpd0;
            double Tppd0;
            double Tppq0;
            double Tpq0;
            double UPhaseStart;
            double QStart;
            double PStart;
            double UStart;
            double SNom;
        };


} /* namespace Powergrids*/

#endif //POWERGRIDS_SynchronousMachineDynamics
