#include "Renderer.hpp"
#include "DisplayUtils.hpp"

cpp_renderer::RGBA32Image cpp_renderer::Renderer::render(const std::vector<Triangle> &polygons, unsigned int width, unsigned int height) const
{
    auto frame = cpp_renderer::RGBA32Image(width, height, {0x00,0x00,0x00,0xFF});
    auto depth_buffer = std::vector<std::vector<float>>(width, std::vector<float>(height, NAN));
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
                    auto depth = DisplayUtils::getDepth(uv.value(), polygon);
                    if(std::isnan(depth_buffer[x][y]) || depth_buffer[x][y] > depth){
                        depth_buffer[x][y] = depth;   
                        uint8_t lightness = (1/(exp(depth)))*0xff;
                        frame.setPixel(x, y, RGBA32Pixel{lightness,lightness,lightness,0xFF});
                    }
                }
            }
        }
    }

    return frame;
}