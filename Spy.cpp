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
    if(!(game.myTurn(this))){
        throw std::invalid_argument("its not your turn");
    }
    pl.setCanArrest(false);
}
int Spy::peek(Player& pl){
    if(!(game.myTurn(this))){
        throw std::invalid_argument("its not your turn");
    }
    return pl.coins();
}