#include "Scene.h"
#include "Canvas.h"
#include "Color.h"
#include "MathUtils.h"

void Scene::Render(Canvas& canvas)
{
	// cast ray for each point (pixel) on the canvas
	for (int y = 0; y < canvas.GetSize().y; y++)
	{
		for (int x = 0; x < canvas.GetSize().x; x++)
		{
			// create vec2 pixel from canvas x,y
			glm::vec2 pixel(static_cast<float>(x), static_cast<float>(y)); //<create vec2 from canvas x, y>
				// get normalized (0 - 1) point coordinates from pixel
			glm::vec2 point = pixel / glm::vec2(canvas.GetSize());  // < divide pixel by canvas size to normalize(0 - 1)
				// flip y
				point.y = 1.0f - point.y;

			// create ray from camera
			//ray_t ray = <get ray from camera using point>
				ray_t ray = m_camera->GetRay(point);

				// cast ray into scene
				// set color value from trace
				Color::color3_t color = Trace(ray);

			// draw color to canvas point (pixel)
			canvas.DrawPoint(pixel, Color::color4_t(color, 1));
		}
	}
}

Color::color3_t Scene::Trace(const ray_t& ray)
{
	glm::vec3 direction = glm::normalize(ray.direction);

	// set scene sky color
	float t = (direction.y + 1) * 0.5f; // direction.y (-1 <-> 1) => (0 <-> 1)
	//Color::color3_t color = <lerp between bottom and top color using t>
	MathUtils mut;

	Color::color3_t color = mut.lerp(m_bottomColor, m_topColor, t); //glm::vec3(mut.lerp(direction.b, direction.t, t));

		return color;
}