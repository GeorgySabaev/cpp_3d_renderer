#pragma once
#include "IntRect.hpp"
#include "Triangle.hpp"

namespace cpp_renderer
{
    class DisplayUtils
    {
        public:
        static IntRect getBounds(const Triangle &polygon);

        static bool checkIfVisible(Triangle triangle);

        static bool checkIfVisible(unsigned int x, unsigned int y, Triangle triangle);
        static bool checkIfInTriangle(unsigned int x, unsigned int y, Triangle triangle);
    };
}