#include "ShapeBuilder.hpp"
#include <numbers>
namespace cpp_renderer {
ShapeBuilder &ShapeBuilder::addPlane(Vector3 position, Matrix3x3 orientation) {
  Vector3 bottom_side = orientation.col(0);
  Vector3 left_side = orientation.col(1);
  if (bottom_side.cross(left_side).dot(orientation.col(2)) < 0) {
    std::swap(bottom_side, left_side);
  }
  polygons_.push_back({position, position + left_side, position + bottom_side});
  polygons_.push_back({position + left_side + bottom_side,
                       position + bottom_side, position + left_side});
  return *this;
}

ShapeBuilder &ShapeBuilder::addCube(Vector3 position, Matrix3x3 orientation) {
  using Rotation = Eigen::AngleAxisf;
  auto &pi = std::numbers::pi;

  auto center_offset = orientation.rowwise().sum() / 2.;
  auto center = position + center_offset;
  for (size_t i = 0; i < 4; i++) {
    auto rotation = Rotation(0.5 * pi * i, orientation.col(0));
    addPlane(center - rotation * center_offset, rotation * orientation);
  }
  for (size_t i = 0; i < 2; i++) {
    auto rotation = Rotation(0.5 * pi + pi * i, orientation.col(1));
    addPlane(center - rotation * center_offset, rotation * orientation);
  }
  return *this;
}

std::vector<Triangle> ShapeBuilder::build() const { return polygons_; }
} // namespace cpp_renderer
