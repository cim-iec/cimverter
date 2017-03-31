/*
 * Transformer.cpp
 */

#include "Transformer.h"

namespace ModPowerSystems {

namespace PhasorSinglePhase {

namespace Transformers {

Transformer::Transformer() {
  // TODO Auto-generated constructor stub

}

Transformer::Transformer(const Transformer &rhs): ModBaseClass(rhs) {

  this->_Vnom1 = rhs._Vnom1;
  this->_Vnom2 = rhs._Vnom2;
  this->_Sr = rhs._Sr;
  this->_URr = rhs._URr;
  this->_Ukr = rhs._Ukr;
  this->_z = rhs._z;
  this->_r = rhs._r;
  this->_x = rhs._x;
  this->_b = rhs._b;
  this->_g = rhs._g;
  this->_Sr = rhs._Sr;

  this->_Vnom1_displayUnit = rhs._Vnom1_displayUnit;
  this->_Vnom2_displayUnit = rhs._Vnom2_displayUnit;
  this->_Sr_displayUnit = rhs._Sr_displayUnit;

}

Transformer& Transformer::operator=(const Transformer &rhs) {

  if(this == &rhs) return *this;
  ModBaseClass::operator=(rhs);
  this->_Vnom1 = rhs._Vnom1;
  this->_Vnom2 = rhs._Vnom2;
  this->_Sr = rhs._Sr;
  this->_URr = rhs._URr;
  this->_Ukr = rhs._Ukr;
  this->_z = rhs._z;
  this->_r = rhs._r;
  this->_x = rhs._x;
  this->_b = rhs._b;
  this->_g = rhs._g;
  this->_Sr = rhs._Sr;

  this->_Vnom1_displayUnit = rhs._Vnom1_displayUnit;
  this->_Vnom2_displayUnit = rhs._Vnom2_displayUnit;
  this->_Sr_displayUnit = rhs._Sr_displayUnit;
  return *this;
}

Transformer::~Transformer() {
  // TODO Auto-generated destructor stub
}

bool Transformer::set_template_values(ctemplate::TemplateDictionary *dictionary) {

  dictionary->SetValue("NAME", this->name());
  dictionary->SetFormattedValue("VNOM1", "%.3f", this->Vnom1());
  dictionary->SetValue("VNOM1_DISPLAYUNIT", (ModelicaUnit[this->Vnom1_displayUnit()]));
  dictionary->SetFormattedValue("VNOM2", "%.3f", this->Vnom2());
  dictionary->SetValue("VNOM2_DISPLAYUNIT", (ModelicaUnit[this->Vnom2_displayUnit()]));
  dictionary->SetFormattedValue("SR", "%.3f", this->Sr());
  dictionary->SetValue("SR_DISPLAYUNIT", (ModelicaUnit[this->Sr_displayUnit()]));
  dictionary->SetFormattedValue("URR", "%.5f", this->URr());
  dictionary->SetFormattedValue("UKR", "%.5f", this->Ukr());

  this->set_template_annotation_values(dictionary);

  return true;
}

} /* namespace Transformers */

} /* namespace PhasorSinglePhase */

} /* namespace ModPowerSystems */
