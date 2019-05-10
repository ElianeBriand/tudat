/*    Copyright (c) 2010-2019, Delft University of Technology *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 */

#include "body.h"

#include <boost/python.hpp>
#include <boost/numpy.hpp>

#include <boost/python/suite/indexing/map_indexing_suite.hpp>

#include <Tudat/PyBindings/WrapperCode/ContainerIndexing.h>

#include "Tudat/Basics/basicTypedefs.h"

#include "Tudat/SimulationSetup/EnvironmentSetup/body.h"


namespace p = boost::python;
namespace np = boost::numpy;


namespace tudat {
    namespace PyBindings_internal {


        namespace {

            std::shared_ptr<tudat::simulation_setup::Body>
            Body_constructorWrapper(const Eigen::Vector6d &state) {
                auto ret = std::make_shared<tudat::simulation_setup::Body>(state);
                return ret;
            }

            std::shared_ptr<tudat::simulation_setup::Body>
            Body_constructorWrapper_noArgs() {
                auto ret = std::make_shared<tudat::simulation_setup::Body>(Eigen::Vector6d::Zero());
                return ret;
            }

            void Body_setBodyInertiaTensor_overloadResolutionHelper_matrixAlone(std::shared_ptr<tudat::simulation_setup::Body> body, const Eigen::Matrix3d& mat) {
                body->setBodyInertiaTensor(mat);
            }

            void Body_setBodyInertiaTensor_overloadResolutionHelper_matrixWDouble(std::shared_ptr<tudat::simulation_setup::Body> body,
                    const Eigen::Matrix3d& mat,
                    const double scaledMeanMomentOfInertia) {
                body->setBodyInertiaTensor(mat,scaledMeanMomentOfInertia);
            }

            BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(setBodyInertiaTensorFromGravityFieldAndExistingMeanMoment_overloads,
                                            tudat::simulation_setup::Body::setBodyInertiaTensorFromGravityFieldAndExistingMeanMoment, 0, 1);

            BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(getGravityFieldVariation_overloads,
                                                   tudat::simulation_setup::Body::getGravityFieldVariation, 1, 2);


        }


        void PyExport_body() {

            p::class_<tudat::simulation_setup::NamedBodyMap>("NamedBodyMap")
                    .def("__len__", &tudat::simulation_setup::NamedBodyMap::size)
                    .def("clear", &tudat::simulation_setup::NamedBodyMap::clear)
                    .def("__getitem__", &MinimalMapIndexing<tudat::simulation_setup::NamedBodyMap>::get,
                         p::return_value_policy<p::copy_non_const_reference>())
                    .def("__setitem__", &MinimalMapIndexing<tudat::simulation_setup::NamedBodyMap>::set,
                         p::with_custodian_and_ward<1, 2>()) // to let container keep value
                    .def("__delitem__", &MinimalMapIndexing<tudat::simulation_setup::NamedBodyMap>::del);

            p::class_<tudat::simulation_setup::Body, std::shared_ptr<tudat::simulation_setup::Body>, boost::noncopyable>(
                    "Body", p::no_init)
                    .def("__init__", p::make_constructor(&Body_constructorWrapper,
                                                         p::default_call_policies(),
                                                         (p::arg("state"))))

                    .def("__init__", p::make_constructor(&Body_constructorWrapper_noArgs,
                                                         p::default_call_policies()))

                    .def("setState", &tudat::simulation_setup::Body::setState,
                         (p::arg("state")),
                         "Set current state of body manually, which must be in the global frame.\n\n\n"
                         ":param state: Current state of the body that is set.")

                    .def("getState",
                         &tudat::simulation_setup::Body::getState,
                         "Returns the internally stored current state vector.\n\n\n"
                         ":return: Current state.\n\n")

                    .def("setStateFromEphemeris",
                         &tudat::simulation_setup::Body::setStateFromEphemeris<double, double>,
                         (p::arg("time")),
                         "set the current state of the body from its ephemeris and global-to-ephemeris-frame function.\n\n"
                         ":param time: Time at which the global state is to be set.\n\n")

                    .def("getStateInBaseFrameFromEphemeris",
                         &tudat::simulation_setup::Body::getStateInBaseFrameFromEphemeris<double, double>,
                         (p::arg("time")),
                         "Get the current state of the body from its ephemeris and\n"
                         "global-to-ephemeris-frame function.  It calls the setStateFromEphemeris state, resetting the currentState_ /\n"
                         "currentLongState_ variables, and returning the state with the requested precision\n\n\n"
                         ":param time: Time at which to evaluate states.\n"
                         ":return: State at requested time\n\n")

                    .def("getGlobalFrameOriginBarycentricStateFromEphemeris",
                         &tudat::simulation_setup::Body::getGlobalFrameOriginBarycentricStateFromEphemeris<double, double>,
                         (p::arg("time")),
                         "Get the current berycentric state of the body from its ephemeris andcglobal-to-ephemeris-frame "
                         "function. It calls the setStateFromEphemeris state, resetting the currentBarycentricState_ or "
                         "currentBarycentricLongState_ variables, and returning the state with the requested precision. This function can ONLY be "
                         "called if this body is the global frame origin, otherwise an exception is thrown.\n\n\n"
                         ":param time: Time at which to evaluate states.\n"
                         ":return: Barycentric State at requested time\n\n")

                    .def("getRotationalStateVector",
                         &tudat::simulation_setup::Body::getRotationalStateVector,
                         "Returns the internally stored current rotational state vector.\n\n\n"
                         ":return: Current rotational state.\n\n")

                    .def("getPosition",
                         &tudat::simulation_setup::Body::getPosition,
                         "Returns the internally stored current position vector.\n\n\n"
                         ":return: Current position.\n\n")

                    .def("getVelocity",
                         &tudat::simulation_setup::Body::getVelocity,
                         "Returns the internally stored current velocity vector.\n\n\n"
                         ":return: Current velocity.\n\n")

                    .def("setCurrentRotationToLocalFrameFromEphemeris",
                         &tudat::simulation_setup::Body::setCurrentRotationToLocalFrameFromEphemeris,
                         (p::arg("time")),
                         "Function to set the rotation from global to body-fixed frame at given time, using the "
                         "rotationalEphemeris_ member object\n\n\n"
                         ":param time: Time at which the rotation is to be retrieved.\n\n")

                    .def("setCurrentRotationToLocalFrameDerivativeFromEphemeris",
                         &tudat::simulation_setup::Body::setCurrentRotationToLocalFrameDerivativeFromEphemeris,
                         (p::arg("time")),
                         "Function to set the rotation matrix derivative from global to body-fixed frame at given time, "
                         "using the rotationalEphemeris_ member object\n\n\n"
                         ":param time: Time at which the rotation matrix derivative is to be retrieved.\n\n")

                    .def("setCurrentAngularVelocityVectorInGlobalFrame",
                         &tudat::simulation_setup::Body::setCurrentAngularVelocityVectorInGlobalFrame,
                         (p::arg("time")),
                         "Function to set the angular velocity vector in the global frame at given time, using the "
                         "rotationalEphemeris_ member object\n\n\n"
                         ":param time: Time at which the angular velocity vector in the global frame is to be retrieved.\n\n")

                    .def("setCurrentRotationalStateToLocalFrameFromEphemeris",
                         &tudat::simulation_setup::Body::setCurrentRotationalStateToLocalFrameFromEphemeris<double>,
                         (p::arg("time")),
                         "Function to set the full rotational state at (rotation from global to body-fixed frame "
                         "rotation matrix derivative from global to body-fixed frame and angular velocity vector in the "
                         "global frame) at given time, using the rotationalEphemeris_ member object."
                         "\n\n\n"
                         ":param time: Time at which the angular velocity vector in the global frame is to be retrieved.\n\n")

                    .def("setCurrentRotationalStateToLocalFrame",
                         &tudat::simulation_setup::Body::setCurrentRotationalStateToLocalFrame,
                         (p::arg("currentRotationalStateFromLocalToGlobalFrame")),
                         "Function to set the full rotational state  directly (rotation from global to body-fixed frame "
                         "rotation matrix derivative from global to body-fixed frame and angular velocity vector in the "
                         "global frame) directly, by providing the current rotational state as input."
                         "\n\n\n"
                         ":param currentRotationalStateFromLocalToGlobalFrame: Quaternion from body-fixed to propagation frame"
                         " (in vector form) and the body's angular velocity vector in body-fixed frame.\n\n")

                    .def("getCurrentRotationToGlobalFrame",
                         &tudat::simulation_setup::Body::getCurrentRotationToGlobalFrame,
                         "Get current rotation from body-fixed to inertial frame, as set from the rotationalEphemeris_ "
                         "by the setCurrentRotationalStateToLocalFrameFromEphemeris or "
                         "setCurrentRotationToLocalFrameFromEphemeris function.  If body has no rotational ephemeris, "
                         "an identity quaternion (no rotation) is returned. "
                         "\n\n\n"
                         ":return: Current rotation from body-fixed to inertial frame.\n\n")

                    .def("getCurrentRotationToLocalFrame",
                         &tudat::simulation_setup::Body::getCurrentRotationToLocalFrame,
                         "Get current rotation from inertial to body-fixed frame, as set from the rotationalEphemeris_ "
                         "by the setCurrentRotationalStateToLocalFrameFromEphemeris or "
                         "setCurrentRotationToLocalFrameFromEphemeris function.  If body has no rotational ephemeris, "
                         "an identity quaternion (no rotation) is returned. "
                         "\n\n\n"
                         ":return: Current rotation from inertial to body-fixed frame.\n\n")

                    .def("getCurrentRotationalState",
                         &tudat::simulation_setup::Body::getCurrentRotationalState,
                         "Get current rotational state, expressed as a quaternion from global to body-fixed frame "
                         "(in vector form) and the body's angular velocity vector in inertial frame."
                         "\n\n\n"
                         ":return: Current rotational state in quaternions and rotational velocity.\n\n")

                    .def("getCurrentRotationMatrixDerivativeToGlobalFrame",
                         &tudat::simulation_setup::Body::getCurrentRotationMatrixDerivativeToGlobalFrame,
                         "Get current rotation matrix derivative from body-fixed frame to global, as set from the\n"
                         " rotationalEphemeris_ by the setCurrentRotationalStateToLocalFrameFromEphemeris or\n"
                         " setCurrentRotationToLocalFrameDerivativeFromEphemeris function. If body has no rotational\n"
                         " ephemeris, an zero matrix (no rotation) is returned."
                         "\n\n\n"
                         ":return: Current otation matrix derivative from global to body-fixed frame.\n\n")

                    .def("getCurrentRotationMatrixDerivativeToLocalFrame",
                         &tudat::simulation_setup::Body::getCurrentRotationMatrixDerivativeToLocalFrame,
                         "Get current rotation matrix derivative from global to body-fixed frame, as set from the\n"
                         " rotationalEphemeris_ by the setCurrentRotationalStateToLocalFrameFromEphemeris or\n"
                         " setCurrentRotationToLocalFrameDerivativeFromEphemeris function. If body has no rotational\n"
                         " ephemeris, an zero matrix (no rotation) is returned."
                         "\n\n\n"
                         ":return: Current rotation matrix derivative from global to body-fixed frame.\n\n")

                    .def("getCurrentAngularVelocityVectorInGlobalFrame",
                         &tudat::simulation_setup::Body::getCurrentAngularVelocityVectorInGlobalFrame,
                         "Get current angular velocity vector for body's rotation, expressed in the global frame."
                         "\n\n\n"
                         ":return: Current angular velocity vector for body's rotation, expressed in the global frame.\n\n")

                    .def("getCurrentAngularVelocityVectorInLocalFrame",
                         &tudat::simulation_setup::Body::getCurrentAngularVelocityVectorInLocalFrame,
                         "Get current angular velocity vector for body's rotation, expressed in the local frame."
                         "\n\n\n"
                         ":return: Current angular velocity vector for body's rotation, expressed in the local frame.\n\n")

                    .def("setEphemeris",
                         &tudat::simulation_setup::Body::setEphemeris,
                         (p::arg("bodyEphemeris")),
                         "Set the ephemeris of the body, which is used to represent the (a priori) "
                         "state history of the body."
                         "\n\n\n"
                         ":param bodyEphemeris: New ephemeris of the body.\n\n")

                    .def("setGravityFieldModel",
                         &tudat::simulation_setup::Body::setGravityFieldModel,
                         (p::arg("gravityFieldModel")),
                         "Set the gravity field of the body; input is also used to (re)set the mass of the "
                         "body."
                         "\n\n\n"
                         ":param gravityFieldModel: New gravity field of the body.\n\n")

                    .def("setAtmosphereModel",
                         &tudat::simulation_setup::Body::setAtmosphereModel,
                         (p::arg("atmosphereModel")),
                         "set the atmosphere model of the body."
                         "\n\n\n"
                         ":param atmosphereModel: Atmosphere model of the body.\n\n")

                    .def("setRotationalEphemeris",
                         &tudat::simulation_setup::Body::setRotationalEphemeris,
                         (p::arg("rotationalEphemeris")),
                         "Set the rotation model of the body."
                         "\n\n\n"
                         ":param rotationalEphemeris: Rotation model of the body.\n\n")

                    .def("setDependentOrientationCalculator",
                         &tudat::simulation_setup::Body::setDependentOrientationCalculator,
                         (p::arg("dependentOrientationCalculator")),
                         "Set a rotation model that is only valid during numerical propagation, as it depends on the full state"
                         " of the environment"
                         "\n\n\n"
                         ":param dependentOrientationCalculator: Object from which the orientation is computed.\n\n")

                    .def("setShapeModel",
                         &tudat::simulation_setup::Body::setShapeModel,
                         (p::arg("shapeModel")),
                         "Set the shape model of the body."
                         "\n\n\n"
                         ":param shapeModel: Shape model of the body.\n\n")
                    .def("setAerodynamicCoefficientInterface",
                         &tudat::simulation_setup::Body::setAerodynamicCoefficientInterface,
                         (p::arg("aerodynamicCoefficientInterface")),
                         "Set the aerodynamic coefficient interface of the body."
                         "\n\n\n"
                         ":param aerodynamicCoefficientInterface: Aerodynamic coefficient interface of the body.\n\n")

                    .def("setFlightConditions",
                         &tudat::simulation_setup::Body::setFlightConditions,
                         (p::arg("aerodynamicFlightConditions")),
                         "Set the body flight conditions, which calculates current aerodynamic angles, "
                         "altitude, etc."
                         "\n\n\n"
                         ":param aerodynamicFlightConditions: Body flight conditions.\n\n")

                    .def("setRadiationPressureInterface",
                         &tudat::simulation_setup::Body::setRadiationPressureInterface,
                         (p::arg("radiatingBody"),p::arg("radiationPressureInterface")),
                         "Set the radiation pressure interface of the body, for a single radiation source."
                         "\n\n\n"
                         ":param radiatingBody: Name of body that is the source of the radiation.\n"
                         ":param radiationPressureInterface: Radiation pressure interface of the body.\n\n")

                    .def("setGravityFieldVariationSet",
                         &tudat::simulation_setup::Body::setGravityFieldVariationSet,
                         (p::arg("gravityFieldVariationSet")),
                         "Set object containing all variations in the gravity field of this body."
                         "\n\n\n"
                         ":param gravityFieldVariationSet: Object containing all variations in the gravity field of this body.\n\n")

                    .def("getGravityFieldModel",
                         &tudat::simulation_setup::Body::getGravityFieldModel,
                         "Get the gravity field model of the body."
                         "\n\n\n"
                         ":return: Gravity field model.\n\n")

                    .def("getEphemeris",
                         &tudat::simulation_setup::Body::getEphemeris,
                         "Get the ephemeris of the body."
                         "\n\n\n"
                         ":return: Ephemeris of the body.\n\n")

                    .def("getAtmosphereModel",
                         &tudat::simulation_setup::Body::getAtmosphereModel,
                         "Get the atmosphere model of the body."
                         "\n\n\n"
                         ":return: Atmosphere model of the body.\n\n")

                    .def("getRotationalEphemeris",
                         &tudat::simulation_setup::Body::getRotationalEphemeris,
                         "Get the rotation model of the body."
                         "\n\n\n"
                         ":return: Rotation model of the body.\n\n")

                    .def("getDependentOrientationCalculator",
                         &tudat::simulation_setup::Body::getDependentOrientationCalculator,
                         "Get the model to compute the rotation of the body based on the current state of the environment"
                         " (model is only valid during propagation)."
                         "\n\n\n"
                         ":return: Model to compute the rotation of the body based on the current state of the environment.\n\n")

                    .def("getShapeModel",
                         &tudat::simulation_setup::Body::getShapeModel,
                         "Get the shape model of body."
                         "\n\n\n"
                         ":return: Shape model of body.\n\n")

                    .def("getAerodynamicCoefficientInterface",
                         &tudat::simulation_setup::Body::getAerodynamicCoefficientInterface,
                         "Get the aerodynamic coefficient model of body."
                         "\n\n\n"
                         ":return: Aerodynamic coefficient model of body.\n\n")

                    .def("getFlightConditions",
                         &tudat::simulation_setup::Body::getFlightConditions,
                         "Get the body flight conditions, which calculates current aerodynamic angles, "
                         " altitude, etc."
                         "\n\n\n"
                         ":return: Body flight conditions.\n\n")

                    .def("getRadiationPressureInterfaces",
                         &tudat::simulation_setup::Body::getRadiationPressureInterfaces
                         /* Existing c++ doc comment incorrectly copy-pasted from getShapeModel ones. */)

                    .def("getGravityFieldVariation",
                         &tudat::simulation_setup::Body::getGravityFieldVariation,
                         getGravityFieldVariation_overloads(
                         (p::arg("deformationType"), p::arg("identifier") = std::string("")),
                         "Retrieve a single object describing variation in the gravity field of this body."
                         "\n\n\n"
                         ":param deformationType: Type of gravity field variation.\n"
                         ":param identifier: Identifier of gravity field variation that is to be retrieved (empty by default; only required "
                         " if multiple variations of same type are present)\n"
                         ":return: Object describing requested variation in the gravity field of this body.\n\n"))

                    .def("getGravityFieldVariationSet",
                         &tudat::simulation_setup::Body::getGravityFieldVariationSet,
                         "Get object containing all variations in the gravity field of this body."
                         "\n\n\n"
                         ":return: Object containing all variations in the gravity field of this body.\n\n")

                    .def("getVehicleSystems",
                         &tudat::simulation_setup::Body::getVehicleSystems,
                         "Get container object with hardware systems present on/in body."
                         "\n\n\n"
                         ":return: Container object with hardware systems present on/in body.\n\n")

                    .def("setVehicleSystems",
                         &tudat::simulation_setup::Body::setVehicleSystems,
                         (p::arg("vehicleSystems")),
                         "Set container object with hardware systems present on/in body (typically only non-nullptr for a vehicle)."
                         "\n\n\n"
                         ":param vehicleSystems: Container object with hardware systems present on/in body.\n\n")

                    .def("setBodyMassFunction",
                         &tudat::simulation_setup::Body::setBodyMassFunction,
                         (p::arg("BodyMassFunction")),
                         "Set the function returning body mass as a function of time."
                         "\n\n\n"
                         ":param vehicleSystems: Function returning body mass as a function of time.\n\n")

                    .def("setConstantBodyMass",
                         &tudat::simulation_setup::Body::setConstantBodyMass,
                         (p::arg("bodyMass")),
                         "Set the body mass as being constant (i.e. time-independent)."
                         "\n\n\n"
                         ":param vehicleSystems: New constant body mass.\n\n")

                    .def("getBodyMassFunction",
                         &tudat::simulation_setup::Body::getBodyMassFunction,
                         "Get the function returning body mass as a function of time."
                         "\n\n\n"
                         ":return: Function returning body mass as a function of time.\n\n")

                    .def("updateMass",
                         &tudat::simulation_setup::Body::updateMass,
                         (p::arg("time")),
                         "Update the body mass to the current time, using the bodyMassFunction_ function."
                         "\n\n\n"
                         ":param time: Current time.\n\n")

                    .def("getBodyMass",
                         &tudat::simulation_setup::Body::getBodyMass,
                         "Get the current body mass."
                         "\n\n\n"
                         ":return: Current body mass.\n\n")

                    .def("getBodyInertiaTensor",
                         &tudat::simulation_setup::Body::getBodyInertiaTensor,
                         "Get the body moment-of-inertia tensor."
                         "\n\n\n"
                         ":return: Body moment-of-inertia tensor.\n\n")

                    .def("getScaledMeanMomentOfInertia",
                         &tudat::simulation_setup::Body::getScaledMeanMomentOfInertia,
                         "Get the body scaled mean moment of inertia."
                         "\n\n\n"
                         ":return: Body scaled mean moment of inertia.\n\n")

                    .def("setScaledMeanMomentOfInertia",
                         &tudat::simulation_setup::Body::setScaledMeanMomentOfInertia,
                         (p::arg("scaledMeanMomentOfInertia")),
                         "Reset body scaled mean moment of inertia, and update associated inertia tensor."
                         "\n\n\n"
                         ":param scaledMeanMomentOfInertia: New body scaled mean moment of inertia.\n\n")

                    .def("setBodyInertiaTensor",
                         &Body_setBodyInertiaTensor_overloadResolutionHelper_matrixAlone,
                         (p::arg("bodyInertiaTensor")),
                         "Reset the body moment-of-inertia tensor."
                         "\n\n\n"
                         ":param bodyInertiaTensor: Body moment-of-inertia tensor.\n\n")

                    .def("setBodyInertiaTensor",
                         &Body_setBodyInertiaTensor_overloadResolutionHelper_matrixWDouble,
                         (p::arg("bodyInertiaTensor"), p::arg("scaledMeanMomentOfInertia")),
                         "Reset the body moment-of-inertia tensor and scaled mean-moment of inertia."
                         "\n\n\n"
                         ":param bodyInertiaTensor: Body moment-of-inertia tensor."
                         ":param scaledMeanMomentOfInertia: New body scaled mean moment of inertia.\n\n")

                    .def("setBodyInertiaTensorFromGravityField",
                         &tudat::simulation_setup::Body::setBodyInertiaTensorFromGravityField,
                         (p::arg("scaledMeanMomentOfInertia")),
                         "Reset the body moment-of-inertia tensor from the gravity field, requires only a mean moment of inertia "
                         " (scaled by mass times reference radius squared). Other data are taken from this body's spherical harmonic gravity field."
                         "\n\n\n"
                         ":param scaledMeanMomentOfInertia: Mean moment of inertial, divided by (M*R^2), with M the mass of the body and R the "
                         " reference radius of the gravity field\n\n")

                    .def("setBodyInertiaTensorFromGravityFieldAndExistingMeanMoment",
                         &tudat::simulation_setup::Body::setBodyInertiaTensorFromGravityFieldAndExistingMeanMoment,
                         setBodyInertiaTensorFromGravityFieldAndExistingMeanMoment_overloads((p::arg("printWarningIfNotSet") = true),
                         "Reset the body moment-of-inertia tensor from existing gravity field and mean moment of inertia."
                         "\n\n\n"
                         ":param printWarningIfNotSet: Boolean to denote whether a warning is to be printed if scaled mean moment is not defined.\n\n"))

                    .def("addGroundStation",
                         &tudat::simulation_setup::Body::addGroundStation,
                         (p::arg("stationName"), p::arg("station")),
                         "Add a ground station to the body"
                         "\n\n\n"
                         ":param stationName: Name of ground station.\n"
                         ":param station: Ground station object that is to be set."
                         "\n\n")

                    .def("getGroundStation",
                         &tudat::simulation_setup::Body::getGroundStation,
                         (p::arg("stationName")),
                         "Get a ground station"
                         "\n\n\n"
                         ":param stationName: Name of ground station\n"
                         ":return: Ground station object that is retrieved."
                         "\n\n")

                    .def("getGroundStationMap",
                         &tudat::simulation_setup::Body::getGroundStationMap,
                         "Get full list of ground stations"
                         "\n\n\n"
                         ":return: Full list of ground stations."
                         "\n\n")

                    .def("updateConstantEphemerisDependentMemberQuantities",
                         &tudat::simulation_setup::Body::updateConstantEphemerisDependentMemberQuantities,
                         "Recompute the internal variables of member variables that depend on the ephemerides of this and other\n"
                         " bodies. This function is typically called after equations of motion have been computed and set in environment to\n"
                         " ensure full model consistency.")

                    .def("recomputeStateOnNextCall",
                         &tudat::simulation_setup::Body::recomputeStateOnNextCall,
                         "Reset the time to which the state was last updated using setStateFromEphemeris function to nan, thereby\n"
                         " signalling that it needs to be recomputed upon next call.")

                    .def("getIsBodyGlobalFrameOrigin",
                         &tudat::simulation_setup::Body::getIsBodyGlobalFrameOrigin,
                         "Retrieve variable denoting whether this body is the global frame origin\n\n"
                         ":return: Variable denoting whether this body is the global frame origin.")

                    .def("setIsBodyGlobalFrameOrigin",
                         &tudat::simulation_setup::Body::setIsBodyGlobalFrameOrigin,
                         (p::arg("bodyIsGlobalFrameOrigin")),
                         "Set variable denoting whether this body is the global frame origin\n"
                         "\n\n\n"
                         ":param bodyIsGlobalFrameOrigin: Variable denoting whether this body is the global frame origin."
                         "\n\n")

                    ;

            p::def("getGlobalFrameOrigin", &tudat::simulation_setup::getGlobalFrameOrigin, (p::arg("bodyMap")),
                    "Retrieve the common global translational state origin of the environment. This function throws an exception "
                    " if multiple bodies are found as the frame origin\n\n\n"
                    ":param bodyMap: List of body objects.\n"
                    ":return: Global translational state origin of the environment");

            p::def("getBodyAccelerationInBaseFramefromNumericalDifferentiation", &tudat::simulation_setup::getBodyAccelerationInBaseFramefromNumericalDifferentiation<double,double>,
                    (p::arg("bodyWithAcceleration"), p::arg("nominalEvalutationTime")),
                   "Compute the acceleration of a body, using its ephemeris and 8th order finite difference and 100 s time step.\n\n\n"
                   ":param bodyWithAcceleration: Body for which acceleration is to be computed\n"
                   ":param nominalEvalutationTime: Time at which acceleration is to be evaluated.");

        }
    }
}