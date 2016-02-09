

#ifndef MATRIX_H
#define MATRIX_H

// for size_t
#include <cstdlib>

#include <vector>

class Matrix {
 public:

  // Initializes a matrix with all zeros
  Matrix(size_t numRows, size_t numColumns);

  // Initializes a matrix from a vector of vectors
  // Note that all the columns MUST have the
  // same number of elements
  Matrix(std::vector<std::vector<double>> m);

  // Initializes a matrix from a matrix of doubles
  Matrix(double** m, size_t numRows, size_t numColumns);

  virtual ~Matrix();

  size_t getNumRows() const
  {
    return m_matrix.size();
  };

  size_t getNumColumns() const
  {
    if (m_matrix.size() == 0) return 0;
    else return m_matrix.at(0).size();
  };

  bool isSquare() const {return getNumRows() == getNumColumns();};

  void setElement(size_t i, size_t j, double n) {m_matrix[i][j] = n;};
  double getElement(size_t i, size_t j) const {return m_matrix[i][j];};

  // Matrix multiplication!
  Matrix operator*(const Matrix& other) const;

  void printMatrix(size_t precision = 10, size_t width = 15) const;

 private:
  std::vector<std::vector<double>> m_matrix;
};

#endif
