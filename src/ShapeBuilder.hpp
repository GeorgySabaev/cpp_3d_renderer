#pragma once
#include "Triangle.hpp"

namespace cpp_renderer {
class ShapeBuilder {
public:
  using Vector3 = Eigen::Vector3f;
  using Matrix3x3 = Eigen::Matrix3f;

  ShapeBuilder &addPlane(Vector3 position, Matrix3x3 orientation);
  ShapeBuilder &addCube(Vector3 position, Matrix3x3 orientation);
  std::vector<cpp_renderer::Triangle> build() const;

protected:
  std::vector<cpp_renderer::Triangle> polygons_;
};
} // namespace cpp_renderer
