/*    Copyright (c) 2010-2019, Delft University of Technology
 *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 */

#include "centralGravityModel.h"

#include <exception>


#include <boost/python.hpp>
#include <boost/numpy.hpp>
#include <boost/iterator/iterator_facade.hpp>


#include <Eigen/Eigen>
#include <iostream>

#include "Tudat/Basics/basicTypedefs.h"

#include "Tudat/Astrodynamics/Gravitation/centralGravityModel.h"


namespace p = boost::python;
namespace np = boost::numpy;

namespace {
    class dummyClassA_centralGravityModel {
    };
}


namespace tudat {
    namespace PyBindings_internal {

        void PyExport_centralGravityModel() {

            p::scope
                    engineScope = p::class_<dummyClassA_centralGravityModel>("CentralGravity");


            p::def("computeGravitationalAcceleration", static_cast<
                           Eigen::Vector3d(*)(const double, const Eigen::Vector3d &, const double, const Eigen::Vector3d &)
                           >(&tudat::gravitation::computeGravitationalAcceleration),
                   (p::arg("universalGravitationalConstant"), p::arg("positionOfBodySubjectToAcceleration"),
                           p::arg("massOfBodyExertingAcceleration"), p::arg("positionOfBodyExertingAcceleration")),
                   "Computes gravitational acceleration experienced by body1, due to its interaction with body2.\n\n\n"
                   "The basis for this gravitational acceleration is that body2 is a point mass,\n"
                   "generating acceleration due to Newton's gravitational force: \n\n"
                   ".. math::\n"
                   "     \\bar{a}_{gravity} = -\\frac{G * m_{2}}{r_{12}^{3}} * \\bar{r}_{12}\n"
                   "\n\n"
                   "where $G$ is the universal gravitational constant, $m_{2}$ is the mass of body2,\n"
                   "and $\\bar{r}_{12}$ is the relative position vector from body1 to body 2, with respect to an\n"
                   "inertial (barycentric) reference frame.\n\n"
                   ":param universalGravitationalConstant: Universal gravitational constant [m^3 kg^-1 s^-2].\n"
                   ":param positionOfBodySubjectToAcceleration: Position vector of body subject to acceleration (body1) [m].\n"
                   ":param massOfBodyExertingAcceleration: Mass of body exerting acceleration (body2) [kg].\n"
                   ":param positionOfBodyExertingAcceleration: Position vector of body exerting acceleration (body2) [m].\n"
                   ":return: Gravitational acceleration exerted on body1 [m s^-2]."
            );

            p::def("computeGravitationalAcceleration", static_cast<
                           Eigen::Vector3d(*)(const Eigen::Vector3d &, const double, const Eigen::Vector3d &)
                           >(&tudat::gravitation::computeGravitationalAcceleration),
                   (p::arg("positionOfBodySubjectToAcceleration"), p::arg(
                           "gravitationalParameterOfBodyExertingAcceleration"),
                           p::arg("positionOfBodyExertingAcceleration")),
                   "Computes gravitational acceleration experienced by body1, due to its interaction with body2.\n\n\n"
                   "The basis for this gravitational acceleration is that body2 is a point mass, generating "
                   "acceleration due to Newton's gravitational force:\n\n"
                   ".. math::\n"
                   "    \\bar{a}_{gravity} = -\\frac{\\mu_{2}}{r_{12}^{3}} * \\bar{r}_{12}\n"
                   "\n\n"
                   "where $\\mu_{2}$ is the gravitational parameter of the body exerting acceleration, "
                   "and $\\bar{r}_{12}$ is the relative position vector from body1 to body 2, with respect to an "
                   "inertial (barycentric) reference frame.\n\n"

                   ":param positionOfBodySubjectToAcceleration: Position vector of body subject to acceleration (body1) [m].\n"
                   ":param gravitationalParameterOfBodyExertingAcceleration: Gravitational parameter of body exerting acceleration (body2) [m^3 s^-2].\n"
                   ":param positionOfBodyExertingAcceleration: Position vector of body exerting acceleration (body2) [m].\n"
                   ":return: Gravitational acceleration exerted on body1 [m s^-2]."
            );

            p::def("computeGravitationalForce", static_cast<
                           Eigen::Vector3d(*)(const double, const double, const Eigen::Vector3d &, const double,
                                              const Eigen::Vector3d &)
                           >(&tudat::gravitation::computeGravitationalForce),
                   (p::arg("universalGravitationalParameter"), p::arg("massOfBodySubjectToForce"), p::arg(
                           "positionOfBodySubjectToForce"), p::arg("massOfBodyExertingForce"),
                           p::arg("positionOfBodyExertingForce")),
                   "Computes gravitational force experienced by body1, due to its interaction with body2.\n\n\n"
                   "The basis for this gravitational force is that both body1 and body2 are point masses, "
                   "generating Newton's gravitational force:\n\n"
                   ".. math::\n"
                   "    \\bar{F}_{gravity} = -\\frac{G * m_{1} * m_{2}}{r_{12}^{3}} * \\bar{r}_{12}\n"
                   "\n\n"
                   "where $G$ is the universal gravitational constant, $m_{1}$ is the mass of body1,\n"
                   "$m_{2}$ is the mass of body2, and $\\bar{r}_{12}$ is the relative position vector\n"
                   "from body1 to body 2, with respect to an inertial (barycentric) reference frame.\n\n"

                   ":param universalGravitationalParameter: Universal gravitational constant [m^3 kg^-1 s^-2].\n"
                   ":param massOfBodySubjectToForce: Mass of body subject to force (body1) [kg].\n"
                   ":param positionOfBodySubjectToForce: Position vector of body subject to force (body1) [m].\n"
                   ":param massOfBodyExertingForce: Mass of body exerting force (body2) [kg].\n"
                   ":param positionOfBodyExertingForce: Position vector of body exerting force (body2) [m].\n"
                   ":return: Gravitational force exerted on body1 [N]."
            );

            p::def("computeGravitationalForce", static_cast<
                           Eigen::Vector3d(*)(const double, const Eigen::Vector3d &, const double, const Eigen::Vector3d &)
                           >(&tudat::gravitation::computeGravitationalForce),
                   (p::arg("massOfBodySubjectToForce"), p::arg("positionOfBodySubjectToForce"), p::arg(
                           "massOfBodyExertingForce"),
                           p::arg("positionOfBodyExertingForce")),
                   "Computes gravitational force experienced by body1, due to its interaction with body2.\n\n\n"
                   "The basis for this gravitational force is that both body1 and body2 are point masses, "
                   "generating Newton's gravitational force:\n\n"
                   ".. math::\n"
                   "    \\bar{F}_{gravity} = -\\frac{G * m_{1} * m_{2}}{r_{12}^{3}} * \\bar{r}_{12}\n"
                   "\n\n"
                   "where $G$ is the universal gravitational constant, $m_{1}$ is the mass of body1,\n"
                   "$m_{2}$ is the mass of body2, and $\\bar{r}_{12}$ is the relative position vector\n"
                   "from body1 to body 2, with respect to an inertial (barycentric) reference frame.\n\n"

                   ":param massOfBodySubjectToForce: Mass of body subject to force (body1) [kg].\n"
                   ":param positionOfBodySubjectToForce: Position vector of body subject to force (body1) [m].\n"
                   ":param massOfBodyExertingForce: Mass of body exerting force (body2) [kg].\n"
                   ":param positionOfBodyExertingForce: Position vector of body exerting force (body2) [m].\n"
                   ":return: Gravitational force exerted on body1 [N]."
            );

            p::class_<std::function<Eigen::Vector3d() >>("StateFunctionHolder");


            // The templated nature of the constructor is somewhat problematic
            // TODO : Export a fully specialized class based on Eigen::Vector3d as state vector

//            p::class_<tudat::gravitation::CentralGravitationalAccelerationModel3d,
//                    p::bases<tudat::basic_astrodynamics::AccelerationModel<Eigen::Vector3d>,
//                            tudat::gravitation::SphericalHarmonicsGravitationalAccelerationModelBase<Eigen::Vector3d >>,
//                    std::shared_ptr<tudat::gravitation::CentralGravitationalAccelerationModel3d >>(
//                    "CentralGravitationalAccelerationModel3d",p::no_init)
////                    .def(p::init<std::function< Eigen::Vector3d( ) >,double, std::function< Eigen::Vector3d( ) >, bool>())
//                    ;


        }

    }
}