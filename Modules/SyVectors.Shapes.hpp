# ifndef _SYVECTORS_SHAPES_HPP_
# define _SYVECTORS_SHAPES_HPP_

# include "../Shapes/Line2.hpp"
# include "../Shapes/Line3.hpp"

static PyObject* Init_SyVectors_Shapes( PyObject* m )
{
    // Line2
    if (PyType_Ready(&Line2_t) < 0) return NULL;

    Py_INCREF(&Line2_t);
    if (PyModule_AddObject(m, "Line2", (PyObject *)&Line2_t) < 0) {
        Py_DECREF(&Line2_t);
        Py_DECREF(m);
        return NULL;
    }

    // Line3
    if (PyType_Ready(&Line3_t) < 0) return NULL;

    Py_INCREF(&Line3_t);
    if (PyModule_AddObject(m, "Line3", (PyObject *)&Line3_t) < 0) {
        Py_DECREF(&Line3_t);
        Py_DECREF(m);
        return NULL;
    }
    
    return m;
}

# endif