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