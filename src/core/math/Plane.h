//
// Created by Damon Tregear on 10/11/23.
//

#ifndef UMBRAENGINE_PLANE_H
#define UMBRAENGINE_PLANE_H

#include "Vector3.h"

/**
 * @struct Plane
 * @brief Representation of planes in 3D.
 *
 * @details A plane is a flat surface that extends infinitely in all directions.
 */

template <typename T>
struct Plane {
/**
 * @section Properties
 * @subsection Instance properties
 */

    /**
     * @property distance
     * @brief The distance from the origin to the plane along the plane's normal.
     */
    T distance;

    /**
     * @property normal
     * @brief The normal of the plane.
     */
    Vector3<T> normal;

/**
 * @section Constructors
 */

    /**
     * @brief Initializes a plane with the given normal and distance.
     * @param normal The normal of the plane.
     * @param distance The distance from the origin to the plane along the plane's normal.
     */
    Plane<T>(const Vector3<T>& normal, T distance);

    /**
     * @brief Initializes a plane with the given normal that passes through the given point.
     * @param normal The normal of the plane.
     * @param point The point that the plane passes through.
     */
    Plane<T>(const Vector3<T>& normal, const Vector3<T>& point);

    /**
     * @brief Initializes a plane with the given three points.
     * @param a The first point.
     * @param b The second point.
     * @param c The third point.
     *
     * @details The plane is constructed from the given points in a clockwise order.
     */
    Plane<T>(const Vector3<T>& a, const Vector3<T>& b, const Vector3<T>& c);

/**
 * @section Properties
 * @subsection Instance properties (read-only)
 */

    /**
     * @property flipped
     * @brief Returns a plane with the opposite normal and distance.
     */
    Plane<T> flipped() const;

/**
 * @section Methods
 * @subsection Public methods
 */

    /**
     * @brief Returns the closest point on the plane to the given point.
     * @param point The point to project onto the plane.
     * @return The closest point on the plane to the given point.
     */
    Vector3<T> ClosestPoint(const Vector3<T>& point) const;

    /**
     * @brief Returns this plane faced in the opposite direction.
     * @return This plane faced in the opposite direction.
     */
    Plane<T> Flip() const;

    /**
     * @brief Returns the signed distance from the plane to the given point.
     * @param point The point to find the signed distance to.
     * @return The signed distance from the plane to the given point.
     */
    T GetDistanceToPoint(const Vector3<T>& point) const;

    /**
     * @brief Checks if the given point is on the positive side of the plane.
     * @param point The point to check.
     * @return True if the given point is on the positive side of the plane, false otherwise.
     */
    bool GetSide(const Vector3<T>& point) const;

    /**
     * TODO: Implement Raycast function
     */

    /**
     * @brief Checks if the given two points are on the same side of the plane.
     * @param a The first point.
     * @param b The second point.
     * @return True if the given two points are on the same side of the plane, false otherwise.
     */
    bool SameSide(const Vector3<T>& a, const Vector3<T>& b) const;

    /**
     * @brief Sets this plane from the given three points.
     * @param a The first point.
     * @param b The second point.
     * @param c The third point.
     *
     * @details The plane is constructed from the given points in a clockwise order.
     */
    void SetPlane(const Vector3<T>& a, const Vector3<T>& b, const Vector3<T>& c);

    /**
     * @brief Sets this plane from the given normal and the given point on the plane.
     * @param normal The normal of the plane.
     * @param point The point on the plane.
     */
    void SetPlane(const Vector3<T>& normal, const Vector3<T>& point);

/**
 * @section Methods
 * @subsection Static methods
 */

    /**
     * @brief Returns a copy of the given plane that is translated by the given amount.
     * @param plane The plane to translate.
     * @param translation The amount to translate the plane by.
     * @return A copy of the given plane that is translated by the given amount.
     */
    static Plane<T> Translate(const Plane<T>& plane, const Vector3<T>& translation);
};

#endif //UMBRAENGINE_PLANE_H
