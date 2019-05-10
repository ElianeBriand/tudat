/*    Copyright (c) 2010-2019, Delft University of Technology
 *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 */

#include "gravityFieldModel.h"


#include <boost/python.hpp>
#include <boost/numpy.hpp>


#include <Eigen/Eigen>
#include <iostream>

#include "Tudat/Basics/basicTypedefs.h"

#include "Tudat/Astrodynamics/Gravitation/gravityFieldModel.h"


namespace p = boost::python;
namespace np = boost::numpy;


namespace tudat {
    namespace PyBindings_internal {

        namespace {
            std::shared_ptr<tudat::gravitation::GravityFieldModel>
            GravityFieldModel_constructorWrapper(double gravitationalParameter) {
                auto ret = std::make_shared<tudat::gravitation::GravityFieldModel>(gravitationalParameter);
                return ret;
            }
        }

        void PyExport_gravityFieldModel() {
            p::class_<tudat::gravitation::GravityFieldModel, std::shared_ptr<tudat::gravitation::GravityFieldModel>>(
                    "GravityFieldModel",
                    p::no_init)
                    .def("__init__", p::make_constructor(&GravityFieldModel_constructorWrapper,
                                                         p::default_call_policies(),
                                                         (p::arg("gravitationalParameter"))),
                                                         "Default constructor.\n\n"
                                                         ":param gravitationalParameter: Gravitational parameter associated with gravity field")

                    .def("resetGravitationalParameter",
                         &tudat::gravitation::GravityFieldModel::resetGravitationalParameter,
                         (p::arg("gravitationalParameter")),
                         "Define the gravitational parameter in meter^3 per second^2.\n\n"
                         ":param gravitationalParameter: New gravitational parameter associated with gravity field.")

                    .def("getGravitationalParameter",
                         &tudat::gravitation::GravityFieldModel::getGravitationalParameter,
                         ":return: Gravitational parameter in meter^3 per second^2.")

                    .def("getGravitationalPotential",
                         &tudat::gravitation::GravityFieldModel::getGravitationalPotential,
                         (p::arg("bodyFixedPosition")),
                         "Return the gravitational potential at given body-fixed position.\n"
                         "\n\n\n"
                         ":param bodyFixedPosition: Position at which the gravitational potential is to be evaluated."
                         ":return Gravitational: potential.")

                    .def("getGradientOfPotential",
                         &tudat::gravitation::GravityFieldModel::getGradientOfPotential,
                         (p::arg("bodyFixedPosition")),
                         "Returns the gradient of the potential for the gravity field selected.\n"
                         "\n\n\n"
                         ":param bodyFixedPosition: Position at which the gradient of potential is to be determined."
                         ":return: Gradient of potential.");

            p::enum_<tudat::gravitation::BodiesWithPredefinedCentralGravityFields>("PredefinedCentralGravityFields")
                    .value("sun",
                           tudat::gravitation::BodiesWithPredefinedCentralGravityFields::sun)
                    .value("mercury",
                           tudat::gravitation::BodiesWithPredefinedCentralGravityFields::mercury)
                    .value("venus",
                           tudat::gravitation::BodiesWithPredefinedCentralGravityFields::venus)
                    .value("earth",
                           tudat::gravitation::BodiesWithPredefinedCentralGravityFields::earth)
                    .value("moon",
                           tudat::gravitation::BodiesWithPredefinedCentralGravityFields::moon)
                    .value("mars",
                           tudat::gravitation::BodiesWithPredefinedCentralGravityFields::mars)
                    .value("jupiter",
                           tudat::gravitation::BodiesWithPredefinedCentralGravityFields::jupiter)
                    .value("saturn",
                           tudat::gravitation::BodiesWithPredefinedCentralGravityFields::saturn)
                    .value("uranus",
                           tudat::gravitation::BodiesWithPredefinedCentralGravityFields::uranus)
                    .value("neptune",
                           tudat::gravitation::BodiesWithPredefinedCentralGravityFields::neptune)
                    ;

            p::def("getPredefinedCentralGravityField", &tudat::gravitation::getPredefinedCentralGravityField,
                   (p::arg("bodyWithPredefinedCentralGravityField")),
                   "Function to create a central gravity field model of one of the planets, moon or sun.\n\n\n"
                   ":param bodyWithPredefinedCentralGravityField: Identifier determining for which body a "
                   " gravity field is to be created.\n"
                   ":return: Central gravity field model of requested body.");

        }

    }
}