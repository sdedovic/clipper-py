//
// Created by stevan on 8/18/20.
//

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/implicit.hpp>

#include "clipper-py.h"

#include "../clipper/clipper.hpp"

using namespace boost::python;

namespace Path {
    ClipperLib::Path push(ClipperLib::Path &path, ClipperLib::IntPoint const &point)
    {
        path << point;
        return path;
    }

    str repr(ClipperLib::Path const &path)
    {
        str string = "Path( ";
        for (int i = 0; i < path.size(); i++) {
            ClipperLib::IntPoint point = path[i];
            str point_str =  str("[" + str(point.X) + ", " +  str(point.Y) + "]");
            string += (str("[" + str(path[i].X) + ","));
        }
        return str("Path( size=" + str(path.size()) + " )");
    }
}

namespace Paths {
    ClipperLib::Paths push(ClipperLib::Paths &paths, ClipperLib::Path const &path)
    {
        paths << path;
        return paths;
    }

    str repr(ClipperLib::Paths const &paths)
    {
        return str("Paths( size=" + str(paths.size()) + " )");
    }
}

void wrap_path()
{
    class_<ClipperLib::Path>("Path")
            .def(vector_indexing_suite<ClipperLib::Path>())
            .def("__str__", Path::repr)
            .def("__repr__", Path::repr)
            .def("push", Path::push);

    class_<ClipperLib::Paths>("Paths")
            .def(vector_indexing_suite<ClipperLib::Paths>())
            .def("__str__", Paths::repr)
            .def("__repr__", Paths::repr)
            .def("push", Paths::push);
}
