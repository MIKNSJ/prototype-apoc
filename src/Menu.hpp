// ===== Established 2024-04-22 - 2024-0X-0X =======
//
//  Functionality: Generates the menu of the game.
//
// =================================================



#pragma once
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
 * Menu class
*/
class Menu {
    public:
        int select;
        bool play;
        int max_score;

        Menu();
        void navigateUp(int &n);
        void navigateDown(int &n);
        void draw_all(sf::RenderWindow &window, int curr_score);
};