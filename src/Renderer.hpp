#pragma once
#include "Buffer2d.hpp"
#include "Camera.hpp"
#include "RGBA32Image.hpp"
#include "Rect.hpp"
#include "Triangle.hpp"
#include <Eigen/Dense>

namespace cpp_renderer {
class Renderer {
public:
  using Vector2 = Eigen::Vector2f;
  RGBA32Image &render(const std::vector<Triangle> &polygons,
                      const Camera &camera);

protected:
  void setResolution(size_t width, size_t height);
  void doGeometryPass(const std::vector<Triangle> &projected_polygons);
  void doRenderingPass();
  void cachePolygonGeometry(const Triangle &polygon);
  bool isPixelVoid(size_t x, size_t y);
  bool checkIfVisible(const Triangle &triangle) const;
  Rect<int> getScreenBounds(const Triangle &screen_space_polygon) const;
  Rect<size_t> clipToScreen(cpp_renderer::Rect<int> bounds, size_t width,
                            size_t height) const;

  RGBA32Image frame;
  Buffer2d<float> depth_buffer_;
  Buffer2d<Vector2> uv_buffer_;
};
} // namespace cpp_renderer
