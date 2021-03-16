# ifndef _SYVECTORS_VECTOR3_HPP_
# define _SYVECTORS_VECTOR3_HPP_

# define PY_SSIZE_T_CLEAN
# include <Python.h>
# include <structmember.h>
# include <string>

/* SyVectors.Vector3
 * 
 * A basic 3D-Vector with an x, y and z value
 * 
 * This struct is used for C-Calculations and Python-Object decleration at the same time.
 * This means that: typedef Vector3 Vector3_o
 * 
 * Struct fields
 *  | double x: The X-Value of the 3D-Vector
 *  | double y: The Y-Value of the 3D-Vector
 *  | double z: The Z-Value of the 3D-Vector
 * 
 * Constructors
 *  | Vector3_o Vector3_CreateNewStruct( double x = 0, double y = 0, double z = 0 )
 *  | Vector3_o Vector3_FromPyObject( PyObject* object )
 * 
 * PyObject creation/conversion
 *  | PyObject* Vector3_CreateNew( double x = 0, double y = 0, double z = 0 )
 *  | PyObject* Vector3_CreateNew( Vector3_o vector )
 */
typedef struct Vector3 {
    PyObject_HEAD
    double x = 0, y = 0, z = 0;
} Vector3_o;

/*
 *
 */
Vector3_o Vector3_CreateNewStruct( double x = 0, double y = 0, double z = 0 )
{
    Vector3_o obj;
    obj.x = x; obj.y = y; obj.z = z;
    return obj;
}

// Python to C
Vector3_o Vector3_FromPyObject(PyObject* object)
{
    Vector3_o vector;
    vector.x = PyFloat_AsDouble(PyObject_GetAttrString(object, "x")); 
    vector.y = PyFloat_AsDouble(PyObject_GetAttrString(object, "y")); 
    vector.z = PyFloat_AsDouble(PyObject_GetAttrString(object, "z")); 
    return vector;
}

static int __Vector3_init(Vector3_o* self, PyObject* args, PyObject* kwargs)
{
    if (!PyArg_ParseTuple(args, "|ddd", &self->x, &self->y, &self->z)) return -1;
    return 0;
}

static void __Vector3_dealloc(Vector3_o* self) { }

PyMemberDef __Vector3_members[] = {
    { "x", T_DOUBLE, offsetof(Vector3_o, x), 0, "The X-value of the vector" },
    { "y", T_DOUBLE, offsetof(Vector3_o, y), 0, "The Y-value of the vector" },
    { "z", T_DOUBLE, offsetof(Vector3_o, z), 0, "The Z-value of the vector" },
    { NULL }
};

// Methods
static std::string Vector3_GetString( Vector3_o vector )
{
    return "( " + std::to_string(vector.x) + " " + std::to_string(vector.y) + " " + std::to_string(vector.z) + " )";
}

static PyObject* __Vector3_repr(PyObject* self) 
{
    Vector3_o vector = Vector3_FromPyObject( self );
    return PyUnicode_FromString(Vector3_GetString(vector).c_str());
}

static PyTypeObject Vector3_t = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "SyVectors.Vector3",                        /* tp_name */
    sizeof(Vector3_o),                          /* tp_basicsize */
    0,                                          /* tp_itemsize */
    (destructor)__Vector3_dealloc,              /* tp_dealloc */
    0,                                          /* tp_print */
    0,                                          /* tp_getattr */
    0,                                          /* tp_setattr */
    0,                                          /* tp_reserved */
    (reprfunc)__Vector3_repr,                   /* tp_repr */
    0,                                          /* tp_as_number */
    0,                                          /* tp_as_sequence */
    0,                                          /* tp_as_mapping */
    0,                                          /* tp_hash */
    0,                                          /* tp_call */
    0,                                          /* tp_str */
    0,                                          /* tp_getattro */
    0,                                          /* tp_setattro */
    0,                                          /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT |
    Py_TPFLAGS_BASETYPE,                        /* tp_flags */
    "A 3D Vector",                              /* tp_doc */
    0,                                          /* tp_traverse */
    0,                                          /* tp_clear */
    0,                                          /* tp_richcompare */
    0,                                          /* tp_weaklistoffset */
    0,                                          /* tp_iter */
    0,                                          /* tp_iternext */
    0,                                          /* tp_methods */
    __Vector3_members,                          /* tp_members */
    0,                                          /* tp_getset */
    0,                                          /* tp_base */
    0,                                          /* tp_dict */
    0,                                          /* tp_descr_get */
    0,                                          /* tp_descr_set */
    0,                                          /* tp_dictoffset */
    (initproc)__Vector3_init,                   /* tp_init */
    0,                                          /* tp_alloc */
    (newfunc)PyType_GenericNew,                 /* tp_new */
};

// C to Python
PyObject* Vector3_CreateNew(double x = 0, double y = 0, double z = 0)
{
    PyObject* argList = Py_BuildValue("ddd", x, y, z);
    PyObject* vector = PyObject_Call((PyObject*)&Vector3_t, argList, NULL);
    Py_DECREF(argList);
    return vector;
}

PyObject* Vector3_CreateNew( Vector3_o vector )
{
    PyObject* argList = Py_BuildValue("ddd", vector.x, vector.y, vector.z);
    PyObject* pyVector = PyObject_Call((PyObject*)&Vector3_t, argList, NULL);
    Py_DECREF(argList);
    return pyVector;
}

# endif