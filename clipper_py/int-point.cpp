//
// Created by stevan on 8/17/20.
//

#include <boost/python.hpp>
#include <boost/python/implicit.hpp>

#include "clipper-py.h"

#include "../clipper/clipper.hpp"

using namespace boost::python;

namespace IntPoint {
    // helpers for point
    tuple point_to_tuple(ClipperLib::IntPoint const &p)
    {
        return make_tuple(p.X, p.Y);
    }

    ClipperLib::IntPoint tuple_to_point(boost::python::tuple const &t)
    {
        return ClipperLib::IntPoint(extract<int>(t[0]), extract<int>(t[1]));
    }

    str repr(ClipperLib::IntPoint const &p)
    {
        return boost::python::str("[" + boost::python::str(p.X) + ", " + boost::python::str(p.Y) + "]");
    }

    int get_item(ClipperLib::IntPoint const &p, int index)
    {
        if (index == 0) return p.X;
        else if (index == 1) return p.Y;
        else {
            PyErr_SetString(PyExc_IndexError, "index out of range");
            boost::python::throw_error_already_set();
        }
    }
}

void wrap_int_point()
{
    class_<ClipperLib::IntPoint>("IntPoint", init<int, int>())
            .def("__str__", IntPoint::repr)
            .def("__repr__", IntPoint::repr)
            .def("__getitem__", IntPoint::get_item)
            .def("tuple", IntPoint:: point_to_tuple);
    implicitly_convertible<ClipperLib::IntPoint,tuple>();
}