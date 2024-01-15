#pragma once
#include "RGBA32Image.hpp"
#include "Triangle.hpp"

namespace my_tmp{ // TODO(me): find a place for all this once you get the other classes
    struct Bounds{
        unsigned int left;
        unsigned int right;
        unsigned int up;
        unsigned int down;
    };

    inline Bounds getBounds(const cpp_renderer::Triangle &polygon)
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
        Bounds bounds;
        bounds.left = floorf(min_x);
        bounds.right = ceilf(max_x);
        bounds.up = floorf(min_y);
        bounds.down = ceilf(max_y);

        return bounds;
    }

    inline bool checkIfInTriangle(unsigned int x, unsigned int y){
        return false;
    }
}

namespace cpp_renderer
{
    class Renderer
    {
    public:
        RGBA32Image render(const std::vector<Triangle> &polygons, unsigned int width, unsigned int height) const;
    private:
        std::vector<std::vector<float>> depth_buffer_;
    };
}