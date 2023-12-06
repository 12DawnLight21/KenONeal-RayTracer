#pragma once
#include <glm/gtx/color_space.hpp>

class Color
{
public:
    // aliases for color representation
	using color3_t = glm::vec3;
	using color4_t = glm::vec4;
	using rgba_t = uint32_t;

public:
	// converts int colors into float colors
    inline static color4_t RGBAToColor(const rgba_t& rgba) 
    {
        float red = static_cast<float>((rgba >> 24) & 0xFF) / 255.0f;
        float green = static_cast<float>((rgba >> 16) & 0xFF) / 255.0f;
        float blue = static_cast<float>((rgba >> 8) & 0xFF) / 255.0f;
        float alpha = static_cast<float>(rgba & 0xFF) / 255.0f;

        return color4_t(red, green, blue, alpha);
    }

    //converts float colors into int colors
    inline static rgba_t ColorToRGBA(const color4_t& color)  
    {
        uint32_t red = static_cast<uint32_t>(color.r * 255.0f) & 0xFF;
        uint32_t green = static_cast<uint32_t>(color.g * 255.0f) & 0xFF;
        uint32_t blue = static_cast<uint32_t>(color.b * 255.0f) & 0xFF;
        uint32_t alpha = static_cast<uint32_t>(color.a * 255.0f) & 0xFF;

        return (red << 24) | (green << 16) | (blue << 8) | alpha;
    }
};