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