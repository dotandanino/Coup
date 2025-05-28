//dotandanino@gmail.com
#include "Judge.hpp"
#include "Game.hpp"
using namespace coup;
/**
 * @brief Judge constructor
 * @param g - the game of the player
 * @param name - the name of the player
 */
Judge::Judge(Game& g,std::string name):Player(g,name){
    g.addPlayer(this);
}
/**
 * @brief this function is to get the role of the player
 * @return the role of the player
 */
string Judge::getRole() const{
    return "Judge";
}
/**
 * @brief this function is to undo the last action of the player in case the last action was bribe
 * @param player - the player to undo his bribe
 * @throw std::invalid_argument if the last action is not bribe
 */
void Judge::undo(Player& player){
    if(player.getLastAction()!="bribe"){
        throw std::invalid_argument("you cant undo this action");
    }
    player.undoBribe();
}
vector<string> Judge::getAvailableActions() const {
        vector<string> actions;
        actions.push_back("gather");
        actions.push_back("tax");
        actions.push_back("sanction");
        actions.push_back("arrest");
        actions.push_back("bribe");
        actions.push_back("coup");
        return actions;
    }