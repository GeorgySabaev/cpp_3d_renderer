#pragma once
#include "RGBA32Color.hpp"
#include <vector>

namespace cpp_renderer {
class RGBA32Image {
public:
  RGBA32Image() = default;
  RGBA32Image(size_t width, size_t height,
              RGBA32Color background_color = {});
  RGBA32Color getPixel(size_t x, size_t y) const;
  void setPixel(size_t x, size_t y, RGBA32Color color);
  const uint8_t *getRawData() const;
  size_t getWidth() const;
  size_t getHeight() const;
  void resize(size_t width, size_t height,
              RGBA32Color background_color);

private:
  std::vector<uint8_t> data_;
  size_t width_;
  size_t height_;
};
} // namespace cpp_renderer
