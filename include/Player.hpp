//dotandanino@gmail.com
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Game.hpp"
#include <iostream>
#include <string>
using namespace std;
namespace coup{
    class Governor;
    class General;
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
        //all the comments here are on the base functions if someone need special he override this function
        
        /**
        * @param g-the game of the player;
        * @param name - the name of the player   
        */
        Player (Game& g,string name);


        
         /**
         * @brief this function is to do gather action
         * @throw std::invalid_argument if this is not his turn
         * @throw std::invalid_argument if the player is under sanction
         * @throw std::invalid_argument if the player have 10 coins or more
         */
        virtual void gather();

        /**
         * @brief this function is to get 2 coins from the bank
         * @throw std::invalid_argument if this is not his turn
         * @throw std::invalid_argument if the player is under sanction
         * @throw std::invalid_argument if the player have 10 coins or more
         */
        virtual void tax();
        
        /**
         * @brief this function is to coup another player
         * @param pl - the player to coup
         * @throw std::invalid_argument if this is not his turn
         * @throw std::invalid_argument if the player is under sanction
         * @throw std::invalid_argument if the player have 10 coins or more
        */
        virtual void coup(Player& pl);
        
        /**
         * @brief this function is to get the amount of money the player have
         * @return the amount of money the player have
         */
        virtual int coins();
        
         /**
         * @brief this function is for giving a player option to pay for bribe and get an extra turn
         * @throw std::invalid_argument if this is not his turn
         * @throw std::invalid_argument if the player have 10 coins or more
         */
        virtual void bribe();
        
        /**
         * @brief this function is to arrest another player
         * @param pl - the player to arrest
         * @throw std::invalid_argument if this is not his turn
         * @throw std::invalid_argument if the player is last one that was arrested
         * @throw std::invalid_argument if the player have 10 coins or more
         * @throw std::invalid_argument if the player is blocked by the spy
         */
        virtual void arrest(Player& pl);
        
        /**
         * @brief this function is to get arrested by another player the main reason for this function is for thw special case of the Merchant and the General
         * @param pl - the player that arrest you
         * @return true if the arresting player need to recive coin
         * @throw std::invalid_argument if arrested player dont have enough money
         */
        virtual bool getArrested();
        
        /**
         * @brief this function is to get the name of the player
         * @return the name of the player
         */
        virtual string getName() const;
        
        /**
         * @brief this function is to get the role of the player
         * @return the role of the player
         */
        virtual string getRole() const =0;
        
         /**
         * @brief this function is to get the last action of the player
         * @return the last action of the player
         */
        string getLastAction() const;
        
        /**
         * @brief this function is for the judge option to undo the bribe
         */
        void undoBribe();
        
        /**
         * @brief this function is for the spy option to block a player from arresting
         * @param b - the boolean value to set the canArrest variable
         */
        void setCanArrest(bool b);
        
        /**
         * @brief this function is to put a player under sanction
         * @param pl - the player to put under sanction
         */
        void sanction(Player& pl);
        
        /**
         * @brief this function is to check if someone is under sanction
         * @return true if the player is under sanction
         * @return false if the player is not under sanction
         */
        bool isUnderSanction() const;
        
        /**
         * @brief this function is to check if the player is still alive
         * @return true if the player is still alive
         * @return false if the player is not alive
         */
        bool isStillAlive() const;
        
        /**
         * @brief this function is to announce that the player is under sanction
         */
        virtual void youAreUnderSanction();

        /**
         * @brief this function is to announce that its the player's turn i need this only for the Merchant
         */
        virtual void yourTurn();// Ensure the player is alive before taking an action
        
        /**
         * @brief // Virtual destructor for the class because it has virtual functions
         */
        virtual ~Player() = default;
        /**
         * @brief Disable copy assignment operator and copy constructor
         */
        Player& operator= (const Player& other)=delete;
        /**
         * @brief Disable copy constructor
         */
        Player(const Player& other) = delete;

        /**
         * @brief this function is to check if the player need to skip his turn
         * @return true if the player need to skip his turn
         * @return false if the player dont need to skip his turn
         * @note the player need to skip his turn if he is under sanction and have less than 3 coins and cant arrest any other player
         */
        bool needSkip();
        /**
         * @brief this function is to check if the player can be arrested
         * @return true if the player can be arrested
         * @return false if the player cant be arrested
         * @note the player can be arrested if he has at least 1 coin and is not the last arrested player expect the Merchant that can be arrested if he has at least 2 coins
         */
        virtual bool canBeArrested() const;

        /**
         * @brief Get the available actions for the player in use for the GUI and no one contain undo because I undo on live.
         */
        virtual vector<string> getAvailableActions() const;
        friend class Governor; // Allow Governor to access private members
        friend class General;
    };
}
#endif