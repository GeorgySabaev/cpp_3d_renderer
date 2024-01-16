#include "LinAlg.hpp"

float cpp_renderer::LinAlg::dot(const Vector3 &a, const Vector3 &b)
{
    float sum = 0;
    for (size_t i = 0; i < 3; i++)
    {
        sum += a[i]*b[i];
    }
    return sum;
}