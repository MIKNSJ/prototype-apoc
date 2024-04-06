#include <SFML/Graphics.hpp>
#include "Input.hpp"



int main()
{
    // setup game executable
    sf::RenderWindow window(sf::VideoMode(1280, 720), "apoc.exe");
    sf::CircleShape shape(25.f);
    shape.setFillColor(sf::Color::Red);

    // setup window options: open and close
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();

        input(shape);
    }

    return 0;
}