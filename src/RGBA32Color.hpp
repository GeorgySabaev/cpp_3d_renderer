#pragma once
#include <array>
#include <cstdint>
#include <vector>

namespace cpp_renderer {
struct RGBA32Color {
  static constexpr size_t CHANNEL_COUNT = 4;

  constexpr RGBA32Color(uint8_t red = 0x00, uint8_t green = 0x00,
                        uint8_t blue = 0x00, uint8_t alpha = 0xFF)
      : data({red, green, blue, alpha}){};
  RGBA32Color(std::vector<uint8_t>::const_iterator raw_data);

  auto operator<=>(const RGBA32Color &) const = default;

  std::array<uint8_t, CHANNEL_COUNT> data;
};

} // namespace cpp_renderer
