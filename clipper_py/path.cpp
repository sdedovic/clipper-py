//
// Created by stevan on 8/18/20.
//

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include "clipper-py.h"

#include "../clipper/clipper.hpp"

using namespace boost::python;

namespace Path {
    ClipperLib::Path push(ClipperLib::Path &path, ClipperLib::IntPoint const &point)
    {
        path << point;
        return path;
    }

    std::string to_string(const ClipperLib::Path& path) {
        if (path.empty())
            return "Path(EMPTY)";

        std::string value = std::string();
        value += "Path(";
        for( int i = 0; i < path.size() - 1; i++) {
            ClipperLib::IntPoint point = path.at(i);
            std::string x = std::to_string(point.X);
            std::string y = std::to_string(point.Y);
            value += "[";
            value += x;
            value += ",";
            value += y;
            value += "], ";
        }
        ClipperLib::IntPoint point = path.at(path.size() - 1);
        std::string x = std::to_string(point.X);
        std::string y = std::to_string(point.Y);
        value += "[";
        value += x;
        value += ",";
        value += y;
        value += "]";

        value += ")";
        return value;
    }

    str repr(const ClipperLib::Path& path)
    {
        return str(to_string(path));
    }
}

namespace Paths {
    ClipperLib::Paths push(ClipperLib::Paths &paths, ClipperLib::Path const &path)
    {
        paths << path;
        return paths;
    }

    std::string to_string(const ClipperLib::Paths& paths) {
        if (paths.empty())
            return "Paths(EMPTY)";

        std::string value = std::string();
        value += "Paths(";
        for (int i = 0; i < paths.size() - 1; i++)
        {
            value += Path::to_string(paths.at(i));
            value += ", ";
        }
        value += Path::to_string(paths.at(paths.size() - 1));

        value += ")";
        return value;
    }

    str repr(ClipperLib::Paths const &paths)
    {
        return str(to_string(paths));
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
