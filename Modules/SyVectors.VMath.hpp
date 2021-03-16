# ifndef _SYVECTORS_VMATH_HPP_
# define _SYVECTORS_VMATH_HPP_

# include "Vectors/VMath.hpp"

// PyMethods
static PyObject* PyAdd3( PyObject* self, PyObject* args )
{
    PyObject *aObj, *bObj;
    if (!PyArg_ParseTuple(args, "OO", &aObj, &bObj)) return NULL;
    return Vector3_CreateNew(Add3(Vector3_FromPyObject(aObj), Vector3_FromPyObject(bObj)));
}

static PyObject* PyAmount3( PyObject* self, PyObject* args )
{
    PyObject *vectorObj;
    if (!PyArg_ParseTuple(args, "O", &vectorObj)) return NULL;
    return PyFloat_FromDouble(Amount3(Vector3_FromPyObject(vectorObj)));
}

static PyObject* PyAngle3( PyObject* self, PyObject* args )
{
    PyObject *vectorObj;
    if (!PyArg_ParseTuple(args, "O", &vectorObj)) return NULL;
    return Vector3_CreateNew(Angle3(Vector3_FromPyObject(vectorObj)));
}

static PyObject* PyCrossProduct( PyObject* self, PyObject* args )
{
    PyObject *aObj, *bObj;
    if (!PyArg_ParseTuple(args, "OO", &aObj, &bObj)) return NULL;
    return Vector3_CreateNew(Subtract3(Vector3_FromPyObject(aObj), Vector3_FromPyObject(bObj)));
}

static PyObject* PyScale3( PyObject* self, PyObject* args )
{
    PyObject *vObj; double a;
    if (!PyArg_ParseTuple(args, "Od", &vObj, &a)) return NULL;
    return Vector3_CreateNew(Scale3(Vector3_FromPyObject(vObj), a));
}

static PyObject* PySubtract3( PyObject* self, PyObject* args )
{
    PyObject *aObj, *bObj;
    if (!PyArg_ParseTuple(args, "OO", &aObj, &bObj)) return NULL;
    return Vector3_CreateNew(Subtract3(Vector3_FromPyObject(aObj), Vector3_FromPyObject(bObj)));
}

static PyObject* PyUnitVector3( PyObject* self, PyObject* args )
{
    PyObject *vectorObj;
    if (!PyArg_ParseTuple(args, "O", &vectorObj)) return NULL;
    return Vector3_CreateNew(UnitVector3(Vector3_FromPyObject(vectorObj)));
}

static PyObject* PyVectorMultiMatrix3( PyObject* self, PyObject* args )
{
    PyObject *vObj, *mObj; Vector3_o v; Matrix3 m;
    if (!PyArg_ParseTuple(args, "OO", &vObj, &mObj)) return NULL;
    return Vector3_CreateNew(VectorMultiMatrix3(Vector3_FromPyObject(vObj), Matrix3_FromObject(Matrix3_FromPyObject(mObj))));
}

// Initalizing
static PyMethodDef SyVectorsVMathMethods[] = {
    { "Add3", PyAdd3, METH_VARARGS, "Add two vectors together"},
    { "Amount3", PyAmount3, METH_VARARGS, "Get the length of a Vector3"},
    { "Angle3", PyAngle3, METH_VARARGS, "Get the angle of a Vector3"},
    { "CrossProduct", PyCrossProduct, METH_VARARGS, "Get the cross-product of the two given vectors a and b"},
    { "Scale3", PyScale3, METH_VARARGS, "Scale a vector by the given number a"},
    { "Subtract3", PySubtract3, METH_VARARGS, "Subtract two vectors"},
    { "UnitVector3", PyUnitVector3, METH_VARARGS, "Get the unitvector of the given vector"},
    { "VectorMultiMatrix3", PyVectorMultiMatrix3, METH_VARARGS, "Multiply a vector by a matrix"},
    { NULL, NULL, 0, NULL }
};

static struct PyModuleDef SyVectorsVMathModule = {
    PyModuleDef_HEAD_INIT,
    "SyVectors.VMath",
    "Vector-Math for the SyVectors module",
    -1,
    SyVectorsVMathMethods
};

static PyObject* Init_SyVectors_VMath( PyObject* m )
{
    // VMath
    if (PyModule_AddObject(m, "VMath", PyModule_Create(&SyVectorsVMathModule)) < 0) {
        Py_DECREF(&SyVectorsVMathModule);
        Py_DECREF(m);
        return NULL;
    };
    
    return m;
}

# endif