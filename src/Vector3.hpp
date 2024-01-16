#pragma once

namespace cpp_renderer
{
    struct Vector3
    {
    public:
        Vector3() = default;
        Vector3(float x, float y, float z);

        float &operator[](size_t i);
        float operator[](size_t i) const;
        float &x();
        float x() const;
        float &y();
        float y() const;
        float &z();
        float z() const;

        Vector3 strip_z() const;

        Vector3 operator+(const Vector3 &other) const;
        Vector3 operator-(const Vector3 &other) const;
        Vector3 operator-() const;

    private:
        float data_[3];
    };
}