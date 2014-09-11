from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize
from glob import glob

py_libconfig = Extension ('py_libconfig',
        ['py_libconfig.pyx'] + glob ('../libconfig/*.c'))

setup (ext_modules = cythonize ([py_libconfig]))
