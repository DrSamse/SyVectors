# ifndef _SYVECTORS_MATRIX3_HPP_
# define _SYVECTORS_MATRIX3_HPP_

# include "Vector3.hpp"

// Class definition
struct Matrix3 
{
    Vector3_o x, y, z;
};

typedef struct {
    PyObject_HEAD
    PyObject *x, *y, *z;    // Vector3_o x, y, z;
} Matrix3_o;

Matrix3 Matrix3_CreateNewStruct( Vector3_o x, Vector3_o y, Vector3_o z ) 
{
    Matrix3 matrix;
    matrix.x = x;
    matrix.y = y;
    matrix.z = z;
    return matrix;
}

// Python to C
Matrix3 Matrix3_FromObject( Matrix3_o matrixObj )
{
    Matrix3 matrix;
    matrix.x = Vector3_FromPyObject( matrixObj.x );
    matrix.y = Vector3_FromPyObject( matrixObj.y );
    matrix.z = Vector3_FromPyObject( matrixObj.z );
    return matrix;
}

Matrix3_o Matrix3_FromPyObject(PyObject* object)
{
    Matrix3_o matrix;
    matrix.x = PyObject_GetAttrString(object, "x"); 
    matrix.y = PyObject_GetAttrString(object, "y"); 
    matrix.z = PyObject_GetAttrString(object, "z"); 
    return matrix;
}

// C to Python
Matrix3_o Matrix3_ObjectFromStructure(Matrix3 matrix)
{
    Matrix3_o m;
    m.x = Vector3_CreateNew( matrix.x );
    m.y = Vector3_CreateNew( matrix.y );
    m.z = Vector3_CreateNew( matrix.z );
    return m;
}

// Basic Functions
static int __Matrix3_init(Matrix3_o* self, PyObject* args, PyObject* kwargs)
{
    if (!PyArg_ParseTuple(args, "OOO", &self->x, &self->y, &self->z)) return -1;
    return 0;
}

static void __Matrix3_dealloc(Matrix3_o* self) 
{ 
    Py_DECREF(self->x);
    Py_DECREF(self->y);
    Py_DECREF(self->z);
}

PyMemberDef __Matrix3_members[] = {
    { "x", T_OBJECT, offsetof(Matrix3_o, x), 0, "The X-value of the matrix" },
    { "y", T_OBJECT, offsetof(Matrix3_o, y), 0, "The Y-value of the matrix" },
    { "z", T_OBJECT, offsetof(Matrix3_o, z), 0, "The Z-value of the matrix" },
    { NULL }
};

// Methods
static std::string Matrix3_GetString( Matrix3_o matrix )
{
    return "( " +   Vector3_GetString(Vector3_FromPyObject(matrix.x)) + " " + 
                    Vector3_GetString(Vector3_FromPyObject(matrix.y)) + " " + 
                    Vector3_GetString(Vector3_FromPyObject(matrix.z)) + " )";
}

static PyObject* __Matrix3_repr(PyObject* self) 
{
    return PyUnicode_FromString(Matrix3_GetString(Matrix3_FromPyObject( self )).c_str());
}

static PyTypeObject Matrix3_t = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "SyVectors.Matrix3",                        /* tp_name */
    sizeof(Matrix3_o),                          /* tp_basicsize */
    0,                                          /* tp_itemsize */
    (destructor)__Matrix3_dealloc,              /* tp_dealloc */
    0,                                          /* tp_print */
    0,                                          /* tp_getattr */
    0,                                          /* tp_setattr */
    0,                                          /* tp_reserved */
    (reprfunc)__Matrix3_repr,                   /* tp_repr */
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
    "A 3x3 Matrix",                             /* tp_doc */
    0,                                          /* tp_traverse */
    0,                                          /* tp_clear */
    0,                                          /* tp_richcompare */
    0,                                          /* tp_weaklistoffset */
    0,                                          /* tp_iter */
    0,                                          /* tp_iternext */
    0,                                          /* tp_methods */
    __Matrix3_members,                          /* tp_members */
    0,                                          /* tp_getset */
    0,                                          /* tp_base */
    0,                                          /* tp_dict */
    0,                                          /* tp_descr_get */
    0,                                          /* tp_descr_set */
    0,                                          /* tp_dictoffset */
    (initproc)__Matrix3_init,                   /* tp_init */
    0,                                          /* tp_alloc */
    (newfunc)PyType_GenericNew,                 /* tp_new */
};

# endif