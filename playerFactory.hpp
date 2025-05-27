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
using namespace coup;
using std::string;
void CreatePlayer(Game&g ,const string name,string role,vector<Player*> & playersList);


#endif