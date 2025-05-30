//dotandanino@gmail.com
#ifndef BARON_HPP
#define BARON_HPP

#include <iostream>
#include <string.h>
#include "Player.hpp"
using std::vector;
using std::string;
namespace coup{
    class Baron:public Player{

        public:
            /**
             * @brief Baron constructor
             * @param g The game instance this player belongs to.
             * @param name The name of the player.
             */
            Baron(Game& g,std::string name);

            /**
             * @brief Returns the role of the player.
             * @return The role of the player as a string.
             */
            string getRole() const override;

            /**
             * @brief The Baron can invest 3 coins and gets 6 coins back.
             * @throw std::invalid_argument if it's not the player's turn.
             * @throw std::invalid_argument if the player has 10 coins or more (must coup instead).
             * @throw std::invalid_argument if the player doesn't have enough money to invest.
             */
            void invest();

            /**
             * @brief Marks the Baron as under sanction, which means they cannot perform certain actions.
             * This is a special method because the Baron gets 1 coin when they are under sanction.
             */
            void youAreUnderSanction() override; //special method because he get 1 coin when he is under sanction
            /**
             * @brief Returns a vector of available actions for the Baron. in use for the GUI
             * @return A vector of strings representing the actions the Baron can perform.
             */
            vector<string> getAvailableActions() const override;// Returns a vector of available actions for the Baron override to add invest.
    };
}
#endif