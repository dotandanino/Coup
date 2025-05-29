//dotandanino@gmail.com
#include "../hppFiles/Judge.hpp"
#include "../hppFiles/Game.hpp"
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
    if(game.getPlayersList().size()<2){
        throw std::invalid_argument("you cant gather if there is no other players in the game");
    }
    if(player.getLastAction()!="bribe"){
        throw std::invalid_argument("you cant undo this action");
    }
    player.undoBribe();
}