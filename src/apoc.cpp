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
#include <stdlib.h>
#include <string>
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
    double fired_cnt = 0;

    // crosshair
    sf::CircleShape crosshair(5.f);
    crosshair.setFillColor(sf::Color::Red);

    // enemy
    sf::Clock clock_two;
    vector<sf::CircleShape> bots;
    sf::CircleShape bot(25.f);
    bot.setFillColor(sf::Color::Magenta);

    // fps
    sf::Clock clock_three;

    // font and text
    sf::Font font;
    if (!font.loadFromFile("../assets/scpro.ttf"))
    {
        cout << "The specified font failed to load." << endl;
    }
    sf::Text test_txt;
    test_txt.setFont(font);
    test_txt.setString("Test");
    sf::Text fired;
    sf::Text fps;
    fired.setFont(font);
    fps.setFont(font);
    fired.setFillColor(sf::Color::Blue);
    fps.setFillColor(sf::Color::Blue);
    fired.setPosition(1000, 600);
    fps.setPosition(1000, 650);
    
    // setup window options: open and close
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time fps_cnt = clock_three.getElapsedTime();
        fps.setString(to_string(1.0f / fps_cnt.asSeconds()));
        clock_three.restart();

        fired.setString(to_string(fired_cnt));

        window.clear();
        window.draw(health_bar);
        window.draw(shape);
        window.draw(crosshair);
        window.draw(fired);
        window.draw(fps);
        //window.draw(test_txt);

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
                fired_cnt++;
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

        sf::Time spawn_rate = clock_two.getElapsedTime();
        if (spawn_rate.asSeconds() >= 2.0f) {
            bot.setPosition(rand() % 1000, rand() % 1000);
            bots.push_back(bot);

            window.draw(bot);
            bot.move(0.5f, 0);
            spawn_rate = clock_two.restart();
        }

        for (int i = 0; i < (int)bots.size(); i++) {
            window.draw(bots[i]);
            bots[i].move(0.5f, 0);

            if (bots[i].getPosition().x > 1000 || bots[i].getPosition().x < 0 ||
                bots[i].getPosition().y < 0 || bots[i].getPosition().y > 700) {
                bots.erase(bots.begin() + i);
            }
        }
        window.display();

        input(shape);
    }

    return 0;
}