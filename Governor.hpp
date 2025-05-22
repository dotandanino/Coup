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
            Governor(Game& g,string name);
            string getRole() const override;
            virtual void tax() override;
            void undo(Player& player);
    };
}

#endif