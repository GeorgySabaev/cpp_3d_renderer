#include "DisplayUtils.hpp"
#include <utility>
#include <cassert>

cpp_renderer::IntRect cpp_renderer::DisplayUtils::getBounds(const Triangle &polygon)
{
    float min_x;
    float max_x;
    float min_y;
    float max_y;
    min_x = max_x = polygon.points[0][0];
    min_y = max_y = polygon.points[0][1];
    for (auto point : polygon.points)
    {
        min_x = std::min(min_x, point[0]);
        min_y = std::min(min_y, point[1]);
        max_x = std::max(max_x, point[0]);
        max_y = std::max(max_y, point[1]);
    }
    IntRect bounds;
    bounds.left = floorf(min_x);
    bounds.right = ceilf(max_x);
    bounds.up = floorf(min_y);
    bounds.down = ceilf(max_y);

    return bounds;
}

bool cpp_renderer::DisplayUtils::checkIfVisible(Triangle triangle)
{
    auto pivot = triangle.points[0].head<2>();
    auto b = triangle.points[1].head<2>() - pivot;
    auto c = triangle.points[2].head<2>() - pivot;
    auto l_perpendicular = Eigen::Vector2f(-c.y(), c.x());
    return b.dot(l_perpendicular) > 0;
}


std::optional<Eigen::Vector2f> cpp_renderer::DisplayUtils::getUV(unsigned int x, unsigned int y, Triangle triangle)
{
    assert(checkIfVisible(triangle));

    auto pivot = triangle.points[0].head<2>();
    Eigen::Matrix2f uv_space;
    uv_space.col(0) = triangle.points[1].head<2>() - pivot;
    uv_space.col(1) = triangle.points[2].head<2>() - pivot;
    auto point = (Eigen::Vector2f(x, y) - pivot).eval();
    
    auto uv = uv_space.colPivHouseholderQr().solve(point);
    if(uv.x() >= 0 && uv.y() >= 0 && uv.x() + uv.y() <= 1){
        return uv;
    }
    return std::nullopt;
}

float cpp_renderer::DisplayUtils::getDepth(Eigen::Vector2f uv, Triangle triangle)
{   
    auto pivot = triangle.points[0];
    Eigen::Matrix<float, 3, 2> uv_space;
    uv_space.col(0) = triangle.points[1] - pivot;
    uv_space.col(1) = triangle.points[2] - pivot;
    
    return (uv_space*uv).z() + pivot.z();
}
