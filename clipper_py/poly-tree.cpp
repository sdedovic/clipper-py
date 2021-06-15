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

    ClipperLib::PolyNode *get_next(ClipperLib::PolyNode const &node)
    {
        return node.GetNext();
    }

    ClipperLib::PolyNodes childs(ClipperLib::PolyNode const &node)
    {
        return node.Childs;
    }

    ClipperLib::PolyNode *parent(ClipperLib::PolyNode const &node)
    {
        return node.Parent;
    }

    ClipperLib::Path contour(ClipperLib::PolyNode const &node)
    {
        return node.Contour;
    }

    std::string to_string(ClipperLib::PolyNode const &node)
    {
        std::string value = std::string();

        value += "PolyNode(";
        value += "child_count=" + std::to_string(child_count(node)) + " ";
        value += "is_open=" + std::to_string(is_open(node)) + " ";
        value += "is_hole=" + std::to_string(is_hole(node));
        value += ")";

        return value;
    }

    str repr(ClipperLib::PolyNode const &node)
    {
        return str(to_string(node));
    }
}

namespace PolyTree {
    ClipperLib::PolyNode *get_first(ClipperLib::PolyTree const &tree)
    {
        return tree.GetFirst();
    }

    int total(ClipperLib::PolyTree const &tree)
    {
        return tree.Total();
    }

    std::string to_string(ClipperLib::PolyTree const &tree)
    {
        std::string value = std::string();

        value += "PolyTree(";
        value += "child_count=" + std::to_string(PolyNode::child_count(tree)) + " ";
        value += "is_open=" + std::to_string(PolyNode::is_open(tree)) + " ";
        value += "is_hole=" + std::to_string(PolyNode::is_hole(tree));
        value += ")";

        return value;
    }

    str repr(ClipperLib::PolyTree const &tree)
    {
        return str(to_string(tree));
    }
}

namespace PolyNodes {
    str repr(ClipperLib::PolyNodes const &nodes)
    {
        return str(str("PolyNodes( size=") + str(nodes.size()) + str(" )"));
    }
}

void wrap_poly_tree()
{
    class_<ClipperLib::PolyNode, std::shared_ptr<ClipperLib::PolyNode> >("PolyNode")
            .def("__str__", PolyNode::repr)
            .def("__repr__", PolyNode::repr)
            .add_property("contour", PolyNode::contour)
            .add_property("childs", PolyNode::childs)
            .add_property("parent", make_function(PolyNode::parent, return_internal_reference<>()))
            .def("child_count", PolyNode::child_count)
            .def("is_open", PolyNode::is_open)
            .def("is_hole", PolyNode::is_hole)
            .def("get_next", PolyNode::get_next, return_internal_reference<>());

    class_<ClipperLib::PolyNodes>("PolyNodes")
            .def(vector_indexing_suite<ClipperLib::PolyNodes>())
            .def("__str__", PolyNodes::repr)
            .def("__repr__", PolyNodes::repr);

    class_<ClipperLib::PolyTree, std::shared_ptr<ClipperLib::PolyTree>, bases<ClipperLib::PolyNode> >("PolyTree")
            .def("__str__", PolyTree::repr)
            .def("__repr__", PolyTree::repr)
            .def("get_first", PolyTree::get_first, return_internal_reference<>())
            .def("total", PolyTree::total);
}
