#pragma once
#include "Buffer2d.hpp"
#include "Camera.hpp"
#include "RGBA32Image.hpp"
#include "Triangle.hpp"
#include <Eigen/Dense>

namespace cpp_renderer {
class Renderer {
public:
  RGBA32Image &render(const std::vector<Triangle> &polygons,
                      const Camera &camera);

protected:
  void setResolution(unsigned int width, unsigned int height);
  void doGeometryPass(const std::vector<Triangle> &projected_polygons);
  void doRenderingPass();
  void cachePolygonGeometry(const Triangle &polygon);
  bool isPixelVoid(unsigned int x, unsigned int y);

  RGBA32Image frame;
  Buffer2d<float> depth_buffer_;
  Buffer2d<Eigen::Vector2f> uv_buffer_;
};
} // namespace cpp_renderer
