/*    Copyright (c) 2010-2019, Delft University of Technology
 *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 */

#include "simulationPythonInterfaceInternals.h"

#include <boost/python.hpp>
#include <boost/numpy.hpp>


#include "Tudat/Basics/basicTypedefs.h"

#include <Tudat/SimulationSetup/tudatSimulationHeader.h>

namespace p = boost::python;
namespace np = boost::numpy;

namespace {
    class dummyClassA_simulationInternal {

    };
}

namespace tudat {
    namespace PyBindings_internal {

        BOOST_PYTHON_FUNCTION_OVERLOADS(loadStandardSpiceKernels_overloads,
                                        tudat::spice_interface::loadStandardSpiceKernels, 0, 1);

        void PyExport_simulationPythonInterfaceInternals() {

            p::scope engineScope
                    = p::class_<dummyClassA_simulationInternal>("SimulationInternals");

            p::def("loadStandardSpiceKernels", &tudat::spice_interface::loadStandardSpiceKernels,
                   loadStandardSpiceKernels_overloads());
        }

    }

}