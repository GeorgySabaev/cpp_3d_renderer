#pragma once

#include "Camera.hpp"
#include "Renderer.hpp"
#include <SFML/Graphics.hpp>

namespace cpp_renderer {
class Application {
public:
  Application();

  void Run();

protected:
  sf::Clock clock;
  cpp_renderer::Renderer renderer;
  sf::RenderWindow window;

  std::vector<cpp_renderer::Triangle> buildScene() const;
  void drawFrame(const RGBA32Image &frame);
};
} // namespace cpp_renderer
