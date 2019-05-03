/*    Copyright (c) 2010-2019, Delft University of Technology
 *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 */

#include <boost/python.hpp>
#include <boost/numpy.hpp>

namespace p = boost::python;
namespace np = boost::numpy;

#include "WrapperCode/DataStructures/eigenWrapper.h"
#include "WrapperCode/DataStructures/dataStructuresUtility.h"

#include "WrapperCode/Mathematics/rootFinder.h"

#include "WrapperCode/Astrodynamics/BasicAstrodynamics/unitConversions.h"
#include "WrapperCode/Astrodynamics/BasicAstrodynamics/constants.h"
#include "WrapperCode/Astrodynamics/BasicAstrodynamics/astrodynamicsFunctions.h"
#include "WrapperCode/Astrodynamics/BasicAstrodynamics/clohessyWiltshirePropagator.h"
#include "WrapperCode/Astrodynamics/BasicAstrodynamics/meanToEccentricAnomalies.h"

#include "WrapperCode/Gravitation/centralGravityModel.h"

#include "WrapperCode/SimulationSetup/simulationPythonInterfaceInternals.h"
#include "WrapperCode/SimulationSetup/EnvironmentSetup/createBodies.h"
#include "WrapperCode/SimulationSetup/EnvironmentSetup/body.h"

#include "Tudat/Basics/basicTypedefs.h"


BOOST_PYTHON_MODULE (Tudat) {

    //Py_Initialize();
    np::initialize();


    tudat::PyBindings_internal::PyExport_EigenDatastructures();
    tudat::PyBindings_internal::PyExport_DatastructuresUtility();

    tudat::PyBindings_internal::PyExport_rootFinder();

    tudat::PyBindings_internal::PyExport_unitConversions();
    tudat::PyBindings_internal::PyExport_constants();
    tudat::PyBindings_internal::PyExport_astrodynamicsFunctions();
    tudat::PyBindings_internal::PyExport_clohessyWiltshirePropagator();
    tudat::PyBindings_internal::PyExport_meanToEccentricAnomalies();

    tudat::PyBindings_internal::PyExport_centralGravityModel();

    // Simulation
    tudat::PyBindings_internal::PyExport_simulationPythonInterfaceInternals();
    tudat::PyBindings_internal::PyExport_body();
    tudat::PyBindings_internal::PyExport_createBodies();
}
