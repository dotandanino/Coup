//dotandanino@gmail.com
#ifndef MERCHANT_HPP
#define MERCHANT_HPP

#include <iostream>
#include <string.h>
#include "Player.hpp"
using std::string;

using namespace std;
namespace coup{
    class Merchant:public Player{

        public:
            /**
             * @brief this function is the constructor of the Merchant class
             * @param g the game of the player
             * @param name the name of the player
             */        
            Merchant(Game& g,string name);

            /**
             * @brief this function is to get the role of the player
             * @return the role of the player
             */
            string getRole() const override;

            /**
             * @brief this function is to get arrested by another player special method because the mercahnt lose 2 coins
             * @return false because the Merchant never give coins to the arresting player
             */
            bool getArrested() override;

            /**
             * @brief this function is to announce that its the player's turn. we need this only for the Merchant because he get 1 coin every turn if he has 3 coins or more
             */
            void yourTurn() override;

            /**
             * @brief this function is to check if the player can be arrested. override because he need 2 coins
             * @return true if the player can be arrested, false otherwise
             */
            bool canBeArrested() const override;
    };
}
#endif