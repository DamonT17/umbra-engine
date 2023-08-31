//
// Created by Damon Tregear on 8/30/23.
//

#include "Vector2.h"

/**
 * @section Constructors
 */

template <typename T>
Vector2<T>::Vector2() : x(T(0)), y(T(0)) {}

template <typename T>
Vector2<T>::Vector2(T x, T y) : x(x), y(y) {}

/**
 * @section Properties
 * @subsection Instance properties
 */

template <typename T>
const T Vector2<T>::magnitude() const {
    return std::sqrt(x * x + y * y);
}

template <typename T>
const T Vector2<T>::sqrMagnitude() const {
    return x * x + y * y;
}

template <typename T>
const Vector2<T> Vector2<T>::normalized() const {
    T magnitude = this->magnitude();
    return Vector2<T>(x / magnitude, y / magnitude);
}

/**
 * @section Properties
 * @subsection Static properties
 */

template <typename T>
Vector2<T> Vector2<T>::Down() {
    return Vector2<T>(T(0), T(-1));
}

template <typename T>
Vector2<T> Vector2<T>::Left() {
    return Vector2<T>(T(-1), T(0));
}

template <typename T>
Vector2<T> Vector2<T>::NegativeInfinity() {
    return Vector2<T>(
            -std::numeric_limits<T>::infinity(),
            -std::numeric_limits<T>::infinity()
    );
}

template <typename T>
Vector2<T> Vector2<T>::One() {
    return Vector2<T>(T(1), T(1));
}

template <typename T>
Vector2<T> Vector2<T>::PositiveInfinity() {
    return Vector2<T>(
            std::numeric_limits<T>::infinity(),
            std::numeric_limits<T>::infinity()
    );
}

template <typename T>
Vector2<T> Vector2<T>::Right() {
    return Vector2<T>(T(1), T(0));
}

template <typename T>
Vector2<T> Vector2<T>::Up() {
    return Vector2<T>(T(0), T(1));
}

template <typename T>
Vector2<T> Vector2<T>::Zero() {
    return Vector2<T>(T(0), T(0));
}

/**
 * @section Methods
 * @subsection Public methods
 */

template <typename T>
bool Vector2<T>::equals(const Vector2<T>& other) const {
    return x == other.x && y == other.y;
}

template <typename T>
void Vector2<T>::set(T x, T y) {
    this->x = x;
    this->y = y;
}

template <typename T>
std::string Vector2<T>::toString() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

/**
 * @section Methods
 * @subsection Static methods
 */

template <typename T>
T Vector2<T>::Angle(const Vector2<T>& from, const Vector2<T>& to) {
    return std::acos(Vector2<T>::Dot(from, to) / (from.magnitude() * to.magnitude()));
}

template <typename T>
Vector2<T> Vector2<T>::ClampMagnitude(const Vector2<T>& vector, T maxLength) {
    if (vector.magnitude() > maxLength) {
        return vector.normalized() * maxLength;
    }

    return vector;
}

template <typename T>
T Vector2<T>::Distance(const Vector2<T>& a, const Vector2<T>& b) {
    return (a - b).magnitude();
}

template <typename T>
T Vector2<T>::Dot(const Vector2<T>& lhs, const Vector2<T>& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

template <typename T>
Vector2<T> Vector2<T>::Lerp(const Vector2<T>& a, const Vector2<T>& b, T t) {
    t = std::clamp(t, T(0), T(1));
    return a + (b - a) * t;
}

template <typename T>
Vector2<T> Vector2<T>::LerpUnclamped(const Vector2<T>& a, const Vector2<T>& b, T t) {
    return a + (b - a) * t;
}

template <typename T>
Vector2<T> Vector2<T>::Max(const Vector2<T>& lhs, const Vector2<T>& rhs) {
    return Vector2<T>(
            std::max(lhs.x, rhs.x),
            std::max(lhs.y, rhs.y)
    );
}

template <typename T>
Vector2<T> Vector2<T>::Min(const Vector2<T>& lhs, const Vector2<T>& rhs) {
    return Vector2<T>(
            std::min(lhs.x, rhs.x),
            std::min(lhs.y, rhs.y)
    );
}

template <typename T>
Vector2<T> Vector2<T>::MoveTowards(const Vector2<T>& current, const Vector2<T>& target, T maxDistanceDelta) {
    Vector2<T> delta = target - current;
    float sqrDeltaMagnitude = delta.sqrMagnitude();

    if (sqrDeltaMagnitude == T(0) ||
        (maxDistanceDelta >= T(0) && sqrDeltaMagnitude <= maxDistanceDelta * maxDistanceDelta)) {
        return target;
    }

    return current + delta * maxDistanceDelta / sqrt(sqrDeltaMagnitude);
}

template <typename T>
Vector2<T> Vector2<T>::Normalize(const Vector2<T>& value) {
    return value.normalized();
}

template <typename T>
Vector2<T> Vector2<T>::Perpendicular(const Vector2<T>& inDirection) {
    return Vector2<T>(-inDirection.y, inDirection.x);
}

template <typename T>
Vector2<T> Vector2<T>::Reflect(const Vector2<T>& inDirection, const Vector2<T>& inNormal) {
    return inDirection - T(2) * Vector2<T>::Dot(inDirection, inNormal) * inNormal;
}

template <typename T>
Vector2<T> Vector2<T>::Scale(const Vector2<T>& a, const Vector2<T>& b) {
    return Vector2<T>(a.x * b.x, a.y * b.y);
}

template <typename T>
T Vector2<T>::SignedAngle(const Vector2<T>& from, const Vector2<T>& to, const Vector2<T>& axis) {
    T angle = Vector2<T>::Angle(from, to);
    T sign = Vector2<T>::Dot(axis, Vector2<T>::Cross(from, to)) < T(0) ? T(-1) : T(1);
    return angle * sign;
}

template <typename T>
Vector2<T> Vector2<T>::SmoothDamp(const Vector2<T>& current, const Vector2<T>& target, Vector2<T>& currentVelocity,
                                  T smoothTime, T maxSpeed, float deltaTime) {
    // TODO: Implement this
}

/**
 * @section Operators
 * @subsection Instance operators
 */

template <typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& other) const {
    return Vector2<T>(x + other.x, y + other.y);
}

template <typename T>
Vector2<T> Vector2<T>::operator-() const {
    return Vector2<T>(-x, -y);
}

template <typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& other) const {
    return Vector2<T>(x - other.x, y - other.y);
}

template <typename T>
Vector2<T> Vector2<T>::operator*(T scalar) const {
    return Vector2<T>(x * scalar, y * scalar);
}

template <typename T>
Vector2<T> Vector2<T>::operator*(const Vector2<T>& other) const {
    return Vector2<T>(x * other.x, y * other.y);
}

template <typename T>
Vector2<T> Vector2<T>::operator/(T scalar) const {
    if (scalar == T(0)) {
        throw std::overflow_error("Divide by zero exception");
    }

    return Vector2<T>(x / scalar, y / scalar);
}

template <typename T>
Vector2<T> Vector2<T>::operator/(const Vector2<T>& other) const {
    if (other.x == T(0) || other.y == T(0)) {
        throw std::overflow_error("Divide by zero exception");
    }

    return Vector2<T>(x / other.x, y / other.y);
}

template <typename T>
bool Vector2<T>::operator==(const Vector2<T>& other) const {
    return Vector2<T>(x - other.x, y - other.y).sqrMagnitude() < T(1e-5);
}

template <typename T>
bool Vector2<T>::operator!=(const Vector2<T>& other) const {
    return Vector2<T>(x - other.x, y - other.y).sqrMagnitude() >= T(1e-5);
}

template <typename T>
T& Vector2<T>::operator[](int index) {
    switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        default:
            throw std::out_of_range("Index out of range");
    }
}

template <typename T>
const T& Vector2<T>::operator[](int index) const {
    switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        default:
            throw std::out_of_range("Index out of range");
    }
}

/**
 * @section Operators
 * @subsection Free operators
 */

template <typename T>
Vector2<T> operator*(const Vector2<T>& a, T scalar) {
    return Vector2<T>(a.x * scalar, a.y * scalar);
}

template <typename T>
Vector2<T> operator*(T scalar, const Vector2<T>& a) {
    return Vector2<T>(scalar * a.x, scalar * a.y);
}

/**
 * @section Template instantiations
 */

template struct Vector2<float>;
template struct Vector2<double>;
template struct Vector2<long double>;
