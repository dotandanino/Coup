//dotandanino@gmail.com
#include "../hppFiles/Spy.hpp"
#include "../hppFiles/Game.hpp"
using namespace coup;
/**
 * @brief Constructor for the Spy class
 * @param g The game instance
 * @param name The name of the player
 */
Spy::Spy(Game& g,std::string name):Player(g,name){
    g.addPlayer(this);
}
/**
 * @brief Returns the role of the player
 * @return A string representing the role of the player
 */
string Spy::getRole() const{
    return "Spy";
}
/**
 * @brief This function is to block another player from arresting
 * @param pl The player to block from arresting
 */
void Spy::BlockArresting(Player& pl){
    if(game.getPlayersList().size()<2){
        throw std::invalid_argument("you cant gather if there is no other players in the game");
    }
    if(!pl.isStillAlive()){
        throw std::invalid_argument("you cant block arresting a dead player");
    }
    pl.setCanArrest(false);
}
/**
 * @brief This function allows the Spy to peek at another player's coins
 */
int Spy::peek(Player& pl){
    return pl.coins();
}
/**
 * @brief Get the available actions for the Spy player because he can blockArresting and peek
 * @return A vector of strings representing the available actions
 */
vector<string> Spy::getAvailableActions() const {
    vector<string> actions= Player::getAvailableActions(); // Get actions from the base class
    actions.push_back("blockArresting"); // Spy can block arresting
    actions.push_back("peek"); // Spy can peek at another player's coins
    return actions;
}