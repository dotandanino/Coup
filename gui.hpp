#ifndef GUI_HPP
#define GUI_HPP

#include "Player.hpp"
#include "Governor.hpp"
#include "Spy.hpp"
#include "Baron.hpp"
#include "General.hpp"
#include "Judge.hpp"
#include "Merchant.hpp"
#include "Game.hpp"
#include "playerFactory.hpp"
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

#endif