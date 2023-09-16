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
Matrix<T>::Matrix(const T value) {
    for (auto & i : m) {
        for (int j = 0; j < 4; ++j) {
            i[j] = T(value);
        }
    }
}

template <typename T>
Matrix<T>::Matrix(const T values[4][4]) {
    memcpy(m, values, sizeof(T) * 16);
}

template <typename T>
Matrix<T>::Matrix(const Vector4<T>& x, const Vector4<T>& y, const Vector4<T>& z, const Vector4<T>& w) {
    Matrix<T>::setRow(0, x);
    Matrix<T>::setRow(1, y);
    Matrix<T>::setRow(2, z);
    Matrix<T>::setRow(3, w);
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other) {
    memcpy(m, other.m, sizeof(T) * 16);
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
    if (det == T(0)) {
        throw std::runtime_error("Cannot invert matrix with determinant of 0.");
    }

    // TODO: Complete implementation
}

template <typename T>
bool Matrix<T>::isIdentity() const {
    Matrix<T> identity = Matrix<T>::identity();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; i < 4; ++i) {
            if (m[i][j] != identity.m[i][j]) {
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
    T values[4][4] = {
        {T(1), T(0), T(0), T(0)},
        {T(0), T(1), T(0), T(0)},
        {T(0), T(0), T(1), T(0)},
        {T(0), T(0), T(0), T(1)}
    };

    return Matrix<T>(values);
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
    // TODO: Implement
}

/**
 * @section Methods
 * @subsection Static methods
 */

template <typename T>
bool Matrix<T>::InverseAffine(const Matrix<T>& input, Matrix<T>& result) {
    // TODO: Implement
}

template <typename T>
Matrix<T> Matrix<T>::LookAt(const Vector3<T>& eye, const Vector3<T>& target, const Vector3<T>& up) {
    // TODO: Implement
}

template <typename T>
Matrix<T> Matrix<T>::Ortho(T left, T right, T bottom, T top, T near, T far) {
    // TODO: Implement
}

template <typename T>
Matrix<T> Matrix<T>::Perspective(T fov, T aspect, T near, T far) {
    // TODO: Implement
}

template <typename T>
Matrix<T> Matrix<T>::Scale(const Vector3<T>& vector) {
    // TODO: Implement
}

template <typename T>
Matrix<T> Matrix<T>::Translate(const Vector3<T>& vector) {
    // TODO: Implement
}

/**
 * @section Operators
 * @subsection Instance operators
 */

template <typename T>
Matrix<T>& Matrix<T>::operator*(const Matrix<T>& other) const {
    // TODO: Implement
}

template <typename T>
Matrix<T>& Matrix<T>::operator*(const Vector4<T>& vector) const {
    // TODO: Implement
}

/**
 * @section Operators
 * @subsection Free operators
 */



/**
* @section Template instantiations
*/

template struct Matrix<float>;
template struct Matrix<double>;
template struct Matrix<long double>;