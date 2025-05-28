//dotandanino@gmail.com
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
void Merchant::yourTurn(){
    if(!this->isAlive){
        throw std::invalid_argument("you are not alive");
    }
    if(this->money>=3){
        this->money++;
    }
}
vector<string> Merchant::getAvailableActions() const {
    vector<string> actions;
    actions.push_back("gather");
    actions.push_back("tax");
    actions.push_back("sanction");
    actions.push_back("arrest");
    actions.push_back("bribe");
    actions.push_back("coup");
    return actions;
}
bool Merchant::canBeArrested() const{
    return(this->money>=2 && this->name != game.getLastArrested());
}