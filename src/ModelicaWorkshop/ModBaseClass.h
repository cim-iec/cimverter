/*
 * ModBaseClass.h
 *
 * Base Class for Modelica ModPowerSystems
 */

#ifndef SRC_MODELICAWORKSHOP_MODBASECLASS_H_
#define SRC_MODELICAWORKSHOP_MODBASECLASS_H_

#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctemplate/template.h>
#include "ModelicaUnit.h"
//#include "tplMarkers.h"

namespace ModelicaWorkshop {

typedef struct Point {

  double x;
  double y;

} Point;

typedef struct Extent {

  Point first;
  Point second;

} Extent;

typedef struct CoordinateSystem {

  Extent extent = {{0, 0}, {0, 0}};
  bool preserveAspectRatio = false;

} CoordinateSystem;

typedef struct Diagram {

  CoordinateSystem coordinate;

} Diagramm;

typedef struct Icon {

  CoordinateSystem coordinate;

} Icon;

typedef struct Transformation {

  Extent extent = {{-5, -5}, {5, 5}};
  int rotation = {0};
  Point origin = {0, 0};

} Transformation;

typedef struct Placement {

  bool visible = true;
  Transformation transfomation;

} Placement;

typedef struct Annotation {

  Placement placement;
  Diagram diagram;
  Icon icon;

} Annotation;

class ModBaseClass {
 public:
  ModBaseClass();
  ModBaseClass(const ModBaseClass &rhs);
  ModBaseClass &operator=(const ModBaseClass &);

  virtual ~ModBaseClass();

  void set_name(std::string name) {
    this->_name = name;
  };
  std::string name() const {
    return this->_name;
  };
  void set_sequenceNumber(int sequenceNumber) {
    this->_sequenceNumber = sequenceNumber;
  };
  int sequenceNumber() const {
    return this->_sequenceNumber;
  };
  void set_connected(bool connected) {
    this->_connected = connected;
  };
  bool is_connected() const {
    return this->_connected;
  };

  Annotation annotation;
  virtual bool set_template_values(ctemplate::TemplateDictionary *dictionary);

 protected:
  bool set_template_annotation_values(ctemplate::TemplateDictionary *dictionary);

 protected:
  std::string _name;
  int _sequenceNumber = 0;
  bool _connected = true;
  std::string output_trans_extent_points() const;
  std::string output_trans_origin_points() const;

};

} /* namespace ModelicaWorkshop */

#endif /* SRC_MODELICAWORKSHOP_MODBASECLASS_H_ */
