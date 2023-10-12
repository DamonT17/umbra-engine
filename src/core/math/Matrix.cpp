//
// Created by Damon Tregear on 8/28/23.
//

#include "Matrix.h"

/**
 * @section Constructors
 */

template <typename T>
Matrix<T>::Matrix() {
    for (auto & i : m) {
        for (int j = 0; j < 4; ++j) {
            i[j] = T(0);
        }
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other) {
    memcpy(m, other.m, sizeof(T) * 16);
}

template <typename T>
Matrix<T>::Matrix(const Vector4<T>& x, const Vector4<T>& y, const Vector4<T>& z, const Vector4<T>& w) {
    Matrix<T>::setRow(0, x);
    Matrix<T>::setRow(1, y);
    Matrix<T>::setRow(2, z);
    Matrix<T>::setRow(3, w);
}

/**
 * @section Properties
 * @subsection Instance properties
 */

template <typename T>
T Matrix<T>::determinant() const {
    T det = 0;
    for (int i = 0; i < 4; ++i) {
        det += m[0][i] * m[1][(i + 1) % 4] * m[2][(i + 2) % 4] * m[3][(i + 3) % 4];
        det -= m[0][i] * m[1][(i + 3) % 4] * m[2][(i + 2) % 4] * m[3][(i + 1) % 4];
    }

    return det;
}

template <typename T>
Matrix<T> Matrix<T>::inverse() const {
    T det = this->determinant();
    if (std::abs(det) < std::numeric_limits<T>::epsilon()) {
        return Matrix<T>::zero();
    }

    Matrix<T> result = *this;
    Matrix<T> identity = Matrix<T>::identity();

    // Find inverse using Gauss-Jordan elimination
    for (int col = 0; col < 4; ++col) {
        int pivotRow = -1;
        T pivot = T(0);

        // Find pivot element
        for (int row = col; row < 4; ++row) {
            T value = std::abs(result.m[row][col]);
            if (value > pivot) {
                pivot = value;
                pivotRow = row;
            }
        }

        if (pivotRow == -1) {
            return Matrix<T>::zero();
        }

        // Swap pivot row with current row
        if (pivotRow != col) {
            T tempRow[4];
            memcpy(tempRow, result.m[col], sizeof(tempRow));
            memcpy(result.m[col], result.m[pivotRow], sizeof(tempRow));
            memcpy(result.m[pivotRow], tempRow, sizeof(tempRow));

            memcpy(tempRow, identity.m[col], sizeof(tempRow));
            memcpy(identity.m[col], identity.m[pivotRow], sizeof(tempRow));
            memcpy(identity.m[pivotRow], tempRow, sizeof(tempRow));
        }

        // Divide pivot row by pivot element
        T pivotValue = result.m[col][col];
        for (int j = 0; j < 4; ++j) {
            result.m[col][j] /= pivotValue;
            identity.m[col][j] /= pivotValue;
        }

        // Subtract current row from all other rows
        for (int row = 0; row < 4; ++row) {
            if (row != col) {
                T value = result.m[row][col];
                for (int j = 0; j < 4; ++j) {
                    result.m[row][j] -= value * result.m[col][j];
                    identity.m[row][j] -= value * identity.m[col][j];
                }
            }
        }
    }

    return identity;
}

template <typename T>
bool Matrix<T>::isIdentity() const {
    for (int i = 0; i < 4; ++i) {
        if (m[i][i] != T(1)) {
            return false;
        }

        for (int j = 0; j < 4; ++j) {
            if (i != j && m[i][j] != T(0)) {
                return false;
            }
        }
    }

    return true;
}

template <typename T>
Matrix<T> Matrix<T>::transpose() const {
    Matrix<T> result;
    for (int i = 0; i < 4; ++i) {
        result.m[i][0] = m[0][i];
        result.m[i][1] = m[1][i];
        result.m[i][2] = m[2][i];
        result.m[i][3] = m[3][i];
    }

    return result;
}


/**
 * @section Properties
 * @subsection Static properties
 */

template <typename T>
Matrix<T> Matrix<T>::identity() {
    return Matrix<T>(
        Vector4<T>(T(1), T(0), T(0), T(0)),
        Vector4<T>(T(0), T(1), T(0), T(0)),
        Vector4<T>(T(0), T(0), T(1), T(0)),
        Vector4<T>(T(0), T(0), T(0), T(1))
    );
}

template <typename T>
Matrix<T> Matrix<T>::zero() {
    return Matrix<T>();
}

/**
 * @section Methods
 * @subsection Public methods
 */

template <typename T>
Vector4<T> Matrix<T>::getColumn(int index) {
    return Vector4<T>(m[0][index], m[1][index], m[2][index], m[3][index]);
}

template <typename T>
Vector3<T> Matrix<T>::getPosition() {
    return Vector3<T>(T(m[3][0]), T(m[3][1]), T(m[3][2]));
}

template <typename T>
Vector4<T> Matrix<T>::getRow(int index) {
    return Vector4<T>(m[index][0], m[index][1], m[index][2], m[index][3]);
}

template <typename T>
void Matrix<T>::setColumn(int index, const Vector4<T>& vector) {
    this->m[0][index] = vector.x;
    this->m[1][index] = vector.y;
    this->m[2][index] = vector.z;
    this->m[3][index] = vector.w;
}

template <typename T>
void Matrix<T>::setRow(int index, const Vector4<T>& vector) {
    this->m[index][0] = vector.x;
    this->m[index][1] = vector.y;
    this->m[index][2] = vector.z;
    this->m[index][3] = vector.w;
}

template <typename T>
std::string Matrix<T>::toString() {
    std::string str;
    for (int i = 0; i < 4; ++i) {
        str += Matrix<T>::getRow(i).toString() + "\n";
    }

    return str;
}

template <typename T>
bool Matrix<T>::isValidTransform() {
    if (this->m[3][3] != T(1)) {
        return false;
    }

    // TODO: Implement

    return true;
}

/**
 * @section Methods
 * @subsection Static methods
 */

template <typename T>
bool Matrix<T>::InverseAffine(const Matrix<T>& input, Matrix<T>& result) {
    T det = input.determinant();
    if (std::abs(det) < std::numeric_limits<T>::epsilon()) {
        result = input;
        return false;
    }

    // Calculate inverse of upper-left 3x3 sub-matrix
    Matrix<T> inverseRotationScaleMatrix = Matrix<T>();
    inverseRotationScaleMatrix.inverse();

    // Calculate the translation portion of the inverse
    Vector3<T> inverseTranslationVector = inverseRotationScaleMatrix.getPosition();

    result = inverseRotationScaleMatrix;
    return true;
}

template <typename T>
Matrix<T> Matrix<T>::LookAt(const Vector3<T>& eye, const Vector3<T>& target, const Vector3<T>& up) {
    Vector3<T> zAxis = (target - eye).normalized();
    Vector3<T> xAxis = Vector3<T>::Cross(up, zAxis).normalized();
    Vector3<T> yAxis = Vector3<T>::Cross(zAxis, xAxis);

    return Matrix<T>(
        Vector4<T>(xAxis.x, yAxis.x, zAxis.x, T(0)),
        Vector4<T>(xAxis.y, yAxis.y, zAxis.y, T(0)),
        Vector4<T>(xAxis.z, yAxis.z, zAxis.z, T(0)),
        Vector4<T>(-Vector3<T>::Dot(xAxis, eye), -Vector3<T>::Dot(yAxis, eye),
                   Vector3<T>::Dot(zAxis, eye), T(1))
    );
}

template <typename T>
Matrix<T> Matrix<T>::Ortho(T left, T right, T bottom, T top, T near, T far) {
    Matrix<T> result = Matrix<T>();
    result.m[0][0] = T(2) / (right - left);
    result.m[1][1] = T(2) / (top - bottom);
    result.m[2][2] = T(-2) / (far - near);
    result.m[3][0] = -(right + left) / (right - left);
    result.m[3][1] = -(top + bottom) / (top - bottom);
    result.m[3][2] = -(far + near) / (far - near);
    result.m[3][3] = T(1);

    return result;
}

template <typename T>
Matrix<T> Matrix<T>::Perspective(T fov, T aspect, T near, T far) {
    Matrix<T> result = Matrix<T>();

    T scale = 1 / std::tan(fov * 0.5f);
    result.m[0][0] = scale / aspect;
    result.m[1][1] = scale;
    result.m[2][2] = -far / (far - near);
    result.m[2][3] = -1;
    result.m[3][2] = -(far * near) / (far - near);

    return result;
}

template <typename T>
Matrix<T> Matrix<T>::Scale(const Vector3<T>& vector) {
    return Matrix<T>(
        Vector4<T>(T(vector.x), T(0), T(0), T(0)),
        Vector4<T>(T(0), T(vector.y), T(0), T(0)),
        Vector4<T>(T(0), T(0), T(vector.z), T(0)),
        Vector4<T>(T(0), T(0), T(0), T(1))
    );
}

template <typename T>
Matrix<T> Matrix<T>::Translate(const Vector3<T>& vector) {
    return Matrix<T>(
        Vector4<T>(T(1), T(0), T(0), T(0)),
        Vector4<T>(T(0), T(1), T(0), T(0)),
        Vector4<T>(T(0), T(0), T(1), T(0)),
        Vector4<T>(T(vector.x), T(vector.y), T(vector.z), T(1))
    );
}

/**
 * @section Operators
 * @subsection Instance operators
 */

template <typename T>
Matrix<T>& Matrix<T>::operator*(const Matrix<T>& other) const {
    Matrix<T> result = Matrix<T>();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = m[i][0] * other.m[0][j] +
                m[i][1] * other.m[1][j] + m[i][2] * other.m[2][j] + m[i][3] * other.m[3][j];
        }
    }

    return result;
}

template <typename T>
Vector4<T> Matrix<T>::operator*(const Vector4<T>& vector) const {
    Vector4<T> result = Vector4<T>();
    for (int i = 0; i < 4; ++i) {
        result[i] = m[i][0] * vector.x + m[i][1] * vector.y + m[i][2] * vector.z + m[i][3] * vector.w;
    }

    // TODO: Check if w is ~1 then normalize?

    return result;
}

/**
* @section Template instantiations
*/

template struct Matrix<float>;
template struct Matrix<double>;