#include <iostream>
#include <cmath>

using namespace std;

const double eps = 0.001;

double func(double x, double y, int n) {
    switch (n) {
        case 1: 
            return 1.5 - cos(y);
        case 2: 
            return 0.5 + sin(x - 0.5) / 2;  
        default:
            return 0;
    }
}

void simpleIterations() {
    cout << "-------------------Simple Iterations------------------" << endl;
    double x0 = 1, y0 = 1, x, y, dx, dy;
    int i = 0;
    do {
        x = func(x0, y0, 1);
        y = func(x0, y0, 2);
        dx = func(x, y, 1) - x;
        dy = func(x, y, 2) - y;
        x0 = x;
        y0 = y;
        i++;
    } while (fabs(dx) > eps || fabs(dy) > eps);

    cout << "x = " << dx + x << " " << "y = " << dy + y << " iterations:" << i << endl;
}

// Частинні похідні функцій
double Jac(double x, double y, int n, int m) {      
    if (n == 0) {
        if (m == 0) return -cos(x - 0.5);
        if (m == 1) return 2;
    }
    else if (n == 1) {
        if (m == 0) return 1;
        if (m == 1) return -sin(y);
    } 
    cout << "Something went wrong!";
    return 0;
}

// Функція, яка повертає значення F(x, y)
double Func(double x, double y, int n) {           
    switch (n) {
        case 1:
            return 2*y - sin(x - 0.5) - 1;
        case 2:
            return -1.5 + cos(y) + x;
        default:' '
            return 0;
    }
}

void Newton() {
    cout << "--------------------Newton Method--------------------" << endl;
    // Початкові значення
    double x0 = 1, y0 = 1, x = x0, y = y0, dx, dy, Jacoby[2][2]; 
    int i = 0;
    do {
        x0 = x;
        y0 = y;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                Jacoby[i][j] = Jac(x0, y0, i, j);
            }
        }
        std::cout << "Jacoby: " << std::endl;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                std::cout << Jacoby[i][j] << "\t";
            }
            std::cout << std::endl;
        }
        double Jacobyan = Jacoby[0][0]*Jacoby[1][1] - Jacoby[0][1]*Jacoby[1][0];
        // Правило Крамера
        dx = -1/Jacobyan*(Func(x0, y0, 1)*Jacoby[1][1] - Func(x0, y0, 2)*Jacoby[0][1]);   
        dy = -1/Jacobyan*(Func(x0, y0, 2)*Jacoby[0][0] - Func(x0, y0, 1)*Jacoby[1][0]);
        x = x0 + dx;
        y = y0 + dy;
        i++;
    } while (abs(dx) > eps && abs(dy) > eps);

    cout << "x = " << x << " " << "y = " << y << " iterations:" << i << endl;
}

int main() {
    simpleIterations();
    Newton();
}
