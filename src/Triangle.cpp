#include "Triangle.hpp"

Eigen::Vector3f cpp_renderer::Triangle::GetSurfacePoint(const Eigen::Vector2f &uv) const
{
    auto pivot = points[0];
    Eigen::Matrix<float, 3, 2> uv_space;
    uv_space.col(0) = points[1] - pivot;
    uv_space.col(1) = points[2] - pivot;

    return (uv_space * uv) + pivot;
}