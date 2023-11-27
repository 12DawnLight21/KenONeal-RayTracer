#include "Renderer.h"

bool Renderer::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void Renderer::Shutdown()
{
	if (m_window != NULL)
	{
		SDL_DestroyWindow(m_window);
	}

	if (m_renderer != NULL)
	{
		SDL_DestroyRenderer(m_renderer);
	}
}

bool Renderer::CreateWindow(const std::string& title, int width, int height)
{
	// creates the window
	m_window = SDL_CreateWindow(title.c_str(), 100, 100, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (!m_window)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}

	// creates the renderer
	//m_renderer = //create sdl renderer
	m_renderer = SDL_CreateRenderer(m_window, -1, 0); // not sure what to do for the index , 0 could be SDL_RendererFlags
	if (!m_renderer)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}