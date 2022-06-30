#include "matrix.h"

Matrix::Matrix() {
    rows = 1; cols = 1;
    AllocMatrix();
}

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols)
{
    AllocMatrix();
}

Matrix::Matrix(std::ifstream& file, int rows, int cols) : rows(rows), cols(cols)
{
    AllocMatrix();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            file >> matrix[i][j];
        }
    }
}

Matrix::~Matrix()
{
    Free();
}

double Matrix::FindMax()
{
    double max = matrix[0][0];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if ( matrix[i][j] > max) max = matrix[i][j];
        }
    }
    return max;
}

double Matrix::FindArithmeticMean()
{
    double sum = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sum += matrix[i][j];
        }
    }
    return (sum / (rows * cols));
}

void Matrix::SortRowAcsending(int index)
{
    if (index >= rows) return;
    SelectionSort(matrix[index], rows, Ascending);
}

void Matrix::SortColumnDescending(int index)
{
    if (index >= cols) return;
    double temp[cols];
    for (int i = 0; i < cols; i++) temp[i] = matrix[i][index];
    SelectionSort(temp, cols, Descending);
    for (int i = 0; i < cols; i++) matrix[i][index] = temp[i];
}

void Matrix::FillRandom()
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand()%20;
        }
    }
}

Matrix * Matrix::Pow(int n)
{
    Matrix * res = new Matrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            res->SetAt(i, j, pow(matrix[i][j], n));
        }
    }
    return res;
}

void Matrix::SetSize(int rows, int cols)
{
    int oldR = this->rows, oldC = this->cols, r  = rows, c = rows;
    c = std::min(oldC, rows);
    r = std::min(oldR, cols);
    double ** tempMatr = new double*[r];
    for(int i = 0; i < r; i++) {
        tempMatr[i] = new double[c]();
    }
    for (int i = 0; i < r; i ++) {
        for (int j = 0; j < c; j++) {
            tempMatr[i][j] = matrix[i][j];
        }
    }
    this->rows = rows; this->cols = cols;
    AllocMatrix();
    for (int i = 0; i < r; i ++) {
        for (int j = 0; j < c; j++) {
            matrix[i][j] = tempMatr[i][j];
        }
    }
    for (int i = 0; i < r; ++i)
        delete [] tempMatr[i];
    delete [] tempMatr;

}

Matrix * Matrix::operator+(const Matrix &matr)
{
    Matrix * res = new Matrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            res->SetAt(i, j, this->At(i, j) + matr[i][j]);
        }
    }
    return res;
}

Matrix * Matrix::operator-(const Matrix &matr)
{
    Matrix * res = new Matrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            res->SetAt(i, j, this->At(i, j) - matr[i][j]);
        }
    }
    return res;
}

Matrix * Matrix::operator*(const Matrix &matr) {
    if (this->cols != matr.rows) return nullptr;
    int resRows = this->rows, resCols = matr.cols;
    Matrix * res = new Matrix(resRows, resCols);
    double sum = 0;
    for (int i = 0; i < resRows; ++i)
    {
        for (int j = 0; j < resCols; ++j) {
            sum = 0;
            for (int k = 0; k < this->cols; ++k)
            {
                sum += this->At(i, k) * matr[k][j];
            }
            res->SetAt(i, j, sum);
        }
    }
    return res;
}

Matrix *Matrix::operator=(Matrix *matr)
{
    delete this;
    return matr;
}

double* &Matrix::operator[](const int &index) const
{
    return  matrix[index];
}

Matrix * Matrix::operator*(const double coeff)
{
    Matrix * res = new Matrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            res->SetAt(i, j, this->At(i, j) * coeff);
        }
    }
    return res;
}

void Matrix::AllocMatrix()
{
    if (matrix != nullptr) {
        Free();
    }
    matrix = new double*[rows];
    for(int i = 0; i < rows; i++) {
        matrix[i] = new double[cols]();
    }
}

int Matrix::Min(const double *array, int start, int n)
{
    double min = array[start];
    int minIndex = start;
    for (int i = start + 1; i < n; i++) {
        if (array[i] < min) {
            min = array[i];
            minIndex = i;
        }
    }
    return minIndex;
}

int Matrix::Max(const double *array, int start, int n)
{
    double max = array[start];
    int maxIndex = start;
    for (int i = start + 1; i < n; i++) {
        if (array[i] > max) {
            max = array[i];
            maxIndex = i;
        }
    }
    return maxIndex;
}

void Matrix::Swap(double *array, int n, int m)
{
    double temp = array[n];
    array[n] = array[m];
    array[m] = temp;
}

void Matrix::SelectionSort(double *array, int n, SortWay way = Ascending)
{
    for (int i = 0; i < n; i++) {
        if (way == Ascending) {
            Swap(array, i, Min(array, i, n));
        } else if (way == Descending) {
            Swap(array, i, Max(array, i, n));
        }
    }
}

void Matrix::Free() {
    for (int i = 0; i < rows; ++i)
        delete [] matrix[i];
    delete [] matrix;
    matrix = nullptr;
}

void Matrix::Print(string header) {
    std::cout << "----------------------------------------------------" << std::endl;
    if (!header.empty()) std::cout << header << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << "-----------------------------------------------------" << std::endl;
}

Matrix * Matrix::Transpose() {
    Matrix * res = new Matrix(cols, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            res->SetAt(j, i, matrix[i][j]);
        }
    }
    return res;
}

Matrix * Matrix::Inverse3() {
    Matrix * res = new Matrix(rows, cols);

    double det = Determinant3();
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            res->SetAt(i, j, pow(-1, i + j) * Minor3(i, j) / det);
        }
    }
    return res->Transpose();
}

double Matrix::Determinant3() {
    double answer;
    double diagonal = matrix[0][0] * matrix[1][1] * matrix[2][2];
    double triangle1 = matrix[0][1] * matrix[1][2] * matrix[2][0];
    double triangle2 = matrix[0][2] * matrix[1][0] * matrix[2][1];
    double antidiagonal = matrix[0][2] * matrix[1][1] * matrix[2][0];
    double antitriangle1 = matrix[0][0] * matrix[1][2] * matrix[2][1];
    double antitriangle2 = matrix[1][0] * matrix[0][1] * matrix[2][2];
    answer = diagonal + triangle1 + triangle2 - antidiagonal - antitriangle1 - antitriangle2;
    return answer;
}

double Matrix::Minor3(int n, int m) {
    double minor[4];
    int k = 0;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if ((i != n) && (j != m))
            {
                minor[k] = matrix[i][j];
                k++;
            }
        }
    }
    double det = minor[0] * minor[3] - minor[1] * minor[2];
    return det;
}