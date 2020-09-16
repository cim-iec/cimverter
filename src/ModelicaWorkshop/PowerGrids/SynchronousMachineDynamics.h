
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
                this->_raPu = rapu;
            }
            double get_raPu(){ return this->_raPu;};

            void set_xdPU(double xdPU){
                this->_xdPu= xdPU;
            }
            double get_xdPu(){ return this->_xdPu;};

            void set_xpdPu(double xpdPu){
                this->_xpdPu= xpdPu;
            }
            double get_xpdPu(){ return this->_xpdPu;};

            void set_xppdPu(double xppdPu){
                this->_xppdPu= xppdPu;
            }
            double get_xppdPu(){ return this->_xppdPu;};

        private:
            double _raPu = 0;
            double _xdPu = 0;
            double _xpdPu = 0;
            double _xppdPu = 0;
            double _xppqPu = 0;
            double _xpqPu = 0;
            double _xqPu = 0;
            double _Tpd0 = 0;
            double _Tppd0 = 0;
            double _Tppq0 = 0;
            double _Tpq0 = 0;
            double _UPhaseStart = 0;
            double _QStart = 0;
            double _PStart = 0;
            double _UStart = 0;
            double _SNom = 0;
        };


} /* namespace Powergrids*/

#endif //POWERGRIDS_SynchronousMachineDynamics
