#include "Baron.hpp"
#include "Game.hpp"
using namespace coup;
Baron::Baron(Game& g,std::string name):Player(g,name){
    g.addPlayer(this);
}
string Baron::getRole() const{
    return "Baron";
}
void Baron::invest(){
    if(!(game.myTurn(this))){
        throw std::invalid_argument("its not your turn");
    }
    if(this->money>=10){
        throw std::invalid_argument("you have to coup because you have 10 coins or more");
    }
    if(money<3){
        throw std::invalid_argument("you dont have enough money to invest");
    }
    money+=3; // Baron invest 3 coins and gets 6 coins back
    if (this->payForBribe){
        this->payForBribe=false;
    }
    else{
        game.nextTurn();
    }
    underSanction=false;
    canArrest=true;
    this->lastAction="invest";
}
void Baron::youAreUnderSanction() {
    this->underSanction = true;
    this->money+=1;
}