#include "Baron.hpp"
#include "Game.hpp"
using namespace coup;
Baron::Baron(Game& g,std::string name):Player(g,name){
    g.addPlayer(this);
}
string Baron::getRole() const{
    return "Baron";
}