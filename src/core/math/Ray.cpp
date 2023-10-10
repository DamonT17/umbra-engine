//
// Created by Damon Tregear on 10/9/23.
//

#include "Ray.h"

/**
 * @section Constructors
 */

template <typename T>
Ray<T>::Ray() : direction(Vector3<T>::Forward()), origin(Vector3<T>::Zero()) {}

template <typename T>
Ray<T>::Ray(const Vector3<T>& origin, const Vector3<T>& direction, bool directionIsNormalized) {
    this->origin = origin;
    this->direction = directionIsNormalized ? direction : direction.normalized();
}

/**
 * @section Methods
 * @subsection Public methods
 */

template <typename T>
Vector3<T> Ray<T>::pointAtDistance(T distance) const {
    return origin + direction * distance;
}

template <typename T>
T Ray<T>::distanceToPoint(const Vector3<T>& point) const {
    return (point - origin).magnitude();
}

template <typename T>
T Ray<T>::squaredDistanceToPoint(const Vector3<T>& point) const {
    return (point - origin).squaredMagnitude();
}

template <typename T>
std::string Ray<T>::toString() const {
    return "Ray(" + origin.toString() + ", " + direction.toString() + ")";
}