#pragma once
#include <vector>
#include "RGBA32Color.hpp"

namespace cpp_renderer
{
    class RGBA32Image
    {
    public:
        RGBA32Image(unsigned int width, unsigned int height, RGBA32Color background_color = {});
        RGBA32Color getPixel(unsigned int x, unsigned int y) const;
        void setPixel(unsigned int x, unsigned int y, RGBA32Color color);
        const std::vector<uint8_t> &getData() const;
        unsigned int getWidth() const;
        unsigned int getHeight() const;

    private:
        std::vector<uint8_t> data_;
        unsigned int width_;
        unsigned int height_;
    };
}