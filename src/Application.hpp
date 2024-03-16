#pragma once

#include "Camera.hpp"
#include "Renderer.hpp"
#include <SFML/Graphics.hpp>

namespace cpp_renderer {
class Application {
public:
  static constexpr size_t DEFAULT_WIDTH = 800;
  static constexpr size_t DEFAULT_HEIGHT = 600;

  Application();

  void Run();

protected:
  sf::Clock clock;
  cpp_renderer::Renderer renderer;
  cpp_renderer::Camera camera;
  sf::RenderWindow window;

  std::vector<cpp_renderer::Triangle> buildScene() const;
  void drawFrame(const RGBA32Image &frame);
  void handleEvents();
  void resizeWindow(size_t width, size_t height);
};
} // namespace cpp_renderer
