#include "DisplayUtils.hpp"
#include <utility>
#include "LinAlg.hpp"
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
    auto pivot = triangle.points[0].strip_z();
    auto b = triangle.points[1].strip_z() - pivot;
    auto c = triangle.points[2].strip_z() - pivot;
    auto l_perpendicular = Vector3(-b.y(), b.x(), 0);
    return LinAlg::dot(b, c) > 0;
}

bool cpp_renderer::DisplayUtils::checkIfInTriangle(unsigned int x, unsigned int y, Triangle triangle)
{
    assert(checkIfVisible(triangle));
    for (size_t i = 0; i < 3; i++)
    {
        auto pivot = triangle.points[i].strip_z();
        auto point = Vector3(x, y, 0) - pivot;
        auto side = triangle.points[(i + 1) % 3].strip_z() - pivot;
        auto l_perpendicular = Vector3(-side.y(), side.x(), 0);
        if (LinAlg::dot(point, l_perpendicular) <= 0)
        {
            return false;
        }
    }
    return true;
}
