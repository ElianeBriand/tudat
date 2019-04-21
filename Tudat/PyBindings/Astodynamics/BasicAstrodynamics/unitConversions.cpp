/*    Copyright (c) 2010-2019, Delft University of Technology
 *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 */
#include "unitConversions.h"

#include <boost/python.hpp>
#include <boost/numpy.hpp>

#include "Tudat/Astrodynamics/BasicAstrodynamics/unitConversions.h"

namespace p = boost::python;
namespace np = boost::numpy;

namespace {
    class dummyClassA_unitConversions {
        int i;
    };
}

void tudat::PyBindings_internal::PyExport_unitConversions(){

    {
        p::scope engineScope
                = p::class_<dummyClassA_unitConversions>("units");

        // Note: Python builtin "float" is actually a double : specializing for this case
        p::def("convertRadiansToDegrees", &tudat::unit_conversions::convertRadiansToDegrees<double>);
        p::def("convertDegreesToRadians", &tudat::unit_conversions::convertDegreesToRadians<double>);

        p::def("convertDegreesToArcminutes", &tudat::unit_conversions::convertDegreesToArcminutes<double>);

        p::def("convertArcSecondsToRadians", &tudat::unit_conversions::convertArcSecondsToRadians<double>);
        p::def("convertRadiansToArcSeconds", &tudat::unit_conversions::convertRadiansToArcSeconds<double>);

        p::def("convertArcminutesToArcseconds", &tudat::unit_conversions::convertArcminutesToArcseconds<double>);

        p::def("convertMetersToKilometers", &tudat::unit_conversions::convertMetersToKilometers<double>);
        p::def("convertKilometersToMeters", &tudat::unit_conversions::convertKilometersToMeters<double>);

        p::def("convertMetersToAstronomicalUnits", &tudat::unit_conversions::convertMetersToAstronomicalUnits<double>);
        p::def("convertAstronomicalUnitsToMeters", &tudat::unit_conversions::convertAstronomicalUnitsToMeters<double>);

        p::def("convertSecondsToMinutes", &tudat::unit_conversions::convertSecondsToMinutes<double>);
        p::def("convertMinutesToSeconds", &tudat::unit_conversions::convertMinutesToSeconds<double>);

        p::def("convertSecondsToHours", &tudat::unit_conversions::convertSecondsToHours<double>);
        p::def("convertHoursToSeconds", &tudat::unit_conversions::convertHoursToSeconds<double>);

        p::def("convertSecondsToJulianDays", &tudat::unit_conversions::convertSecondsToJulianDays<double>);
        p::def("convertJulianDaysToSeconds", &tudat::unit_conversions::convertJulianDaysToSeconds<double>);

        p::def("convertSecondsToSiderealDays", &tudat::unit_conversions::convertSecondsToSiderealDays<double>);
        p::def("convertSiderealDaysToSeconds", &tudat::unit_conversions::convertSiderealDaysToSeconds<double>);

        p::def("convertJulianDaysToJulianYears", &tudat::unit_conversions::convertJulianDaysToJulianYears<double>);
        p::def("convertJulianYearsToJulianDays", &tudat::unit_conversions::convertJulianYearsToJulianDays<double>);

        p::def("convertRankineToKelvin", &tudat::unit_conversions::convertRankineToKelvin<double>);

        p::def("convertFeetToMeter", &tudat::unit_conversions::convertFeetToMeter<double>);

        p::def("convertPoundPerSquareFeetToPascal", &tudat::unit_conversions::convertPoundPerSquareFeetToPascal<double>);

    }


}

