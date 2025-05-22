#include "Governor.hpp"
#include "Game.hpp"
//using namespace coup;
namespace coup{

    Governor::Governor(Game& g,std::string name):Player(g,name){
        g.addPlayer(this);
    }
    string Governor::getRole() const{
        return "Governor";
    }
    void Governor::tax(){
        
    }
    void Governor::undo(Player& p){

    }
}