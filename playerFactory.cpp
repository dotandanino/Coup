#include "playerFactory.hpp"

void CreatePlayer(Game&g ,const string name,string role,vector<Player*> & playersList){
    if(role=="Governor"){
        playersList.push_back(new Governor(g,name));
    }
    else if(role=="Spy"){
        playersList.push_back(new Spy(g,name));
    }
    else if(role=="Baron"){
        playersList.push_back(new Baron(g,name));
    }
    else if(role=="General"){
        playersList.push_back(new General(g,name));
    }
    else if(role=="Judge"){
        playersList.push_back(new Judge(g,name));
    }
    else if(role=="Merchant"){
        playersList.push_back(new Merchant(g,name));
    }
    else{
        throw std::invalid_argument("this role is not valid");
    }
}