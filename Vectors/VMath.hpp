# ifndef _SYMESVECTORS_VMATH_HPP_
# define _SYMESVECTORS_VMATH_HPP_

# include <math.h>

# include "Vector3.hpp"
# include "Matrix3.hpp"

double Amount( double x )
{
    if ( x < 0 ) return -x; 
    return x;
}

/** A fully defined arctan function.            
 *   [ y = 1, x = 0 ]   => returns PI / 2    
 *   [ y = -1, x = 0 ]  => returns 3PI / 2  
 */
double DefinedAtan( double x, double y )
{
    if (x == 0) {
        if (y > 0) {
            return Py_MATH_PI / 2;
        } else if (y < 0) {
            return Py_MATH_PI * 3 / 2;
        } else {
            return NULL;
        }
    } else {
        return atan(y / x);
    }
}

Vector3_o Add3( Vector3_o a, Vector3_o b )
{
    return Vector3_CreateNewStruct(a.x + b.x, a.y + b.y, a.z + b.z);
}

double Amount3( Vector3_o vector )
{
    return sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
}

Vector3_o Angle3( Vector3_o vector )
{
    return Vector3_CreateNewStruct(DefinedAtan(vector.y, vector.z), DefinedAtan(vector.x, vector.z), DefinedAtan(vector.x, vector.y));
}

Vector3_o CrossProduct( Vector3_o a, Vector3_o b )
{
    return Vector3_CreateNewStruct(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

Vector3_o Scale3( Vector3_o v, double a ) {  return Vector3_CreateNewStruct(v.x * a, v.y * a, v.z * a);  }

Vector3_o Subtract3( Vector3_o a, Vector3_o b ) {  return Vector3_CreateNewStruct(a.x - b.x, a.y - b.y, a.z - b.z);  }

Vector3_o UnitVector3( Vector3_o v ) {  return Scale3(v, 1 / Amount3(v));  }

Vector3_o VectorMultiMatrix3( Vector3_o v, Matrix3 m )
{
    return Vector3_CreateNewStruct(
        (m.x.x + m.x.y + m.x.z) * v.x,
        (m.y.x + m.y.y + m.y.z) * v.y,
        (m.z.x + m.z.y + m.z.z) * v.z
    );
}

# endif