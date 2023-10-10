//
// Created by Damon Tregear on 10/9/23.
//

#include "Ray2.h"

/**
 * @section Constructors
 */

template <typename T>
Ray2<T>::Ray2() : direction(Vector2<T>::Forward()), origin(Vector2<T>::Zero()) {}

template <typename T>
Ray2<T>::Ray2(const Vector2<T>& origin, const Vector2<T>& direction, bool directionIsNormalized) {
    this->origin = origin;
    this->direction = directionIsNormalized ? direction : direction.normalized();
}

/**
 * @section Methods
 * @subsection Public methods
 */

template <typename T>
Vector2<T> Ray2<T>::pointAtDistance(T distance) const {
    return origin + direction * distance;
}

template <typename T>
T Ray2<T>::distanceToPoint(const Vector2<T>& point) const {
    return (point - origin).magnitude();
}

template <typename T>
T Ray2<T>::squaredDistanceToPoint(const Vector2<T>& point) const {
    return (point - origin).squaredMagnitude();
}

template <typename T>
std::string Ray2<T>::toString() const {
    return "Ray(" + origin.toString() + ", " + direction.toString() + ")";
}
