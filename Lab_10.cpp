#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <map>
#include <stdio.h>
#include <stdarg.h>

using namespace std;

const double eps = 1, coeff = 100000;
const int a = 0, b = 6;

double funcOld(double x){
    return pow(x, 3)*exp(x/3)*cosh(x);
}

double func(double x) {
    return sqrt(3 + x*x);
}

double derivative2(double x) {
    return 3*x*exp((4/3)*x) + 4*x*x*exp((4/3)*x) + (8*x*x*x*exp((4/3)*x))/9 + x*exp((-2/3)*x) * (3 - 2*x) + ((2*x*x*x)/(9*exp((2/3)*x)));
}

void ShowError(double h, int method) {
    if (method  == 3) return;
    cout << endl;
    cout << "Error: " << derivative2((b - a) / 2) / (24/method) * (b - a) * h * h << endl; 
}

double LeftRectangles(double a, double b, double h){
    double answ = 0, temp = 0;
    int n = (b-a)/h;
    cout << h << "* (";
    for(int i = 0; i < n; i++) {
        temp = func(a+i*h);
        answ += temp;
        cout << temp << "(x=" << a+i*h << ")" << " + ";
    }
    cout << ");\n";
    return h*answ;
}

double RightRectangles(double a, double b, double h){
    double answ = 0;
    int n = (b-a)/h;
    for(int i = 1; i <= n; i++){
        answ += func(a+i*h);
    }
    return h*answ;
}

double MiddleRectangles(double a, double b, double h){
    double answ = 0;
    int n = (b-a)/h;
    for(int i = 0; i < n; i++){
        answ += func(a+i*h + h/2);
    }
    return h*answ;
}

double Trapezoidal(double a, double b, double h){
    double answ = (func(a) + func(b))/2, temp = 0;
    int n = (b-a)/h;
    cout << h << "* (";
    cout << "(" << func(a) << " + " << func(b) << ")/2 + ";
    for(int i = 0; i < n - 1; i++) {
        temp = func(a+i*h + h);
        answ += temp;
        cout << temp << "(x=" << a+i*h + h << ")" << " + ";
    }
    cout << ");\n";
    return h*answ;
}

double Simpson(double a, double b, double h){
    double answ = 0;
    int n = (b-a)/h/2;
    for(int i = 1; i <= n; i++){
        if(i != n) answ += 2*func(a+2*i*h);
        answ += 4*func(a + (2*i-1)*h);
    }
    return h/3*(func(a) + func(a + 2*n*h) + answ);
}

double DefiniteIntegral(double h, double (*Integral)(double a, double b, double h), int n){
    while(fabs(Integral(a, b, h/2) - Integral(a, b, h)) > eps){
        h /= 2;
    } 
    ShowError(h/2, n);
    return Integral(a, b, h/2) / coeff;   
}

int main() {
    double a = 2, b = 6, h = (b - a) / 10;
    cout << "a: " << a << " b: " << b << endl;

    // double rectH = pow(eps, 1.0/2.0), h = rectH;
    cout << endl;
    cout << "Left rectangles method: " << LeftRectangles(a, b, h) << endl;
    // h = rectH;
    // cout << "Middle rectangles method: " << DefiniteIntegral(h, MiddleRectangles, 1) << " * 10^5" << endl;
    // h = rectH;
    // cout << "Right rectangles method: " << DefiniteIntegral(h, RightRectangles, 1) << " * 10^5" << endl;
    // h = rectH;
    cout << "Trapezoidal rule: " << Trapezoidal(a, b, h) << endl;
    // h = pow(eps, 1);
    // cout << "Simpson's method: " << DefiniteIntegral(h, Simpson, 3) << " * 10^5" << endl;
}
