#ifndef GUI_HPP
#define GUI_HPP

#include "../hppFiles/Player.hpp"
#include "../hppFiles/Governor.hpp"
#include "../hppFiles/Spy.hpp"
#include "../hppFiles/Baron.hpp"
#include "../hppFiles/General.hpp"
#include "../hppFiles/Judge.hpp"
#include "../hppFiles/Merchant.hpp"
#include "../hppFiles/Game.hpp"
#include "../hppFiles/playerFactory.hpp"
#include <sstream>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace coup;
void showWelcomeScreen(sf::Font& font);
int choose_player_screen(sf::Font& font);
std::vector<std::string> get_player_names_screen(sf::Font& font, int playerAmount);
void startGame(const std::vector<std::string>& playerNames,Game & game);
void showPlayerTurn(Game& game);
void showWinnerWindow(const std::string& winnerName);
string showCancelConfirmation(sf::RenderWindow& mainWindow, sf::Font& font, string name);
#endif