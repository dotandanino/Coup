#ifndef BARON_HPP
#define BARON_HPP

#include <iostream>
#include <string.h>
#include "Player.hpp"

using namespace std;
namespace coup{
    class Baron:public Player{

        public:
            Baron(Game& g,std::string name);
            string getRole() const override;
            void invest();
    };
}
#endif