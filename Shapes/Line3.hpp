# ifndef _SYVECTORS_SHAPES_LINE3_HPP_
# define _SYVECTORS_SHAPES_LINE3_HPP_

# include "../Vectors/Vector3.hpp"

// Class definition
struct Line3 
{
    Vector3_o a, b;
};

typedef struct {
    PyObject_HEAD
    PyObject *a, *b;
} Line3_o;

Line3 Line3_CreateNewStruct( Vector3_o a, Vector3_o b ) 
{
    Line3 line;
    line.a = a;
    line.b = b;
    return line;
}

// Python to C
Line3 Line3_FromObject( Line3_o lineObj )
{
    Line3 line;
    line.a = Vector3_FromPyObject( lineObj.a );
    line.b = Vector3_FromPyObject( lineObj.b );
    return line;
}

Line3_o Line3_FromPyObject(PyObject* object)
{
    Line3_o line;
    line.a = PyObject_GetAttrString(object, "a"); 
    line.b = PyObject_GetAttrString(object, "b"); 
    return line;
}

// C to Python
// Matrix3_o Matrix3_ObjectFromStructure(Matrix3 matrix)
// {
//     Matrix3_o m;
//     m.x = Vector3_CreateNew( matrix.x );
//     m.y = Vector3_CreateNew( matrix.y );
//     m.z = Vector3_CreateNew( matrix.z );
//     return m;
// }

// Basic Functions
static int __Line3_init(Line3_o* self, PyObject* args, PyObject* kwargs)
{
    if (!PyArg_ParseTuple(args, "OO", &self->a, &self->b)) return -1;
    return 0;
}

static void __Line3_dealloc(Line3_o* self) 
{ 
    Py_DECREF(self->a);
    Py_DECREF(self->b);
}

PyMemberDef __Line3_members[] = {
    { "a", T_OBJECT, offsetof(Line3_o, a), 0, "The A-point of the line" },
    { "b", T_OBJECT, offsetof(Line3_o, b), 0, "The B-point of the line" },
    { NULL }
};

// Methods
static std::string Line3_GetString( Line3_o line )
{
    return "g[ A" + Vector3_GetString(Vector3_FromPyObject(line.a)) + "; B" + 
                    Vector3_GetString(Vector3_FromPyObject(line.b)) + " ]";
}

static PyObject* __Line3_repr(PyObject* self) 
{
    return PyUnicode_FromString(Line3_GetString(Line3_FromPyObject( self )).c_str());
}

static PyTypeObject Line3_t = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "SyVectors.Line3",                          /* tp_name */
    sizeof(Line3_o),                            /* tp_basicsize */
    0,                                          /* tp_itemsize */
    (destructor)__Line3_dealloc,                /* tp_dealloc */
    0,                                          /* tp_print */
    0,                                          /* tp_getattr */
    0,                                          /* tp_setattr */
    0,                                          /* tp_reserved */
    (reprfunc)__Line3_repr,                     /* tp_repr */
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
    "A 3D Line",                                /* tp_doc */
    0,                                          /* tp_traverse */
    0,                                          /* tp_clear */
    0,                                          /* tp_richcompare */
    0,                                          /* tp_weaklistoffset */
    0,                                          /* tp_iter */
    0,                                          /* tp_iternext */
    0,                                          /* tp_methods */
    __Line3_members,                            /* tp_members */
    0,                                          /* tp_getset */
    0,                                          /* tp_base */
    0,                                          /* tp_dict */
    0,                                          /* tp_descr_get */
    0,                                          /* tp_descr_set */
    0,                                          /* tp_dictoffset */
    (initproc)__Line3_init,                     /* tp_init */
    0,                                          /* tp_alloc */
    (newfunc)PyType_GenericNew,                 /* tp_new */
};

PyObject* Line3_CreateNew( Line3 line )
{
    PyObject* argList = Py_BuildValue("OO", Vector3_CreateNew(line.a), Vector3_CreateNew(line.b));
    PyObject* pyLine = PyObject_Call((PyObject*)&Line3_t, argList, NULL);
    Py_DECREF(argList);
    return pyLine;
}

# endif