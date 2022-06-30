// Варіант 14
#include <iostream>
#include <cmath>
#include <string>

const int MatrixSize = 3;

using std::string;
using std::cout;
using std::cin;
using std::endl;

void displayMatrix(string msg, double const arrayA[][MatrixSize], double const arrayB[])
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


void copyMatrix(double const stablearray[][MatrixSize], double tmpArray[][MatrixSize])
{
    for (int i = 0; i < MatrixSize; i++)
    {
        for (int j = 0; j < MatrixSize; j++)
        {
            tmpArray[i][j] = stablearray[i][j];
        }
    }
}


int findAbsMax(double matrix[][MatrixSize], int n)
{
    int maxIndex = n;
    for (int i = n + 1; i < MatrixSize; ++i) 
    {
        if (abs(matrix[i][n]) > abs(matrix[maxIndex][n])) 
        {
            maxIndex = i;
        }
    }
    return maxIndex;
}

void swapRows(double matrix[][MatrixSize], double arrayB[], int n, int m)
{
    double tmp;
    for (int k = 0; k < MatrixSize; k++)
    {
        tmp = matrix[m][k];
        matrix[m][k] = matrix[n][k];
        matrix[n][k] = tmp;
    }
    tmp = arrayB[m];
    arrayB[m] = arrayB[n];
    arrayB[n] = tmp;
}

void TriangularMatrix(double arrayA[][MatrixSize], double arrayB[])
{
    double m = 0, eps = 1e-10;
    int maxI;
    for (int i = 0; i < MatrixSize; ++i)
    {
        swapRows(arrayA, arrayB, i, findAbsMax(arrayA, i));
        for (int j = i + 1; j < MatrixSize; j++)
        {
            m = arrayA[j][i] / arrayA[i][i];
            arrayB[j] -= m * arrayB[i];
            for (int k = i; k < MatrixSize; k++) {
                arrayA[j][k] -= m * arrayA[i][k];
            } 
        }
    }
    for (int i = 0; i < MatrixSize; i++) {
        for (int j = 0; j < MatrixSize; j++) {
            if (fabs(arrayA[i][j]) < eps) 
                arrayA[i][j] = 0;
        }
        if (fabs(arrayB[i]) < eps) 
            arrayB[i] = 0;
    }
}

void Gauss(double const arrayA[][MatrixSize], double *const arrayB)
{
    cout << "----------------------------------------------------------------\n"
         << "\t\t\tGauss method" << endl;
    double tempMatrixA[MatrixSize][MatrixSize], tempMatrixB[MatrixSize];
    double results[MatrixSize] = {0};

    copyMatrix(arrayA, tempMatrixA);
    for (int i = 0; i < MatrixSize; i++)
        tempMatrixB[i] = arrayB[i];

    TriangularMatrix(tempMatrixA, tempMatrixB);
    displayMatrix( "Triangular Matrix: ", tempMatrixA, tempMatrixB);

    for (int i = MatrixSize-1; i >= 0; i--)
    {
        results[i] = tempMatrixB[i] / tempMatrixA[i][i];
        for (int j = MatrixSize-1; j >= i; j--)
        {
            tempMatrixB[i-1] -= tempMatrixA[i-1][j] * results[j];
        }
    }
    cout << "Result x1: " << results[0] << endl;
    cout << "Result x2: " << results[1] << endl;
    cout << "Result x3: " << results[2] << endl;
    cout << "----------------------------------------------------------------" << endl;
}

void LUDecomposition(double const arrayA[][MatrixSize], double const arrayB[])
{
    cout << "----------------------------------------------------------------\n"
         << "\t\t\tLU Decompilation" << endl;
    double L[MatrixSize][MatrixSize] = {0}, 
           U[MatrixSize][MatrixSize] = {0};

    for (int i = 0; i < MatrixSize; i++) {
        // Upper Triangular
        for (int k = i; k < MatrixSize; k++) {
            // Summation of L(i, j) * U(j, k)
            double sum = 0;
            for (int j = 0; j < i; j++) {
                sum += (L[i][j] * U[j][k]);
            }
            // Evaluating U(i, k)
            U[i][k] = arrayA[i][k] - sum;

        }
        // Lower Triangular
        for (int k = i; k < MatrixSize; k++) {
            if (i == k) {
                L[i][i] = 1; // Diagonal as 1
            }
            else {
                // Sum of L(k, j) * U(j, i)
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

    displayMatrix("U matrix:", U, arrayB);
    displayMatrix("L matrix:", L, arrayB);

    double results[MatrixSize];

    double Y[MatrixSize];
    double B[MatrixSize];
    for (int i = 0; i < MatrixSize; i++)
        B[i] = arrayB[i];

    for (int i = 0; i < MatrixSize; i++) {
        Y[i] = B[i] / L[i][i];
        for (int j = i; j < MatrixSize; j++) {
            B[j] -= Y[i] * L[j][i];
        }
    }

    for (int i = MatrixSize - 1; i >= 0; i--) {
        results[i] = Y[i] / U[i][i];
        for (int j = 0; j <= i; j++) {
            Y[j] -= results[i] * U[j][i];
        }
    }
    cout << "Result x1: " << results[0] << endl;
    cout << "Result x2: " << results[1] << endl;
    cout << "Result x3: " << results[2] << endl;
    cout << "----------------------------------------------------------------" << endl;
}

int main() {
    
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
    Gauss(arrayA, arrayB);
    LUDecomposition(arrayA, arrayB);
 
    return 0;
}