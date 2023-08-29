//
// Created by Damon Tregear on 8/26/23.
//

#include "Vector3.h"

/**
 * @section Constructors
 */

Vector3::Vector3() {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

Vector3::Vector3(float x, float y) {
    this->x = x;
    this->y = y;
    this->z = 0.0f;
}

Vector3::Vector3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

/**
 * @section Properties
 * @subsection Instance properties
 */

const float Vector3::magnitude() const {
    return std::sqrt(x * x + y * y + z * z);
}

const float Vector3::sqrMagnitude() const {
    return x * x + y * y + z * z;
}

const Vector3 Vector3::normalized() const {
    float magnitude = this->magnitude();
    return Vector3(x / magnitude, y / magnitude, z / magnitude);
}

/**
 * @section Properties
 * @subsection Static properties
 */

Vector3 Vector3::Back() {
    return Vector3(0.0f, 0.0f, -1.0f);
}

Vector3 Vector3::Down() {
    return Vector3(0.0f, -1.0f, 0.0f);
}

Vector3 Vector3::Forward() {
    return Vector3(0.0f, 0.0f, 1.0f);
}

Vector3 Vector3::Left() {
    return Vector3(-1.0f, 0.0f, 0.0f);
}

Vector3 Vector3::NegativeInfinity() {
    return Vector3(
        -std::numeric_limits<float>::infinity(),
        -std::numeric_limits<float>::infinity(),
        -std::numeric_limits<float>::infinity()
    );
}

Vector3 Vector3::One() {
    return Vector3(1.0f, 1.0f, 1.0f);
}

Vector3 Vector3::PositiveInfinity() {
    return Vector3(
        std::numeric_limits<float>::infinity(),
        std::numeric_limits<float>::infinity(),
        std::numeric_limits<float>::infinity()
    );
}

Vector3 Vector3::Right() {
    return Vector3(1.0f, 0.0f, 0.0f);
}

Vector3 Vector3::Up() {
    return Vector3(0.0f, 1.0f, 0.0f);
}

Vector3 Vector3::Zero() {
    return Vector3(0.0f, 0.0f, 0.0f);
}

/**
 * @section Methods
 * @subsection Public methods
 */

bool Vector3::equals(const Vector3 &other) const {
    return x == other.x && y == other.y && z == other.z;
}

void Vector3::set(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

std::string Vector3::toString() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}

/**
 * @section Methods
 * @subsection Static methods
 */

float Vector3::Angle(const Vector3 &from, const Vector3 &to) {
    return acos(Vector3::Dot(from, to) / (from.magnitude() * to.magnitude()));
}

Vector3 Vector3::ClampMagnitude(const Vector3 &vector, float maxLength) {
    if (vector.magnitude() > maxLength) {
        return vector.normalized() * maxLength;
    }

    return vector;
}

Vector3 Vector3::Cross(const Vector3 &lhs, const Vector3 &rhs) {
    return Vector3(
        lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.x * rhs.y - lhs.y * rhs.x
    );
}

float Vector3::Distance(const Vector3 &a, const Vector3 &b) {
    return (a - b).magnitude();
}

float Vector3::Dot(const Vector3 &lhs, const Vector3 &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Vector3 Vector3::Lerp(const Vector3 &a, const Vector3 &b, float t) {
    t = std::clamp(t, 0.0f, 1.0f);
    return a + (b - a) * t;
}

Vector3 Vector3::LerpUnclamped(const Vector3 &a, const Vector3 &b, float t) {
    return a + (b - a) * t;
}

Vector3 Vector3::Max(const Vector3 &lhs, const Vector3 &rhs) {
    return Vector3(
        std::max(lhs.x, rhs.x),
        std::max(lhs.y, rhs.y),
        std::max(lhs.z, rhs.z)
    );
}

Vector3 Vector3::Min(const Vector3 &lhs, const Vector3 &rhs) {
    return Vector3(
        std::min(lhs.x, rhs.x),
        std::min(lhs.y, rhs.y),
        std::min(lhs.z, rhs.z)
    );
}

Vector3 Vector3::MoveTowards(const Vector3 &current, const Vector3 &target, float maxDistanceDelta) {
    Vector3 delta = target - current;
    float sqrDeltaMagnitude = delta.sqrMagnitude();

    if (sqrDeltaMagnitude == 0.0f ||
        (maxDistanceDelta >= 0.0f && sqrDeltaMagnitude <= maxDistanceDelta * maxDistanceDelta)) {
        return target;
    }

    return current + delta * maxDistanceDelta / sqrt(sqrDeltaMagnitude);
}

Vector3 Vector3::Normalize(const Vector3 &value) {
    return value.normalized();
}

void Vector3::OrthoNormalize(Vector3 &normal, Vector3 &tangent) {
    normal = normal.normalized();
    tangent = Vector3::ProjectOnPlane(tangent, normal).normalized();
}

Vector3 Vector3::Project(const Vector3 &vector, const Vector3 &onNormal) {
    return onNormal * Vector3::Dot(vector, onNormal) / onNormal.sqrMagnitude();
}

Vector3 Vector3::ProjectOnPlane(const Vector3 &vector, const Vector3 &planeNormal) {
    return vector - Vector3::Project(vector, planeNormal);
}

Vector3 Vector3::Reflect(const Vector3 &inDirection, const Vector3 &inNormal) {
    return inDirection - 2.0f * Vector3::Dot(inDirection, inNormal) * inNormal;
}

Vector3 Vector3::RotateTowards(const Vector3 &current, const Vector3 &target, float maxRadiansDelta,
                               float maxMagnitudeDelta) {
    float angle = Vector3::Angle(current, target);
    if (angle == 0.0f) {
        return target;
    }

    float t = std::min(1.0f, maxRadiansDelta / angle);
    return Vector3::SlerpUnclamped(current, target, t).normalized() * Vector3::MoveTowards(current, target,
                                                                                           maxMagnitudeDelta);
}

Vector3 Vector3::Scale(const Vector3 &a, const Vector3 &b) {
    return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
}

float Vector3::SignedAngle(const Vector3 &from, const Vector3 &to, const Vector3 &axis) {
    float angle = Vector3::Angle(from, to);
    float sign = Vector3::Dot(axis, Vector3::Cross(from, to)) < 0.0f ? -1.0f : 1.0f;
    return angle * sign;
}

Vector3 Vector3::Slerp(const Vector3 &a, const Vector3 &b, float t) {
    t = std::clamp(t, 0.0f, 1.0f);
    float angle = Vector3::Angle(a, b);
    return (std::sin((1.0f - t) * angle) / std::sin(angle)) * a +
        (std::sin(t * angle) / std::sin(angle)) * b;
}

Vector3 Vector3::SlerpUnclamped(const Vector3 &a, const Vector3 &b, float t) {
    float angle = Vector3::Angle(a, b);
    return (sin((1.0f - t) * angle) / sin(angle)) * a + (sin(t * angle) / sin(angle)) * b;
}

/**
 * @section Operators
 * @subsection Instance operators
 */

Vector3 Vector3::operator+(const Vector3 &other) const {
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3 &other) const {
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator*(float scalar) const {
    return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3 Vector3::operator*(const Vector3 &other) const {
    return Vector3(x * other.x, y * other.y, z * other.z);
}

Vector3 Vector3::operator/(float scalar) const {
    if (scalar == 0.0f) {
        throw std::overflow_error("Divide by zero exception");
    }

    return Vector3(x / scalar, y / scalar, z / scalar);
}

Vector3 Vector3::operator/(const Vector3 &other) const {
    if (other.x == 0.0f || other.y == 0.0f || other.z == 0.0f) {
        throw std::overflow_error("Divide by zero exception");
    }

    return Vector3(x / other.x, y / other.y, z / other.z);
}

bool Vector3::operator==(const Vector3 &other) const {
    return Vector3(x - other.x, y - other.y, z - other.z).sqrMagnitude() < 1e-5;
}

bool Vector3::operator!=(const Vector3 &other) const {
    return Vector3(x - other.x, y - other.y, z - other.z).sqrMagnitude() >= 1e-5;
}

float &Vector3::operator[](int index) {
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

const float &Vector3::operator[](int index) const {
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

Vector3 operator*(const Vector3& a, float scalar) {
    return Vector3(a.x * scalar, a.y * scalar, a.z * scalar);
}

Vector3 operator*(float scalar, const Vector3& a) {
    return Vector3(scalar * a.x, scalar * a.y, scalar * a.z);
}