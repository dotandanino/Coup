//dotandanino@gmail.com
#include "Player.hpp"
#include "Governor.hpp"
#include "Spy.hpp"
#include "Baron.hpp"
#include "General.hpp"
#include "Judge.hpp"
#include "Merchant.hpp"
#include "Game.hpp"

#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;
using namespace coup;

int main() {
    Game game_1{};

    Governor governor(game_1, "Moshe");
    Spy spy(game_1, "Yossi");
    Baron baron(game_1, "Meirav");
    General general(game_1, "Reut");
    Judge judge(game_1, "Gilad");

    vector<string> players = game_1.players();
    
    // Expected output:
    // Moshe
    // Yossi
    // Meirav
    // Reut
    // Gilad
    for(string name : players){
        cout << name << endl;
    }

    // Expected output: Moshe
    cout << game_1.turn() << endl;

    governor.gather();
    spy.gather();
    baron.gather();
    general.gather();
    judge.gather();

    // Expected exception - Not spy's turn
    try{
        spy.gather();
    } catch (const std::exception &e){
        std::cerr << e.what() << '\n';
    }

    governor.gather();
    spy.tax();

    // Expected exception - Judge cannot undo tax
    try{
        judge.undo(governor);
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    cout << governor.coins() << endl; // Expected: 2
    cout << spy.coins() << endl; // Expected: 3

    governor.undo(spy); // Governor undo tax
    cout << spy.coins() << endl; // Expected: 1

    baron.tax();
    general.gather();
    judge.gather(); 

    governor.tax();
    spy.gather();
    baron.invest(); // Baron traded its 3 coins and got 6 
    general.gather();
    judge.gather();
    
    cout << baron.coins() << endl; // Expected: 6

    governor.tax();
    spy.gather();
    baron.gather();
    general.gather();
    judge.gather();

    governor.tax();
    spy.gather();
    cout << baron.coins() << endl; // Expected: 7
    baron.coup(governor); // Coup against governor
    general.gather();
    judge.gather();
    
    players = game_1.players();
    // Since no one blocked the Baron, the expected output is:
    // Yossi
    // Meirav
    // Reut
    // Gilad
    for (string name : players) {
        cout << name << endl;
    }
    cout<<"Demo Extention"<<endl;
    cout<<"Arresting judge"<<endl;
    cout<<"before: judge coins: "<<judge.coins()<<"spy coins"<<spy.coins()<<endl;
    spy.arrest(judge); // Spy arrest judge
    cout<<"after: judge coins: "<<judge.coins()<<"spy coins"<<spy.coins()<<endl;
    cout<<"Trying to arrest the same player"<<endl;
    try{
        baron.arrest(judge); // Baron arrest judge
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    cout<<"turn: "<<game_1.turn()<<endl; // Expected: Meirav (baron)
    baron.gather();
    cout<<endl;
    spy.BlockArresting(general); // Spy blocks general from arresting
    try{
        general.arrest(baron); // General arrest baron 
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    cout<<"Show bribe"<<endl; 
    general.bribe(); // General bribe
    cout<<endl;

    cout<<"Trying to bribe with less then 4 coins "<<endl;
    try{
        general.bribe(); // General bribe
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    cout<<endl;

    general.tax(); // General tax
    cout<<general.coins()<<endl; // Expected: 3
    cout<<game_1.turn()<<endl; // Expected: reut (general) because general bribe
    general.gather(); // General gather
    judge.tax(); // Judge tax
  
    cout<<"try to prevent the spy from briding"<<endl;
    
    spy.bribe(); // Spy bribe
    cout<<endl;
    judge.undo(spy); // Judge prevent spy from briding
    cout<<"Trying to preform second move"<<endl;
    spy.gather(); // Spy gather
    try{
        spy.gather(); //now its not his turn because the spy undo his bribe
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    cout<<endl;
    cout<<"After one round yossi can gather again"<<endl;
    cout<<spy.coins()<<endl; // Expected: 2
    cout<<game_1.turn()<<endl; // Expected: Meirav (Baron)
    cout<<"baron coins"<<baron.coins()<<endl;
    baron.gather(); // Baron gather
    general.gather();
    judge.gather();

    cout<<game_1.turn()<<endl; // Expected: yossi (spy)
    spy.gather(); 


    cout<<endl;
    cout<<"Trying reach a coup with judge"<<endl;
    cout<<"baron coins: "<<baron.coins()<<endl;
    cout<<"general coins: "<<general.coins()<<endl;
    cout<<"judge coins: "<<judge.coins()<<endl;
    cout<<"spy coins: "<<spy.coins()<<endl; 
    baron.tax(); // Baron invest
    general.tax(); // General tax
    judge.tax(); // Judge gather
    spy.tax(); // Spy tax
    cout<<endl;
    cout<<"baron coins: "<<baron.coins()<<endl;
    cout<<"general coins: "<<general.coins()<<endl;
    cout<<"judge coins: "<<judge.coins()<<endl;
    cout<<"spy coins: "<<spy.coins()<<endl;
    baron.invest(); // Baron invest
    general.tax(); // General tax
    judge.tax(); // Judge gather
    spy.tax(); // Spy tax
    baron.invest(); // Baron invest
    general.tax(); // General tax
    cout<<"Trying to gather when judge have to coup"<<endl;
    try{
        judge.gather(); // Judge gather
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    cout<<endl;
    cout<<"Trying to coup dead player"<<endl;
    try{
        judge.coup(governor); // Judge coup spy
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    cout<<endl;
    judge.coup(baron); // Judge coup spy
    cout<<endl;

    cout<<spy.peek(general)<<endl; // Spy see the amount of coins baron have

    spy.tax(); // Spy tax

    cout<<"Trying to play with dead player"<<endl;
    try{
        baron.gather(); 
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    cout<<endl;
    general.coup(spy); // General coup spy
    judge.tax(); // Judge tax
    general.tax(); // General gather
    judge.tax(); // Judge tax
    general.tax(); // General gather
    judge.tax(); // Judge tax
    general.tax(); // General gather
    cout<<endl;
    judge.coup(general); // Judge coup general
    cout<<"the winner is: "<<game_1.winner()<<endl; // Expected: Gilad (Judge)
}