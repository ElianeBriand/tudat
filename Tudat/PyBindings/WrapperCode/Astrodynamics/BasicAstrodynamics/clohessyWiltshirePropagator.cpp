/*    Copyright (c) 2010-2019, Delft University of Technology
 *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 */

#include "clohessyWiltshirePropagator.h"

#include <boost/python.hpp>
#include <boost/numpy.hpp>

#include <Tudat/Astrodynamics/BasicAstrodynamics/clohessyWiltshirePropagator.h>

#include "Tudat/Basics/basicTypedefs.h"


namespace p = boost::python;
namespace np = boost::numpy;



void tudat::PyBindings_internal::PyExport_clohessyWiltshirePropagator() {

    p::def("propagateClohessyWiltshire", &tudat::basic_astrodynamics::propagateClohessyWiltshire,
           (p::arg("initialState"), p::arg("propagationDuration"), p::arg("centralBodyGravitationalParameter"),
                   p::arg("referenceOrbitRadius")),
            "This function propagates linearized relative motion, based on the Clohessy-Wiltshire equations.\n"
            "It calculates the motion of a point mass A with respect to a local-vertical-local-horizontal\n"
            "reference frame centered on a point mass B.\n"
            "\n\n"
            "The following assumptions apply:\n"
            "    (1) Masses A and B are negligable compared to the central body mass (e.g. mass A is a\n"
            "        daughter spacecraft, mass B is a mother spacecraft, and the central body is planet\n"
            "        Earth).\n"
            "    (2) Orbit perturbations are negligable (i.e. massses A and B follow Kepler orbits about\n"
            "        the central body).\n"
            "    (3) The orbit of mass B is circular.\n"
            "    (4) The separation between mass A and mass B is very small compared to the circumference of\n"
            "        the orbit of mass B.\n"
            "\n\n"
            "The Clohessy-Wilthsire equations are given by Vallado [2001] as:\n\n"
            "\n\n"
            ".. math::\n\n"
            "    x( t ) &= \\frac{ \\dot{ x }_0 }{ n } \\sin( n t )\n"
            "        - \\left( 3 x_0 + \\frac{ 2 \\dot{ y }_0 } { n } \\right) \\cos( n t )\n"
            "        + \\left( 4 x_0 + \\frac{ 2 \\dot{ y }_0 }{ n } \\right) \\\\\n"
            "    y( t ) &= \\left( 6 x_0 + \\frac{ 4 \\dot{ y_0 } }{ n } \\right) \\sin( n t )\n"
            "             + \\frac{ 2 \\dot{ x }_0 }{ n } \\cos( n t )\n"
            "             - ( 6 x_0 n + 3 \\dot{ y_0 } ) t\n"
            "             + \\left( y_0 - \\frac{ 2 \\dot{ x }_0 }{ n } \\right) \\\\\n"
            "    z( t ) &= \\frac{ \\dot{ z }_0 }{ n } \\sin( n t )\n"
            "             + z_0 \\cos ( n t ) \\\\\n"
            "    \\dot{ x }( t ) &= ( 3 x_0 n + 2 \\dot{ y }_0 ) \\sin( n t )\n"
            "                     + \\dot{ x }_0 \\cos( n t ) \\\\\n"
            "    \\dot{ y }( t ) &= - 2 \\dot{ x }_0 \\sin( n t )\n"
            "                     + ( 6 x_0 n + 4 \\dot{ y }_0 ) \\cos( n t)\n"
            "                     - ( 6 n x_0 + 3 \\dot{ y }_0 ) \\\\\n"
            "    \\dot{ z }( t ) &= - z_0 n \\sin( n t )\n"
            "                     + \\dot{ z }_0 \\cos( n t )\n"
            ""
            "\n\n\n"
            "in which $x( t )$, $y( t )$ and $z( t )$ are the radial, along-track and "
            "cross-track position respectively, of mass A. Parameters $x_0$, $y_0$ and "
            "$z_0$ are the initial radial, along-track and cross-track position respectively. "
            "Parameter $n$ is the mean angular motion of the circular orbit of mass B. Finally, "
            "parameter $t$ is time.\n"
            "\n\n"
            ":param initialState: Initial state vector in Cartesian elements. The order is important! \n"
            "* initialState( 0 ) = radial position [m],  \n"
            "* initialState( 1 ) = along-track position [m],  \n"
            "* initialState( 2 ) = cross-track position [m],  \n"
            "* initialState( 3 ) = radial velocity [m/s],  \n"
            "* initialstate( 4 ) = along-track velocity [m/s],  \n"
            "* initialState( 5 ) = cross-track velocity [m/s].\n\n\n"
            ":param propagationDuration: Duration of propagation [s].\n"
            ":param centralBodyGravitationalParameter: Gravitational parameter of central body [m^3 s^-2].\n"
            ":param referenceOrbitRadius: Radius of circular orbit of mass B [m].\n"
            ":return: Final state vector in Cartesian elements. The order is important! "
            "* finalState( 0 ) = radial position [m]\n"
            "* finalState( 1 ) = along-track position [m]\n"
            "* finalState( 2 ) = cross-track position [m]\n"
            "* finalState( 3 ) = radial velocity [m/s]\n"
            "* finalState( 4 ) = along-track velocity [m/s]\n"
            "* finalState( 5 ) = cross-track velocity [m/s]\n\n\n"
            );

}