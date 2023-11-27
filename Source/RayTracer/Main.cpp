#include <iostream>
#include "Renderer.h"

int main(int argc, char* argv[])
{
	std::cout << "Hello World!";

	// creates and initializes renderer
	Renderer rend;
	rend.Initialize();
	rend.CreateWindow("Ray Tracer", 400, 300);

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
	}

	rend.Shutdown();

	return 0;
}