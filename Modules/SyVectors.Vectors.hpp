# ifndef _SYVECTORS_VECTORS_HPP_
# define _SYVECTORS_VECTORS_HPP_

# include "../Vectors/Vector2.hpp"
# include "../Vectors/Vector3.hpp"
# include "../Vectors/Matrix3.hpp"

static PyObject* Init_SyVectors_Vectors(PyObject* m)
{
    // Vector2
    if (PyType_Ready(&Vector2_t) < 0) return NULL;

    Py_INCREF(&Vector2_t);
    if (PyModule_AddObject(m, "Vector2", (PyObject *)&Vector2_t) < 0) {
        Py_DECREF(&Vector2_t);
        Py_DECREF(m);
        return NULL;
    }

    // Vector3 
    if (PyType_Ready(&Vector3_t) < 0) return NULL;

    Py_INCREF(&Vector3_t);
    if (PyModule_AddObject(m, "Vector3", (PyObject *)&Vector3_t) < 0) {
        Py_DECREF(&Vector3_t);
        Py_DECREF(m);
        return NULL;
    }

    // Matrix3
    int iResult = PyType_Ready(&Matrix3_t);
    if (iResult < 0) return NULL;

    Py_INCREF(&Matrix3_t);
    if (PyModule_AddObject(m, "Matrix3", (PyObject *)&Matrix3_t) < 0) {
        Py_DECREF(&Matrix3_t);
        Py_DECREF(m);
        return NULL;
    }
    return m;
}

# endif