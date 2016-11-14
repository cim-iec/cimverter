/*
 * ZLoad.cpp
 *
 */

#include "ZLoad.h"

namespace ModPowerSystems {

namespace SinglePhase {

namespace Loads {

ZLoad::ZLoad() {
  // TODO Auto-generated constructor stub

}

ZLoad::~ZLoad() {
  // TODO Auto-generated destructor stub
}

bool ZLoad::set_template_values(ctemplate::TemplateDictionary *dictionary) {
  dictionary->SetValue(NAME, this->name());
  dictionary->SetFormattedValue(PNOM, "%.2f", this->Pnom());
  dictionary->SetFormattedValue(QNOM, "%.2f", this->Qnom());
  dictionary->SetFormattedValue(VNOM, "%.2f", this->Vnom());
  dictionary->SetValue(PNOM_DISPLAYUNIT, (ModelicaUnit[this->Pnom_displayUnit()]));
  dictionary->SetValue(QNOM_DISPLAYUNIT, (ModelicaUnit[this->Qnom_displayUnit()]));
  dictionary->SetValue(VNOM_DISPLAYUNIT, (ModelicaUnit[this->Vnom_displayUnit()]));

  this->set_template_annotation_values(dictionary);

  return true;
}

} /* namespace Loads */

} /* namespace SinglePhase */

} /* namespace ModPowerSystems */
