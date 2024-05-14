# automatically fill the __version__.py script setting
# the variable defined as @VAR@
# NOTE: this is the standard way in which we can customize
# a script according to runtime build.
configure_file(
  "${CMAKE_SOURCE_DIR}/cython_hello_world/__version__.py.in"
  "${CMAKE_SOURCE_DIR}/cython_hello_world/__version__.py"
  @ONLY
)

# Include the *.pxd directory
include_directories("${CMAKE_SOURCE_DIR}/cython_hello_world/lib")

# add a new target for the Cython builder
# setting the language of the build as CXX
add_cython_target(hello CXX)

# add the Cython library, configuring it as a module
# of the resulting Python package
# NOTE: this line creates an association between the target
# and a new module with a custom name
add_library(hello MODULE "${hello}")
# setting the module for the final Python package
python_extension_module(hello)

# install the compiled Cython target in the same location
# of the final Python package
# NOTE: the resulting module will be built as a CXX library,
# so a binary file in fmt .so, .dll according to the OS
install(TARGETS hello LIBRARY DESTINATION cython_hello_world)
# dynamic link the Cython library to the pre-built CXX utility
# library
# NOTE: This line is very important for the correct usage of
# the final package and it requires a carefully management of
# the imports and environment variables!!
# (see cython_hello_world/__init__.py file for a detailed description
# of the issues and their possible workarounds...)
target_link_libraries(hello ${cython_utilslib})
