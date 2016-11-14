/*
 * GenericGenerator.cpp
 *
 */

#include "GenericGenerator.h"

namespace ModPowerSystems {

namespace SinglePhase {

namespace Generations {

GenericGenerator::GenericGenerator() {
  // TODO Auto-generated constructor stub

}

GenericGenerator::~GenericGenerator() {
  // TODO Auto-generated destructor stub
}

bool GenericGenerator::set_template_values(ctemplate::TemplateDictionary *dictionary) {

  dictionary->SetValue(NAME, this->name());
  this->set_template_annotation_values(dictionary);

  return true;
}

} /* namespace Generations */

} /* namespace SinglePhase */

} /* namespace ModPowerSystems */
