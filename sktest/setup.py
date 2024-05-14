#!/usr/bin/env python
# -*- coding: utf-8 -*-

import warnings
from skbuild import setup

PACKAGE_NAME = 'cython_hello_world'
AUTHOR = 'Nico Curti'
EMAIL = 'nico.curti2@unibo.it'
REQUIRES_PYTHON = '>=3.5'
KEYWORDS = 'scikit-build cython examples dummy'
PACKAGE_VERSION = '0.0.1'
DESCRIPTION = 'MWE for Cython build with scikit-build support'

setup(
    name=PACKAGE_NAME,
    version=PACKAGE_VERSION,
    description=DESCRIPTION,
    author=AUTHOR,
    author_email=EMAIL,
    maintainer=AUTHOR,
    maintainer_email=EMAIL,
    python_requires=REQUIRES_PYTHON,
    install_requires=[],
    url='localhost/sktest',
    download_url='',
    keywords=KEYWORDS,
    setup_requires=[],
    packages=[PACKAGE_NAME,],
    package_data={
      PACKAGE_NAME: [
        '__version__.py.in',
      ],
    },
    include_package_data=True,
    platforms='any',
    classifiers=[
      'Natural Language :: English',
      'Operating System :: MacOS :: MacOS X',
      'Operating System :: POSIX',
      'Operating System :: POSIX :: Linux',
      'Operating System :: Microsoft :: Windows',
      'Programming Language :: Python',
      'Programming Language :: Python :: 3',
      'Programming Language :: Python :: 3.5',
      'Programming Language :: Python :: 3.6',
      'Programming Language :: Python :: 3.7',
      'Programming Language :: Python :: 3.8',
      'Programming Language :: Python :: Implementation :: CPython',
      'Programming Language :: Python :: Implementation :: PyPy'
    ],
    license='MIT',
    cmake_install_dir='',
    cmake_args=[
      '-DCMAKE_BUILD_TYPE:STRING=Release',
      f'-DPACKAGE_VERSION:STRING={PACKAGE_VERSION}',
      f'-DCMAKE_PROJECT_DESCRIPTION:STRING={DESCRIPTION}',
    ],
)

warnings.warn( (
  'Dynamic libraries added to the installation path. '
  'Please add to the LD_LIBRARY_PATH the current installation path to avoid '
  'possible ImportError exception '
  ),
  category=UserWarning
)
