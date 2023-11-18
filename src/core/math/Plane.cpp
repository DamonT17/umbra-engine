//
// Created by Damon Tregear on 10/11/23.
//

#include "Plane.h"

namespace UmbraEngine::Core::Math {
/******************************
 * @section Constructors
 *****************************/
template<typename T>
Plane<T>::Plane(const Vector3<T>& normal, T distance) {
    this->normal = normal;
    this->distance = distance;
}

template<typename T>
Plane<T>::Plane(const Vector3<T>& normal, const Vector3<T>& point) {
    SetPlane(normal, point);
}

template<typename T>
Plane<T>::Plane(const Vector3<T>& a, const Vector3<T>& b, const Vector3<T>& c) {
    SetPlane(a, b, c);
}

/******************************
 * @section Properties
 * @subsection Instance properties (read-only)
 *****************************/
template<typename T>
Plane<T> Plane<T>::flipped() const {
    return Plane<T>(-normal, -distance);
}

/******************************
 * @section Methods
 * @subsection Public methods
 *****************************/
template<typename T>
Vector3<T> Plane<T>::ClosestPoint(const Vector3<T>& point) const {
    T t = Vector3<T>::Dot(normal, point) + distance;

    return point - (normal * t);
}

template<typename T>
Plane<T> Plane<T>::Flip() const {
    return flipped();
}

template<typename T>
T Plane<T>::GetDistanceToPoint(const Vector3<T>& point) const {
    return Vector3<T>::Dot(normal, point) + distance;
}

template<typename T>
bool Plane<T>::GetSide(const Vector3<T>& point) const {
    return Vector3<T>::Dot(normal, point) + distance >= T(1e-5);
}

template<typename T>
bool Plane<T>::SameSide(const Vector3<T>& a, const Vector3<T>& b) const {
    return GetSide(a) == GetSide(b);
}

template<typename T>
void Plane<T>::SetPlane(const Vector3<T>& a, const Vector3<T>& b, const Vector3<T>& c) {
    Vector3<T> ab = b - a;
    Vector3<T> ac = c - a;

    this->normal = Vector3<T>::Cross(ab, ac).Vector3<T>::normalized();
    this->distance = -Vector3<T>::Dot(normal, a);
}

template<typename T>
void Plane<T>::SetPlane(const Vector3<T>& normal, const Vector3<T>& point) {
    this->normal = normal;
    this->distance = -Vector3<T>::Dot(normal, point);
}

/******************************
 * @section Methods
 * @subsection Static methods
 *****************************/
template<typename T>
Plane<T> Plane<T>::Translate(const Plane<T>& plane, const Vector3<T>& translation) {
    return Plane<T>(plane.normal, plane.distance - Vector3<T>::Dot(plane.normal, translation));
}

/******************************
 * @section Template instantiations
 *****************************/
template struct Plane<float>;
template struct Plane<double>;
}