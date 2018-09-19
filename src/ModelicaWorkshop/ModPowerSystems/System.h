/*
 * System.h
 *
 */

#ifndef SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SYSTEM_H_
#define SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SYSTEM_H_

#include "../ModBaseClass.h"
#include "../../ConfigManager.h"

using namespace ModelicaWorkshop;

namespace ModPowerSystems {

class System : public ModBaseClass {
 public:
  System();
  System(const ConfigManager & configManager);//using SystemSetting parameters from config
  System(double lx, double ly, double rx, double ry);
  enum dyn_types{
      SteadyState,
      SteadyInitial,
      FixedInitial,
      FreeInitial };

  virtual ~System();

  void set_f_nom(double f_nom) {
    this->_f_nom = f_nom;
  };
  double f_nom() const {
    return _f_nom;
  };

  void set_f_nom_displayUnit(modelicaUnit f_nom_displayUnit) {
    this->_f_nom_displayUnit = f_nom_displayUnit;
  };

  void set_dyn_type(dyn_types type) {
    this->dyn_type = "PowerSystems.Types.Dynamics." + getStringFromDyn(type);
  };

  std::string getStringFromDyn(dyn_types type){
    switch (type)
    {
      case FreeInitial: return "FreeInitial";
      case FixedInitial: return "FixedInitial";
      case SteadyInitial: return "SteadyInitial";
      case SteadyState: return "SteadyState";

    }
  };

  modelicaUnit f_nom_displayUnit() const {
    return _f_nom_displayUnit;
  };

  bool set_system_label(ctemplate::TemplateDictionary *dictionary);
  bool set_system_setting(ctemplate::TemplateDictionary *dictionary);
  bool set_template_values(ctemplate::TemplateDictionary *dictionary) override;

 private:
  std::string dyn_type = "PowerSystems.Types.Dynamics.SteadyState";
  double _f_nom = 50;  //nominal frequency
  modelicaUnit _f_nom_displayUnit = modelicaUnit::Hz;

  double _lx = 0;
  double _ly = 0;
  double _rx = 0;
  double _ry = 0;

  std::string output_diagram_extent_points() const;
  std::string output_icon_extent_points() const;

};

} /* namespace ModPowerSystems */

#endif /* SRC_MODELICAWORKSHOP_MODPOWERSYSTEMS_SYSTEM_H_ */
