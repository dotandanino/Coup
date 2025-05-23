#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Game.hpp"
#include <iostream>
#include <string>
using namespace std;
namespace coup{
    class Player{
    protected:
      string name;//the name of the player
      int money;//the amount of money the player have
      Game& game;//the game this player belong to
      bool underSanction;//boolean var to say if this player is under sanction
      string lastAction;//string to save his last action for the undo method
      bool payForBribe;//to indicate if this player paid for 2 turns
      bool isAlive;//to know if we need to skip on him
      bool canArrest; //check if the player can arrest another player

    public:
        //all the comments here are on the standart functions if someone need special he override this function
        Player (Game& g,string name);//constructor
        virtual void gather();//take 1 coin from the bank cost: 0
        virtual void tax();//take 2 coins from the bank cost:0
        virtual void coup(Player& pl);//kick out another player from the game cost:7
        virtual int coins();//print the amount of money the player have
        virtual void bribe();//pay to get exrta turn cost:4
        virtual void arrest(Player& pl);//take 1 coin from the player cost:0
        virtual bool getArrestedBy(Player& pl);//this function is to get arrested by another player
        virtual string getName() const;//return the name of the player
        virtual string getRole() const =0;//return the role of the player this function is also to make sure the class will be absrtact
        string getLastAction() const;//return the last action of the player
        void undoBribe();//undo the bribe in case judge undo the action
        void setCanArrest(bool b);//set the player to be able to arrest another player
        void sanction(Player& pl);//put the player under sanction cost:3
        bool isUnderSanction() const;//return if the player is under sanction
        bool isStillAlive() const;//return if the player is alive
      };
}
#endif