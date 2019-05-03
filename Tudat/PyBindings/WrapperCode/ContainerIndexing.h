/*    Copyright (c) 2010-2019, Delft University of Technology
 *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 */

#ifndef TUDAT_PYBINDINGS_CONTAINERINDEXING_H
#define TUDAT_PYBINDINGS_CONTAINERINDEXING_H


#include <exception>
#include <stdexcept>

namespace tudat {
    namespace PyBindings_internal {
        template<class T>
        struct MinimalMapIndexing
        {
            typedef typename T::key_type K;
            typedef typename T::mapped_type V;
            static V& get(T & x, K const& i)
            {
                if( x.find(i) != x.end() ) return x[i];
                throw std::runtime_error("Key not in map");
            }
            static void set(T & x, K const& i, V const& v)
            {
                x[i]=v; // use map autocreation feature
            }
            static void del(T & x, K const& i)
            {
                if( x.find(i) != x.end() ) x.erase(i);
                else
                    throw std::runtime_error("Key not in map");
            }
        };
    }
}



#endif //TUDAT_PYBINDINGS_CONTAINERINDEXING_H
