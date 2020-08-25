CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)
PROJECT(polyclipping)

SET(CMAKE_BUILD_TYPE "Release" CACHE STRING "Release type")

include(GNUInstallDirs)

SET(PYTHON_SRC
        clipper/clipper.cpp
        clipper_py/clipper.cpp
        clipper_py/path.cpp
        clipper_py/int-point.cpp
        clipper_py/clipper-py.cpp)

FIND_PACKAGE(Boost REQUIRED COMPONENTS python3)
FIND_PACKAGE(Python3 COMPONENTS Development)

INCLUDE_DIRECTORIES(./clipper ./clipper_py ${Python3_INCLUDE_DIRS} ${Boost_INCLUDE3_DIRS} )
ADD_LIBRARY(clipper_py SHARED ${PYTHON_SRC})
SET_TARGET_PROPERTIES(clipper_py PROPERTIES PREFIX "_")
TARGET_LINK_LIBRARIES(clipper_py PUBLIC ${Python3_LIBRARY_DIRS} ${Boost_PYTHON3_LIBRARY})