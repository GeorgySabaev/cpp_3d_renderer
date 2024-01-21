#include <SFML/Graphics.hpp>
#include "Renderer.hpp"
#include "Camera.hpp"

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Magenta);

        auto win_size = window.getView().getSize();

        // example triangles
        // TODO(me): read actual files

        std::vector<cpp_renderer::Triangle> triangles(1);
        triangles[0].points[0][0] = 1;
        triangles[0].points[0][1] = 1;
        triangles[0].points[0][2] = 4;
        triangles[0].points[1][0] = -1;
        triangles[0].points[1][1] = -1;
        triangles[0].points[1][2] = 8;
        triangles[0].points[2][0] = -1;
        triangles[0].points[2][1] = 1;
        triangles[0].points[2][2] = 12;
        /*
        triangles[0].points[0][0] = 120;
        triangles[0].points[0][1] = 50;
        triangles[0].points[0][2] = 0.4;
        triangles[0].points[1][0] = 150;
        triangles[0].points[1][1] = 300;
        triangles[0].points[1][2] = 1;
        triangles[0].points[2][0] = 230;
        triangles[0].points[2][1] = 210;
        triangles[0].points[2][2] = 2.5;

        triangles[1].points[0][0] = 100;
        triangles[1].points[0][1] = 180;
        triangles[1].points[0][2] = 1.8;
        triangles[1].points[1][0] = 300;
        triangles[1].points[1][1] = 250;
        triangles[1].points[1][2] = 1.5;
        triangles[1].points[2][0] = 300;
        triangles[1].points[2][1] = 120;
        triangles[1].points[2][2] = 0.15;

        triangles[1].points[0][0] = 100;
        triangles[1].points[0][1] = 180;
        triangles[1].points[0][2] = 2;
        triangles[1].points[1][0] = 300;
        triangles[1].points[1][1] = 250;
        triangles[1].points[1][2] = 2;
        triangles[1].points[2][0] = 300;
        triangles[1].points[2][1] = 120;
        triangles[1].points[2][2] = 1;
        */

        // actual renderer call
        auto renderer = cpp_renderer::Renderer();
        auto frame = renderer.render(triangles, win_size.x, win_size.y, cpp_renderer::Camera(1, win_size.x, win_size.y));

        auto image = sf::Image();
        image.create(win_size.x, win_size.y, reinterpret_cast<const sf::Uint8 *>(frame.getData().data()));

        auto texture = sf::Texture();
        texture.loadFromImage(image);

        auto sprite = sf::Sprite(texture);
        window.draw(sprite);

        // end the current frame
        window.display();
    }

    return 0;
}
