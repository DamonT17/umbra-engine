//
// Created by Damon Tregear on 8/30/23.
//

#ifndef UMBRA_ENGINE_VECTOR4_H
#define UMBRA_ENGINE_VECTOR4_H

#include <cmath>
#include <limits>
#include <string>

/**
 * @struct Vector4<T>
 * @brief Representation of 4D vectors.
 *
 * @details This structure is used to represent four component vectors (e.g., mesh tangents).
 */

template <typename T>
struct Vector4 {
/**
 * @section Properties
 * @subsection Instance properties
 */
    /**
     * @property x
     * @brief X component of the vector.
     */
    T x;

    /**
     * @property y
     * @brief Y component of the vector.
     */
    T y;

    /**
     * @property z
     * @brief Z component of the vector.
     */
    T z;

    /**
     * @property w
     * @brief W component of the vector.
     */
     T w;

/**
 * @section Properties
 * @subsection Instance properties (read-only)
 */

    /**
     * @property magnitude
     * @brief Returns the length of this vector (read-only).
     * @return T
     *
     * @details The length of the vector is the square root of (x*x+y*y+z*z+w*w).
     */
    const T magnitude() const;

    /**
     * @property sqrMagnitude
     * @brief Returns the squared length of this vector (read-only).
     * @return T
     *
     * @details This property is calculated using the formula (x*x+y*y+z*z+w*w). This property is faster than
     * calculating the magnitude because it avoids calculating a square root.
     */
    const T sqrMagnitude() const;

    /**
     * @property normalized
     * @brief Returns this vector with a magnitude of 1 (read-only).
     * @return Vector4
     *
     * @details When normalized, a vector keeps the same direction but its length is 1. Note that the current vector
     * is unchanged and a new normalized vector is returned. If you want to normalize the current vector, use Normalize
     * function.
     */
    const Vector4<T> normalized() const;

/**
 * @section Constructors
 */

    /**
     * @brief Creates a new vector and sets x, y, z, and w components to zero.
     */
    Vector4<T>();

    /**
     * @brief Creates a new vector with given x, y components and sets z, w to zero.
     * @param x X component of the vector.
     * @param y Y component of the vector.
     */
    Vector4<T>(T x, T y);

    /**
     * @brief Creates a new vector with given x, y, and z components and sets w to zero.
     * @param x X component of the vector.
     * @param y Y component of the vector.
     * @param z Z component of the vector.
     */
    Vector4<T>(T x, T y, T z);

    /**
     * @brief Creates a new vector with given x, y, z, and w components.
     * @param x X component of the vector.
     * @param y Y component of the vector.
     * @param z Z component of the vector.
     * @param w W component of the vector.
     */
    Vector4<T>(T x, T y, T z, T w);

/**
 * @section Properties
 * @subsection Static properties
 */

    /**
     * @property NegativeInfinity
     * @static
     * @brief Shorthand for writing Vector4(-infinity, -infinity, -infinity, -infinity).
     * @return Vector4<T>
     */
    static Vector4<T> NegativeInfinity();

    /**
     * @property One
     * @static
     * @brief Shorthand for writing Vector4(1, 1, 1, 1).
     * @return Vector4<T>
     */
    static Vector4<T> One();

    /**
     * @property PositiveInfinity
     * @static
     * @brief Shorthand for writing Vector4(infinity, infinity, infinity, infinity).
     * @return Vector4<T>
     */
    static Vector4<T> PositiveInfinity();

    /**
     * @property Zero
     * @static
     * @brief Shorthand for writing Vector4(0, 0, 0, 0).
     * @return Vector4<T>
     */
    static Vector4<T> Zero();

/**
 * @section Methods
 * @subsection Public methods
 */

    /**
     * @brief Returns true if the given vector is exactly equal to this vector.
     * @param other
     * @return bool
     */
    bool equals(const Vector4<T>& other) const;

    /**
     * @brief Set x, y, z, and w components of an existing Vector4.
     * @param x
     * @param y
     * @param z
     * @param w
     * @return void
     */
    void set(T x, T y, T z, T w);

    /**
     * @brief Returns a formatted string for this vector.
     * @return std::string
     */
    std::string toString() const;

/**
 * @section Methods
 * @subsection Static methods
 */

    /**
     * @brief Returns the distance between a and b.
     * @param a The first point.
     * @param b The second point.
     * @return T
     *
     * @details This function is equivalent to (a - b).magnitude().
     */
    static T Distance(const Vector4<T>& a, const Vector4<T>& b);

    /**
     * @brief Returns the dot product of two vectors.
     * @param lhs The first vector.
     * @param rhs The second vector.
     * @return T
     *
     * @details The dot product is a <T> value equal to the magnitudes of the two vectors multiplied together and then
     * multiplied by the cosine of the angle between them. For normalized vectors Dot returns 1 if they point in exactly
     * the same direction, -1 if they point in completely opposite directions and zero if the vectors are perpendicular.
     */
    static T Dot(const Vector4<T>& lhs, const Vector4<T>& rhs);

    /**
     * @brief Linearly interpolates between two points.
     * @param a Start value, returned when t = 0.
     * @param b End value, returned when t = 1.
     * @param t Value used to interpolate between a and b.
     * @return Vector4<T> Interpolated value, equals to a + (b - a) * t.
     *
     * @details Interpolates between the points a and b by the interpolant t. The parameter t is clamped to the range
     * [0, 1]. This is most commonly used to find a point some fraction of the way along a line between two endpoints
     * (e.g. to move an object gradually between those points).
     */
    static Vector4<T> Lerp(const Vector4<T>& a, const Vector4<T>& b, T t);

    /**
     * @brief Linearly interpolates between two points.
     * @param a Start value, returned when t = 0.
     * @param b End value, returned when t = 1.
     * @param t Value used to interpolate between a and b.
     * @return Vector4<T> Interpolated value, equals to a + (b - a) * t.
     *
     * @details Interpolates between the points a and b by the interpolant t. The parameter t is clamped to the range
     * [0, 1]. This is most commonly used to find a point some fraction of the way along a line between two endpoints
     * (e.g. to move an object gradually between those points). When t = 0 returns a. When t = 1 returns b. When t = 0.5
     * returns the point midway between a and b.
     */
    static Vector4<T> LerpUnclamped(const Vector4<T>& a, const Vector4<T>& b, T t);

    /**
     * @brief Returns a vector that is made from the largest components of two vectors.
     * @param lhs The first source vector.
     * @param rhs The second source vector.
     * @return Vector4<T>
     */
    static Vector4<T> Max(const Vector4<T>& lhs, const Vector4<T>& rhs);

    /**
     * @brief Returns a vector that is made from the smallest components of two vectors.
     * @param lhs The first source vector.
     * @param rhs The second source vector.
     * @return Vector4<T>
     */
    static Vector4<T> Min(const Vector4<T>& lhs, const Vector4<T>& rhs);

    /**
     * @brief Calculate a position between the points specified by current and target, moving no farther than the
     * distance specified by maxDistanceDelta.
     * @param current The position to move from.
     * @param target The position to move towards.
     * @param maxDistanceDelta Distance to move current per call.
     * @return Vector4<T> The new position.
     */
    static Vector4<T> MoveTowards(const Vector4<T>& current, const Vector4<T>& target, T maxDistanceDelta);

    /**
     * @brief Makes this vector have a magnitude of 1.
     * @param value The vector to normalize.
     * @return Vector4<T>
     *
     * @details When normalized, a vector keeps the same direction but its length is 1.0. Note that this function will
     * change the current vector. If you want to keep the current vector unchanged, use normalized variable. If this
     * vector is too small to be normalized it will be set to zero.
     */
    static Vector4<T> Normalize(const Vector4<T>& value);

    /**
     * @brief Projects a vector onto another vector.
     * @param vector
     * @param onNormal
     * @return Vector4<T>
     */
    static Vector4<T> Project(const Vector4<T>& vector, const Vector4<T>& onNormal);

    /**
     * @brief Multiplies two vectors component-wise.
     * @param a
     * @param b
     * @return Vector4<T>
     */
    static Vector4<T> Scale(const Vector4<T>& a, const Vector4<T>& b);

/**
 * @section Operators
 * @subsection Instance operators
 */

    /**
     * @brief Adds two vectors.
     * @param other The vector to add to this vector.
     * @return Vector4<T>
     */
    Vector4<T> operator+(const Vector4<T>& other) const;

    /**
     * @brief Negates a vector.
     * @return Vector4<T>
     */
    Vector4<T> operator-() const;

    /**
     * @brief Subtracts one vector from another.
     * @param other The vector to subtract from this vector.
     * @return Vector4<T>
     */
    Vector4<T> operator-(const Vector4<T>& other) const;

    /**
     * @brief Multiplies a vector by a number (<T>).
     * @param scalar The number to multiply by this vector.
     * @return Vector4<T>
     */
    Vector4<T> operator*(T scalar) const;

    /**
     * @brief Multiplies a vector by another vector (Vector4<T>).
     * @param other The vector to multiply by this vector.
     * @return Vector4<T>
     */
    Vector4<T> operator*(const Vector4<T>& other) const;

    /**
     * @brief Divides a vector by a number (T).
     * @param scalar The number to divide by this vector.
     * @return Vector4<T>
     * @throws std::overflow_error
     */
    Vector4<T> operator/(T scalar) const;

    /**
     * @brief Divides a vector by another vector (Vector4<T>).
     * @param other The vector to divide by this vector.
     * @return Vector4<T>
     * @throws std::overflow_error
     */
    Vector4<T> operator/(const Vector4<T>& other) const;

    /**
     * @brief Returns true if two vectors are approximately equal.
     * @param other The vector to compare to this vector.
     * @return bool
     */
    bool operator==(const Vector4<T>& other) const;

    /**
     * @brief Returns true if two vectors are not approximately equal.
     * @param other The vector to compare to this vector.
     * @return bool
     */
    bool operator!=(const Vector4<T>& other) const;

    /**
     * @brief Returns the component at the given index.
     * @param index The index of the component to return.
     * @return T
     * @throws std::out_of_range
     *
     * @details The index is zero-based, so valid values are 0, 1, 2, and 3.
     */
    T& operator[](int index);

    /**
     * @brief Returns the component at the given index.
     * @param index The index of the component to return.
     * @return T
     * @throws std::out_of_range
     *
     * @details The index is zero-based, so valid values are 0, 1, 2, and 3.
     */
    const T& operator[](int index) const;
};

/**
 * @section Operators
 * @subsection Free operators
 */

template <typename T>
Vector4<T> operator*(const Vector4<T>& a, T scalar);

template <typename T>
Vector4<T> operator*(T scalar, const Vector4<T>& a);

#endif //UMBRA_ENGINE_VECTOR4_H
