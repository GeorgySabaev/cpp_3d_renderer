#include "Triangle.hpp"

namespace cpp_renderer {
Triangle::Vector3 &Triangle::operator[](int point_idx) {
  return points[point_idx];
}

const Triangle::Vector3 &Triangle::operator[](int point_idx) const {
  return points[point_idx];
}

Triangle::Vector3 Triangle::getPointByUv(const Vector2 &uv) const {
  auto pivot = points[0];
  auto uv_basis = getUVBasis();

  return (uv_basis * uv) + pivot;
}

std::optional<Triangle::Vector2> Triangle::getUVCoordinates(size_t x,
                                                            size_t y) const {
  auto pivot = points[0].head<2>();
  auto point = (Vector2(x, y) - pivot).eval();
  auto uv_basis = getUVBasisScreenSpace();
  auto uv = uv_basis.colPivHouseholderQr().solve(point);
  if (uv.x() >= 0 && uv.y() >= 0 && uv.x() + uv.y() <= 1) {
    return uv;
  }

  return std::nullopt;
}
Triangle::Matrix2x2 Triangle::getUVBasisScreenSpace() const {
  auto pivot = points[0].head<2>();
  Matrix2x2 uv_basis;
  uv_basis.col(0) = points[1].head<2>() - pivot;
  uv_basis.col(1) = points[2].head<2>() - pivot;
  return uv_basis;
}
Triangle::Matrix3x2 Triangle::getUVBasis() const {
  auto pivot = points[0];
  Matrix3x2 uv_basis;
  uv_basis.col(0) = points[1] - pivot;
  uv_basis.col(1) = points[2] - pivot;
  return uv_basis;
}
} // namespace cpp_renderer
