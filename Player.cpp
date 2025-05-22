#include "Player.hpp"
#include "Game.hpp"
namespace coup{

    /**
    @param g-the game of the player;
    @param name - the name of the player
    
    */
    Player::Player(Game& g,string name):game(g){
        vector<string> names=g.players();
        if(names.size()>=6){
            throw std::runtime_error("you cant add more players to the game");
        }
        bool isInside = false;
        for(string n:names){
            if(n==name){
                isInside=true;
                break;
            }
        }
        if(isInside){
            throw std::invalid_argument("this name is already in use in this game.");
        }
        this->game=g;
        this->name = name;
        this->money=0;
        this->underSanction=false;
        this->payForBribe=false;
        this->isDeath=false;
        this->canArrest=true;
        lastAction="";
    }
    string Player::getName() const{
        return this->name;
    }
    /**
     * @brief this function is to do gather action
     * @throw std::invalid_argument if this is not his turn
     * @throw std::invalid_argument if the player is under sanction
     */
    void Player::gather(){
        if(!(game.myTurn(this))){
            throw std::invalid_argument("its not your turn");
        }
        if(underSanction){
            throw std::invalid_argument("you are under sanction");
        }
        money+=1;
        if (this->payForBribe){
            this->payForBribe=false;
        }
        else{
            game.nextTurn();
            underSanction=false;
            canArrest=true;
        }
        underSanction=false;
        canArrest=true;
        this->lastAction="gather";
    }
    /**
     * @brief this function is to get the role of the player
     * @return the role of the player
     * @throw std::invalid_argument if this is not his turn
     * @throw std::invalid_argument if the player is under sanction
     */
    void Player::tax(){
        if(!(game.myTurn(this))){
            throw std::invalid_argument("its not your turn");
        }
        if(underSanction){
            throw std::invalid_argument("you are under sanction");
        }
        money+=2;

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
    int Player::coins(){
        return this->money;
    }
    void Player::coup(Player& pl){




    }
    void Player::arrest(Player& pl){
        if(!(game.myTurn(this))){
            throw std::invalid_argument("its not your turn");
        }
        if(game.getLastArrested()==pl.getName()){
            throw std::invalid_argument("you cant arrest the same player twice in a row");
        }
        if(!this->canArrest){
            throw std::invalid_argument("you cant arrest this turn");
        }
        if(pl.getArrestedBy(*this)){
            this->money+=1;
        }
        if (this->payForBribe){
            this->payForBribe=false;
        }
        else{
            game.nextTurn();
        }
        underSanction=false;
        canArrest=true;
        this->lastAction="arrest";
    }
    bool Player::getArrestedBy(Player& pl){
        if(this->money<1){
            throw std::invalid_argument("you dont have enough money to pay for the arrest");
        }
        this->money-=1;
        this->game.setLastArrested(this->getName());
        return true;
    }
    string Player::getLastAction() const{
        return this->lastAction;
    }
    void Player::undoBribe(){
        this->payForBribe=false;
    }
    void Player::bribe(){
        if(!(game.myTurn(this))){
            throw std::invalid_argument("its not your turn");
        }
        if(this->money<4){
            throw std::invalid_argument("you dont have enough money to pay for the bribe");
        }
        this->money-=4;
        this->payForBribe=true;
        this->lastAction="bribe";
    }

    void Player::setCanArrest(bool b){
        this->canArrest=b;
    }
} 