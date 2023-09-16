//
// Created by Damon Tregear on 8/28/23.
//

#ifndef UMBRA_ENGINE_MATRIX_H
#define UMBRA_ENGINE_MATRIX_H

#include <string>

#include "Vector3.h"
#include "Vector4.h"

/**
 * @struct Matrix
 * @brief A standard 4x4 transformation matrix. The matrix is stored in row-major order (i.e., the position of a
 * transformation matrix is in the last row and the first three rows contain the x, y, and z axes).
 *
 * @details A transformation matrix can perform arbitrary linear 3D transformations (i.e., translation, rotation, scale,
 * shear etc.) and perspective transformations using homogenous coordinates.
 */

template <typename T>
struct Matrix {
/**
 * @section Properties
 * @subsection Instance properties
 */

    /**
     * @property m
     * @brief The matrix elements.
     */
    T m[4][4];

/**
 * @section Properties
 * @subsection Instance properties (read-only)
 */

    /**
     * @property determinant
     * @brief Returns the determinant of this matrix (read-only).
     * @return T
     *
     * @details You cannot invert matrices with a determinant of 0.
     */
    T determinant() const;

    /**
     * @property inverse
     * @brief Returns the inverse of this matrix (read-only).
     * @return Matrix<T>
     *
     * @details Inverted matrix multiplied by original matrix should equal identity matrix.
     */
    Matrix<T> inverse() const;

    /**
     * @property isIdentity
     * @brief Returns true if the matrix is an identity matrix (read-only).
     * @return bool
     *
     * @details Identity matrix is a matrix with 1's on the diagonal and 0's everywhere else.
     */
    bool isIdentity() const;

    /**
     * @property transpose
     * @brief Returns the transpose of this matrix (read-only).
     * @return Matrix<T>
     *
     * @details The transpose of a matrix is the matrix flipped over its main diagonal.
     */
    Matrix<T> transpose() const;

/**
 * @section Constructors
 */

    /**
     * @brief Creates a new matrix and sets all elements to 0.
     */
    Matrix<T>();

    /**
     * @brief Creates a new matrix and sets all elements to the given value.
     */
    explicit Matrix<T>(T value);

    /**
     * @brief Creates a new matrix and sets all elements to the given values in the 2D array.
     */
    explicit Matrix<T>(const T values[4][4]);

    /**
     * @brief Creates a new matrix and sets each row to the given x, y, z, and w vectors.
     */
    explicit Matrix<T>(const Vector4<T>& x, const Vector4<T>& y, const Vector4<T>& z, const Vector4<T>& w);

    /**
     * @brief Creates a new matrix and copies the values from the given matrix.
     */
    Matrix<T>(const Matrix<T>& other);

/**
 * @section Properties
 * @subsection Static properties
 */

    /**
     * @property identity
     * @brief Returns the identity matrix (read-only).
     * @return Matrix<T>
     */
    static Matrix<T> identity();

    /**
     * @property zero
     * @brief Returns the zero matrix (read-only).
     * @return Matrix<T>
     */
    static Matrix<T> zero();

/**
 * @section Methods
 * @subsection Public methods
 */

    /**
     * @brief Get a column of this matrix.
     * @param index The index of the column to get.
     * @return Vector4<T>
     *
     * @details Returns a column of this matrix as a vector. index must be from 0 to 3.
     */
    Vector4<T> getColumn(int index);

    /**
     * @brief Returns the position of this matrix.
     * @return Vector3<T>
     *
     * @details Returns the position of this matrix as a Vector3<T>. The position of a matrix is in the last row (row
     * major).
     */
    Vector3<T> getPosition();

    /**
     * @brief Get a row of this matrix.
     * @param index The index of the row to get.
     * @return Vector4<T>
     *
     * @details Returns a row of this matrix as a vector. index must be from 0 to 3.
     */
    Vector4<T> getRow(int index);

    /**
     * @brief Sets a column of this matrix.
     * @param index The index of the column to set.
     * @param vector The vector to set the column to.
     *
     * @details Sets a column of this matrix from a Vector4. index must be from 0 to 3.
     */
    void setColumn(int index, const Vector4<T>& vector);

    /**
     * @brief Sets a row of this matrix.
     * @param index The index of the row to set.
     * @param vector The vector to set the row to.
     * @return void
     *
     * @details Sets a row of this matrix from a Vector4. index must be from 0 to 3.
     */
    void setRow(int index, const Vector4<T>& vector);

    /**
     * @brief Returns a formatted string for this matrix.
     * @return std::string
     */
    std::string toString();

    /**
     * @brief Checks if this matrix is a valid transform matrix.
     * @return bool
     */
    bool isValidTransform();

/**
 * @section Methods
 * @subsection Static methods
 */

    /**
     * @brief Returns true and a valid inverse if the matrix is invertible. If not, a copy of the input matrix is
     * returned.
     * @param input
     * @param result
     * @return bool
     *
     * @details Computes the inverse of a 3D affine matrix. This function is dedicated to a non-singular matrix
     * (typically, a transform matrix), otherwise, returns false and the result is a copy of the input matrix.
     */
    static bool InverseAffine(const Matrix<T>& input, Matrix<T>& result);

    /**
     * @brief Returns a "look at" matrix.
     * @param eye The position of the camera.
     * @param target The position of the target.
     * @param up The up direction.
     * @return Matrix<T>
     *
     * @details Given an eye point, a target point, and an up vector, computes a transformation matrix that corresponds
     * to a camera viewing the target from the eye, such that the right-hand vector is perpendicular to the up vector.
     */
    static Matrix<T> LookAt(const Vector3<T>& eye, const Vector3<T>& target, const Vector3<T>& up);

    /**
     * @brief Returns an orthographic projection matrix.
     * @param left The left edge of the viewing frustum.
     * @param right The right edge of the viewing frustum.
     * @param bottom The bottom edge of the viewing frustum.
     * @param top The top edge of the viewing frustum.
     * @param near The distance to the near clipping plane.
     * @param far The distance to the far clipping plane.
     * @return Matrix<T>
     *
     * @details TODO: Add details
     */
    static Matrix<T> Ortho(T left, T right, T bottom, T top, T near, T far);

    /**
     * @brief Returns a perspective projection matrix.
     * @param fov The field of view in the y direction, in radians.
     * @param aspect The aspect ratio, defined as view space width divided by height.
     * @param near The distance to the near clipping plane.
     * @param far The distance to the far clipping plane.
     * @return Matrix<T>
     *
     * @details TODO: Add details
     */
    static Matrix<T> Perspective(T fov, T aspect, T near, T far);

    /**
     * @brief Returns a scaling matrix.
     * @param vector The amount to scale by.
     * @return Matrix<T>
     *
     * @details Returned matrix is a scaling matrix with the given vector as the scale factor.
     */
    static Matrix<T> Scale(const Vector3<T>& vector);

    /**
     * @brief Returns a translation matrix.
     * @param vector The amount to translate by.
     * @return Matrix<T>
     *
     * @details Returned matrix is a translation matrix with the given vector as the translation factor.
     */
    static Matrix<T> Translate(const Vector3<T>& vector);

/**
 * @section Operators
 * @subsection Instance operators
 */

    /**
     * @brief Multiplies two matrices.
     * @param other The matrix to multiply by.
     * @return Matrix<T>
     */
    Matrix<T>& operator*(const Matrix<T>& other) const;

    /**
     * @brief Transforms a vector by a matrix.
     * @param vector The vector to transform.
     * @return Matrix<T>
     */
    Matrix<T>& operator*(const Vector4<T>& vector) const;
};

#endif //UMBRA_ENGINE_MATRIX_H
