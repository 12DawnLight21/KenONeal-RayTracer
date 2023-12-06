#include <iostream>xx
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"

int main(int argc, char* argv[])
{
	std::cout << "Ken ONeal - Computer Graphics";


	// creates and initializes renderer
	Random rand;
	// have to cast it to static or it dont work
	rand.seedRandom(static_cast<unsigned int>(time(nullptr)));

	Renderer renderer;
	renderer.Initialize(); 
	renderer.CreateWindow("Ray Tracer", 400, 300); 

	Canvas canvas(400, 300, renderer);

	float aspectRatio = canvas.GetSize().x / static_cast<float>(canvas.GetSize().y);
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 1, 10 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);

	
	Scene scene(8, glm::vec3{ 1.0f }, glm::vec3{ 0.5f, 0.7f, 1.0f });
	scene.SetCamera(camera);

	// create material
	auto material = std::make_shared<Lambertian>(Color::color3_t{ 0, 1, 0 });
	auto lambertian = std::make_shared<Lambertian>(Color::color3_t{ 0, 0, 1 });
	auto metal = std::make_shared<Metal>(Color::color3_t{ 1, 1, 1 }, 0.0f);

	// create objects -> add to scene

	// Triangle
	auto triangleMaterial = std::make_shared<Lambertian>(Color::color3_t{ 1.0f, 0.0f, 0.0f }); // Red Lambertian material
	auto triangle = std::make_unique<Triangle>(
	    glm::vec3{ 0, 1, 0 }, 
	    glm::vec3{ -1, 0, 0 }, 
	    glm::vec3{ 1, 0, 0 },
	    triangleMaterial
	);
	scene.AddObject(std::move(triangle));
	/*
	for (int x = -10; x < 10; x++)
	{
		for (int z = -10; z < 10; z++)
		{
			std::shared_ptr<Material> material;

			// create random material
			float r = rand.random01();
			if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ rand.random(0, 360), 1.0f, 1.0f }));
			else if (r < 0.6f)	material = std::make_shared<Metal>(Color::color3_t{ rand.random(0.5f, 1.0f) }, rand.random(0, 0.5f));
			else if (r < 0.9f)	material = std::make_shared<Dielectric>(Color::color3_t{ 1.0f }, rand.random(1.1f, 2));
			else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ rand.random(0, 360), 1.0f, 1.0f }), 5.0f);

			// set random sphere radius
			float radius = rand.random(0.2f, 0.3f);
			// create sphere using random radius and material
			auto sphere = std::make_unique<Sphere>(glm::vec3{ x + rand.random(-0.5f, 0.5f), radius, z + rand.random(-0.5f, 0.5f) }, radius, material);
			// add sphere to the scene
			scene.AddObject(std::move(sphere));
		}
	}
	*/

	//auto material = std::make_shared<Lambertian>(Color::color3_t{ 0.2f });
	auto plane = std::make_unique<Plane>(glm::vec3{ 0, -1, 0 }, glm::vec3{ 0, 1, 0 }, material); 
	scene.AddObject(std::move(plane)); 

	canvas.Clear({ 0, 0, 0, 1 }); 
	scene.Render(canvas, 10); 
	canvas.Update(); 

	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		renderer.PresentCanvas(canvas); 

	}

	renderer.Shutdown(); 

	return 0;
}