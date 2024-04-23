// ===== Established 2024-04-17 - 2024-0X-0X =====
//
//  Functionality: Generates the game.
//
// ===============================================



#include <SFML/Graphics.hpp>
#include "Menu.hpp"
#include "Input.hpp"
#include <vector>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string>
using namespace std;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720



// =========================== CLASSES ========================================
/**
 * Player class
*/
class Player {
    public:
        sf::CircleShape sprite;
        sf::FloatRect hitbox;
        sf::Vector2f position;
        int health;
        bool invin;

        Player() : sprite(25.f), hitbox(), position(), health(100),
            invin(true) {
            sprite.setFillColor(sf::Color::Red);
            sprite.setPosition(640, 550);
            hitbox = sprite.getGlobalBounds();
            position = sprite.getPosition();
        }
};
// ============================================================================

/**
 * Enemy class
*/
class Enemy {
    public:
        sf::Clock spawn_timer;
        sf::CircleShape bot;
        vector<sf::CircleShape> bots;
        vector<float> direction;
        sf::FloatRect hitbox;
        sf::Vector2f position;
        float spawn_delay;
        float speed_modifier;
        int perk;
        int perk_two;

        Enemy() : spawn_timer(), bot(20.f), bots(), direction(), hitbox(),
            position(), spawn_delay(5.0), speed_modifier(1.0), perk(0),
            perk_two(0) {
            bot.setFillColor(sf::Color::Magenta);
            hitbox = bot.getGlobalBounds();
            position = bot.getPosition();
        }
};
// ============================================================================

/**
 * Projectile class
*/
class Projectile {
    public:
        sf::Clock fire_delay;
        sf::CircleShape bullet;
        vector<sf::CircleShape> bullets;
        vector<float> direction;
        sf::FloatRect hitbox;
        sf::Vector2f start_position;
    
    Projectile(float size) : fire_delay(), bullet(size), bullets(),
    direction(), hitbox(), start_position() {
        bullet.setFillColor(sf::Color::White);
        hitbox = bullet.getGlobalBounds();
    }
};
// ============================================================================

/**
 * HUD class
*/
class HUD {
    public:
        sf::Font font;
        sf::CircleShape crosshair;
        sf::Clock fps_timer;
        sf::Clock ig_timer;
        sf::Text display_ig_time;
        int minute;
        int seconds;
        sf::Text display_fps;
        sf::Text display_health;
        sf::Text display_score;
        sf::Text pause;
        sf::Text game_over;
        bool game_over_ind;
        int score;
        int last_score;
        bool pause_ind;
        bool show_crosshair;

        HUD(sf::RenderWindow &window) : font(), crosshair(5.f), fps_timer(),
            ig_timer(), display_ig_time(), minute(0), seconds(0), display_fps(),
            display_health(), display_score(), pause(), game_over(),
            game_over_ind(false), score(-1), last_score(-1), pause_ind(false),
            show_crosshair(true) {

            // Setup the default font of this game: Source Code Pro.
            if (!font.loadFromFile("../assets/scpro.ttf")) {
                cout << "The required font has failed to load." << endl;
                window.close();
            }

            crosshair.setFillColor(sf::Color::Green);

            display_fps.setFont(font);
            display_fps.setFillColor(sf::Color::White);
            display_fps.setPosition(1045, 650);

            display_ig_time.setFont(font);
            display_ig_time.setFillColor(sf::Color::White);
            display_ig_time.setPosition(1045, 600);

            display_health.setFont(font);
            display_health.setFillColor(sf::Color::White);
            display_health.setPosition(50, 600);

            display_score.setFont(font);
            display_score.setFillColor(sf::Color::White);
            display_score.setPosition(50, 650);

            game_over.setFont(font);
            game_over.setString("[GAME OVER]");
            game_over.setFillColor(sf::Color::Magenta);
            game_over.setPosition(575, 575);

            pause.setFont(font);
            pause.setString("[PAUSED]");
            pause.setFillColor(sf::Color::Magenta);
            pause.setPosition(575, 0);
        }
};
// ============================================================================
// ======================== END OF CLASSES ====================================

/**
 * Enables for user input of a vector
 * @param argc number of arguments
 * @param argv the commands
 * @return 0 for no errors, otherwise 1.
*/
int main()
{
    // ========== WINDOW SETTINGS =============================================
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
        "apoc.exe");
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(120);
    // ========================================================================



    // ================ INIT ==================================================
    Player player;
    Enemy enemy;
    Projectile projectile(5.0f);
    HUD hud(window);
    Menu menu(SCREEN_WIDTH, SCREEN_HEIGHT);
    // ========================================================================
    


    // =============== GAME ===================================================
    while (window.isOpen()) {

        // ================== EVENT ===========================================
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            // catch the resize events
            if (event.type == sf::Event::Resized) {
                // ...
            }

            /**
             * pause system
             * Press "P" to pause, "O" to unpause
             * Pause is not toggle-binded to a single key due to multiple input
             * registeration when pressed on a specific key once.
            */
            if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                    hud.pause_ind = true;
                }   

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
                    hud.pause_ind = false;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    menu.navigateUp(menu.select);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    menu.navigateDown(menu.select);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    if (menu.select == 0) {
                        menu.play = true;
                        menu.select = -1;
                    } 

                    if (menu.select == 1) {
                        window.close();
                    }

                    if (hud.game_over_ind) {
                        player.invin = true;
                        menu.play = false;
                        menu.select = 0;
                    } else {
                        player.invin = false;
                    }

                    hud.score = 0;
                    enemy.bots.clear();
                    projectile.bullets.clear();
                    hud.pause_ind = false;
                    hud.game_over_ind = false;
                    player.sprite.setPosition(640, 550);
                    player.health = 3;
                    enemy.spawn_delay = 5.0f;
                    enemy.speed_modifier = 1.0f;
                    hud.ig_timer.restart();
                    hud.fps_timer.restart();
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
                    hud.show_crosshair = false;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
                    hud.show_crosshair = true;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window.close();
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
                    enemy.bots.clear();
                    projectile.bullets.clear();
                    menu.play = true;
                    hud.pause_ind = false;
                    hud.game_over_ind = false;
                    player.sprite.setPosition(640, 550);
                    player.health = 3;
                    player.invin = false;
                    enemy.spawn_delay = 5.0f;
                    enemy.speed_modifier = 1.0f;
                    hud.ig_timer.restart();
                    hud.fps_timer.restart();
                }
            }
        }
        // ====================================================================
        if (player.health == 0) {
            hud.game_over_ind = true;
            hud.pause_ind = true;
        }

        if (!hud.pause_ind && !hud.game_over_ind) {        
            // ===================== SPRITE/PLAYER ============================
            // ==================== PLAYER BOUNDARIES =========================
            if (player.sprite.getPosition().x < 0) {
                player.sprite.setPosition(0, player.sprite.getPosition().y);
            }

            if (player.sprite.getPosition().x > 1230) {
                player.sprite.setPosition(1230, player.sprite.getPosition().y);
            }

            if (player.sprite.getPosition().y < 0) {
                player.sprite.setPosition(player.sprite.getPosition().x, 0);
            }

            if (player.sprite.getPosition().y > 670) {
                player.sprite.setPosition(player.sprite.getPosition().x, 670);
            }
            // ================================================================
            // ================================================================

            // ====================== HUD =====================================
            hud.display_health.setString(string("HP: ") +
                to_string(player.health));
            hud.crosshair.setPosition(sf::Mouse::getPosition(window).x,
                sf::Mouse::getPosition(window).y);
            hud.display_fps.setString("FPS: " +
                to_string(1.0f / hud.fps_timer.getElapsedTime().asSeconds()));
            hud.fps_timer.restart();
            hud.display_score.setString(string("SCORE: ") +
                to_string(hud.score));
            if (hud.seconds == 60) {
                hud.ig_timer.restart();
                hud.minute++;
            }
            hud.seconds = hud.ig_timer.getElapsedTime().asSeconds();
            if (hud.seconds < 10) {
                hud.display_ig_time.setString(string("TIMER: ") +
                    to_string(hud.minute) + ":0" + to_string(hud.seconds));
            } else {
                hud.display_ig_time.setString(string("TIMER: ") +
                    to_string(hud.minute) + ":" + to_string(hud.seconds));
            }
            // ================================================================

            // ============== DRAW ============================================
            if (!menu.play) {
                window.clear();
                menu.draw_all(window, hud.last_score);
            } else {
                window.clear();
                window.draw(player.sprite);
                window.draw(hud.display_health);
                window.draw(hud.display_ig_time);
                if (hud.show_crosshair) {
                    window.draw(hud.crosshair);
                }
                window.draw(hud.display_score);
                window.draw(hud.display_fps);
            }
            // ================================================================

            // ======================== PROJECTILE ============================
            projectile.start_position = sf::Vector2f(
                player.sprite.getPosition().x + player.sprite.getRadius(),
                player.sprite.getPosition().y + player.sprite.getRadius());
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (projectile.fire_delay.getElapsedTime().asSeconds() >=
                    0.3f) {
                    projectile.fire_delay.restart();
                    projectile.bullet.setPosition(projectile.start_position);
                    projectile.bullets.push_back(projectile.bullet);
                    projectile.direction.push_back(atan2(
                        sf::Mouse::getPosition(window).y -
                        player.sprite.getPosition().y,
                        sf::Mouse::getPosition(window).x -
                        player.sprite.getPosition().x));
                }

            }

            for (int i = 0; i < (int)projectile.bullets.size(); i++) {
                window.draw(projectile.bullets[i]);
                projectile.bullets[i].move(5.0f * cos(projectile.direction[i]),
                    5.0f * sin(projectile.direction[i]));

                if (projectile.bullets[i].getPosition().x > 
                    window.getSize().x ||
                    projectile.bullets[i].getPosition().x < 0 ||
                    projectile.bullets[i].getPosition().y < 0 ||
                    projectile.bullets[i].getPosition().y >
                    window.getSize().y) {
                    projectile.bullets.erase(projectile.bullets.begin() + i);
                    projectile.direction.erase(
                        projectile.direction.begin() + i);
                }
            }
            // ================================================================

            // ================= ENEMY ========================================
            if (enemy.perk == 5 && enemy.spawn_delay > 1.0) {
                enemy.perk = 0;
                enemy.spawn_delay-=0.1;
            }

            if (enemy.perk_two == 10 && enemy.speed_modifier < 3.0) {
                enemy.perk_two = 0;
                enemy.speed_modifier+=0.1;
            }

            if (enemy.spawn_timer.getElapsedTime().asSeconds() >=
                enemy.spawn_delay) {
                enemy.bot.setPosition(rand() % 1230, 0);
                enemy.bots.push_back(enemy.bot);
                enemy.direction.push_back(atan2(
                        player.sprite.getPosition().y -
                        enemy.bot.getPosition().y,
                        player.sprite.getPosition().x -
                        enemy.bot.getPosition().x));
                enemy.spawn_timer.restart();
            }

            for (int i = 0; i < (int)enemy.bots.size(); i++) {
                window.draw(enemy.bots[i]);
                enemy.direction[i] = atan2(
                    player.sprite.getPosition().y -
                    enemy.bots[i].getPosition().y,
                    player.sprite.getPosition().x -
                    enemy.bots[i].getPosition().x);
                enemy.bots[i].move(
                    enemy.speed_modifier * cos(enemy.direction[i]),
                    enemy.speed_modifier * sin(enemy.direction[i]));

                enemy.hitbox = enemy.bots[i].getGlobalBounds();
                player.hitbox = player.sprite.getGlobalBounds();

                if (player.hitbox.intersects(enemy.hitbox)) {
                    enemy.bots.erase(enemy.bots.begin() + i);
                    enemy.direction.erase(enemy.direction.begin() + i);
                    if (!player.invin) {
                        player.health--;
                    }
                }
            }
            // ================================================================

            // ================= COLLISION ====================================
            for (int i = 0; i < (int)projectile.bullets.size(); i++) {
                for (int j = 0; j < (int)enemy.bots.size(); j++) {
                    projectile.hitbox = projectile.bullets[i].getGlobalBounds();
                    player.hitbox = player.sprite.getGlobalBounds();

                    if (projectile.hitbox.intersects(enemy.hitbox)) {
                        projectile.bullets.erase(
                            projectile.bullets.begin() + i);
                        projectile.direction.erase(
                            projectile.direction.begin() + i);
                        enemy.bots.erase(enemy.bots.begin() + j);
                        enemy.direction.erase(enemy.direction.begin() + j);
                        hud.score++;
                        enemy.perk++;
                        enemy.perk_two++;

                        hud.last_score = hud.score;
                    }
                }
            }
            // ================================================================

            // ===================== AFTER-PROCESSING =========================
            window.display();
            input(player.sprite);
        } else if (hud.pause_ind && !hud.game_over_ind) {
            window.draw(hud.pause);
            window.display();
        } else {
            window.draw(hud.game_over);
            window.display();
        }
        // ====================================================================
    }
    // ========================================================================

    return 0;
}