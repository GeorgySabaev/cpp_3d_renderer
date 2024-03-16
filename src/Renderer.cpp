#include "Renderer.hpp"
#include "DisplayUtils.hpp"

namespace cpp_renderer {

void Renderer::setResolution(unsigned int width, unsigned int height) {
  depth_buffer_.clear(width, height, NAN);
  uv_buffer_.clear(width, height);
  poly_id_buffer_.clear(width, height);
  frame.resize(width, height, {0x00, 0x00, 0x00, 0xFF});
}

RGBA32Image &Renderer::render(const std::vector<Triangle> &polygons,
                              const Camera &camera) {
  auto width = camera.getWidth();
  auto height = camera.getHeight();
  setResolution(width, height);

  // TODO(potentially): separate rendering passes into submethods if they start
  // growing out of control
  auto projected_polygons = polygons;

  for (auto &polygon : projected_polygons) {
    for (auto &point : polygon.points) {
      point = camera.transform(point);
    }
  }

  // geometry pass
  for (size_t poly_id = 0; poly_id < projected_polygons.size(); poly_id++) {
    const auto &polygon = projected_polygons[poly_id];
    if (!DisplayUtils::checkIfVisible(polygon)) {
      continue;
    }
    auto bounds = DisplayUtils::clipToScreen(DisplayUtils::getBounds(polygon),
                                             width, height);

    for (auto x = bounds.left; x < bounds.right; ++x) {
      for (auto y = bounds.up; y < bounds.down; ++y) {
        auto uv = DisplayUtils::getUV(x, y, polygon);
        if (uv.has_value()) {
          auto depth = polygon.GetSurfacePoint(uv.value()).z();
          if (std::isnan(depth_buffer_(x, y)) || depth_buffer_(x, y) > depth) {
            uv_buffer_(x, y) = uv.value();
            depth_buffer_(x, y) = depth;
            poly_id_buffer_(x, y) = poly_id;
          }
        }
      }
    }
  }

  for (auto x = 0; x < width; ++x) {
    for (auto y = 0; y < height; ++y) {
      if (std::isnan(depth_buffer_(x, y))) { // no object at (x, y)
        continue;
      }
      // TODO(me): proper color later
      uint8_t lightness = 0xff * std::pow((1 + depth_buffer_(x, y)) / 2, 3);
      // uint8_t lightness = (1 /
      // (exp(polygons[poly_id_buffer[x][y]].GetSurfacePoint(uv_buffer[x][y]).norm()
      // / 5))) * 0xff;
      frame.setPixel(x, y, RGBA32Color(lightness, lightness, lightness));
    }
  }

  return frame;
}
} // namespace cpp_renderer
