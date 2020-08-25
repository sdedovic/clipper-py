//
// Created by stevan on 8/18/20.
//

#include <boost/python.hpp>
#include <boost/python/implicit.hpp>

#include "clipper-py.h"

#include "../clipper/clipper.hpp"

using namespace boost::python;

namespace Clipper {
    ClipperLib::PolyFillType polyFillType_from_str(std::string const &polyFillType)
    {
        if (polyFillType == "even-odd") return ClipperLib::pftEvenOdd;
        else if (polyFillType == "non-zero") return ClipperLib::pftNonZero;
        else if (polyFillType == "positive") return ClipperLib::pftPositive;
        else if (polyFillType == "negative") return ClipperLib::pftNegative;
    }

    ClipperLib::ClipType clipType_from_str(std::string const &clipType)
    {
        if (clipType == "intersection") return ClipperLib::ctIntersection;
        else if (clipType == "union") return ClipperLib::ctUnion;
        else if (clipType == "difference") return ClipperLib::ctDifference;
        else if (clipType == "xor") return ClipperLib::ctXor;
    }

    ClipperLib::PolyType polyType_from_str(std::string const &polyType)
    {
        if (polyType == "subject") return ClipperLib::ptSubject;
        else if (polyType == "clip") return ClipperLib::ptClip;
    }

    // helpers for point
    bool add_paths(ClipperLib::Clipper &clipper, ClipperLib::Paths const &paths, std::string const &polyType, bool closed)
    {
        const ClipperLib::PolyType pt = polyType_from_str(polyType);
        return clipper.AddPaths(paths, pt, closed);
    }

    ClipperLib::Paths execute(ClipperLib::Clipper &clipper, std::string const &clipType, std::string const &subjFillType, std::string const &clipFillType)
    {
        ClipperLib::ClipType ct = clipType_from_str(clipType);
        ClipperLib::PolyFillType sft = polyFillType_from_str(subjFillType);
        ClipperLib::PolyFillType cft = polyFillType_from_str(clipFillType);
        ClipperLib::Paths solution;

        clipper.Execute(ct, solution, sft, cft);

        return solution;
    }
}

void wrap_clipper()
{
    class_<ClipperLib::TEdge>("TEdge");
    class_<ClipperLib::LocalMinimum>("LocalMinimum");
    class_<ClipperLib::ClipperBase>("ClipperBase");
    class_<ClipperLib::Clipper, bases<ClipperLib::ClipperBase>>("Clipper", init<int>())
            .def("add_paths", Clipper::add_paths)
            .def("execute", Clipper::execute);
}