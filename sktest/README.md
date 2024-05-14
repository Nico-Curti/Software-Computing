# Scikit-Build + Cython MWE

Dummy example for the usage of *scikit-build* library combined with *cython* C++ wrap.

| :warning: WARNING |
|:------------------|
| The installation path of the `cython_utils` library (aka the original CXX function declaration library) is set to the same path of the Cython library. It must be manually included to the `LD_LIBRARY_PATH` for the correct import of the module! We have scheduled a workaround in the `__init__.py` script adding messages also in the `setup.py` script, but it remains an open issue |

### How to build

```bash
cd sktest
python -m pip install . -v
```

### How to deploy the package to Pypi

```bash
cd sktest
sudo apt install python3.10-venv
python -m pip install --upgrade build
python -m build
python -m pip install --upgrade twine
python -m twine upload --repository sktest dist/*
```
