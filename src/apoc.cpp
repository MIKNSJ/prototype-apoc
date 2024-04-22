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

        Player() : sprite(25.f), hitbox(), position(), health(100) {
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
    
    Projectile() : fire_delay(), bullet(5.0f), bullets(), direction(), hitbox(),
    start_position() {
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
        int score;

        HUD(sf::RenderWindow &window) : font(), crosshair(5.f), fps_timer(),
            ig_timer(), display_ig_time(), minute(0), seconds(0), display_fps(),
            display_health(), display_score(), score(0) {

            // Setup the default font of this game: Source Code Pro.
            if (!font.loadFromFile("../assets/scpro.ttf")) {
                cout << "The required font has failed to load." << endl;
                window.close();
            }

            crosshair.setFillColor(sf::Color::Red);

            display_fps.setFont(font);
            display_fps.setFillColor(sf::Color::Blue);
            display_fps.setPosition(1045, 650);

            display_ig_time.setFont(font);
            display_ig_time.setFillColor(sf::Color::Blue);
            display_ig_time.setPosition(1045, 600);

            display_health.setFont(font);
            display_health.setFillColor(sf::Color::Blue);
            display_health.setPosition(50, 600);

            display_score.setFont(font);
            display_score.setFillColor(sf::Color::Blue);
            display_score.setPosition(50, 650);
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
    Projectile projectile;
    HUD hud(window);
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
        }
        // ====================================================================

        // ===================== SPRITE/PLAYER ================================
        // ==================== PLAYER BOUNDARIES =============================
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
        // ====================================================================
        // ====================================================================

        // ====================== HUD =========================================
        hud.display_health.setString(string("HP: ") + to_string(player.health));
        hud.crosshair.setPosition(sf::Mouse::getPosition(window).x,
            sf::Mouse::getPosition(window).y);
        hud.display_fps.setString("FPS: " +
            to_string(1.0f / hud.fps_timer.getElapsedTime().asSeconds()));
        hud.fps_timer.restart();
        hud.display_score.setString(string("SCORE: ") + to_string(hud.score));
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
        // ====================================================================

        // ============== DRAW ================================================
        window.clear();
        window.draw(player.sprite);
        window.draw(hud.display_health);
        window.draw(hud.display_ig_time);
        window.draw(hud.crosshair);
        window.draw(hud.display_score);
        window.draw(hud.display_fps);
        // ====================================================================

        // ======================== PROJECTILE ================================
        projectile.start_position = sf::Vector2f(
            player.sprite.getPosition().x + player.sprite.getRadius(),
            player.sprite.getPosition().y + player.sprite.getRadius());
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (projectile.fire_delay.getElapsedTime().asSeconds() >= 0.3f) {
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

            if (projectile.bullets[i].getPosition().x > window.getSize().x ||
                projectile.bullets[i].getPosition().x < 0 ||
                projectile.bullets[i].getPosition().y < 0 ||
                projectile.bullets[i].getPosition().y > window.getSize().y) {
                projectile.bullets.erase(projectile.bullets.begin() + i);
                projectile.direction.erase(projectile.direction.begin() + i);
            }
        }
        // ====================================================================

        // ================= ENEMY ============================================
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
                    player.sprite.getPosition().y - enemy.bot.getPosition().y,
                    player.sprite.getPosition().x - enemy.bot.getPosition().x));
            enemy.spawn_timer.restart();
        }

        for (int i = 0; i < (int)enemy.bots.size(); i++) {
            window.draw(enemy.bots[i]);
            enemy.direction[i] = atan2(
                player.sprite.getPosition().y - enemy.bots[i].getPosition().y,
                player.sprite.getPosition().x - enemy.bots[i].getPosition().x);
            enemy.bots[i].move(enemy.speed_modifier * cos(enemy.direction[i]),
                enemy.speed_modifier * sin(enemy.direction[i]));

            enemy.hitbox = enemy.bots[i].getGlobalBounds();
            player.hitbox = player.sprite.getGlobalBounds();
            if (player.hitbox.intersects(enemy.hitbox)) {
                enemy.bots.erase(enemy.bots.begin() + i);
                enemy.direction.erase(enemy.direction.begin() + i);
                player.health--;
            }
        }
        // ====================================================================

        // ================= COLLISION ========================================
        for (int i = 0; i < (int)projectile.bullets.size(); i++) {
            for (int j = 0; j < (int)enemy.bots.size(); j++) {
                projectile.hitbox = projectile.bullets[i].getGlobalBounds();
                player.hitbox = player.sprite.getGlobalBounds();

                if (projectile.hitbox.intersects(enemy.hitbox)) {
                    projectile.bullets.erase(projectile.bullets.begin() + i);
                    projectile.direction.erase(
                        projectile.direction.begin() + i);
                    enemy.bots.erase(enemy.bots.begin() + j);
                    enemy.direction.erase(enemy.direction.begin() + j);
                    hud.score++;
                    enemy.perk++;
                    enemy.perk_two++;
                }
            }
        }
        // ====================================================================

        // ===================== AFTER-PROCESSING =============================
        window.display();
        input(player.sprite);
    }
    // ========================================================================

    return 0;
}