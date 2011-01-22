/*! \file orbitalElementConversions.h
 *    This header file contains a namespace with orbital element conversion
 *     functions.
 *
 *    Path              : /Astrodynamics/States/
 *    Version           : 6
 *    Check status      : Checked
 *
 *    Author            : E. Iorfida
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : elisabetta_iorfida@yahoo.it
 *
 *    Checker           : J. Melman
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : J.C.P.Melman@tudelft.nl
 *
 *    Date created      : 20 Checked, 2010
 *    Last modified     : 19 December, 2010
 *
 *    References
 *
 *    Notes
 *
 *    Copyright (c) 2010 Delft University of Technology.
 *
 *    This software is protected by national and international copyright.
 *    Any unauthorized use, reproduction or modification is unlawful and
 *    will be prosecuted. Commercial and non-private application of the
 *    software in any form is strictly prohibited unless otherwise granted
 *    by the authors.
 *
 *    The code is provided without any warranty; without even the implied
 *    warranty of merchantibility or fitness for a particular purpose.
 *
 *    Changelog
 *      YYMMDD    author        comment
 *      101020    K. Kumar      First creation of code.
 *      101025    E. Iorfida    Fulfillment of the code with gravitational parameter.
 *      101130    E. Iorfida    Gravitational parameter removed.
 *      101202    J. Melman     Replaced #endif statement and changed Doxygen
 *                              return statement.
 *      101203    E. Iorfida    Gravitational parameter added.
 *      101219    J. Melman     Doxygen comment on gravitational parameter added.
 */

// Include statements.
#include "cartesianElements.h"
#include "keplerianElements.h"
#include "gravityFieldParameters.h"
#include "linearAlgebra.h"

#ifndef ORBITALELEMENTCONVERSIONS_H
#define ORBITALELEMENTCONVERSIONS_H

// TEMPORARY!
//! Function to compute the modulo.
/*!
 * This function computes the remainder of division of one number by another.
 * The remainder is in the range [ 0, divisor ].
 * \param dividend Number to be divided.
 * \param divisor Number that is divided by.
 * \return Remainder of division of dividend by divisor.
 */
double computeModulo( double dividend, double divisor );

//! Orbital element conversions namespace.
/*!
 *  Orbital element conversions namespace.
 */
namespace orbital_element_conversions
{

//! Function to convert Keplerian to Cartesian orbital elements.
/*!
 * This function converts Keplerian to Cartesian orbital elements.
 * \param keplerianElements Reference to KeplerianElements object.
 * \param gravitationalParameter Gravitational Parameter.
 * \return CartesianElements object.
 */
CartesianElements convertKeplerianToCartesianElements(
        KeplerianElements& keplerianElements,
        double gravitationalParameter );

//! Function to convert Cartesian to Keplerian orbital elements.
/*!
 * This function converts Cartesian to Keplerian orbital elements.
 * \param cartesianElements Reference to CartesianElements object.
 * \param gravitationalParameter Gravitational Parameter.
 * \return KeplerianElements object.
 */
KeplerianElements convertCartesianToKeplerianElements(
        CartesianElements& cartesianElements,
        double gravitationalParameter );

}

#endif // ORBITALELEMENTCONVERSIONS_H

// End of file.
