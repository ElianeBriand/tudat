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
#include <iostream>

#include "Tudat/Basics/basicTypedefs.h"



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
        template <typename EigenVectorType>
        p::list Vector_toList(EigenVectorType* vec) {
            p::list vecList;

            for (unsigned int j = 0; j < EigenVectorType::RowsAtCompileTime; ++j) {
                p::list coordList;
                coordList.append((double) (*vec)[j]);
                vecList.append(coordList);
            }

            return vecList;
        }


        // Useful helpers for python []-access
        template <typename EigenVectorType>
        void Vector_setElemAtIndexHelper(EigenVectorType* vec, int index, double value) {
            if(index >= EigenVectorType::RowsAtCompileTime || index < 0)
            {
                throw std::out_of_range("Vector access out of range.");
            }
            (*vec)[index] = value;
        }

        template <typename EigenVectorType>
        double Vector_getElemAtIndexHelper(EigenVectorType* vec, int index) {
            if(index >= EigenVectorType::RowsAtCompileTime || index < 0)
            {
                throw std::out_of_range("Vector access out of range.");
            }
            return (*vec)[index];
        }


        template <typename EigenVectorType>
        class EigenVector_iterator
                : public boost::iterator_facade<EigenVector_iterator<EigenVectorType>, double, boost::forward_traversal_tag> {
        public:
            EigenVector_iterator()
                    : vector_(nullptr),
                      position(EigenVectorType::RowsAtCompileTime) // Default constructor gives end iterator
            {}

            explicit EigenVector_iterator(EigenVectorType* vector)
            : vector_(vector),
              position(0)
                    {}

        private:
            EigenVectorType* vector_;
            unsigned int position;

            friend class boost::iterator_core_access;

            void increment() { position++; }

            bool equal(EigenVector_iterator const& other) const
            {
                return this->position == other.position;
            }

            double& dereference() const {
                if(position < EigenVectorType::RowsAtCompileTime) {
                    return (*vector_)[position];
                }else {
                    throw std::out_of_range("Vector iterator out of range");
                }
            }

        };

        template <typename EigenVectorType>
        EigenVector_iterator<EigenVectorType> Vector_begin(EigenVectorType& vec) {
            return EigenVector_iterator<EigenVectorType>(&vec);
        }

        template <typename EigenVectorType>
        EigenVector_iterator<EigenVectorType> Vector_end(EigenVectorType& vec) {
            return EigenVector_iterator<EigenVectorType>();
        }

        // Note: templating the *_toNPArray family of function leads runtime error :
        //       "TypeError: No to_python (by-value) converter found for C++ type: Eigen::Matrix<double, 3, 1, 0, 3, 1>::{unnamed type#2}"
        //       Not knowing how to fix this, one function for each type is written.
        np::ndarray Vector3d_toNPArray(Eigen::Vector3d* vec) {

            p::tuple shape = p::make_tuple(3, 1); // as row vector
            np::dtype dtype = np::dtype::get_builtin<double>();

            p::list vecAsPythonList = Vector_toList<Eigen::Vector3d>(vec);
            np::ndarray a = np::array(vecAsPythonList,dtype);
            return a;
        }

        np::ndarray Vector6d_toNPArray(Eigen::Vector6d* vec) {

            p::tuple shape = p::make_tuple(6, 1); // as row vector
            np::dtype dtype = np::dtype::get_builtin<double>();

            p::list vecAsPythonList = Vector_toList<Eigen::Vector6d>(vec);
            np::ndarray a = np::array(vecAsPythonList,dtype);
            return a;
        }

        std::shared_ptr<Eigen::Vector6d> Vector6d_ConstructorWrapper_default() {
            auto ret = std::make_shared<Eigen::Vector6d>();
            return ret;
        }

        std::shared_ptr<Eigen::Vector6d> Vector6d_ConstructorWrapper_values(double v0, double v1, double v2, double v3, double v4, double v5) {
            auto ret = std::make_shared<Eigen::Vector6d>();
            (*ret)[0] = v0;
            (*ret)[1] = v1;
            (*ret)[2] = v2;
            (*ret)[3] = v3;
            (*ret)[4] = v4;
            (*ret)[5] = v5;
            return ret;
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
                    .def("columnList", &Vector_toList<Eigen::Vector3d>)
                    .def("__iter__", p::range(&Vector_begin<Eigen::Vector3d>,&Vector_end<Eigen::Vector3d>))
                    .def("toNumpy", &Vector3d_toNPArray)
                    .def("_setElemAtIndex", &Vector_setElemAtIndexHelper<Eigen::Vector3d>)
                    .def("_getElemAtIndex", &Vector_getElemAtIndexHelper<Eigen::Vector3d>)
                    ;


            p::class_<Eigen::Vector6d, std::shared_ptr<Eigen::Vector6d>>("Vector6d", p::no_init)
                    // Some magic is required to implement the constructor as a wrapper (because Eigen doesn't define it)
                    .def("__init__", p::make_constructor(&Vector6d_ConstructorWrapper_values))
                    .def("__init__", p::make_constructor(&Vector6d_ConstructorWrapper_default))
                    .def("norm", &Eigen::Vector6d::norm)
                    .def("normalize", &Eigen::Vector6d::normalize)
                    .def("columnList", &Vector_toList<Eigen::Vector6d>)
                    .def("__iter__", p::range(&Vector_begin<Eigen::Vector6d>,&Vector_end<Eigen::Vector6d>))
                    .def("toNumpy", &Vector6d_toNPArray)
                    .def("_setElemAtIndex", &Vector_setElemAtIndexHelper<Eigen::Vector6d>)
                    .def("_getElemAtIndex", &Vector_getElemAtIndexHelper<Eigen::Vector6d>)
                    ;
        }

    }
}