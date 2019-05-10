/*    Copyright (c) 2010-2019, Delft University of Technology
 *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 */

#include "accelerationSettings.h"

#include <boost/python.hpp>
#include <boost/numpy.hpp>

#include <boost/python/suite/indexing/map_indexing_suite.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <Tudat/PyBindings/WrapperCode/ContainerIndexing.h>


#include "Tudat/Basics/basicTypedefs.h"

#include "Tudat/SimulationSetup/PropagationSetup/accelerationSettings.h"


namespace p = boost::python;
namespace np = boost::numpy;


namespace tudat {
    namespace PyBindings_internal {

        namespace {
            std::shared_ptr<tudat::simulation_setup::MutualSphericalHarmonicAccelerationSettings>
            MutualSphericalHarmonicAccelerationSettings_constructorWrapper(
                    const int maximumDegreeOfBodyExertingAcceleration,
                    const int maximumOrderOfBodyExertingAcceleration,
                    const int maximumDegreeOfBodyUndergoingAcceleration,
                    const int maximumOrderOfBodyUndergoingAcceleration,
                    const int maximumDegreeOfCentralBody = 0,
                    const int maximumOrderOfCentralBody = 0) {
                auto ret = std::make_shared<tudat::simulation_setup::MutualSphericalHarmonicAccelerationSettings>(
                        maximumDegreeOfBodyExertingAcceleration,
                        maximumOrderOfBodyExertingAcceleration, maximumDegreeOfBodyUndergoingAcceleration,
                        maximumOrderOfBodyUndergoingAcceleration, maximumDegreeOfCentralBody,
                        maximumOrderOfCentralBody);
                return ret;
            }

            std::shared_ptr<tudat::simulation_setup::RelativisticAccelerationCorrectionSettings>
            RelativisticAccelerationCorrectionSettings_constructorWrapper(
                    const bool calculateSchwarzschildCorrection = true,
                    const bool calculateLenseThirringCorrection = false,
                    const bool calculateDeSitterCorrection = false,
                    const std::string primaryBody = "",
                    const Eigen::Vector3d centralBodyAngularMomentum = Eigen::Vector3d::Zero()) {
                auto ret = std::make_shared<tudat::simulation_setup::RelativisticAccelerationCorrectionSettings>(
                        calculateSchwarzschildCorrection,
                        calculateLenseThirringCorrection,
                        calculateDeSitterCorrection,
                        primaryBody,
                        centralBodyAngularMomentum);
                return ret;
            }


            std::shared_ptr<tudat::simulation_setup::EmpiricalAccelerationSettings>
            EmpiricalAccelerationSettings_constructorWrapper(
                    const Eigen::Vector3d &constantAcceleration = Eigen::Vector3d::Zero(),
                    const Eigen::Vector3d &sineAcceleration = Eigen::Vector3d::Zero(),
                    const Eigen::Vector3d &cosineAcceleration = Eigen::Vector3d::Zero()
            ) {
                auto ret = std::make_shared<tudat::simulation_setup::EmpiricalAccelerationSettings>(
                        constantAcceleration,
                        sineAcceleration,
                        cosineAcceleration);
                return ret;
            }


            void AccelerationSettings_addAccelerationHelper_InsertInMap(std::map<std::string, std::vector<std::shared_ptr<tudat::simulation_setup::AccelerationSettings> > >* this_,
                                                                        std::string bodyName,
                                                                        std::vector<std::shared_ptr<tudat::simulation_setup::AccelerationSettings> > vectorOfAccelSettings) {
                auto search = this_->find(bodyName);
                if (search == this_->end()) {
                    // No existing settings for the body
                    this_->insert(std::make_pair(bodyName,vectorOfAccelSettings));
                } else {
                    // Replace existing settings
                    (*this_)[bodyName] = vectorOfAccelSettings;
                }
            }

            void AccelerationSettings_addAccelerationHelper_oneAccel(std::map<std::string, std::vector<std::shared_ptr<tudat::simulation_setup::AccelerationSettings> > >* this_,
                                                            p::str exertingBodyName,
                                                            tudat::basic_astrodynamics::AvailableAcceleration accelType) {
                std::string bodyName = p::extract<std::string> (exertingBodyName)();
                std::vector<std::shared_ptr<tudat::simulation_setup::AccelerationSettings> > vectorOfAccelSettings;
                vectorOfAccelSettings.emplace_back(std::make_shared<tudat::simulation_setup::AccelerationSettings>(accelType));
                AccelerationSettings_addAccelerationHelper_InsertInMap(this_,bodyName,vectorOfAccelSettings);

            }

            void AccelerationSettings_addAccelerationHelper_list(std::map<std::string, std::vector<std::shared_ptr<tudat::simulation_setup::AccelerationSettings> > >* this_,
                                                            p::str exertingBodyName,
                                                            p::list listOfAccelSettings) {

                std::string bodyName = p::extract<std::string> (exertingBodyName)();

                std::vector<std::shared_ptr<tudat::simulation_setup::AccelerationSettings> > vectorOfAccelSettings;

                for (int i = 0; i < p::len(listOfAccelSettings); ++i)
                {
                    p::extract<std::shared_ptr<tudat::simulation_setup::AccelerationSettings>> settingsShPtrValue(listOfAccelSettings[i]);
                    if (settingsShPtrValue.check()) {
                        // The value is directly an acceleration settings object
                        vectorOfAccelSettings.push_back(settingsShPtrValue());
                    } else {
                        p::extract<tudat::basic_astrodynamics::AvailableAcceleration> settingsEnumValue(listOfAccelSettings[i]);
                        if (settingsEnumValue.check()) {
                            // That's an enum value for a setting type, we create the setting object
                            auto shPtr_AccelSettings = std::make_shared<tudat::simulation_setup::AccelerationSettings>(settingsEnumValue());
                            vectorOfAccelSettings.push_back(shPtr_AccelSettings);
                        }else {
                            // That's nothing useful
                            throw std::runtime_error("listOfAccelSettings must be a list of AccelerationSettings and/or AvailableAcceleration type");
                        }
                    }
                }

                AccelerationSettings_addAccelerationHelper_InsertInMap(this_,bodyName,vectorOfAccelSettings);

            }

        }


        void PyExport_accelerationSettings() {


            p::enum_<tudat::basic_astrodynamics::AvailableAcceleration>("AvailableAcceleration")
                    // Deprecated "synonyms" like central_gravity for point_mass_gravity were consciously not exported.
                    .value("undefined_acceleration",
                           tudat::basic_astrodynamics::AvailableAcceleration::undefined_acceleration)
                    .value("point_mass_gravity",
                           tudat::basic_astrodynamics::AvailableAcceleration::point_mass_gravity)
                    .value("aerodynamic",
                           tudat::basic_astrodynamics::AvailableAcceleration::aerodynamic)
                    .value("cannon_ball_radiation_pressure",
                           tudat::basic_astrodynamics::AvailableAcceleration::cannon_ball_radiation_pressure)
                    .value("spherical_harmonic_gravity",
                           tudat::basic_astrodynamics::AvailableAcceleration::spherical_harmonic_gravity)
                    .value("mutual_spherical_harmonic_gravity",
                           tudat::basic_astrodynamics::AvailableAcceleration::mutual_spherical_harmonic_gravity)
                    .value("third_body_point_mass_gravity",
                           tudat::basic_astrodynamics::AvailableAcceleration::third_body_point_mass_gravity)
                    .value("third_body_spherical_harmonic_gravity",
                           tudat::basic_astrodynamics::AvailableAcceleration::third_body_spherical_harmonic_gravity)
                    .value("third_body_mutual_spherical_harmonic_gravity",
                           tudat::basic_astrodynamics::AvailableAcceleration::third_body_mutual_spherical_harmonic_gravity)
                    .value("thrust_acceleration",
                           tudat::basic_astrodynamics::AvailableAcceleration::thrust_acceleration)
                    .value("relativistic_correction_acceleration",
                           tudat::basic_astrodynamics::AvailableAcceleration::relativistic_correction_acceleration)
                    .value("empirical_acceleration",
                           tudat::basic_astrodynamics::AvailableAcceleration::empirical_acceleration)
                    .value("direct_tidal_dissipation_in_central_body_acceleration",
                           tudat::basic_astrodynamics::AvailableAcceleration::direct_tidal_dissipation_in_central_body_acceleration)
                    .value("direct_tidal_dissipation_in_orbiting_body_acceleration",
                           tudat::basic_astrodynamics::AvailableAcceleration::direct_tidal_dissipation_in_orbiting_body_acceleration);

            p::class_<tudat::simulation_setup::AccelerationSettings, std::shared_ptr<tudat::simulation_setup::AccelerationSettings>>(
                    "AccelerationSettings",
                    "Class for providing settings for acceleration model. This class is a functional (base) class for\n"
                    "settings of acceleration models that  require no information in addition to their type.\n"
                    "Classes defining settings for acceleration models requiring additional information must be\n"
                    "derived from this class.",
                    p::init<tudat::basic_astrodynamics::AvailableAcceleration>())
                    .def_readonly("accelerationType",
                                  &tudat::simulation_setup::AccelerationSettings::accelerationType_);

            p::class_<tudat::simulation_setup::SphericalHarmonicAccelerationSettings, p::bases<
                    tudat::simulation_setup::AccelerationSettings>, std::shared_ptr<tudat::simulation_setup::SphericalHarmonicAccelerationSettings>>
                    (
                            "SphericalHarmonicAccelerationSettings",
                            "Class for providing settings for spherical harmonics acceleration model,\n"
                            "specifically the maximum degree and order up to which the field is to be expanded. Note that\n"
                            "the minimum degree and order are currently always set to zero.",
                            p::init<int, int>((p::arg("maximumDegree"), p::arg("maximumOrder")),
                                              "Constructor to set maximum degree and order that is to be taken into account.\n\n"
                                              ":param maximumDegree: Maximum degree\n"
                                              ":param maximumOrder: Maximum order"))
                    .def_readwrite("maximumDegree",
                                   &tudat::simulation_setup::SphericalHarmonicAccelerationSettings::maximumDegree_)
                    .def_readwrite("maximumOrder_",
                                   &tudat::simulation_setup::SphericalHarmonicAccelerationSettings::maximumOrder_);


            p::class_<tudat::simulation_setup::MutualSphericalHarmonicAccelerationSettings, p::bases<
                    tudat::simulation_setup::AccelerationSettings>, std::shared_ptr<tudat::simulation_setup::MutualSphericalHarmonicAccelerationSettings>>
                    (
                            "MutualSphericalHarmonicAccelerationSettings",
                            "Class for providing acceleration settings for mutual spherical harmonics acceleration model,\n"
                            "specifically the maximum degree and order up to which the fields of the bodies are be expanded.\n"
                            "Please note that the minimum degrees and orders are currently always set to zero.",
                            p::no_init)
                    .def("__init__",
                         p::make_constructor(&MutualSphericalHarmonicAccelerationSettings_constructorWrapper,
                                             p::default_call_policies(),
                                             (p::arg("maximumDegreeOfBodyExertingAcceleration"),
                                                     p::arg("maximumOrderOfBodyExertingAcceleration"),
                                                     p::arg("maximumDegreeOfBodyUndergoingAcceleration"),
                                                     p::arg("maximumOrderOfBodyUndergoingAcceleration"),
                                                     p::arg("maximumDegreeOfCentralBody") = 0,
                                                     p::arg("maximumOrderOfCentralBody") = 0)),
                         "Constructor to set maximum degrees and orders that are to be taken into account.\n\n"
                         ":param maximumDegreeOfBodyExertingAcceleration: Maximum degree of body exerting acceleration.\n"
                         ":param maximumOrderOfBodyExertingAcceleration: Maximum order of body exerting acceleration.\n"
                         ":param maximumDegreeOfBodyUndergoingAcceleration: Maximum degree of body undergoing acceleration.\n"
                         ":param maximumOrderOfBodyUndergoingAcceleration: Maximum order of body undergoing acceleration.\n"
                         ":param maximumDegreeOfCentralBody: Maximum degree of central body (only relevant for 3rd body acceleration).\n"
                         ":param maximumOrderOfCentralBody: Maximum order of central body (only relevant for 3rd body acceleration).\n\n")
                    .def_readwrite("maximumDegreeOfBodyExertingAcceleration",
                                   &tudat::simulation_setup::MutualSphericalHarmonicAccelerationSettings::maximumDegreeOfBodyExertingAcceleration_)
                    .def_readwrite("maximumOrderOfBodyExertingAcceleration",
                                   &tudat::simulation_setup::MutualSphericalHarmonicAccelerationSettings::maximumOrderOfBodyExertingAcceleration_)
                    .def_readwrite("maximumDegreeOfBodyUndergoingAcceleration",
                                   &tudat::simulation_setup::MutualSphericalHarmonicAccelerationSettings::maximumDegreeOfBodyUndergoingAcceleration_)
                    .def_readwrite("maximumOrder",
                                   &tudat::simulation_setup::MutualSphericalHarmonicAccelerationSettings::maximumOrderOfBodyUndergoingAcceleration_)
                    .def_readwrite("maximumDegreeOfCentralBody",
                                   &tudat::simulation_setup::MutualSphericalHarmonicAccelerationSettings::maximumDegreeOfCentralBody_)
                    .def_readwrite("maximumOrderOfCentralBody",
                                   &tudat::simulation_setup::MutualSphericalHarmonicAccelerationSettings::maximumOrderOfCentralBody_);


            p::class_<tudat::simulation_setup::RelativisticAccelerationCorrectionSettings, p::bases<
                    tudat::simulation_setup::AccelerationSettings>, std::shared_ptr<tudat::simulation_setup::RelativisticAccelerationCorrectionSettings>>
                    (
                            "RelativisticAccelerationCorrectionSettings",
                            "Class to provide settings for typical relativistic corrections to the dynamics of an orbiter: the\n"
                            "Schwarzschild, Lense-Thirring and de Sitter terms. An excellent introduction to\n"
                            "these models is given in 'General Relativity and Space Geodesy' by L. Combrinck (2012).",
                            p::no_init)
                    .def("__init__",
                         p::make_constructor(&RelativisticAccelerationCorrectionSettings_constructorWrapper,
                                             p::default_call_policies(),
                                             (p::arg("calculateSchwarzschildCorrection") = true,
                                              p::arg("calculateLenseThirringCorrection") = false,
                                              p::arg("calculateDeSitterCorrection") = false,
                                              p::arg("primaryBody") = "",
                                              p::arg("centralBodyAngularMomentum") = Eigen::Vector3d(
                                                      Eigen::Vector3d::Zero()))),
                         "Constructor\n\n"
                         ":param calculateSchwarzschildCorrection: Boolean denoting whether the Schwarzschild term is used.\n"
                         ":param calculateLenseThirringCorrection: Boolean denoting whether the Lense-Thirring term is used.\n"
                         ":param calculateDeSitterCorrection: Boolean denoting whether the de Sitter term is used.\n"
                         ":param primaryBody: Name of primary body (e.g. Sun for acceleration acting on an Earth-orbiting satellite)\n"
                         ":param centralBodyAngularMomentum: Constant angular momentum of central body. NOTE: Passing angular momentum through this"
                         "function is temporary: in the future this will be done consistently with rotation/gravity field.")
                    .def_readwrite("calculateSchwarzschildCorrection",
                                   &tudat::simulation_setup::RelativisticAccelerationCorrectionSettings::calculateSchwarzschildCorrection_)
                    .def_readwrite("calculateLenseThirringCorrection",
                                   &tudat::simulation_setup::RelativisticAccelerationCorrectionSettings::calculateLenseThirringCorrection_)
                    .def_readwrite("calculateDeSitterCorrection",
                                   &tudat::simulation_setup::RelativisticAccelerationCorrectionSettings::calculateDeSitterCorrection_)
                    .def_readwrite("primaryBody",
                                   &tudat::simulation_setup::RelativisticAccelerationCorrectionSettings::primaryBody_)
                    .def_readwrite("centralBodyAngularMomentum",
                                   &tudat::simulation_setup::RelativisticAccelerationCorrectionSettings::centralBodyAngularMomentum_);

            p::class_<tudat::simulation_setup::EmpiricalAccelerationSettings, p::bases<
                    tudat::simulation_setup::AccelerationSettings>, std::shared_ptr<tudat::simulation_setup::EmpiricalAccelerationSettings>>
                    (
                            "EmpiricalAccelerationSettings",
                            "Class to define settings for empirical accelerations.",
                            p::no_init)
                    .def("__init__",
                         p::make_constructor(&EmpiricalAccelerationSettings_constructorWrapper,
                                             p::default_call_policies(),
                                             (p::arg("constantAcceleration") = Eigen::Vector3d(Eigen::Vector3d::Zero()),
                                              p::arg("sineAcceleration") = Eigen::Vector3d(Eigen::Vector3d::Zero()),
                                              p::arg("cosineAcceleration") = Eigen::Vector3d(Eigen::Vector3d::Zero()))),
                         "Constructor\n\n"
                         ":param constantAcceleration: Acceleration (in RSW frame) that is constant\n"
                         ":param sineAcceleration: Acceleration (in RSW frame) that scales with sine of true anomaly\n"
                         ":param cosineAcceleration: Acceleration (in RSW frame) that scales with cosine of true anomaly")
                    .def_readwrite("constantAcceleration",
                                   &tudat::simulation_setup::EmpiricalAccelerationSettings::constantAcceleration_)
                    .def_readwrite("sineAcceleration",
                                   &tudat::simulation_setup::EmpiricalAccelerationSettings::sineAcceleration_)
                    .def_readwrite("cosineAcceleration",
                                   &tudat::simulation_setup::EmpiricalAccelerationSettings::cosineAcceleration_);

            p::class_<std::vector<std::shared_ptr<tudat::simulation_setup::AccelerationSettings> >>(
                    "AccelerationSettingsList")
                    .def(p::vector_indexing_suite<std::vector<std::shared_ptr<tudat::simulation_setup::AccelerationSettings> >>());


            p::class_<std::map<std::string, std::vector<std::shared_ptr<tudat::simulation_setup::AccelerationSettings> > >>(
                    "PerBodyAccelerationSettings")
                    .def(p::map_indexing_suite<std::map<std::string, std::vector<std::shared_ptr<tudat::simulation_setup::AccelerationSettings> > >>())
                    .def("addAcceleration", &AccelerationSettings_addAccelerationHelper_list, (p::arg("exertingBodyName"), p::arg("listOfAccelerationSettings")))
                    .def("addAcceleration", &AccelerationSettings_addAccelerationHelper_oneAccel, (p::arg("exertingBodyName"), p::arg("accelerationType")));

            p::class_<tudat::simulation_setup::SelectedAccelerationMap>("FullAccelerationMap")
                    .def(p::map_indexing_suite<tudat::simulation_setup::SelectedAccelerationMap>());


            p::class_<tudat::basic_astrodynamics::SingleBodyAccelerationMap>("SingleBodyAccelerationMap")
                    .def("__len__", &tudat::basic_astrodynamics::SingleBodyAccelerationMap::size)
                    .def("clear", &tudat::basic_astrodynamics::SingleBodyAccelerationMap::clear)
                    .def("__getitem__", &MinimalMapIndexing<tudat::basic_astrodynamics::SingleBodyAccelerationMap>::get,
                         p::return_value_policy<p::copy_non_const_reference>())
                    .def("__setitem__", &MinimalMapIndexing<tudat::basic_astrodynamics::SingleBodyAccelerationMap>::set,
                         p::with_custodian_and_ward<1,2>()) // to let container keep value
                    .def("__delitem__", &MinimalMapIndexing<tudat::basic_astrodynamics::SingleBodyAccelerationMap>::del)
                    ;

            p::class_<tudat::basic_astrodynamics::AccelerationMap>("ModelAccelerationMap")
                    .def("__len__", &tudat::basic_astrodynamics::AccelerationMap::size)
                    .def("clear", &tudat::basic_astrodynamics::AccelerationMap::clear)
                    .def("__getitem__", &MinimalMapIndexing<tudat::basic_astrodynamics::AccelerationMap>::get,
                         p::return_value_policy<p::copy_non_const_reference>())
                    .def("__setitem__", &MinimalMapIndexing<tudat::basic_astrodynamics::AccelerationMap>::set,
                         p::with_custodian_and_ward<1,2>()) // to let container keep value
                    .def("__delitem__", &MinimalMapIndexing<tudat::basic_astrodynamics::AccelerationMap>::del)
                    ;




        }


    }
}