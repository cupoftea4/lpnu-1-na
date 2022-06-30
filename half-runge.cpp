#include <iostream>
#include <array>
#include <list>
#include <math.h>

double eps = 0.01;
using std::cout;
using std::endl;

double func(double x)
{
    double result = 2.0 / x + x - 4;
    return result;
}

double func(double x, double y)
{
    double result = x * x * y - 2;
    return result;
}

double half(double a, double b)
{
    double middle = (a + b) / 2.0f;
    cout.width(10);
    cout << "a: " << a;
    cout.width(10);
    cout << "| b: " << b;
    cout.width(10);
    cout << "| Middle: " << middle;
    cout.width(10);
    cout <<  "| Func: " << func(middle) << std::endl;
    if (func(middle) == 0 || fabs(b - a) < eps)
        return middle;
    if (func(a) * func(middle) < 0) {
        return half(a, middle);
    }else {
        return half(middle, b);
    }

}

double calcDeltaY(double x, double y, double h) {
    double k1 = h * func(x, y);
    cout << "k1:" << k1 << " (1 * " << func(x, y) << ");" << endl;
    double k2 = h * func(x + h / 2.0, y + k1 / 2.0);
    cout << "k2:" << k2 << " (1 * " << func(x + h / 2.0, y + k1 / 2.0) << ");"  << endl;
    double k3 = h * func(x + h / 2.0, y + k2 / 2.0);
    cout << "k3:" << k3 << " (1 * " << func(x + h / 2.0, y + k2 / 2.0) << ");" << endl;
    double k4 = h * func(x + h, y + k3);
    cout << "k4:" << k4 << " (1 * " << func(x + h, y + k3) << ");" << endl;
    double k = (k1 + 2 * k2 + 2 * k3 + k4) / 6.0; 
    cout << "DeltaY: " << k << " (1/6 * (" << k1 << " + " << 2 * k2 << " + " << 2 * k3 << " + " << k4 << "))" << endl;
    return k;
}

int main() {
//    std::cout << half(2, 4);
   double y = 0, x0 = 0, h = 1;
   for (int x = x0; x < 2; x += h) {
       double deltaY = calcDeltaY(x, y, h);
       cout << "Y0: " << y << " + ";
       y += deltaY;
       cout << "DeltaY: " << deltaY << " = " << "Y: " << y << endl;

   }


}