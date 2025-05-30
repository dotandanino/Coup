#ifndef GUI_HPP
#define GUI_HPP

#include "../include/Player.hpp"
#include "../include/Governor.hpp"
#include "../include/Spy.hpp"
#include "../include/Baron.hpp"
#include "../include/General.hpp"
#include "../include/Judge.hpp"
#include "../include/Merchant.hpp"
#include "../include/Game.hpp"
#include "../include/playerFactory.hpp"
#include <sstream>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace coup;
void showWelcomeScreen(sf::Font& font);
int choose_player_screen();
std::vector<std::string> get_player_names_screen(sf::Font& font, int playerAmount);
void startGame(const std::vector<std::string>& playerNames,Game & game);
void showPlayerTurn(Game& game);
void showWinnerWindow(const std::string& winnerName);
string showCancelConfirmation(sf::RenderWindow& mainWindow, sf::Font& font, string name);
#endif