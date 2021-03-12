# ifndef _SYVECTORS_RENDER_OBJ2_HPP_
# define _SYVECTORS_RENDER_OBJ2_HPP_

# include <vector>

# include "../Shapes/Line2.hpp"

// Class definition
struct RenderObj2
{
    std::vector<Line2> lines;
};

typedef struct {
    PyObject_HEAD
    PyObject* lines;
} RenderObj2_o;

RenderObj2 RenderObj2_CreateNewStruct( std::vector<Line2> lines = { } ) 
{
    RenderObj2 renderObj2;
    renderObj2.lines = lines;
    return renderObj2;
}

// Python to C
RenderObj2 RenderObj2_FromObject( RenderObj2_o renderObj )
{
    RenderObj2 renderObj2;
    for (int i = 0; i < PyList_Size(renderObj.lines); i++ ) {
        renderObj2.lines.push_back( Line2_FromObject(Line2_FromPyObject(PyList_GetItem(renderObj.lines, i))) );
    }
    return renderObj2;
}

RenderObj2_o RenderObj2_FromPyObject(PyObject* object)
{
    RenderObj2_o renderObj;
    renderObj.lines = PyObject_GetAttrString(object, "lines"); 
    return renderObj;
}

// C to Python
RenderObj2_o RenderObj2_ObjectFromStructure( RenderObj2 renderObj2 )
{
    RenderObj2_o renderObj;
    for (unsigned int i = 0; i < renderObj2.lines.size(); i++) {
        PyList_Append(renderObj.lines, Line2_CreateNew(renderObj2.lines[i]));
    }
    return renderObj;
}

// Basic Functions
static int __RenderObj2_init(RenderObj2_o* self, PyObject* args, PyObject* kwargs)
{
    self->lines = PyList_New(0);
    return 0;
}

static void __RenderObj2_dealloc(RenderObj2_o* self) 
{ 
    Py_DECREF(self->lines); 
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyMemberDef __RenderObj2_members[] = {
    { "lines", T_OBJECT, offsetof(RenderObj2_o, lines), 0, "The list of the 2D-Lines to render" },
    { NULL }
};

static PyTypeObject RenderObj2_t = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "SyVectors.RenderObj2",                     /* tp_name */
    sizeof(RenderObj2_o),                       /* tp_basicsize */
    0,                                          /* tp_itemsize */
    (destructor)__RenderObj2_dealloc,           /* tp_dealloc */
    0,                                          /* tp_print */
    0,                                          /* tp_getattr */
    0,                                          /* tp_setattr */
    0,                                          /* tp_reserved */
    0,                                          /* tp_repr */
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
    "A class to store render-data",             /* tp_doc */
    0,                                          /* tp_traverse */
    0,                                          /* tp_clear */
    0,                                          /* tp_richcompare */
    0,                                          /* tp_weaklistoffset */
    0,                                          /* tp_iter */
    0,                                          /* tp_iternext */
    0,                                          /* tp_methods */
    __RenderObj2_members,                       /* tp_members */
    0,                                          /* tp_getset */
    0,                                          /* tp_base */
    0,                                          /* tp_dict */
    0,                                          /* tp_descr_get */
    0,                                          /* tp_descr_set */
    0,                                          /* tp_dictoffset */
    (initproc)__RenderObj2_init,                /* tp_init */
    0,                                          /* tp_alloc */
    (newfunc)PyType_GenericNew,                 /* tp_new */
};

static PyObject* RenderObj2_CreateNew( RenderObj2 renderObj2 ) 
{
    PyObject* renderObj = PyObject_Call((PyObject*)&RenderObj2_t, NULL, NULL);
    for (unsigned int i = 0; i < renderObj2.lines.size(); i++) {
        PyList_Append(PyObject_GetAttrString(renderObj, "lines"), Line2_CreateNew(renderObj2.lines[i]));
    }   return renderObj;
}

# endif