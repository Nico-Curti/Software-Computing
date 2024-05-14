#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os

__author__ = 'Nico Curti'
__email__ = 'nico.curti2@unibo.it'

# absolute path of the current file
# NOTE: using the magic symbol __file__ you can
# ensure the correctness of this path in any location in
# which the script is called!
path = os.path.dirname(__file__)

try:

  # try to import the Cython submodules of the package
  from .hello import _HelloWorld as HelloWorld

except ImportError as e:

  import ctypes
  import warnings
  from glob import glob

  # all these issues can be solved setting the LD_LIBRARY_PATH env
  # variable to the correct path
  warnings.warn( (
    'Load of the dynamic library failed. '
    f'To avoid this issue you must add to the LD_LIBRARY_PATH the path:{path} '
    'Trying to solve this issue with a dynamic loading via ctypes '
    ),
    category=UserWarning
  )

  # set the library name
  # NOTE: you can change this line and re-use the entire
  # code (with the appropriated import...) in any other project
  LIBRARY_NAME = 'cython_utils'
  # search all the occurrences with that name in a library format
  LIBRARY_PATH = glob(f'{path}/*{LIBRARY_NAME}[.-]*')

  if len(LIBRARY_PATH) != 1:
    # there are multiple locations with the required name
    # or there are no location found
    raise ImportError('Failed to load the dynamic library')

  # get the first item of the list
  LIBRARY_PATH = LIBRARY_PATH[0]
  # load the dynamic library
  ctypes.cdll.LoadLibrary(LIBRARY_PATH)

  # now you can correctly perform the import
  from .hello import _HelloWorld as HelloWorld

