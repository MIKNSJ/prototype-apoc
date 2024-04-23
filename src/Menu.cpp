// ===== Established 2024-04-22 - 2024-0X-0X =======
//
//  Functionality: Generates the menu of the game.
//
// =================================================



#include "Menu.hpp"



/**
 * Menu class
*/
sf::Font font;
sf::Text title;
sf::Text score;
sf::Text max_score_txt;
vector<sf::Text> options_list(2);

Menu::Menu(float width, float height) : select(-1),
    play(false), max_score(-1) {
    // Setup the default font of this menu: Source Code Pro.
    if (!font.loadFromFile("../assets/scpro.ttf")) {
        cout << "The required font has failed to load." << endl;
    }

    title.setFont(font);
    title.setString("prototype-apoc");
    title.setCharacterSize(75);
    title.setFillColor(sf::Color::White);
    title.setPosition(320, 50);

    options_list[0].setFont(font);
    options_list[0].setString("Play");
    options_list[0].setCharacterSize(35);
    options_list[0].setFillColor(sf::Color::White);
    options_list[0].setPosition(600, 400);

    options_list[1].setFont(font);
    options_list[1].setString("Exit");
    options_list[1].setCharacterSize(35);
    options_list[1].setFillColor(sf::Color::White);
    options_list[1].setPosition(600, 500);
}



/**
 * Draws menu
 * @param window The window
 * @return nothing
*/
void Menu::draw_all(sf::RenderWindow &window, int curr_score) {
    window.draw(title);

    if (max_score < curr_score) {
        max_score = curr_score;
    }
    score.setFont(font);
    score.setString(string("Last Score: ") + to_string(curr_score));
    score.setFillColor(sf::Color::White);
    score.setPosition(900, 600);
    max_score_txt.setFont(font);
    max_score_txt.setString(string("Max Score: ") + to_string(max_score));
    max_score_txt.setFillColor(sf::Color::White);
    max_score_txt.setPosition(900, 650);
    window.draw(score);
    window.draw(max_score_txt);

    for (int i = 0; i < (int)options_list.size(); i++) {
        window.draw(options_list[i]);
    }
}



/**
* Move cursor up
* @param n The menu option
* @return nothing
*/
void Menu::navigateUp(int &n) {
    if (n == -1) {
        options_list[0].setFillColor(sf::Color::Red);
        n++;
    } else if (n == 1) {
        options_list[1].setFillColor(sf::Color::White);
        options_list[0].setFillColor(sf::Color::Red);
        n = 0;
    } else {
        options_list[0].setFillColor(sf::Color::White);
        options_list[1].setFillColor(sf::Color::Red);
        n = 1;
    }
}



/**
* Move cursor down
* @param n The menu option
* @return nothing
*/
void Menu::navigateDown(int &n) {
    if (n == -1) {
        options_list[0].setFillColor(sf::Color::Red);
        n++;
    } else if (n == 0) {
        options_list[0].setFillColor(sf::Color::White);
        options_list[1].setFillColor(sf::Color::Red);
        n = 1;
    } else {
        options_list[1].setFillColor(sf::Color::White);
        options_list[0].setFillColor(sf::Color::Red);
        n = 0;
    }
}