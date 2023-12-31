#include "Scene.h"
#include "Canvas.h"
#include "Color.h"
#include "MathUtils.h"
#include "Plane.h"
#include "Sphere.h"
#include "Mesh.h"
#include <iomanip>

void Scene::Render(Canvas& canvas, int numSamples, int depth)
{
    Random rand;
	// cast ray for each point (pixel) on the canvas
	for (int y = 0; y < canvas.GetSize().y; y++)
	{
		for (int x = 0; x < canvas.GetSize().x; x++)
		{
            // create vec2 pixel from canvas x,y
            glm::vec2 pixel = glm::vec2{ x, y }; 

            // set initial color
            Color::color3_t color{ 0 }; 
            // cast a ray for each sample, accumulate color value for each sample
            // each ray will have a random offset
            for (int i = 0; i < numSamples; i++) //<iterate number of samples>
            {
                // get normalized (0 - 1) point coordinates from pixel
                // add random x and y offset (0-1) to each pixel
                //glm::vec2 point = (pixel + <add vec2 of random01>) / canvas.GetSize();
                glm::vec2 point = (pixel + glm::vec2{rand.random01(), rand.random01()}) / canvas.GetSize(); 
                // flip y
                point.y = 1.0f - point.y;

                // create ray from camera
                ray_t ray = m_camera->GetRay(point); 

                // cast ray into scene
                // add color value from trace
                raycastHit_t raycastHit; 
                color += Trace(ray, 0, 100, raycastHit, depth); 
            }

            std::cout << std::setprecision(2) << std::setw(5) << ((y / (float)canvas.GetSize().y) * 100) << "%\n";

            // draw color to canvas point (pixel)
            // get average color (average = (color + color + color) / number of samples)
            color /= numSamples; //<divide color by number of samples>
            canvas.DrawPoint(pixel, Color::color4_t(color, 1));
		}
	}
}

Color::color3_t Scene::Trace(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit, int depth)
{
    MathUtils mut;
    bool rayHit = false;
    float closestDistance = maxDistance;

    // check if scene objects are hit by the ray
    for (auto& object : m_objects)
    {
        // when checking objects don't include objects farther than closest hit (starts at max distance)
        if (object->Hit(ray, minDistance, closestDistance, raycastHit))
        {
            rayHit = true;
            // set closest distance to the raycast hit distance (only hit objects closer than closest distance)
            closestDistance = raycastHit.distance;
        }
    }

    //// if ray hit object, scatter (bounce) ray and check for next hit
    //if (rayHit)
    //{
    //    ray_t scattered;
    //    Color::color3_t color;

    //    // check if maximum depth (number of bounces) is reached, get color from material and scattered ray
    //    if (depth > 0 && raycastHit.material->Scatter(ray, raycastHit, color, scattered))
    //    {
    //        // recursive function, call self and modulate (multiply) colors of depth bounces
    //        return color * Trace(scattered, minDistance, maxDistance, raycastHit, depth - 1);
    //    }
    //    else
    //    {
    //        // reached maximum depth of bounces (color is black)
    //        return Color::color3_t{ 0, 0, 0 };
    //    }

    //}

    // if ray hit object, scatter (bounce) ray and check for next hit
    if (rayHit)
    {
        ray_t scattered;
        Color::color3_t color;

        // check if maximum depth (number of bounces) is reached, get color from material and scattered ray
        if (depth > 0 && raycastHit.material->Scatter(ray, raycastHit, color, scattered))
        {
            // recursive function, call self and modulate colors of depth bounces
            return color * Trace(scattered, minDistance, maxDistance, raycastHit, depth - 1);
        }
        else
        {
            // reached maximum depth of bounces (get emissive color, will be black except for Emissive materials)
            return raycastHit.material->GetEmissive();
        }
    }


    // if ray not hit, return scene sky color
    glm::vec3 direction = glm::normalize(ray.direction);
    float t = (direction.y + 1) * 0.5f; // direction.y (-1 <-> 1) => (0 <-> 1)
    Color::color3_t color = mut.lerp(m_bottomColor, m_topColor, t);

    return color;
}