#include <iostream>
#include <cmath>

using namespace std;
const int MatrixSize = 4;
const double eps = 0.001;

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

void copyArray(double const initArray[], double tempArray[]) {
    for (int i = 0; i < MatrixSize; i++) tempArray[i] = initArray[i];
}

bool isConvergent(double const matrix[][MatrixSize]) {

    double sum = 0, sum2 = 0;

    // check 1
    for (int i = 0; i < MatrixSize; i++) {
        sum = 0;
        for (int j = 0; j < MatrixSize; j++) {
            sum += fabs(matrix[i][j] / matrix[j][i]);
        }
        if (sum < 1) return true;
    }

    // check 2
    for (int j = 0; j < MatrixSize; j++) {
        sum = 0;
        for (int i = 0; i < MatrixSize; i++) {
            sum += fabs(matrix[i][j] / matrix[j][i]);
        }
        if (sum < 1) return true;
    }

    // check 3
    for (int i = 0; i < MatrixSize; i++) {
        sum = 0, sum2 = 0;
        for (int j = 0; j < MatrixSize; j++) {
            sum += pow(matrix[i][j] / matrix[i][i], 2);
            sum2 += pow(matrix[j][i] / matrix[j][j], 2);
        }
        if (sum < 1 && sum2 < 1) return true;
    }

    // check from example
    double maxi = 0, maxj = 0;
    for(int i = 0; i < MatrixSize; i++){
        sum = 0, sum2 = 0;
        for(int j = 0; j < MatrixSize; j++){
            sum += fabs(matrix[i][j]);
            sum2 += fabs(matrix[j][i]);
        }
        maxi = max(maxi, sum);
        maxj = max(maxj, sum2);
    }
    if(maxi < 1 || maxj < 1) return true;

    // check from wiki
    for (int i = 0; i < MatrixSize; i++) {
        sum = 0;
        for (int j = 0; j < MatrixSize; j++) {
            if (i == j) continue;
            sum += fabs(matrix[i][j]);
        }
        if (matrix[i][i] <= sum) break;
        if (i == MatrixSize - 1) return true;
    }

    return false;
}

void Jacobi(double const arrayA[][MatrixSize], double const arrayB[]) {
    
    cout << "----------------------------------------------------------------\n"
         << "\t\t\tJacobi method" << endl;

    double tempA[MatrixSize][MatrixSize], tempB[MatrixSize];
    for (int i = 0; i < MatrixSize; i++) {
        tempB[i] = arrayB[i] / arrayA[i][i];
        for (int j = 0; j < MatrixSize; j++) {
            tempA[i][j] = - arrayA[i][j] / arrayA[i][i];
            if (i == j) tempA[i][j] = 0;
        }
    }
    displayMatrix("Matrix after Jacobi: ", tempA, tempB);
    cout << "Is matrix convergent? " << isConvergent(tempA) << endl;
    
    double results[MatrixSize], tempResults[MatrixSize];
    double zeroArr[MatrixSize] = {0};
    double oneArr[MatrixSize] = {1, 1, 1, 1};
    copyArray(tempB, results);
    copyArray(tempB, tempResults);

    double sum = 0;
    int iterCount = 0;
    while (true) {
        for (int i = 0; i < MatrixSize; i++) {
            sum = 0;
            for (int j = 0; j < MatrixSize; j++) {
                if (j == i) continue;
                sum += tempA[i][j] * tempResults[j];
            }
            results[i] = tempB[i] + sum;
        }
        sum = 0;
        for (int i = 0; i < MatrixSize; i++) {
            sum += results[i] - tempResults[i];
        }
        if (fabs(sum) < eps) break;
        copyArray(results, tempResults);
        iterCount++;
    }
    for (int i = 0; i < MatrixSize; i++) cout << "Result x" << i + 1 << ": " << results[i] << endl;
    cout << "Iteration count: " << iterCount << endl;
    cout << "----------------------------------------------------------------" << endl;
}

void Seidel(double const arrayA[][MatrixSize], double const arrayB[]) {
    cout << "----------------------------------------------------------------\n"
         << "\t\t\tGauss-Seidel method" << endl;

    double tempA[MatrixSize][MatrixSize], tempB[MatrixSize];
    for (int i = 0; i < MatrixSize; i++) {
        tempB[i] = arrayB[i] / arrayA[i][i];
        for (int j = 0; j < MatrixSize; j++) {
            tempA[i][j] = - arrayA[i][j] / arrayA[i][i];
            if (i == j) tempA[i][j] = 0;
        }
    }
    displayMatrix("Matrix after Jacobi: ", tempA, tempB);
    cout << "Is matrix convergent? " << isConvergent(tempA) << endl;

    double results[MatrixSize], tempResults[MatrixSize];
    double zeroArr[MatrixSize] = {0};
    double oneArr[MatrixSize] = {1, 1, 1, 1};
    copyArray(oneArr, results);
    copyArray(oneArr, tempResults);

    double sum = 0;
    int iterCount = 0;
    while (true) {
        for (int i = 0; i < MatrixSize; i++) {
            sum = 0;
            for (int j = 0; j < i; j++) {
                sum += tempA[i][j] * results[j];
            }
            for (int j = i+1; j < MatrixSize; j++) {
                sum += tempA[i][j] * tempResults[j];
            }
            results[i] = tempB[i] + sum;
        }
        sum = 0;
        for (int i = 0; i < MatrixSize; i++) {
            sum += results[i] - tempResults[i];
        }
        if (fabs(sum) < eps) break;
        copyArray(results, tempResults);
        iterCount++;
    }
    for (int i = 0; i < MatrixSize; i++) cout << "Result x" << i + 1 << ": " << results[i] << endl;
    cout << "Iteration count: " << iterCount << endl;
    cout << "----------------------------------------------------------------" << endl;
}

int main() {
    double arrayA[MatrixSize][MatrixSize];
    double arrayB[MatrixSize];


    exit(7);

    char way;
    cout << "i - input, f - file" << endl;
    cin >> way;
    if (way == 'f') {
        freopen("file5.txt", "r", stdin);
    } 

    for(int i = 0; i < MatrixSize; i++) {
        for (int j = 0; j < MatrixSize; j++) {
            cin >> arrayA[i][j];
        }
    }
    for (int i = 0; i < MatrixSize; i++) {
        cin >> arrayB[i];
    }
    displayMatrix("Matrix : ", arrayA, arrayB);
    Jacobi(arrayA, arrayB);
    Seidel(arrayA, arrayB);
}