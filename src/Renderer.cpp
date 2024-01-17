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
                auto uv = DisplayUtils::getUV(x, y, polygon);
                if(uv.has_value()){
                    // frame.setPixel(x, y, RGBA32Pixel{0xFF,0x10,0x50,0xFF});
                    frame.setPixel(x, y, RGBA32Pixel{static_cast<uint8_t>(uv.value().x() * 200),static_cast<uint8_t>(uv.value().y() * 200),0x00,0xFF});
                }
            }
        }
    }
    return frame;
}