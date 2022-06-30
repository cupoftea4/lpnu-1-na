// Варіант 14

#include <iostream>
#include <cmath>
#include <string>

const int MatrixSize = 3;

using namespace std;

void DisplayMatrixWithB(string msg, double const arrayA[][MatrixSize], double const arrayB[])
{
    cout << msg << endl;
    for (int i = 0; i < MatrixSize; i++)
    {
        for (int j = 0; j < MatrixSize; j++)
        {
            cout << arrayA[i][j] << "\t";
        }
        cout << arrayB[i] << endl;
    }
}

void DisplayMatrix(string msg, double const arrayA[][MatrixSize])
{
    cout << msg << endl;
    for (int i = 0; i < MatrixSize; i++)
    {
        for (int j = 0; j < MatrixSize; j++)
        {
            cout << arrayA[i][j] << "\t";
        }
        cout << endl;
    }
}

double determinant(double array[][MatrixSize])
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

void copyMatrix(double const arrayA[][3], double tmpArray[][3])
{
    for (int i = 0; i < MatrixSize; i++)
    {
        for (int j = 0; j < MatrixSize; j++)
        {
            tmpArray[i][j] = arrayA[i][j];
        }
    }
}
void Cramer(double arrayA[][MatrixSize], double arrayB[])
{
    cout << "----------------------------------------------------------------\n\
    \t\t\t Cramer's rule" << endl;
    double tmparray[MatrixSize][MatrixSize];
    double deltax, deltay, deltaz;
    double det  = determinant(arrayA);
    cout << "Array determinant: " << det << endl;

    copyMatrix(arrayA, tmparray);
    for (int i = 0; i < MatrixSize; i++)
    {
        tmparray[i][0] = arrayB[i];
    }
    DisplayMatrix( "Delta x matrix: ", tmparray);
    deltax = determinant(tmparray);
    cout << "Delta x determinant: " << deltax << endl;

    copyMatrix(arrayA, tmparray);
    for (int i = 0; i < MatrixSize; i++)
    {
        tmparray[i][1] = arrayB[i];
    }
    DisplayMatrix("Delta y matrix: ", tmparray);
    deltay = determinant(tmparray);
    cout << "Delta y determinant: " << deltay << endl;

    copyMatrix(arrayA, tmparray);
    for (int i = 0; i < MatrixSize; i++)
    {
        tmparray[i][2] = arrayB[i];
    }
    DisplayMatrix("Delta z matrix: ", tmparray);
    deltaz = determinant(tmparray);
    cout << "Delta z determinant: " << deltaz << endl;

    cout << "Result x1: " << deltax / det << endl;
    cout << "Result x2: " << deltay / det << endl;
    cout << "Result x3: " << deltaz / det << endl;
    cout << "----------------------------------------------------------------" << endl;
}

double detMinor(double mas[][MatrixSize], int n, int m)
{
    double minor[4];
    int k = 0;

    for (int i = 0; i < MatrixSize; ++i)
    {
        for (int j = 0; j < MatrixSize; ++j)
        {
            if ((i != n) && (j != m))
            {
                minor[k] = mas[i][j];
                k++;
            }
        }
    }
    double det = minor[0] * minor[3] - minor[1] * minor[2];
    return det;
}
void cofactor(double arr[][MatrixSize], double cofactorMatr[][MatrixSize])
{
    double det = determinant(arr);
    for (int i = 0; i < MatrixSize; i++)
    {
        for (int j = 0; j < MatrixSize; j++)
        {
            cofactorMatr[i][j] = pow(-1, i + j) * detMinor(arr, i, j) / det;
        }
    }
}
void multiplyMatrixes(double first[][MatrixSize], double second[], double result[3])
{
    double sum = 0;
    for (int i = 0; i < MatrixSize; ++i)
    {
        sum = 0;
        for (int k = 0; k < MatrixSize; ++k)
        {
            sum += first[i][k] * second[k];
        }
        result[i] = sum;
    }
}

void InverseMatrixMethod(double arrayA[][MatrixSize], double arrayB[]) {
    cout << "----------------------------------------------------------------\n\
    \t\t\t Inverse Matrix Method" << endl;
    double arrayCof[3][3], transponsed[3][3], result[3];
    cofactor(arrayA, arrayCof);
    DisplayMatrix("Array^-1: ", arrayCof);
    
    // transponse matrix
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            transponsed[i][j] = arrayCof[j][i];
        }
    }

    multiplyMatrixes(transponsed, arrayB, result);
    cout << "Result x1: " << result[0] << endl;
    cout << "Result x2: " << result[1] << endl;
    cout << "Result x3: " << result[2] << endl;
    cout << "----------------------------------------------------------------" << endl;

}

int main()
{
    double arrayA[MatrixSize][MatrixSize];
    double arrayB[MatrixSize];
    char way;
    cout << "i - input, f - file" << endl;
    cin >> way;
    if (way == 'f') {
        freopen("file.txt", "r", stdin);
    } 

    for(int i = 0; i < MatrixSize; i++) {
        for (int j = 0; j < MatrixSize; j++) {
            cin >> arrayA[i][j];
        }
    }
    for (int i = 0; i < 3; i++) {
        cin >> arrayB[i];
    }

    if (!determinant(arrayA)){
        cout << "Det is 0";
        return 0;
    }
    Cramer(arrayA, arrayB);
    InverseMatrixMethod(arrayA, arrayB);
    return 0;
}