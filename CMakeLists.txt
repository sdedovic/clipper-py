CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)
PROJECT(polyclipping)

IF (APPLE)
    INCLUDE(GNUInstallDirs)
    SET(CMAKE_MACOSX_RPATH FALSE)
    SET(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
ELSEIF(UNIX)
    include(GNUInstallDirs)
ENDIF()

SET(PYTHON_SRC
        clipper/clipper.cpp
        clipper_py/clipper.cpp
        clipper_py/path.cpp
        clipper_py/int-point.cpp
        clipper_py/clipper-py.cpp)

FIND_PACKAGE(Boost 1.60.0 REQUIRED)
FIND_PACKAGE(Boost REQUIRED COMPONENTS python38)
FIND_PACKAGE(Python3 COMPONENTS Development)

INCLUDE_DIRECTORIES(./clipper ./clipper_py ${Python3_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
ADD_LIBRARY(clipper_py SHARED ${PYTHON_SRC})
SET_TARGET_PROPERTIES(clipper_py PROPERTIES PREFIX "_")

TARGET_LINK_LIBRARIES(clipper_py PUBLIC ${Python3_LIBRARIES} ${Boost_LIBRARIES})