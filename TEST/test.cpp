#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../hppFiles/Game.hpp"
#include "../hppFiles/Player.hpp"
#include "../hppFiles/Governor.hpp"
#include "../hppFiles/Spy.hpp"
#include "../hppFiles/Baron.hpp"
#include "../hppFiles/General.hpp"
#include "../hppFiles/Judge.hpp"
#include "../hppFiles/Merchant.hpp"
#include "../hppFiles/playerFactory.hpp"
#include <iostream>
#include <vector>

using namespace coup;
using std::string;
using std::vector;

TEST_CASE("Game Initialization") {
    Game game;
    CHECK(game.players().size() == 0);//the list of players should be empty
    CHECK_THROWS_WITH(game.turn(), "there is no players in the game");
    Baron baron(game, "Dotan");
    CHECK(game.players().size() == 1);//the baron is in the list.
    CHECK(game.turn() == "Dotan");
    General general(game, "Itamar");
    CHECK(game.players().size() == 2);
    CHECK(game.turn() == "Dotan");//dotan didnt play yet so he is still the current player
    Spy spy(game, "Ori");
    CHECK(game.players().size() == 3);
    CHECK(game.turn() == "Dotan");//dotan didnt play yet so he is still the current player
    Judge judge(game, "Sharon");
    CHECK(game.players().size() == 4);
    CHECK(game.turn() == "Dotan");//dotan didnt play yet so he is still the current player
    CHECK_THROWS_WITH(Governor(game, "Dotan"), "this name is already in use in this game.");//trying to add a player with the same name should throw an error
    Merchant merchant(game, "Shay");
    CHECK(game.players().size() == 5);
    CHECK(game.turn() == "Dotan");//dotan didnt play yet so he is still the current player
    Governor governor(game, "Yonathan");
    CHECK(game.players().size() == 6);
    CHECK(game.turn() == "Dotan");//dotan didnt play yet so he is still the current player
    CHECK_THROWS_WITH(Governor(game, "NewPlayer"), "you cant add more players to the game");//trying to add more than 6 players should throw an error
}

TEST_CASE("Gather"){
    Game game;
    SUBCASE("Tax not in turn"){
        Game game;
        Baron baron(game, "Dotan");
        General general(game, "Itamar");
        Spy spy(game, "Ori");
        Judge judge(game, "Sharon");
        Merchant merchant(game, "Shay");
        Governor governor(game, "Yonathan");
        CHECK_THROWS_WITH(general.gather(), "its not your turn");//General should not be able to gather if it's not his turn
    }
    SUBCASE("baron Gather in sanction"){
        Baron baron(game, "Dotan");
        General general(game, "Itamar");
        Spy spy(game, "Ori");
        Judge judge(game, "Sharon");
        Merchant merchant(game, "Shay");
        Governor governor(game, "Yonathan");
        baron.youAreUnderSanction(); // Baron is under sanction
        CHECK_THROWS_WITH(baron.tax(), "you are under sanction");//Baron should not be able to tax while under sanction
    }
    
    SUBCASE("general Gather in sanction"){
        General general(game, "Itamar");
        Baron baron(game, "Dotan");
        Spy spy(game, "Ori");
        Judge judge(game, "Sharon");
        Merchant merchant(game, "Shay");
        Governor governor(game, "Yonathan");
        general.youAreUnderSanction(); // Baron is under sanction
        CHECK_THROWS_WITH(general.gather(), "you are under sanction");//Baron should not be able to tax while under sanction
    }
    SUBCASE("Judge Gather in sanction"){
        Judge judge(game, "Sharon");
        Baron baron(game, "Dotan");
        General general(game, "Itamar");
        Spy spy(game, "Ori");
        Merchant merchant(game, "Shay");
        Governor governor(game, "Yonathan");
        judge.youAreUnderSanction(); // Baron is under sanction
        CHECK_THROWS_WITH(judge.gather(), "you are under sanction");//Baron should not be able to tax while under sanction
    }
    SUBCASE("merchant Gather in sanction"){
        Merchant merchant(game, "Shay");
        Baron baron(game, "Dotan");
        General general(game, "Itamar");
        Spy spy(game, "Ori");
        Judge judge(game, "Sharon");
        Governor governor(game, "Yonathan");
        merchant.youAreUnderSanction(); // Baron is under sanction
        CHECK_THROWS_WITH(merchant.gather(), "you are under sanction");//Baron should not be able to tax while under sanction
    }
    SUBCASE("Governor Gather under sanction"){
        Governor governor(game, "Yonathan");
        Baron baron(game, "Dotan");
        General general(game, "Itamar");
        Spy spy(game, "Ori");
        Judge judge(game, "Sharon");
        Merchant merchant(game, "Shay");
        governor.youAreUnderSanction(); // Governor is under sanction
        CHECK_THROWS_WITH(governor.gather(), "you are under sanction");//Governor should not be able to tax while under sanction
    }
    SUBCASE("spy tax under sanction"){
        Spy spy(game, "Ori");
        Governor governor(game, "Yonathan");
        Baron baron(game, "Dotan");
        General general(game, "Itamar");
        Judge judge(game, "Sharon");
        Merchant merchant(game, "Shay");
        spy.youAreUnderSanction(); // Spy is under sanction
        CHECK_THROWS_WITH(spy.gather(), "you are under sanction");//Governor should not be able to tax while under sanction
    }

    SUBCASE("Gather not in turn"){
        Game game;
        Baron baron(game, "Dotan");
        General general(game, "Itamar");
        Spy spy(game, "Ori");
        Judge judge(game, "Sharon");
        Merchant merchant(game, "Shay");
        Governor governor(game, "Yonathan");
        CHECK_THROWS_WITH(general.gather(), "its not your turn");//General should not be able to gather if it's not his turn
    }
    SUBCASE("work"){
        Game game;
        Baron baron(game, "Dotan");
        General general(game, "Itamar");
        Spy spy(game, "Ori");
        Judge judge(game, "Sharon");
        Merchant merchant(game, "Shay");
        Governor governor(game, "Yonathan");
        CHECK(baron.coins() == 0);
        CHECK(general.coins() == 0);
        CHECK(spy.coins() == 0);
        CHECK(judge.coins() == 0);
        CHECK(merchant.coins() == 0);
        CHECK(governor.coins() == 0);
        baron.gather(); // Baron gather
        CHECK(baron.coins() == 1); // Baron should have 1 coin after gathering
        CHECK(game.turn() == "Itamar"); // Next turn should be Itamar (General)
        general.gather(); // General gather
        CHECK(general.coins() == 1); // General should have 1 coin after gathering
        CHECK(game.turn() == "Ori"); // Next turn should be Ori (Spy)
        spy.gather(); // Spy gather
        CHECK(spy.coins() == 1); // Spy should have 1 coin after gathering
        CHECK(game.turn() == "Sharon"); // Next turn should be Sharon (Judge)
        judge.gather(); // Judge gather
        CHECK(judge.coins() == 1); // Judge should have 1 coin after gathering
        CHECK(game.turn() == "Shay"); // Next turn should be Shay (Merchant)
        merchant.gather(); // Merchant gather
        CHECK(merchant.coins() == 1); // Merchant should have 1 coin after gathering
        CHECK(game.turn() == "Yonathan"); // Next turn should be Yonathan (Governor)
        governor.gather(); // Governor gather
        CHECK(governor.coins() == 1); // Governor should have 1 coin after gathering
        CHECK(game.turn() == "Dotan"); // Next turn should be Dotan (Baron)
        baron.gather(); // Baron gather again
        CHECK(baron.coins() == 2); // Baron should have 2 coins after gathering again
        CHECK(game.turn() == "Itamar"); // Next turn should be Itamar (General)
        general.gather(); // General gather again
        CHECK(general.coins() == 2); // General should have 2 coins after gathering again
        CHECK(game.turn() == "Ori"); // Next turn should be Ori (Spy)
        spy.gather(); // Spy gather again
        CHECK(spy.coins() == 2); // Spy should have 2 coins after gathering again
        CHECK(game.turn() == "Sharon"); // Next turn should be Sharon (Judge)
        judge.gather(); // Judge gather again
        CHECK(judge.coins() == 2); // Judge should have 2 coins after gathering again
        CHECK(game.turn() == "Shay"); // Next turn should be Shay (Merchant)
        merchant.gather(); // Merchant gather again
        CHECK(merchant.coins() == 2); // Merchant should have 2 coins after gathering again
        CHECK(game.turn() == "Yonathan"); // Next turn should be Yonathan (Governor)
        governor.gather(); // Governor gather again
        CHECK(governor.coins() == 2); // Governor should have 2 coins after gathering again
    }
    SUBCASE("10 coins"){
        Game game;
        Baron dotan(game, "Dotan");
        Governor yonathan(game, "Yonathan");
        dotan.gather();
        yonathan.gather();
        dotan.gather();
        yonathan.gather();
        dotan.gather();
        yonathan.gather();
        dotan.gather();
        yonathan.gather();
        dotan.gather();
        yonathan.gather();
        dotan.gather();
        yonathan.gather();
        dotan.gather();
        yonathan.gather();
        dotan.gather();
        yonathan.gather();
        dotan.gather();
        yonathan.gather();
        dotan.gather();
        yonathan.gather();
        CHECK(dotan.coins() == 10); // Dotan should have 10 coins after gathering
        CHECK_THROWS_WITH(dotan.gather(), "you have to coup because you have 10 coins or more");//Dotan should not be able to gather if he has 10 coins or more
    }

}

TEST_CASE("Tax"){
    Game game;
    
    SUBCASE("baron Tax in sanction"){
        Baron baron(game, "Dotan");
        General general(game, "Itamar");
        Spy spy(game, "Ori");
        Judge judge(game, "Sharon");
        Merchant merchant(game, "Shay");
        Governor governor(game, "Yonathan");
        baron.youAreUnderSanction(); // Baron is under sanction
        CHECK_THROWS_WITH(baron.tax(), "you are under sanction");//Baron should not be able to tax while under sanction
    }
    SUBCASE("Tax not in turn"){
        Game game;
        Baron baron(game, "Dotan");
        General general(game, "Itamar");
        Spy spy(game, "Ori");
        Judge judge(game, "Sharon");
        Merchant merchant(game, "Shay");
        Governor governor(game, "Yonathan");
        CHECK_THROWS_WITH(general.tax(), "its not your turn");//General should not be able to gather if it's not his turn
    }
    SUBCASE("general Tax in sanction"){
        General general(game, "Itamar");
        Baron baron(game, "Dotan");
        Spy spy(game, "Ori");
        Judge judge(game, "Sharon");
        Merchant merchant(game, "Shay");
        Governor governor(game, "Yonathan");
        general.youAreUnderSanction(); // Baron is under sanction
        CHECK_THROWS_WITH(general.tax(), "you are under sanction");//Baron should not be able to tax while under sanction
    }
    SUBCASE("Judge Tax in sanction"){
        Judge judge(game, "Sharon");
        Baron baron(game, "Dotan");
        General general(game, "Itamar");
        Spy spy(game, "Ori");
        Merchant merchant(game, "Shay");
        Governor governor(game, "Yonathan");
        judge.youAreUnderSanction(); // Baron is under sanction
        CHECK_THROWS_WITH(judge.tax(), "you are under sanction");//Baron should not be able to tax while under sanction
    }
    SUBCASE("merchant Tax in sanction"){
        Merchant merchant(game, "Shay");
        Baron baron(game, "Dotan");
        General general(game, "Itamar");
        Spy spy(game, "Ori");
        Judge judge(game, "Sharon");
        Governor governor(game, "Yonathan");
        merchant.youAreUnderSanction(); // Baron is under sanction
        CHECK_THROWS_WITH(merchant.tax(), "you are under sanction");//Baron should not be able to tax while under sanction
    }
    SUBCASE("Governor tax under sanction"){
        Governor governor(game, "Yonathan");
        Baron baron(game, "Dotan");
        General general(game, "Itamar");
        Spy spy(game, "Ori");
        Judge judge(game, "Sharon");
        Merchant merchant(game, "Shay");
        governor.youAreUnderSanction(); // Governor is under sanction
        CHECK_THROWS_WITH(governor.tax(), "you are under sanction");//Governor should not be able to tax while under sanction
    }
    SUBCASE("spy tax under sanction"){
        Spy spy(game, "Ori");
        Governor governor(game, "Yonathan");
        Baron baron(game, "Dotan");
        General general(game, "Itamar");
        Judge judge(game, "Sharon");
        Merchant merchant(game, "Shay");
        spy.youAreUnderSanction(); // Governor is under sanction
        CHECK_THROWS_WITH(spy.tax(), "you are under sanction");//Governor should not be able to tax while under sanction
    }

    SUBCASE("work"){
        Baron baron(game, "Dotan");
        General general(game, "Itamar");
        Spy spy(game, "Ori");
        Judge judge(game, "Sharon");
        Merchant merchant(game, "Shay");
        Governor governor(game, "Yonathan");
        CHECK(baron.coins() == 0);
        CHECK(general.coins() == 0);
        CHECK(spy.coins() == 0);
        CHECK(judge.coins() == 0);
        CHECK(merchant.coins() == 0);
        CHECK(governor.coins() == 0);
        baron.tax(); // Baron tax
        CHECK(baron.coins() == 2); // Baron should have 2 coins after tax
        CHECK(game.turn() == "Itamar"); // Next turn should be Itamar (General)
        general.tax(); // General tax
        CHECK(general.coins() == 2); // General should have 2 coins after tax
        CHECK(game.turn() == "Ori"); // Next turn should be Ori (Spy)
        spy.tax(); // Spy tax
        CHECK(spy.coins() == 2); // Spy should have 2 coins after tax
        CHECK(game.turn() == "Sharon"); // Next turn should be Sharon (Judge)
        judge.tax(); // Judge tax
        CHECK(judge.coins() == 2); // Judge should have 2 coins after tax
        CHECK(game.turn() == "Shay"); // Next turn should be Shay (Merchant)
        merchant.tax(); // Merchant tax
        CHECK(merchant.coins() == 2); // Merchant should have 2 coins after tax
        CHECK(game.turn() == "Yonathan"); // Next turn should be Yonathan (Governor)
        governor.tax(); // Governor tax
        CHECK(governor.coins() == 3); // Governor should have 2 coins after tax
        CHECK(game.turn() == "Dotan"); // Next turn should be Dotan (Baron)
        baron.tax(); // Baron tax again
        CHECK(baron.coins() == 4); // Baron should have 4 coins after tax
        CHECK(game.turn() == "Itamar"); // Next turn should be Itamar (General)
        general.tax(); // General tax again
        CHECK(general.coins() == 4); // General should have 4 coins after tax
        CHECK(game.turn() == "Ori"); // Next turn should be Ori (Spy)
        spy.tax(); // Spy tax again
        CHECK(spy.coins() == 4); // Spy should have 4 coins after tax
        CHECK(game.turn() == "Sharon"); // Next turn should be Sharon (Judge)
        judge.tax(); // Judge tax again
        CHECK(judge.coins() == 4); // Judge should have 4 coins after tax
        CHECK(game.turn() == "Shay"); // Next turn should be Shay (Merchant)
        merchant.tax(); // Merchant tax again
        CHECK(merchant.coins() == 4); // Merchant should have 4 coins after tax
        CHECK(game.turn() == "Yonathan"); // Next turn should be Yonathan (Governor)
        governor.tax(); // Governor tax again
        CHECK(governor.coins() == 6); // Governor should have 3 coins after tax
    }
    SUBCASE("10 coins"){
        Game game;
        Baron dotan(game, "Dotan");
        Spy yonathan(game, "Yonathan");
        dotan.tax();
        yonathan.tax();
        dotan.tax();
        yonathan.tax();
        dotan.tax();
        yonathan.tax();
        dotan.tax();
        yonathan.tax();
        dotan.tax();
        yonathan.tax();
        CHECK(dotan.coins() == 10); // Dotan should have 10 coins after gathering
        CHECK_THROWS_WITH(dotan.gather(), "you have to coup because you have 10 coins or more");//Dotan should not be able to gather if he has 10 coins or more
    }

}

TEST_CASE("Bribe"){
    Game game;
    Governor dotan(game, "Dotan");
    General itamar(game, "Itamar");
    Spy ori(game, "Ori");
    SUBCASE("Bribe without enough coins") {
        CHECK(dotan.coins() == 0);
        CHECK_THROWS_WITH(dotan.bribe(), "you dont have enough money to pay for the bribe");
    }
    SUBCASE("Bribe not in turn"){
        CHECK_THROWS_WITH(ori.bribe(), "its not your turn");
    }

    SUBCASE("10 coins"){
        Game game;
        Baron dotan(game, "Dotan");
        Governor yonathan(game, "Yonathan");
        dotan.tax();
        yonathan.tax();
        dotan.tax();
        yonathan.tax();
        dotan.tax();
        yonathan.tax();
        dotan.tax();
        yonathan.tax();
        dotan.tax();
        CHECK(yonathan.coins() == 12); // Yonathan should have 10 coins after gathering
        CHECK_THROWS_WITH(yonathan.bribe(), "you have to coup because you have 10 coins or more");//Yonathan should not be able to bribe if he has 10 coins or more
    }
    SUBCASE("work Bribe"){
        dotan.tax();//dotan coins 3
        itamar.tax();//itamar coins 2
        ori.tax();//ori coins 2
        dotan.tax();//dotan coins 6
        itamar.tax();//itamar coins 4
        ori.tax();//ori coins 4
        dotan.bribe();//dotan coins 2
        CHECK(dotan.coins() == 2); // Dotan should have 4 coins after bribe
        dotan.tax();//dotan coins=5
        CHECK(game.turn()=="Dotan"); // Dotan should have another turn after bribe
        dotan.tax();//dotan coins=8
        itamar.bribe(); // Itamar coins 0
        itamar.arrest(dotan); // Itamar arrest Dotan itamar coins 1 Dotan coins 7
        CHECK(game.turn()=="Itamar");// Itamar should have another turn after bribe
        itamar.gather();//itamar coins 2
        ori.bribe();//ori coins 0
        ori.gather();//ori coins 1
        CHECK(game.turn()=="Ori");// Ori should have another turn after bribe
        ori.gather();//ori coins 2
        dotan.bribe();// Dotan coins 4
        dotan.sanction(ori); // Dotan coins 1
        CHECK(game.turn() == "Dotan"); // Dotan should have another turn after sanction
    }
}

TEST_CASE("Sanction"){
    SUBCASE("Sanction without money") {
        Game game;
        Baron baron(game, "Dotan");
        General general(game, "Itamar");
        Spy spy(game, "Ori");
        Judge judge(game, "Sharon");
        Merchant merchant(game, "Shay");
        Governor governor(game, "Yonathan");
        CHECK_THROWS_WITH(baron.sanction(general), "you dont have enough money");
    }
    
    SUBCASE("Sanction not in turn") {
        Game game;
        Baron baron(game, "Dotan");
        General general(game, "Itamar");
        Spy spy(game, "Ori");
        Judge judge(game, "Sharon");
        Merchant merchant(game, "Shay");
        Governor governor(game, "Yonathan");
        baron.tax();
        general.tax();
        spy.tax();
        judge.tax();
        merchant.tax();
        governor.tax();
        baron.tax();
        general.tax();
        spy.tax();
        judge.tax();
        merchant.tax();
        governor.tax();
        CHECK_THROWS_WITH(general.sanction(baron), "its not your turn");
    }

    SUBCASE("Sanction on already sanctioned player") {
        Game game;
        Baron baron(game, "Dotan");
        General general(game, "Itamar");
        Spy spy(game, "Ori");
        Judge judge(game, "Sharon");
        Merchant merchant(game, "Shay");
        Governor governor(game, "Yonathan");
        baron.tax();
        general.tax();
        spy.tax();
        judge.tax();
        merchant.tax();
        governor.tax();
        baron.tax();
        general.tax();
        spy.tax();
        judge.tax();
        merchant.tax();
        governor.tax();
        baron.sanction(governor);
        CHECK_THROWS_WITH(general.sanction(governor), "this player is already under sanction");
    }

    SUBCASE("work"){
        Game game;
        Baron baron(game, "Dotan");
        General general(game, "Itamar");
        Spy spy(game, "Ori");
        Judge judge(game, "Sharon");
        Merchant merchant(game, "Shay");
        Governor governor(game, "Yonathan");
        baron.tax();
        general.tax();
        spy.tax();
        judge.tax();
        merchant.tax();
        governor.tax();
        baron.tax();
        general.tax();
        spy.tax();
        judge.tax();
        merchant.tax();
        governor.tax();
        baron.sanction(general);
        CHECK_THROWS_WITH(general.gather(), "you are under sanction");
        CHECK_THROWS_WITH(general.tax(), "you are under sanction");
        general.sanction(spy);
        CHECK_THROWS_WITH(spy.gather(), "you are under sanction");
        CHECK_THROWS_WITH(spy.tax(), "you are under sanction");
        spy.sanction(judge);
        CHECK_THROWS_WITH(judge.gather(), "you are under sanction");
        CHECK_THROWS_WITH(judge.tax(), "you are under sanction");
        judge.sanction(merchant);
        CHECK_THROWS_WITH(merchant.gather(), "you are under sanction");
        CHECK_THROWS_WITH(merchant.tax(), "you are under sanction");
        merchant.sanction(governor);
        CHECK_THROWS_WITH(governor.gather(), "you are under sanction");
        CHECK_THROWS_WITH(governor.tax(), "you are under sanction");
        governor.sanction(baron);
        CHECK_THROWS_WITH(baron.gather(), "you are under sanction");
        CHECK_THROWS_WITH(baron.tax(), "you are under sanction");
    }
    SUBCASE("money decrease after sanction on judge"){
        Game game;
        Baron dotan(game, "Dotan");
        Judge judge(game, "Sharon");
        dotan.tax(); // Dotan has 2 coins
        judge.tax(); // Judge has 2 coins
        dotan.gather();//dotan has 3 coins
        judge.gather();
        CHECK(dotan.coins() == 3); 
        CHECK_THROWS_WITH(dotan.sanction(judge), "you dont have enough money");//Dotan should not be able to sanction Judge if he has less than 4 coins
        dotan.gather();//dotan has 4 coins
        judge.gather();
        CHECK_NOTHROW(dotan.sanction(judge)); // Dotan sanctions Judge
    }
    SUBCASE("money decrease after sanction on another player"){
        Game game;
        Baron dotan(game,"dotan");
        General itamar(game, "Itamar");
        dotan.tax(); // Dotan has 2 coins
        itamar.tax(); // Itamar has 2 coins
        dotan.gather(); // Dotan has 3 coins
        itamar.gather(); // Itamar has 3 coins
        CHECK(dotan.coins() == 3);
        CHECK_NOTHROW(dotan.sanction(itamar)); // Dotan sanctions Itamar
    }
    SUBCASE("Sanction on baron (get extra coin)") {
        Game game;
        Baron baron(game, "Dotan");
        General general(game, "Itamar");
        Spy spy(game, "Ori");
        Judge judge(game, "Sharon");
        Merchant merchant(game, "Shay");
        Governor governor(game, "Yonathan");
        baron.tax();//2 coins
        general.tax();
        spy.tax();
        judge.tax();
        merchant.tax();
        governor.tax();
        baron.tax();//4 coins
        general.tax();
        spy.tax();
        judge.tax();
        merchant.tax();
        governor.tax();
        baron.tax();//6 coins
        general.sanction(baron);
        spy.tax();
        judge.tax();
        merchant.tax();
        governor.tax();
        CHECK_THROWS_WITH(baron.gather(), "you are under sanction");
        CHECK(baron.coins() == 7); // Baron should have 7 coins after sanction
    }
    SUBCASE("10 coins"){
        Game game;
        Baron dotan(game, "Dotan");
        Spy yonathan(game, "Yonathan");
        dotan.tax();
        yonathan.tax();
        dotan.tax();
        yonathan.tax();
        dotan.tax();
        yonathan.tax();
        dotan.tax();
        yonathan.tax();
        dotan.tax();
        yonathan.tax();
        CHECK(dotan.coins() == 10); // Dotan should have 10 coins after gathering
        CHECK_THROWS_WITH(dotan.sanction(yonathan), "you have to coup because you have 10 coins or more");//Dotan should not be able to sanction if he has 10 coins or more

    }
    SUBCASE("dont enough money to sanction Judge"){
        Game game;
        Baron dotan(game, "Dotan");
        Judge judge(game, "Sharon");
        dotan.tax();
        judge.tax();
        dotan.gather();
        judge.gather();
        CHECK_THROWS_WITH(dotan.sanction(judge), "you dont have enough money");
    }
}

TEST_CASE("Arrest"){
    SUBCASE("arrest general with 0 money"){
        Game game;
        Baron dotan(game, "Dotan");
        General itamar(game, "Itamar");
        CHECK_NOTHROW(dotan.arrest(itamar));
    }
    SUBCASE("arrest player that have no money") {
        Game game;
        Baron dotan(game, "Dotan");
        Spy itamar(game, "Itamar");
        CHECK_THROWS_WITH(dotan.arrest(itamar),"the other player dont have enough money to pay for the arrest");
    }

    SUBCASE("arrest not in turn"){
        Game game;
        Baron dotan(game, "Dotan");
        General itamar(game, "Itamar");
        dotan.tax();
        itamar.tax();
        CHECK_THROWS_WITH(itamar.arrest(dotan),"its not your turn");
    }

    SUBCASE("arrest the same player twice"){
        Game game;
        Baron dotan(game, "Dotan");
        Spy ori(game, "Ori");
        General itamar(game, "Itamar");
        dotan.tax();
        ori.tax();
        itamar.tax();
        dotan.arrest(itamar);
        CHECK_THROWS_WITH(ori.arrest(itamar),"you cant arrest the same player twice in a row");
    }

    SUBCASE("arrest Merchant with 0 coins"){
        Game game;
        Baron dotan(game, "Dotan");
        Merchant shay(game, "Shay");
        CHECK_THROWS_WITH(dotan.arrest(shay),"the other player dont have enough money to pay for the arrest");
    }
    
    SUBCASE("arrest Merchant with 1 coins"){
        Game game;
        Baron dotan(game, "Dotan");
        Merchant shay(game, "Shay");
        dotan.tax();
        shay.gather();
        CHECK_THROWS_WITH(dotan.arrest(shay),"the other player dont have enough money to pay for the arrest");
    }

    SUBCASE("arrest Merchant with 2 coins"){
        Game game;
        Baron dotan(game, "Dotan");
        Merchant shay(game, "Shay");
        dotan.tax();
        shay.tax();
        CHECK_NOTHROW(dotan.arrest(shay));
    }

    SUBCASE("work"){
        Game game;
        Merchant dotan(game, "Dotan");
        General itamar(game, "Itamar");
        Spy ori(game, "Ori");
        Judge sharon(game, "Sharon");
        Baron shay(game, "Shay");
        Governor yonathan(game, "Yonathan");
        
        dotan.tax(); // Dotan coins 2
        itamar.tax(); // Itamar coins 2
        ori.tax(); // Ori coins 2
        sharon.tax(); // Sharon coins 2
        shay.tax(); // Shay coins 2
        yonathan.tax(); // Yonathan coins 2
        
        dotan.arrest(itamar); // Dotan arrests Itamar
        CHECK(itamar.coins() == 2);//general dont pay for arrest
        CHECK(dotan.coins() == 2);//general dont pay for arrest
        
        itamar.arrest(ori); // Itamar arrests Ori, Ori pays 1 coin to Itamar
        CHECK(ori.coins() == 1); // Ori should have 1 coin after arrest
        CHECK(itamar.coins() == 3); // Itamar should have 3 coins after arrest

        ori.arrest(sharon); // Ori arrests Sharon, Sharon pays 1 coin to Ori
        CHECK(sharon.coins() == 1); // Sharon should have 1 coin after arrest
        CHECK(ori.coins() == 2); // Ori should have 2 coins after arrest
        
        sharon.arrest(shay); // Sharon arrests Shay, Shay pays 1 coin to Sharon
        CHECK(shay.coins() == 1); // Shay should have 1 coin after arrest
        CHECK(sharon.coins() == 2); // Sharon should have 2 coins after arrest

        shay.arrest(yonathan); // Shay arrests Yonathan, Yonathan pays 1 coin to Shay
        CHECK(yonathan.coins() == 2); // Yonathan should have 2 coin after arrest (had 3 from tax)
        CHECK(shay.coins() == 2); // Shay should have 2 coins after arrest

        yonathan.arrest(dotan);
        CHECK(dotan.coins() == 0); // Dotan should have 1 coin after arrest
        CHECK(yonathan.coins() == 2); // The player who arrested merchant dont receive money from the merchant
    }
}

TEST_CASE("Coup"){

    SUBCASE("Coup not in turn") {
        Game game;
        Baron dotan(game, "Dotan");
        General itamar(game, "Itamar");
        dotan.tax();
        itamar.tax();
        dotan.tax();
        itamar.tax();
        dotan.invest();
        CHECK_THROWS_WITH(dotan.coup(itamar), "its not your turn");
    }

    SUBCASE("Coup without enough coins") {
        Game game;
        Baron dotan(game, "Dotan");
        General itamar(game, "Itamar");
        dotan.tax();
        itamar.tax();
        dotan.tax();
        itamar.tax();
        CHECK_THROWS_WITH(dotan.coup(itamar), "you done have enough money for coup");
    }

    SUBCASE("Coup with 7 coins") {
        Game g;
        Baron dotan(g, "Dotan");
        General itamar(g, "Itamar");

        dotan.tax(); // Dotan has 2 coins
        itamar.tax(); // Itamar has 2 coins
        dotan.tax(); // Dotan has 4 coins
        itamar.tax(); // Itamar has 4 coins
        dotan.tax(); // Dotan has 6 coins
        itamar.tax(); // Itamar has 6 coins
        dotan.tax(); // Dotan has 8 coins
        itamar.tax(); // Itamar has 8 coins
        CHECK(dotan.coins() == 8); // Dotan should have 8 coins
        dotan.coup(itamar); // Dotan coups Itamar
        CHECK(itamar.isStillAlive() == false); // Itamar should be dead after coup
    }

    SUBCASE("Coup to dead player") {
        Game g;
        Governor dotan(g, "Dotan");
        General itamar(g, "Itamar");
        Spy ori(g, "Ori");

        dotan.tax(); // Dotan has 3 coins
        itamar.tax(); // Itamar has 2 coins
        ori.tax(); // Ori has 2 coins
        dotan.tax(); // Dotan has 6 coins
        itamar.tax(); // Itamar has 4 coins
        ori.tax(); // Ori has 4 coins
        dotan.tax(); // Dotan has 9 coins
        itamar.tax(); // Itamar has 6 coins
        ori.tax(); // Ori has 6 coins
        dotan.coup(itamar); // Dotan coups Itamar, 2 coins
        CHECK(itamar.isStillAlive() == false); // Itamar should be dead after coup
        ori.tax(); // Ori has 8 coins
        dotan.tax(); // Dotan has 5 coins
        ori.tax(); // Ori has 10 coins
        dotan.tax(); // Dotan has 8 coins
        CHECK_THROWS_WITH(ori.coup(itamar), "you cant coup someone that already couped"); // Dotan should not be able to coup Itamar again
        
    }

}

TEST_CASE("Undo"){
    SUBCASE("General can undo coup") {
        Game g;
        Governor gov(g, "gov");
        General gen(g, "gen");

        // gov earns 10
        gov.tax();//3 
        gen.tax(); //2
        gov.tax(); //6
        gen.tax(); //4
        gov.tax(); //9
        gen.tax(); //6
        gov.gather(); // = 10
        gen.tax(); //8
        gov.coup(gen);//gov-7 coins - ->3
        CHECK(gen.isStillAlive() == false);


        gen.undo(gen); // Revives
        CHECK(gen.isStillAlive() == true);
    }

    SUBCASE("Judge undo bribe") {
    
        Game g;
        Spy spy(g, "spy");
        Judge judge(g, "judge");

        spy.tax();
        judge.tax();
        spy.tax();
        judge.tax();
        spy.bribe(); // cost 4
        CHECK(spy.coins() == 0);
        judge.undo(spy);
        CHECK(spy.coins() != 4); // refunded
    }

    SUBCASE("General undo coup") {
        Game g;
        Governor gov(g, "gov");
        General gen(g, "gen");

        // Build up coins for coup
        gov.tax();          // +3 → 3
        gen.gather();       // 1
        gov.tax();          // 6
        gen.gather();       // 2
        gov.tax();          // 9
        gen.gather();       // 3
        gov.gather();       // 10

        CHECK_THROWS(gov.tax()); // Should throw since gov has 10

        gen.tax();//6
        gov.coup(gen);
        
        CHECK(gen.isStillAlive() == false);
        CHECK_NOTHROW(gen.undo(gen));  // Should succeed
        CHECK(gen.isStillAlive() == true);
    }

    SUBCASE("Governor undo with 0 coins") {
        Game g;
        Governor gov(g, "gov");
        General gen(g, "gen");

        // Build up coins for coup
        gov.tax();          // +3 → 3
        gen.gather();       // 1
        gov.tax();          // 6
        gen.gather();       // 2
        gov.tax();          // 9
        gen.gather();       // 3
        gov.gather();       // 10

        CHECK_THROWS(gov.tax()); // Should throw since gov has 10

        gen.tax();//6
        gov.coup(gen);
        
        CHECK(gen.isStillAlive() == false);
        CHECK_THROWS_WITH(gov.undo(gen),"you cant undo an action of a dead player");  // Should succeed
        CHECK(gen.isStillAlive() == false);
    }
    
    SUBCASE("Undo coup with less than 5 coins") {
        Game g;
        Governor gov(g, "gov");
        General gen(g, "gen");

        // Build up coins for coup
        gov.tax();          // 3
        gen.gather();       // 1
        gov.tax();          // 6
        gen.gather();       // 2
        gov.tax();          // 9
        gen.gather();       // 3
        gov.gather();       // 10
        gen.gather();       // 4
        CHECK_THROWS(gov.tax()); // Should throw since gov has 10

        gov.coup(gen);
        
        CHECK(gen.isStillAlive() == false);
        CHECK_THROWS_WITH(gen.undo(gen),"you dont have enough money");  // Should succeed
        CHECK(gen.isStillAlive() == false);
    }

    SUBCASE("general try to undo bribe"){
        Game g;
        Governor gov(g, "gov");
        General gen(g, "gen");
        gov.tax(); // gov has 3 coins
        gen.tax(); // gen has 2 coins
        gov.tax(); // gov has 6 coins
        gen.tax(); // gen has 4 coins
        gov.bribe(); // gov has 2 coins
        CHECK(gov.coins() == 2); // gov should have 2 coins after bribe
        CHECK_THROWS_WITH(gen.undo(gov), "you can undo only coup and only at the same time its happen"); // gen should not be able to undo gov's bribe
    }

    SUBCASE("genreral try to undo tax"){
        Game g;
        Governor gov(g, "gov");
        General gen(g, "gen");
        gov.tax(); // gov has 3 coins
        gen.tax(); // gen has 2 coins
        gov.tax(); // gov has 6 coins
        CHECK_THROWS_WITH(gen.undo(gov), "you can undo only coup and only at the same time its happen"); // gen should not be able to undo gov's tax
    }

    SUBCASE("Judge try to undo coup"){
        Game g;
        Governor gov(g, "gov");
        Judge gen(g, "gen");
        gov.tax(); // gov has 3 coins
        gen.tax(); // gen has 2 coins
        gov.tax(); // gov has 6 coins
        gen.tax(); // gen has 4 coins
        gov.tax();
        gen.tax();
        gov.coup(gen); // gov has 2 coins
        CHECK_THROWS_WITH(gen.undo(gov), "you cant undo this action"); // gen should not be able to undo gov's bribe
    }

    SUBCASE("Judge try to undo tax"){
        Game g;
        Governor gov(g, "gov");
        Judge gen(g, "gen");
        gov.tax(); // gov has 3 coins
        gen.tax(); // gen has 2 coins
        gov.tax(); // gov has 6 coins
        CHECK_THROWS_WITH(gen.undo(gov), "you cant undo this action"); // gen should not be able to undo gov's bribe
    }

    SUBCASE("Judge try to undo coup"){
        Game g;
        Governor gov(g, "gov");
        Governor gen(g, "gen");
        gov.tax(); // gov has 3 coins
        gen.tax(); // gen has 2 coins
        gov.tax(); // gov has 6 coins
        gen.tax(); // gen has 4 coins
        gov.bribe(); // gov has 2 coins
        CHECK(gov.coins() == 2); // gov should have 2 coins after bribe
        CHECK_THROWS_WITH(gen.undo(gov), "you cant undo this action"); // gen should not be able to undo gov's bribe
    }

    SUBCASE("Governor try to undo bribe"){
        Game g;
        Governor gov(g, "gov");
        Governor gen(g, "gen");
        gov.tax(); // gov has 3 coins
        gen.tax(); // gen has 2 coins
        gov.tax(); // gov has 6 coins
        gen.tax(); // gen has 4 coins
        gov.bribe(); // gov has 2 coins
        CHECK(gov.coins() == 2); // gov should have 2 coins after bribe
        CHECK_THROWS_WITH(gen.undo(gov), "you cant undo this action"); // gen should not be able to undo gov's bribe
    }

    SUBCASE("General dont have money to undo"){
        Game game;
        Governor gov(game, "gov");
        General gen(game, "gen");
        gov.tax(); // gov has 3 coins
        gen.tax(); // gen has 2 coins
        gov.tax(); // gov has 6 coins
        gen.gather(); // gen has 3 coins
        gov.tax(); // gov has 9 coins
        gen.gather(); // gen has 4 coins
        gov.coup(gen);
        CHECK_THROWS_WITH(gen.undo(gen),"you dont have enough money"); // gov try to undo gen's gather
    }
}

TEST_CASE("nextTurn"){
    Game game;
    Baron baron(game, "baron");
    General general(game, "general");
    Spy spy(game, "spy");
    baron.tax();
    general.tax();
    spy.tax();
    baron.tax();
    general.tax();
    spy.tax();
    baron.invest();
    general.tax();
    spy.tax();
    baron.coup(general);
    CHECK(game.turn()=="spy");//we should skip general because he is dead
}

TEST_CASE("Dead Player"){
    SUBCASE("GATHER"){
        Game game;
        Governor gov(game, "gov");
        General gen(game, "gen");
        gov.tax(); // gov has 3 coins
        gen.gather(); // gen has 1 coin
        gov.tax(); // gov has 6 coins
        gen.gather(); // gen has 2 coins
        gov.tax(); // gov has 9 coins
        gen.gather(); // gen has 3 coins
        gov.coup(gen); // gov coups gen
        CHECK(gen.isStillAlive() == false); // gen should be dead after coup
        CHECK_THROWS_WITH(gen.gather(), "its not your turn"); // gen should not be able to gather after being dead
    }
    SUBCASE("TAX"){
        Game game;
        Governor gov(game, "gov");
        General gen(game, "gen");
        gov.tax(); // gov has 3 coins
        gen.gather(); // gen has 1 coin
        gov.tax(); // gov has 6 coins
        gen.gather(); // gen has 2 coins
        gov.tax(); // gov has 9 coins
        gen.gather(); // gen has 3 coins
        gov.coup(gen); // gov coups gen
        CHECK(gen.isStillAlive() == false); // gen should be dead after coup
        CHECK_THROWS_WITH(gen.tax(), "its not your turn"); // gen should not be able to tax after being dead
    }
    SUBCASE("bribe"){
        Game game;
        Governor gov(game, "gov");
        Baron baron(game, "baron");
        gov.tax(); // gov has 3 coins
        baron.tax(); // baron has 2 coins
        gov.tax(); // gov has 6 coins
        baron.tax(); // gen has 4 coins
        gov.tax(); // gov has 9 coins
        baron.invest(); // gen has 7 coins
        gov.coup(baron); // gov coups gen
        CHECK(baron.isStillAlive() == false); // gen should be dead after coup
        CHECK_THROWS_WITH(baron.bribe(), "its not your turn"); // gen should not be able to bribe after being dead
    }
    SUBCASE("Arrest"){
        Game game;
        Governor gov(game, "gov");
        Baron baron(game, "baron");
        gov.tax(); // gov has 3 coins
        baron.tax(); // baron has 2 coins
        gov.tax(); // gov has 6 coins
        baron.tax(); // gen has 4 coins
        gov.tax(); // gov has 9 coins
        baron.invest(); // gen has 7 coins
        gov.coup(baron); // gov coups gen
        CHECK(baron.isStillAlive() == false); // gen should be dead after coup
        CHECK_THROWS_WITH(baron.arrest(gov), "its not your turn"); // gen should not be able to arrest after being dead
    }
    SUBCASE("GATHER"){
        Game game;
        Governor gov(game, "gov");
        Baron baron(game, "baron");
        gov.tax(); // gov has 3 coins
        baron.tax(); // baron has 2 coins
        gov.tax(); // gov has 6 coins
        baron.tax(); // gen has 4 coins
        gov.tax(); // gov has 9 coins
        baron.invest(); // gen has 7 coins
        gov.coup(baron); // gov coups gen
        CHECK(baron.isStillAlive() == false); // gen should be dead after coup
        CHECK_THROWS_WITH(baron.sanction(gov), "its not your turn"); // gen should not be able to sanction after being dead
    }
    SUBCASE("GATHER"){
        Game game;
        Governor gov(game, "gov");
        Baron baron(game, "baron");
        gov.tax(); // gov has 3 coins
        baron.tax(); // baron has 2 coins
        gov.tax(); // gov has 6 coins
        baron.tax(); // gen has 4 coins
        gov.tax(); // gov has 9 coins
        baron.invest(); // gen has 7 coins
        gov.coup(baron); // gov coups gen
        CHECK(baron.isStillAlive() == false); // gen should be dead after coup
        CHECK_THROWS_WITH(baron.coup(gov), "its not your turn"); // gen should not be able to coup after being dead
    }
}

TEST_CASE("block arresting"){
    Game game;
    Spy spy(game, "spy");
    General general(game, "general");
    spy.BlockArresting(general);
    spy.tax();
    CHECK_THROWS_WITH(general.arrest(spy), "you cant arrest this turn");
    general.tax();
    spy.tax();
    CHECK_NOTHROW(general.arrest(spy));
}

TEST_CASE("need skip"){
    SUBCASE("governor and Baron"){//baron get extra coin when someone do sunction him;
        Game game;
        Governor gov(game,"gov");
        Baron baron(game,"baron");
        gov.tax();
        baron.gather();
        gov.sanction(baron);
        CHECK(game.turn()=="gov");
    }
    SUBCASE("Not governor and Baron"){//baron get extra coin when someone do sunction him;
        Game game;
        Spy spy(game,"spy");
        Baron baron(game,"baron");
        spy.tax();
        baron.gather();
        spy.gather();
        baron.gather();
        spy.sanction(baron);
        CHECK(game.turn()=="baron");
    }
    SUBCASE("Regular"){
        Game game;
        Spy spy(game,"spy");
        Merchant mer(game,"mer");
        spy.tax();
        mer.gather();
        spy.gather();
        mer.gather();
        spy.sanction(mer);
        CHECK(game.turn()=="spy");
    }
}

TEST_CASE("Merchant"){
    Game game;
    Spy spy(game,"spy");
    Merchant merchant(game,"mer");
    spy.tax();
    merchant.tax();
    spy.tax();
    merchant.tax();
    CHECK(merchant.coins()==4);
    spy.tax();
    CHECK(merchant.coins()==5);//the merchant get one more money
}

TEST_CASE("invest"){
    SUBCASE("not in turn"){
        Game game;
        Spy spy(game,"spy");
        Baron baron(game,"baron");
        CHECK_THROWS_WITH(baron.invest(),"its not your turn");
    }
    SUBCASE("dont have money"){
        Game game;
        Spy spy(game,"spy");
        Baron baron(game,"baron");
        spy.tax();
        CHECK_THROWS_WITH(baron.invest(),"you dont have enough money to invest");
    }
    SUBCASE("10 coins"){
        Game game;
        Baron baron(game,"baron");
        Spy spy(game,"spy");
        baron.tax();
        spy.tax();
        baron.tax();
        spy.tax();
        baron.tax();
        spy.tax();
        baron.tax();
        spy.tax();
        baron.tax();
        spy.tax();
        CHECK_THROWS_WITH(baron.invest(),"you have to coup because you have 10 coins or more");
    }
    SUBCASE("work"){
        Game game;
        Baron baron(game,"baron");
        Spy spy(game,"spy");
        baron.tax();//2
        spy.tax();//2
        baron.tax();//4
        spy.tax();//4
        baron.tax();//6
        spy.tax();//6
        baron.tax();//8
        spy.tax();//8
       
        CHECK_NOTHROW(baron.invest());
    }
}

//invest
