"""
Copyright (c) 2016 The Pybind Development Team, All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors
   may be used to endorse or promote products derived from this software
   without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

You are under no obligation whatsoever to provide any bug fixes, patches, or
upgrades to the features, functionality or performance of the source code
("Enhancements") to anyone; however, if you choose to make your Enhancements
available either publicly, or directly to the author of this software, without
imposing a separate written license agreement for such Enhancements, then you
hereby grant the following license: a non-exclusive, royalty-free perpetual
license to install, use, modify, prepare derivative works, incorporate into
other computer software, distribute, and sublicense such enhancements or
derivative works thereof, in binary and source code form.
"""

import os
import sys
import platform
import subprocess
import re
import ast

from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext


class CMakeExtension(Extension):
    def __init__(self, name, sourcedir=''):
        Extension.__init__(self, name, sources=[])
        self.sourcedir = os.path.abspath(sourcedir)


class CMakeBuild(build_ext):
    def run(self):
        try:
            out = subprocess.check_output(['cmake', '--version'])
        except OSError:
            raise RuntimeError("CMake must be installed to build the following extensions: " +
                               ", ".join(e.name for e in self.extensions))

        if platform.system() == "Windows":
            raise RuntimeError("Windows is not supported")

        for ext in self.extensions:
            self.build_extension(ext)

    def build_extension(self, ext):
        extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))
        # required for auto-detection of auxiliary "native" libs
        if not extdir.endswith(os.path.sep):
            extdir += os.path.sep

        cmake_args = ['-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=' + extdir,
                      '-DPYTHON_EXECUTABLE=' + sys.executable]

        cfg = 'Debug' if self.debug else 'Release'
        build_args = ['--config', cfg]

        if platform.system() == "Windows":
            raise RuntimeError("Windows is not supported")
        else:
            cmake_args += ['-DCMAKE_BUILD_TYPE=' + cfg]
            build_args += ['--', '-j2']

        env = os.environ.copy()
        env['CXXFLAGS'] = '{} -DVERSION_INFO=\\"{}\\"'.format(env.get('CXXFLAGS', ''),
                                                              self.distribution.get_version())
        if not os.path.exists(self.build_temp):
            os.makedirs(self.build_temp)
        subprocess.check_call(['cmake', ext.sourcedir] + cmake_args, cwd=self.build_temp, env=env)
        subprocess.check_call(['cmake', '--build', '.'] + build_args, cwd=self.build_temp)


with open("README.md", "r", encoding='utf-8') as readme:
    long_description = readme.read()

with open('clipper_py/__init__.py', 'rb') as f:
    _file = f.read().decode('utf-8')
    _version_re = re.compile(r'__version__\s+=\s+(.*)')
    version = str(ast.literal_eval(_version_re.search(_file).group(1)))


def get_cpp(path):
    import os
    return [os.path.join(path, name) for path, subdirs, files in os.walk(path) for name in files if
            name.endswith('.cpp') or name.endswith('.hpp') or name.endswith('.h')]


setup(
    name='clipper-py',
    version=version,
    author='Stevan Dedovic',
    author_email='stevan@dedovic.com',
    description='Python Bindings for Clipper using Boost.Python',
    long_description=long_description,
    long_description_content_type="text/markdown",
    keywords='clipper polygon clipping polygon-clipping',
    url="https://github.com/sdedovic/clipper-py",
    project_urls={
        "Bug Tracker": "https://github.com/sdedovic/clipper-py/issues",
        "Documentation": "https://github.com/sdedovic/clipper-py",
        "Source Code": "https://github.com/sdedovic/clipper-py",
    },
    classifiers=["Development Status :: 3 - Alpha",
                 "Environment :: Other Environment",
                 "Intended Audience :: Developers",
                 "Operating System :: POSIX :: Linux",
                 "Programming Language :: C++",
                 "Programming Language :: Python :: 3 :: Only",
                 "License :: OSI Approved",
                 "License :: OSI Approved :: MIT License",
                 "Topic :: Multimedia :: Graphics",
                 "Topic :: Artistic Software",
                 "Topic :: Scientific/Engineering :: Mathematics",
                 "Topic :: Software Development :: Libraries :: Python Modules"
                 ],
    packages=['clipper_py'],
    ext_modules=[CMakeExtension('clipper_py')],
    data_files=[('clipper', get_cpp('clipper')),
                ('clipper_py', get_cpp('clipper_py')),
                ('', ['polyclipping.pc.cmakein', 'CMakeLists.txt'])],
    cmdclass=dict(build_ext=CMakeBuild),
    zip_safe=False,
)
