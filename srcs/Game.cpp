//dotandanino@gmail.com

#include "../include/Game.hpp"
#include "../include/Player.hpp"
using namespace coup;
using std::string;
/**
 * * @brief Game constructor
*/
Game::Game(){
    this->currentTurn=0;
    this->lastArrested="";
    this->lastGameAction="";
}

/**
 * @brief return the name of the players that are still in the game
 * @return vector with the names of the players
 */
vector<string> Game::players(){
    std::vector<string> names;
    for(size_t i=0;i<playersList.size();i++){
        if(playersList[i]->isStillAlive()){//we want to return only the players that are still alive
            names.push_back(playersList[i]->getName());
        }
    }
    return names;
}

/**
 * @brief return the name of the current player
 * @return the name of the current player
 * @throw std::invalid_argument if there are no players in the game
 */
string Game::turn(){
    if(playersList.size()==0){
        throw std::runtime_error("there is no players in the game");
    }
    return(playersList[currentTurn%playersList.size()]->getName());
}

/**
 * @brief move to the next player that is still alive and have an action to do
 */
void Game::nextTurn(){
    do{
        currentTurn+=1;
        currentTurn%=playersList.size();
    }while(!playersList[currentTurn]->isStillAlive() || playersList[currentTurn]->needSkip());
    playersList[currentTurn]->yourTurn();
}
/**
 * @brief add player to the game
 * @param p the player to add
 * @throw std::invalid_argument if the name is already in use
 * @throw std::runtime_error if there are already 6 players in the game
 */
void Game::addPlayer(Player* p){
    if (playersList.size()>=6){// check if there are already 6 players in the game
        throw std::runtime_error("you cant add more players to the game");
    }
    for(size_t i=0;i<playersList.size();i++){//check this name is not already in use
        if(playersList[i]->getName()==p->getName()){
            throw std::invalid_argument("this name is already in use in this game.");
        }
    }
    this->playersList.push_back(p);
}
/**
 * @brief check if its the players turn method in use for the player actions
 * @param p the player to check
 * @return true if its the players turn, false otherwise
 */
bool Game::myTurn(Player* p){
    return(turn()==p->getName());
}
/**
 * @brief return the name of the winner
 * @return the name of the winner
 * @throw std::runtime_error if there is no winner yet
 * @throw std::invalid_argument if there is no players in the game
 */
string Game::winner(){
    int alivePlayers=0;
    string name="";
    if(playersList.size()==0){
        throw std::invalid_argument("there is no players in the game");
    }
    for(size_t i=0;i<playersList.size();i++){//for to check how many players still alive
        if(playersList[i]->isStillAlive()){
            alivePlayers++;
            name=playersList[i]->getName();
        }
    }
    if(alivePlayers==1){//if there is 1 player alive
        return name;
    }
    throw std::runtime_error("there is no winner yet");
}
/**
 * @brief update the last arrested player
 * @param name the name of the last arrested player
 */
void Game::setLastArrested(string name){
    this->lastArrested=name;
}
/**
 * @brief return the name of the last arrested player
 * @return the name of the last arrested player
 */
string Game::getLastArrested() const{
    return this->lastArrested;
}

/**
 * @brief return the current player
 * @return the current player
 */
Player* Game::getCurrentPlayer(){
    return playersList[currentTurn];
}

/**
 * @brief return the list of all the players in the game (including dead players)
 * @return vector with the players in the game
 */
vector<Player*>& Game::getPlayersList() {
    return playersList;
}

/**
 * @brief return the last action of the game
 * @return the last action of the game
 */
string Game::getLastAction() const{
    return this->lastGameAction;
}

/**
 * @brief set the last action of the game
 * @param str the last action of the game
 */
void Game::setLastAction(string str){
    this->lastGameAction=str;
}