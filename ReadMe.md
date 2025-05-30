
coup assignment

# student information:
- name: dotan danino
- id 328144951
- gmail: dotandanino@gmail.com
# project information:
- In this project i had implemnted the game COUP.
- every  player have this actions:

 Action             | Description                                                      |
|--------------------|------------------------------------------------------------------|
| `gather`           | Take 1 coin from the bank                                        |
| `tax`              | Take 2 coins from the bank                                       |
| `bribe`            | Get an extra turn                                                |
| `arrest`           | Pick another player and take 1 coin from them                    |
| `sanction`         | Disable another player from doing finance actions (tax/gather)   |
| `coup`             | Coup another player and kick them out of the game                |

- I this type of players with this special action

 Type            | Special ability                                                            |
|----------------|----------------------------------------------------------------------------|
| `Governor`     | Take 3 coins from the bank when  using tax ,can undo tax(undo is free)     |
| `Spy`          | Block another players from arresting , look at the coins of another Player |
| `Baron`        | can invest 3 coins and get 6 , get 1 coin when he is under sanction        |
| `General`      | can undo coup , get the coin back when someone arrest him                  |
| `Judge`        | can undo bribe , if someonde do sanction on him he need to pay 4 coins     |
| `Merchant`     | get an extra coins if he starts turn with 3 coins or more, in arrest pay 2 for bank insted fo pay to the Player                |


- there is four ways to run this project you can run the main or the test or to run valgrind on both of then.
    #### run Demo
    - to run main first time you need to write the next commands:
        - make Demo
    - after you build the files you can write: ./Demo
    #### run test
    - to run test you need to write the next commands:
        - make test
    #### run valgrind
    - to run valgrind(on both Demo and test) you need to write the next commands:
        - make valgrind
    #### run Gui
    - to run valgrind you need to write the next commands:
        - make gui
    

# files namespace and classes
### Files:
    -   GUI(folder):
        - gui.cpp
        - gui.hpp
        - names.jpg
        - players.jpeg
        - playersNumber.jpeg
        - playersNumber.jpg
        - PTSerif-Bold.ttf
        - PTSerif-Regular.ttf
        - welcome_background.png
        - winner.jpeg

    -include(folder):
        - Baron.hpp
        - General.hpp
        - Governor.hpp
        - Spy.hpp
        - Judge.hpp
        - Merchant.hpp
        - Game.hpp
        - Player.hpp
        - playerFactory.hpp 
    
    -srcs(folder):
        - Baron.cpp
        - General.cpp
        - Governor.cpp
        - Spy.cpp
        - Judge.cpp
        - Merchant.cpp
        - Game.cpp
        - Player.cpp
        - playerFactory.cpp

    -TEST:
        - test.cpp
        - doctest.h


    - makefile
    - Demo.cpp
    

### Classes:
    - Game
    - Player
    - Baron
    - General
    - Governor
    - Judge
    - Merchant
    - Spy

### Data Structures:
    i didnt need to build any Data Structures to this project 
### NameSpace
    all the project excecpt the GUI is under the name space Coup