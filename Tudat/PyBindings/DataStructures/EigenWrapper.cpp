/*    Copyright (c) 2010-2019, Delft University of Technology
 *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 */

#include "EigenWrapper.h"

#include <boost/python.hpp>
#include <boost/numpy.hpp>

#include <Eigen/Eigen>
#include <iostream>

namespace p = boost::python;
namespace np = boost::numpy;


namespace tudat {
    namespace PyBindings_internal {

        namespace {

            /*
             * This anonymous namespace contains getter/setter wrappers for add_properties.
             *
             * The lifetime of reference type returned by member function (for example Vector3d->x()) is tied
             * to the lifetime of the owning object : we must either inform python of this (so it keeps around
             * the owning object while a reference to a member is kept), or we use wrappers to copy references
             * to values (the value lifetime is then divorced from the original owning object).
             *
             * For primitive type, we always transform reference to value, because 1/ the cost is minimal and 2/ python
             * primitive type are immutable (even if you pass a reference to the primitive type, python expects that it
             * doesn't change -- which in our C++, it could)
             * For non-primitive type with negigible copying cost, we can also transform to value.
             * If copying cost are non-negligible, we use call policies like return_internal_reference.
             *
             * In addition we may need wrappers for add_properties (allow for b.x = 1 instead of b.setX(1))
             *
             */


            double Vector3d_x_getter(Eigen::Vector3d* vec3d) {
                return vec3d->x();
            }

            void Vector3d_x_setter(Eigen::Vector3d* vec3d, double x) {
                vec3d->x() = x;
            }

            double Vector3d_y_getter(Eigen::Vector3d* vec3d) {
                return vec3d->y();
            }

            void Vector3d_y_setter(Eigen::Vector3d* vec3d, double y) {
                vec3d->y() = y;
            }

            double Vector3d_z_getter(Eigen::Vector3d* vec3d) {
                return vec3d->z();
            }

            void Vector3d_z_setter(Eigen::Vector3d* vec3d, double z) {
                vec3d->z() = z;
            }

        }

        void PyExport_EigenDatastructures() {


            p::class_<Eigen::Vector3d>("Vector3d")
                    .add_property("x", &Vector3d_x_getter,
                                  &Vector3d_x_setter)
                    .add_property("y", &Vector3d_y_getter,
                                  &Vector3d_y_setter)
                    .add_property("z", &Vector3d_z_getter,
                                  &Vector3d_z_setter);
        }

    }
}