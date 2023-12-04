#include <iostream>xx
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"

int main(int argc, char* argv[])
{
	std::cout << "Ken ONeal - Computer Graphics";


	// creates and initializes renderer
	Random r;
	// have to cast it to static or it dont work
	r.seedRandom(static_cast<unsigned int>(time(nullptr)));

	Renderer renderer;
	renderer.Initialize(); 
	renderer.CreateWindow("Ray Tracer", 400, 300); 

	Canvas canvas(400, 300, renderer);

	float aspectRatio = canvas.GetSize().x / static_cast<float>(canvas.GetSize().y);
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

	//Color::color3_t t = { 1, 1, 1 };
	//Color::color3_t b = { 0, 0, 0 };

	Scene scene(20); // sky color could be set with the top and bottom color
	scene.SetCamera(camera);

	// create material
	//auto material = std::make_shared<Lambertian>(Color::color3_t{ 1, 0, 0 });
	auto lambertian = std::make_shared<Lambertian>(Color::color3_t{ 0, 0, 1 });
	auto metal = std::make_shared<Metal>(Color::color3_t{ 1, 1, 1 }, 0.0f);

	// create objects -> add to scene
	for (int i = 0; i < 10; i++)
	{
		// <use rand() and %to randomly pick the material>
		std::shared_ptr<Material> material = (std::rand() % 2 == 0) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);

		//auto sphere = <create the sphere with the material>;
		auto sphere = std::make_unique<Sphere>(
			glm::vec3{ r.random(-5, 5), r.random(-5, 5), r.random(-10, -3) },
			r.random(0.5, 0.8),
			material
		);

		scene.AddObject(std::move(sphere));
	}

	/*
	// create objects -> add to scene
	auto sphere = std::make_unique<Sphere>(glm::vec3{ 0, 0, -1 }, 0.5f, material);
	scene.AddObject(std::move(sphere));

	for (int i = 0; i < 8; ++i) {
		// makes Lambertian material with random colors
		auto randomColor = Color::color3_t{ r.random01(), r.random01(), r.random01() };
		auto randomMaterial = std::make_shared<Lambertian>(randomColor);

		// makes sphere with the Lambertian material, random positions, and random radius
		auto randomSphere = std::make_unique<Sphere>(
			glm::vec3{ r.random(-5, 5), r.random(-5, 5), r.random(-10, -5) },
			r.random(0.5, 0.8),
			randomMaterial
		);

		scene.AddObject(std::move(randomSphere));
	}
	*/

	canvas.Clear({ 0, 0, 0, 1 }); 
	scene.Render(canvas, 50); 
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

		/*
		canvas.Clear({0, 0, 0, 1});
		
		for (int i = 0; i < 1000; i++) 
		{
			canvas.DrawPoint({ r.random(0, 400), r.random(0, 300) }, { r.random01(), r.random01(), r.random01(), 1 }); 
		}
		canvas.Update(); 

		renderer.PresentCanvas(canvas);	
		*/	
	}

	renderer.Shutdown(); 

	return 0;
}