# About
[![](https://github.com/sdedovic/clipper-py/workflows/Publish%20to%20PyPI/badge.svg)](#)
[![](https://img.shields.io/pypi/v/clipper-py)](https://pypi.org/project/clipper-py/)

clipper-py is a Boost.Python wrapper exposing the C++ translation of the [Angus Johnson's Clipper library](http://angusj.com/delphi/clipper.php) (6.4 Rev 495).

clipper-py is tested and built against Python 3.8 on Arch Linux.

**This project is very much a work-in-progress. Please contribute.**

## About Clipper
> Clipper - an open source freeware library for clipping and offsetting lines and polygons.
>
> The Clipper library performs line & polygon clipping - intersection, union, difference & exclusive-or, and line & polygon offsetting. The library is based on Vatti's clipping algorithm.
>
> Angus Johnson's Clipper library

# Install
## Dependencies
### Linux
- Boost.Python Headers (`libboost-python-dev`) compiled against version `1.67.0`
#### Debian, Ubuntu
```bash
apt-get install libboost-python-dev
```
#### Arch
```bash
pacman -S libboost-python-dev
```
### Mac
#### Homebrew
```bash
brew install boost-python3
```

## From PyPI
```bash
pip install clipper-py
```

## From source
CMake required.

### Install:
```bash
pip3 install .
```

# Usage
##  Basic clipping example (based on Angus Johnson's Clipper library):
```python
from clipper_py import Path, Paths, Clipper, IntPoint

subj = Paths()
subj.push(Path().push(IntPoint(180, 200)).push(IntPoint(260, 200)).push(IntPoint(260, 150)).push(IntPoint(180, 150)))
subj.push(Path().push(IntPoint(215, 160)).push(IntPoint(230, 190)).push(IntPoint(200, 190)))
print(subj, subj[0], subj[1])

clip = Paths()
clip.push(Path().push(IntPoint(190, 210)).push(IntPoint(240, 210)).push(IntPoint(240, 130)).push(IntPoint(190, 130)))
print(clip, clip[0])

clipper = Clipper(0)
clipper.add_paths(subj, 'subject', True)
clipper.add_paths(clip, 'clip', True)
solution = clipper.execute('intersection', 'non-zero', 'non-zero')

# solution: [[[240, 200], [190, 200], [190, 150], [240, 150]], [[200, 190], [230, 190], [215, 160]]]
```

# Authors
- The Clipper library is written by Angus Johnson,
- This readme was modified from the original written by various authors of the pyclipper library
- The PyPI `setup.py` file was modified from a CMake-based build example of the PyBind project

# License
- clipper-py is available under a [MIT license](http://opensource.org/licenses/MIT).
- Pyclipper is available under a [MIT license](http://opensource.org/licenses/MIT).
- The core Clipper library is available under a [Boost Software License](http://www.boost.org/LICENSE_1_0.txt). Freeware for both open source and commercial applications.
- cmake_example by Pybind is available under a [BSD-style license](https://github.com/pybind/cmake_example/blob/master/LICENSE)

# Changelog
## 0.1.3
- Dynamically determine version of Python for Boost.Python headers
- Minor cleanup

## 0.1.2
- Get MacOS builds working
- Make things a little bit more portable on Linux

## 0.1.0
- update `setup.py` with urls
- Publish to PyPI

## 0.0.1
Initial project setup.
