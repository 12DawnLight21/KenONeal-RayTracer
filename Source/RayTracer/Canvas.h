#pragma once
#include <vector>
#include "Color.h"

class Canvas
{
public:
    //Canvas(int width, int height, <const reference to Renderer(forward declaration)> renderer);
    Canvas(int width, int height, const class Renderer& renderer);
    ~Canvas();

    void Update();

    void Clear(const Color::color4_t& color);
    //void DrawPoint(<const reference to glm integer vector 2> point, const color4_t& color);
    void DrawPoint(const glm::ivec2& point, const Color::color4_t& color);

    //<return const reference of m_size> GetSize() const { return m_size; }
    glm::vec2 GetSize() const { return m_size; }

    //<allow Renderer to access Canvas private data>
    friend class Renderer;

private:
    //<SDL Texture pointer(forward declaration)> m_texture<default to nullptr>;
    struct SDL_Texture* m_texture{ nullptr };

    //<vector of rgba_t> m_buffer;
    std::vector<Color::rgba_t> m_buffer;

    //<glm integer vector2> m_size<default to 0>;
    glm::ivec2 m_size{ 0 };
};