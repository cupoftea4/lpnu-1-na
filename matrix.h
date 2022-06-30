#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <algorithm>
#include <fstream>

using std::string;

class Matrix
{
public:
    Matrix();
    Matrix(int n, int m);
    Matrix(Matrix &matr);
    Matrix(std::ifstream& file, int rows, int cols);
    ~Matrix(); 
    void Free();

    double FindMax();
    double FindArithmeticMean();
    void SortRowAcsending(int index);
    void SortColumnDescending(int index);
    void FillRandom();
    Matrix * Pow(int n);
    Matrix * Transpose();
    Matrix * Inverse3();
    double Determinant3();
    double Minor3(int i, int j);

    int GetRows() { return rows; }
    int GetCols() { return cols; }
    void SetSize(int rows, int cols);
    double* &operator[](const int &index) const;

    Matrix * operator+(const Matrix &matr);
    Matrix * operator-(const Matrix &matr);
    Matrix * operator*(const Matrix &matr);
    Matrix * operator=(Matrix  * matr);
    Matrix * operator*(const double coeff);
    void Print(string header="");

    void SetAt (int i, int j, double num) { if (i >= 0 && i < rows && j >= 0 && j < cols) matrix[i][j] = num; }
    double At (int i, int j) const { return matrix[i][j];  }


private:
    void AllocMatrix();
    enum SortWay { Descending, Ascending };
    int Min(const double * array, int start, int n);
    int Max(const double * array, int start, int n);
    void Swap(double * array, int n, int m);
    void SelectionSort(double * array, int n, SortWay way);
    double ** matrix = nullptr;
    int rows = 0;
    int cols = 0;
};

#endif // MATRIX_H
