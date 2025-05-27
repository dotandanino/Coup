//dotandanino@gmail.com

#ifndef GAME_HPP
#define GAME_HPP


#include <vector>
#include <string>
#include <iostream>
using std::string;
using std::vector;
namespace coup{
    class Player;
    class Game{
        std::vector<Player*> playersList;
        int currentTurn;
        string lastArrested;
        string lastGameAction;
        public:
            Game();
            std::vector<string> players();// retrurn vector with the names of the players
            string turn();//return the name of the current player
            void nextTurn();//move to the next player
            void addPlayer(Player* p);//add player to the game
            bool myTurn(Player *p);//check if its his turn
            string winner();//return the name of the winner
            void setLastArrested(string name);//update the last arrested player
            string getLastArrested() const;//return the name of the last arrested player
            Player* getCurrentPlayer();
            vector<Player*>& getPlayersList();
            string getLastAction() const;
            void setLastAction(string str);
    };
}
#endif