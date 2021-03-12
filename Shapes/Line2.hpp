# ifndef _SYVECTORS_SHAPES_LINE2_HPP_
# define _SYVECTORS_SHAPES_LINE2_HPP_

# include "../Vectors/Vector2.hpp"

// Class definition
struct Line2 
{
    Vector2_o a, b;
};

typedef struct {
    PyObject_HEAD
    PyObject *a, *b;
} Line2_o;

Line2 Line2_CreateNewStruct( Vector2_o a, Vector2_o b ) 
{
    Line2 line;
    line.a = a;
    line.b = b;
    return line;
}

// Python to C
Line2 Line2_FromObject( Line2_o lineObj )
{
    Line2 line;
    line.a = Vector2_FromPyObject( lineObj.a );
    line.b = Vector2_FromPyObject( lineObj.b );
    return line;
}

Line2_o Line2_FromPyObject(PyObject* object)
{
    Line2_o line;
    line.a = PyObject_GetAttrString(object, "a"); 
    line.b = PyObject_GetAttrString(object, "b"); 
    return line;
}

// C to Python
Line2_o Matrix3_ObjectFromStructure(Line2 line)
{
    Line2_o lineObj;
    lineObj.a = Vector2_CreateNew( line.a );
    lineObj.b = Vector2_CreateNew( line.b );
    return lineObj;
}

// Basic Functions
static int __Line2_init(Line2_o* self, PyObject* args, PyObject* kwargs)
{
    if (!PyArg_ParseTuple(args, "OO", &self->a, &self->b)) return -1;
    return 0;
}

static void __Line2_dealloc(Line2_o* self) 
{ 
    Py_DECREF(self->a);
    Py_DECREF(self->b);
}

PyMemberDef __Line2_members[] = {
    { "a", T_OBJECT, offsetof(Line2_o, a), 0, "The A-point of the line" },
    { "b", T_OBJECT, offsetof(Line2_o, b), 0, "The B-point of the line" },
    { NULL }
};

// Methods
static std::string Line2_GetString( Line2_o line )
{
    return "g[ A" + Vector2_GetString(Vector2_FromPyObject(line.a)) + "; B" + 
                    Vector2_GetString(Vector2_FromPyObject(line.b)) + " ]";
}

static PyObject* __Line2_repr(PyObject* self) 
{
    return PyUnicode_FromString(Line2_GetString(Line2_FromPyObject( self )).c_str());
}

static PyTypeObject Line2_t = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "SyVectors.Line3",                          /* tp_name */
    sizeof(Line2_o),                            /* tp_basicsize */
    0,                                          /* tp_itemsize */
    (destructor)__Line2_dealloc,                /* tp_dealloc */
    0,                                          /* tp_print */
    0,                                          /* tp_getattr */
    0,                                          /* tp_setattr */
    0,                                          /* tp_reserved */
    (reprfunc)__Line2_repr,                     /* tp_repr */
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
    "A 2D Line",                                /* tp_doc */
    0,                                          /* tp_traverse */
    0,                                          /* tp_clear */
    0,                                          /* tp_richcompare */
    0,                                          /* tp_weaklistoffset */
    0,                                          /* tp_iter */
    0,                                          /* tp_iternext */
    0,                                          /* tp_methods */
    __Line2_members,                            /* tp_members */
    0,                                          /* tp_getset */
    0,                                          /* tp_base */
    0,                                          /* tp_dict */
    0,                                          /* tp_descr_get */
    0,                                          /* tp_descr_set */
    0,                                          /* tp_dictoffset */
    (initproc)__Line2_init,                     /* tp_init */
    0,                                          /* tp_alloc */
    (newfunc)PyType_GenericNew,                 /* tp_new */
};

PyObject* Line2_CreateNew( Line2 line )
{
    PyObject* argList = Py_BuildValue("OO", Vector2_CreateNew(line.a), Vector2_CreateNew(line.b));
    PyObject* pyVector = PyObject_Call((PyObject*)&Line2_t, argList, NULL);
    Py_DECREF(argList);
    return pyVector;
}

# endif