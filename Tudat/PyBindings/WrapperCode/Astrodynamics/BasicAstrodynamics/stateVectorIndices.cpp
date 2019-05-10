/*    Copyright (c) 2010-2019, Delft University of Technology
 *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 */
#include "stateVectorIndices.h"

#include <boost/python.hpp>
#include <boost/numpy.hpp>

#include "Tudat/Astrodynamics/BasicAstrodynamics/stateVectorIndices.h"

namespace p = boost::python;
namespace np = boost::numpy;


void tudat::PyBindings_internal::PyExport_stateVectorIndices() {


    p::enum_<tudat::orbital_element_conversions::CartesianElementIndices>("CartesianElementIndices")
            .value("xCartesianPositionIndex",
                   tudat::orbital_element_conversions::CartesianElementIndices::xCartesianPositionIndex)
            .value("yCartesianPositionIndex",
                   tudat::orbital_element_conversions::CartesianElementIndices::yCartesianPositionIndex)
            .value("zCartesianPositionIndex",
                   tudat::orbital_element_conversions::CartesianElementIndices::zCartesianPositionIndex)
            .value("xCartesianVelocityIndex",
                   tudat::orbital_element_conversions::CartesianElementIndices::xCartesianVelocityIndex)
            .value("yCartesianVelocityIndex",
                   tudat::orbital_element_conversions::CartesianElementIndices::yCartesianVelocityIndex)
            .value("zCartesianVelocityIndex",
                   tudat::orbital_element_conversions::CartesianElementIndices::zCartesianVelocityIndex)
                   ;

    p::enum_<tudat::orbital_element_conversions::KeplerianElementIndices>("KeplerianElementIndices")
            .value("semiMajorAxisIndex",
                   tudat::orbital_element_conversions::KeplerianElementIndices::semiMajorAxisIndex)
            .value("eccentricityIndex",
                   tudat::orbital_element_conversions::KeplerianElementIndices::eccentricityIndex)
            .value("inclinationIndex",
                   tudat::orbital_element_conversions::KeplerianElementIndices::inclinationIndex)
            .value("argumentOfPeriapsisIndex",
                   tudat::orbital_element_conversions::KeplerianElementIndices::argumentOfPeriapsisIndex)
            .value("longitudeOfAscendingNodeIndex",
                   tudat::orbital_element_conversions::KeplerianElementIndices::longitudeOfAscendingNodeIndex)
            .value("trueAnomalyIndex",
                   tudat::orbital_element_conversions::KeplerianElementIndices::trueAnomalyIndex)
            .value("semiLatusRectumIndex",
                   tudat::orbital_element_conversions::KeplerianElementIndices::semiLatusRectumIndex)
            ;



    p::enum_<tudat::orbital_element_conversions::ModifiedEquinoctialElementVectorIndices>("ModifiedEquinoctialElementVectorIndices")
            .value("semiParameterIndex",
                   tudat::orbital_element_conversions::ModifiedEquinoctialElementVectorIndices::semiParameterIndex)
            .value("fElementIndex",
                   tudat::orbital_element_conversions::ModifiedEquinoctialElementVectorIndices::fElementIndex)
            .value("gElementIndex",
                   tudat::orbital_element_conversions::ModifiedEquinoctialElementVectorIndices::gElementIndex)
            .value("hElementIndex",
                   tudat::orbital_element_conversions::ModifiedEquinoctialElementVectorIndices::hElementIndex)
            .value("kElementIndex",
                   tudat::orbital_element_conversions::ModifiedEquinoctialElementVectorIndices::kElementIndex)
            .value("trueLongitudeIndex",
                   tudat::orbital_element_conversions::ModifiedEquinoctialElementVectorIndices::trueLongitudeIndex)
            ;



    p::enum_<tudat::orbital_element_conversions::SphericalOrbitalStateElementIndices>("SphericalOrbitalStateElementIndices")
            .value("radiusIndex",
                   tudat::orbital_element_conversions::SphericalOrbitalStateElementIndices::radiusIndex)
            .value("latitudeIndex",
                   tudat::orbital_element_conversions::SphericalOrbitalStateElementIndices::latitudeIndex)
            .value("longitudeIndex",
                   tudat::orbital_element_conversions::SphericalOrbitalStateElementIndices::longitudeIndex)
            .value("speedIndex",
                   tudat::orbital_element_conversions::SphericalOrbitalStateElementIndices::speedIndex)
            .value("flightPathIndex",
                   tudat::orbital_element_conversions::SphericalOrbitalStateElementIndices::flightPathIndex)
            .value("headingAngleIndex",
                   tudat::orbital_element_conversions::SphericalOrbitalStateElementIndices::headingAngleIndex)
            ;


    p::enum_<tudat::orbital_element_conversions::UnifiedStateModelQuaternionsElementIndices>("UnifiedStateModelQuaternionsElementIndices")
            .value("CHodographUSM7Index",
                   tudat::orbital_element_conversions::UnifiedStateModelQuaternionsElementIndices::CHodographUSM7Index)
            .value("Rf1HodographUSM7Index",
                   tudat::orbital_element_conversions::UnifiedStateModelQuaternionsElementIndices::Rf1HodographUSM7Index)
            .value("Rf2HodographUSM7Index",
                   tudat::orbital_element_conversions::UnifiedStateModelQuaternionsElementIndices::Rf2HodographUSM7Index)
            .value("etaUSM7Index",
                   tudat::orbital_element_conversions::UnifiedStateModelQuaternionsElementIndices::etaUSM7Index)
            .value("epsilon1USM7Index",
                   tudat::orbital_element_conversions::UnifiedStateModelQuaternionsElementIndices::epsilon1USM7Index)
            .value("epsilon2USM7Index",
                   tudat::orbital_element_conversions::UnifiedStateModelQuaternionsElementIndices::epsilon2USM7Index)
            .value("epsilon3USM7Index",
                   tudat::orbital_element_conversions::UnifiedStateModelQuaternionsElementIndices::epsilon3USM7Index)
            ;


    p::enum_<tudat::orbital_element_conversions::UnifiedStateModelModifiedRodriguesParametersElementIndices>("UnifiedStateModelModifiedRodriguesParametersElementIndices")
            .value("CHodographUSM6Index",
                   tudat::orbital_element_conversions::UnifiedStateModelModifiedRodriguesParametersElementIndices::CHodographUSM6Index)
            .value("Rf1HodographUSM6Index",
                   tudat::orbital_element_conversions::UnifiedStateModelModifiedRodriguesParametersElementIndices::Rf1HodographUSM6Index)
            .value("Rf2HodographUSM6Index",
                   tudat::orbital_element_conversions::UnifiedStateModelModifiedRodriguesParametersElementIndices::Rf2HodographUSM6Index)
            .value("sigma1USM6Index",
                   tudat::orbital_element_conversions::UnifiedStateModelModifiedRodriguesParametersElementIndices::sigma1USM6Index)
            .value("sigma2USM6Index",
                   tudat::orbital_element_conversions::UnifiedStateModelModifiedRodriguesParametersElementIndices::sigma2USM6Index)
            .value("sigma3USM6Index",
                   tudat::orbital_element_conversions::UnifiedStateModelModifiedRodriguesParametersElementIndices::sigma3USM6Index)
            .value("shadowFlagUSM6Index",
                   tudat::orbital_element_conversions::UnifiedStateModelModifiedRodriguesParametersElementIndices::shadowFlagUSM6Index)
            ;


    p::enum_<tudat::orbital_element_conversions::UnifiedStateModelExponentialMapElementIndices>("UnifiedStateModelExponentialMapElementIndices")
            .value("CHodographUSMEMIndex",
                   tudat::orbital_element_conversions::UnifiedStateModelExponentialMapElementIndices::CHodographUSMEMIndex)
            .value("Rf1HodographUSMEMIndex",
                   tudat::orbital_element_conversions::UnifiedStateModelExponentialMapElementIndices::Rf1HodographUSMEMIndex)
            .value("Rf2HodographUSMEMIndex",
                   tudat::orbital_element_conversions::UnifiedStateModelExponentialMapElementIndices::Rf2HodographUSMEMIndex)
            .value("e1USMEMIndex",
                   tudat::orbital_element_conversions::UnifiedStateModelExponentialMapElementIndices::e1USMEMIndex)
            .value("e2USMEMIndex",
                   tudat::orbital_element_conversions::UnifiedStateModelExponentialMapElementIndices::e2USMEMIndex)
            .value("e3USMEMIndex",
                   tudat::orbital_element_conversions::UnifiedStateModelExponentialMapElementIndices::e3USMEMIndex)
            .value("shadowFlagUSMEMIndex",
                   tudat::orbital_element_conversions::UnifiedStateModelExponentialMapElementIndices::shadowFlagUSMEMIndex)
            ;


    p::enum_<tudat::orbital_element_conversions::QuaternionsElementIndices>("QuaternionsElementIndices")
            .value("etaQuaternionIndex",
                   tudat::orbital_element_conversions::QuaternionsElementIndices::etaQuaternionIndex)
            .value("epsilon1QuaternionIndex",
                   tudat::orbital_element_conversions::QuaternionsElementIndices::epsilon1QuaternionIndex)
            .value("epsilon2QuaternionIndex",
                   tudat::orbital_element_conversions::QuaternionsElementIndices::epsilon2QuaternionIndex)
            .value("epsilon3QuaternionIndex",
                   tudat::orbital_element_conversions::QuaternionsElementIndices::epsilon3QuaternionIndex)
            ;



    p::enum_<tudat::orbital_element_conversions::ModifiedRodriguesParametersElementIndices>("ModifiedRodriguesParametersElementIndices")
            .value("sigma1ModifiedRodriguesParametersIndex",
                   tudat::orbital_element_conversions::ModifiedRodriguesParametersElementIndices::sigma1ModifiedRodriguesParametersIndex)
            .value("sigma2ModifiedRodriguesParametersIndex",
                   tudat::orbital_element_conversions::ModifiedRodriguesParametersElementIndices::sigma2ModifiedRodriguesParametersIndex)
            .value("sigma3ModifiedRodriguesParametersIndex",
                   tudat::orbital_element_conversions::ModifiedRodriguesParametersElementIndices::sigma3ModifiedRodriguesParametersIndex)
            .value("shadowFlagModifiedRodriguesParametersIndex",
                   tudat::orbital_element_conversions::ModifiedRodriguesParametersElementIndices::shadowFlagModifiedRodriguesParametersIndex)
            ;


    p::enum_<tudat::orbital_element_conversions::ExponentialMapElementIndices>("ExponentialMapElementIndices")
            .value("e1ExponentialMapIndex",
                   tudat::orbital_element_conversions::ExponentialMapElementIndices::e1ExponentialMapIndex)
            .value("e2ExponentialMapIndex",
                   tudat::orbital_element_conversions::ExponentialMapElementIndices::e2ExponentialMapIndex)
            .value("e3ExponentialMapIndex",
                   tudat::orbital_element_conversions::ExponentialMapElementIndices::e3ExponentialMapIndex)
            .value("shadowFlagExponentialMapIndex",
                   tudat::orbital_element_conversions::ExponentialMapElementIndices::shadowFlagExponentialMapIndex)
            ;

}