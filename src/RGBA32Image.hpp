#pragma once
#include <vector>
#include "RGBA32Pixel.hpp"

namespace cpp_renderer
{
    class RGBA32Image
    {
    public:
        RGBA32Image(unsigned int width, unsigned int height, RGBA32Pixel background_color = {0x00, 0x00, 0x00, 0xFF});
        RGBA32Pixel getPixel(unsigned int x, unsigned int y);
        void setPixel(unsigned int x, unsigned int y, RGBA32Pixel color);
        const std::vector<RGBA32Pixel>& getData() const;
        unsigned int getWidth() const;
        unsigned int getHeight() const;

    private:
        std::vector<RGBA32Pixel> data_;
        unsigned int width_;
        unsigned int height_;
    };
}