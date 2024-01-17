#include "RGBA32Image.hpp"
#include <cassert>

cpp_renderer::RGBA32Image::RGBA32Image(unsigned int width, unsigned int height, RGBA32Pixel background_color)
{
    data_ = std::vector<RGBA32Pixel>(width*height, background_color);
    width_ = width;
    height_ = height;
}

cpp_renderer::RGBA32Pixel cpp_renderer::RGBA32Image::getPixel(unsigned int x, unsigned int y)
{
    assert(x < width_);
    assert(y < height_);
    return data_[width_*y + x];
}

void cpp_renderer::RGBA32Image::setPixel(unsigned int x, unsigned int y, RGBA32Pixel color)
{
    data_[width_*y + x] = color;
}

const std::vector<cpp_renderer::RGBA32Pixel> &cpp_renderer::RGBA32Image::getData() const
{
    return data_;
}

unsigned int cpp_renderer::RGBA32Image::getWidth() const
{
    return width_;
}

unsigned int cpp_renderer::RGBA32Image::getHeight() const
{
    return height_;
}
