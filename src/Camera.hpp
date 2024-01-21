#pragma once
#include <Eigen/Dense>

namespace cpp_renderer
{
    class Camera
    {
    public:
        explicit Camera(float fov, int width, int height);

        Eigen::Vector3f transform_naive(const Eigen::Vector3f &point) const;

        Eigen::Vector3f transform(const Eigen::Vector3f &point) const;

    private:
        void calculateTransformMatrix();
        int width_;
        int height_;
        float perspective_coef_;
        Eigen::Matrix4f transform_matrix_;
    };
}