#pragma once
#include <Eigen/Dense>
#include <array>
#include <optional>

namespace cpp_renderer {
struct Triangle {
public:
  using Vector2 = Eigen::Vector2f;
  using Vector3 = Eigen::Vector3f;

  Vector3 &operator[](int point_idx);
  const Vector3 &operator[](int point_idx) const;
  Vector3 GetSurfacePoint(const Vector2 &uv) const;
  std::optional<Vector2> getUV(size_t x, size_t y) const;

  std::array<Vector3, 3> points;
};
} // namespace cpp_renderer
