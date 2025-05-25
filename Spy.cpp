#include "Spy.hpp"
#include "Game.hpp"
using namespace coup;
Spy::Spy(Game& g,std::string name):Player(g,name){
    g.addPlayer(this);
}
string Spy::getRole() const{
    return "Spy";
}
void Spy::BlockArresting(Player& pl){
    pl.setCanArrest(false);
}
int Spy::peek(Player& pl){
    return pl.coins();
}