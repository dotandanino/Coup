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
            Baron(Game& g,std::string name);
            string getRole() const override;
            void invest();
            void youAreUnderSanction() override;
            vector<string> getAvailableActions() const override;
    };
}
#endif