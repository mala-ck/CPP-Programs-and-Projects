#include <iostream>
#include "Vector3D.h"
using namespace std;

/* Program for 3D vector operations */


int main()
{

    // Initialization
    VECTOR_3D<float> x(-1,-1,-1);
    VECTOR_3D<float> y(9.2,10,11.1);

    VECTOR_3D<float> a;


    // Examples

    cout<< "Vector assignment: " << endl;
    a = x;
    cout<<"x is " << x << " and after a=x, a is "<< a << endl;

    cout<< "Vector negation: " << endl;
    a = x;
    cout<< "x is " << x<<", -x is " << -a << endl;
    a = y;
    cout<< "y is " << y<<", -y is " << -a << endl;



    std::cout<< "Vector addition: " << std::endl;
    std::cout<< x << " + " << y << " = " << (x + y) << std::endl;
    std::cout<< y << " + " << x << " = " << (x + y) << std::endl;

    a = x;
    a += y;
    std::cout<< x << " += " << y << " = " << a << std::endl;
    a = y;
    a += x;
    std::cout<< y << " += " << x << " = " << a << std::endl;

    std::cout<< "Vector subtraction: " << std::endl;
    std::cout<< x << " - " << y << " = " << (x - y) << std::endl;
    std::cout<< y << " - " << x << " = " << (y - x) << std::endl;
    a = x;
    a -= y;
    std::cout<< x << " -= " << y << " = " << a << std::endl;
    a = y;
    a -= x;
    std::cout<< y << " -= " << x << " = " << a << std::endl;

    std::cout<< "Vector inner/dot product: " << std::endl;
    std::cout<< x << " * " << y << " = " << (x * y) << std::endl;
    std::cout<< y << ".dot(" << x << ") = " << (y.dot(x)) << std::endl;

    std::cout<< "Vector outer/cross product: " << std::endl;
    std::cout<< x << " % " << y << " = " << (x % y) << std::endl;
    a = x;
    a %= y;
    std::cout<< x << " %= " << y << " = " << a << std::endl;
    std::cout<< x << ".cross(" << y << ") = " << (x.cross(y)) << std::endl;

    std::cout << "Vector length: " << std::endl;
    std::cout<< x << ".length() = " << x.length() << std::endl;
    std::cout<< y << ".length() = " << y.length() << std::endl;

    std::cout << "Vector scaling: " << std::endl;
    std::cout<< x << " / " << 2 << " = " << x/2 << std::endl;
    a = x;
    a /= 2;
    std::cout<< x << " /= " << 2 << " = " << a << std::endl;

    std::cout << "Vector scaling: " << std::endl;
    std::cout<< x << " / " << 0 << " = " << x/0 << std::endl;
    a = x;
    a /= 0;
    std::cout<< x << " /= " << 0 << " = " << a << std::endl;

    std::cout<< x << " * " << 2 << " = " << x*2 << std::endl;
    a = x;
    a *= 2;
    std::cout<< x << " *= " << 2 << " = " << a << std::endl;

    std::cout << "Vector comparison: " << std::endl;
    std::cout<< x << " == " << y << " is ";
    if(x == y)
        cout << "True" << std::endl;
    else
        cout << "False" << std::endl;

    std::cout<< x << " != " << y << " is ";
    if(x != y)
        cout << "True" << std::endl;
    else
        cout << "False" << std::endl;

    return 0;
}

