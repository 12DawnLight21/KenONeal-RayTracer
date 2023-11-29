#include "Camera.h"
#include "MathUtils.h"

void Camera::LookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up)
{
	MathUtils mut;
	m_eye = eye;
	// set the camera axis vectors (forward, right, up)
	// forward vector (eye <- target)
	m_forward = glm::normalize(eye - target);
		// use cross product to create vectors
		// right = up x forward 
	m_right = glm::normalize(mut.cross(up, m_forward));
		// up = forward x right
	m_up = mut.cross(m_forward, m_right);

	CalculateViewPlane();
}

void Camera::CalculateViewPlane()
{
	// convert fov angle (degrees) to radians
	float theta = glm::radians(m_fov);

	// calculate the width / height of the view plane
	float halfHeight = tan(theta * 0.5f);
	float height = halfHeight * 2; // <twice the size of half height>;
	float width = height * m_aspectRatio; // <height * aspectRatio>;

	// calculate horizontal vector (right vector * width)
	m_horizontal = m_right * width;//<right * width>
		// calculate vertical vector (up vector * height)
	m_vertical = m_up * height; // <up * height>
		// calculate lower left location (origin)
		m_lowerLeft = m_eye - (m_horizontal * 0.5f) - (m_vertical * 0.5f) - m_forward; // m_eye - (<half horizontal>) - (<half vertical>) - m_forward;
}

ray_t Camera::GetRay(const glm::vec2& point) const
{
	ray_t ray;
	// the ray origin is the camera eye
	//<set ray origin>
		ray.origin = m_eye;

		// calculate direction from point
		ray.direction = m_lowerLeft + (m_horizontal * point.x) + (m_vertical * point.y) - m_eye; //<lower left + (horizontal * point x) + (vertical * point.y) - eye>

		return ray;
}