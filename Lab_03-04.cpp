// Варіант 14

#include <iostream>
#include <cmath>
#include <string>

using namespace std;

void DisplayMatrix(double const arrayA[][3], double const arrayB[], int size, string msg)
{
    cout << msg << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << arrayA[i][j] << "\t";
        }
        cout << arrayB[i] << endl;
    }
}

double determinant(double array[][3])
{
    double answer;
    double diagonal = array[0][0] * array[1][1] * array[2][2];
    double triangle1 = array[0][1] * array[1][2] * array[2][0];
    double triangle2 = array[0][2] * array[1][0] * array[2][1];
    double antidiagonal = array[0][2] * array[1][1] * array[2][0];
    double antitriangle1 = array[0][0] * array[1][2] * array[2][1];
    double antitriangle2 = array[1][0] * array[0][1] * array[2][2];
    answer = diagonal + triangle1 + triangle2 - antidiagonal - antitriangle1 - antitriangle2;
    return answer;
}

void copyMatrix(double const stablearray[][3], double tmpArray[][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            tmpArray[i][j] = stablearray[i][j];
        }
    }
}
void Cramer(double stablearray[][3], double arrayB[])
{
    double tmparray[3][3];
    double deltax, deltay, deltaz;
    int tabulation;
    double a;
    cout << "Array determinant: ";
    a = determinant(stablearray);
    cout << a << endl;
    copyMatrix(stablearray, tmparray);
    cout << "Delta x matrix: " << endl;
    for (int i = 0; i < 3; i++)
    {
        tmparray[i][0] = arrayB[i];
    }
    for (int i = 0; i < 3; i++)
    {
        tabulation = 0;
        for (int j = 0; j < 3; j++)
        {
            tabulation++;
            cout << tmparray[i][j] << " ";
            if (tabulation == 3)
                cout << endl;
        }
    }
    cout << "Delta x determinant: ";
    deltax = determinant(tmparray);
    cout << deltax << endl;

    cout << "Delta y matrix: " << endl;
    copyMatrix(stablearray, tmparray);
    for (int i = 0; i < 3; i++)
    {
        tmparray[i][1] = arrayB[i];
    }
    for (int i = 0; i < 3; i++)
    {
        tabulation = 0;
        for (int j = 0; j < 3; j++)
        {
            tabulation++;
            cout << tmparray[i][j] << " ";
            if (tabulation == 3)
                cout << endl;
        }
    }
    cout << "Delta y determinant: ";
    deltay = determinant(tmparray);
    cout << deltay << endl;

    cout << "Delta z matrix: " << endl;
    copyMatrix(stablearray, tmparray);
    for (int i = 0; i < 3; i++)
    {
        tmparray[i][2] = arrayB[i];
    }
    for (int i = 0; i < 3; i++)
    {
        tabulation = 0;
        for (int j = 0; j < 3; j++)
        {
            tabulation++;
            cout << tmparray[i][j] << " ";
            if (tabulation == 3)
                cout << endl;
        }
    }
    cout << "Delta z determinant: ";
    deltaz = determinant(tmparray);
    cout << deltaz << endl;

    cout << "Result x: " << deltax / a << endl;
    cout << "Result y: " << deltay / a << endl;
    cout << "Result z: " << deltaz / a << endl;
}
double detMinor(double mas[3][3], int i, int j)
{
    double minor[4];
    int k = 0;

    for (int i1 = 0; i1 < 3; ++i1)
    {
        for (int j1 = 0; j1 < 3; ++j1)
        {
            if ((i1 != i) && (j1 != j))
            {
                minor[k] = mas[i1][j1];
                k++;
            }
        }
    }
    double det = minor[0] * minor[3] - minor[1] * minor[2];
    return det;
}
void cofactor(double arr[3][3], double cofactorMatr[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cofactorMatr[i][j] = pow(-1, i + j) * detMinor(arr, i, j) / determinant(arr);
        }
    }
}
void multiplyMatrixes(double first[3][3], double second[], double result[3][1])
{
    double sum = 0;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 1; ++j)
        {
            sum = 0;
            for (int k = 0; k < 3; ++k)
            {
                sum += first[i][k] * second[k];
            }
            result[i][j] = sum;
        }
    }
}

int findAbsMax(double matrix[][3], int n)
{
    int maxIndex = n, count = 3;
    for (int i = n + 1; i < count; ++i)
    {
        if (abs(matrix[i][n]) > abs(matrix[maxIndex][n]))
        {
            maxIndex = i;
        }
    }
    return maxIndex;
}

void swapRows(double matrix[][3], double arrayB[], int n, int m)
{
    double tmp;
    for (int k = 0; k < 3; k++)
    {
        tmp = matrix[m][k];
        matrix[m][k] = matrix[n][k];
        matrix[n][k] = tmp;
    }
    tmp = arrayB[m];
    arrayB[m] = arrayB[n];
    arrayB[n] = tmp;
}

void TriangularMatrix(double arrayA[][3], double *arrayB)
{
    double m = 0;
    int maxI;
    for (int i = 0; i < 3; ++i)
    {
        swapRows(arrayA, arrayB, i, findAbsMax(arrayA, i));
        for (int j = i + 1; j < 3; j++)
        {
            m = arrayA[j][i] / arrayA[i][i];
            arrayB[j] -= m * arrayB[i];
            for (int k = i; k < 3; k++)
                arrayA[j][k] -= m * arrayA[i][k];
        }
    }
}

void Gauss(double const arrayA[][3], double *const arrayB)
{
    cout << "----------------------------------------------------------------"
         << "\nGauss method" << endl;
    double tempMatrixA[3][3], tempMatrixB[3];
    double x1, x2, x3;
    copyMatrix(arrayA, tempMatrixA);
    for (int i = 0; i < 3; i++)
        tempMatrixB[i] = arrayB[i];
    TriangularMatrix(tempMatrixA, tempMatrixB);
    DisplayMatrix(tempMatrixA, tempMatrixB, 3, "Triangular Matrix: ");
    x3 = tempMatrixB[2] / tempMatrixA[2][2];
    x2 = (tempMatrixB[1] - tempMatrixA[1][2] * x3) / tempMatrixA[1][1];
    x1 = (tempMatrixB[0] - (tempMatrixA[0][1] * x2 + tempMatrixA[0][2] * x3)) / tempMatrixA[0][0];
    cout << "x1: " << x1 << "\nx2: " << x2 << "\nx3: " << x3 << endl;
    cout << "----------------------------------------------------------------" << endl;
}

void LUDecomposition(double const arrayA[][3], double const arrayB[])
{
    cout << "----------------------------------------------------------------\n LU Decompilation" << endl;
    double L[3][3] = {0}, U[3][3] = {0}, eps = 0.0001;
    int size = 3;

    for (int i = 0; i < size; i++)
    {
        // Upper Triangular
        for (int k = i; k < size; k++)
        {
            // Summation of L(i, j) * U(j, k)
            double sum = 0;
            for (int j = 0; j < i; j++)
            {
                sum += (L[i][j] * U[j][k]);
            }
            // Evaluating U(i, k)
            U[i][k] = arrayA[i][k] - sum;

            if (abs(U[i][i]) < eps)
            {
                cout << "Матриця потенційно вироджена!";
            }
        }
        // Lower Triangular
        for (int k = i; k < size; k++)
        {
            if (i == k)
            {
                L[i][i] = 1; // Diagonal as 1
            }
            else
            {
                // Summation of L(k, j) * U(j, i)
                double sum = 0;
                for (int j = 0; j < i; j++)
                {
                    sum += (L[k][j] * U[j][i]);
                }
                // Evaluating L(k, i)
                L[k][i] = (arrayA[k][i] - sum) / U[i][i];
            }
        }
    }

    DisplayMatrix(U, arrayB, size, "U matrix:");
    DisplayMatrix(L, arrayB, size, "L matrix: ");

    double results[size];

    double Y[size];
    double B[size];
    for (int i = 0; i < size; i++)
        B[i] = arrayB[i];

    for (int i = 0; i < size; i++)
    {
        Y[i] = B[i] / L[i][i];
        for (int j = i; j < size; j++)
        {
            B[j] -= Y[i] * L[j][i];
        }
    }

    for (int i = size - 1; i >= 0; i--)
    {
        results[i] = Y[i] / U[i][i];
        for (int j = 0; j <= i; j++)
        {
            Y[j] -= results[i] * U[j][i];
        }
    }
    cout << "x1: " << results[0] << "\nx2: " << results[1] << "\nx3: " << results[2] << endl;
    cout << "----------------------------------------------------------------" << endl;
}

int main()
{
    double arrayA[3][3] = {{0.43, 1.24, -0.58}, {0.74, 0.83, 1.17}, {1.43, -1.58, 0.83}}, arrayCof[3][3], forMultiplication[3][3], result[3][1];
    double arrayB[3] = {2.71, 1.26, 1.03};
    LUDecomposition(arrayA, arrayB);
    Gauss(arrayA, arrayB);
    int tabulation;
    Cramer(arrayA, arrayB);
    cofactor(arrayA, arrayCof);
    cout << "Array^-1: " << endl;
    for (int i = 0; i < 3; i++)
    {
        tabulation = 0;
        for (int j = 0; j < 3; j++)
        {
            tabulation++;
            cout << arrayCof[j][i] << " ";
            if (tabulation == 3)
                cout << endl;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            forMultiplication[i][j] = arrayCof[j][i];
        }
    }
    cout << "A^-1 result: " << endl;
    multiplyMatrixes(forMultiplication, arrayB, result);
    for (int i = 0; i < 3; i++)
        cout << result[i][0] << endl;
    return 0;
}