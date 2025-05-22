#include "Judge.hpp"
#include "Game.hpp"
using namespace coup;

Judge::Judge(Game& g,std::string name):Player(g,name){
    g.addPlayer(this);
}
string Judge::getRole() const{
    return "Judge";
}
void Judge::undo(Player& player){
    if(player.getName()!=this->game.turn()){
        throw std::invalid_argument("its not your turn");
    }
    if(player.getLastAction()!="bribe"){
        throw std::invalid_argument("you cant undo this action");
    }
}