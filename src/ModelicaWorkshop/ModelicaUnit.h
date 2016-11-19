/*
 * ModelicaUnit.h
 *
 * Unit in Modelica
 *
 * Created on: Sep 16, 2016
 */

#ifndef SRC_MODELICAWORKSHOP_MODELICAUNIT_H_
#define SRC_MODELICAWORKSHOP_MODELICAUNIT_H_

#include "IEC61970.h"

namespace ModelicaWorkshop {

enum class modelicaUnit {

  /*
   * Angle Unit
   */
  rad,
  sr,

  /*
   * Frequency Unit
   */
  Hz,
  Bq,

  /*
   * Power Unit
   */
  W,
  MW,
  kW,
  mW,
  var,

  /*
   * Voltage Unit
   */
  V,
  MV,
  kV,
  mV,

  /*
   * Current Unit
   */
  A,
  kA,
  mA,

  /*
   * Load Unit
   */
  Ohm,

  /*
   * Shunt Conductance Unit
   */
  S
};

static std::map<const modelicaUnit, const std::string> ModelicaUnit { { modelicaUnit::rad, "rad" }, { modelicaUnit::sr,
    "sr" }, { modelicaUnit::Hz, "Hz" }, { modelicaUnit::Bq, "Bq" }, { modelicaUnit::W, "W" },
    { modelicaUnit::MW, "MW" }, { modelicaUnit::kW, "kW" }, { modelicaUnit::mW, "mW" }, { modelicaUnit::var, "var" }, {
        modelicaUnit::A, "A" }, { modelicaUnit::kA, "kA" }, { modelicaUnit::mA, "mA" }, { modelicaUnit::V, "V" }, {
        modelicaUnit::MV, "MV" }, { modelicaUnit::kV, "kV" }, { modelicaUnit::mV, "mV" }, { modelicaUnit::S, "S" }, {
        modelicaUnit::Ohm, "Ohm" } };

}
#endif /* SRC_MODELICAWORKSHOP_MODELICAUNIT_H_ */
