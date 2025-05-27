//dotandanino@gmail.com
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
vector<string> Spy::getAvailableActions() const {
    vector<string> actions;
    actions.push_back("gather");
    actions.push_back("tax");
    actions.push_back("sanction");
    actions.push_back("arrest");
    actions.push_back("bribe");
    actions.push_back("coup");
    actions.push_back("blockArresting"); // Spy can block arresting
    actions.push_back("peek"); // Spy can peek at another player's coins
    return actions;
}