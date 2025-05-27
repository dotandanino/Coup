//dotandanino@gmail.com
#include "Baron.hpp"
#include "Game.hpp"
using namespace coup;
using std::vector;
using std::string;
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
    game.setLastAction("invest");
}
void Baron::youAreUnderSanction() {
    this->underSanction = true;
    this->money+=1;
}
vector<string> Baron::getAvailableActions() const {
    vector<string> actions;
    actions.push_back("gather");
    actions.push_back("tax");
    actions.push_back("sanction");
    actions.push_back("arrest");
    actions.push_back("bribe");
    actions.push_back("coup");
    actions.push_back("invest"); // Baron can invest
    return actions;
}