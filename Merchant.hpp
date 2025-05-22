#ifndef MERCHANT_HPP
#define MERCHANT_HPP

#include <iostream>
#include <string.h>
#include "Player.hpp"
using std::string;

using namespace std;
namespace coup{
    class Merchant:public Player{

        public:
            Merchant(Game& g,string name);
            string getRole() const override;
            bool getArrestedBy(Player& pl) override;
    };
}
#endif