//
// Created by stevan on 8/17/20.
//

#include <boost/python.hpp>
#include <boost/python/implicit.hpp>

#include "clipper-py.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(_clipper_py)
{
    wrap_int_point();
    wrap_path();
    wrap_clipper();
}
