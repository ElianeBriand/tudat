/*    Copyright (c) 2010-2019, Delft University of Technology
 *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 */

#include "dataStructuresUtility.h"


#include <boost/python.hpp>
#include <boost/numpy.hpp>


#include <Eigen/Eigen>
#include <iostream>

#include "Tudat/Astrodynamics/BasicAstrodynamics/attitudeElementConversions.h"
#include "Tudat/Basics/basicTypedefs.h"


namespace p = boost::python;
namespace np = boost::numpy;


void tudat::PyBindings_internal::PyExport_DatastructuresUtility() {

    p::def("convertQuaternionsToModifiedRodriguesParameterElements",
           &tudat::orbital_element_conversions::convertQuaternionsToModifiedRodriguesParameterElements,
           (p::arg("quaternionElements")),
           "Convert quaternions to modified Rodrigues parameters. The conversion is slightly different for modified Rodrigues parameters (MRP)\n"
           "than for shadow modified Rodrigues parameters (SMRP). This difference is embodied by conversionSign.\n\n"
           ":param quaternionElements: Vector of quaternion elements.\n"
           ":return: convertedModifiedRodriguesParameterElements Vector of (shadow) modified Rodrigues parameter elements."
    );

    p::def("convertModifiedRodriguesParametersToQuaternionElements",
           &tudat::orbital_element_conversions::convertModifiedRodriguesParametersToQuaternionElements,
           (p::arg("modifiedRodriguesParameterElements")),
           "Convert modified Rodrigues parameters to quaternions. The conversion is slightly different for modified Rodrigues parameters (MRP)\n"
           "than for shadow modified Rodrigues parameters (SMRP). This difference is embodied by conversionSign.\n\n"
           ":param modifiedRodriguesParameterElements: Vector of (shadow) modified Rodrigues parameters elements.\n"
           ":return: convertedQuaternionElements Vector of quaternion elements."
    );

    p::def("convertQuaternionsToExponentialMapElements",
           &tudat::orbital_element_conversions::convertQuaternionsToExponentialMapElements,
           (p::arg("quaternionElements")),
           "Convert quaternions to exponential map. The conversion is the same for both exponential map (EM) and shadow\n"
           "exponential map (SEM).\n\n"
           ":param quaternionElements: Vector of quaternion elements.\n"
           ":return: convertedExponentialMapElements Vector of (shadow) exponential map elements."
    );


    p::def("convertExponentialMapToQuaternionElements",
           &tudat::orbital_element_conversions::convertExponentialMapToQuaternionElements,
           (p::arg("exponentialMapElements")),
           "Convert exponential map to quaternions. The conversion is the same for both exponential map (EM) and shadow\n"
           "exponential map (SEM).\n\n"
           ":param exponentialMapElements: Vector of (shadow) exponential map elements.\n"
           ":return: convertedQuaternionElements Vector of quaternion elements."
    );

}