#include "Application.hpp"
#include "ShapeBuilder.hpp"
#include <iostream>
#include <numbers>

namespace cpp_renderer {
Application::Application()
    : window(sf::VideoMode(DEFAULT_WIDTH, DEFAULT_HEIGHT), "My window"),
      camera(1, DEFAULT_WIDTH, DEFAULT_HEIGHT, 1, 20), model("./teapot.obj") {
  for (auto &triangle : model.polygons) {
    for (auto &point : triangle.points) {
      point.z() -= 5;
      point.y() -= 1;
    }
  }
}

void Application::Run() {
  while (window.isOpen()) {
    handleEvents();

    window.clear(sf::Color::Magenta);

    auto win_size = window.getView().getSize();
    auto &triangles = model.polygons; // buildScene();
    auto &frame = renderer.render(triangles, camera);
    drawFrame(frame);

    window.display();
  }
}

std::vector<cpp_renderer::Triangle> Application::buildScene() const {
  cpp_renderer::ShapeBuilder shapeBuilder;
  auto rotation =
      Eigen::AngleAxisf(clock.getElapsedTime().asSeconds() * std::numbers::pi,
                        Eigen::Vector3f::UnitY())
          .matrix();
  rotation = rotation *
             Eigen::AngleAxisf(-atan(1 / sqrt(2)), Eigen::Vector3f::UnitX());
  rotation = rotation * Eigen::AngleAxisf(-0.25 * std::numbers::pi,
                                          Eigen::Vector3f::UnitZ());
  return shapeBuilder.addCube({0, 0, -3}, rotation)
      .addCube({-0.5, -0.5, -3}, Eigen::Matrix3f::Identity())
      .build();
}

void Application::drawFrame(const RGBA32Image &frame) {
  auto image = sf::Image();
  image.create(frame.getWidth(), frame.getHeight(), frame.getRawData());

  auto texture = sf::Texture();
  texture.loadFromImage(image);

  auto sprite = sf::Sprite(texture);
  window.draw(sprite);
}

void Application::handleEvents() {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
    } else if (event.type == sf::Event::Resized) {
      resizeWindow(event.size.width, event.size.height);
    }
  }
}

void Application::resizeWindow(size_t width, size_t height) {
  window.setView(sf::View(sf::FloatRect(0, 0, width, height)));
  camera.resizeScreen(width, height);
}
} // namespace cpp_renderer
