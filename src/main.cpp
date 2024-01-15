#include <SFML/Graphics.hpp>
#include "Renderer.hpp"
#include <iostream>

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
        std::vector<cpp_renderer::Triangle> triangles(2);
        triangles[0].points[0][0] = 100;
        triangles[0].points[0][1] = 150;
        triangles[0].points[0][2] = 0;
        triangles[0].points[1][0] = 200;
        triangles[0].points[1][1] = 250;
        triangles[0].points[1][2] = 0;
        triangles[0].points[2][0] = 200;
        triangles[0].points[2][1] = 150;
        triangles[0].points[2][2] = 0;
        
        triangles[1].points[0][0] = 300;
        triangles[1].points[0][1] = 130;
        triangles[1].points[0][2] = 0;
        triangles[1].points[1][0] = 500;
        triangles[1].points[1][1] = 250;
        triangles[1].points[1][2] = 0;
        triangles[1].points[2][0] = 500;
        triangles[1].points[2][1] = 120;
        triangles[1].points[2][2] = 0;

        // tests
        std::cout << "test" << std::endl;
        auto b = my_tmp::getBounds(triangles[0]);
        

        // actual renderer call
        auto renderer = cpp_renderer::Renderer();
        auto frame = renderer.render(triangles, win_size.x, win_size.y);

        auto image = sf::Image();
        image.create(win_size.x, win_size.y, reinterpret_cast<const sf::Uint8*>(frame.getData().data()));

        auto texture = sf::Texture();
        texture.loadFromImage(image);

        auto sprite = sf::Sprite(texture);
        window.draw(sprite);

        // end the current frame
        window.display();
    }

    return 0;
}
