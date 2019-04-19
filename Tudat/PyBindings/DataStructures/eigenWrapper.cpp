/*    Copyright (c) 2010-2019, Delft University of Technology
 *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 */

#include "eigenWrapper.h"

#include <exception>


#include <boost/python.hpp>
#include <boost/numpy.hpp>
#include <boost/iterator/iterator_facade.hpp>


#include <Eigen/Eigen>


namespace p = boost::python;
namespace np = boost::numpy;


namespace tudat {
    namespace PyBindings_internal {

        namespace {

            /*
             * This anonymous namespace contains getter/setter wrappers for add_properties
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

        // C++ classes to python datatype converting methods

        p::list Vector3d_toList(Eigen::Vector3d* vec3d) {
            p::list vecList;

            p::list xList;
            xList.append((double) vec3d->x());

            p::list yList;
            yList.append((double) vec3d->y());

            p::list zList;
            zList.append((double) vec3d->z());

            vecList.append(xList);
            vecList.append(yList);
            vecList.append(zList);
            return vecList;
        }





        class Vector3d_iterator
                : public boost::iterator_facade<Vector3d_iterator, double, boost::forward_traversal_tag> {
        public:
            Vector3d_iterator()
                    : vector_(nullptr),
                      position(3) // Default constructor gives end iterator
            {}

            explicit Vector3d_iterator(Eigen::Vector3d* vector)
            : vector_(vector),
              position(0)
                    {}

        private:
            Eigen::Vector3d* vector_;
            unsigned int position;

            friend class boost::iterator_core_access;

            void increment() { position++; }

            bool equal(Vector3d_iterator const& other) const
            {
                return this->position == other.position;
            }

            double& dereference() const {
                switch(position) {
                    case 0:
                        return vector_->x();
                        break;
                    case 1:
                        return vector_->y();
                        break;
                    case 2:
                        return vector_->z();
                        break;
                    default:
                        throw std::out_of_range("Vector3d iterator out of range");
                        break;
                }
            }

        };

        Vector3d_iterator Vector3d_begin(Eigen::Vector3d& vec3d) {
            return Vector3d_iterator(&vec3d);
        }

        Vector3d_iterator Vector3d_end(Eigen::Vector3d& vec3d) {
            return Vector3d_iterator();
        }

        np::ndarray Vector3d_toNPArray(Eigen::Vector3d* vec3d) {

            p::tuple shape = p::make_tuple(3, 1); // as row vector
            np::dtype dtype = np::dtype::get_builtin<double>();

            p::list vecAsPythonList = Vector3d_toList(vec3d);
            np::ndarray a = np::array(vecAsPythonList,dtype);
            return a;
        }


        void PyExport_EigenDatastructures() {


            p::class_<Eigen::Vector3d>("Vector3d")
                    .def(p::init<double, double, double>())  // Constructor from x,y,z
                    .add_property("x", &Vector3d_x_getter,
                                  &Vector3d_x_setter)
                    .add_property("y", &Vector3d_y_getter,
                                  &Vector3d_y_setter)
                    .add_property("z", &Vector3d_z_getter,
                                  &Vector3d_z_setter)
                    .def("norm", &Eigen::Vector3d::norm)
                    .def("normalize", &Eigen::Vector3d::normalize)
                    .def("columnList", &Vector3d_toList)
                    .def("__iter__", p::range(&Vector3d_begin,&Vector3d_end))
                    .def("toNumpy", &Vector3d_toNPArray);
        }

    }
}