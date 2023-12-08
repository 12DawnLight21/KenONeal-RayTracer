#include "Plane.h"
#include "MathUtils.h"

bool Plane::Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit)
{
    // check dot product of ray direction and plane normal, if result is 0 then ray direction if parallel to plane
    // the dot product is 0 if the two vectors are perpendicular (90 degrees)
    MathUtils mut;

    float denominator = dot(ray.direction, m_normal);
    if (mut.approximately(denominator, 0))
    {
        return false; // ray direction and plane parallel, no intersection
    }

    // get t (distance) along ray direction to hit point
    float t = glm::dot(m_center - ray.origin, m_normal) / denominator;
    if (t < 0)
    {
        return false; // plane behind ray's origin, no intersection
    }

    // check if t is outside min and max distance
    if (t > minDistance && t < maxDistance) //<check if t is outside the min and max distance <= || >= >
    {
        // set raycast hit 
        raycastHit.distance = t; //<set distance>;
        raycastHit.point = ray.At(t); //<set point using At()>;
        raycastHit.normal = glm::normalize(m_normal); //<set normal from plane normal>;
        raycastHit.material = m_material.get(); //<set mateterial>;

        return true;
    }

    return false;
}