/*    Copyright (c) 2010-2019, Delft University of Technology
 *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 */

#include "accelerationModel.h"

#include <boost/python.hpp>
#include <boost/numpy.hpp>

#include <boost/python/suite/indexing/map_indexing_suite.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include "Tudat/Astrodynamics/BasicAstrodynamics/accelerationModel.h"


namespace p = boost::python;
namespace np = boost::numpy;

//namespace {
//    class dummyClassA_accelerationModel {
//    };
//}

void tudat::PyBindings_internal::PyExport_accelerationModel() {



    p::class_<std::shared_ptr<tudat::basic_astrodynamics::AccelerationModel3d>>("AccelerationModel3d");

    p::class_<std::vector<std::shared_ptr< tudat::basic_astrodynamics::AccelerationModel3d >>>("AccelerationModel3dList")
            .def(p::vector_indexing_suite<std::vector<std::shared_ptr< tudat::basic_astrodynamics::AccelerationModel3d >>>());

    p::class_<std::shared_ptr<tudat::basic_astrodynamics::AccelerationModel2d>>("AccelerationModel2d");

    p::class_<std::vector<std::shared_ptr< tudat::basic_astrodynamics::AccelerationModel2d >>>("AccelerationModel2dList")
            .def(p::vector_indexing_suite<std::vector<std::shared_ptr< tudat::basic_astrodynamics::AccelerationModel2d >>>());

}