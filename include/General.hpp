//dotandanino@gmail.com
#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <iostream>
#include <string.h>
#include "Player.hpp"
using std::string;
namespace coup{
    class General:public Player{

        public:
            /**
             * @brief General constructor
             * @param g the game this player belong to
             * @param name the name of the player
             */
            General(Game& g,std::string name);

            /**
             * @brief Get the role of the player
             * @return the role of the player
             */
            string getRole() const override;

            /**
             * @brief Get arrested by another player
             * @return false, as if someone arrest general he dont need to get the coin because the general get the coin back
             */
            bool getArrested() override;

            /**
             * @brief Undo the last action of the player (only if its coup)
             * @param p the player to undo
             * @throw std::invalid_argument if the last action is not a coup
             * @throw std::invalid_argument if the other player is still alive
             * @throw std::invalid_argument if the player doesn't have enough money
             */
            void undo(Player& p);
    };
}
#endif