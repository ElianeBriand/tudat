/*    Copyright (c) 2010-2019, Delft University of Technology
 *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 */

#include "astrodynamicsFunctions.h"
#include <boost/python.hpp>
#include <boost/numpy.hpp>

#include "Tudat/Astrodynamics/BasicAstrodynamics/astrodynamicsFunctions.h"
#include "Tudat/Basics/basicTypedefs.h"


namespace p = boost::python;
namespace np = boost::numpy;

namespace {
    class dummyClassA_astrodynamicsFunctions {
    };
}


void tudat::PyBindings_internal::PyExport_astrodynamicsFunctions() {

    {
        p::scope
        engineScope   = p::class_<dummyClassA_astrodynamicsFunctions>("astrodynamics");


        p::def("computeKeplerOrbitalPeriod", &tudat::basic_astrodynamics::computeKeplerOrbitalPeriod,
                (p::arg("semiMajorAxis"), p::arg("gravitationalParameterOfCentralBody"),
                                                                        p::arg("massOfOrbitingBody") = 0.0),
                "Computes the two-body orbital period of an orbiting body that follows a closed conic section\n"
                "(circle or ellipse Kepler orbit).\n\n The mass of the orbiting body is set to that of a test\n"
                "particle by default.\n\n"
                ":param semiMajorAxis: Semi-major axis of Kepler orbit (circle or ellipse).\n"
                ":param gravitationalParameterOfCentralBody: Gravitational parameter of central body.\n"
                ":param massOfOrbitingBody: Mass of orbiting body.\n"
                ":return: Two-body orbital period."
        );

        // Note : It is necessary to explicitly cast to function pointer when dealing with overloaded functions
        // (to allow template argument deduction p::def<typename F>(char* name, F fn ...) )
        p::def("computeKeplerRadialDistance", static_cast<double (*)(const double, const double,
                                                                     const double)>(&tudat::basic_astrodynamics::computeKeplerRadialDistance),
               (p::arg("semiMajorAxis"), p::arg("eccentricity"), p::arg("trueAnomaly")),
               "Compute two-body radial distance.\n\n"
               ":param semiMajorAxis: Semi-major axis of Kepler orbit (circle or ellipse).\n"
               ":param eccentricity: Eccentricity of Kepler orbit (circle or ellipse).\n"
               ":param trueAnomaly: True anomaly of Kepler orbit (circle or ellipse).\n"
               ":return: Two-body radial distance at specified true anomaly."
        );

        p::def("computeKeplerRadialDistance",
               static_cast<double (*)(
                       const Eigen::Vector6d &)>(&tudat::basic_astrodynamics::computeKeplerRadialDistance),
               (p::arg("keplerianElements")),
               "Compute two-body radial distance.\n\n"
               ":param keplerianElements: Vector denoting the Keplerian elements (circle or ellipse).\n"
               ":return: Two-body radial distance at specified true anomaly."
        );


        p::def("computeKeplerOrbitalVelocity",
               static_cast<double (*)(const double, const double, const double, const double, const double) >
               (&tudat::basic_astrodynamics::computeKeplerOrbitalVelocity),
               (p::arg("semiMajorAxis"),
                       p::arg("eccentricity"),
                       p::arg("trueAnomaly"),
                       p::arg("gravitationalParameterOfCentralBody"),
                       p::arg("massOfOrbitingBody") = 0.0),
               "Compute two-body orbital velocity with vis-viva equation.\n\n"
               ":param semiMajorAxis: Semi-major axis of Kepler orbit (circle or ellipse).\n"
               ":param eccentricity: Eccentricity of Kepler orbit (circle or ellipse).\n"
               ":param trueAnomaly: True anomaly of Kepler orbit (circle or ellipse).\n"
               ":param gravitationalParameterOfCentralBody: Gravitational parameter of central body.\n"
               ":param massOfOrbitingBody: Mass of orbiting body.\n"
               ":return: Two-body orbital velocity at current conditions."
        );

        p::def("computeKeplerOrbitalVelocity", static_cast<double (*)(const Eigen::Vector6d &, const double,
                                                                      const double)>(&tudat::basic_astrodynamics::computeKeplerOrbitalVelocity),
               (p::arg("keplerianElements"), p::arg("gravitationalParameterOfCentralBody"), p::arg(
                       "massOfOrbitingBody") = 0.0),
               "Compute two-body orbital velocity with vis-viva equation.\n\n"
               ":param keplerianElements: Vector denoting the Keplerian elements (circle or ellipse).\n"
               ":param gravitationalParameterOfCentralBody: Gravitational parameter of central body.\n"
               ":param massOfOrbitingBody: Mass of orbiting body.\n"
               ":return: Two-body orbital velocity at current conditions."
        );

        p::def("computeKeplerAngularMomentum", static_cast<double (*)(const double, const double, const double,
                                                                      const double)>(&tudat::basic_astrodynamics::computeKeplerAngularMomentum),
               (p::arg("semiMajorAxis"),
                       p::arg("eccentricity"),
                       p::arg("gravitationalParameterOfCentralBody"),
                       p::arg("massOfOrbitingBody") = 0.0),
               "Computes the angular momentum of an orbiting body that follows a conic section (Kepler orbit),\n"
               "relative to the center-of-mass of the central body. The default mass value is for the angular\n"
               "momentum per unit mass.\n\n"
               ":param semiMajorAxis: Semi-major axis of Kepler orbit.\n"
               ":param eccentricity: Eccentricity of Kepler orbit.\n"
               ":param gravitationalParameterOfCentralBody: Gravitational parameter of central body.\n"
               ":param massOfOrbitingBody: Mass of orbiting body.\n"
               ":return: Two-body angular momentum."
        );

        p::def("computeKeplerMeanMotion", static_cast<double (*)(const double, const double,
                                                                 const double)>(&tudat::basic_astrodynamics::computeKeplerMeanMotion),
               (p::arg("semiMajorAxis"),
                       p::arg("gravitationalParameterOfCentralBody"),
                       p::arg("massOfOrbitingBody") = 0.0),
               "Computes the two-body mean motion of an orbiting body that follows a conic section\n"
               "(Kepler orbit). The mass of the orbiting body is set to that of a test particle by default.\n\n"
               ":param semiMajorAxis: Semi-major axis of Kepler orbit.\n"
               ":param gravitationalParameterOfCentralBody: Gravitational parameter of central body.\n"
               ":param massOfOrbitingBody: Mass of orbiting body.\n"
               ":return: Two-body mean motion."
        );

        p::def("computeKeplerEnergy", static_cast<double (*)(const double, const double,
                                                             const double)>(&tudat::basic_astrodynamics::computeKeplerEnergy),
               (p::arg("semiMajorAxis"),
                       p::arg("gravitationalParameterOfCentralBody"),
                       p::arg("massOfOrbitingBody") = 1.0),
               "Computes the energy of an orbiting body that follows a conic section (Kepler orbit). The\n"
               "default mass value is for the two-body orbital energy per unit mass. For closed conic sections\n"
               "(circles, ellipses), the semi-major axis is positive, and for open sections (hyperbolas) the\n"
               "semi-major axis is negative.\n\n"
               ":param semiMajorAxis: Semi-major axis of Kepler orbit.\n"
               ":param gravitationalParameterOfCentralBody: Gravitational parameter of central body.\n"
               ":param massOfOrbitingBody: Mass of orbiting body.\n"
               ":return: Kepler orbital energy."
        );


        p::def("computeSynodicPeriod",
               static_cast<double (*)(const double, const double)>(&tudat::basic_astrodynamics::computeSynodicPeriod),
               (p::arg("orbitalPeriodBody1"),
                       p::arg("orbitalPeriodBody2")),
               "Computes synodic period between two bodies in different Kepler orbits (closed conic sections).\n"
               "The orbital periods must be positive values for the synodic period to be sensible.\n\n"
               ":param orbitalPeriodBody1: Orbital period of Body 1.\n"
               ":param orbitalPeriodBody2: Orbital period of Body 2.\n"
               ":return: Synodic period."
        );


        p::def("computePeriapsisAltitudeFromKeplerianState",
               static_cast<double (*)(const Eigen::Vector6d &, const double)>
               (&tudat::basic_astrodynamics::computePeriapsisAltitudeFromKeplerianState),
               (p::arg("state"), p::arg("centralBodyRadius")),
               "Compute periapsis altitude from Keplerian state for spherical central body.\n"
               ":param state: Keplerian state of the propagated body.\n"
               ":param centralBodyRadius: Radius of the central body (assumed spherical).\n\n"
               ":return: The distance from the propagated body to the central body's spherical surface at periapsis."
        );

        p::def("computePeriapsisAltitudeFromCartesianState",
               static_cast<double (*)(const Eigen::Vector6d &, const double, const double)>
               (&tudat::basic_astrodynamics::computePeriapsisAltitudeFromCartesianState),
               (p::arg("state"), p::arg("centralBodyGravitationalParameter"), p::arg("centralBodyRadius")),
               "Compute periapsis altitude from Cartesian state for spherical central body.\n\n"
               ":param state: Cartesian state of the propagated body.\n"
               ":param centralBodyGravitationalParameter: Gravitational parameter of the central body.\n"
               ":param centralBodyRadius: Radius of the central body (assumed spherical).\n"
               ":return: The distance from the propagated body to the central body's spherical surface at periapsis."
        );
    }

}