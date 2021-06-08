//
// Created by stevan on 8/18/20.
//

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/implicit.hpp>

#include "clipper-py.h"

#include "../clipper/clipper.hpp"

using namespace boost::python;

inline const char* const BoolToString(bool b)
{
    return b ? "True" : "False";
}

namespace PolyNode {
    bool is_open(ClipperLib::PolyNode const &node)
    {
        return node.IsOpen();
    }

    bool is_hole(ClipperLib::PolyNode const &node)
    {
        return node.IsHole();
    }

    int child_count(ClipperLib::PolyNode const &node)
    {
        return node.ChildCount();
    }

    ClipperLib::PolyNode get_next(ClipperLib::PolyNode const &node)
    {
        return *node.GetNext();
    }

    ClipperLib::PolyNodes childs(ClipperLib::PolyNode const &node)
    {
        return node.Childs;
    }

    ClipperLib::PolyNode parent(ClipperLib::PolyNode const &node)
    {
        return *node.Parent;
    }

    ClipperLib::Path contour(ClipperLib::PolyNode const &node)
    {
        return node.Contour;
    }

    str repr(ClipperLib::PolyNode const &node)
    {
        // TODO: repond with something better here
        return str("PolyNode(  )");
    }
}

namespace PolyTree {
    ClipperLib::PolyNode get_first(ClipperLib::PolyTree const &tree)
    {
        return *tree.GetFirst();
    }

    int total(ClipperLib::PolyTree const &tree)
    {
        return tree.Total();
    }
}

namespace PolyNodes {
    str repr(ClipperLib::PolyNodes const &nodes)
    {
        return str("PolyNodes( size=" + str(nodes.size()) + " )");
    }
}

void wrap_poly_tree()
{
    class_<ClipperLib::PolyNode>("PolyNode")
            .def("__str__", PolyNode::repr)
            .def("__repr__", PolyNode::repr)
            .add_property("contour", PolyNode::contour)
            .add_property("childs", PolyNode::childs)
            .add_property("parent", PolyNode::parent)
            .def("child_count", PolyNode::child_count)
            .def("is_open", PolyNode::is_open)
            .def("is_hole", PolyNode::is_hole)
            .def("get_next", PolyNode::get_next);

    class_<ClipperLib::PolyNodes>("PolyNodes")
            .def(vector_indexing_suite<ClipperLib::PolyNodes>())
            .def("__str__", PolyNodes::repr)
            .def("__repr__", PolyNodes::repr);

    class_<ClipperLib::PolyTree>("PolyTree")
            .def("__str__", PolyNode::repr)
            .def("__repr__", PolyNode::repr)
            .add_property("contour", PolyNode::contour)
            .add_property("childs", PolyNode::childs)
            .add_property("parent", PolyNode::parent)
            .def("child_count", PolyNode::child_count)
            .def("is_open", PolyNode::is_open)
            .def("is_hole", PolyNode::is_hole)
            .def("get_next", PolyNode::get_next)
            .def("get_first", PolyTree::get_first)
            .def("total", PolyTree::total);
}
