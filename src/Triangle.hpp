#pragma once
#include <Eigen/Dense>
#include <array>

namespace cpp_renderer {
struct Triangle {
public:
  using Vector2 = Eigen::Vector2f;
  using Vector3 = Eigen::Vector3f;
  Vector3 GetSurfacePoint(const Vector2 &uv) const;

  std::array<Vector3, 3> points;
};
} // namespace cpp_renderer
