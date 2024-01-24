#include "Camera.hpp"

cpp_renderer::Camera::Camera(float fov, int width, int height, float near_plane, float far_plane)
{
    width_ = width;
    height_ = height;
    perspective_coef_ = tan(fov);
    near_plane_ = near_plane;
    far_plane_ = far_plane;
    calculateTransformMatrix();
}

Eigen::Vector3f cpp_renderer::Camera::transform(const Eigen::Vector3f &point) const
{
    Eigen::Vector4f homogenous_point;
    homogenous_point << point, 1;
    homogenous_point = transform_matrix_ * homogenous_point;
    return homogenous_point.head<3>() / homogenous_point.w();
}

void cpp_renderer::Camera::calculateTransformMatrix()
{
    Eigen::Matrix4f projection_matrix, screen_matrix;
    projection_matrix << 1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, -(far_plane_ / (far_plane_ - near_plane_)), -(far_plane_ * near_plane_ / (far_plane_ - near_plane_)),
        0, 0, -perspective_coef_, 0;

    screen_matrix << height_, 0, 0, width_ / 2,
        0, -height_, 0, height_ / 2,
        0, 0, 1, 0,
        0, 0, 0, 1;

    transform_matrix_ = screen_matrix * projection_matrix;
}
