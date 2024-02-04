#pragma once
#include <Eigen/Dense>

namespace cpp_renderer
{
    class Camera
    {
    public:
        explicit Camera(float fov, int width, int height, float near_plane, float far_plane);

        int getWidth() const;
        int getHeight() const;

        Eigen::Vector3f transform(const Eigen::Vector3f &point) const;

    private:
        void calculateTransformMatrix();
        int width_;
        int height_;
        float near_plane_;
        float far_plane_;
        float perspective_coef_;
        Eigen::Matrix4f transform_matrix_;
    };
}