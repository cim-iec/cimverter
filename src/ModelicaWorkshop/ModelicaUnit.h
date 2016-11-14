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

static std::map<const IEC61970::Base::Domain::UnitSymbol, const modelicaUnit> unit_in_modelica { {
    IEC61970::Base::Domain::UnitSymbol::rad, modelicaUnit::rad }, { IEC61970::Base::Domain::UnitSymbol::sr,
    modelicaUnit::sr }, { IEC61970::Base::Domain::UnitSymbol::V, modelicaUnit::V }, {
    IEC61970::Base::Domain::UnitSymbol::W, modelicaUnit::W }, { IEC61970::Base::Domain::UnitSymbol::VAr,
    modelicaUnit::var }, { IEC61970::Base::Domain::UnitSymbol::Hz, modelicaUnit::Hz }, {
    IEC61970::Base::Domain::UnitSymbol::Bq, modelicaUnit::Bq },
    { IEC61970::Base::Domain::UnitSymbol::A, modelicaUnit::A }, };

static modelicaUnit cast_unit(const IEC61970::Base::Domain::UnitMultiplier unitMultiplier,
                              const IEC61970::Base::Domain::UnitSymbol unitSymbol) {
  switch (unitMultiplier) {
    case IEC61970::Base::Domain::UnitMultiplier::c:
      std::cout << "c" << std::endl;
      break;
    case IEC61970::Base::Domain::UnitMultiplier::m:
      std::cout << "m" << std::endl;
      break;
    case IEC61970::Base::Domain::UnitMultiplier::k:
      std::cout << "k" << std::endl;
      break;
    case IEC61970::Base::Domain::UnitMultiplier::M:
      std::cout << "M" << std::endl;
      break;
    case IEC61970::Base::Domain::UnitMultiplier::none:
//						std::cout << "none" << std::endl;
      break;

  }

  modelicaUnit req;

  switch (unitSymbol) {
    case IEC61970::Base::Domain::UnitSymbol::rad:
      req = modelicaUnit::rad;
      break;
    case IEC61970::Base::Domain::UnitSymbol::sr:
      req = modelicaUnit::sr;
      break;

    case IEC61970::Base::Domain::UnitSymbol::V:
      req = modelicaUnit::V;
      break;

    case IEC61970::Base::Domain::UnitSymbol::W:
      req = modelicaUnit::W;
      break;

    case IEC61970::Base::Domain::UnitSymbol::VAr:
      req = modelicaUnit::var;
      break;

    case IEC61970::Base::Domain::UnitSymbol::Hz:
      req = modelicaUnit::Hz;
      break;

    case IEC61970::Base::Domain::UnitSymbol::Bq:
      req = modelicaUnit::Bq;
      break;

    case IEC61970::Base::Domain::UnitSymbol::A:
      req = modelicaUnit::A;
      break;

  }

//			if (unitMultiplier == IEC61970::Base::Domain::UnitMultiplier::none){
//
//				switch (unitSymbol){
//				case IEC61970::Base::Domain::UnitSymbol::rad:
//					return modelicaUnit::rad;
//				case IEC61970::Base::Domain::UnitSymbol::sr:
//					return modelicaUnit::sr;
//				case IEC61970::Base::Domain::UnitSymbol::V:
//					return modelicaUnit::V;
//				case IEC61970::Base::Domain::UnitSymbol::W:
//					return modelicaUnit::W;
//				case IEC61970::Base::Domain::UnitSymbol::VAr:
//					return modelicaUnit::var;
//				case IEC61970::Base::Domain::UnitSymbol::Hz:
//					return modelicaUnit::Hz;
//				case IEC61970::Base::Domain::UnitSymbol::Bq:
//					return modelicaUnit::Bq;
//				case IEC61970::Base::Domain::UnitSymbol::A:
//					return modelicaUnit::A;
//				}
//
//			} else
  if (unitMultiplier == IEC61970::Base::Domain::UnitMultiplier::k) {

    switch (unitSymbol) {
      case IEC61970::Base::Domain::UnitSymbol::V:
        req = modelicaUnit::kV;
        break;

    }
  }

  return req;
}
}

#endif /* SRC_MODELICAWORKSHOP_MODELICAUNIT_H_ */
