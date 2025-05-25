#include "Player.hpp"
#include "Game.hpp"
namespace coup{
    //in alll the functions we check if the player paid for the bribe and
    // if so we just cancel the bribe and not change the turn
    
    
    /**
    @param g-the game of the player;
    @param name - the name of the player
    
    */
    Player::Player(Game& g,string name):name(name),game(g){
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
        this->isAlive=true;
        this->canArrest=true;
        lastAction="";
    }

    /**
     * @brief this function is to do gather action
     * @throw std::invalid_argument if this is not his turn
     * @throw std::invalid_argument if the player is under sanction
     * @throw std::invalid_argument if the player have 10 coins or more
     */
    void Player::gather(){
        if(!(game.myTurn(this))){
            throw std::invalid_argument("its not your turn");
        }
        if(underSanction){
            throw std::invalid_argument("you are under sanction");
        }
        if(this->money>=10){
            throw std::invalid_argument("you have to coup because you have 10 coins or more");
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
     * @brief this function is to get 2 coins from the bank
     * @throw std::invalid_argument if this is not his turn
     * @throw std::invalid_argument if the player is under sanction
     * @throw std::invalid_argument if the player have 10 coins or more
     */
    void Player::tax(){
        if(!(game.myTurn(this))){
            throw std::invalid_argument("its not your turn");
        }
        if(underSanction){
            throw std::invalid_argument("you are under sanction");
        }
        if(this->money>=10){
            throw std::invalid_argument("you have to coup because you have 10 coins or more");
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
    /**
     * @brief this function is to coup another player
     * @param pl - the player to coup
     * @throw std::invalid_argument if this is not his turn
     * @throw std::invalid_argument if the player is under sanction
     * @throw std::invalid_argument if the player have 10 coins or more
     */
    void Player::coup(Player& pl){
        if(!(game.myTurn(this))){
            throw std::invalid_argument("its not your turn");
        }
        if(this->money <7){
            throw std::runtime_error("you done have enough money for coup");
        }
        if(!(pl.isAlive)){
            throw std::invalid_argument("you cant coup someone that already couped");
        }
        if (this->payForBribe){
            this->payForBribe=false;
        }
        else{
            game.nextTurn();
        }
        this->money-=7;
        underSanction=false;
        canArrest=true;
        this->lastAction="coup";
        pl.isAlive=false;
    }
    /**
     * @brief this function is to get the amount of money the player have
     * @return the amount of money the player have
     */
    int Player::coins(){
        return this->money;
    }
    /**
     * @brief this function is for giving a player option to pay for bribe and get an extra turn
     * @throw std::invalid_argument if this is not his turn
     * @throw std::invalid_argument if the player have 10 coins or more
     */
    void Player::bribe(){
        if(!(game.myTurn(this))){
            throw std::invalid_argument("its not your turn");
        }
        if(this->money<4){
            throw std::invalid_argument("you dont have enough money to pay for the bribe");
        }
        if(this->money>=10){
            throw std::invalid_argument("you have to coup because you have 10 coins or more");
        }
        this->money-=4;
        this->payForBribe=true;
        this->lastAction="bribe";
    }
    /**
     * @brief this function is to arrest another player
     * @param pl - the player to arrest
     * @throw std::invalid_argument if this is not his turn
     * @throw std::invalid_argument if the player is last one that was arrested
     * @throw std::invalid_argument if the player have 10 coins or more
     * @throw std::invalid_argument if the player is blocked by the spy
     */
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
        if(pl.getArrested()){
            this->money+=1;
        }
        if(this->money>=10){
            throw std::invalid_argument("you have to coup because you have 10 coins or more");
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
    /**
     * @brief this function is to get arrested by another player the main reason for this function is for thw special case of the Merchant and the General
     * @param pl - the player that arrest you
     * @throw std::invalid_argument if arrested player dont have enough money
     */
    bool Player::getArrested(){
        if(this->money<1){
            throw std::invalid_argument("you dont have enough money to pay for the arrest");
        }
        this->money-=1;
        this->game.setLastArrested(this->getName());
        return true;
    }
    
    /**
     * @brief this function is to get the name of the player
     * @return the name of the player
     */
    string Player::getName() const{
        return this->name;
    }
    
    /**
     * @brief this function is to get the role of the player
     * @return the role of the player
     */
    string Player::getLastAction() const{
        return this->lastAction;
    }
    /**
     * @brief this function is for the judge option to undo the bribe
     */
    void Player::undoBribe(){
        this->payForBribe=false;
    }

    /**
     * @brief this function is for the spy option to block a player from arresting
     * @param b - the boolean value to set the canArrest variable
     */
    void Player::setCanArrest(bool b){
        this->canArrest=b;
    }
    
    /**
     * @brief this function is to put a player under sanction
     * @param pl - the player to put under sanction
     */
    void Player::sanction(Player& pl){
        if(!(game.myTurn(this))){
            throw std::invalid_argument("its not your turn");
        }
        if(!(pl.isAlive)){
            throw std::invalid_argument("you cant coup someone that already couped");
        }
        if(this->money<3){
            throw std::invalid_argument("you dont have enough money");
        }
        if(pl.underSanction){
            throw std::invalid_argument("this player is already under sanction");
        }
        if(this->money>=10){
            throw std::invalid_argument("you have to coup because you have 10 coins or more");
        }
        pl.youAreUnderSanction();
        this->money-=3;
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
        this->lastAction="sanction";
    }
    
    /**
     * @brief this function is to check if someone is under sanction
     * @return true if the player is under sanction
     * @return false if the player is not under sanction
     */
    bool Player::isUnderSanction() const{
        return this->underSanction;
    }
    /**
     * @brief this function is to check if the player is still alive
     * @return true if the player is still alive
     * @return false if the player is not alive
     */
    bool Player::isStillAlive() const{
        return(this->isAlive);
    }
    void Player::youAreUnderSanction(){
        this->underSanction=true;
    }
}