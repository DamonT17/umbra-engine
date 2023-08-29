//
// Created by Damon Tregear on 8/26/23.
//

#ifndef UMBRA_ENGINE_VECTOR3_H
#define UMBRA_ENGINE_VECTOR3_H

#include <cmath>
#include <limits>
#include <string>

/**
 * @struct Vector3
 * @brief Representation of 3D vectors and points with floating point precision.
 *
 * @details This structure is used throughout the engine to represent 3D vectors and points with floating point
 * precision.
 */

struct Vector3 {
    /**
     * @section Properties
     * @subsection Instance properties
     */

    /**
     * @property x
     * @brief X component of the vector.
     */
    float x;

    /**
     * @property y
     * @brief Y component of the vector.
     */
    float y;

    /**
     * @property z
     * @brief Z component of the vector.
     */
    float z;

    /**
     * @section Properties
     * @subsection Instance properties (read-only)
     */

    /**
     * @property magnitude
     * @brief Returns the length of this vector (read-only).
     * @return float
     *
     * @details The length of the vector is the square root of (x*x+y*y+z*z).
     */
    const float magnitude() const;

    /**
     * @property sqrMagnitude
     * @brief Returns the squared length of this vector (read-only).
     * @return float
     *
     * @details This property is calculated using the formula (x*x+y*y+z*z). This property is faster than calculating
     * the magnitude because it avoids calculating a square root.
     */
    const float sqrMagnitude() const;

    /**
     * @property normalized
     * @brief Returns this vector with a magnitude of 1 (read-only).
     * @return Vector3
     *
     * @details When normalized, a vector keeps the same direction but its length is 1.0. Note that the current vector
     * is unchanged and a new normalized vector is returned. If you want to normalize the current vector, use Normalize
     * function.
     */
    const Vector3 normalized() const;

    /**
     * @section Constructors
     */

    /**
     * @brief Creates a new vector and sets x, y, and z components to zero.
     */
    Vector3();

    /**
     * @brief Creates a new vector with given x, y components and sets z to zero.
     * @param x X component of the vector.
     * @param y Y component of the vector.
     */
    Vector3(float x, float y);

    /**
     * @brief Creates a new vector with given x, y, and z components.
     * @param x X component of the vector.
     * @param y Y component of the vector.
     * @param z Z component of the vector.
     */
    Vector3(float x, float y, float z);

    /**
     * @section Properties
     * @subsection Static properties
     */

    /**
     * @property Back
     * @static
     * @brief Shorthand for writing Vector3(0, 0, -1).
     * @return Vector3
     */
    static Vector3 Back();

    /**
     * @property Down
     * @static
     * @brief Shorthand for writing Vector3(0, -1, 0).
     * @return Vector3
     */
    static Vector3 Down();

    /**
     * @property Forward
     * @static
     * @brief Shorthand for writing Vector3(0, 0, 1).
     * @return Vector3
     */
    static Vector3 Forward();

    /**
     * @property Left
     * @static
     * @brief Shorthand for writing Vector3(-1, 0, 0).
     * @return Vector3
     */
    static Vector3 Left();

    /**
     * @property NegativeInfinity
     * @static
     * @brief Shorthand for writing Vector3(-infinity, -infinity, -infinity).
     * @return Vector3
     */
    static Vector3 NegativeInfinity();

    /**
     * @property One
     * @static
     * @brief Shorthand for writing Vector3(1, 1, 1).
     * @return Vector3
     */
    static Vector3 One();

    /**
     * @property PositiveInfinity
     * @static
     * @brief Shorthand for writing Vector3(infinity, infinity, infinity).
     * @return Vector3
     */
    static Vector3 PositiveInfinity();

    /**
     * @property Right
     * @static
     * @brief Shorthand for writing Vector3(1, 0, 0).
     * @return Vector3
     */
    static Vector3 Right();

    /**
     * @property Up
     * @static
     * @brief Shorthand for writing Vector3(0, 1, 0).
     * @return Vector3
     */
    static Vector3 Up();

    /**
     * @property Zero
     * @static
     * @brief Shorthand for writing Vector3(0, 0, 0).
     * @return Vector3
     */
    static Vector3 Zero();

    /**
     * @section Methods
     * @subsection Public methods
     */

    /**
     * @brief Returns true if the given vector is exactly equal to this vector.
     * @param other
     * @return bool
     */
    bool equals(const Vector3& other) const;

    /**
     * @brief Set x, y and z components of an existing Vector3.
     * @param x
     * @param y
     * @param z
     * @return void
     */
    void set(float x, float y, float z);

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
     * @brief Returns the angle in degrees between from and to.
     * @param from The vector from which the angular difference is measured.
     * @param to The vector to which the angular difference is measured.
     * @return The angle in degrees between the two vectors.
     *
     * @details The angle returned is the angle of rotation from the first vector to the second, when treating these two
     * vector inputs as directions.The angle returned is always the smaller of the two, never greater. The angle
     * returned will always be between 0 and 180 degrees.
     */
    static float Angle(const Vector3& from, const Vector3& to);

    /**
     * @brief Returns a copy of vector with its magnitude clamped to maxLength.
     * @param vector The vector to clamp.
     * @param maxLength The maximum length of the returned vector.
     * @return Vector3
     */
    static Vector3 ClampMagnitude(const Vector3& vector, float maxLength);

    /**
     * @brief Returns the cross product of two vectors.
     * @param lhs The first vector.
     * @param rhs The second vector.
     * @return Vector3
     */
    static Vector3 Cross(const Vector3& lhs, const Vector3& rhs);

    /**
     * @brief Returns the distance between a and b.
     * @param a The first point.
     * @param b The second point.
     * @return float
     *
     * @details This function is equivalent to (a - b).magnitude().
     */
    static float Distance(const Vector3& a, const Vector3& b);

    /**
     * @brief Returns the dot product of two vectors.
     * @param lhs The first vector.
     * @param rhs The second vector.
     * @return float
     *
     * @details The dot product is a float value equal to the magnitudes of the two vectors multiplied together and then
     * multiplied by the cosine of the angle between them. For normalized vectors Dot returns 1 if they point in exactly
     * the same direction, -1 if they point in completely opposite directions and zero if the vectors are perpendicular.
     */
    static float Dot(const Vector3& lhs, const Vector3& rhs);

    /**
     * @brief Linearly interpolates between two points.
     * @param a Start value, returned when t = 0.
     * @param b End value, returned when t = 1.
     * @param t Value used to interpolate between a and b.
     * @return Vector3 Interpolated value, equals to a + (b - a) * t.
     *
     * @details Interpolates between the points a and b by the interpolant t. The parameter t is clamped to the range
     * [0, 1]. This is most commonly used to find a point some fraction of the way along a line between two endpoints
     * (e.g. to move an object gradually between those points).
     */
    static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);

    /**
     * @brief Linearly interpolates between two points.
     * @param a Start value, returned when t = 0.
     * @param b End value, returned when t = 1.
     * @param t Value used to interpolate between a and b.
     * @return Vector3 Interpolated value, equals to a + (b - a) * t.
     *
     * @details Interpolates between the points a and b by the interpolant t. The parameter t is clamped to the range
     * [0, 1]. This is most commonly used to find a point some fraction of the way along a line between two endpoints
     * (e.g. to move an object gradually between those points). When t = 0 returns a. When t = 1 returns b. When t = 0.5
     * returns the point midway between a and b.
     */
    static Vector3 LerpUnclamped(const Vector3& a, const Vector3& b, float t);

    /**
     * @brief Returns a vector that is made from the largest components of two vectors.
     * @param lhs The first source vector.
     * @param rhs The second source vector.
     * @return Vector3
     */
    static Vector3 Max(const Vector3& lhs, const Vector3& rhs);

    /**
     * @brief Returns a vector that is made from the smallest components of two vectors.
     * @param lhs The first source vector.
     * @param rhs The second source vector.
     * @return Vector3
     */
    static Vector3 Min(const Vector3& lhs, const Vector3& rhs);

    /**
     * @brief Calculate a position between the points specified by current and target, moving no farther than the
     * distance specified by maxDistanceDelta.
     * @param current The position to move from.
     * @param target The position to move towards.
     * @param maxDistanceDelta Distance to move current per call.
     * @return Vector3 The new position.
     */
    static Vector3 MoveTowards(const Vector3& current, const Vector3& target, float maxDistanceDelta);

    /**
     * @brief Makes this vector have a magnitude of 1.
     * @param value The vector to normalize.
     * @return Vector3
     *
     * @details When normalized, a vector keeps the same direction but its length is 1.0. Note that this function will
     * change the current vector. If you want to keep the current vector unchanged, use normalized variable. If this
     * vector is too small to be normalized it will be set to zero.
     */
    static Vector3 Normalize(const Vector3& value);

    /**
     * @brief Makes vectors normalized and orthogonal to each other.
     * @param normal
     * @param tangent
     * @return void
     *
     * @details Normalizes normal. Normalizes tangent and makes sure it is orthogonal to normal (that is, angle between
     * them is 90 degrees).
     */
    static void OrthoNormalize(Vector3& normal, Vector3& tangent);

    /**
     * @brief Projects a vector onto another vector.
     * @param vector
     * @param onNormal
     * @return Vector3
     */
    static Vector3 Project(const Vector3& vector, const Vector3& onNormal);

    /**
     * @brief Projects a vector onto a plane defined by a normal orthogonal to the plane.
     * @param vector
     * @param planeNormal
     * @return Vector3
     */
    static Vector3 ProjectOnPlane(const Vector3& vector, const Vector3& planeNormal);

    /**
     * @brief Reflects a vector off the plane defined by a normal.
     * @param inDirection
     * @param inNormal
     * @return Vector3
     */
    static Vector3 Reflect(const Vector3& inDirection, const Vector3& inNormal);

    /**
     * @brief Rotates a vector current towards target.
     * @param current
     * @param target
     * @param maxRadiansDelta
     * @param maxMagnitudeDelta
     * @return Vector3
     *
     * @details This function is similar to MoveTowards except that the vector is treated as a direction rather than a
     * position. The current vector will be rotated round toward the target direction by an angle of maxRadiansDelta,
     * although it will land exactly on the target rather than overshoot. If the magnitudes of current and target are
     * different, then the magnitude of the result will be linearly interpolated during the rotation. If a negative
     * value is used for maxRadiansDelta, the vector will rotate away from target/ until it is pointing in exactly the
     * opposite direction, then stops.
     */
    static Vector3 RotateTowards(const Vector3& current, const Vector3& target, float maxRadiansDelta,
                                 float maxMagnitudeDelta);

    /**
     * @brief Multiplies two vectors component-wise.
     * @param a
     * @param b
     * @return Vector3
     */
    static Vector3 Scale(const Vector3& a, const Vector3& b);

    /**
     * @brief Returns the signed angle in degrees between from and to in relation to axis.
     * @param from
     * @param to
     * @param axis
     * @return float
     */
    static float SignedAngle(const Vector3& from, const Vector3& to, const Vector3& axis);

    /**
     * @brief Spherically interpolates between two vectors.
     * @param a
     * @param b
     * @param t
     * @return Vector3
     *
     * @details Interpolates between a and b by amount t. The difference between this and linear interpolation (aka,
     * "lerp") is that the vectors are treated as directions rather than points in space. The direction of the returned
     * vector is interpolated by the angle and its magnitude is interpolated between the magnitudes of from and to. The
     * parameter t is clamped to the range [0, 1].
     */
    static Vector3 Slerp(const Vector3& a, const Vector3& b, float t);

    /**
     * @brief Spherically interpolates between two vectors.
     * @param a
     * @param b
     * @param t
     * @return Vector3
     *
     * @details Interpolates between a and b by amount t. The difference between this and linear interpolation (aka,
     * "lerp") is that the vectors are treated as directions rather than points in space. The direction of the returned
     * vector is interpolated by the angle and its magnitude is interpolated between the magnitudes of from and to.
     */
    static Vector3 SlerpUnclamped(const Vector3& a, const Vector3& b, float t);

    /**
     * @section Operators
     * @subsection Instance operators
     */

    /**
     * @brief Adds two vectors.
     * @param other The vector to add to this vector.
     * @return Vector3
     */
    Vector3 operator+(const Vector3& other) const;

    /**
     * @brief Subtracts one vector from another.
     * @param other The vector to subtract from this vector.
     * @return Vector3
     */
    Vector3 operator-(const Vector3& other) const;

    /**
     * @brief Multiplies a vector by a number (float).
     * @param scalar The number to multiply by this vector.
     * @return Vector3
     */
    Vector3 operator*(float scalar) const;

    /**
     * @brief Multiplies a vector by another vector (Vector3).
     * @param other The vector to multiply by this vector.
     * @return Vector3
     */
    Vector3 operator*(const Vector3& other) const;

    /**
     * @brief Divides a vector by a number (float).
     * @param scalar The number to divide by this vector.
     * @return Vector3
     * @throws std::overflow_error
     */
    Vector3 operator/(float scalar) const;

    /**
     * @brief Divides a vector by another vector (Vector3).
     * @param other The vector to divide by this vector.
     * @return Vector3
     * @throws std::overflow_error
     */
    Vector3 operator/(const Vector3& other) const;

    /**
     * @brief Returns true if two vectors are approximately equal.
     * @param other The vector to compare to this vector.
     * @return bool
     */
    bool operator==(const Vector3& other) const;

    /**
     * @brief Returns true if two vectors are not approximately equal.
     * @param other The vector to compare to this vector.
     * @return bool
     */
    bool operator!=(const Vector3& other) const;

    /**
     * @brief Returns the component at the given index.
     * @param index The index of the component to return.
     * @return float
     * @throws std::out_of_range
     *
     * @details The index is zero-based, so valid values are 0, 1, and 2.
     */
    float& operator[](int index);

    /**
     * @brief Returns the component at the given index.
     * @param index The index of the component to return.
     * @return float
     * @throws std::out_of_range
     *
     * @details The index is zero-based, so valid values are 0, 1, and 2.
     */
    const float& operator[](int index) const;
};

/**
 * @section Operators
 * @subsection Free operators
 */

Vector3 operator*(const Vector3& a, int scalar);
Vector3 operator*(int scalar, const Vector3& a);

#endif //UMBRA_ENGINE_VECTOR3_H
