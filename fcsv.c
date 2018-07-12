#include <Python.h>


/**
 * Write a beautiful CSV
 */
static PyObject *
create (PyObject *self, PyObject *args)
{
    FILE *fp;
    char filename[] = "filename.csv";
    fp = fopen(filename,"w+");
    char delimiter[] = ",";
    
    PyObject* list_obj;
    PyObject* sequence;
    PyObject* first_row;

    if (!PyArg_ParseTuple(args, "O", &list_obj)) {
        return NULL;
    }

    sequence = PySequence_Fast(list_obj, "Expected a list object");
    int seq_size = PySequence_Size(list_obj);

    first_row = PySequence_Fast_GET_ITEM(sequence, 0);
    PyObject* header = PyDict_Keys(first_row);
    int key_count = PyList_Size(header);

    for (int j = 0; j < seq_size; j++) {
        if (j == 0) {
            for(int i = 0; i < key_count; i++) {
            PyObject* column = PyList_GetItem(header, i);
            if(PyUnicode_Check(column)) {
                PyObject* columnAscii = PyUnicode_AsASCIIString(column);

                fprintf(fp, "%s", PyBytes_AsString(columnAscii));
                Py_DECREF(columnAscii);

                if (i + 1 != key_count) {
                    fprintf(fp, "%s", delimiter);
                }
            }
        }
        fprintf(fp, "\n");
        }

        first_row = PySequence_Fast_GET_ITEM(sequence, j);
        PyObject* header = PyDict_Values(first_row);
        int key_count = PyList_Size(header);

        for(int i = 0; i < key_count; i++) {
            PyObject* column = PyList_GetItem(header, i);
            PyObject* columnAscii = PyUnicode_AsASCIIString(column);

            fprintf(fp, "%s", PyBytes_AsString(columnAscii));
            Py_DECREF(columnAscii);

            if (i + 1 != key_count) {
                fprintf(fp, "%s", delimiter);
            }
        }
        fprintf(fp, "\n");
    }
    Py_DECREF(sequence);
    Py_DECREF(list_obj);
    Py_DECREF(first_row);
    Py_DECREF(header);

    fclose(fp);
    return Py_BuildValue("s", filename);
}

static char create_docstring[] = "Creating faster CSV using Python but written in C";

/**
 * List of module methods
 */
static PyMethodDef module_methods[] = {
    {"create", (PyCFunction) create, METH_VARARGS, create_docstring},
    {NULL}
};

static struct PyModuleDef fcsv =
{
    PyModuleDef_HEAD_INIT,
    "fcsv",
    "usage: fcsv.create(dict, )\n",
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