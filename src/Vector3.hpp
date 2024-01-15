#pragma once

namespace cpp_renderer
{
    struct Vector3{
    public:
        float x;
        float y;
        float z;
        float& operator[](size_t i);
        float operator[](size_t i) const;
    };
}