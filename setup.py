from distutils.core import setup
from distutils.core import Extension


setup(
    name='fcsv',
    version='1.0',
    ext_modules=[Extension('fcsv', ['fcsv.c'])]
)