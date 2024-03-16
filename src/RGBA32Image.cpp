#include "RGBA32Image.hpp"
#include <cassert>

cpp_renderer::RGBA32Image::RGBA32Image(unsigned int width, unsigned int height,
                                       RGBA32Color background_color) {
  width_ = width;
  height_ = height;
  data_ = std::vector<uint8_t>(width * height * 4);

  if (background_color != RGBA32Color(0, 0, 0, 0)) {
    for (size_t i = 0; i < width * height; i++) {
      std::copy(background_color.data.begin(), background_color.data.end(),
                data_.begin() + i * 4);
    }
  }
}

cpp_renderer::RGBA32Color
cpp_renderer::RGBA32Image::getPixel(unsigned int x, unsigned int y) const {
  assert(x < width_);
  assert(y < height_);
  RGBA32Color color;
  std::copy(data_.begin() + (width_ * y + x) * 4,
            data_.begin() + (width_ * y + x + 1) * 4, color.data.begin());
  return color;
}

void cpp_renderer::RGBA32Image::setPixel(unsigned int x, unsigned int y,
                                         RGBA32Color color) {
  assert(x < width_);
  assert(y < height_);
  std::copy(color.data.begin(), color.data.end(),
            data_.begin() + (width_ * y + x) * 4);
}

const uint8_t *cpp_renderer::RGBA32Image::getRawData() const {
  return data_.data();
}

unsigned int cpp_renderer::RGBA32Image::getWidth() const { return width_; }

unsigned int cpp_renderer::RGBA32Image::getHeight() const { return height_; }
