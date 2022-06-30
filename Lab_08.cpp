#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <stdio.h>
#include <stdarg.h>

using namespace std;
const int Size = 10;

long double Lagrange(vector<long double>& x, vector<long double>& y, long double x0) {
    cout << "--------------------Lagrange----------------------" << endl;
    long double h = -1;
    long double sum = 0;
    long long sz = x.size();
    for (long i = 2; i < sz; i++) {
        if ((x[i] - x[i - 1]) - (x[1] - x[0])) h = x[1] - x[0];
        else {
            h = -1;
            break;
        }
    }
    for (long i = 0; i < sz; i++) {
        long double ch = 1, zn = 1;
        for (long j = 0; j < sz; j++) {
            if (j == i) continue;
            if (h == -1) {
                ch *= (x0 - x[j]);
                zn *= (x[i] - x[j]);
            }
            else {
                ch *= (x0 - (x[0] + j * h));
                zn *= h * (i - j);
            }
        }
        sum += y[i] * (ch / zn);
        cout << i+1 << ". " << "Ch: " << ch << "\tZn: " << zn << endl;
    }
    return sum;
}

long double Newton(vector<long double>& x, vector<long double>& y, long double x0) {
    cout << "--------------------Newton----------------------" << endl; 
    long double result = y[0];
    long double prod2 = x0 - x[0];
    long double prod1 = 1, f = 0;
    for (long i = 1; i < x.size(); i++) {
        f = 0;
        for(long j = 0; j <= i; j++){
            prod1 = 1;
            for(long k = 0; k <= i; k++){
                if(k != j) prod1 *= x[j] - x[k];
            }
            f += y[j] / prod1;
        }
        string str = (i > 4)?"\tProduct: ":"\t\tProduct: ";
        cout << i << ". " << "F: " << f << str << prod2 << endl;
        result += f*prod2;
        prod2 *= x0-x[i];
    }
    return result;
}

int main() {
    freopen("file8.txt", "r", stdin);
    vector<long double> x(Size), y(Size);
    for (long i = 0; i < Size; i++) {
        cin >> x[i];
    }
    for (long i = 0; i < Size; i++) {
        cin >> y[i];
    }
    long double x0;
    cin >> x0;
    cout  << Lagrange(x, y, x0) << endl;
    cout  << Newton(x, y, x0)  << endl;
}