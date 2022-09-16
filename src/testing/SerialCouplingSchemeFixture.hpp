#pragma once

#include "cplscheme/SerialCouplingScheme.hpp"

namespace precice {
namespace testing {
/*
 * @brief A fixture that is used to access private functions of the SerialCouplingScheme class.
 *
 * The fixture can be used to call private functions for individual testing.
 */
struct SerialCouplingSchemeFixture {
  static bool isImplicitCouplingScheme(cplscheme::SerialCouplingScheme &cplscheme);

  static cplscheme::PtrCouplingData getReceiveData(cplscheme::SerialCouplingScheme &cplscheme, DataID dataID);

  static cplscheme::PtrCouplingData getSendData(cplscheme::SerialCouplingScheme &cplscheme, DataID dataID);

  static void setTimeWindows(cplscheme::SerialCouplingScheme &cplscheme, int timeWindows);

  static void storeIteration(cplscheme::SerialCouplingScheme &cplscheme);

  static void initializeStorages(cplscheme::SerialCouplingScheme &cplscheme);

  static void storeExtrapolationData(cplscheme::SerialCouplingScheme &cplscheme);

  static void moveToNextWindow(cplscheme::SerialCouplingScheme &cplscheme);
};

} // namespace testing
} // namespace precice
