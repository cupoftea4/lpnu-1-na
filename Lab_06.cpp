#include "matrix.h"

using std::cout;

void LeastSquares(Matrix * matrA, Matrix * matrB) {
    matrA->Print("A: ");
    matrA->Transpose()->Print("Transposed A: ");
    Matrix * N = *matrA->Transpose() * *matrA;
    N->Print("N: ");

    Matrix * C = *matrA->Transpose() * *matrB;
    C->Print("C: ");
    if (N->Determinant3() <= 0) return;

    Matrix * L = new Matrix(N->GetRows(), N->GetCols());
    double sum = 0;

    for (int i = 0; i < N->GetRows(); i++) {
        for (int j = 0; j < N->GetCols(); j++) {
            if (i < j) continue;
            sum = 0;
            if (i == j) {
                for (int k = 0; k < j; k++) {
                    sum += pow(L->At(j, k), 2);
                }
                L->SetAt(j, j, sqrt(N->At(j, j) - sum));        
            } else {
                for (int k = 0; k < j; k++) {
                    sum += L->At(i, k) * L->At(j, k);
                    
                }
                L->SetAt(i, j, ((N->At(i, j) - sum) / L->At(j, j)));  
            }
        }
    }

    Matrix * Y = *(L->Inverse3()) * *C ;
    Matrix * X = *(L->Transpose()->Inverse3()) * *Y;
    X->Print("X: ");

}

int main() {
    std::ifstream file("file6.txt");
    Matrix * matrA = new Matrix(file, 5,  3);
    Matrix * matrB = new Matrix(file, 5,  1);

    LeastSquares(matrA, matrB);

    delete matrB;
    delete matrA;
}