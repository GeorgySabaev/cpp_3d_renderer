#pragma once
#include "RGBA32Color.hpp"
#include <vector>

namespace cpp_renderer {
class RGBA32Image {
public:
  RGBA32Image() = default;
  RGBA32Image(unsigned int width, unsigned int height,
              RGBA32Color background_color = {});
  RGBA32Color getPixel(unsigned int x, unsigned int y) const;
  void setPixel(unsigned int x, unsigned int y, RGBA32Color color);
  const uint8_t *getRawData() const;
  unsigned int getWidth() const;
  unsigned int getHeight() const;
  void resize(unsigned int width, unsigned int height,
              RGBA32Color background_color);

private:
  std::vector<uint8_t> data_;
  unsigned int width_;
  unsigned int height_;
};
} // namespace cpp_renderer
