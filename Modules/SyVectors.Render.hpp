# ifndef _SYVECTORS_RENDER_HPP_
# define _SYVECTORS_RENDER_HPP_

# include "../Rendering/Camera.hpp"
# include "../Rendering/RenderObject2.hpp"
# include "../Rendering/RenderObject3.hpp"
# include "../Rendering/HighDetail.hpp"

static PyMethodDef SyVectorsRenderMethods[] = {
    { "LineSplitDown", PyLine3_SplitDown, METH_VARARGS, "Split a line down to a renderObj with the desired quality"},
    { NULL, NULL, 0, NULL }
}; 

static PyObject* Init_SyVectors_Render(PyObject* m)
{
    // Methods
    PyModule_AddFunctions(m, SyVectorsRenderMethods);

    // Camera
    if (PyType_Ready(&Camera_t) < 0) return NULL;
    Py_INCREF(&Camera_t);
    if (PyModule_AddObject(m, "Camera", (PyObject *)&Camera_t) < 0) {
        Py_DECREF(&Camera_t);
        Py_DECREF(m);
        return NULL;
    }

    // RenderObj2
    if (PyType_Ready(&RenderObj2_t) < 0) return NULL;
    Py_INCREF(&RenderObj2_t);
    if (PyModule_AddObject(m, "RenderObj2", (PyObject *)&RenderObj2_t) < 0) {
        Py_DECREF(&RenderObj2_t);
        Py_DECREF(m);
        return NULL;
    }

    // RenderObj3
    if (PyType_Ready(&RenderObj3_t) < 0) return NULL;
    Py_INCREF(&RenderObj3_t);
    if (PyModule_AddObject(m, "RenderObj3", (PyObject *)&RenderObj3_t) < 0) {
        Py_DECREF(&RenderObj3_t);
        Py_DECREF(m);
        return NULL;
    }
    
    return m;
}

# endif