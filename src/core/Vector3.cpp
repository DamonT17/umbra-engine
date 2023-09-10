//
// Created by Damon Tregear on 8/26/23.
//

#include "Vector3.h"

/**
 * @section Constructors
 */

template <typename T>
Vector3<T>::Vector3() : x(T(0)), y(T(0)), z(T(0)) {}

template <typename T>
Vector3<T>::Vector3(T x, T y) : x(x), y(y), z(T(0)) {}

template <typename T>
Vector3<T>::Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

/**
 * @section Properties
 * @subsection Instance properties
 */

template <typename T>
const T Vector3<T>::magnitude() const {
    return std::sqrt(x * x + y * y + z * z);
}

template <typename T>
const T Vector3<T>::sqrMagnitude() const {
    return x * x + y * y + z * z;
}

template <typename T>
const Vector3<T> Vector3<T>::normalized() const {
    T magnitude = this->magnitude();
    return Vector3<T>(x / magnitude, y / magnitude, z / magnitude);
}

/**
 * @section Properties
 * @subsection Static properties
 */

template <typename T>
Vector3<T> Vector3<T>::Back() {
    return Vector3<T>(T(0), T(0), T(-1));
}

template <typename T>
Vector3<T> Vector3<T>::Down() {
    return Vector3<T>(T(0), T(-1), T(0));
}

template <typename T>
Vector3<T> Vector3<T>::Forward() {
    return Vector3<T>(T(0), T(0), T(1));
}

template <typename T>
Vector3<T> Vector3<T>::Left() {
    return Vector3<T>(T(-1), T(0), T(0));
}

template <typename T>
Vector3<T> Vector3<T>::NegativeInfinity() {
    return Vector3<T>(
        -std::numeric_limits<T>::infinity(),
        -std::numeric_limits<T>::infinity(),
        -std::numeric_limits<T>::infinity()
    );
}

template <typename T>
Vector3<T> Vector3<T>::One() {
    return Vector3<T>(T(1), T(1), T(1));
}

template <typename T>
Vector3<T> Vector3<T>::PositiveInfinity() {
    return Vector3<T>(
        std::numeric_limits<T>::infinity(),
        std::numeric_limits<T>::infinity(),
        std::numeric_limits<T>::infinity()
    );
}

template <typename T>
Vector3<T> Vector3<T>::Right() {
    return Vector3<T>(T(1), T(0), T(0));
}

template <typename T>
Vector3<T> Vector3<T>::Up() {
    return Vector3<T>(T(0), T(1), T(0));
}

template <typename T>
Vector3<T> Vector3<T>::Zero() {
    return Vector3<T>(T(0), T(0), T(0));
}

/**
 * @section Methods
 * @subsection Public methods
 */

template <typename T>
bool Vector3<T>::equals(const Vector3<T>& other) const {
    return x == other.x && y == other.y && z == other.z;
}

template <typename T>
void Vector3<T>::set(T x, T y, T z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

template <typename T>
std::string Vector3<T>::toString() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}

/**
 * @section Methods
 * @subsection Static methods
 */

template <typename T>
T Vector3<T>::Angle(const Vector3<T>& from, const Vector3<T>& to) {
    return std::acos(Vector3<T>::Dot(from, to) / (from.magnitude() * to.magnitude()));
}

template <typename T>
Vector3<T> Vector3<T>::ClampMagnitude(const Vector3<T>& vector, T maxLength) {
    if (vector.magnitude() > maxLength) {
        return vector.normalized() * maxLength;
    }

    return vector;
}

template <typename T>
Vector3<T> Vector3<T>::Cross(const Vector3<T>& lhs, const Vector3<T>& rhs) {
    return Vector3<T>(
        lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.x * rhs.y - lhs.y * rhs.x
    );
}

template <typename T>
T Vector3<T>::Distance(const Vector3<T>& a, const Vector3<T>& b) {
    return (a - b).magnitude();
}

template <typename T>
T Vector3<T>::Dot(const Vector3<T>& lhs, const Vector3<T>& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

template <typename T>
Vector3<T> Vector3<T>::Lerp(const Vector3<T>& a, const Vector3<T>& b, T t) {
    t = std::clamp(t, T(0), T(1));
    return a + (b - a) * t;
}

template <typename T>
Vector3<T> Vector3<T>::LerpUnclamped(const Vector3<T>& a, const Vector3<T>& b, T t) {
    return a + (b - a) * t;
}

template <typename T>
Vector3<T> Vector3<T>::Max(const Vector3<T>& lhs, const Vector3<T>& rhs) {
    return Vector3<T>(
        std::max(lhs.x, rhs.x),
        std::max(lhs.y, rhs.y),
        std::max(lhs.z, rhs.z)
    );
}

template <typename T>
Vector3<T> Vector3<T>::Min(const Vector3<T>& lhs, const Vector3<T>& rhs) {
    return Vector3<T>(
        std::min(lhs.x, rhs.x),
        std::min(lhs.y, rhs.y),
        std::min(lhs.z, rhs.z)
    );
}

template <typename T>
Vector3<T> Vector3<T>::MoveTowards(const Vector3<T>& current, const Vector3<T>& target, T maxDistanceDelta) {
    Vector3<T> delta = target - current;
    float sqrDeltaMagnitude = delta.sqrMagnitude();

    if (sqrDeltaMagnitude == T(0) ||
        (maxDistanceDelta >= T(0) && sqrDeltaMagnitude <= maxDistanceDelta * maxDistanceDelta)) {
        return target;
    }

    return current + delta * maxDistanceDelta / sqrt(sqrDeltaMagnitude);
}

template <typename T>
Vector3<T> Vector3<T>::Normalize(const Vector3<T>& value) {
    return value.normalized();
}

template <typename T>
void Vector3<T>::OrthoNormalize(Vector3<T>& normal, Vector3<T>& tangent) {
    normal = normal.normalized();
    tangent = Vector3<T>::ProjectOnPlane(tangent, normal).normalized();
}

template <typename T>
Vector3<T> Vector3<T>::Project(const Vector3<T>& vector, const Vector3<T>& onNormal) {
    return onNormal * Vector3<T>::Dot(vector, onNormal) / onNormal.sqrMagnitude();
}

template <typename T>
Vector3<T> Vector3<T>::ProjectOnPlane(const Vector3<T>& vector, const Vector3<T>& planeNormal) {
    return vector - Vector3<T>::Project(vector, planeNormal);
}

template <typename T>
Vector3<T> Vector3<T>::Reflect(const Vector3<T>& inDirection, const Vector3<T>& inNormal) {
    return inDirection - T(2) * Vector3<T>::Dot(inDirection, inNormal) * inNormal;
}

template <typename T>
Vector3<T> Vector3<T>::RotateTowards(const Vector3<T>& current, const Vector3<T>& target, T maxRadiansDelta,
                               T maxMagnitudeDelta) {
    T angle = Vector3<T>::Angle(current, target);
    if (angle == T(0)) {
        return target;
    }

    T t = std::min(T(1), maxRadiansDelta / angle);
    return Vector3<T>::SlerpUnclamped(current, target, t).normalized() * Vector3<T>::MoveTowards(current, target,
                                                                                           maxMagnitudeDelta);
}

template <typename T>
Vector3<T> Vector3<T>::Scale(const Vector3<T>& a, const Vector3<T>& b) {
    return Vector3<T>(a.x * b.x, a.y * b.y, a.z * b.z);
}

template <typename T>
T Vector3<T>::SignedAngle(const Vector3<T>& from, const Vector3<T>& to, const Vector3<T>& axis) {
    T angle = Vector3<T>::Angle(from, to);
    T sign = Vector3<T>::Dot(axis, Vector3<T>::Cross(from, to)) < T(0) ? T(-1) : T(1);
    return angle * sign;
}

template <typename T>
Vector3<T> Vector3<T>::Slerp(const Vector3<T>& a, const Vector3<T>& b, T t) {
    t = std::clamp(t, T(0), T(1));
    T angle = Vector3<T>::Angle(a, b);

    return (std::sin((T(1) - t) * angle) / std::sin(angle)) * a + (std::sin(t * angle) / std::sin(angle)) * b;
}

template <typename T>
Vector3<T> Vector3<T>::SlerpUnclamped(const Vector3<T>& a, const Vector3<T>& b, T t) {
    T angle = Vector3<T>::Angle(a, b);

    return (std::sin((T(1) - t) * angle) / std::sin(angle)) * a +
        (std::sin(t * angle) / std::sin(angle)) * b;
}

/**
 * @section Operators
 * @subsection Instance operators
 */

template <typename T>
Vector3<T> Vector3<T>::operator+(const Vector3<T>& other) const {
    return Vector3<T>(x + other.x, y + other.y, z + other.z);
}

template <typename T>
Vector3<T> Vector3<T>::operator-() const {
    return Vector3<T>(-x, -y, -z);
}

template <typename T>
Vector3<T> Vector3<T>::operator-(const Vector3<T>& other) const {
    return Vector3<T>(x - other.x, y - other.y, z - other.z);
}

template <typename T>
Vector3<T> Vector3<T>::operator*(T scalar) const {
    return Vector3<T>(x * scalar, y * scalar, z * scalar);
}

template <typename T>
Vector3<T> Vector3<T>::operator*(const Vector3<T>& other) const {
    return Vector3<T>(x * other.x, y * other.y, z * other.z);
}

template <typename T>
Vector3<T> Vector3<T>::operator/(T scalar) const {
    if (scalar == T(0)) {
        throw std::overflow_error("Divide by zero exception");
    }

    return Vector3<T>(x / scalar, y / scalar, z / scalar);
}

template <typename T>
Vector3<T> Vector3<T>::operator/(const Vector3<T>& other) const {
    if (other.x == T(0) || other.y == T(0) || other.z == T(0)) {
        throw std::overflow_error("Divide by zero exception");
    }

    return Vector3<T>(x / other.x, y / other.y, z / other.z);
}

template <typename T>
bool Vector3<T>::operator==(const Vector3<T>& other) const {
    return Vector3<T>(x - other.x, y - other.y, z - other.z).sqrMagnitude() < T(1e-5);
}

template <typename T>
bool Vector3<T>::operator!=(const Vector3<T>& other) const {
    return Vector3<T>(x - other.x, y - other.y, z - other.z).sqrMagnitude() >= T(1e-5);
}

template <typename T>
T& Vector3<T>::operator[](int index) {
    switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            throw std::out_of_range("Index out of range");
    }
}

template <typename T>
const T& Vector3<T>::operator[](int index) const {
    switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            throw std::out_of_range("Index out of range");
    }
}

/**
 * @section Operators
 * @subsection Free operators
 */

template <typename T>
Vector3<T> operator*(const Vector3<T>& a, T scalar) {
    return Vector3<T>(a.x * scalar, a.y * scalar, a.z * scalar);
}

template <typename T>
Vector3<T> operator*(T scalar, const Vector3<T>& a) {
    return Vector3<T>(scalar * a.x, scalar * a.y, scalar * a.z);
}

/**
 * @section Template instantiations
 */

template struct Vector3<float>;
template struct Vector3<double>;
template struct Vector3<long double>;
