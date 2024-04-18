// ===== Established 2024-04-17 - 2024-0X-0X =====
//
//  Functionality: Generates the game.
//
// ===============================================



#include <SFML/Graphics.hpp>
#include "Input.hpp"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720



/**
 * Enables for user input of a vector
 * @param argc number of arguments
 * @param argv the commands
 * @return 0 for no errors, otherwise 1.
*/
int main()
{
    // setup game executable
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
        "apoc.exe");
    
    // test sprite, default: circle
    sf::CircleShape shape(25.f);
    shape.setFillColor(sf::Color::Red);

    // healthbar
    sf::RectangleShape health_bar(sf::Vector2f(300, 30));
    health_bar.setFillColor(sf::Color::Green);
    health_bar.setOutlineColor(sf::Color::Red);
    health_bar.setOutlineThickness(5);
    health_bar.setOrigin(-490, -650);


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
        window.draw(health_bar);
        window.draw(shape);
        window.display();

        input(shape);
    }

    return 0;
}