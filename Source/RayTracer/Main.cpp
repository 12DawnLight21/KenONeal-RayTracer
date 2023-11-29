#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Camera.h"
#include "Scene.h"

int main(int argc, char* argv[])
{
	std::cout << "Hello World!";


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

	Scene scene; // sky color could be set with the top and bottom color
	scene.SetCamera(camera);

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


		canvas.Clear({ 0, 0, 0, 1 }); 
		scene.Render(canvas); 
		canvas.Update(); 

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