//dotandanino@gmail.com
#ifndef JUDGE_HPP
#define JUDGE_HPP

#include <iostream>
#include <string.h>
#include "Player.hpp"
using std::string;

using namespace std;
namespace coup{
    class Judge:public Player{

        public:
            /**
             * @brief Judge constructor
             * @param g - the game of the player
             * @param name - the name of the player
             */
            Judge(Game& g,string name);

            /**
             * @brief this function is to get the role of the player
             * @return the role of the player
             */
            string getRole() const override;

            /**
             * @brief this function is to undo the last action of the player in case the last action was bribe
             * @param player - the player to undo his bribe
             * @throw std::invalid_argument if the last action is not bribe
             */
            void undo(Player& player);
    };
}

#endif