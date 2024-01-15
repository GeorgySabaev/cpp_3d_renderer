#include "Renderer.hpp"

cpp_renderer::RGBA32Image cpp_renderer::Renderer::render(const std::vector<Triangle> &polygons, unsigned int width, unsigned int height) const
{
    auto frame = cpp_renderer::RGBA32Image(width, height, {0xFF,0xFF,0x00,0xFF});

    (void) depth_buffer_.empty();

    for (const auto& polygon : polygons)
    {
        auto bounds = my_tmp::getBounds(polygon);

        for (auto x = bounds.left; x < bounds.right; ++x)
        {
            for (auto y = bounds.up; y < bounds.down; ++y)
            {
                if(my_tmp::checkIfInTriangle(x, y)){
                    frame.setPixel(x, y, RGBA32Pixel{0xFF,0xFF,0xFF,0xFF});
                } else {
                    frame.setPixel(x, y, RGBA32Pixel{0xFF,0x00,0x00,0xFF});
                }
            }
        }
    }
    return frame;
}