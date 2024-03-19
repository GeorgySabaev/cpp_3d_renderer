#pragma once
#include <vector>

namespace cpp_renderer {
template <typename T> class Buffer2d {
public:
  size_t getWidth() const { return width_; }
  size_t getHeight() const { return data_.size() / width_; }

  const T &operator()(size_t x, size_t y) const {
    return data_[y * width_ + x];
  }

  T &operator()(size_t x, size_t y) { return data_[y * width_ + x]; }

  void resize(size_t width, size_t height, T value = T()) {
    data_.resize(0);
    data_.resize(width * height, value);
    width_ = width;
  }

  void resize() { resize(width_, getHeight()); }

private:
  std::vector<T> data_;
  size_t width_;
};
} // namespace cpp_renderer
