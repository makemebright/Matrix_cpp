#ifndef MATRIX
#define MATRIX
#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include <iostream>

class MatrixOutOfRange : public std::runtime_error {
 public:
  MatrixOutOfRange() : std::runtime_error("MatrixOutOfRange") {
  }
};

template <class T, size_t Rows, size_t Columns>
class Matrix {
 public:
  T buffer[Rows][Columns];

  size_t RowsNumber() {
    return Rows;
  }

  size_t ColumnsNumber() {
    return Columns;
  }

  size_t RowsNumber() const {
    return Rows;
  }

  size_t ColumnsNumber() const {
    return Columns;
  }

  T&operator()(size_t i, size_t j) {
    return buffer[i][j];
  }

  const T operator()(size_t i, size_t j) const {
    return buffer[i][j];
  }

  T &At(size_t row, size_t column) {
    if (row >= Rows || column >= Columns) {
      throw MatrixOutOfRange{};
    }
    return buffer[row][column];
  }

  const T At(size_t row, size_t column) const {
    if (row >= Rows || column >= Columns) {
      throw MatrixOutOfRange{};
    }
    return buffer[row][column];
  }

  Matrix<T, Rows, Columns>& operator+=(const Matrix<T, Rows, Columns>& other) {
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        buffer[i][j] += other(i, j);
      }
    }
    return *this;
  }

  Matrix<T, Rows, Columns>& operator-=(const Matrix<T, Rows, Columns>& other) {
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        buffer[i][j] -= other(i, j);
      }
    }
    return *this;
  }

  Matrix<T, Rows, Columns>& operator*=(const Matrix<T, Columns, Columns>& other) {
    Matrix<T, Rows, Columns> result;
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        result.At(i, j) = 0;
        for (size_t k = 0; k < Columns; ++k) {
          result.buffer[i][j] += buffer[i][k] * other(k, j);
        }
      }
    }
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        this->buffer[i][j] = result.buffer[i][j];
      }
    }
    return *this;
  }

  Matrix<T, Rows, Columns>& operator*=(const T value) {
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        buffer[i][j] *= value;
      }
    }
    return *this;
  }

  Matrix<T, Rows, Columns>& operator/=(const T &value) {
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        buffer[i][j] /= value;
      }
    }
    return *this;
  }

  Matrix<T, Rows, Columns> operator/(const T &value) const {
    Matrix<T, Rows, Columns> result;
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        result.At(i, j) = buffer[i][j] / value;
      }
    }
    return result;
  }

  Matrix<T, Rows, Columns> operator+(const Matrix<T, Rows, Columns>& second) const {
    Matrix<T, Rows, Columns> result;
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        result.At(i, j) = buffer[i][j] + second.buffer[i][j];
      }
    }
    return result;
  }

  Matrix<T, Rows, Columns> operator-(const Matrix<T, Rows, Columns>& second) const {
    Matrix<T, Rows, Columns> result;
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        result.At(i, j) = buffer[i][j] - second.buffer[i][j];
      }
    }
    return result;
  }

  Matrix<T, Rows, Columns> operator*(const T& value) const {
    Matrix<T, Rows, Columns> result;
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        result.At(i, j) = buffer[i][j] * value;
      }
    }
    return result;
  }
};

template <class T, size_t Rows, size_t Columns>
Matrix<T, Columns, Rows> GetTransposed(const Matrix<T, Rows, Columns>& matrix) {
  auto result = Matrix<T, Columns, Rows>{};
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      T t = matrix.buffer[i][j];
      result.buffer[j][i] = t;
    }
  }
  return result;
}

template <class T, size_t Rows, size_t Columns, size_t N>
Matrix<T, Rows, N> operator*(const Matrix<T, Rows, Columns>& first, const Matrix<T, Columns, N>& other) {
  Matrix<T, Rows, N> result;
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < N; ++j) {
      result.buffer[i][j] = 0;
      for (size_t k = 0; k < Columns; ++k) {
        result.buffer[i][j] += first.At(i, k) * other.At(k, j);
      }
    }
  }
  return result;
}

template <class T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> operator*(const T& value, const Matrix<T, Rows, Columns>& other) {
  Matrix<T, Rows, Columns> result;
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      result.At(i, j) = other.At(i, j) * value;
    }
  }
  return result;
}

template <class T, size_t Rows, size_t Columns>
bool operator==(const Matrix<T, Rows, Columns>& first, const Matrix<T, Rows, Columns>& second) {
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      if (first.buffer[i][j] != second.buffer[i][j]) {
        return false;
      }
    }
  }
  return true;
}

template <class T, size_t Rows, size_t Columns>
bool operator!=(const Matrix<T, Rows, Columns>& first, const Matrix<T, Rows, Columns>& second) {
  return !(first == second);
}

template <typename T, size_t Rows, size_t Columns>
std::ostream& operator<<(std::ostream& os, const Matrix<T, Rows, Columns>& other) {
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns - 1; ++j) {
      os << other.At(i, j) << " ";
    }
    os << other.At(i, Columns - 1) << '\n';
  }
  return os;
}

template <class T, size_t Rows, size_t Columns>
std::istream& operator>>(std::istream& is, Matrix<T, Rows, Columns>& first) {
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Columns; ++j) {
      is >> first.buffer[i][j];
    }
  }
  return is;
}

#endif