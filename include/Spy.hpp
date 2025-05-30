//dotandanino@gmail.com
#ifndef SPY_HPP
#define SPY_HPP

#include <iostream>
#include <string.h>
#include "Player.hpp"

using namespace std;
namespace coup{
    class Spy:public Player{

        public:
            /**
             * @brief Constructor for the Spy class
             * @param g The game instance
             * @param name The name of the player
             */
            Spy(Game& g,string name);

            /**
             * @brief Returns the role of the player
             * @return A string representing the role of the player
             */
            string getRole() const override;

            /**
             * @brief This function is to block another player from arresting
             * @param pl The player to block from arresting
             */
            void BlockArresting(Player& pl);

            /**
             * @brief This function allows the Spy to peek at another player's coins
             */
            int peek(Player& pl);

            /**
             * @brief Get the available actions for the Spy player because he can blockArresting and peek
             * @return A vector of strings representing the available actions
             */
            vector<string> getAvailableActions() const override;
    };
}
#endif