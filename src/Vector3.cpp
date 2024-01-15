#include "Vector3.hpp"
#include <cassert>

float &cpp_renderer::Vector3::operator[](size_t i)
{
    assert(i < 3);
    return reinterpret_cast<float*>(this)[i];
}

float cpp_renderer::Vector3::operator[](size_t i) const
{
    assert(i < 3);
    return reinterpret_cast<const float*>(this)[i];
}
