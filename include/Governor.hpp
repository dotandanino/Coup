//dotandanino@gmail.com
#ifndef GOVERNOR_HPP
#define GOVERNOR_HPP
#include "Player.hpp"
#include <iostream>
#include <string>
using std::string;


namespace coup{
    class Game;
    class Governor:public Player{

        public:
            /**
             * @brief Constructor for the Governor class
             * @param g - the game instance
             * @param name - the name of the player
             */
            Governor(Game& g,string name);

            /**
             * @brief Returns the role of the player
             * @return the role of the player as a string
             */
            string getRole() const override;

            /**
             * @brief the governor can get 3 coins instead of 2
             * @throw std::invalid_argument if this is not his turn
             * @throw std::invalid_argument if the player is under sanction
             * @throw std::invalid_argument if the player have 10 coins or more
            */
            virtual void tax() override;

            /**
             * @brief Undo the last action of another player (only tax)
             * @param p - the player we want to undo his tax
             * @throw std::invalid_argument if the last action of the player is not tax
             * @throw std::invalid_argument if the player doesn't have enough money to undo the tax
            */
            void undo(Player& player);
    };
}

#endif