#include "matrix.h"

int main() {
  Matrix<int, 2, 3> a{{{1, 2, 3}, {4, 5, 6}}};
  Matrix<int, 3, 2> b = GetTransposed(a);
 //  + b; // CE
 a + a;     // Ok
// a * a;     // CE 
  a * b;     // Ok
 // a *= b;  // CE - в матрицу a нельзя присвоить матрицу другого размера
  b *= Matrix<int, 2, 2>{1, 2, 3, 4}; // Ok

std::cout << b;

  return 0;
}