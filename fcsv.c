#include <Python.h>


/**
 * Write a beautiful CSV
 */
static PyObject *
create (PyObject *self)
{
    return Py_BuildValue("s", "Hello Pythonista");
}

static char create_docstring[] = "Creating faster CSV using Python but written in C";

/**
 * List of module methods
 */
static PyMethodDef module_methods[] = {
    {"create", (PyCFunction) create, METH_NOARGS, create_docstring},
    {NULL}
};

static struct PyModuleDef fcsv =
{
    PyModuleDef_HEAD_INIT,
    "fcsv",
    "usage: fcsv.create()\n",
    -1,   /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    module_methods
};

/**
 * Module inicialization function
 */
PyMODINIT_FUNC
PyInit_fcsv(void)
{
    return PyModule_Create(&fcsv);
}