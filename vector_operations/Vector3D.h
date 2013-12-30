#ifndef VECTOR3D_H
#define VECTOR3D_H

#endif // VECTOR3D_H
#include <math.h>
#include <iostream>

using namespace std;

/* 3-dimensional Vector class.
 * The class calculates vector addition, subtraction, Euclidean norm, and an inner product.
 */

template <class T>
class VECTOR_3D
{
    T x;
    T y;
    T z;

public:

    // Constructors
    VECTOR_3D()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    VECTOR_3D(T a, T b, T c):x(a), y(b), z(c)
    {

    }

    // Vector assignment operator
    VECTOR_3D<T>& operator =(VECTOR_3D<T> const &v);

    // Vector Arithmetic operations

    // Vector negation
    VECTOR_3D<T> operator -() const;

    // Vector addition
    VECTOR_3D<T> operator +(VECTOR_3D<T> const &v);
    VECTOR_3D<T>& operator +=(VECTOR_3D<T> const &v);

    // Vector subtraction
    VECTOR_3D<T> operator -(VECTOR_3D<T> const &v);
    VECTOR_3D<T>& operator -=(VECTOR_3D<T> const &v);


    // Vector comaprison operators === and !=
    bool operator ==(VECTOR_3D const &v);
    bool operator !=(VECTOR_3D const &v);


    // Vector dot product
    T operator *(VECTOR_3D<T> const &v);
    T dot(VECTOR_3D const &v);


    // Vector cross product
    VECTOR_3D<T> operator %(VECTOR_3D<T> const &v);
    VECTOR_3D<T>& operator %=(VECTOR_3D<T> const &v);
    VECTOR_3D<T> cross(VECTOR_3D<T> const &v);

    // Scaling operaitons
    VECTOR_3D<T> operator /(float scalr);
    VECTOR_3D<T>& operator /=(float scalar);
    VECTOR_3D<T> operator *(float scalr);
    VECTOR_3D<T>& operator *=(float scalar);

    // Magnitude/length/euclidian norm of a vector
    float length();

    // Overloading output stream operator
    friend ostream& operator <<(ostream &os, VECTOR_3D<T> const &v)
    {
        os << "[ " << v.x << ", " << v.y << ", " << v.z << "]";
        return os;
    }

}; // End of class description

// Vector assignment operator
template <class T>
VECTOR_3D<T>& VECTOR_3D<T>::operator =(VECTOR_3D<T> const &v)
{
    // do the copy
    x = v.x;
    y = v.y;
    z = v.z;
    // return the existing object
    return *this;
}


// Vector arithmetic

// Vector negation
template <class T>
VECTOR_3D<T> VECTOR_3D<T>::operator -() const
{
    VECTOR_3D<T> tmp;

    tmp.x = -x;
    tmp.y = -y;
    tmp.z = -z;

    return tmp;
}

// Vector addition
template <class T>
VECTOR_3D<T> VECTOR_3D<T>::operator +(VECTOR_3D<T> const &v)
{
    VECTOR_3D<T> result;

    result.x = x + v.x;
    result.y = y + v.y;
    result.z = z + v.z;

    return result;
}

template <class T>
VECTOR_3D<T>& VECTOR_3D<T>::operator +=(VECTOR_3D<T> const &v)
{

    x = x + v.x;
    y = y + v.y;
    z = z + v.z;

    return *this;
}

// Vector subtraction
template <class T>
VECTOR_3D<T> VECTOR_3D<T>::operator -(VECTOR_3D<T> const &v)
{
    VECTOR_3D<T> result;

    result.x = x - v.x;
    result.y = y - v.y;
    result.z = z - v.z;

    return result;
}

template <class T>
VECTOR_3D<T>& VECTOR_3D<T>::operator -=(VECTOR_3D<T> const &v)
{

    x = x - v.x;
    y = y - v.y;
    z = z - v.z;

    return *this;
}


// Dot product
template <class T>
T VECTOR_3D<T>::operator *(VECTOR_3D<T> const &v)
{
    T result = 0;

    result += (x * v.x);
    result += (y * v.y);
    result += (z * v.z);

    return result;

}

template <class T>
T VECTOR_3D<T>::dot(VECTOR_3D const &v)
{
    T result = 0;

    result += (x * v.x);
    result += (y * v.y);
    result += (z * v.z);

    return result;

}


// Cross product
template <class T>
VECTOR_3D<T> VECTOR_3D<T>::operator %(VECTOR_3D<T> const &v)
{
    /*cx = aybz - azby
    cy = azbx - axbz
    cz = axby - aybx*/

    VECTOR_3D<T> result;

    result.x = (y * v.z) - (z * v.y);
    result.y = (z * v.x) - (x * v.z);
    result.z = (x * v.y) - (y * v.x);

    return result;

}

template <class T>
VECTOR_3D<T>& VECTOR_3D<T>::operator %=(VECTOR_3D<T> const &v)
{
    /*cx = aybz - azby
    cy = azbx - axbz
    cz = axby - aybx*/
    VECTOR_3D<T> result;

    result.x = (y * v.z) - (z * v.y);
    result.y = (z * v.x) - (x * v.z);
    result.z = (x * v.y) - (y * v.x);

    *this = result;

    return *this;

}

template <class T>
VECTOR_3D<T> VECTOR_3D<T>::cross(VECTOR_3D<T> const &v)
{
    /*cx = aybz - azby
    cy = azbx - axbz
    cz = axby - aybx*/

    VECTOR_3D result;
    result.x = (y * v.z) - (z * v.y);
    result.y = (z * v.x) - (x * v.z);
    result.z = (x * v.y) - (y * v.x);

    return result;

}

// Length/ eculidian norm/ magnitude
template <class T>
float VECTOR_3D<T>::length()
{
    float result = 0;

    result += x * x;
    result += y * y;
    result += z * z;

    return(sqrt(result));

}

// Comparison operators
template <class T>
bool VECTOR_3D<T>::operator ==(VECTOR_3D const &v)
{

    if((fabs(x - v.x) < 0.00001) &&
            (fabs(y - v.y) < 0.00001) &&
            (fabs(z - v.z) < 0.00001) ) return true;
    else
        return false;

}

template <class T>
bool VECTOR_3D<T>::operator !=(VECTOR_3D const &v)
{
    if(*this == v)
        return false;
    else
        return true;

}

// Scalar operations , scalar division and scalar multiplication
template <class T>
VECTOR_3D<T> VECTOR_3D<T>::operator /(float scalar)
{
    VECTOR_3D<T> result;

    result.x = x/scalar;
    result.y = y/scalar;
    result.z = z/scalar;

    return result;
}

template <class T>
VECTOR_3D<T>& VECTOR_3D<T>::operator /=(float scalar)
{
    if( fabs(scalar) < 0.00001 ) return *this;
    x = x/scalar;
    y = y/scalar;
    z = z/scalar;

    return *this;
}

template <class T>
VECTOR_3D<T> VECTOR_3D<T>::operator *(float scalar)
{
    VECTOR_3D<T> result;

    result.x = x*scalar;
    result.y = y*scalar;
    result.z = z*scalar;

    return result;
}

template <class T>
VECTOR_3D<T>& VECTOR_3D<T>::operator *=(float scalar)
{
    if( fabs(scalar) < 0.00001 ) return *this;
    x = x*scalar;
    y = y*scalar;
    z = z*scalar;

    return *this;
}
