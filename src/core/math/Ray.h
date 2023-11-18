//
// Created by Damon Tregear on 10/9/23.
//

#ifndef UMBRAENGINE_RAY_H
#define UMBRAENGINE_RAY_H

#include "Vector3.h"

namespace UmbraEngine::Core::Math {
/**
 * @struct Ray
 * @brief Representation of rays in 3D.
 *
 * @details A ray is a line that extends to infinity in only one direction.
 */
template<typename T>
struct Ray {
/******************************
 * @section Properties
 * @subsection Instance properties
 *****************************/
    /**
     * @property direction
     * @brief The direction of the ray.
     */
    Vector3<T> direction;

    /**
     * @property origin
     * @brief The origin point of the ray.
     */
    Vector3<T> origin;

/******************************
 * @section Constructors
 *****************************/
    /**
     * @brief Default constructor. Initializes a ray with an origin of 0 and in the positive z-direction.
     */
    Ray<T>();

    /**
     * @brief Initializes a ray with the given origin and direction. The direction will be normalized unless
     * directionIsNormalized is true.
     */
    Ray<T>(const Vector3<T>& origin, const Vector3<T>& direction, bool directionIsNormalized = false);

/******************************
 * @section Methods
 * @subsection Public methods
 *****************************/
    /**
     * @brief Returns the point at the given distance along the ray.
     * @param distance The distance along the ray.
     * @return The point at the given distance along the ray.
     */
    Vector3<T> pointAtDistance(T distance) const;

    /**
     * @brief Returns the distance from the ray's origin to the given point.
     * @param point The point to find the distance to.
     * @return The distance from the ray's origin to the given point.
     */
    T distanceToPoint(const Vector3<T>& point) const;

    /**
     * @brief Returns the squared distance from the ray's origin to the given point.
     * @param point The point to find the squared distance to.
     * @return The squared distance from the ray's origin to the given point.
     */
    T squaredDistanceToPoint(const Vector3<T>& point) const;

    /**
     * @brief Returns a formatted string representation of the ray.
     * @return A formatted string representation of the ray.
     */
    std::string toString() const;
};
}

#endif //UMBRAENGINE_RAY_H
