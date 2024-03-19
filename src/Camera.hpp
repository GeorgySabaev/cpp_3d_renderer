#pragma once
#include <Eigen/Dense>

namespace cpp_renderer {
class Camera {
public:
  Camera(float fov, size_t width, size_t height, float near_plane,
         float far_plane);

  int getWidth() const;
  int getHeight() const;

  void resizeScreen(size_t width, size_t height);
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
} // namespace cpp_renderer
