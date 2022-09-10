#include <Eigen/Core>
#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "acceleration/config/AccelerationConfiguration.hpp"
#include "cplscheme/BaseCouplingScheme.hpp"
#include "cplscheme/Constants.hpp"
#include "cplscheme/CouplingData.hpp"
#include "cplscheme/ParallelCouplingScheme.hpp"
#include "cplscheme/SharedPointer.hpp"
#include "cplscheme/config/CouplingSchemeConfiguration.hpp"
#include "cplscheme/impl/MinIterationConvergenceMeasure.hpp"
#include "cplscheme/impl/SharedPointer.hpp"
#include "logging/LogMacros.hpp"
#include "m2n/config/M2NConfiguration.hpp"
#include "mesh/Data.hpp"
#include "mesh/Mesh.hpp"
#include "mesh/SharedPointer.hpp"
#include "mesh/config/DataConfiguration.hpp"
#include "mesh/config/MeshConfiguration.hpp"
#include "precice/config/ParticipantConfiguration.hpp"
#include "testing/ParallelCouplingSchemeFixture.hpp"
#include "testing/TestContext.hpp"
#include "testing/Testing.hpp"
#include "utils/EigenHelperFunctions.hpp"
#include "xml/XMLTag.hpp"

using namespace precice;
using namespace precice::cplscheme;

BOOST_AUTO_TEST_SUITE(CplSchemeTests)

struct ParallelImplicitCouplingSchemeFixture {
  std::string _pathToTests;

  ParallelImplicitCouplingSchemeFixture()
  {
    _pathToTests = testing::getPathToSources() + "/cplscheme/tests/";
  }
};

BOOST_FIXTURE_TEST_SUITE(ParallelImplicitCouplingSchemeTests, ParallelImplicitCouplingSchemeFixture)

#ifndef PRECICE_NO_MPI

BOOST_AUTO_TEST_CASE(testParseConfigurationWithRelaxation)
{
  PRECICE_TEST(1_rank);
  using namespace mesh;

  int dimensions = 3;

  std::string path(_pathToTests + "parallel-implicit-cplscheme-relax-const-config.xml");

  xml::XMLTag          root = xml::getRootTag();
  PtrDataConfiguration dataConfig(new DataConfiguration(root));
  dataConfig->setDimensions(dimensions);
  PtrMeshConfiguration meshConfig(new MeshConfiguration(root, dataConfig));
  meshConfig->setDimensions(dimensions);
  m2n::M2NConfiguration::SharedPointer m2nConfig(
      new m2n::M2NConfiguration(root));
  precice::config::PtrParticipantConfiguration participantConfig(new precice::config::ParticipantConfiguration(root, meshConfig));
  participantConfig->setDimensions(dimensions);
  CouplingSchemeConfiguration cplSchemeConfig(root, meshConfig, m2nConfig, participantConfig);

  xml::configure(root, xml::ConfigurationContext{}, path);
  BOOST_CHECK(cplSchemeConfig._accelerationConfig->getAcceleration().get());
}

BOOST_AUTO_TEST_CASE(testInitializeData)
{
  PRECICE_TEST("Participant0"_on(1_rank), "Participant1"_on(1_rank), Require::Events);
  testing::ConnectionOptions options;
  options.useOnlyPrimaryCom = true;
  std::string participant0("Participant0");
  std::string participant1("Participant1");
  auto        m2n = context.connectPrimaryRanks(participant0, participant1, options);

  std::map<std::string, m2n::PtrM2N> m2ns;
  if (context.name == participant0) {
    m2ns[participant1] = m2n;
  } else {
    m2ns[participant0] = m2n;
  }

  xml::XMLTag root = xml::getRootTag();

  int dimensions = 3;

  // Create a data configuration, to simplify configuration of data
  mesh::PtrDataConfiguration dataConfig(new mesh::DataConfiguration(root));
  dataConfig->setDimensions(dimensions);
  dataConfig->addData("Data0", 1);
  dataConfig->addData("Data1", 3);

  mesh::MeshConfiguration meshConfig(root, dataConfig);
  meshConfig.setDimensions(dimensions);
  mesh::PtrMesh mesh(new mesh::Mesh("Mesh", 3, testing::nextMeshID()));
  const auto    dataID0 = mesh->createData("Data0", 1, 0_dataID)->getID();
  const auto    dataID1 = mesh->createData("Data1", 3, 1_dataID)->getID();
  mesh->createVertex(Eigen::Vector3d::Zero());
  mesh->allocateDataValues();
  meshConfig.addMesh(mesh);

  // Create all parameters necessary to create a ParallelImplicitCouplingScheme object
  double      maxTime        = 1.0;
  int         maxTimeWindows = 3;
  double      timeWindowSize = 0.1;
  std::string nameParticipant0("Participant0");
  std::string nameParticipant1("Participant1");
  std::string from;
  std::string to;
  int         sendDataIndex              = -1;
  int         receiveDataIndex           = -1;
  bool        dataRequiresInitialization = false;
  int         extrapolationOrder         = 0;
  if (context.isNamed(nameParticipant0)) {
    sendDataIndex              = dataID0;
    receiveDataIndex           = dataID1;
    dataRequiresInitialization = true;
    from                       = nameParticipant1;
    to                         = nameParticipant1;
  } else {
    sendDataIndex              = dataID1;
    receiveDataIndex           = dataID0;
    dataRequiresInitialization = true;
    from                       = nameParticipant0;
    to                         = nameParticipant0;
  }

  // Create the coupling scheme object
  ParallelCouplingScheme cplScheme(
      maxTime, maxTimeWindows, timeWindowSize, 16, context.name, m2ns, constants::FIXED_TIME_WINDOW_SIZE, BaseCouplingScheme::Implicit, nameParticipant1, 100, extrapolationOrder);

  using Fixture = testing::ParallelCouplingSchemeFixture;
  cplScheme.addDataToSend(mesh->data(sendDataIndex), mesh, dataRequiresInitialization, to);
  CouplingData *sendCouplingData = Fixture::getSendData(cplScheme, sendDataIndex);
  cplScheme.addDataToReceive(mesh->data(receiveDataIndex), mesh, dataRequiresInitialization, from);
  CouplingData *receiveCouplingData = Fixture::getReceiveData(cplScheme, receiveDataIndex);
  cplScheme.determineInitialDataExchange();

  // Add convergence measures
  int                                    minIterations = 3;
  cplscheme::impl::PtrConvergenceMeasure minIterationConvMeasure1(
      new cplscheme::impl::MinIterationConvergenceMeasure(minIterations));
  cplscheme::impl::PtrConvergenceMeasure minIterationConvMeasure2(
      new cplscheme::impl::MinIterationConvergenceMeasure(minIterations));
  cplScheme.addConvergenceMeasure(dataID1, false, false, minIterationConvMeasure1, true);
  cplScheme.addConvergenceMeasure(dataID0, false, false, minIterationConvMeasure2, true);

  std::string writeIterationCheckpoint(constants::actionWriteIterationCheckpoint());
  std::string readIterationCheckpoint(constants::actionReadIterationCheckpoint());

  if (context.isNamed(nameParticipant0)) {
    BOOST_TEST(testing::equals(receiveCouplingData->values(), Eigen::Vector3d(0.0, 0.0, 0.0)));
    BOOST_TEST(receiveCouplingData->values().size() == 3);
    BOOST_TEST(receiveCouplingData->previousIteration().size() == 3);
    BOOST_TEST(testing::equals(sendCouplingData->values()(0), 0.0));
    BOOST_TEST(sendCouplingData->values().size() == 1);
    BOOST_TEST(sendCouplingData->previousIteration().size() == 1);
    BOOST_TEST(Fixture::isImplicitCouplingScheme(cplScheme));
    BOOST_TEST(cplScheme.isActionRequired(constants::actionWriteInitialData()));
    sendCouplingData->values() = Eigen::VectorXd::Constant(1, 4.0);
    cplScheme.markActionFulfilled(constants::actionWriteInitialData());
    cplScheme.initialize(0.0, 0);
    BOOST_TEST(cplScheme.hasDataBeenReceived());
    BOOST_TEST(testing::equals(receiveCouplingData->values(), Eigen::Vector3d(1.0, 2.0, 3.0)));
    BOOST_TEST(receiveCouplingData->previousIteration().size() == 3);
    BOOST_TEST(testing::equals(receiveCouplingData->previousIteration(), Eigen::Vector3d(0.0, 0.0, 0.0)));
    BOOST_TEST(sendCouplingData->previousIteration().size() == 1);
    BOOST_TEST(testing::equals(sendCouplingData->previousIteration()(0), 4.0));
    while (cplScheme.isCouplingOngoing()) {
      if (cplScheme.isActionRequired(writeIterationCheckpoint)) {
        cplScheme.markActionFulfilled(writeIterationCheckpoint);
      }
      if (cplScheme.isActionRequired(readIterationCheckpoint)) {
        cplScheme.markActionFulfilled(readIterationCheckpoint);
      }
      cplScheme.addComputedTime(timeWindowSize);
      cplScheme.advance();
      BOOST_TEST(cplScheme.hasDataBeenReceived());
    }
  } else {
    BOOST_TEST(context.isNamed(nameParticipant1));
    BOOST_TEST(cplScheme.isActionRequired(constants::actionWriteInitialData()));
    Eigen::VectorXd v(3);
    v << 1.0, 2.0, 3.0;
    sendCouplingData->values() = v;
    cplScheme.markActionFulfilled(constants::actionWriteInitialData());
    BOOST_TEST(testing::equals(receiveCouplingData->values()(0), 0.0));
    BOOST_TEST(receiveCouplingData->values().size() == 1);
    BOOST_TEST(receiveCouplingData->previousIteration().size() == 1);
    BOOST_TEST(testing::equals(sendCouplingData->values(), Eigen::Vector3d(1.0, 2.0, 3.0)));
    BOOST_TEST(sendCouplingData->values().size() == 3);
    BOOST_TEST(sendCouplingData->previousIteration().size() == 3);
    cplScheme.initialize(0.0, 0);
    BOOST_TEST(cplScheme.hasDataBeenReceived());
    BOOST_TEST(testing::equals(receiveCouplingData->values()(0), 4.0));
    BOOST_TEST(receiveCouplingData->previousIteration().size() == 1);
    BOOST_TEST(testing::equals(receiveCouplingData->previousIteration()(0), 0.0));
    BOOST_TEST(testing::equals(sendCouplingData->values(), Eigen::Vector3d(1.0, 2.0, 3.0)));
    BOOST_TEST(sendCouplingData->previousIteration().size() == 3);
    BOOST_TEST(testing::equals(sendCouplingData->previousIteration(), Eigen::Vector3d(1.0, 2.0, 3.0)));
    while (cplScheme.isCouplingOngoing()) {
      if (cplScheme.isActionRequired(writeIterationCheckpoint)) {
        cplScheme.markActionFulfilled(writeIterationCheckpoint);
      }
      cplScheme.addComputedTime(timeWindowSize);
      cplScheme.advance();
      BOOST_TEST(cplScheme.hasDataBeenReceived());
      if (cplScheme.isActionRequired(readIterationCheckpoint)) {
        cplScheme.markActionFulfilled(readIterationCheckpoint);
      }
    }
  }
  cplScheme.finalize();
}
#endif // not PRECICE_NO_MPI

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
