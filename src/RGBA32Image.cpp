#include "RGBA32Image.hpp"
#include <cassert>

cpp_renderer::RGBA32Image::RGBA32Image(size_t width, size_t height,
                                       RGBA32Color background_color) {
  width_ = width;
  height_ = height;
  data_ = std::vector<uint8_t>(width * height * 4);

  for (size_t i = 0; i < width * height; i++) {
    std::copy(background_color.data.begin(), background_color.data.end(),
              data_.begin() + i * 4);
  }
}

cpp_renderer::RGBA32Color cpp_renderer::RGBA32Image::getPixel(size_t x,
                                                              size_t y) const {
  assert(x < width_);
  assert(y < height_);
  RGBA32Color color(data_.begin() + (width_ * y + x) * 4);
  return color;
}

void cpp_renderer::RGBA32Image::setPixel(size_t x, size_t y,
                                         RGBA32Color color) {
  assert(x < width_);
  assert(y < height_);
  std::copy(color.data.begin(), color.data.end(),
            data_.begin() + (width_ * y + x) * 4);
}

const uint8_t *cpp_renderer::RGBA32Image::getRawData() const {
  return data_.data();
}

size_t cpp_renderer::RGBA32Image::getWidth() const { return width_; }

size_t cpp_renderer::RGBA32Image::getHeight() const { return height_; }

void cpp_renderer::RGBA32Image::resize(size_t width, size_t height,
                                       RGBA32Color background_color) {
  width_ = width;
  height_ = height;
  data_.resize(width * height * 4);

  if (background_color != RGBA32Color(0, 0, 0, 0)) {
    for (size_t i = 0; i < width * height; i++) {
      std::copy(background_color.data.begin(), background_color.data.end(),
                data_.begin() + i * 4);
    }
  }
}
