# ifndef _SYVECTORS_RENDERING_CAMERA_HPP_ 
# define _SYVECTORS_RENDERING_CAMERA_HPP_ 

# include "../Vectors/Vector2.hpp"
# include "../Vectors/Vector3.hpp"
# include "../Vectors/Matrix3.hpp"
# include "../Vectors/VMath.hpp"

# include "./Shapes/Line2.hpp"
# include "./Shapes/Line3.hpp"

# include "./RenderObject2.hpp"
# include "./RenderObject3.hpp"

# include <iostream>

# define __SYVECTORS_RENDER_ERROR_NOT_IN_VIEW -1

// Class definition
struct Camera
{
    Vector3_o pos, viewX, viewY, viewZ;
    Vector2_o maxAngles, screenSize;
};

typedef struct {
    PyObject_HEAD
    PyObject *pos, *viewX, *viewY, *viewZ;      // Vector3_o
    PyObject *maxAngles, *screenSize;   // Vector2_o
} Camera_o;

// Python to C
Camera Camera_FromObject( Camera_o cameraObj )
{
    Camera camera;
    camera.pos = Vector3_FromPyObject( cameraObj.pos );
    camera.viewX = Vector3_FromPyObject( cameraObj.viewX );
    camera.viewY = Vector3_FromPyObject( cameraObj.viewY ); 
    camera.viewZ = Vector3_FromPyObject( cameraObj.viewZ ); 
    camera.maxAngles = Vector2_FromPyObject( cameraObj.maxAngles );
    camera.screenSize = Vector2_FromPyObject( cameraObj.screenSize );
    return camera;
}

Camera_o Camera_FromPyObject(PyObject* object)
{
    Camera_o camera;
    camera.pos = PyObject_GetAttrString(object, "pos");
    camera.viewX = PyObject_GetAttrString(object, "viewX");
    camera.viewY = PyObject_GetAttrString(object, "viewY");
    camera.viewZ = PyObject_GetAttrString(object, "viewZ");
    camera.maxAngles = PyObject_GetAttrString(object, "maxAngles");
    camera.screenSize = PyObject_GetAttrString(object, "screenSize");
    return camera;
}

// Basic Functions
static int __Camera_init(Camera_o* self, PyObject* args, PyObject* kwargs)
{
    if (!PyArg_ParseTuple(args, "OOOOO", &self->pos, &self->viewX, &self->viewY, &self->maxAngles, &self->screenSize)) return -1;
    self->viewZ = Vector3_CreateNew(CrossProduct(UnitVector3(Vector3_FromPyObject(self->viewX)), UnitVector3(Vector3_FromPyObject(self->viewY))));
    return 0;
}

static void __Camera_dealloc(Camera_o* self) 
{ 
    Py_DECREF(self->pos);
    Py_DECREF(self->viewX);
    Py_DECREF(self->viewY);
    Py_DECREF(self->viewZ);
    Py_DECREF(self->maxAngles);
    Py_DECREF(self->screenSize);
}

// Methods
Vector2_o Camera_RenderPoint( Camera* camera, Vector3 vector)
{
    Matrix3 viewMatrix = Matrix3_CreateNewStruct(UnitVector3(camera->viewX), UnitVector3(camera->viewY), camera->viewZ);
    Vector3 relPosition = Subtract3(vector, camera->pos);
    Vector3 scaledPosition = VectorMultiMatrix3(relPosition, viewMatrix);
    Vector3 scaledAngles = Angle3(scaledPosition);
    // std::cout   << "Point: " << Vector3_GetString(vector) << std::endl 
    //             << "View-Matrix: " << Matrix3_GetString(Matrix3_ObjectFromStructure(viewMatrix)) << std::endl 
    //             << "Rel-Position: " << Vector3_GetString(relPosition) << std::endl
    //             << "Scaled-Positon: " << Vector3_GetString(scaledPosition) << std::endl 
    //             << "Scaled-Angle: " << Vector3_GetString(scaledAngles) << std::endl;
    if ((Amount(scaledAngles.z) > camera->maxAngles.x) || (Amount(scaledAngles.y) > camera->maxAngles.y)) throw __SYVECTORS_RENDER_ERROR_NOT_IN_VIEW;
    return Vector2_CreateNewStruct(
        camera->screenSize.x / 2 * (scaledAngles.z / camera->maxAngles.x),
        camera->screenSize.y / 2 * (scaledAngles.y / camera->maxAngles.y)
    );
}

Line2 Camera_RenderLine( Camera* camera, Line3 line )
{
    Vector2 a = Camera_RenderPoint( camera, line.a );
    Vector2 b = Camera_RenderPoint( camera, line.b );
    Line2 line2 = Line2_CreateNewStruct(
        a, b
    );
    return line2;
}

RenderObj2 Camera_RenderObj( Camera* camera, RenderObj3 renderObj3 )
{
    RenderObj2 renderObj2;
    for (unsigned int i = 0; i < renderObj3.lines.size(); i++ ) {
        try { 
            renderObj2.lines.push_back( Camera_RenderLine(camera, renderObj3.lines[i]) ); 
        } catch ( ... ) { }
    }   return renderObj2;
}

static PyObject* _Camera_RenderPoint( Camera_o* self, PyObject* args )
{
    Camera camera = Camera_FromObject( (*self) ); PyObject* pointObj;
    if (!PyArg_ParseTuple(args, "O", &pointObj)) return NULL;
    Vector3 point = Vector3_FromPyObject(pointObj);
    try { Vector2_o rendered = Camera_RenderPoint(&camera, point); } catch (...) { return Py_None; }
    return Vector2_CreateNew( Camera_RenderPoint(&camera, point) );
}

static PyObject* _Camera_RenderLine( Camera_o* self, PyObject* args )
{
    Camera camera = Camera_FromObject( (*self) ); PyObject* lineObj; Line3 line;
    if (!PyArg_ParseTuple(args, "O", &lineObj)) return NULL;
    try { line = Line3_FromObject( Line3_FromPyObject(lineObj) ); } catch (...) { return Py_None; }
    return Line2_CreateNew( Camera_RenderLine( &camera, line ) );
}

static PyObject* _Camera_RenderObj( Camera_o* self, PyObject* args )
{   
    Camera camera = Camera_FromObject( (*self) ); PyObject* renderObj;
    if (!PyArg_ParseTuple(args, "O", &renderObj)) return NULL;
    RenderObj3 render = RenderObj3_FromObject( RenderObj3_FromPyObject( renderObj ) );
    return RenderObj2_CreateNew( Camera_RenderObj( &camera, render ) );
}

// Member definition
PyMemberDef __Camera_members[] = {
    { "pos", T_OBJECT, offsetof(Camera_o, pos), 0, "The Position of the Camera" },
    { "viewX", T_OBJECT, offsetof(Camera_o, viewX), 0, "The view-unit-X-vector of the Camera" },
    { "viewY", T_OBJECT, offsetof(Camera_o, viewY), 0, "The view-unit-Y-vector of the Camera" },
    { "viewZ", T_OBJECT, offsetof(Camera_o, viewZ), 0, "The view-unit-Z-vector of the Camera" },
    { "maxAngles", T_OBJECT, offsetof(Camera_o, maxAngles), 0, "The max viewAngles in X and Y" },
    { "screenSize", T_OBJECT, offsetof(Camera_o, screenSize), 0, "The screen size" },
    { NULL }
};

PyMethodDef __Camera_methods[] = {
    { "RenderPoint", (PyCFunction)_Camera_RenderPoint, METH_VARARGS, "Render the given Point from a 3D Coordinate-System to a 2D-Screen point"},
    { "RenderLine", (PyCFunction)_Camera_RenderLine, METH_VARARGS, "Render the given Line from a 3D Coordinate-System to a 2D-Screen line"},
    { "RenderObj", (PyCFunction)_Camera_RenderObj, METH_VARARGS, "Render the given RenderObj from a 3D Coordinate-System to a 2D-Screen object"},
    { NULL }
};

// Type
static PyTypeObject Camera_t = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "SyVectors.Camera",                         /* tp_name */
    sizeof(Camera),                             /* tp_basicsize */
    0,                                          /* tp_itemsize */
    (destructor)__Camera_dealloc,               /* tp_dealloc */
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
    "A 3D Camera",                              /* tp_doc */
    0,                                          /* tp_traverse */
    0,                                          /* tp_clear */
    0,                                          /* tp_richcompare */
    0,                                          /* tp_weaklistoffset */
    0,                                          /* tp_iter */
    0,                                          /* tp_iternext */
    __Camera_methods,                           /* tp_methods */
    __Camera_members,                           /* tp_members */
    0,                                          /* tp_getset */
    0,                                          /* tp_base */
    0,                                          /* tp_dict */
    0,                                          /* tp_descr_get */
    0,                                          /* tp_descr_set */
    0,                                          /* tp_dictoffset */
    (initproc)__Camera_init,                    /* tp_init */
    0,                                          /* tp_alloc */
    (newfunc)PyType_GenericNew,                 /* tp_new */
};

# endif