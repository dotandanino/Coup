//dotandanino@gmail.com
#include "../hppFiles/Governor.hpp"
#include "../hppFiles/Game.hpp"
//using namespace coup;
namespace coup{
    /**
     * @brief Constructor for the Governor class
     * @param g - the game instance
     * @param name - the name of the player
     */
    Governor::Governor(Game& g,std::string name):Player(g,name){
        g.addPlayer(this);
    }
    /**
     * @brief Returns the role of the player
     * @return the role of the player as a string
     */
    string Governor::getRole() const{
        return "Governor";
    }
    /**
     * @brief the governor can get 3 coins instead of 2
     * @throw std::invalid_argument if this is not his turn
     * @throw std::invalid_argument if the player is under sanction
     * @throw std::invalid_argument if the player have 10 coins or more
     */
    void Governor::tax(){
        if(!(game.myTurn(this))){
            throw std::invalid_argument("its not your turn");
        }
        if(underSanction){
            throw std::invalid_argument("you are under sanction");
        }
        if(this->money>=10){
            throw std::invalid_argument("you have to coup because you have 10 coins or more");
        }
        money+=3; // Governor takes 3 coins instead of 2

        if (this->payForBribe){
            this->payForBribe=false;
        }
        else{
            game.nextTurn();
        }
        underSanction=false;
        canArrest=true;
        this->lastAction="tax";
    }
    
    /**
     * @brief Undo the last action of another player (only tax)
     * @param p - the player we want to undo his tax
     * @throw std::invalid_argument if the last action of the player is not tax
     * @throw std::invalid_argument if the player doesn't have enough money to undo the tax
    */
    void Governor::undo(Player& p){
        if(p.getLastAction()!="tax"){
            throw std::invalid_argument("you cant undo this action");
        }
        if(p.getRole() == "Governor"){//governor recive 3 coins in tax and we need to reduce him extra coin
            if(p.coins()<=3){
                throw std::invalid_argument("this player didnt have enough money");
            }
            p.money -= 1; // tax og Governor is to take 3 coins and not only 2
        }
        if(p.coins()<=2){
            throw std::invalid_argument("this player didnt have enough money");
        }
        p.money -= 2; // Undo the tax action by removing 3 coins
        p.lastAction = ""; // Clear the last action to avoid another undo
        this->lastAction="undo";
        game.setLastAction("undo");
    }
}