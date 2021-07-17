#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "algo1.hpp"
#include "numpy/arrayobject.h"

static PyObject *extnp_wrapper(PyObject *self, PyObject *args)
{
    PyObject *in = NULL, *out = NULL;
    PyObject *arr = NULL, *outArr = NULL;
    double k;

    // "O": Store a Python object (without any conversion) in a C object pointer.
    //      The C program thus receives the actual object that was passed.
    //      The object’s reference count is not increased. The pointer stored is not NULL.
    // "d": Convert a Python floating point number to a C double
    if (!PyArg_ParseTuple(args, "OOd", &in, &out, &k))
        return NULL;

    arr = PyArray_FROM_OTF(in, NPY_DOUBLE, NPY_ARRAY_IN_ARRAY);
    if (arr == NULL)
        return NULL;

#if NPY_API_VERSION >= 0x0000000c
    outArr = PyArray_FROM_OTF(out, NPY_DOUBLE, NPY_ARRAY_INOUT_ARRAY2);
#else
    outArr = PyArray_FROM_OTF(out, NPY_DOUBLE, NPY_ARRAY_INOUT_ARRAY);
#endif
    if (outArr == NULL)
    {
        Py_XDECREF(arr);
        Py_XDECREF(outArr);
        return NULL;
    }

    // For demo purpose, copy the data from input numpy array into a vector
    // and use an instance of the ExampleClass to perform mutiplication
    std::vector<double> data;
    for (size_t i = 0; i < PyArray_DIM(arr, 0); i++)
        data.push_back(*(double *)PyArray_GETPTR1(arr, i));

    auto ec = ExampleClass();
    ec.multiply(data, k);

    // write the result to the output array
    for (size_t i = 0; i < data.size(); i++)
        PyArray_SETITEM(outArr,
                        PyArray_GETPTR1(outArr, i),
                        PyFloat_FromDouble(data[i]));

    Py_DECREF(arr);
    Py_DECREF(outArr);

    Py_INCREF(Py_None);
    return Py_None;
};

// All methods in the module
static PyMethodDef extnp_methods[] = {
    {
        "multiply_by",                              // method name exposed to Python
        extnp_wrapper,                              // wrapper function
        METH_VARARGS,                               // varargs flag
        "multiply all elements in an 1d array by k" // docstring
    },
    {NULL, NULL, 0, NULL}};

// Define the module
static struct PyModuleDef extnpModule = {
    PyModuleDef_HEAD_INIT,
    "algo1",      // module name
    "Algorithms", // docstring
    -1,
    extnp_methods // module methods
};

// Module initializer PyInit_{name} where name has to be the module name
PyMODINIT_FUNC PyInit_algo1_ext()
{
    import_array(); // required to init Numpy API
    return PyModule_Create(&extnpModule);
}
