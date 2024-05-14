# distutils: language = c++
# cython: language_level=2

# import the wrapped Cython type from the
# cython std library
from libcpp.string cimport string

# define the import of the CXX functions from the
# header files, following the syntax:
#
# cdef extern from "header.h" [namespace "std"] [nogil]:

cdef extern from "hello.h" namespace "test" nogil:

  string HelloWorld (const string & name) except +;
