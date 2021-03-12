# ifndef _SYVECTORS_VECTOR2_HPP_
# define _SYVECTORS_VECTOR2_HPP_

# define PY_SSIZE_T_CLEAN
# include <Python.h>
# include <structmember.h>
# include <string>

/* SyVectors.Vector2 
 * 
 * A basic 2D-Vector with an x and an y axis.
 * 
 * This struct is used for C-Calculations and Python-Object decleration at the same time.
 * This means that: typedef Vector2 Vector2_o
 * 
 * Struct fields
 *  | double x: The X-Coordinate of the 2D-Vector
 *  | double y: The Y-Coordinate of the 2D-Vector
 *  
 * Constructors
 *  | Vector2_o Vector2_CreateNewstruct( double x = 0, double y = 0)
 *  | Vector2_o Vector2_FromPyObject( PyObject* object )
 * 
 * Python-Conversions
 *  | PyObject* Vector2_CreateNew( double x = 0, double y = 0 )
 *  | PyObject* Vector2_CreateNew( Vector2_o vector )
 */
typedef struct Vector2 {
    PyObject_HEAD
    double x = 0, y = 0;
} Vector2_o;

/* Constructor of SyVectors.Vector2 
 *
 * Creates a new Vector2 struct with fields set:
 *  | Vector2.x = x  [ default 0 ]
 *  | Vector2.y = y  [ default 0 ]
 */
Vector2_o Vector2_CreateNewStruct( double x = 0, double y = 0 )
{
    Vector2_o obj;
    obj.x = x; obj.y = y; 
    return obj;
}

/* Constructor of SyVectors.Vector2
 * 
 * Converts the given PyObject* to a Vector2_o
 * If the PyObject* is not pointing to a valid Vector2 object in Python, an error will occure
 * 
 * Params:
 *  | PyObject* object; The PyObject-pointer to convert
 */
Vector2_o Vector2_FromPyObject(PyObject* object)
{
    Vector2_o vector;
    vector.x = PyFloat_AsDouble(PyObject_GetAttrString(object, "x")); 
    vector.y = PyFloat_AsDouble(PyObject_GetAttrString(object, "y")); 
    return vector;
}

/* Vector2.__repr__()
 * Equal to the repr() function in Python but for C/C++
 * 
 * Params:
 *  | Vector2_o vector; The vector you want to have the representing string
 * 
 * Returns: std::string; The representing string of the given 2D-Vector vector
 */
static std::string Vector2_GetString( Vector2_o vector )
{
    return "( " + std::to_string(vector.x) + " " + std::to_string(vector.y) + " )";
}


// [[  Python-Type-Functions  ]]

static int __Vector2_init(Vector2_o* self, PyObject* args, PyObject* kwargs)
{

    if (!PyArg_ParseTuple(args, "|dd:", &self->x, &self->y)) return -1;
    return 0;
}

static void __Vector2_dealloc(Vector2_o* self) { }

static PyObject* __Vector2_repr(PyObject* self) 
{
    Vector2_o vector = Vector2_FromPyObject( self );
    return PyUnicode_FromString(Vector2_GetString(vector).c_str());
}

PyMemberDef __Vector2_members[] = {
    { "x", T_DOUBLE, offsetof(Vector2_o, x), 0, "The X-value of the vector" },
    { "y", T_DOUBLE, offsetof(Vector2_o, y), 0, "The Y-value of the vector" },
    { NULL }
};

// Python type
static PyTypeObject Vector2_t = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "SyVectors.Vector2",                        /* tp_name */
    sizeof(Vector2_o),                          /* tp_basicsize */
    0,                                          /* tp_itemsize */
    (destructor)__Vector2_dealloc,              /* tp_dealloc */
    0,                                          /* tp_print */
    0,                                          /* tp_getattr */
    0,                                          /* tp_setattr */
    0,                                          /* tp_reserved */
    (reprfunc)__Vector2_repr,                   /* tp_repr */
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
    __Vector2_members,                          /* tp_members */
    0,                                          /* tp_getset */
    0,                                          /* tp_base */
    0,                                          /* tp_dict */
    0,                                          /* tp_descr_get */
    0,                                          /* tp_descr_set */
    0,                                          /* tp_dictoffset */
    (initproc)__Vector2_init,                   /* tp_init */
    0,                                          /* tp_alloc */
    (newfunc)PyType_GenericNew,                 /* tp_new */
};

/* Python conversion/creation of SyVectors.Vector2
 * 
 * Create a new SyVectors.Vector2 instance, the instance is returned as PyObject-Pointer
 * 
 * Params:
 *  | double x; The X-Coordinate of the vector [ Vector2.x = x ]
 *  | double y; The Y-Coordinate of the vector [ Vector2.y = y ]
 * 
 * Returns PyObject*; The PyObject-Pointer to the new instance
 */
PyObject* Vector2_CreateNew(double x = 0, double y = 0)
{
    PyObject* argList = Py_BuildValue("dd", x, y);
    PyObject* vector = PyObject_Call((PyObject*)&Vector2_t, argList, NULL);
    Py_DECREF(argList);
    return vector;
}

/* Python conversion/creation of SyVectors.Vector2
 * 
 * Create a new SyVectors.Vector2 instance, the instance is returned as PyObject-Pointer
 * 
 * Params:
 *  | Vector2_o vector; The vector to convert to a PyObject-Pointer
 * 
 * Returns PyObject*; The PyObject-Pointer to the new instance
 */
PyObject* Vector2_CreateNew( Vector2_o vector )
{
    PyObject* argList = Py_BuildValue("dd", vector.x, vector.y);
    PyObject* pyVector = PyObject_Call((PyObject*)&Vector2_t, argList, NULL);
    Py_DECREF(argList);
    return pyVector;
}

# endif