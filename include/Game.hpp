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
            /**
             * * @brief Game constructor
            */
            Game();

            /**
             * @brief return the name of the players that are still in the game
             * @return vector with the names of the players
             */
            std::vector<string> players();

            /**
            * @brief return the name of the current player
            * @return the name of the current player
            * @throw std::invalid_argument if there are no players in the game
            */
            string turn();
            
            /**
            * @brief move to the next player that is still alive and have an action to do
            */
            void nextTurn();
            
            /**
             * @brief add player to the game
             * @param p the player to add
             * @throw std::invalid_argument if the name is already in use
             * @throw std::runtime_error if there are already 6 players in the game
             */
            void addPlayer(Player* p);

            /**
             * @brief check if its the players turn method in use for the player actions
             * @param p the player to check
             * @return true if its the players turn, false otherwise
             */
            bool myTurn(Player *p);
            
            /**
             * @brief return the name of the winner
             * @return the name of the winner
             * @throw std::runtime_error if there is no winner yet
             * @throw std::invalid_argument if there is no players in the game
             */
            string winner();
            
            /**
             * @brief update the last arrested player
             * @param name the name of the last arrested player
             */
            void setLastArrested(string name);
            
            /**
             * @brief return the name of the last arrested player
             * @return the name of the last arrested player
             */
            string getLastArrested() const;
            
            /**
             * @brief return the current player
             * @return the current player
             */
            Player* getCurrentPlayer();

            /**
             * @brief return the list of all the players in the game (including dead players)
             * @return vector with the players in the game
             */
            vector<Player*>& getPlayersList();

            /**
             * @brief return the last action of the game
             * @return the last action of the game
             */
            string getLastAction() const;

            /**
             * @brief set the last action of the game
             * @param str the last action of the game
             */
            void setLastAction(string str);
    };
}
#endif