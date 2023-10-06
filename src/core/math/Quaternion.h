//
// Created by Damon Tregear on 10/4/2023.
//

#ifndef UMBRAENGINE_QUATERNION_H
#define UMBRAENGINE_QUATERNION_H

#include "Vector3.h"

/**
 * @struct Quaternion
 * @brief A quaternion is a 4D vector that can be used to represent rotations in 3D space.
 *
 * @details Quaternions are a more efficient way to represent rotations than matrices. They are also less prone to
 * gimbal lock and can easily be interpolated.
 */

template <typename T>
struct Quaternion {
/**
 * @section Properties
 * @subsection Instance properties
 */

    /**
     * @property x
     * @brief The x component of the quaternion.
     */
    T x;

    /**
     * @property y
     * @brief The y component of the quaternion.
     */
    T y;

    /**
     * @property z
     * @brief The z component of the quaternion.
     */
    T z;

    /**
     * @property w
     * @brief The w component of the quaternion.
     */
    T w;

    /**
     * @property eulerAngles
     * @brief Returns the euler angle representation of this rotation.
     * @return Vector3<T>
     *
     * @details The euler angles are returned in the order of x, y, z.
     */
    Vector3<T> eulerAngles();

/**
 * @section Constructors
 */

    /**
     * @brief Default constructor. Creates a new quaternion and sets all components to T(0).
     */
    Quaternion<T>();

    /**
     * @brief Creates a new quaternion with the given x, y, z, and w components.
     */
    Quaternion<T>(T x, T y, T z, T w);

    /**
     * @brief Creates a new quaternion and copies the values from the given quaternion.
     */
    Quaternion<T>(const Quaternion<T>& other);

/**
 * @section Properties
 * @subsection Instance properties (read-only)
 */

    /**
     * @property normalized
     * @brief Returns a normalized version of this quaternion (read-only).
     * @return Quaternion<T>
     *
     * @details A normalized quaternion has a magnitude of T(1).
     */
    Quaternion<T> normalized() const;

/**
 * @section Properties
 * @subsection Static properties
 */

    /**
     * @property Identity
     * @brief Returns the identity quaternion (read-only).
     * @return Quaternion<T>
     *
     * @details The identity quaternion represents "no rotation" - its components are (0, 0, 0, 1).
     */
    static Quaternion<T> Identity();

/**
 * @section Methods
 * @subsection Public methods
 */

    /**
     * @brief Sets the x, y, z, and w components of this quaternion.
     * @param x The x component.
     * @param y The y component.
     * @param z The z component.
     * @param w The w component.
     * @return void
     */
    void set(T x, T y, T z, T w);

    /**
     * @brief Returns a formatted string representing this quaternion.
     * @return std::string
     */
    std::string toString() const;

/**
 * @section Methods
 * @subsection Static methods
 */

    /**
     * @brief Returns the angle in degrees between two quaternions.
     * @param a The first quaternion.
     * @param b The second quaternion.
     * @return T
     */
    static T Angle(const Quaternion<T>& a, const Quaternion<T>& b);

    /**
     * @brief Returns a quaternion that rotates angle degrees around axis.
     * @param angle The angle to rotate in degrees.
     * @param axis The axis to rotate around.
     * @return Quaternion<T>
     */
    static Quaternion<T> AngleAxis(T angle, const Vector3<T>& axis);

    /**
     * @brief Returns the dot product of two quaternions.
     * @param a The first quaternion.
     * @param b The second quaternion.
     * @return T
     *
     * @details TODO: Explain dot product of quaternions.
     */
    static T Dot(const Quaternion<T>& a, const Quaternion<T>& b);

    /**
     * @brief Returns the euler angle representation of a rotation.
     * @param x The x component of the euler angles.
     * @param y The y component of the euler angles.
     * @param z The z component of the euler angles.
     * @return Quaternion<T>
     *
     * @details TODO: Explain euler angles.
     */
    static Quaternion<T> Euler(T x, T y, T z);

    /**
     * @brief Returns the inverse of a quaternion.
     * @param rotation The quaternion to invert.
     * @return Quaternion<T>
     *
     * @details TODO: Explain quaternion inversion.
     */
    static Quaternion<T> Inverse(const Quaternion<T>& rotation);

    /**
     * @brief Returns a quaternion that is the linear interpolation between a and b at t and normalizes the result. The
     * parameter t is clamped to the range [0, 1].
     * @param a The first quaternion. Returned when t = 0.
     * @param b The second quaternion. Returned when t = 1.
     * @param t The interpolation value.
     * @return Quaternion<T>
     *
     * @details TODO: Explain quaternion interpolation.
     */
    static Quaternion<T> Lerp(const Quaternion<T>& a, const Quaternion<T>& b, T t);

    /**
     * @brief Returns a quaternion that is the linear interpolation between a and b at t and normalizes the result. The
     * parameter t is not clamped.
     * @param a The first quaternion.
     * @param b The second quaternion.
     * @param t The interpolation value.
     * @return Quaternion<T>
     *
     * @details TODO: Explain quaternion interpolation.
     */
    static Quaternion<T> LerpUnclamped(const Quaternion<T>& a, const Quaternion<T>& b, T t);

    /**
     * @brief Returns this quaternion but with a magnitude of 1.
     * @param rotation The quaternion to normalize.
     * @return Quaternion<T>
     *
     * @details TODO: Explain quaternion normalization.
     */
    static Quaternion<T> Normalize(const Quaternion<T>& rotation);

    /**
     * @brief Rotates a quaternion from toward to.
     * @param from The rotation to rotate from.
     * @param to The rotation to rotate to.
     * @param maxDegreesDelta The maximum number of degrees to rotate.
     * @return Quaternion<T>
     *
     * @details The from quaternion is rotated towards to by an angular step of maxDegreesDelta. Negative values of
     * maxDegreesDelta will move away from to until the rotation is exactly the opposite direction.
     */
    static Quaternion<T> RotateTowards(const Quaternion<T>& from, const Quaternion<T>& to, T maxDegreesDelta);

    /**
     * @brief Returns a quaternion that is spherically interpolated between a and b at t. The parameter t is clamped to
     * the range [0, 1].
     * @param a The first quaternion. Returned when t = 0.
     * @param b The second quaternion. Returned when t = 1.
     * @param t The interpolation ratio.
     * @return Quaternion<T>
     *
     * @details TODO: Explain quaternion spherical interpolation.
     */
    static Quaternion<T> Slerp(const Quaternion<T>& a, const Quaternion<T>& b, T t);

    /**
     * @brief Returns a quaternion that is spherically interpolated between a and b at t. The parameter t is not
     * clamped.
     * @param a The first quaternion.
     * @param b The second quaternion.
     * @param t The interpolation ratio.
     * @return Quaternion<T>
     *
     * @details TODO: Explain quaternion spherical interpolation.
     */
    static Quaternion<T> SlerpUnclamped(const Quaternion<T>& a, const Quaternion<T>& b, T t);

/**
 * @section Operators
 * @subsection Instance operators
 */

    /**
     * @brief Adds two quaternions.
     * @param other The quaternion to add.
     * @return Quaternion<T>
     */
    Quaternion<T> operator+(const Quaternion<T>& other) const;

    /**
     * @brief Component-wise addition of two quaternions.
     * @param other The quaternion to add.
     * @return Quaternion<T>
     */
    Quaternion<T> operator+=(const Quaternion<T>& other);

    /**
     * @brief Subtracts two quaternions.
     * @param other The quaternion to subtract.
     * @return Quaternion<T>
     */
    Quaternion<T> operator-(const Quaternion<T>& other) const;

    /**
     * @brief Component-wise subtraction of two quaternions.
     * @param other The quaternion to subtract.
     * @return Quaternion<T>
     */
    Quaternion<T> operator-=(const Quaternion<T>& other);

    /**
     * @brief Negates a quaternion.
     * @return Quaternion<T>
     */
    Quaternion<T> operator-() const;

    /**
     * @brief Multiplies two quaternions.
     * @param other The quaternion to multiply by.
     * @return Quaternion<T>
     */
    Quaternion<T> operator*(const Quaternion<T>& other) const;

    /**
     * @brief Component-wise multiplication of two quaternions.
     * @param other The quaternion to multiply by.
     * @return Quaternion<T>
     */
    Quaternion<T> operator*=(const Quaternion<T>& other);

    /**
     * @brief Divides this quaternion by a scalar.
     * @param scalar The scalar to divide by.
     * @return Quaternion<T>
     */
    Quaternion<T> operator/(T scalar) const;

    /**
     * @brief Component-wise division of this quaternion by a scalar.
     * @param scalar The scalar to divide by.
     * @return Quaternion<T>
     */
    Quaternion<T> operator/=(T scalar);

    /**
     * @brief Checks if two quaternions are equal.
     * @param other The quaternion to compare to.
     * @return bool
     *
     * @details Quaternions are considered equal if the dot product of the two quaternions is within 1e-5 of 1.
     */
    bool operator==(const Quaternion<T>& other) const;

    /**
     * @brief Checks if two quaternions are not equal.
     * @param other The quaternion to compare to.
     * @return bool
     *
     * @details Quaternions are considered not equal if the dot product of the two quaternions is not within 1e-5 of 1.
     */
    bool operator!=(const Quaternion<T>& other) const;

};

/**
 * @section Operators
 * @subsection Free operators
 */

#endif //UMBRAENGINE_QUATERNION_H
