#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"

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

		for (int i = 0; i < 1000; i++) 
		{
			canvas.DrawPoint({ r.random(0, 400), r.random(0, 300) }, { r.random01(), r.random01(), r.random01(), 1 }); 
		}
		canvas.Update(); 

		renderer.PresentCanvas(canvas);		
	}

	renderer.Shutdown(); 

	return 0;
}