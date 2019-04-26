/*    Copyright (c) 2010-2019, Delft University of Technology
 *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 */

#include "physicalConstants.h"
#include <boost/python.hpp>
#include <boost/numpy.hpp>

#include "Tudat/Astrodynamics/BasicAstrodynamics/physicalConstants.h"

namespace p = boost::python;
namespace np = boost::numpy;

namespace {
    class dummyClassA_physicalConstants {
    };
}

void tudat::PyBindings_internal::PyExport_physicalConstants() {
    {
        p::scope engineScope
                = p::class_<dummyClassA_physicalConstants>("constants")
                        // See physicalConstants.h for the source of the constants
                        // Note: PEP8 guide recommend constant being all caps in python too
                        // Note: Unfortunately, it is not possible to add docstring to variable in Python (only classes and functions)
                        // Note: Annotate the units if they are SI ? or implicitly SI if not said ?
                        // Note: Python has no native "long double"
                        // Note: Accidentally defining the same variable with the same name produces almost silent bugs
                        //       as the python module only report SystemError: initialization of Tudat raised unreported exception
                        //       and not what variable/function triggered it
                        .def_readonly("SEA_LEVEL_GRAVITATIONAL_ACCELERATION",
                                      &tudat::physical_constants::SEA_LEVEL_GRAVITATIONAL_ACCELERATION,
                                      " Standard gravitational acceleration at sea-level.")
                        .def_readonly("JULIAN_DAY_IN_SECONDS",
                                &tudat::physical_constants::JULIAN_DAY,
                                "Julian day in seconds (NASA, 2012).")
                        .def_readonly("JULIAN_YEAR_IN_DAYS",
                                &tudat::physical_constants::JULIAN_YEAR_IN_DAYS,
                                "Julian year in Julian days (NASA, 2012)")
                        .def_readonly("JULIAN_YEAR_IN_SECONDS",
                                &tudat::physical_constants::JULIAN_YEAR,
                                "Julian year in seconds. Result of JULIAN_YEAR_IN_DAYS * JULIAN_DAY.")
                        .def_readonly("SIDEREAL_DAY_IN_SECONDS",
                                &tudat::physical_constants::SIDEREAL_DAY,
                                "Sidereal day in seconds (NASA, 2012).")
                        .def_readonly("SIDEREAL_YEAR_IN_DAYS",
                                &tudat::physical_constants::SIDEREAL_YEAR_IN_DAYS,
                                "Sidereal year in Julian days in quasar reference frame (NASA, 2012).")
                        .def_readonly("SIDEREAL_YEAR_IN_SECONDS",
                                &tudat::physical_constants::SIDEREAL_YEAR,
                                "Sidereal year in seconds in quasar reference frame. Result of SIDEREAL_YEAR_IN_DAYS * JULIAN_DAY.")
                        .def_readonly("SPEED_OF_LIGHT",
                                &tudat::physical_constants::SPEED_OF_LIGHT,
                                "Speed of light in meters per second (Standish, 1995).")
                        .def_readonly("GRAVITATIONAL_CONSTANT",
                                &tudat::physical_constants::GRAVITATIONAL_CONSTANT,
                                "Gravitational constant in meter^3 per kilogram per second^2, (Standish, 1995).")
                        .def_readonly("ASTRONOMICAL_UNIT",
                                &tudat::physical_constants::ASTRONOMICAL_UNIT,
                                "Astronomical Unit in meters (Standish, 1998).")
                        .def_readonly("SPECIFIC_GAS_CONSTANT_AIR",
                                      &tudat::physical_constants::SPECIFIC_GAS_CONSTANT_AIR,
                                      "The specific gas constant of air in J per kg Kelvin (J/(kg K)) (Anderson, 2006).")
                        .def_readonly("MOLAR_GAS_CONSTANT",
                                &tudat::physical_constants::MOLAR_GAS_CONSTANT,
                                "The molar gas constant in J per mole Kelvin (J/(mol K))")
                        .def_readonly("AVOGADRO_CONSTANT",
                                &tudat::physical_constants::AVOGADRO_CONSTANT,
                                "Avogadro's number in unity per mole (1/mol).")
                        .def_readonly("PLANCK_CONSTANT",
                                &tudat::physical_constants::PLANCK_CONSTANT,
                                "Planck's constant in m^{2} kg/s, (NIST, 2013).")
                        .def_readonly("BOLTZMANN_CONSTANT",
                                &tudat::physical_constants::BOLTZMANN_CONSTANT,
                                "The Boltzmann constant (gas constant per particle) in  m^{2} kg / ( s^{2} K ), (NIST, 2013).")
                        .def_readonly("STEFAN_BOLTZMANN_CONSTANT",
                                      &tudat::physical_constants::STEFAN_BOLTZMANN_CONSTANT,
                                      "Stefan-Boltzmann constant, used for calculating black body radiation intensity, (Wolfram, 2013)"
                                      " * in J / (s m^{2} K{4} )")
                        .def_readonly("INVERSE_SQUARE_SPEED_OF_LIGHT",
                                      &tudat::physical_constants::INVERSE_SQUARE_SPEED_OF_LIGHT,
                                      "Precomputed inverse-square of speed of light.")
                        .def_readonly("INVERSE_CUBIC_SPEED_OF_LIGHT",
                                      &tudat::physical_constants::INVERSE_CUBIC_SPEED_OF_LIGHT,
                                      "Precomputed inverse 3rd power of speed of light.")
                        .def_readonly("INVERSE_QUARTIC_SPEED_OF_LIGHT",
                                      &tudat::physical_constants::INVERSE_QUARTIC_SPEED_OF_LIGHT,
                                      "Precomputed inverse 4th power of speed of light.")
                        .def_readonly("INVERSE_QUINTIC_SPEED_OF_LIGHT",
                                      &tudat::physical_constants::INVERSE_QUINTIC_SPEED_OF_LIGHT,
                                      "Precomputed inverse 5th power of speed of light.")
                        .def_readonly("VACUUM_PERMEABILITY",
                                &tudat::physical_constants::VACUUM_PERMEABILITY,
                                "Permeability of vacuum.")
                        .def_readonly("VACUUM_PERMITTIVITY",
                                &tudat::physical_constants::VACUUM_PERMITTIVITY,
                                "Permittivity of vacuum.")
                        .def_readonly("LG_TIME_RATE_TERM",
                                &tudat::physical_constants::LG_TIME_RATE_TERM,
                                "Relative time rate difference between TCG and TT time scales.")
                        .def_readonly("LB_TIME_RATE_TERM",
                                &tudat::physical_constants::LB_TIME_RATE_TERM,
                                "Relative time rate difference between TCB and TDB time scales.");

    }
}