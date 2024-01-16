#include "Vector3.hpp"
#include <cassert>

cpp_renderer::Vector3::Vector3(float x, float y, float z)
{
    data_[0] = x;
    data_[1] = y;
    data_[2] = z;
}

float &cpp_renderer::Vector3::operator[](size_t i)
{
    assert(i < 3);
    return data_[i];
}

float cpp_renderer::Vector3::operator[](size_t i) const
{
    assert(i < 3);
    return data_[i];
}

float &cpp_renderer::Vector3::x()
{
    return data_[0];
}

float cpp_renderer::Vector3::x() const
{
    return data_[0];
}

float &cpp_renderer::Vector3::y()
{
    return data_[1];
}

float cpp_renderer::Vector3::y() const
{
    return data_[1];
}

float &cpp_renderer::Vector3::z()
{
    return data_[2];
}

float cpp_renderer::Vector3::z() const
{
    return data_[2];
}

cpp_renderer::Vector3 cpp_renderer::Vector3::strip_z() const
{
    return Vector3(this->x(), this->y(), 0);
}

cpp_renderer::Vector3 cpp_renderer::Vector3::operator+(const Vector3 &other) const
{
    return Vector3(other.x() + this->x(), other.y() + this->y(), other.z() + this->z());
}

cpp_renderer::Vector3 cpp_renderer::Vector3::operator-(const Vector3 &other) const
{
    return Vector3(this->x() - other.x(), this->y() - other.y(), this->z() - other.z());
}

cpp_renderer::Vector3 cpp_renderer::Vector3::operator-() const
{
    return Vector3(-this->x(), -this->y(), -this->z());
}