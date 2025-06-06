//dotandanino@gmail.com
#include "../include/Baron.hpp"
#include "../include/Game.hpp"
using namespace coup;
using std::vector;
using std::string;
/**
 * @brief Baron constructor
 * @param g The game instance this player belongs to.
 * @param name The name of the player.
 */
Baron::Baron(Game& g,std::string name):Player(g,name){
    g.addPlayer(this);
}
/**
 * @brief Returns the role of the player.
 * @return The role of the player as a string.
 */
string Baron::getRole() const{
    return "Baron";
}
/**
 * @brief The Baron can invest 3 coins and gets 6 coins back.
 * @throw std::invalid_argument if it's not the player's turn.
 * @throw std::invalid_argument if the player has 10 coins or more (must coup instead).
 * @throw std::invalid_argument if the player doesn't have enough money to invest.
 */
void Baron::invest(){
    if(!(game.myTurn(this))){
        throw std::invalid_argument("its not your turn");
    }
    if(game.getPlayersList().size()<2){
        throw std::invalid_argument("you cant gather if there is no other players in the game");
    }
    if(this->money>=10){
        throw std::invalid_argument("you have to coup because you have 10 coins or more");
    }
    if(money<3){
        throw std::invalid_argument("you dont have enough money to invest");
    }
    money+=3; //like to spend 3 coins and get 6 coins back
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
/**
 * @brief Marks the Baron as under sanction, which means they cannot perform certain actions.
 * This is a special method because the Baron gets 1 coin when they are under sanction.
 */
void Baron::youAreUnderSanction() {
    this->underSanction = true;
    this->money+=1;
}
/**
 * @brief Returns a vector of available actions for the Baron. in use for the GUI
 * @return A vector of strings representing the actions the Baron can perform.
 */
vector<string> Baron::getAvailableActions() const {
    vector<string> actions= Player::getAvailableActions(); // Get actions from the base class
    actions.push_back("invest"); // Baron can invest
    return actions;
}