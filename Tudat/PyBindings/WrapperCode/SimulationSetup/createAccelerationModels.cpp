/*    Copyright (c) 2010-2019, Delft University of Technology
 *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 */

#include "createAccelerationModels.h"

#include <boost/python.hpp>
#include <boost/numpy.hpp>

#include <boost/python/suite/indexing/map_indexing_suite.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <Tudat/PyBindings/WrapperCode/ContainerIndexing.h>


#include "Tudat/Basics/basicTypedefs.h"

#include "Tudat/SimulationSetup/PropagationSetup/createAccelerationModels.h"
#include "Tudat/SimulationSetup/PropagationSetup/accelerationSettings.h"

namespace p = boost::python;
namespace np = boost::numpy;


namespace tudat {
    namespace PyBindings_internal {


        namespace {
            tudat::basic_astrodynamics::AccelerationMap createAccelerationModelsMap_ListWrapper(
                    const tudat::simulation_setup::NamedBodyMap& bodyMap,
                    const tudat::simulation_setup::SelectedAccelerationMap& selectedAccelerationPerBody,
                    p::list propagatedBodiesList,
                    p::list centralBodiesList
                    ) {
                std::vector<std::string> propagatedBodies;
                std::vector<std::string> centralBodies;

                for (int i = 0; i < p::len(propagatedBodiesList); ++i) {
                    p::extract<std::string> stringValue(propagatedBodiesList[i]);
                    if (stringValue.check()) {
                        propagatedBodies.push_back(stringValue());
                    }else {
                        throw std::runtime_error("propagagtedBodiesList must be a list of the name of bodies to be propagated");
                    }
                }

                for (int i = 0; i < p::len(centralBodiesList); ++i) {
                    p::extract<std::string> stringValue(centralBodiesList[i]);
                    if (stringValue.check()) {
                        centralBodies.push_back(stringValue());
                    }else {
                        throw std::runtime_error("centralBodiesList must be a list of the name of bodies to be propagated");
                    }
                }

                return tudat::simulation_setup::createAccelerationModelsMap(bodyMap,selectedAccelerationPerBody,propagatedBodies,centralBodies);
            }
        }

        void PyExport_createAccelerationModels() {

            p::def("createAccelerationModelsMap", &createAccelerationModelsMap_ListWrapper,
                   (p::arg("bodyMap"), p::arg("fullAccelerationMap"), p::arg("propagatedBodiesList"), p::arg("centralBodiesList")),
                   "Function to create acceleration models from a map of bodies and acceleration model types.\n\n\n"
                   ":param bodyMap: List of pointers to bodies required for the creation of the acceleration model objects.\n"
                   ":param selectedAccelerationPerBody: List identifying which bodies exert which type of acceleration(s)"
                   " on which bodies.\n"
                   ":param propagatedBodies: List of bodies that are to be propagated\n"
                   ":param centralBodies: List of central bodies for each body undergoing acceleration (in same order as propagatedBodies).\n"
                   ":return: List of acceleration model objects, in form of AccelerationMap."
            );


        }

    }
}