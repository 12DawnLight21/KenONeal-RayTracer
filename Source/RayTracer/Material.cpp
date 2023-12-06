#include "Material.h"
#include "MathUtils.h"

bool Lambertian::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, Color::color3_t& color, ray_t& scattered) const
{
	Random rand;

	// scatters the lambertain reflection in a random direction
	glm::vec3 target = raycastHit.point + raycastHit.normal + rand.randomInUnitSphere(); 
	glm::vec3 direction = glm::normalize(target - raycastHit.point); 
	scattered = { raycastHit.point, direction }; 
	color = m_albedo; 

	return true;
}

bool Metal::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, glm::vec3& color, ray_t& scattered) const
{
	MathUtils mut;
	Random rand;

	glm::vec3 reflected = mut.reflect(glm::normalize(ray.direction), raycastHit.normal);
	scattered = { raycastHit.point, reflected + (rand.randomInUnitSphere() * m_fuzz) };
	color = m_albedo; 

	return (glm::dot(scattered.direction, raycastHit.normal) > 0);
}

bool Dielectric::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, glm::vec3& color, ray_t& scattered) const
{
    MathUtils mut;
    Random rand;

    glm::vec3 reflected = reflect(glm::normalize(ray.direction), raycastHit.normal);
    glm::vec3 refracted;

    glm::vec3 outNormal;
    float ni_over_nt;
    float cosine;

    // ray hits inside of surface ( ray -> | -> normal )
    // ray is going out of object (ray direction is facing in the same direction of the surface normal)
    if (glm::dot(ray.direction, raycastHit.normal) > 0)
    {
        outNormal = -raycastHit.normal;
        ni_over_nt = m_index;
        cosine = m_index * glm::dot(ray.direction, raycastHit.normal) / ray.direction.length();
    }
    else
    {
        // ray hits outside of surface ( ray -> | <- normal )
        // ray is going into object (ray direction is facing in the opposite direction of the surface norma)
        outNormal = raycastHit.normal;
        ni_over_nt = 1.0f / m_index;
        cosine = -glm::dot(ray.direction, raycastHit.normal) / ray.direction.length();
    }

    // set the probability of the ray being reflected or refracted
    float reflectProbability = 1.0f;
    if (mut.refract(ray.direction, outNormal, ni_over_nt, refracted))
    {
        // use schlick and cosine (angle) to determine if ray is reflected or refracted
        reflectProbability = mut.schlick(cosine, m_index);
    }

    // create reflected or refracted ray
    scattered = (rand.random01() < reflectProbability) ? ray_t{ raycastHit.point, reflected } : ray_t{ raycastHit.point, refracted };
    color = m_albedo;

    return true;
}