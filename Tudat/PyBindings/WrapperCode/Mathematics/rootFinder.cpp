/*    Copyright (c) 2010-2019, Delft University of Technology
 *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 */

#include "rootFinder.h"

#include <boost/python.hpp>
#include <boost/numpy.hpp>

#include "Tudat/Basics/basicTypedefs.h"

#include "Tudat/Mathematics/RootFinders/rootFinder.h"


namespace p = boost::python;
namespace np = boost::numpy;



namespace tudat {
    namespace PyBindings_internal {

        void PyExport_rootFinder() {

            p::class_< std::function< bool( double, double, double, double, unsigned int )> >("TerminationFunction");

            p::class_<std::shared_ptr<tudat::root_finders::RootFinderCore< double >> >("RootFinderCore");

        }
    }
}