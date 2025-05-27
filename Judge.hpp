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
            Judge(Game& g,string name);
            string getRole() const override;
            void undo(Player& player);
            vector<string> getAvailableActions() const override;
    };
}

#endif