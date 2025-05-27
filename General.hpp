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
            General(Game& g,std::string name);
            string getRole() const override;
            bool getArrested() override;
            vector<string> getAvailableActions() const override;
            void undo(Player& p);
    };
}
#endif