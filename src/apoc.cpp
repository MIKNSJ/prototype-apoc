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
    
    // setup font
    sf::Font font;
    if (!font.loadFromFile("../assets/scpro.ttf"))
    {
        cout << "The specified font failed to load." << endl;
    }
    
    // test sprite, default: circle
    sf::CircleShape shape(25.f);
    shape.setFillColor(sf::Color::Red);
    //sf::CircleShape *shape_ptr;
    //shape_ptr = &shape;
    //cout << shape_ptr->getPosition().x << endl;
    //cout << shape_ptr->getPosition().y << endl;
    sf::FloatRect shape_hitbox;

    // healthbar
    int health_num = 100;
    sf::RectangleShape health_bar(sf::Vector2f(300, 30));
    health_bar.setFillColor(sf::Color::Green);
    health_bar.setOutlineColor(sf::Color::Red);
    health_bar.setOutlineThickness(5);
    health_bar.setOrigin(-490, -650);

    // heath in num
    sf::Text health;
    health.setFont(font);
    health.setFillColor(sf::Color::Blue);
    health.setString(string("HP: ") + to_string(health_num));
    health.setPosition(100, 650);

    // test projectiles
    sf::RectangleShape bullet(sf::Vector2f(15, 5));
    bullet.setFillColor(sf::Color::Yellow);
    vector<sf::RectangleShape> bullets;
    //vector<sf::CircleShape> bullets;
    sf::Clock clock; // starts the clock
    vector<float> direction;
    //sf::Vector2f bullet_pos(shape.getPosition().x + shape.getRadius(), shape.getPosition().y + shape.getRadius());
    sf::FloatRect bullet_hitbox;

    // crosshair
    sf::CircleShape crosshair(5.f);
    crosshair.setFillColor(sf::Color::Red);

    // enemy
    sf::Clock clock_two;
    vector<sf::CircleShape> bots;
    sf::CircleShape bot(25.f);
    bot.setFillColor(sf::Color::Magenta);
    vector<float> enemy_direction;
    sf::FloatRect enemy_hitbox;

    // fps
    sf::Clock clock_three;

    // ig timer
    sf::Clock clock_four;
    sf::Time ig_time;
    sf::Text ig_timer;
    ig_timer.setFont(font);
    ig_timer.setFillColor(sf::Color::Blue);
    ig_timer.setPosition(100, 600);

    // font and text
    sf::Text test_txt;
    test_txt.setFont(font);
    test_txt.setString("Test");
    sf::Text score_txt;
    sf::Text fps;
    score_txt.setFont(font);
    fps.setFont(font);
    score_txt.setFillColor(sf::Color::Blue);
    fps.setFillColor(sf::Color::Blue);
    score_txt.setPosition(1000, 600);
    fps.setPosition(1000, 650);
    int score = 0;

    // setup camera
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(1920, 1080));
    //view.setCenter(shape.getPosition().x, shape.getPosition().y);
    //window.setView(view);
    sf::View uiView = window.getDefaultView();
    
    // setup window options: open and close
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            // catch the resize events
            if (event.type == sf::Event::Resized) {
                // ...
            }
        }

        
        health.setString(string("HP: ") + to_string(health_num));

        sf::Time fps_cnt = clock_three.getElapsedTime();
        fps.setString(to_string(1.0f / fps_cnt.asSeconds()));
        clock_three.restart();

        score_txt.setString(string("Score: ") + to_string(score));

        ig_time = clock_four.getElapsedTime();
        ig_timer.setString(to_string(ig_time.asSeconds()));


        window.clear();
        //view.setCenter(shape.getPosition().x, shape.getPosition().y);
        //window.setView(view);
        window.draw(shape);

        //window.draw(health_bar);

        //window.setView(uiView);
        window.draw(health);
        window.draw(ig_timer);
        window.draw(crosshair);
        window.draw(score_txt);
        window.draw(fps);

        //window.setView(view);
        //window.draw(test_txt);

        crosshair.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

        sf::Time fire_rate = clock.getElapsedTime();
        sf::Vector2f bullet_pos(shape.getPosition().x + shape.getRadius(), shape.getPosition().y + shape.getRadius());

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

            /*if (bullets[i].getPosition().x > window.getSize().x || bullets[i].getPosition().x < 0 ||
                bullets[i].getPosition().y < 0 || bullets[i].getPosition().y > window.getSize().y) {
                bullets.erase(bullets.begin() + i);
                direction.erase(direction.begin() + i);
            }*/
        }

        sf::Time spawn_rate = clock_two.getElapsedTime();
        if (spawn_rate.asSeconds() >= 3.0f) {
            bot.setPosition(rand() % 1000, rand() % 1000);
            bots.push_back(bot);
            enemy_direction.push_back(atan2(shape.getPosition().y - bot.getPosition().y,
                    shape.getPosition().x - bot.getPosition().x));

            spawn_rate = clock_two.restart();
        }

        for (int i = 0; i < (int)bots.size(); i++) {
            window.draw(bots[i]);
            enemy_direction[i] = atan2(shape.getPosition().y - bots[i].getPosition().y,
                    shape.getPosition().x - bots[i].getPosition().x);
            bots[i].move(0.3f * cos(enemy_direction[i]), 0.3f * sin(enemy_direction[i]));


            /*if (bots[i].getPosition().x > 1000 || bots[i].getPosition().x < 0 ||
                bots[i].getPosition().y < 0 || bots[i].getPosition().y > 700) {
                bots.erase(bots.begin() + i);
                enemy_direction.erase(enemy_direction.begin() + i);
            }*/

            enemy_hitbox = bots[i].getGlobalBounds();
            shape_hitbox = shape.getGlobalBounds();
            if (shape_hitbox.intersects(enemy_hitbox)) {
                bots.erase(bots.begin() + i);
                enemy_direction.erase(enemy_direction.begin() + i);
                health_num-=10;
            }
        }


        for (int i = 0; i < (int)bullets.size(); i++) {
            for (int j = 0; j < (int)bots.size(); j++) {
                bullet_hitbox = bullets[i].getGlobalBounds();
                shape_hitbox = shape.getGlobalBounds();
                if (bullet_hitbox.intersects(enemy_hitbox)) {
                    bullets.erase(bullets.begin() + i);
                    direction.erase(direction.begin() + i);
                    bots.erase(bots.begin() + j);
                    enemy_direction.erase(enemy_direction.begin() + j);
                    score++;
                }
            }
        }
        window.display();

        input(shape);
    }

    return 0;
}