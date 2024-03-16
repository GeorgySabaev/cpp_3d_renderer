#include "Triangle.hpp"

namespace cpp_renderer {
Triangle::Vector3 Triangle::GetSurfacePoint(const Vector2 &uv) const {
  auto pivot = points[0];
  Eigen::Matrix<float, 3, 2> uv_space;
  uv_space.col(0) = points[1] - pivot;
  uv_space.col(1) = points[2] - pivot;

  return (uv_space * uv) + pivot;
}
} // namespace cpp_renderer
