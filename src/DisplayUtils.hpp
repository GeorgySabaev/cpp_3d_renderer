#pragma once
#include "Rect.hpp"
#include "Triangle.hpp"
#include <optional>

namespace cpp_renderer {
class DisplayUtils {
public:
  static Rect<int> getBounds(const Triangle &polygon);

  static cpp_renderer::Rect<size_t> clipToScreen(cpp_renderer::Rect<int> bounds,
                                                 size_t width, size_t height);

  static bool checkIfVisible(Triangle triangle);

  static std::optional<Eigen::Vector2f> getUV(size_t x, size_t y,
                                              Triangle triangle);
};
} // namespace cpp_renderer
