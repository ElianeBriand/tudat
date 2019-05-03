/*    Copyright (c) 2010-2019, Delft University of Technology
 *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 */

#include "createBodies.h"

#include <boost/python.hpp>
#include <boost/numpy.hpp>

#include <boost/python/suite/indexing/map_indexing_suite.hpp>

#include "Tudat/Basics/basicTypedefs.h"

#include "Tudat/SimulationSetup/EnvironmentSetup/createBodies.h"
#include "Tudat/SimulationSetup/EnvironmentSetup/defaultBodies.h"

namespace p = boost::python;
namespace np = boost::numpy;



namespace tudat {
    namespace PyBindings_internal {


        namespace {

            std::map< std::string, std::shared_ptr< tudat::simulation_setup::BodySettings> > getDefaultBodySettings_fromPyList(p::list& bodies,
                                                                                    const double initialTime,
                                                                                    const double finalTime,
                                                                                    const double timeStep = 300.0 ) {
                std::vector<std::string> bodiesNameList;
                for (int i = 0; i < p::len(bodies); ++i)
                {
                    p::extract<std::string&> value(bodies[i]);
                    if (value.check()) {
                        bodiesNameList.push_back(value());
                    } else {
                      throw std::runtime_error("The bodies list is to be a list of string corresponding to the name of the bodies");
                    }
                }
                return tudat::simulation_setup::getDefaultBodySettings(bodiesNameList,initialTime,finalTime,timeStep);
            }

            BOOST_PYTHON_FUNCTION_OVERLOADS(getDefaultBodySettings_fromPyList_overloads, getDefaultBodySettings_fromPyList, 3, 4);

            std::map< std::string, std::shared_ptr< tudat::simulation_setup::BodySettings> > getDefaultBodySettings_lax_fromPyList(p::list& bodies ) {
                std::vector<std::string> bodiesNameList;
                for (int i = 0; i < p::len(bodies); ++i)
                {
                    p::extract<std::string> value(bodies[i]);
                    if (value.check()) {
                        bodiesNameList.push_back(value());
                    } else {
                        throw std::runtime_error("The bodies list is to be a list of string corresponding to the name of the bodies");
                    }
                }
                return tudat::simulation_setup::getDefaultBodySettings(bodiesNameList);
            }

        }


        void PyExport_createBodies() {

            p::class_<std::map< std::string, std::shared_ptr< tudat::simulation_setup::BodySettings> > >("BodySettingsMap")
                    .def(p::map_indexing_suite<std::map<std::string, std::shared_ptr< tudat::simulation_setup::BodySettings>> >() )
                    ;

            p::class_<tudat::simulation_setup::BodySettings, std::shared_ptr< tudat::simulation_setup::BodySettings > >("BodySettings")
                    .def_readwrite("constantMass",&tudat::simulation_setup::BodySettings::constantMass)
                    .def_readwrite("atmosphereSettings",&tudat::simulation_setup::BodySettings::atmosphereSettings)
                    .def_readwrite("ephemerisSettings",&tudat::simulation_setup::BodySettings::ephemerisSettings)
                    .def_readwrite("gravityFieldSettings",&tudat::simulation_setup::BodySettings::gravityFieldSettings)
                    .def_readwrite("rotationModelSettings",&tudat::simulation_setup::BodySettings::rotationModelSettings)
                    .def_readwrite("shapeModelSettings",&tudat::simulation_setup::BodySettings::shapeModelSettings)
                    .def_readwrite("radiationPressureSettings",&tudat::simulation_setup::BodySettings::radiationPressureSettings)
                    .def_readwrite("aerodynamicCoefficientSettings",&tudat::simulation_setup::BodySettings::aerodynamicCoefficientSettings)
                    .def_readwrite("gravityFieldVariationSettings",&tudat::simulation_setup::BodySettings::gravityFieldVariationSettings)
                    .def_readwrite("groundStationSettings",&tudat::simulation_setup::BodySettings::groundStationSettings)
                    ;

            p::def("createBodies", &tudat::simulation_setup::createBodies,
                   (p::arg("bodySettings")),
                   "Function to create a map of body objects based on model-specific settings for the bodies, "
                   "containing settings for each relevant environment model. The return value is an opaque type (for the python "
                   " interface) to be passed to functions as-is.\n\n\n"
                   ":param bodySettings: List of settings for the bodies that are to be created (Tudat.BodySettingsMap)\n"
                   ":return: List of bodies created according to settings in bodySettings. (Opaque type)");

            p::def("setGlobalFrameBodyEphemerides", &tudat::simulation_setup::setGlobalFrameBodyEphemerides<double,double>,
                   (p::arg("namedBodyMap"),p::arg("globalFrameOrigin"),p::arg("globalFrameOrientation")),
                   "Function to define the global origin and orientation of the reference frame that is to be used in\n"
                   "the simulations.  This function checks the origin and orientation of the Ephemeris and\n"
                   "RotationalEphemeris, and checks whether their origin/orientation is the same as that\n"
                   "globalFrameOrigin and globalFrameOrientation provided as input.  In particular, this function\n"
                   "sets the ephemerisFrameToBaseFrameFunction and ephemerisFrameToBaseFrameLongFunction variables\n"
                   "of the Body objects, which provide a time-dependent translation of the global origin to the\n"
                   "body's ephemeris origin. In case of an inconsistency in the current and required frames, this\n"
                   "function throws an error.\n\n\n"
                   ":param namedBodyMap: List of body objects that constitute the environment.\n"
                   ":param globalFrameOrigin: Global reference frame origin.\n"
                   ":param globalFrameOrientation: Global referencef frame orientation.");

            p::def("getDefaultBodySettings", &getDefaultBodySettings_fromPyList,
                   getDefaultBodySettings_fromPyList_overloads(
                   (p::arg("bodies"),p::arg("initialTime"),p::arg("finalTime"),p::arg("timeStep") = 300.0)
                   ,"Function to create default settings from which to create a set of body objects using\n"
                    "the createBodies() function. This function is included to streamline and simplify the\n"
                    "creation of typical celestial bodies. The default settings for the various\n"
                    "environment models of the body are defined in the various functions defined in this file.\n\n\n"
                    ":param bodies: List of bodies name as string, for which default settings are to be retrieved.\n"
                    ":param initialTime: Start time at which environment models in body are to be created\n"
                    "(included as some environment models require e.g., interpolators to be created over\n"
                    "a certain time period).\n"
                    ":param finalTime: End time up to which environment models in body are to be created "
                    "(included as some environment models require e.g., interpolators to be created over "
                    "a certain time period).\n"
                    ":param timeStep: Time step with which interpolated data from Spice should be created.\n"
                    ":return: Default settings from which to create a set of body objects.\n\n"
                   )
                   );

            p::def("getDefaultBodySettings", &getDefaultBodySettings_lax_fromPyList,
                   (p::arg("bodies")),
                   "Function to create default settings from which to create a set of body objects using\n"
                   "the createBodies() function. This function is included to streamline and simplify the\n"
                   "creation of typical celestial bodies. The default settings for the various\n"
                   "environment models of the body are defined in the various functions defined in this file.\n\n\n"
                   ":param bodies: List of bodies name as string, for which default settings are to be retrieved.\n"
                   ":return: Default settings from which to create a set of body objects.\n\n");
        }
    }
}