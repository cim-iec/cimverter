/*
 * ConnectivityNode.cpp
 *
 */

#include "ConnectivityNode.h"

namespace ModPowerSystems {

namespace PhasorSinglePhase {

namespace Connections {

ConnectivityNode::ConnectivityNode()
    : _Vnom(110000) {
  // TODO Auto-generated constructor stub

}

ConnectivityNode::ConnectivityNode(const ConnectivityNode &rhs) {
  this->_Vnom = rhs._Vnom;
}

ConnectivityNode& ConnectivityNode::operator=(const ConnectivityNode &rhs) {

  if(this == &rhs) return *this;
  ModBaseClass::operator=(rhs);
  this->_Vnom = rhs._Vnom;
  return *this;
}

ConnectivityNode::~ConnectivityNode() {

}

bool ConnectivityNode::set_template_values(ctemplate::TemplateDictionary *dictionary) {

  dictionary->SetFormattedValue(VNOM, "%.f", this->Vnom());
  dictionary->SetValue(NAME, this->name());
  this->set_template_annotation_values(dictionary);

  return true;
}

} /* namespace Connections */

} /* namespace PhasorSinglePhase */

} /* namespace ModPowerSystems */
