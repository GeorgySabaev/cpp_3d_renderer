#pragma once
#include <Eigen/Dense>
#include <array>
#include <optional>

namespace cpp_renderer {
struct Triangle {
  using Vector2 = Eigen::Vector2f;
  using Vector3 = Eigen::Vector3f;
  using Matrix2x2 = Eigen::Matrix2f;
  using Matrix3x2 = Eigen::Matrix<float, 3, 2>;

  Vector3 &operator[](int point_idx);
  const Vector3 &operator[](int point_idx) const;
  Vector3 getPointByUv(const Vector2 &uv) const;
  std::optional<Vector2> getUVCoordinates(size_t x, size_t y) const;
  Matrix2x2 getUVBasisScreenSpace() const;
  Matrix3x2 getUVBasis() const;

  std::array<Vector3, 3> points;
};
} // namespace cpp_renderer
