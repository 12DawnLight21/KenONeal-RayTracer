#pragma once
#include <iostream>
#include <SDL.h>

class Renderer
{
public:
	Renderer() = default;

	bool Initialize();
	void Shutdown();
	bool CreateWindow(const std::string& title, int width, int height);

private:
	// SDL_Window pointer = nullptr
	SDL_Renderer* m_renderer = nullptr;

	// SDL_Renderer pointer = nullptr
	SDL_Window* m_window = nullptr;
};