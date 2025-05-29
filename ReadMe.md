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



- there is three ways to run this project you can run the main or the test or to run valgrind on both of then.
    #### run main
    - to run main first time you need to write the next commands:
        - make main
    - after you build the files you can write: ./main
    #### run test
    - to run test you need to write the next commands:
        - make test
    #### run valgrind
    - to run valgrind you need to write the next commands:
        - make valgrind

# files namespace and classes
### Files:
    - Squaremat.hpp Squaremat.cpp
    - doctest.h
    - makefile
    - Main.cpp
    - test.cpp
    - row.hpp row.cpp
### Classes:
    - SquareMat
    - rows
    all the operators are declared in the hpp file
### Data Structures:
    - I build data structures to represent a row for the mat[i][j] operator
### NameSpace
    all the project is under the name space matrix