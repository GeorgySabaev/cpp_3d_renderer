#include "Renderer.hpp"

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
    if (!checkIfVisible(polygon)) {
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
  auto bounds = clipToScreen(getScreenBounds(polygon), frame.getWidth(),
                             frame.getHeight());

  for (auto x = bounds.left; x < bounds.right; ++x) {
    for (auto y = bounds.up; y < bounds.down; ++y) {
      auto uv = polygon.getUV(x, y);
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

bool Renderer::checkIfVisible(const Triangle &triangle) const {
  auto pivot = triangle[0].head<2>();
  auto b = triangle[1].head<2>() - pivot;
  auto c = triangle[2].head<2>() - pivot;
  auto l_perpendicular = Eigen::Vector2f(-c.y(), c.x());

  return b.dot(l_perpendicular) > 0;
}

Rect<int>
Renderer::getScreenBounds(const Triangle &screen_space_polygon) const {
  float min_x;
  float max_x;
  float min_y;
  float max_y;
  min_x = max_x = screen_space_polygon[0][0];
  min_y = max_y = screen_space_polygon[0][1];
  for (auto point : screen_space_polygon.points) {
    min_x = std::min(min_x, point[0]);
    min_y = std::min(min_y, point[1]);
    max_x = std::max(max_x, point[0]);
    max_y = std::max(max_y, point[1]);
  }
  Rect<int> bounds;
  bounds.left = floorf(min_x);
  bounds.right = ceilf(max_x);
  bounds.up = floorf(min_y);
  bounds.down = ceilf(max_y);

  return bounds;
}

Rect<size_t> Renderer::clipToScreen(cpp_renderer::Rect<int> bounds,
                                    size_t width, size_t height) const {
  Rect<size_t> new_bounds;
  new_bounds.left = std::max(bounds.left, 0);
  new_bounds.up = std::max(bounds.up, 0);
  if (new_bounds.right < 0) {
    new_bounds.right = 0;
  } else {
    new_bounds.right = std::min(static_cast<size_t>(bounds.right), width);
  }
  if (new_bounds.down < 0) {
    new_bounds.down = 0;
  } else {
    new_bounds.down = std::min(static_cast<size_t>(bounds.down), height);
  }
  return new_bounds;
}

} // namespace cpp_renderer
