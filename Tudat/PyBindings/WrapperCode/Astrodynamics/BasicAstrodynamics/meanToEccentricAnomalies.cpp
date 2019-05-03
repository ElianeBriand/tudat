/*    Copyright (c) 2010-2019, Delft University of Technology
 *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 */

#include "meanToEccentricAnomalies.h"

#include <boost/python.hpp>
#include <boost/numpy.hpp>

#include <Tudat/Astrodynamics/BasicAstrodynamics/convertMeanToEccentricAnomalies.h>
#include "Tudat/Mathematics/BasicMathematics/mathematicalConstants.h"

#include "Tudat/Basics/basicTypedefs.h"


namespace p = boost::python;
namespace np = boost::numpy;

namespace tudat {
    namespace PyBindings_internal {
        namespace {


            BOOST_PYTHON_FUNCTION_OVERLOADS(convertMeanAnomalyToEccentricAnomaly_overloads,
                    tudat::orbital_element_conversions::convertMeanAnomalyToEccentricAnomaly<double>, 2, 5);

            BOOST_PYTHON_FUNCTION_OVERLOADS(convertMeanAnomalyToHyperbolicEccentricAnomaly_overloads,
                                            tudat::orbital_element_conversions::convertMeanAnomalyToHyperbolicEccentricAnomaly<double>, 2, 5);
        }
    }
}




void tudat::PyBindings_internal::PyExport_meanToEccentricAnomalies() {

    p::def("computeKeplersFunctionForEllipticalOrbits", &tudat::orbital_element_conversions::computeKeplersFunctionForEllipticalOrbits<double>,
           (p::arg("eccentricAnomaly"),p::arg("eccentricity"),p::arg("meanAnomaly")),
           "Computes Kepler's function, given as:\n\n"
           ".. math::\n\n"
           "     f( E ) = E - e * sin( E ) - M\n"
           "\n\n\n"
           "for elliptical orbits, where $E$ is the eccentric anomaly, $e$ is the\n"
           "eccentricity, $M$ is the mean anomaly. All eccentricities >= 0.0 and < 1.0 are valid.\n"
           ":param eccentricAnomaly: Eccentric anomaly.\n\n"
           ":param eccentricity: Eccentricity.\n"
           ":param meanAnomaly: Mean anomaly.\n"
           ":return: Value of Kepler's function for elliptical orbits.");

    p::def("computeFirstDerivativeKeplersFunctionForEllipticalOrbits", &tudat::orbital_element_conversions::computeFirstDerivativeKeplersFunctionForEllipticalOrbits<double>,
           (p::arg("eccentricAnomaly"),p::arg("eccentricity")),
           "Computes the first-derivative of Kepler's function, given as:\n\n"
           ".. math::\n\n"
           "     f( E ) = E - e * sin( E ) - M\n"
           "\n\n\n"
           "for elliptical orbits, where $E$ is the eccentric anomaly, $e$ is the\n"
           "eccentricity, $M$ is the mean anomaly. All eccentricities >= 0.0 and < 1.0 are valid.\n"
           ":param eccentricAnomaly: Eccentric anomaly.\n\n"
           ":param eccentricity: Eccentricity.\n"
           ":return: Value of Kepler's function for elliptical orbits.");

    p::def("computeKeplersFunctionForHyperbolicOrbits", &tudat::orbital_element_conversions::computeKeplersFunctionForHyperbolicOrbits<double>,
           (p::arg("hyperbolicEccentricAnomaly"),p::arg("eccentricity"),p::arg("hyperbolicMeanAnomaly")),
           "Computes Kepler's function, given as:\n\n"
           ".. math::\n\n"
           "     f( F ) = e * sinh( F ) - F - M\n"
           "\n\n\n"
           "for hyperbolic orbits, where $F$ is the eccentric anomaly, $e$ is the\n"
           "eccentricity, $M$ is the mean anomaly. All eccentricities > 1.0 are valid.\n\n"
           ":param eccentricAnomaly: Eccentric anomaly.\n"
           ":param eccentricity: Eccentricity.\n"
           ":param meanAnomaly: Mean anomaly.\n"
           ":return: Value of Kepler's function for elliptical orbits.");


    p::def("convertMeanAnomalyToEccentricAnomaly", &tudat::orbital_element_conversions::convertMeanAnomalyToEccentricAnomaly<double>,
           convertMeanAnomalyToEccentricAnomaly_overloads
                   ((p::arg("eccentricity"),
                   p::arg("aMeanAnomaly"),
                   p::arg("useDefaultInitialGuess") = true,
                   p::arg("userSpecifiedInitialGuess") = TUDAT_NAN,
                   p::arg("rootFinder") = std::shared_ptr< tudat::root_finders::RootFinderCore<double>>( )  ),
           "Converts mean anomaly to eccentric anomaly for elliptical orbits for all eccentricities >=\n"
           "0.0 and < 1.0. If the conversion fails or the eccentricity falls outside the valid range,\n"
           "then NaN is returned. Calculated with an accuracy of 1.0e-13 for all cases, except\n"
           "for some near-parabolic cases in which machine precision problems occur. These are tested\n"
           "against an accuracy of 1.0e-9. Near-parabolic in this sense means e > 1.0-1.0e-11. Also\n"
           "note that your mean anomaly is automatically transformed to fit within the 0 to 2.0*PI\n"
           "spectrum. \n\n\n"
           ":param eccentricity: Eccentricity of the orbit [-].\n"
           ":param aMeanAnomaly: Mean anomaly to convert to eccentric anomaly [rad].\n"
           ":param useDefaultInitialGuess: Boolean specifying whether to use default initial guess [-].\n"
           ":param userSpecifiedInitialGuess: Initial guess for rootfinder [rad].\n"
           ":param rootFinder: Rootfinder that is to be used. Default is "
           " Newton-Raphson using 1000 iterations as maximum and apprximately 1.0e-13 absolute "
           " X-tolerance (for doubles; 500 times ScalarType resolution ). "
           " Higher precision may invoke machine precision problems for some values.\n"
           ":return: Eccentric anomaly [rad].\n\n"));

    p::def("convertMeanAnomalyToHyperbolicEccentricAnomaly",
            &tudat::orbital_element_conversions::convertMeanAnomalyToHyperbolicEccentricAnomaly<double>,
            convertMeanAnomalyToHyperbolicEccentricAnomaly_overloads(
           (p::arg("eccentricity"),
                   p::arg("hyperbolicMeanAnomaly"),
                   p::arg("useDefaultInitialGuess") = true,
                   p::arg("userSpecifiedInitialGuess") = TUDAT_NAN,
                   p::arg("rootFinder") = std::shared_ptr< tudat::root_finders::RootFinderCore<double>>( )  ),
           "Converts mean anomaly to hyperbolic eccentric anomaly for hyperbolic orbits for all eccentricities >=\n"
           " 1.0. If the conversion fails or the eccentricity falls outside the valid range,\n"
           "then NaN is returned. Calculated with an accuracy of 1.0e-14 for all reasonable cases"
           "(eccentricities up to 1.0e15, mean anomalies -1.2e12 to 1.2e12). \n\n\n"
           ":param eccentricity: Eccentricity of the orbit [-].\n"
           ":param hyperbolicMeanAnomaly: Hyperbolic mean anomaly to convert to eccentric anomaly  [rad].\n"
           ":param useDefaultInitialGuess: Boolean specifying whether to use default initial guess [-].\n"
           ":param userSpecifiedInitialGuess: Initial guess for rootfinder [rad].\n"
           ":param rootFinder: Rootfinder that is to be used. Default is "
           " Newton-Raphson using 1000 iterations as maximum and apprximately 1.0e-13 absolute "
           " X-tolerance (for doubles; 500 times ScalarType resolution ). "
           " Higher precision may invoke machine precision problems for some values.\n"
           ":return: Hyperbolic eccentric anomaly [rad].\n\n"));


}
