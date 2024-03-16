#pragma once
#include "RGBA32Image.hpp"
#include "Triangle.hpp"
#include "Camera.hpp"
#include "Buffer2d.hpp"
#include <Eigen/Dense>

namespace cpp_renderer
{
    class Renderer
    {
    public:
        RGBA32Image render(const std::vector<Triangle> &polygons, const Camera &camera);

    private:
        void setResolution(unsigned int width, unsigned int height);

        Buffer2d<float> depth_buffer_;
        Buffer2d<Eigen::Vector2f> uv_buffer_;
        Buffer2d<size_t> poly_id_buffer_;
    };
}