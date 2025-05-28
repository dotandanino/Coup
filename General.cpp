//dotandanino@gmail.com
#include "General.hpp"
#include "Game.hpp"
using namespace coup;
using namespace std;
General::General(Game& g,std::string name):Player(g,name){
    g.addPlayer(this);
}
string General::getRole() const{
    return "General";
}
bool General::getArrested(){
    this->game.setLastArrested(this->getName());
    return false;
}
void General::undo(Player&p){
    if(game.getLastAction()!="coup"){
        throw std::invalid_argument("you can undo only coup and only at the same time its happen");
    }
    if(p.isStillAlive()){
        throw std::invalid_argument("this player is already alive");
    }
    if(this->money<5){
        throw std::invalid_argument("you dont have enough money");
    }
    p.isAlive=true;
    this->money-=5;
    this->lastAction="undo";
    game.setLastAction("undo");
}
vector<string> General::getAvailableActions() const {
    vector<string> actions;
    actions.push_back("gather");
    actions.push_back("tax");
    actions.push_back("sanction");
    actions.push_back("arrest");
    actions.push_back("bribe");
    actions.push_back("coup");
    return actions;
}