#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

const int Size = 6;

double findSumForA(vector<double>& array, int degree) {
  double sum = 0;
  for (int i = 0; i < Size; i++) {
    sum += pow(array[i], degree);
  }
  return sum;

}
double findSumForB(vector<double>& x, vector<double>& y, int degree) {
    double sum = 0;
    for (int i = 0; i < Size; i++) {
      sum+= pow(x[i], degree)*y[i];
    }
    return sum;
}

double determinant(vector<vector<double>>& matr) {
    if (matr.size() == 1) return matr[0][0];
    double answ = 0;
    vector<vector<double>> mt(matr.size()-1, (vector<double>(matr.size()-1, 0)));
    for (int i = 0; i < matr.size(); i++) {
        for (int j = 1; j < matr.size(); j++) {
            for (int k = 0; k < matr.size(); k++) {
                if (k == i) continue;
                else mt[j - 1][k > i ? k - 1 : k] = matr[j][k];
            }
        }
        answ += matr[0][i] * determinant(mt) * (i & 1 ? -1 : 1);
    }
    return answ;
}

void Cramer(vector<vector<double>>& matr, vector<double>& b, vector<double>& x) {
    cout << "Matrix:" << endl;
    for(int i = 0; i < matr.size(); i++){
        for(auto j : matr[i]){
            printf("%#.3f ", j);
        }
        printf("%#.3f ", b[i]);
        cout << endl;
    }
    cout << endl;
    double d = determinant(matr);
    for (int i = 0; i < x.size(); i++) {
        swap(matr[i], b);
        double di = determinant(matr);
        x[i] = di / d;
        swap(matr[i], b);;
    }
}

void LeastSquares(vector<double>& x, vector<double>& y, int m) {
    ++m;
    vector<double> b(m, 0), results(m, 0);
    vector<vector<double>> matr;
    for (int i = 0; i < m; i++) {
        matr.push_back(vector<double>());
        for (int j = 0; j < m; j++) {
            if (i == 0 && j == 0) {
                matr[i].push_back(Size);
            } else {
                matr[i].push_back(findSumForA(x, i+j));
            }
        }
        b[i] = findSumForB(x, y, i);
    }
    Cramer(matr, b, results);
    cout << "P^" << m-1 <<  " = ";
    for(int i = 0; i < m; i++){
        cout << ((i)?((results[i] > 0)? " + ": " - "):"") << abs(results[i]) << "*x^" << i << " ";
    }
    cout << endl << endl;
}

int main() {

    freopen("file9.txt", "r", stdin);
    vector<double> x(Size), y(Size);
    for (long i = 0; i < Size; i++) {
        cin >> x[i];
        cout << x[i] << " ";
    }
    cout << endl;
    for (long i = 0; i < Size; i++) {
        cin >> y[i];
        cout << y[i] << " ";
    }
    cout << endl << endl;
    LeastSquares(x, y, 1);
    LeastSquares(x, y, 2);
    LeastSquares(x, y, 3);
}