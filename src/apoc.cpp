// ===== Established 2024-04-17 - 2024-0X-0X =====
//
//  Functionality: Generates the game.
//
// ===============================================



#include <SFML/Graphics.hpp>
#include "Input.hpp"
#include <vector>
#include <iostream>
#include <math.h>
using namespace std;

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

    // test projectiles
    sf::RectangleShape bullet(sf::Vector2f(15, 5));
    bullet.setFillColor(sf::Color::Yellow);
    vector<sf::RectangleShape> bullets;
    //vector<sf::CircleShape> bullets;
    sf::Clock clock; // starts the clock
    vector<float> direction;
    //sf::Vector2f bullet_pos(shape.getPosition().x + shape.getRadius(), shape.getPosition().y + shape.getRadius());

    // crosshair
    sf::CircleShape crosshair(5.f);
    crosshair.setFillColor(sf::Color::Red);
    
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
        window.draw(crosshair);

        crosshair.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
        sf::Time fire_rate = clock.getElapsedTime();
        sf::Vector2f bullet_pos(shape.getPosition().x + shape.getRadius(), shape.getPosition().y + shape.getRadius());

        //double player_pos_x = shape.getPosition().x;
        //double player_pos_y = shape.getPosition().y;

        //cout << shape.getPosition().x << endl;
        //cout << shape.getPosition().y << endl;
        //cout << clock.getElapsedTime().asSeconds() << endl;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (fire_rate.asSeconds() >= 0.3f) {
                fire_rate = clock.restart();
                //bullet.setPosition(shape.getPosition());
                bullet.setPosition(bullet_pos);
                bullets.push_back(bullet);
                direction.push_back(atan2(sf::Mouse::getPosition(window).y - shape.getPosition().y,
                    sf::Mouse::getPosition(window).x - shape.getPosition().x));
            }

            /* bullets.push_back(sf::CircleShape());
            bullets.back().setRadius(5);
            bullets.back().setOrigin(5,5);
            bullets.back().setPosition(shape.getPosition());
            direction.push_back(atan2(sf::Mouse::getPosition(window).y - shape.getPosition().y,
                    sf::Mouse::getPosition(window).x - shape.getPosition().x)); */
        }

        for (int i = 0; i < (int)bullets.size(); i++) {
            window.draw(bullets[i]);
            bullets[i].move(0.5f * cos(direction[i]), 0.5f * sin(direction[i]));

            if (bullets[i].getPosition().x > 1000 || bullets[i].getPosition().x < 0 ||
                bullets[i].getPosition().y < 0 || bullets[i].getPosition().y > 700) {
                bullets.erase(bullets.begin() + i);
                direction.erase(direction.begin() + i);
            }
        }
        window.display();

        input(shape);
        // cout << shape.getPosition().x << " " << shape.getPosition().y << endl;
    }

    return 0;
}