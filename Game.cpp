#include "Game.hpp"
#include "Player.hpp"
using namespace coup;
using std::string;
Game::Game(){
    this->currentTurn=0;
    this->lastArrested="";
}
void Game::addPlayer(Player* p){
    this->playersList.push_back(p);
}
vector<string> Game::players(){
    std::vector<string> names;
    for(size_t i=0;i<playersList.size();i++){
        names.push_back(playersList[i]->getName());
    }
    return names;
}
string Game::turn(){
    return(playersList[currentTurn%playersList.size()]->getName());
}
bool Game::myTurn(Player* p){
    return(turn()==p->getName());
}
void Game::nextTurn(){
    currentTurn+=1;
    currentTurn%=playersList.size();
}
void Game::setLastArrested(string name){
    this->lastArrested=name;
}
string Game::getLastArrested() const{
    return this->lastArrested;
}