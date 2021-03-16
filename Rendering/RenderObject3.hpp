# ifndef _SYVECTORS_RENDER_OBJ3_HPP_
# define _SYVECTORS_RENDER_OBJ3_HPP_

# include <vector>
# include <iostream>

# include "../Shapes/Line3.hpp"

// Class definition
struct RenderObj3
{
    std::vector<Line3> lines;
};

typedef struct {
    PyObject_HEAD
    PyObject* lines;
} RenderObj3_o;

RenderObj3 RenderObj3_CreateNewStruct( std::vector<Line3> lines = { } ) 
{
    RenderObj3 renderObj;
    renderObj.lines = lines;
    return renderObj;
}

// Python to C
RenderObj3 RenderObj3_FromObject( RenderObj3_o renderObj3 )
{
    RenderObj3 renderObj;
    for (int i = 0; i < PyList_Size(renderObj3.lines); i++ ) {
        renderObj.lines.push_back( Line3_FromObject(Line3_FromPyObject(PyList_GetItem(renderObj3.lines, i))) );
    }
    return renderObj;
}

RenderObj3_o RenderObj3_FromPyObject(PyObject* object)
{
    RenderObj3_o renderObj;
    renderObj.lines = PyObject_GetAttrString(object, "lines"); 
    return renderObj;
}

// C to Python
RenderObj3_o RenderObj3_ObjectFromStructure( RenderObj3 renderObj3 )
{
    RenderObj3_o renderObj;
    for (unsigned int i = 0; i < renderObj3.lines.size(); i++) {
        PyList_Append(renderObj.lines, Line3_CreateNew(renderObj3.lines[i]));
    }
    return renderObj;
}

// Basic Functions
static int __RenderObj3_init(RenderObj3_o* self, PyObject* args, PyObject* kwargs)
{
    self->lines = PyList_New(0);
    return 0;
}

static void __RenderObj3_dealloc(RenderObj3_o* self) 
{ 
    Py_DECREF(self->lines); 
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyMemberDef __RenderObj3_members[] = {
    { "lines", T_OBJECT, offsetof(RenderObj3_o, lines), 0, "The list of the 3D-Lines to render" },
    { NULL }
};

static PyTypeObject RenderObj3_t = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "SyVectors.RenderObj3",                     /* tp_name */
    sizeof(RenderObj3_o),                       /* tp_basicsize */
    0,                                          /* tp_itemsize */
    (destructor)__RenderObj3_dealloc,           /* tp_dealloc */
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
    __RenderObj3_members,                       /* tp_members */
    0,                                          /* tp_getset */
    0,                                          /* tp_base */
    0,                                          /* tp_dict */
    0,                                          /* tp_descr_get */
    0,                                          /* tp_descr_set */
    0,                                          /* tp_dictoffset */
    (initproc)__RenderObj3_init,                /* tp_init */
    0,                                          /* tp_alloc */
    (newfunc)PyType_GenericNew,                 /* tp_new */
};

static PyObject* RenderObj3_CreateNew( RenderObj3 renderObj3 )
{
    PyObject* renderObj = PyObject_Call((PyObject*)&RenderObj3_t, NULL, NULL);
    for (unsigned int i = 0; i < renderObj3.lines.size(); i++) {
        Line3 line = renderObj3.lines[i];
        PyObject* lineObj = Line3_CreateNew(line);
        PyObject* list = PyObject_GetAttrString(renderObj, "lines");
        PyList_Append(list, lineObj);
    }   return renderObj;
}


# endif