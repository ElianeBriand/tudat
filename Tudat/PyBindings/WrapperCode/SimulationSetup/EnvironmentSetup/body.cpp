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


        }


        void PyExport_body() {

            p::class_<tudat::simulation_setup::NamedBodyMap>("NamedBodyMap")
                    .def("__len__", &tudat::simulation_setup::NamedBodyMap::size)
                    .def("clear", &tudat::simulation_setup::NamedBodyMap::clear)
                    .def("__getitem__", &MinimalMapIndexing<tudat::simulation_setup::NamedBodyMap>::get,
                         p::return_value_policy<p::copy_non_const_reference>())
                    .def("__setitem__", &MinimalMapIndexing<tudat::simulation_setup::NamedBodyMap>::set,
                         p::with_custodian_and_ward<1,2>()) // to let container keep value
                    .def("__delitem__", &MinimalMapIndexing<tudat::simulation_setup::NamedBodyMap>::del)
                    ;

            p::class_<tudat::simulation_setup::Body, std::shared_ptr<tudat::simulation_setup::Body>, boost::noncopyable>(
                    "Body", p::no_init)
                    .def("__init__", p::make_constructor(&Body_constructorWrapper,
                                                         p::default_call_policies(),
                                                         (p::arg("state"))))
                    .def("__init__", p::make_constructor(&Body_constructorWrapper_noArgs,
                                                         p::default_call_policies()));

        }
    }
}