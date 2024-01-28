#include "RGBA32Color.hpp"

cpp_renderer::RGBA32Color::RGBA32Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) : data({red, green, blue, alpha}) {}

cpp_renderer::RGBA32Color::RGBA32Color(uint8_t value) : RGBA32Color(value, value, value) {}

cpp_renderer::RGBA32Color::RGBA32Color() : RGBA32Color(0x00) {}
