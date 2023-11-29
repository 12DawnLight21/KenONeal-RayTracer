#pragma once
#include "Color.h"
#include "Ray.h"
#include "Camera.h"
#include <iostream>

class Scene
{
public:
	Scene() = default;
	Scene(const Color::color3_t& topColor, const Color::color3_t& bottomColor) :
		m_topColor{ topColor },
		m_bottomColor{ bottomColor }
	{}

	void Render(class Canvas& canvas);
	Color::color3_t Trace(const ray_t& ray);

	void SetCamera(std::shared_ptr<Camera> camera) { m_camera = camera; }

private:
	//<shared pointer of Camera> m_camera;
	std::shared_ptr<Camera> m_camera;

	Color::color3_t m_topColor{ 0 };
	Color::color3_t m_bottomColor{ 1 };
};