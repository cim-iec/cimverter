
#ifndef POWERGRIDS_SynchronousMachineDynamics
#define POWERGRIDS_SynchronousMachineDynamics
#include "../ModBaseClass.h"

//using namespace ModelicaWorkshop;
namespace PowerGrids {
        class SynchronousMachineDynamics: public ModelicaWorkshop::ModBaseClass {
        public:
            SynchronousMachineDynamics();
            virtual ~SynchronousMachineDynamics();
            bool set_template_values(ctemplate::TemplateDictionary *dictionary) override;

            void set_inertia(double inertia){
                this->_inertia = inertia;
            }
            double get_inertia(){return this->_inertia;};
            
            void set_raPu(double rapu){
                this->_raPu = rapu;
            }
            double get_raPu(){ return this->_raPu;};

            void set_xdPU(double xdPU){
                this->_xdPu = xdPU;
            }
            double get_xdPu(){ return this->_xdPu;};

            void set_xlPu(double xlPu){
                this->_xlPu = xlPu;
            }
            double get_xlPu(){ return this->_xlPu;};

            void set_xpdPu(double xpdPu){
                this->_xpdPu = xpdPu;
            }
            double get_xpdPu(){ return this->_xpdPu;};

            void set_xppdPu(double xppdPu){
                this->_xppdPu = xppdPu;
            }
            double get_xppdPu(){ return this->_xppdPu;};

            void set_xppqPu(double xppqPu){
                this->_xppqPu = xppqPu;
            }
            double get_xppqPu(){ return this->_xppqPu;};

            void set_xpqPu(double xpqPu){
                this->_xpqPu = xpqPu;
            }
            double get_xpqPu(){ return this->_xpqPu;};

            void set_xqPu(double xqPu){
                this->_xqPu = xqPu;
            }
            double get_xqPu(){ return this->_xqPu;};

            void set_Tpd0(double Tpd0){
                this->_Tpd0 = Tpd0;
            }
            double get_Tpd0(){ return this->_Tpd0;};

            void set_Tppd0(double Tppd0){
                this->_Tppd0 = Tppd0;
            }
            double get_Tppd0(){ return this->_Tppd0;};

            void set_Tppq0(double Tppq0){
                this->_Tppq0 = Tppq0;
            }
            double get_Tppq0(){ return this->_Tppq0;};

            void set_Tpq0(double Tpq0){
                this->_Tpq0 = Tpq0;
            }
            double get_Tpq0(){ return this->_Tpq0;};

            void set_UPhaseStart(double UPhaseStart){
                this->_UPhaseStart = UPhaseStart;
            }
            double get_UPhaseStart(){ return this->_UPhaseStart;};

            void set_QStart(double QStart){
                this->_QStart= QStart;
            }
            double get_QStart(){ return this->_QStart;};

            void set_PStart(double PStart){
                this->_PStart= PStart;
            }
            double get_PStart(){ return this->_PStart;};

            void set_UStart(double UStart){
                this->_UStart = UStart;
            }
            double get_UStart(){ return this->_UStart;};

            void set_SNom(double SNom){
                this->_SNom = SNom;
            }
            double get_SNom(){ return this->_SNom;};

            void set_VNom(double VNom){
                this->_VNom = VNom;
            }
            double get_VNom(){ return this->_VNom;};





        private:
            double _inertia = 0;
            double _raPu = 0;
            double _xdPu = 0;
            double _xlPu = 0;
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
            double _VNom = 0;
        };


} /* namespace Powergrids*/

#endif //POWERGRIDS_SynchronousMachineDynamics
