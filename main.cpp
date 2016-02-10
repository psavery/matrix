
#include <iostream>

#include "matrix.h"

using namespace std;

int main()
{
  vector<vector<double>> tempA = {{1, 0, -2}, {0, 3, -1}};
  vector<vector<double>> tempB = {{0, 3}, {-2, -1}, {0, 4}};
  Matrix A(tempA);
  Matrix B(tempB);
  A.printMatrix();
  B.printMatrix();

  Matrix C = B * A;
  C.printMatrix();

  vector<vector<double>> tempD = {{3, 0, 2, -1}, {1, 2, 0, -2}, {4, 0, 6, -3}, {5, 0, 2, 0}};
  Matrix D(tempD);

  cout << "Determinant of:\n";
  D.printMatrix();
  cout << "is " << D.getDeterminant() << "\n";
}
