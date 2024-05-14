cmake_minimum_required(VERSION 3.18.22)

# NOTE: the variable PACKAGE_VERSION and CMAKE_PROJECT_DESCRIPTION
# are fed by the command line built by the setup.py script
project(cython_hello
  LANGUAGES CXX
  VERSION ${PACKAGE_VERSION}
  DESCRIPTION ${CMAKE_PROJECT_DESCRIPTION}
)
enable_language(C) # this is mandatory for scikit-build check
enable_language(CXX)

# add to the path a location in which look for .cmake files
# NOTE: this kind of files is useful for the correct search
# of the libraries and other required packages
set(CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/"
    ${CMAKE_MODULE_PATH}
)

# set the suffix for debug libraries
set(CMAKE_DEBUG_POSTFIX d)

# mandatory script of the build
find_package(Cython REQUIRED)
find_package(PythonExtensions REQUIRED)

# get the full list of scripts to build
file(GLOB SOURCE_CXX  "${CMAKE_CURRENT_LIST_DIR}/src/*.cxx"  )
file(GLOB HEADER_CXX  "${CMAKE_CURRENT_LIST_DIR}/include/*.h")
file(GLOB HPP_CXX     "${CMAKE_CURRENT_LIST_DIR}/hpp/*.hpp"  )

# add the include directory to the list of paths in which
# look for the -I cmd
include_directories("${CMAKE_SOURCE_DIR}/include")

# set the name of the utils library to build
# NOTE: the utils library in this case stores
# all the CXX scripts wrapped by Cython
set (cython_utilslib cython_utils)

# add the library to the list of builds, including
# all the .cxx, .h, .hpp files as dependencies
add_library(${cython_utilslib}
  SHARED
  ${SOURCE_CXX} ${HEADER_CXX} ${HPP_CXX}
)

# install the cython_utils library in the same location
# of the final Python package
# (e.g. /.local/lib/python3.10/site-packages/cython_hello_world)
install(TARGETS ${cython_utilslib}
  LIBRARY DESTINATION cython_hello_world
  RUNTIME DESTINATION cython_hello_world
)

# move to the cython CMakeFile sub-directory
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/cython_hello_world/source")
