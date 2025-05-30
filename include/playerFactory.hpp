#ifndef FACTORY_HPP
#define FACTORY_HPP
#include "Player.hpp"
#include "Governor.hpp"
#include "Spy.hpp"
#include "Baron.hpp"
#include "General.hpp"
#include "Judge.hpp"
#include "Merchant.hpp"
#include "Game.hpp"
#include <vector>
using namespace coup;
using std::string;
/**
 * @brief this function creates a player according to the role and adds it to the playersList in use for the GUI.
 */
void CreatePlayer(Game&g ,const string name,string role,vector<Player*> & playersList);


#endif