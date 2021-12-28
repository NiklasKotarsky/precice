#
# This file lists all sources that will be compiles into the precice library
#

target_sources(precice
    PRIVATE
    ${CMAKE_BINARY_DIR}/src/precice/impl/versions.cpp
    ${CMAKE_BINARY_DIR}/src/precice/impl/versions.hpp
    src/acceleration/Acceleration.cpp
    src/acceleration/Acceleration.hpp
    src/acceleration/AitkenAcceleration.cpp
    src/acceleration/AitkenAcceleration.hpp
    src/acceleration/BaseQNAcceleration.cpp
    src/acceleration/BaseQNAcceleration.hpp
    src/acceleration/BroydenAcceleration.cpp
    src/acceleration/BroydenAcceleration.hpp
    src/acceleration/ConstantRelaxationAcceleration.cpp
    src/acceleration/ConstantRelaxationAcceleration.hpp
    src/acceleration/IQNILSAcceleration.cpp
    src/acceleration/IQNILSAcceleration.hpp
    src/acceleration/MVQNAcceleration.cpp
    src/acceleration/MVQNAcceleration.hpp
    src/acceleration/SharedPointer.hpp
    src/acceleration/config/AccelerationConfiguration.cpp
    src/acceleration/config/AccelerationConfiguration.hpp
    src/acceleration/impl/ConstantPreconditioner.cpp
    src/acceleration/impl/ConstantPreconditioner.hpp
    src/acceleration/impl/ParallelMatrixOperations.cpp
    src/acceleration/impl/ParallelMatrixOperations.hpp
    src/acceleration/impl/Preconditioner.hpp
    src/acceleration/impl/QRFactorization.cpp
    src/acceleration/impl/QRFactorization.hpp
    src/acceleration/impl/ResidualPreconditioner.cpp
    src/acceleration/impl/ResidualPreconditioner.hpp
    src/acceleration/impl/ResidualSumPreconditioner.cpp
    src/acceleration/impl/ResidualSumPreconditioner.hpp
    src/acceleration/impl/SVDFactorization.cpp
    src/acceleration/impl/SVDFactorization.hpp
    src/acceleration/impl/SharedPointer.hpp
    src/acceleration/impl/ValuePreconditioner.cpp
    src/acceleration/impl/ValuePreconditioner.hpp
    src/action/Action.hpp
    src/action/ComputeCurvatureAction.cpp
    src/action/ComputeCurvatureAction.hpp
    src/action/PythonAction.cpp
    src/action/PythonAction.hpp
    src/action/RecorderAction.cpp
    src/action/RecorderAction.hpp
    src/action/ScaleByAreaAction.cpp
    src/action/ScaleByAreaAction.hpp
    src/action/ScaleByDtAction.cpp
    src/action/ScaleByDtAction.hpp
    src/action/SharedPointer.hpp
    src/action/SummationAction.cpp
    src/action/SummationAction.hpp
    src/action/config/ActionConfiguration.cpp
    src/action/config/ActionConfiguration.hpp
    src/com/CommunicateBoundingBox.cpp
    src/com/CommunicateBoundingBox.hpp
    src/com/CommunicateMesh.cpp
    src/com/CommunicateMesh.hpp
    src/com/Communication.cpp
    src/com/Communication.hpp
    src/com/CommunicationFactory.hpp
    src/com/ConnectionInfoPublisher.cpp
    src/com/ConnectionInfoPublisher.hpp
    src/com/MPICommunication.cpp
    src/com/MPICommunication.hpp
    src/com/MPIDirectCommunication.cpp
    src/com/MPIDirectCommunication.hpp
    src/com/MPIPortsCommunication.cpp
    src/com/MPIPortsCommunication.hpp
    src/com/MPIPortsCommunicationFactory.cpp
    src/com/MPIPortsCommunicationFactory.hpp
    src/com/MPIRequest.cpp
    src/com/MPIRequest.hpp
    src/com/MPISinglePortsCommunication.cpp
    src/com/MPISinglePortsCommunication.hpp
    src/com/MPISinglePortsCommunicationFactory.cpp
    src/com/MPISinglePortsCommunicationFactory.hpp
    src/com/Request.cpp
    src/com/Request.hpp
    src/com/SharedPointer.hpp
    src/com/SocketCommunication.cpp
    src/com/SocketCommunication.hpp
    src/com/SocketCommunicationFactory.cpp
    src/com/SocketCommunicationFactory.hpp
    src/com/SocketRequest.cpp
    src/com/SocketRequest.hpp
    src/com/SocketSendQueue.cpp
    src/com/SocketSendQueue.hpp
    src/com/config/CommunicationConfiguration.cpp
    src/com/config/CommunicationConfiguration.hpp
    src/cplscheme/BaseCouplingScheme.cpp
    src/cplscheme/BaseCouplingScheme.hpp
    src/cplscheme/BiCouplingScheme.cpp
    src/cplscheme/BiCouplingScheme.hpp
    src/cplscheme/CompositionalCouplingScheme.cpp
    src/cplscheme/CompositionalCouplingScheme.hpp
    src/cplscheme/Constants.cpp
    src/cplscheme/Constants.hpp
    src/cplscheme/CouplingData.cpp
    src/cplscheme/CouplingData.hpp
    src/cplscheme/CouplingScheme.cpp
    src/cplscheme/CouplingScheme.hpp
    src/cplscheme/MultiCouplingScheme.cpp
    src/cplscheme/MultiCouplingScheme.hpp
    src/cplscheme/ParallelCouplingScheme.cpp
    src/cplscheme/ParallelCouplingScheme.hpp
    src/cplscheme/SerialCouplingScheme.cpp
    src/cplscheme/SerialCouplingScheme.hpp
    src/cplscheme/SharedPointer.hpp
    src/cplscheme/config/CouplingSchemeConfiguration.cpp
    src/cplscheme/config/CouplingSchemeConfiguration.hpp
    src/cplscheme/impl/AbsoluteConvergenceMeasure.cpp
    src/cplscheme/impl/AbsoluteConvergenceMeasure.hpp
    src/cplscheme/impl/ConvergenceMeasure.hpp
    src/cplscheme/impl/Extrapolation.cpp
    src/cplscheme/impl/Extrapolation.hpp
    src/cplscheme/impl/MinIterationConvergenceMeasure.cpp
    src/cplscheme/impl/MinIterationConvergenceMeasure.hpp
    src/cplscheme/impl/RelativeConvergenceMeasure.cpp
    src/cplscheme/impl/RelativeConvergenceMeasure.hpp
    src/cplscheme/impl/ResidualRelativeConvergenceMeasure.cpp
    src/cplscheme/impl/ResidualRelativeConvergenceMeasure.hpp
    src/cplscheme/impl/SharedPointer.hpp
    src/io/Export.hpp
    src/io/ExportContext.hpp
    src/io/ExportVTK.cpp
    src/io/ExportVTK.hpp
    src/io/ExportVTP.cpp
    src/io/ExportVTP.hpp
    src/io/ExportVTU.cpp
    src/io/ExportVTU.hpp
    src/io/ExportXML.cpp
    src/io/ExportXML.hpp
    src/io/SharedPointer.hpp
    src/io/TXTReader.cpp
    src/io/TXTReader.hpp
    src/io/TXTTableWriter.cpp
    src/io/TXTTableWriter.hpp
    src/io/TXTWriter.cpp
    src/io/TXTWriter.hpp
    src/io/config/ExportConfiguration.cpp
    src/io/config/ExportConfiguration.hpp
    src/logging/LogConfiguration.cpp
    src/logging/LogConfiguration.hpp
    src/logging/LogMacros.hpp
    src/logging/Logger.cpp
    src/logging/Logger.hpp
    src/logging/Tracer.cpp
    src/logging/Tracer.hpp
    src/logging/config/LogConfiguration.cpp
    src/logging/config/LogConfiguration.hpp
    src/m2n/BoundM2N.cpp
    src/m2n/BoundM2N.hpp
    src/m2n/DistributedComFactory.hpp
    src/m2n/DistributedCommunication.hpp
    src/m2n/GatherScatterComFactory.cpp
    src/m2n/GatherScatterComFactory.hpp
    src/m2n/GatherScatterCommunication.cpp
    src/m2n/GatherScatterCommunication.hpp
    src/m2n/M2N.cpp
    src/m2n/M2N.hpp
    src/m2n/PointToPointComFactory.cpp
    src/m2n/PointToPointComFactory.hpp
    src/m2n/PointToPointCommunication.cpp
    src/m2n/PointToPointCommunication.hpp
    src/m2n/SharedPointer.hpp
    src/m2n/config/M2NConfiguration.cpp
    src/m2n/config/M2NConfiguration.hpp
    src/mapping/Mapping.cpp
    src/mapping/Mapping.hpp
    src/mapping/NearestNeighborMapping.cpp
    src/mapping/NearestNeighborMapping.hpp
    src/mapping/NearestProjectionMapping.cpp
    src/mapping/NearestProjectionMapping.hpp
    src/mapping/PetRadialBasisFctMapping.hpp
    src/mapping/Polation.cpp
    src/mapping/Polation.hpp
    src/mapping/RadialBasisFctMapping.hpp
    src/mapping/SharedPointer.hpp
    src/mapping/config/MappingConfiguration.cpp
    src/mapping/config/MappingConfiguration.hpp
    src/mapping/impl/BasisFunctions.hpp
    src/math/barycenter.cpp
    src/math/barycenter.hpp
    src/math/constants.hpp
    src/math/differences.hpp
    src/math/geometry.cpp
    src/math/geometry.hpp
    src/math/la.hpp
    src/math/math.hpp
    src/mesh/BoundingBox.cpp
    src/mesh/BoundingBox.hpp
    src/mesh/Data.cpp
    src/mesh/Data.hpp
    src/mesh/Edge.cpp
    src/mesh/Edge.hpp
    src/mesh/Filter.hpp
    src/mesh/Mesh.cpp
    src/mesh/Mesh.hpp
    src/mesh/RangeAccessor.hpp
    src/mesh/SharedPointer.hpp
    src/mesh/Triangle.cpp
    src/mesh/Triangle.hpp
    src/mesh/Utils.cpp
    src/mesh/Utils.hpp
    src/mesh/Vertex.cpp
    src/mesh/Vertex.hpp
    src/mesh/config/DataConfiguration.cpp
    src/mesh/config/DataConfiguration.hpp
    src/mesh/config/MeshConfiguration.cpp
    src/mesh/config/MeshConfiguration.hpp
    src/partition/Partition.cpp
    src/partition/Partition.hpp
    src/partition/ProvidedPartition.cpp
    src/partition/ProvidedPartition.hpp
    src/partition/ReceivedPartition.cpp
    src/partition/ReceivedPartition.hpp
    src/partition/SharedPointer.hpp
    src/precice/SolverInterface.cpp
    src/precice/SolverInterface.hpp
    src/precice/Tooling.cpp
    src/precice/Tooling.hpp
    src/precice/config/Configuration.cpp
    src/precice/config/Configuration.hpp
    src/precice/config/ParticipantConfiguration.cpp
    src/precice/config/ParticipantConfiguration.hpp
    src/precice/config/SharedPointer.hpp
    src/precice/config/SolverInterfaceConfiguration.cpp
    src/precice/config/SolverInterfaceConfiguration.hpp
    src/precice/impl/CommonErrorMessages.hpp
    src/precice/impl/DataContext.cpp
    src/precice/impl/DataContext.hpp
    src/precice/impl/MappingContext.hpp
    src/precice/impl/MeshContext.hpp
    src/precice/impl/Participant.cpp
    src/precice/impl/Participant.hpp
    src/precice/impl/ReadDataContext.cpp
    src/precice/impl/ReadDataContext.hpp
    src/precice/impl/SharedPointer.hpp
    src/precice/impl/SolverInterfaceImpl.cpp
    src/precice/impl/SolverInterfaceImpl.hpp
    src/precice/impl/ValidationMacros.hpp
    src/precice/impl/WatchIntegral.cpp
    src/precice/impl/WatchIntegral.hpp
    src/precice/impl/WatchPoint.cpp
    src/precice/impl/WatchPoint.hpp
    src/precice/types.hpp
    src/query/Index.cpp
    src/query/Index.hpp
    src/query/impl/Indexer.cpp
    src/query/impl/Indexer.hpp
    src/query/impl/RTreeAdapter.hpp
    src/time/SharedPointer.hpp
    src/time/Time.cpp
    src/time/Time.hpp
    src/time/Waveform.cpp
    src/time/Waveform.hpp
    src/utils/ArgumentFormatter.hpp
    src/utils/Dimensions.cpp
    src/utils/Dimensions.hpp
    src/utils/EigenHelperFunctions.cpp
    src/utils/EigenHelperFunctions.hpp
    src/utils/EigenIO.hpp
    src/utils/Event.cpp
    src/utils/Event.hpp
    src/utils/EventUtils.cpp
    src/utils/EventUtils.hpp
    src/utils/Helpers.cpp
    src/utils/Helpers.hpp
    src/utils/MPI_Mock.hpp
    src/utils/ManageUniqueIDs.cpp
    src/utils/ManageUniqueIDs.hpp
    src/utils/MasterSlave.cpp
    src/utils/MasterSlave.hpp
    src/utils/MultiLock.hpp
    src/utils/Parallel.cpp
    src/utils/Parallel.hpp
    src/utils/Petsc.cpp
    src/utils/Petsc.hpp
    src/utils/PointerVector.hpp
    src/utils/Statistics.hpp
    src/utils/String.cpp
    src/utils/String.hpp
    src/utils/TableWriter.cpp
    src/utils/TableWriter.hpp
    src/utils/TypeNames.hpp
    src/utils/algorithm.hpp
    src/utils/assertion.hpp
    src/utils/fmt.hpp
    src/utils/fmtEigen.hpp
    src/utils/fmtSTL.hpp
    src/utils/networking.cpp
    src/utils/networking.hpp
    src/utils/span.hpp
    src/utils/span_tools.hpp
    src/utils/stacktrace.cpp
    src/utils/stacktrace.hpp
    src/utils/traits.hpp
    src/xml/ConfigParser.cpp
    src/xml/ConfigParser.hpp
    src/xml/Printer.cpp
    src/xml/Printer.hpp
    src/xml/ValueParser.cpp
    src/xml/ValueParser.hpp
    src/xml/XMLAttribute.hpp
    src/xml/XMLTag.cpp
    src/xml/XMLTag.hpp
    )

#
# Select headers to install
#

set_property(TARGET precice PROPERTY PUBLIC_HEADER
    src/precice/SolverInterface.hpp
    src/precice/Tooling.hpp
    src/precice/types.hpp
    )
