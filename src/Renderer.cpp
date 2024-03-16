#include "Renderer.hpp"
#include "DisplayUtils.hpp"

namespace cpp_renderer {

RGBA32Image &Renderer::render(const std::vector<Triangle> &polygons,
                              const Camera &camera) {
  auto width = camera.getWidth();
  auto height = camera.getHeight();
  setResolution(width, height);

  auto projected_polygons = polygons;
  for (auto &polygon : projected_polygons) {
    for (auto &point : polygon.points) {
      point = camera.transform(point);
    }
  }

  doGeometryPass(projected_polygons);
  doRenderingPass();

  return frame;
}

void Renderer::setResolution(size_t width, size_t height) {
  depth_buffer_.resize(width, height, NAN);
  uv_buffer_.resize(width, height);
  frame.resize(width, height, RGBA32Colors::BLACK);
}

void Renderer::doGeometryPass(const std::vector<Triangle> &projected_polygons) {
  for (size_t poly_id = 0; poly_id < projected_polygons.size(); poly_id++) {
    const auto &polygon = projected_polygons[poly_id];
    if (!DisplayUtils::checkIfVisible(polygon)) {
      continue;
    }
    cachePolygonGeometry(polygon);
  }
}

void Renderer::doRenderingPass() {
  for (auto x = 0; x < frame.getWidth(); ++x) {
    for (auto y = 0; y < frame.getHeight(); ++y) {
      if (isPixelVoid(x, y)) { // no object at (x, y)
        continue;
      }
      // TODO(me): proper color later
      uint8_t lightness = 0xff * std::pow((1 + depth_buffer_(x, y)) / 2, 3);
      frame.setPixel(x, y, RGBA32Color(lightness, lightness, lightness));
    }
  }
}

void Renderer::cachePolygonGeometry(const Triangle &polygon) {
  auto bounds = DisplayUtils::clipToScreen(DisplayUtils::getBounds(polygon),
                                           frame.getWidth(), frame.getHeight());

  for (auto x = bounds.left; x < bounds.right; ++x) {
    for (auto y = bounds.up; y < bounds.down; ++y) {
      auto uv = DisplayUtils::getUV(x, y, polygon);
      if (!uv.has_value()) {
        continue;
      }
      auto depth = polygon.GetSurfacePoint(uv.value()).z();
      if (depth_buffer_(x, y) <= depth) {
        continue;
      }
      uv_buffer_(x, y) = uv.value();
      depth_buffer_(x, y) = depth;
    }
  }
}

bool Renderer::isPixelVoid(size_t x, size_t y) {
  return std::isnan(depth_buffer_(x, y));
}

} // namespace cpp_renderer
