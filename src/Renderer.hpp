#pragma once
#include "RGBA32Image.hpp"
#include "Triangle.hpp"
#include "Camera.hpp"

namespace cpp_renderer
{
    class Renderer
    {
    public:
        RGBA32Image render(const std::vector<Triangle> &polygons, unsigned int width, unsigned int height, const Camera &camera) const;
    };
}