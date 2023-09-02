//
// Created by Damon Tregear on 8/28/23.
//

#include "Matrix.h"

/**
 * @section Constructors
 */

template <typename T>
Matrix<T>::Matrix() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m[i][j] = T(0);
        }
    }
}

template <typename T>
Matrix<T>::Matrix(const T value) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m[i][j] = T(value);
        }
    }
}

template <typename T>
Matrix<T>::Matrix(const T values[4][4]) {
    memcpy(m, values, sizeof(T) * 16);
}

/**
 * @section Properties
 * @subsection Instance properties
 */

template <typename T>
const T Matrix<T>::determinant() const {
    // TODO: Implement
}

template <typename T>
const Matrix<T> Matrix<T>::inverse() const {
    // TODO: Implement
}

template <typename T>
const bool Matrix<T>::isIdentity() const {
    // TODO: Implement
}

template <typename T>
const Matrix<T> Matrix<T>::transpose() const {
    // TODO: Implement
}


/**
 * @section Properties
 * @subsection Static properties
 */

template <typename T>
const Matrix<T> Matrix<T>::identity() {
    // TODO: Implement
}

template <typename T>
const Matrix<T> Matrix<T>::zero() {
    // TODO: Implement
}

/**
 * @section Methods
 * @subsection Public methods
 */

template <typename T>
Vector4<T> Matrix<T>::getColumn(int index) {
    // TODO: Implement
}

template <typename T>
Vector3<T> Matrix<T>::getPosition() {
    // TODO: Implement
}

template <typename T>
Vector4<T> Matrix<T>::getRow(int index) {
    // TODO: Implement
}

template <typename T>
void Matrix<T>::setColumn(int index, const Vector4<T>& vector) {
    // TODO: Implement
}

template <typename T>
void Matrix<T>::setRow(int index, const Vector4<T>& vector) {
    // TODO: Implement
}

std::string Matrix<T>::toString() {
    // TODO: Implement
}

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