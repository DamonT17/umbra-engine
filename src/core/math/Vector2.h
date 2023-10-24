//
// Created by Damon Tregear on 8/30/23.
//

#ifndef UMBRA_ENGINE_VECTOR2_H
#define UMBRA_ENGINE_VECTOR2_H

#include <cmath>
#include <limits>
#include <string>

namespace UmbraEngine::Core::Math {
    /**
     * @struct Vector2<T>
     * @brief Representation of 2D vectors and points.
     *
     * @details This structure is used throughout the engine to represent 2D vectors and points.
     */
    template<typename T>
    struct Vector2 {
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
     * @section Properties
     * @subsection Instance properties (read-only)
     */
        /**
         * @property magnitude
         * @brief Returns the length of this vector (read-only).
         * @return T
         *
         * @details The length of the vector is the square root of (x*x+y*y).
         */
        T magnitude() const;

        /**
         * @property sqrMagnitude
         * @brief Returns the squared length of this vector (read-only).
         * @return T
         *
         * @details This property is calculated using the formula (x*x+y*y). This property is faster than calculating
         * the magnitude because it avoids calculating a square root.
         */
        T sqrMagnitude() const;

        /**
         * @property normalized
         * @brief Returns this vector with a magnitude of 1 (read-only).
         * @return Vector2
         *
         * @details When normalized, a vector keeps the same direction but its length is 1. Note that the current vector
         * is unchanged and a new normalized vector is returned. If you want to normalize the current vector, use 
         * Normalize function.
         */
        Vector2<T> normalized() const;

    /**
     * @section Constructors
     */
        /**
         * @brief Creates a new vector and sets x and y components to zero.
         */
        Vector2<T>();

        /**
         * @brief Creates a new vector with given x, y components.
         * @param x X component of the vector.
         * @param y Y component of the vector.
         */
        Vector2<T>(T x, T y);

    /**
     * @section Properties
     * @subsection Static properties
     */
        /**
         * @property Down
         * @static
         * @brief Shorthand for writing Vector2(0, -1).
         * @return Vector2<T>
         */
        static Vector2<T> Down();

        /**
         * @property Left
         * @static
         * @brief Shorthand for writing Vector2(-1, 0).
         * @return Vector2<T>
         */
        static Vector2<T> Left();

        /**
         * @property NegativeInfinity
         * @static
         * @brief Shorthand for writing Vector2(-infinity, -infinity).
         * @return Vector2<T>
         */
        static Vector2<T> NegativeInfinity();

        /**
         * @property One
         * @static
         * @brief Shorthand for writing Vector2(1, 1).
         * @return Vector2<T>
         */
        static Vector2<T> One();

        /**
         * @property PositiveInfinity
         * @static
         * @brief Shorthand for writing Vector2(infinity, infinity).
         * @return Vector2<T>
         */
        static Vector2<T> PositiveInfinity();

        /**
         * @property Right
         * @static
         * @brief Shorthand for writing Vector2(1, 0).
         * @return Vector2<T>
         */
        static Vector2<T> Right();

        /**
         * @property Up
         * @static
         * @brief Shorthand for writing Vector2(0, 1).
         * @return Vector2<T>
         */
        static Vector2<T> Up();

        /**
         * @property Zero
         * @static
         * @brief Shorthand for writing Vector2(0, 0).
         * @return Vector2<T>
         */
        static Vector2<T> Zero();

    /**
     * @section Methods
     * @subsection Public methods
     */
        /**
         * @brief Returns true if the given vector is exactly equal to this vector.
         * @param other
         * @return bool
         */
        bool equals(const Vector2<T>& other) const;

        /**
         * @brief Set x and y components of an existing Vector2.
         * @param x
         * @param y
         * @return void
         */
        void set(T x, T y);

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
         * @details The angle returned is the angle of rotation from the first vector to the second, when treating these 
         * two vector inputs as directions.The angle returned is always the smaller of the two, never greater. The angle
         * returned will always be between 0 and 180 degrees.
         */
        static T Angle(const Vector2<T>& from, const Vector2<T>& to);

        /**
         * @brief Returns a copy of vector with its magnitude clamped to maxLength.
         * @param vector The vector to clamp.
         * @param maxLength The maximum length of the returned vector.
         * @return Vector2
         */
        static Vector2<T> ClampMagnitude(const Vector2<T>& vector, T maxLength);

        /**
         * @brief Returns the distance between a and b.
         * @param a The first point.
         * @param b The second point.
         * @return T
         *
         * @details This function is equivalent to (a - b).magnitude().
         */
        static T Distance(const Vector2<T>& a, const Vector2<T>& b);

        /**
         * @brief Returns the dot product of two vectors.
         * @param lhs The first vector.
         * @param rhs The second vector.
         * @return T
         *
         * @details The dot product is a <T> value equal to the magnitudes of the two vectors multiplied together and 
         * then multiplied by the cosine of the angle between them. For normalized vectors Dot returns 1 if they 
         * point in exactly the same direction, -1 if they point in completely opposite directions and zero if the 
         * vectors are perpendicular.
         */
        static T Dot(const Vector2<T>& lhs, const Vector2<T>& rhs);

        /**
         * @brief Linearly interpolates between two points.
         * @param a Start value, returned when t = 0.
         * @param b End value, returned when t = 1.
         * @param t Value used to interpolate between a and b.
         * @return Vector2<T> Interpolated value, equals to a + (b - a) * t.
         *
         * @details Interpolates between the points a and b by the interpolant t. The parameter t is clamped to the 
         * range [0, 1]. This is most commonly used to find a point some fraction of the way along a line between two
         * endpoints (e.g., to move an object gradually between those points).
         */
        static Vector2<T> Lerp(const Vector2<T>& a, const Vector2<T>& b, T t);

        /**
         * @brief Linearly interpolates between two points.
         * @param a Start value, returned when t = 0.
         * @param b End value, returned when t = 1.
         * @param t Value used to interpolate between a and b.
         * @return Vector2<T> Interpolated value, equals to a + (b - a) * t.
         *
         * @details Interpolates between the points a and b by the interpolant t. The parameter t is clamped to the
         * range [0, 1]. This is most commonly used to find a point some fraction of the way along a line between two
         * endpoints (e.g., to move an object gradually between those points). When t = 0 returns a. When t = 1 returns
         * b. When t = 0.5 returns the point midway between a and b.
         */
        static Vector2<T> LerpUnclamped(const Vector2<T>& a, const Vector2<T>& b, T t);

        /**
         * @brief Returns a vector that is made from the largest components of two vectors.
         * @param lhs The first source vector.
         * @param rhs The second source vector.
         * @return Vector2<T>
         */
        static Vector2<T> Max(const Vector2<T>& lhs, const Vector2<T>& rhs);

        /**
         * @brief Returns a vector that is made from the smallest components of two vectors.
         * @param lhs The first source vector.
         * @param rhs The second source vector.
         * @return Vector2<T>
         */
        static Vector2<T> Min(const Vector2<T>& lhs, const Vector2<T>& rhs);

        /**
         * @brief Calculate a position between the points specified by current and target, moving no farther than the
         * distance specified by maxDistanceDelta.
         * @param current The position to move from.
         * @param target The position to move towards.
         * @param maxDistanceDelta Distance to move current per call.
         * @return Vector2<T> The new position.
         */
        static Vector2<T> MoveTowards(const Vector2<T>& current, const Vector2<T>& target, T maxDistanceDelta);

        /**
         * @brief Makes this vector have a magnitude of 1.
         * @param value The vector to normalize.
         * @return Vector2<T>
         *
         * @details When normalized, a vector keeps the same direction but its length is 1.0. Note that this function
         * will change the current vector. If you want to keep the current vector unchanged, use normalized variable.
         * If this vector is too small to be normalized it will be set to zero.
         */
        static Vector2<T> Normalize(const Vector2<T>& value);

        /**
         * @brief Returns a vector that is perpendicular to the input vector.
         * @brief inDirection The vector from which to compute the perpendicular vector.
         * @return Vector2<T>
         *
         * @details The returned vector is always rotated 90 degrees in a counter-clockwise direction for a
         * 2D-coordinate system where the positive Y axis goes up and the positive X axis goes right.
         */
        static Vector2<T> Perpendicular(const Vector2<T>& inDirection);

        /**
         * @brief Reflects a vector off the plane defined by a normal.
         * @param inDirection
         * @param inNormal
         * @return Vector2<T>
         */
        static Vector2<T> Reflect(const Vector2<T>& inDirection, const Vector2<T>& inNormal);

        /**
         * @brief Multiplies two vectors component-wise.
         * @param a
         * @param b
         * @return Vector2<T>
         */
        static Vector2<T> Scale(const Vector2<T>& a, const Vector2<T>& b);

        /**
         * @brief Returns the signed angle in degrees between from and to in relation to axis.
         * @param from
         * @param to
         * @param axis
         * @return T
         */
        static T SignedAngle(const Vector2<T>& from, const Vector2<T>& to, const Vector2<T>& axis);

        /**
         * @brief Gradually changes a vector towards a desired goal over time.
         * @param current The current position.
         * @param target The position we are trying to reach.
         * @param currentVelocity The current velocity, this value is modified by the function every time you call it.
         * @param smoothTime Approximately the time it will take to reach the target. A smaller value will reach the
         * target faster.
         * @param maxSpeed Optionally allows you to clamp the maximum speed. TODO: Add default value of infinity
         * @param deltaTime The time since the last call to this function. TODO: Add default value of Time.deltaTime
         */
        static Vector2<T> SmoothDamp(const Vector2<T>& current, const Vector2<T>& target, Vector2<T>& currentVelocity,
                                     T smoothTime, T maxSpeed, float deltaTime);

    /**
     * @section Operators
     * @subsection Instance operators
     */
        /**
         * @brief Adds two vectors.
         * @param other The vector to add to this vector.
         * @return Vector2<T>
         */
        Vector2<T> operator+(const Vector2<T>& other) const;

        /**
         * @brief Negates a vector.
         * @return Vector2<T>
         */
        Vector2<T> operator-() const;

        /**
         * @brief Subtracts one vector from another.
         * @param other The vector to subtract from this vector.
         * @return Vector2<T>
         */
        Vector2<T> operator-(const Vector2<T>& other) const;

        /**
         * @brief Multiplies a vector by a number (<T>).
         * @param scalar The number to multiply by this vector.
         * @return Vector2<T>
         */
        Vector2<T> operator*(T scalar) const;

        /**
         * @brief Multiplies a vector by another vector (Vector2<T>).
         * @param other The vector to multiply by this vector.
         * @return Vector2<T>
         */
        Vector2<T> operator*(const Vector2<T>& other) const;

        /**
         * @brief Divides a vector by a number (T).
         * @param scalar The number to divide by this vector.
         * @return Vector2<T>
         * @throws std::overflow_error
         */
        Vector2<T> operator/(T scalar) const;

        /**
         * @brief Divides a vector by another vector (Vector2<T>).
         * @param other The vector to divide by this vector.
         * @return Vector2<T>
         * @throws std::overflow_error
         */
        Vector2<T> operator/(const Vector2<T>& other) const;

        /**
         * @brief Returns true if two vectors are approximately equal.
         * @param other The vector to compare to this vector.
         * @return bool
         */
        bool operator==(const Vector2<T>& other) const;

        /**
         * @brief Returns true if two vectors are not approximately equal.
         * @param other The vector to compare to this vector.
         * @return bool
         */
        bool operator!=(const Vector2<T>& other) const;

        /**
         * @brief Returns the component at the given index.
         * @param index The index of the component to return.
         * @return T
         * @throws std::out_of_range
         *
         * @details The index is zero-based, so valid values are 0, and 1.
         */
        T& operator[](int index);

        /**
         * @brief Returns the component at the given index.
         * @param index The index of the component to return.
         * @return T
         * @throws std::out_of_range
         *
         * @details The index is zero-based, so valid values are 0, and 1.
         */
        const T& operator[](int index) const;
    };

/**
 * @section Operators
 * @subsection Free operators
 */
    template<typename T>
    Vector2<T> operator*(const Vector2<T>& a, T scalar);

    template<typename T>
    Vector2<T> operator*(T scalar, const Vector2<T>& a);
}

#endif //UMBRA_ENGINE_VECTOR2_H
