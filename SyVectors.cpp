/*     SyVectors-Module
 * ########################
 * Author:      Samuel Nösslböck
 * Creted:      05/03/2021
 * Last-Update: 12/03/2021
 * 
 * The whole module is assambled here, see the module header files (./Modules)
 */
# define PY_SSIZE_T_CLEAN
# include <Python.h>
# include <structmember.h>

// Include the module parts
# include "./Modules/SyVectors.Render.hpp"
# include "./Modules/SyVectors.Shapes.hpp"
# include "./Modules/SyVectors.Vectors.hpp"
# include "./Modules/SyVectors.VMath.hpp"

extern "C"
{

/* Test-Funciton
 * A function from testing stuff, has no course, will be removed in future updates
 */
static PyObject* TestFunction( PyObject* self, PyObject* args )
{
    PyObject* list = PyList_New(0);
    PyList_Append(list, PyLong_FromDouble(10));
    PyList_Append(list, Vector2_CreateNew( 10, 10 ));
    return list;
}

static PyMethodDef SyVectorsMethods[] = {
    { "TestFunction", TestFunction, METH_VARARGS, "A test function"},
    { NULL, NULL, 0, NULL }
};

static struct PyModuleDef SyVectorsModule = {
    PyModuleDef_HEAD_INIT,
    "SyVectors",
    "A high-performace Vector and Matrix-Math module",
    -1,
    SyVectorsMethods
};

/* The module Init-Function
 * All the Init-Functions of the external header files are called here
 */
PyMODINIT_FUNC 
PyInit_SyVectors(void) 
{
    PyObject *m;
    
    m = PyModule_Create(&SyVectorsModule);
    if (m == NULL) return NULL;
    
    // Render
    PyObject* render = Init_SyVectors_Render(m);
    if (render == NULL) return NULL;

    // Shapes
    PyObject* shapes = Init_SyVectors_Shapes(m);
    if (shapes == NULL) return NULL;

    // Vectors
    PyObject* vectors = Init_SyVectors_Vectors(m);
    if (vectors == NULL) return NULL;
    
    // VMath
    PyObject* vMath = Init_SyVectors_VMath(m);
    if (vMath == NULL) return NULL;

    return m;
};


}