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

#include "DataStructures/eigenWrapper.h"
#include "Astodynamics/BasicAstrodynamics/unitConversions.h"
#include "Astodynamics/BasicAstrodynamics/physicalConstants.h"



BOOST_PYTHON_MODULE (Tudat) {

    //Py_Initialize();
    np::initialize();

    tudat::PyBindings_internal::PyExport_EigenDatastructures();
    tudat::PyBindings_internal::PyExport_unitConversions();
    tudat::PyBindings_internal::PyExport_physicalConstants();

}
