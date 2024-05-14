# distutils: language = c++
# cython: language_level=2

# import the declaration of the CXX function
# from the pxd header file
from hello cimport HelloWorld

__author__ = ['Nico Curti']
__email__ = ['nico.curti2@unibo.it']

# NOTE: the typing of the input variables
# and returns boosts the efficiency of the
# Cython wrap! Use it as much as possible...

def _HelloWorld (str name) -> str:
  '''
  Dummy function in Cython to wrap
  C++ interface.

  Parameters
  ----------
    name : str
      Name to hello.

  Returns
  -------
    msg : str
      Hello message with name
  '''

  # NOTE: the management of the string between
  # Cython and CXX is not straightforward!
  # For the correct forward/backward transmission
  # you need to convert them in Bytes using the
  # correct encoding... (std way is utf-8 fmt)
  cdef bytes _name = name.encode('utf-8')
  cdef bytes res = HelloWorld(_name)

  return res.decode('utf-8')
