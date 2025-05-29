//dotandanino@gmail.com
#include "../hppFiles/General.hpp"
#include "../hppFiles/Game.hpp"
using namespace coup;
using namespace std;
/**
 * @brief General constructor
 * @param g the game this player belong to
 * @param name the name of the player
 */
General::General(Game& g,std::string name):Player(g,name){
    g.addPlayer(this);
}
/**
 * @brief Get the role of the player
 * @return the role of the player
 */
string General::getRole() const{
    return "General";
}
/**
 * @brief Get arrested by another player
 * @return false, as if someone arrest general he dont need to get the coin because the general get the coin back
 */
bool General::getArrested(){
    this->game.setLastArrested(this->getName());
    return false;
}

/**
 * @brief Undo the last action of the player (only if its coup)
 * @param p the player to undo
 * @throw std::invalid_argument if the last action is not a coup
 * @throw std::invalid_argument if the other player is still alive
 * @throw std::invalid_argument if the player doesn't have enough money
 */
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