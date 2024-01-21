#include "Renderer.hpp"
#include "DisplayUtils.hpp"

cpp_renderer::RGBA32Image cpp_renderer::Renderer::render(const std::vector<Triangle> &polygons, unsigned int width, unsigned int height) const
{ // TODO(potentially): separate rendering passes into submethods if they start growing out of control

    // geometry pass
    auto depth_buffer = std::vector<std::vector<float>>(width, std::vector<float>(height, NAN));
    auto uv_buffer = std::vector<std::vector<Eigen::Vector2f>>(width, std::vector<Eigen::Vector2f>(height));
    auto poly_id_buffer = std::vector<std::vector<size_t>>(width, std::vector<size_t>(height, 0));

    for (size_t poly_id = 0; poly_id < polygons.size(); poly_id++)
    {
        const auto &polygon = polygons[poly_id];
        if (!DisplayUtils::checkIfVisible(polygon))
        {
            continue;
        }
        auto bounds = DisplayUtils::getBounds(polygon);

        for (auto x = bounds.left; x < bounds.right; ++x)
        {
            for (auto y = bounds.up; y < bounds.down; ++y)
            {
                auto uv = DisplayUtils::getUV(x, y, polygon);
                if (uv.has_value())
                {
                    auto depth = polygon.GetSurfacePoint(uv.value()).z();
                    if (std::isnan(depth_buffer[x][y]) || depth_buffer[x][y] > depth)
                    {
                        uv_buffer[x][y] = uv.value();
                        depth_buffer[x][y] = depth;
                        poly_id_buffer[x][y] = poly_id;
                    }
                }
            }
        }
    }

    // rendering pass
    auto frame = cpp_renderer::RGBA32Image(width, height, {0x00, 0x00, 0x00, 0xFF});

    for (auto x = 0; x < width; ++x)
    {
        for (auto y = 0; y < height; ++y)
        {
            if (NAN == depth_buffer[x][y])
            { // no object at (x, y)
                continue;
            }
            // TODO(me): proper color later
            uint8_t lightness = (1 / (exp(depth_buffer[x][y]))) * 0xff;
            frame.setPixel(x, y, RGBA32Pixel{lightness, lightness, lightness, 0xFF});
        }
    }
    return frame;
}