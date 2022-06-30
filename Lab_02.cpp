#include <iostream>
#include <string>
#include <cmath>
#include <float.h>
using namespace std;

double eps = 0.00001;
double tempX = 0;

double func(double x)
{
    double result = x * x * x + 0.2 * x * x - 0.6 * x + 1.5;
    if (result < eps && result > -eps)
        result = 0;
    return result;
}

double derivative(double x)
{
    return 3 * x * x + 0.4 * x - 0.6;
}

double derivative2(double x)
{
    return 6 * x + 0.4;
}

double newton(double x)
{
    if (abs(tempX - x) < eps) return x;
    tempX = x;
    cout << "x: " << x << endl;
    return newton(x - (func(x) / derivative(x)));
}

double phi(double x)
{
    return x - func(x) / (5);  
}

double fixedPointIteration(double x)
{
    if (abs(tempX - x) < eps) return x;
    tempX = x;
    cout << "x: " << x << endl;
    return fixedPointIteration(phi(x));
}

double prepareNewton(double a, double b)
{
    tempX = 0;
    if (func(a) * derivative2(a) > 0)
    {
        return newton(a);
    }
    else if (func(b) * derivative2(b) > 0)
    {
        return newton(b);
    }
    else
    {
        cout << "Something went wrong" << endl;
        return 0;
    }
}

double reduceInterval(double a, double b)
{
    double num;
    if (a == -1000)
    {
        num = b;
        while (func(num) * func(--num) >= 0);
    }
    else
    {
        num = a;
        while (func(num) * func(num++) >= 0 && num < b);
    }
    return num;
}

int solve(double *coefs, double *x1, double *x2)
{
    double a = coefs[0], b = coefs[1], c = coefs[2];
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) return 0;
    *x1 = (-b - sqrt(discriminant)) / (2 * a);
    *x2 = (-b + sqrt(discriminant)) / (2 * a);
    return 1;
}

int main()
{
    double coefficients[3] = {3, 0.4, -0.6};
    double res1, res2;
    cout << "Enter eps: ";
    cin >> eps;
    solve(coefficients, &res1, &res2);
    cout << "Check: " << derivative(res1) << " " << derivative(res2) << endl;
    double intervalStart;
    if (func(-1000) * func(res1) < 0)
    {
        intervalStart = reduceInterval(-1000, res1);
        cout << "a: " << intervalStart << endl;
        cout << "b: " << intervalStart + 1 << endl;
        cout << "max hald deriv on [a, b] (phi): " 
             << max(derivative(intervalStart) / 2, derivative(intervalStart + 1) / 2) << endl;
        cout << "\nNewton: \n" << prepareNewton(intervalStart, intervalStart + 1) 
             << "\nfixedPointIteration: \n" << fixedPointIteration(intervalStart + 0.5) << endl;
    }
    if (func(res1) * func(res2) < 0)
    {
        intervalStart = reduceInterval(res1, res2);
        cout << "\nNewton: \n" << prepareNewton(intervalStart, intervalStart + 1) 
             << "\nfixedPointIteration: \n" << fixedPointIteration(intervalStart + 0.5) << endl;
    }
    if (func(res2) * func(1000) < 0)
    {
        intervalStart = reduceInterval(res2, 1000);
        cout << "\nNewton: \n" << prepareNewton(intervalStart, intervalStart + 1) 
             << "\nfixedPointIteration: \n" << fixedPointIteration(intervalStart + 0.5) << endl;
    }

    return 0;
}