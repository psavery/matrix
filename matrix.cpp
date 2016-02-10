
#include <cmath> // pow
#include <iomanip> // setw
#include <iostream> // cout

#include "matrix.h"

using namespace std;

const static size_t MAX_SIZE = 100;

Matrix::Matrix(size_t numRows, size_t numColumns)
{
  for (size_t i = 0; i < numRows; i++) {
    vector<double> row;
    for (size_t j = 0; j < numColumns; j++) {
      row.push_back(0);
    }
    m_matrix.push_back(row);
  }
}

Matrix::Matrix(vector<vector<double>> m)
{
  if (m.size() == 0) return;

  // Every row MUST have the same number of elements
  size_t numColumns = m.at(0).size();
  for (size_t i = 1; i < m.size(); i++) {
    if (m.at(i).size() != numColumns) {
      cout << "Error in Matrix::Matrix(vector<vector<double>>): \n"
           << "  Every row must have the same number of elements.\n";
      exit(EXIT_FAILURE);
    }
  }

  m_matrix = m;
}

Matrix::Matrix(double** m, size_t numRows, size_t numColumns)
{
  for (size_t i = 0; i < numRows; i++) {
    vector<double> row;
    for (size_t j = 0; j < numColumns; j++) {
      row.push_back(m[i][j]);
    }
    m_matrix.push_back(row);
  }
}

Matrix::~Matrix()
{

}

// Scalar multiplication
Matrix Matrix::operator*(double s) const
{
  Matrix ret(this->getNumRows(), this->getNumColumns());

  for (size_t i = 0; i < ret.getNumRows(); i++) {
    for (size_t j = 0; j < ret.getNumColumns(); j++) {
      ret.setElement(i, j, m_matrix[i][j] * s);
    }
  }

  return ret;
}

// *this * other
Matrix Matrix::operator*(const Matrix& other) const
{
  // Make sure the multiplication is doable
  if (this->getNumColumns() != other.getNumRows()) {
    cout << "Error: cannot multiply a "
         << this->getNumRows() << "x" << this->getNumColumns()
         << " matrix with a "
         << other.getNumRows() << "x" << other.getNumColumns() << " matrix!\n";
    return Matrix(0,0);
  }

  size_t numSumTerms = this->getNumColumns();

  // The size of the new matrix is going to be:
  // this->getNumRows() x other.getNumColumns()
  size_t newNumRows = this->getNumRows();
  size_t newNumColumns = other.getNumColumns();
  Matrix ret(newNumRows, newNumColumns);

  for (size_t i = 0; i < newNumRows; i++) {
    for (size_t j = 0; j < newNumColumns; j++) {
      double sum = 0;
      for (size_t k = 0; k < numSumTerms; k++) {
        sum += this->getElement(i,k) * other.getElement(k,j);
      }
      ret.setElement(i, j, sum);
    }
  }

  return ret;
}

double determ(double a[MAX_SIZE][MAX_SIZE], int n)
{
  double det = 0, temp[MAX_SIZE][MAX_SIZE];
  size_t p, h, k, i, j;
  if (n == 1) return a[0][0];
  else if (n == 2) {
    det = (a[0][0]*a[1][1]-a[0][1]*a[1][0]);
    return det;
  } else {
    for(p = 0; p < n; p++) {
      h = 0;
      k = 0;
      for(i = 1; i < n; i++) {
        for(j = 0; j < n; j++) {
          if(j == p) {
            continue;
          }
          temp[h][k] = a[i][j];
          k++;
          if(k == n-1) {
            h++;
            k = 0;
          }
        }
      }
      det += a[0][p] * pow(-1, p) * determ(temp, n - 1);
    }
    return det;
  }
}

double Matrix::getDeterminant() const
{
  if (!this->isSquare()) {
    cout << "Error: " << __FUNCTION__ << " was called on a matrix that is not "
         << "square! Returning -1\n";
    return -1;
  }

  double temp[MAX_SIZE][MAX_SIZE];
  for (size_t i = 0; i < getNumRows(); i++) {
    for (size_t j = 0; j < getNumColumns(); j++) {
      temp[i][j] = m_matrix[i][j];
    }
  }

  return determ(temp, getNumRows());
}

void Matrix::printMatrix(size_t precision, size_t width) const
{
  cout << "\n**** Printing matrix ****\n";
  for (size_t i = 0; i < m_matrix.size(); i++) {
    for (size_t j = 0; j < m_matrix.at(i).size(); j++) {
      cout << setw(width) << setprecision(precision) << fixed
           << m_matrix.at(i).at(j) << " ";
    }
    cout << "\n";
  }
  cout << "\n";
}
