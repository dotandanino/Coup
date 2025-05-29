//dotandanino@gmail.com
#include "../hppFiles/Merchant.hpp"
#include "../hppFiles/Game.hpp"
using namespace coup;
using namespace std;
/**
 * @brief this function is the constructor of the Merchant class
 * @param g the game of the player
 * @param name the name of the player
 */
Merchant::Merchant(Game& g,string name):Player(g,name){
    g.addPlayer(this);
}
/**
 * @brief this function is to get the role of the player
 * @return the role of the player
 */
string Merchant::getRole() const{
    return "Merchant";
}
/**
 * @brief this function is to get arrested by another player special method because the mercahnt lose 2 coins
 * @return false because the Merchant never give coins to the arresting player
 */
bool Merchant::getArrested(){
    if(this->money<2){
            throw std::invalid_argument("the other player dont have enough money to pay for the arrest");
    }
    this->money-=2;
    this->game.setLastArrested(this->getName());
    return false;
}
/**
 * @brief this function is to announce that its the player's turn. we need this only for the Merchant because he get 1 coin every turn if he has 3 coins or more
 */
void Merchant::yourTurn(){
    if(!this->isAlive){
        throw std::invalid_argument("you are not alive");
    }
    if(this->money>=3){
        this->money++;
    }
}
/**
 * @brief this function is to check if the player can be arrested. override because he need 2 coins
 * @return true if the player can be arrested, false otherwise
 */
bool Merchant::canBeArrested() const{
    return(this->money>=2 && this->name != game.getLastArrested());
}