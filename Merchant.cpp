#include "Merchant.hpp"
#include "Game.hpp"
using namespace coup;
using namespace std;
Merchant::Merchant(Game& g,string name):Player(g,name){
    g.addPlayer(this);
}
string Merchant::getRole() const{
    return "Merchant";
}
bool Merchant::getArrested(){
    if(this->money<2){
            throw std::invalid_argument("you dont have enough money to pay for the arrest");
    }
    this->money-=2;
    this->game.setLastArrested(this->getName());
    return false;
}