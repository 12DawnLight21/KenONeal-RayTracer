#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Mesh.h"

void InitScene01(Scene& scene, const Canvas& canvas);
void InitScene02(Scene& scene, const Canvas& canvas);
void InitScene03(Scene& scene, const Canvas& canvas);

int main(int argc, char* argv[])
{
	std::cout << "Ken ONeal - Computer Graphics";

	const int width = 400;
	const int height = 300;
	const int samples = 200;
	const int depth = 5;

	// creates and initializes renderer
	Random rand;
	// have to cast it to static or it dont work
	rand.seedRandom(static_cast<unsigned int>(time(nullptr)));

	Renderer renderer;
	renderer.Initialize(); 
	renderer.CreateWindow("Ray Tracer", width, height); 

	Canvas canvas(width, height, renderer);

	float aspectRatio = canvas.GetSize().x / static_cast<float>(canvas.GetSize().y);
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 1, 10 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);

	
	Scene scene(glm::vec3{ 1.0f }, glm::vec3{ 0.5f, 0.7f, 1.0f });
	//scene.SetCamera(camera);

	// initialize scene for rendering
	InitScene01(scene, canvas);

	canvas.Clear({ 0, 0, 0, 1 }); 
	scene.Render(canvas, samples, depth); 
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

void InitScene01(Scene& scene, const Canvas& canvas)
{
	Random rand;
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	// create objects -> add to scene
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

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(Color::color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));
}

void InitScene02(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(Color::color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));

	auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(Color::color3_t{ 0, 0, 1 }));
	mesh->Load("models/cube.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
	scene.AddObject(std::move(mesh));
}

void InitScene03(Scene& scene, const Canvas& canvas)
{
	Random rand;

	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 1, 10 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, .5, 0 }, 15.0f, aspectRatio);
	scene.SetCamera(camera);

	// mats
	auto light = std::make_shared<Emissive>(Color::color3_t{ 1.0f }, 5.0f);

	// walls n ceiling meshes
	auto ceilingMesh = std::make_unique<Mesh>(std::make_shared<Emissive>(Color::color3_t{ 0.5f }));
	ceilingMesh->Load("models/quad.obj", glm::vec3{ 0, 1, 0 }, glm::vec3{ 90, 0, 0 }, glm::vec3{ 2 }); // ceiling to top of box

	auto backWallMesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(Color::color3_t{ 1, 1, 1 }));
	backWallMesh->Load("models/quad.obj", glm::vec3{ 0, 0, -1 }, glm::vec3{ 0, 0, 90 }, glm::vec3{ 2 });

	auto leftWallMesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(Color::color3_t{ 1, 0, 0 }));
	leftWallMesh->Load("models/quad.obj", glm::vec3{ -1, 0, 0 }, glm::vec3{ 0, 90, 90 }, glm::vec3{ 2 }); // left wall on left side of box

	auto rightWallMesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(Color::color3_t{ 0, 1, 0 }));
	rightWallMesh->Load("models/quad.obj", glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, -90, -90 }, glm::vec3{ 2 }); // right wall on right side of box

	// floor n light source
	auto floor = std::make_unique<Mesh>(std::make_shared<Lambertian>(Color::color3_t{ 1, 1, 1 }));
	floor->Load("models/quad.obj", glm::vec3{ 0, -1, 0 }, glm::vec3{ -90, 0, 0 }, glm::vec3{ 2 });

	auto cube = std::make_unique<Mesh>(std::make_shared<Metal>(Color::color3_t{ 1.0f }, 1));
	cube->Load("models/cube.obj", glm::vec3{ 0.5f, 0, 0 }, glm::vec3{ 0, 45, 0 }, glm::vec3{ 0.5f }); 

	// set random sphere radius
	float radius = rand.random(0.2f, 0.3f);

	// create sphere using random radius and material
	auto sphere = std::make_unique<Sphere>(glm::vec3{ -0.5f,0,0 }, radius, std::make_shared<Metal>(Color::color3_t{ rand.random(0.5f, 1.0f) }, rand.random(0, 0.5f)));

	// Add Meshes to the Scene

	scene.AddObject(std::move(sphere));
	scene.AddObject(std::move(floor));
	scene.AddObject(std::move(ceilingMesh));
	scene.AddObject(std::move(backWallMesh));
	scene.AddObject(std::move(leftWallMesh));
	scene.AddObject(std::move(rightWallMesh));
	scene.AddObject(std::move(cube));
}