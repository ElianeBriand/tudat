/*    Copyright (c) 2010-2019, Delft University of Technology
 *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 */
#include "orbitalElementsConversions.h"

#include <boost/python.hpp>
#include <boost/numpy.hpp>

#include "Tudat/Astrodynamics/BasicAstrodynamics/orbitalElementConversions.h"

namespace p = boost::python;
namespace np = boost::numpy;


void tudat::PyBindings_internal::PyExport_orbitalElementsConversions() {

    p::def("computeSemiLatusRectum",
            &tudat::orbital_element_conversions::computeSemiLatusRectum<double>,
           (p::arg("eccentricity"), p::arg("semiMajorAxis"), p::arg("tolerance")),
           "Compute orbit semi-latus rectum."
           "\n\n\n"
           ":param eccentricity: Eccentricity of orbit\n"
           ":param semiMajorAxis: Semi-major axis of orbit (in Tudat, this input must equal semi-latus rectum for parabolic orbits)\n"
           ":param tolerance: Eccentricity tolerance for which orbit is deemed to be parabolic.\n"
           ":return: Orbit semi-latus rectum.\n\n"
           );

    p::def("computeOrbitalAngularMomentumPerUnitMass",
           &tudat::orbital_element_conversions::computeOrbitalAngularMomentumPerUnitMass<double>,
           (p::arg("semiLatusRectum"), p::arg("centralBodyGravitationalParameter")),
           "Compute orbit angular momentum per unit mass."
           "\n\n\n"
           ":param semiLatusRectum: Semi-latus rectum of orbit\n"
           ":param centralBodyGravitationalParameter: Gravitational parameter of central body.\n"
           ":return: Orbital angular momentum.\n\n"
    );

    p::def("convertKeplerianToCartesianElements",
           &tudat::orbital_element_conversions::convertKeplerianToCartesianElements<double>,
           (p::arg("keplerianElements"), p::arg("centralBodyGravitationalParameter")),
           "Converts Keplerian to Cartesian orbital elements (Chobotov, 2002). "
           "\n\n\n"
           ":param keplerianElements: Vector containing Keplerian elements. \n"
           ":param centralBodyGravitationalParameter Gravitational parameter of central body.\n"
           ":return: Converted state in Cartesian elements.\n\n"
    );

    p::def("convertCartesianToKeplerianElements",
           &tudat::orbital_element_conversions::convertCartesianToKeplerianElements<double>,
           (p::arg("cartesianElements"), p::arg("centralBodyGravitationalParameter")),
           "Converts Keplerian to Cartesian orbital elements (Chobotov, 2002). "
           "\n\n\n"
           ":param cartesianElements: Vector containing Cartesian elements.\n"
           ":param centralBodyGravitationalParameter Gravitational parameter of central body.\n"
           ":return: Converted state in Keplerian elements.\n\n\n"
           "WARNING: If eccentricity is 1.0 within 1.0e-15, "
           "keplerianElements( 0 ) = semi-latus rectum, since the orbit is parabolic.\n\n"
           "WARNING: If eccentricity is 0.0 within 1.0e-15,"
           "argument of periapsis is set to 0.0, since the orbit is circular.\n\n"
           "WARNING: If inclination is 0.0 within 1.0e-15, "
           "longitude of ascending node is set to 0.0, since the orbit is equatorial.\n\n\n"
           "The tolerance 1.0e-15 is hard-coded, as it should not be changed for performance "
           "reasons, unless required for specific scenarios. In those cases, users are expected "
           "to update the internal tolerance to the required value. Below these tolerance values "
           "for eccentricity and inclination, the orbit is considered to be a limit case. "
           "Essentially, special solutions are then used for parabolic, circular inclined, "
           "non-circular equatorial, and circular equatorial orbits. These special solutions are "
           "required because of singularities in the classical Keplerian elements. If high "
           "precision is required near these singularities, users are encouraged to consider using "
           "other elements, such as modified equinoctial elements. It should be noted that "
           "modified equinoctial elements also suffer from singularities, but not for zero "
           "eccentricity and inclination."
    );

    p::def("convertTrueAnomalyToEllipticalEccentricAnomaly",
           &tudat::orbital_element_conversions::convertTrueAnomalyToEllipticalEccentricAnomaly<double>,
           (p::arg("trueAnomaly"), p::arg("eccentricity")),
           "Converts true anomaly to eccentric anomaly for elliptical orbits ( 0 <= eccentricity < 1.0 ). "
           " The equations used can be found in (Chobotov, 2002)."
           "\n\n\n"
           ":param trueAnomaly: True anomaly. [rad] \n"
           ":param eccentricity: Eccentricity. [-].\n"
           ":return: (Elliptical) Eccentric anomaly. [rad]\n\n"
    );

    p::def("convertTrueAnomalyToHyperbolicEccentricAnomaly",
           &tudat::orbital_element_conversions::convertTrueAnomalyToHyperbolicEccentricAnomaly<double>,
           (p::arg("trueAnomaly"), p::arg("eccentricity")),
           "Converts true anomaly to hyperbolic eccentric anomaly for hyperbolic orbits "
           "  ( eccentricity > 1.0 )"
           " The equations used can be found in (Chobotov, 2002)."
           "\n\n\n"
           ":param trueAnomaly: True anomaly. [rad] \n"
           ":param eccentricity: Eccentricity. [-].\n"
           ":return: Hyperbolic eccentric anomaly. [rad]\n\n"
    );

    p::def("convertTrueAnomalyToEccentricAnomaly",
           &tudat::orbital_element_conversions::convertTrueAnomalyToEccentricAnomaly<double>,
           (p::arg("trueAnomaly"), p::arg("eccentricity")),
           "Converts true anomaly to eccentric anomaly for elliptical and hyperbolic orbits "
           "( eccentricity < 1.0 && eccentricity > 1.0 ). This function is essentially a wrapper for "
           "convertTrueAnomalyToEllipticalEccentricAnomaly() and "
           "convertTrueAnomalyToHyperbolicEccentricAnomaly(). It should be used in cases where the "
           "eccentricity of the orbit is not known a priori. Currently, this implementation performs a "
           "check on the eccentricity and throws an error for eccentricity < 0.0 and parabolic orbits, which "
           "have not been implemented. The equations used can be found in (Chobotov, 2002)."
           "\n\n\n"
           ":param trueAnomaly: True anomaly. [rad] \n"
           ":param eccentricity: Eccentricity. [-].\n"
           ":return: Eccentric anomaly. [rad]\n\n"
    );

    p::def("convertEllipticalEccentricAnomalyToTrueAnomaly",
           &tudat::orbital_element_conversions::convertEllipticalEccentricAnomalyToTrueAnomaly<double>,
           (p::arg("ellipticEccentricAnomaly"), p::arg("eccentricity")),
           "Converts eccentric anomaly to true anomaly for elliptical orbits ( 0 <= eccentricity < 1.0 )."
           " The equations used can be found in (Chobotov, 2002)."
           "\n\n\n"
           ":param ellipticEccentricAnomaly: Elliptical eccentric anomaly. [rad] \n"
           ":param eccentricity: Eccentricity. [-].\n"
           ":return: True anomaly. [rad]\n\n"
    );

    p::def("convertHyperbolicEccentricAnomalyToTrueAnomaly",
           &tudat::orbital_element_conversions::convertHyperbolicEccentricAnomalyToTrueAnomaly<double>,
           (p::arg("hyperbolicEccentricAnomaly"), p::arg("eccentricity")),
           "Converts hyperbolic eccentric anomaly to true anomaly for hyperbolic orbits "
           " ( eccentricity > 1.0 )."
           " The equations used can be found in (Chobotov, 2002)."
           "\n\n\n"
           ":param hyperbolicEccentricAnomaly: Hyperbolic eccentric anomaly. [rad] \n"
           ":param eccentricity: Eccentricity. [-].\n"
           ":return: True anomaly. [rad]\n\n"
    );

    p::def("convertEccentricAnomalyToTrueAnomaly",
           &tudat::orbital_element_conversions::convertEccentricAnomalyToTrueAnomaly<double>,
           (p::arg("eccentricAnomaly"), p::arg("eccentricity")),
           "Converts eccentric anomaly to true anomaly for elliptical and hyperbolic orbits  "
           "( eccentricity < 1.0 && eccentricity > 1.0 ). This function is essentially a wrapper for  "
           "convertEllipticalEccentricAnomalyToTrueAnomaly() and  "
           "convertHyperbolicEccentricAnomalyToTrueAnomaly(). It should be used in cases where the  "
           "eccentricity of the orbit is not known a priori. Currently, this implementation performs a  "
           "check on the eccentricity and throws an error for eccentricity < 0.0 and parabolic orbits, which  "
           "have not been implemented."
           " The equations used can be found in (Chobotov, 2002)."
           "\n\n\n"
           ":param eccentricAnomaly: Eccentric anomaly. [rad] \n"
           ":param eccentricity: Eccentricity. [-].\n"
           ":return: True anomaly. [rad]\n\n"
    );

    p::def("convertEllipticalEccentricAnomalyToMeanAnomaly",
           &tudat::orbital_element_conversions::convertEllipticalEccentricAnomalyToMeanAnomaly<double>,
           (p::arg("ellipticalEccentricAnomaly"), p::arg("eccentricity")),
           "Converts eccentric anomaly to mean anomaly for elliptical orbits ( 0 <= eccentricity < 1.0 )."
           " The equations used can be found in (Chobotov, 2002)."
           "\n\n\n"
           ":param ellipticalEccentricAnomaly: (Elliptical) eccentric anomaly. [rad] \n"
           ":param eccentricity: Eccentricity. [-].\n"
           ":return: Mean anomaly [rad].\n\n"
    );

    p::def("convertHyperbolicEccentricAnomalyToMeanAnomaly",
           &tudat::orbital_element_conversions::convertHyperbolicEccentricAnomalyToMeanAnomaly<double>,
           (p::arg("ellipticalEccentricAnomaly"), p::arg("eccentricity")),
           "Converts hyperbolic eccentric anomaly to mean anomaly for hyperbolic orbits ( eccentricity > 1.0 )."
           " The equations used can be found in (Chobotov, 2002)."
           "\n\n\n"
           ":param hyperbolicEccentricAnomaly: Hyperbolic eccentric anomaly. [rad] \n"
           ":param eccentricity: Eccentricity. [-].\n"
           ":return: Mean anomaly [rad].\n\n"
    );

    p::def("convertEccentricAnomalyToMeanAnomaly",
           &tudat::orbital_element_conversions::convertEccentricAnomalyToMeanAnomaly<double>,
           (p::arg("eccentricAnomaly"), p::arg("eccentricity")),
           "Converts eccentric anomaly to mean anomaly for elliptical and hyperbolic orbits  "
           "( eccentricity < 1.0 && eccentricity > 1.0 ). This function is essentially a wrapper for  "
           "convertEllipticalEccentricAnomalyToMeanAnomaly() and  "
           "convertHyperbolicEccentricAnomalyToMeanAnomaly(). It should be used in cases where the  "
           "eccentricity of the orbit is not known a priori. Currently, this implementation performs a  "
           "check on the eccentricity and throws an error for eccentricity < 0.0 and parabolic orbits, which  "
           "have not been implemented. "
           "The equations used can be found in (Chobotov, 2002)."
           "\n\n\n"
           ":param eccentricAnomaly: Eccentric anomaly. [rad] \n"
           ":param eccentricity: Eccentricity. [-].\n"
           ":return: Mean anomaly [rad].\n\n"
    );

    p::def("convertElapsedTimeToEllipticalMeanAnomalyChange",
           &tudat::orbital_element_conversions::convertElapsedTimeToEllipticalMeanAnomalyChange<double>,
           (p::arg("elapsedTime"), p::arg("centralBodyGravitationalParameter"), p::arg("semiMajorAxis")),
           "Converts elapsed time to mean anomaly change for elliptical orbits ( 0 <= eccentricity < 1.0 ). "
           " The semi-major axis must be non-negative; this function will throw an error to indicate if the "
           " semi-major axis is invalid. "
           "The equations used can be found in (Chobotov, 2002)."
           "\n\n\n"
           ":param elapsedTime: Elapsed time. [s] \n"
           ":param centralBodyGravitationalParameter: Gravitational parameter of central body. [m^3/s^2]\n"
           ":param semiMajorAxis: Semi-major axis. [m]\n"
           ":return: (Elliptical) Mean anomaly change. [rad].\n\n"
    );

    p::def("convertElapsedTimeToHyperbolicMeanAnomalyChange",
           &tudat::orbital_element_conversions::convertElapsedTimeToHyperbolicMeanAnomalyChange<double>,
           (p::arg("elapsedTime"), p::arg("centralBodyGravitationalParameter"), p::arg("semiMajorAxis")),
           "Converts elapsed time to mean anomaly change for for hyperbolic orbits ( eccentricity > 1.0 )."
           " The semi-major axis must be non-positive; this function will throw an error to indicate if the "
           " semi-major axis is invalid. "
           "The equations used can be found in (Chobotov, 2002)."
           "\n\n\n"
           ":param elapsedTime: Elapsed time. [s] \n"
           ":param centralBodyGravitationalParameter: Gravitational parameter of central body. [m^3/s^2]\n"
           ":param semiMajorAxis: Semi-major axis. [m]\n"
           ":return: Mean anomaly change. [rad].\n\n"
    );

    p::def("convertElapsedTimeToMeanAnomalyChange",
           &tudat::orbital_element_conversions::convertElapsedTimeToMeanAnomalyChange<double>,
           (p::arg("elapsedTime"), p::arg("centralBodyGravitationalParameter"), p::arg("semiMajorAxis")),
           "Converts elapsed time to mean anomaly change for elliptical and hyperbolic orbits  "
           " ( eccentricity < 1.0 && eccentricity > 1.0 ). This function is essentially a wrapper for  "
           " convertElapsedTimeToEllipticalMeanAnomalyChange() and  "
           " convertElapsedTimeToHyperbolicMeanAnomalyChange(). It should be used in cases where the  "
           " eccentricity of the orbit is not known a priori. The equations used can be found in  "
           " (Wertz, 2001)."
           "\n\n\n"
           ":param elapsedTime: Elapsed time. [s] \n"
           ":param centralBodyGravitationalParameter: Gravitational parameter of central body. [m^3/s^2]\n"
           ":param semiMajorAxis: Semi-major axis. [m]\n"
           ":return: Mean anomaly change. [rad].\n\n"
    );





    p::def("convertEllipticalMeanAnomalyChangeToElapsedTime",
           &tudat::orbital_element_conversions::convertEllipticalMeanAnomalyChangeToElapsedTime<double>,
           (p::arg("ellipticalMeanAnomalyChange"), p::arg("centralBodyGravitationalParameter"), p::arg("semiMajorAxis")),
           "Converts mean anomaly change to elapsed time for elliptical orbits ( 0 <= eccentricity < 1.0 ).  "
           " The equation used can be found in (Wertz, 2001). This function checks if the semi-major axis is  "
           "  non-negative and throws an error if it not."
           "\n\n\n"
           ":param ellipticalMeanAnomalyChange: (Elliptical) Mean anomaly change.  [rad] \n"
           ":param centralBodyGravitationalParameter: Gravitational parameter of central body. [m^3/s^2]\n"
           ":param semiMajorAxis: Semi-major axis. [m]\n"
           ":return: Elapsed time. [s].\n\n"
    );
    p::def("convertHyperbolicMeanAnomalyChangeToElapsedTime",
           &tudat::orbital_element_conversions::convertHyperbolicMeanAnomalyChangeToElapsedTime<double>,
           (p::arg("hyperbolicMeanAnomalyChange"), p::arg("centralBodyGravitationalParameter"), p::arg("semiMajorAxis")),
           "Converts mean anomaly change to elapsed time for hyperbolic orbits ( eccentricity > 1.0 ).  "
           "The equation used can be found in (Wertz, 2001). This function checks if the semi-major axis is  "
           "non-positive and throws an error if it not."
           "\n\n\n"
           ":param hyperbolicMeanAnomalyChange:  Hyperbolic mean anomaly change. [rad] \n"
           ":param centralBodyGravitationalParameter: Gravitational parameter of central body. [m^3/s^2]\n"
           ":param semiMajorAxis: Semi-major axis. [m]\n"
           ":return: Elapsed time. [s].\n\n"
    );



    p::def("convertMeanAnomalyChangeToElapsedTime",
           &tudat::orbital_element_conversions::convertMeanAnomalyChangeToElapsedTime<double>,
           (p::arg("meanAnomalyChange"), p::arg("centralBodyGravitationalParameter"), p::arg("semiMajorAxis")),
           "Converts mean anomaly change to elapsed time for elliptical and hyperbolic orbits  "
           " ( eccentricity < 1.0 && eccentricity > 1.0 ). This function is essentially a wrapper for  "
           " convertEllipticalMeanAnomalyChangeToElapsedTime() and  "
           " convertHyperbolicMeanAnomalyChangeToElapsedTime(). It should be used in cases where the  "
           " eccentricity of the orbit is not known a priori. The equations used can be found in  "
           " (Wertz, 2001)."
           "\n\n\n"
           ":param meanAnomalyChange: Mean anomaly change.  [rad] \n"
           ":param centralBodyGravitationalParameter: Gravitational parameter of central body. [m^3/s^2]\n"
           ":param semiMajorAxis: Semi-major axis. [m]\n"
           ":return: Elapsed time. [s].\n\n"
    );


    p::def("convertEllipticalMeanMotionToSemiMajorAxis",
           &tudat::orbital_element_conversions::convertEllipticalMeanMotionToSemiMajorAxis<double>,
           (p::arg("ellipticalMeanMotion"), p::arg("centralBodyGravitationalParameter")),
           "Converts mean motion to semi-major axis for elliptical orbits.."
           "\n\n\n"
           ":param ellipticalMeanMotion: (Elliptical) Mean motion. [rad/s] \n"
           ":param centralBodyGravitationalParameter: Gravitational parameter of central body. [m^3/s^2]\n"
           ":return: Semi-major axis. [m].\n\n"
    );

    p::def("convertSemiMajorAxisToEllipticalMeanMotion",
           &tudat::orbital_element_conversions::convertSemiMajorAxisToEllipticalMeanMotion<double>,
           (p::arg("semiMajorAxis"), p::arg("centralBodyGravitationalParameter")),
           "Converts mean motion to semi-major axis for elliptical orbits.."
           "\n\n\n"
           ":param semiMajorAxis: Semi-major axis [m] \n"
           ":param centralBodyGravitationalParameter: Gravitational parameter of central body. [m^3/s^2]\n"
           ":return: (Elliptical) Mean motion. [rad/s]\n\n"
    );



}