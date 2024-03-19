#pragma once
#include "RGBA32Color.hpp"

namespace cpp_renderer {
class RGBA32Colors {
public:
  static constexpr RGBA32Color BLACK{0x00, 0x00, 0x00, 0xFF};
  static constexpr RGBA32Color WHITE{0xFF, 0xFF, 0xFF, 0xFF};
  static constexpr RGBA32Color MAGENTA{0xFF, 0x00, 0xFF, 0xFF};

  RGBA32Colors() = delete;
};
} // namespace cpp_renderer
