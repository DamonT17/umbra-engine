//
// Created by Damon Tregear on 8/30/23.
//

#include "Vector4.h"

namespace UmbraEngine::Core::Math {
/**
 * @section Constructors
 */
    template<typename T>
    Vector4<T>::Vector4() : x(T(0)), y(T(0)), z(T(0)), w(T(0)) {}

    template<typename T>
    Vector4<T>::Vector4(T x, T y) : x(x), y(y), z(T(0)), w(T(0)) {}

    template<typename T>
    Vector4<T>::Vector4(T x, T y, T z) : x(x), y(y), z(z), w(T(0)) {}

    template<typename T>
    Vector4<T>::Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

/**
 * @section Properties
 * @subsection Instance properties
 */
    template<typename T>
    T Vector4<T>::magnitude() const {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }

    template<typename T>
    T Vector4<T>::sqrMagnitude() const {
        return x * x + y * y + z * z + w * w;
    }

    template<typename T>
    Vector4<T> Vector4<T>::normalized() const {
        T magnitude = this->magnitude();
        return Vector4<T>(x / magnitude, y / magnitude, z / magnitude, w / magnitude);
    }

/**
 * @section Properties
 * @subsection Static properties
 */
    template<typename T>
    Vector4<T> Vector4<T>::NegativeInfinity() {
        return Vector4<T>(
                -std::numeric_limits<T>::infinity(),
                -std::numeric_limits<T>::infinity(),
                -std::numeric_limits<T>::infinity(),
                -std::numeric_limits<T>::infinity()
        );
    }

    template<typename T>
    Vector4<T> Vector4<T>::One() {
        return Vector4<T>(T(1), T(1), T(1), T(1));
    }

    template<typename T>
    Vector4<T> Vector4<T>::PositiveInfinity() {
        return Vector4<T>(
                std::numeric_limits<T>::infinity(),
                std::numeric_limits<T>::infinity(),
                std::numeric_limits<T>::infinity(),
                std::numeric_limits<T>::infinity()
        );
    }

    template<typename T>
    Vector4<T> Vector4<T>::Zero() {
        return Vector4<T>(T(0), T(0), T(0), T(0));
    }

/**
 * @section Methods
 * @subsection Public methods
 */
    template<typename T>
    bool Vector4<T>::equals(const Vector4<T>& other) const {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    template<typename T>
    void Vector4<T>::set(T x, T y, T z, T w) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    template<typename T>
    std::string Vector4<T>::toString() const {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " +
               std::to_string(w) + ")";
    }

/**
 * @section Methods
 * @subsection Static methods
 */
    template<typename T>
    T Vector4<T>::Distance(const Vector4<T>& a, const Vector4<T>& b) {
        return (a - b).magnitude();
    }

    template<typename T>
    T Vector4<T>::Dot(const Vector4<T>& lhs, const Vector4<T>& rhs) {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
    }

    template<typename T>
    Vector4<T> Vector4<T>::Lerp(const Vector4<T>& a, const Vector4<T>& b, T t) {
        t = std::clamp(t, T(0), T(1));
        return a + (b - a) * t;
    }

    template<typename T>
    Vector4<T> Vector4<T>::LerpUnclamped(const Vector4<T>& a, const Vector4<T>& b, T t) {
        return a + (b - a) * t;
    }

    template<typename T>
    Vector4<T> Vector4<T>::Max(const Vector4<T>& lhs, const Vector4<T>& rhs) {
        return Vector4<T>(
                std::max(lhs.x, rhs.x),
                std::max(lhs.y, rhs.y),
                std::max(lhs.z, rhs.z),
                std::max(lhs.w, rhs.w)
        );
    }

    template<typename T>
    Vector4<T> Vector4<T>::Min(const Vector4<T>& lhs, const Vector4<T>& rhs) {
        return Vector4<T>(
                std::min(lhs.x, rhs.x),
                std::min(lhs.y, rhs.y),
                std::min(lhs.z, rhs.z),
                std::min(lhs.w, rhs.w)
        );
    }

    template<typename T>
    Vector4<T> Vector4<T>::MoveTowards(const Vector4<T>& current, const Vector4<T>& target, T maxDistanceDelta) {
        Vector4<T> delta = target - current;
        float sqrDeltaMagnitude = delta.sqrMagnitude();

        if (sqrDeltaMagnitude == T(0) ||
            (maxDistanceDelta >= T(0) && sqrDeltaMagnitude <= maxDistanceDelta * maxDistanceDelta)) {
            return target;
        }

        return current + delta * maxDistanceDelta / sqrt(sqrDeltaMagnitude);
    }

    template<typename T>
    Vector4<T> Vector4<T>::Normalize(const Vector4<T>& value) {
        return value.normalized();
    }

    template<typename T>
    Vector4<T> Vector4<T>::Project(const Vector4<T>& vector, const Vector4<T>& onNormal) {
        return onNormal * Vector4<T>::Dot(vector, onNormal) / onNormal.sqrMagnitude();
    }

    template<typename T>
    Vector4<T> Vector4<T>::Scale(const Vector4<T>& a, const Vector4<T>& b) {
        return Vector4<T>(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
    }

/**
 * @section Operators
 * @subsection Instance operators
 */
    template<typename T>
    Vector4<T> Vector4<T>::operator+(const Vector4<T>& other) const {
        return Vector4<T>(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    template<typename T>
    Vector4<T> Vector4<T>::operator-() const {
        return Vector4<T>(-x, -y, -z, -w);
    }

    template<typename T>
    Vector4<T> Vector4<T>::operator-(const Vector4<T>& other) const {
        return Vector4<T>(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    template<typename T>
    Vector4<T> Vector4<T>::operator*(T scalar) const {
        return Vector4<T>(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    template<typename T>
    Vector4<T> Vector4<T>::operator*(const Vector4<T>& other) const {
        return Vector4<T>(x * other.x, y * other.y, z * other.z, w * other.w);
    }

    template<typename T>
    Vector4<T> Vector4<T>::operator/(T scalar) const {
        if (scalar == T(0)) {
            throw std::overflow_error("Divide by zero exception");
        }

        return Vector4<T>(x / scalar, y / scalar, z / scalar, w / scalar);
    }

    template<typename T>
    Vector4<T> Vector4<T>::operator/(const Vector4<T>& other) const {
        if (other.x == T(0) || other.y == T(0) || other.z == T(0) || other.w == T(0)) {
            throw std::overflow_error("Divide by zero exception");
        }

        return Vector4<T>(x / other.x, y / other.y, z / other.z, w / other.w);
    }

    template<typename T>
    bool Vector4<T>::operator==(const Vector4<T>& other) const {
        return Vector4<T>(x - other.x, y - other.y, z - other.z, w - other.w).sqrMagnitude() < T(1e-5);
    }

    template<typename T>
    bool Vector4<T>::operator!=(const Vector4<T>& other) const {
        return Vector4<T>(x - other.x, y - other.y, z - other.z, w - other.w).sqrMagnitude() >= T(1e-5);
    }

    template<typename T>
    T& Vector4<T>::operator[](int index) {
        switch (index) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            case 3:
                return w;
            default:
                throw std::out_of_range("Index out of range");
        }
    }

    template<typename T>
    const T& Vector4<T>::operator[](int index) const {
        switch (index) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            case 3:
                return w;
            default:
                throw std::out_of_range("Index out of range");
        }
    }

/**
 * @section Operators
 * @subsection Free operators
 */
    template<typename T>
    Vector4<T> operator*(const Vector4<T>& a, T scalar) {
        return Vector4<T>(a.x * scalar, a.y * scalar, a.z * scalar, a.w * scalar);
    }

    template<typename T>
    Vector4<T> operator*(T scalar, const Vector4<T>& a) {
        return Vector4<T>(scalar * a.x, scalar * a.y, scalar * a.z, scalar * a.w);
    }

/**
 * @section Template instantiations
 */
    template struct Vector4<float>;
    template struct Vector4<double>;
}
