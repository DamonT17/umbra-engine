//
// Created by Damon Tregear on 10/4/2023.
//

#include "Quaternion.h"

namespace UmbraEngine::Core::Math {
/******************************
 * @section Constructors
 *****************************/
template<typename T>
Quaternion<T>::Quaternion() : x(T(0)), y(T(0)), z(T(0)), w(T(0)) {}

template<typename T>
Quaternion<T>::Quaternion(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

template<typename T>
Quaternion<T>::Quaternion(const Quaternion<T>& other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    this->w = other.w;
}

/******************************
 * @section Properties
 * @subsection Instance properties
 *****************************/
template<typename T>
Vector3<T> Quaternion<T>::eulerAngles() {
    return Vector3<T>(
            std::atan2(2 * (w * x + y * z), 1 - 2 * (x * x + y * y)),
            std::asin(2 * (w * y - z * x)),
            std::atan2(2 * (w * z + x * y), 1 - 2 * (y * y + z * z))
    );
}

template<typename T>
T Quaternion<T>::magnitude() const {
    return std::sqrt(x * x + y * y + z * z + w * w);
}

template<typename T>
Quaternion<T> Quaternion<T>::normalized() const {
    return *this / this->magnitude();
}

/******************************
 * @section Properties
 * @subsection Static properties
 *****************************/
template<typename T>
Quaternion<T> Quaternion<T>::Identity() {
    return Quaternion<T>(T(0), T(0), T(0), T(1));
}

/******************************
 * @brief Methods
 * @subsection Public methods
 *****************************/
template<typename T>
void Quaternion<T>::set(T x, T y, T z, T w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

template<typename T>
std::string Quaternion<T>::toString() const {
    return std::string("(") + std::to_string(x) + ", " + std::to_string(y) + ", " +
           std::to_string(z) + ", " + std::to_string(w) + ")";
}

/******************************
 * @section Methods
 * @subsection Static methods
 *****************************/
template<typename T>
static T Angle(const Quaternion<T>& a, const Quaternion<T>& b) {
    return std::acos(std::abs(Quaternion<T>::Dot(a, b))) * T(2) * T(180) / T(M_PI);
}

template<typename T>
static Quaternion<T> AngleAxis(T angle, const Vector3<T>& axis) {
    T halfAngle = angle * T(0.5);
    T cosHalfAngle = std::cos(halfAngle);
    T sinHalfAngle = std::sin(halfAngle);

    return Quaternion<T>(axis.x * sinHalfAngle, axis.y * sinHalfAngle, axis.z * sinHalfAngle, cosHalfAngle);
}

template<typename T>
static T Dot(const Quaternion<T>& a, const Quaternion<T>& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

template<typename T>
static Quaternion<T> Euler(T x, T y, T z) {
    // Calculate the cosine and sine of the half angles
    T halfX = x * T(0.5);
    T cosHalfX = std::cos(halfX);
    T sinHalfX = std::sin(halfX);

    T halfY = y * T(0.5);
    T cosHalfY = std::cos(halfY);
    T sinHalfY = std::sin(halfY);

    T halfZ = z * T(0.5);
    T cosHalfZ = std::cos(halfZ);
    T sinHalfZ = std::sin(halfZ);

    // Calculate the x, y, z, and w components
    T newX = cosHalfY * sinHalfX * cosHalfZ + sinHalfY * cosHalfX * sinHalfZ;
    T newY = sinHalfY * cosHalfX * cosHalfZ - cosHalfY * sinHalfX * sinHalfZ;
    T newZ = cosHalfY * cosHalfX * sinHalfZ - sinHalfY * sinHalfX * cosHalfZ;
    T newW = cosHalfY * cosHalfX * cosHalfZ + sinHalfY * sinHalfX * sinHalfZ;

    return Quaternion<T>(newX, newY, newZ, newW);
}

template<typename T>
static Quaternion<T> Inverse(const Quaternion<T>& rotation) {
    return Quaternion<T>(-rotation.x, -rotation.y, -rotation.z, rotation.w);
}

template<typename T>
static Quaternion<T> Lerp(const Quaternion<T>& a, const Quaternion<T>& b, T t) {
    t = std::clamp(t, T(0), T(1));

    return a + (b - a) * t;
}

template<typename T>
static Quaternion<T> LerpUnclamped(const Quaternion<T>& a, const Quaternion<T>& b, T t) {
    return a + (b - a) * t;
}

template<typename T>
static Quaternion<T> Normalize(const Quaternion<T>& rotation) {
    return rotation.normalized();
}

template<typename T>
static Quaternion<T> RotateTowards(const Quaternion<T>& from, const Quaternion<T>& to, T maxDegreesDelta) {
    T angle = Quaternion<T>::Angle(from, to);
    if (angle < T(1e-5)) {
        return to;
    }

    T t = std::min(T(1), maxDegreesDelta / angle);

    return Quaternion<T>::SlerpUnclamped(from, to, t);
}

template<typename T>
static Quaternion<T> Slerp(const Quaternion<T>& a, const Quaternion<T>& b, T t) {
    t = std::clamp(t, T(0), T(1));
    T angle = Quaternion<T>::Angle(a, b);

    return (std::sin((T(1) - t) * angle) / std::sin(angle)) * a + (std::sin(t * angle) / std::sin(angle)) * b;
}

template<typename T>
static Quaternion<T> SlerpUnclamped(const Quaternion<T>& a, const Quaternion<T>& b, T t) {
    T angle = Quaternion<T>::Angle(a, b);

    return (std::sin((T(1) - t) * angle) / std::sin(angle)) * a + (std::sin(t * angle) / std::sin(angle)) * b;
}

/******************************
 * @section Operators
 * @subsection Instance operators
 *****************************/
template<typename T>
Quaternion<T> Quaternion<T>::operator+(const Quaternion<T>& other) const {
    return Quaternion<T>(x + other.x, y + other.y, z + other.z, w + other.w);
}

template<typename T>
Quaternion<T> Quaternion<T>::operator+=(const Quaternion<T>& other) {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    this->w += other.w;

    return *this;
}

template<typename T>
Quaternion<T> Quaternion<T>::operator-(const Quaternion<T>& other) const {
    return Quaternion<T>(x - other.x, y - other.y, z - other.z, w - other.w);
}

template<typename T>
Quaternion<T> Quaternion<T>::operator-=(const Quaternion<T>& other) {
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    this->w -= other.w;

    return *this;
}

template<typename T>
Quaternion<T> Quaternion<T>::operator-() const {
    return Quaternion<T>(-x, -y, -z, -w);
}

template<typename T>
Quaternion<T> Quaternion<T>::operator*(T scalar) const {
    return Quaternion<T>(x * scalar, y * scalar, z * scalar, w * scalar);
}

template<typename T>
Quaternion<T> Quaternion<T>::operator*(const Quaternion<T>& other) const {
    return Quaternion<T>(
            w * other.x + x * other.w + y * other.z - z * other.y,
            w * other.y + y * other.w + z * other.x - x * other.z,
            w * other.z + z * other.w + x * other.y - y * other.x,
            w * other.w - x * other.x - y * other.y - z * other.z
    );
}

template<typename T>
Quaternion<T> Quaternion<T>::operator*=(const Quaternion<T>& other) {
    this->x = w * other.x + x * other.w + y * other.z - z * other.y;
    this->y = w * other.y + y * other.w + z * other.x - x * other.z;
    this->z = w * other.z + z * other.w + x * other.y - y * other.x;
    this->w = w * other.w - x * other.x - y * other.y - z * other.z;

    return *this;
}

template<typename T>
Quaternion<T> Quaternion<T>::operator/(T scalar) const {
    if (scalar < T(1e-5)) {
        throw std::overflow_error("Divide by zero exception");
    }

    return Quaternion<T>(x / scalar, y / scalar, z / scalar, w / scalar);
}

template<typename T>
Quaternion<T> Quaternion<T>::operator/=(T scalar) {
    if (scalar < T(1e-5)) {
        throw std::overflow_error("Divide by zero exception");
    }

    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;
    this->w /= scalar;

    return *this;
}

template<typename T>
bool Quaternion<T>::operator==(const Quaternion<T>& other) const {
    return Quaternion<T>(x - other.x, y - other.y, z - other.z, w - other.w).magnitude() < T(1e-5);
}

template<typename T>
bool Quaternion<T>::operator!=(const Quaternion<T>& other) const {
    return Quaternion<T>(x - other.x, y - other.y, z - other.z, w - other.w).magnitude() >= T(1e-5);
}

template<typename T>
T& Quaternion<T>::operator[](int index) {
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
const T& Quaternion<T>::operator[](int index) const {
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

/******************************
 * @section Template instantiations
 *****************************/
    template struct Quaternion<float>;
    template struct Quaternion<double>;
}