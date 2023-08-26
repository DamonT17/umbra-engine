//
// Created by Damon Tregear on 8/26/23.
//

#include "Vector3.h"

Vector3::Vector3() : x(0.0), y(0.0), z(0.0), magnitude(0.0), sqrMagnitude(0.0), normalized(Vector3::Zero()) {}

Vector3::Vector3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;

    magnitude = sqrt(x * x + y * y + z * z);
    sqrMagnitude = x * x + y * y + z * z;
    // TODO: normalized
}

Vector3 Vector3::operator+(const Vector3 &other) const {
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3 &other) const {
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator*(const Vector3 &other) const {
    return Vector3(x * other.x, y * other.y, z * other.z);
}

Vector3 Vector3::operator/(const Vector3 &other) const {
    return Vector3(x / other.x, y / other.y, z / other.z);
}

Vector3 Vector3::operator==(const Vector3 &other) const {
    return Vector3(x - other.x, y - other.y, z - other.z).sqrMagnitude < 1e-5;
}

Vector3 Vector3::operator!=(const Vector3 &other) const {
    return Vector3(x - other.x, y - other.y, z - other.z).sqrMagnitude > 1e-5;
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

Vector3 Vector3::Back() {
    return Vector3(0.0, 0.0, -1.0);
}

Vector3 Vector3::Down() {
    return Vector3(0.0, -1.0, 0.0);
}

Vector3 Vector3::Forward() {
    return Vector3(0.0, 0.0, 1.0);
}

Vector3 Vector3::Left() {
    return Vector3(-1.0, 0.0, 0.0);
}

Vector3 Vector3::NegativeInfinity() {
    return Vector3(
        -std::numeric_limits<float>::infinity(),
        -std::numeric_limits<float>::infinity(),
        -std::numeric_limits<float>::infinity()
    );
}

Vector3 Vector3::One() {
    return Vector3(1.0, 1.0, 1.0);
}

Vector3 Vector3::PositiveInfinity() {
    return Vector3(
        std::numeric_limits<float>::infinity(),
        std::numeric_limits<float>::infinity(),
        std::numeric_limits<float>::infinity()
    );
}

Vector3 Vector3::Right() {
    return Vector3(1.0, 0.0, 0.0);
}

Vector3 Vector3::Up() {
    return Vector3(0.0, 1.0, 0.0);
}

Vector3 Vector3::Zero() {
    return Vector3(0.0, 0.0, 0.0);
}

float Vector3::Cross(const Vector3 &lhs, const Vector3 &rhs) {
    return lhs.magnitude * rhs.magnitude * sin(Vector3::Angle(lhs, rhs));
}

float Vector3::Dot(const Vector3 &lhs, const Vector3 &rhs) {
    return lhs.magnitude * rhs.magnitude * cos(Vector3::Angle(lhs, rhs));
}



bool Vector3::Equals(const Vector3 &other) const {
    return x == other.x && y == other.y && z == other.z;
}

void Vector3::Set(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

std::string Vector3::ToString() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}
