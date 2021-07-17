# python-cpp-extension-numpy
 
This repo presents a minimal example of developing a C/C++ extension in a Python package `extnp`, which performs some calculations on Numpy arrays.

```
|extnp                  # Python module
|--|algo                # submodule
|--|--|src              # C/C++ source files
|--|--|--algo1.hpp
|--|--|--wrapper.cpp
|--|--__init__.py
|--__init__.py
|--setup.py
```

## Example

First, build and install the package.

```
python setup.py build_ext --inplace
pip install .
```

Then, try it out:

```Python
>>> from extnp.algo import cpp_multiply, py_multiply
>>> import numpy as np
>>> data = np.array([i for i in range(100)], dtype=np.double)
>>> cpp_multiply(data, k=2)
array([  0.,   2.,   4.,   6.,   8.,  10.,  12.,  14.,  16.,  18.,  20.,
        22.,  24.,  26.,  28.,  30.,  32.,  34.,  36.,  38.,  40.,  42.,
        44.,  46.,  48.,  50.,  52.,  54.,  56.,  58.,  60.,  62.,  64.,
        88.,  90.,  92.,  94.,  96.,  98., 100., 102., 104., 106., 108.,
       110., 112., 114., 116., 118., 120., 122., 124., 126., 128., 130.,
       132., 134., 136., 138., 140., 142., 144., 146., 148., 150., 152.,
       154., 156., 158., 160., 162., 164., 166., 168., 170., 172., 174.,
       176., 178., 180., 182., 184., 186., 188., 190., 192., 194., 196.,
       198.])
>>> np.array_equal(cpp_multiply(data,2), py_multiply(data,2))
True
```

## Note

In `extnp.algo` there are two functions to multiply all elements in the Numpy array by `k`:

* `cpp_multiply`: a wrapper that calls the C++ function to perform the multiplication
* `py_multiply`: a simple python function to do the same thing

Check [extnp/algo/src/wrapper.cpp](https://github.com/mgao6767/python-cpp-extension-numpy/blob/main/extnp/algo/src/wrapper.cpp) for details.