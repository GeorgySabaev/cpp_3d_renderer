#include "ShapeBuilder.hpp"
#include <numbers>

cpp_renderer::ShapeBuilder &cpp_renderer::ShapeBuilder::addPlane(Eigen::Vector3f position, Eigen::Matrix3f orientation)
{
    Eigen::Vector3f bottom_side = orientation.col(0);
    Eigen::Vector3f left_side = orientation.col(1);
    if (bottom_side.cross(left_side).dot(orientation.col(2)) < 0)
    {
        std::swap(bottom_side, left_side);
    }
    polygons_.push_back({position, position + left_side, position + bottom_side});
    polygons_.push_back({position + left_side + bottom_side, position + bottom_side, position + left_side});
    return *this;
}

cpp_renderer::ShapeBuilder &cpp_renderer::ShapeBuilder::addCube(Eigen::Vector3f position, Eigen::Matrix3f orientation)
{
    auto center_offset = orientation.rowwise().sum() / 2;
    auto center = position + center_offset;
    for (size_t i = 0; i < 4; i++)
    {
        auto rotation = Eigen::AngleAxisf(0.5 * std::numbers::pi * i, orientation.col(0));
        addPlane(center - rotation * center_offset, rotation * orientation);
    }
    for (size_t i = 0; i < 2; i++)
    {
        auto rotation = Eigen::AngleAxisf(0.5 * std::numbers::pi + std::numbers::pi * i, orientation.col(1));
        addPlane(center - rotation * center_offset, rotation * orientation);
    }
    return *this;
}

std::vector<cpp_renderer::Triangle> cpp_renderer::ShapeBuilder::build() const
{
    return polygons_;
}
