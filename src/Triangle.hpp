#pragma once
#include <Eigen/Dense>
#include <array>
#include <optional>

namespace cpp_renderer {
struct Triangle {
public:
  using Vector2 = Eigen::Vector2f;
  using Vector3 = Eigen::Vector3f;
  using Matrix2 = Eigen::Matrix2f;

  Vector3 &operator[](int point_idx);
  const Vector3 &operator[](int point_idx) const;
  Vector3 GetSurfacePoint(const Vector2 &uv) const;
  std::optional<Vector2> getUVCoordinates(size_t x, size_t y) const;
  Matrix2 getUVBasis() const;

  std::array<Vector3, 3> points;
};
} // namespace cpp_renderer
