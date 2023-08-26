//
// Created by Damon Tregear on 8/26/23.
//

#ifndef UMBRA_ENGINE_VECTOR3_H
#define UMBRA_ENGINE_VECTOR3_H

struct Vector3 {
    float x;
    float y;
    float z;
    const float magnitude;
    const float sqrMagnitude;
    Vector3 normalized;

    Vector3();                          // Default constructor
    Vector3(float x, float y, float z); // Constructor with parameters

    // Operator overloading
    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator*(const Vector3& other) const;
    Vector3 operator/(const Vector3& other) const;
    Vector3 operator==(const Vector3& other) const;
    Vector3 operator!=(const Vector3& other) const;
    float& operator[](int index);
    const float& operator[](int index) const;

    // Static properties
    static Vector3 Back();
    static Vector3 Down();
    static Vector3 Forward();
    static Vector3 Left();
    static Vector3 NegativeInfinity();
    static Vector3 One();
    static Vector3 PositiveInfinity();
    static Vector3 Right();
    static Vector3 Up();
    static Vector3 Zero();

    // Static methods
    static float Angle(const Vector3& from, const Vector3& to);
    static Vector3 ClampMagnitude(const Vector3& vector, float maxLength);
    static float Cross(const Vector3& lhs, const Vector3& rhs);
    static float Distance(const Vector3& a, const Vector3& b);
    static float Dot(const Vector3& lhs, const Vector3& rhs);
    static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);
    static Vector3 LerpUnclamped(const Vector3& a, const Vector3& b, float t);
    static Vector3 Max(const Vector3& lhs, const Vector3& rhs);
    static Vector3 Min(const Vector3& lhs, const Vector3& rhs);
    static Vector3 MoveTowards(const Vector3& current, const Vector3& target, float maxDistanceDelta);
    static Vector3 Normalize(const Vector3& value);
    static void OrthoNormalize(Vector3& normal, Vector3& tangent);
    static Vector3 Project(const Vector3& vector, const Vector3& onNormal);
    static Vector3 ProjectOnPlane(const Vector3& vector, const Vector3& planeNormal);
    static Vector3 Reflect(const Vector3& inDirection, const Vector3& inNormal);
    static Vector3 RotateTowards(const Vector3& current, const Vector3& target, float maxRadiansDelta, float maxMagnitudeDelta);
    static Vector3 Scale(const Vector3& a, const Vector3& b);
    static float SignedAngle(const Vector3& from, const Vector3& to, const Vector3& axis);
    static Vector3 Slerp(const Vector3& a, const Vector3& b, float t);
    static Vector3 SlerpUnclamped(const Vector3& a, const Vector3& b, float t);

    // Instance methods
    bool Equals(const Vector3& other) const;
    void Set(float x, float y, float z);
    std::string ToString() const;
};

#endif //UMBRA_ENGINE_VECTOR3_H
