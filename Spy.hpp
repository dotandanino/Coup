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
            Spy(Game& g,string name);
            string getRole() const override;
            void BlockArresting(Player& pl);
            int peek(Player& pl);
            vector<string> getAvailableActions() const override;
    };
}
#endif