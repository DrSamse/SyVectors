# ifndef _SYVECTORS_HIGH_DETAIL_HPP_
# define _SYVECTORS_HIGH_DETAIL_HPP_

# include "../Shapes/Line3.hpp"
# include "RenderObject3.hpp"
# include "../Vectors/VMath.hpp"
# include <iostream>

# define SYVECTORS_QUALITY_LOW 10
# define SYVECTORS_QUALITY_MEDIUM 100
# define SYVECTORS_QUALITY_HIGH 1000

RenderObj3 Line3_SplitDown( Line3 line, int quality = SYVECTORS_QUALITY_LOW )
{
    RenderObj3 renderObj;
    double intervall = 1 / (double)quality;
    Vector3 direct = Subtract3(line.b, line.a);
    double length = Amount3(direct);
    int breakAmount = (int)(length / intervall) + 1;
    Vector3 prevPoint = line.a;
    Vector3 currentPoint;
    for (int i = 1; i < breakAmount; i++) {
        currentPoint = Add3( line.a, Scale3(direct, (double)i/(double)breakAmount));
        renderObj.lines.push_back(Line3_CreateNewStruct(prevPoint, currentPoint));
        prevPoint = currentPoint;
    }   renderObj.lines.push_back(Line3_CreateNewStruct(prevPoint, line.b));
    return renderObj;
}

static PyObject* PyLine3_SplitDown( PyObject* self, PyObject* args )
{
    PyObject* lineObj; int quality = SYVECTORS_QUALITY_LOW;
    if (!PyArg_ParseTuple(args, "O|i", &lineObj, &quality)) return NULL;
    RenderObj3 obj = Line3_SplitDown(Line3_FromObject(Line3_FromPyObject(lineObj)), quality);
    return RenderObj3_CreateNew(obj);
}

# endif