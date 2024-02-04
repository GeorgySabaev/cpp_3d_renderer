#pragma once
#include <Eigen/Dense>
#include <array>

namespace cpp_renderer
{
    struct Triangle
    {
    public:
        Eigen::Vector3f GetSurfacePoint(const Eigen::Vector2f &uv) const;

        std::array<Eigen::Vector3f, 3> points;
    };
}