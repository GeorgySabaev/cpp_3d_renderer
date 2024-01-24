#pragma once
#include "Triangle.hpp"

namespace cpp_renderer
{
    struct ShapeBuilder
    {
    public:
        ShapeBuilder &addPlane(Eigen::Vector3f position, Eigen::Matrix3f orientation);
        ShapeBuilder &addCube(Eigen::Vector3f position, Eigen::Matrix3f orientation);
        std::vector<cpp_renderer::Triangle> build() const;

    protected:
        std::vector<cpp_renderer::Triangle> polygons_;
    };
}