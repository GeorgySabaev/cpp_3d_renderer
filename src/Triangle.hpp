#pragma once
#include <Eigen/Dense>

namespace cpp_renderer
{
    struct Triangle
    {
    public:
        Eigen::Vector3f GetSurfacePoint(const Eigen::Vector2f &uv) const;

        Eigen::Vector3f points[3];
    };
}