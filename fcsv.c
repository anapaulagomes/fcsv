#include <Python.h>


/**
 * Write a beautiful CSV
 */
static PyObject *
create (PyObject *self, PyObject *args)
{
    FILE *fp;
    fp=fopen("filename2.csv","w+");
    
    PyObject* list_obj;
    PyObject* sequence;
    // PyObject* item; // row
    PyObject* first_row;

    if (!PyArg_ParseTuple(args, "O", &list_obj)) {
        return NULL;
    }

    sequence = PySequence_Fast(list_obj, "Expected a list object");
    // lista aqui
    int seq_size = PySequence_Size(list_obj);

    printf("-----======= %d\n", seq_size);

    first_row = PySequence_Fast_GET_ITEM(sequence, 0); // pega o primeiro dict
    PyObject* header = PyDict_Keys(first_row); // pega as keys desse dict
    int key_count = PyList_Size(header); // SO FAR SO GOOD

    // data = [{'a': 'lalala'}]

    // loop on the keys and get the values
    for(int i = 0; i < key_count; i++) { // percorre as keys do dict -> 'id', 'name'
        PyObject* column = PyList_GetItem(header, i);
        printf("-----======= %d\n", seq_size);
        if(PyUnicode_Check(column)) {
            PyObject* columnAscii = PyUnicode_AsASCIIString(column);
            printf("-> %s", PyBytes_AsString(columnAscii));
            fprintf(fp, PyBytes_AsString(columnAscii));
            Py_DECREF(columnAscii);
        }
    }
    fprintf(fp, "\n");
    

    Py_DECREF(sequence);
    Py_DECREF(list_obj);
    Py_DECREF(first_row);
    Py_DECREF(header);

    // fp = fopen("filename.csv","w+");
    // fprintf(fp, "Student Id, Physics, Chemistry, Maths\n");
    // fprintf(fp, "a,b,c,d");
    fclose(fp);

    return Py_BuildValue("s", "Hello Pythonista");
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
    "usage: fcsv.create(filename, )\n",
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