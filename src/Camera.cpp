#include "Camera.hpp"

cpp_renderer::Camera::Camera(float fov, int width, int height)
{
    width_ = width;
    height_ = height;
    perspective_coef_ = tan(fov);
    calculateTransformMatrix();
}

// TODO(me): replace with proper matrix once i can understand it
Eigen::Vector3f cpp_renderer::Camera::transform_naive(const Eigen::Vector3f &point) const
{
    Eigen::Vector4f homogenous_point;
    homogenous_point << point, 1;
    homogenous_point = transform_matrix_ * homogenous_point;
    return homogenous_point.head<3>() / homogenous_point.w();
}

Eigen::Vector3f cpp_renderer::Camera::transform(const Eigen::Vector3f &point) const
{
    return transform_naive(point);
}

void cpp_renderer::Camera::calculateTransformMatrix()
{
    Eigen::Matrix4f projection_matrix, screen_matrix;
    projection_matrix << 1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, perspective_coef_, 0;

    screen_matrix << width_, 0, 0, width_ / 2,
        0, height_, 0, height_ / 2,
        0, 0, 1, 0,
        0, 0, 0, 1;

    transform_matrix_ = screen_matrix * projection_matrix;
}
