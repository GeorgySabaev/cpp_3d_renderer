#include "Renderer.hpp"
#include "DisplayUtils.hpp"

cpp_renderer::RGBA32Image cpp_renderer::Renderer::render(const std::vector<Triangle> &polygons, unsigned int width, unsigned int height) const
{
    auto frame = cpp_renderer::RGBA32Image(width, height, {0x00,0x00,0x00,0xFF});

    (void) depth_buffer_.empty();

    for (const auto& polygon : polygons)
    {
        if(!DisplayUtils::checkIfVisible(polygon)){
            continue;
        }
        auto bounds = DisplayUtils::getBounds(polygon);

        for (auto x = bounds.left; x < bounds.right; ++x)
        {
            for (auto y = bounds.up; y < bounds.down; ++y)
            {
                if(DisplayUtils::checkIfInTriangle(x, y, polygon)){
                    frame.setPixel(x, y, RGBA32Pixel{0xFF,0xFF,0xFF,0xFF});
                }
            }
        }
    }
    return frame;
}