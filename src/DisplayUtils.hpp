#pragma once
#include "IntRect.hpp"
#include "Triangle.hpp"
#include <optional>

namespace cpp_renderer
{
    class DisplayUtils
    {
        public:
        static IntRect getBounds(const Triangle &polygon);

        static bool checkIfVisible(Triangle triangle);
        
        static std::optional<Eigen::Vector2f> getUV(unsigned int x, unsigned int y, Triangle triangle);
    };
}