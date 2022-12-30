#pragma once

#include <string>
#include <vector>

#include "BaseCouplingScheme.hpp"
#include "cplscheme/Constants.hpp"
#include "logging/Logger.hpp"
#include "m2n/SharedPointer.hpp"
#include "mesh/SharedPointer.hpp"
#include "precice/impl/SharedPointer.hpp"
#include "precice/types.hpp"
#include "utils/assertion.hpp"

namespace precice {
namespace cplscheme {
class CouplingData;

/**
 * @brief Abstract base class for coupling schemes with two participants.
 *
 * ! General description
 * A BiCouplingScheme couples two participants. It is a specialization of
 * BaseCouplingScheme.
 *
 */
class BiCouplingScheme : public BaseCouplingScheme {

public:
  BiCouplingScheme(
      double                        maxTime,
      int                           maxTimeWindows,
      double                        timeWindowSize,
      int                           validDigits,
      std::string                   firstParticipant,
      std::string                   secondParticipant,
      const std::string &           localParticipant,
      m2n::PtrM2N                   m2n,
      int                           maxIterations,
      CouplingMode                  cplMode,
      constants::TimesteppingMethod dtMethod,
      int                           extrapolationOrder);

  /// Adds data to be sent on data exchange and possibly be modified during coupling iterations.
  void addDataToSend(
      const mesh::PtrData &data,
      mesh::PtrMesh        mesh,
      bool                 requiresInitialization);

  /// Adds data to be received on data exchange.
  void addDataToReceive(
      const mesh::PtrData &data,
      mesh::PtrMesh        mesh,
      bool                 requiresInitialization);

  void determineInitialDataExchange() override;

  /// returns list of all coupling partners
  std::vector<std::string> getCouplingPartners() const override final;

  /**
   * @returns true, if coupling scheme has any sendData
   */
  bool hasAnySendData() override final;

  /**
   * @returns true, if coupling scheme has sendData with given DataID
   */
  bool hasSendData(DataID dataID);

  void storeReceiveData(double relativeDt, bool mustOverwrite = false) override final;

  void loadReceiveDataFromStorage(double relativeDt) override final;

  std::vector<double> getReceiveTimes() override final;

protected:
  /// Returns all data to be sent.
  DataMap &getSendData();

  /// Returns all data to be received.
  DataMap &getReceiveData();

  /**
   * @brief BiCouplingScheme has _sendData and _receiveData
   * @returns DataMap with all data
   */
  const DataMap getAllData() override final;

  /// Sets the values
  CouplingData *getSendData(DataID dataID);

  /// Returns all data to be received with data ID as given.
  CouplingData *getReceiveData(DataID dataID);

  /// @return Communication device to the other coupling participant.
  m2n::PtrM2N getM2N() const;

  void storeSendValuesAtTime(double relativeDt) override final;

  void initializeSendDataStorage() override final;

private:
  mutable logging::Logger _log{"cplscheme::BiCouplingScheme"};

  /// Communication to the other coupling participant.
  m2n::PtrM2N _m2n;

  /// All send data as a map "data ID -> data"
  DataMap _sendData;

  /// All receive data as a map "data ID -> data"
  DataMap _receiveData;

  /// First participant name.
  std::string _firstParticipant = "unknown";

  /// Second participant name.
  std::string _secondParticipant = "unknown";
};

} // namespace cplscheme
} // namespace precice
