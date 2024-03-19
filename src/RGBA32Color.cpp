#include "RGBA32Color.hpp"

namespace cpp_renderer {
RGBA32Color::RGBA32Color(std::vector<uint8_t>::const_iterator raw_data) {
  for (size_t i = 0; i < CHANNEL_COUNT; i++) {
    data[i] = raw_data[i];
  }
}

} // namespace cpp_renderer
