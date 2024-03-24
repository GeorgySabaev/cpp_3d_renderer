#pragma once
#include "Triangle.hpp"
#include <vector>

namespace cpp_renderer {
class Model {
public:
  Model(std::string path);

  std::vector<Triangle> polygons;
};
} // namespace cpp_renderer
