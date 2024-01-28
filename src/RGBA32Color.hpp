#pragma once
#include <array>
#include <cstdint>

namespace cpp_renderer
{
    struct RGBA32Color
    {
        RGBA32Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 0xFF);
        RGBA32Color(uint8_t value);
        RGBA32Color();

        auto operator<=>(const RGBA32Color &) const = default;

        std::array<uint8_t, 4> data;
    };

}