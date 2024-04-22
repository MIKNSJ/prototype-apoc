// ===== Established 2024-04-05 - 2024-XX-XX ====================
//
// Purpose: Functionality for the input of a mouse or keyboard
//
// ==============================================================



#include "Input.hpp"



/**
 * Generates sprite input
 * @param sprite The sprite.
 * @return nothing
*/
void input(sf::CircleShape& shape) {
    // move up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        shape.move(0.f, -2.5f);
    }

    // move down
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    // left key is pressed: move our character
        shape.move(0.f, 2.5f);
    }

    // move left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    // left key is pressed: move our character
        shape.move(-2.5f, 0.f);
    }

    // move right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    // left key is pressed: move our character
        shape.move(2.5f, 0.f);
    }
}