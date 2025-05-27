#include <SFML/Graphics.hpp>
#include <iostream>
#include "gui.hpp"
using namespace coup;
using std::vector;
using std::string;
/**
 * @brief Displays a welcome screen with a button to start the game.
 * @param font The font to use for the text.
 */
void showWelcomeScreen(sf::Font& font) {
    sf::RenderWindow welcome(sf::VideoMode(500, 250), "Welcome to Coup");

    sf::Text welcomeText("Welcome to Coup Game!", font, 28);
    welcomeText.setPosition(60, 60);
    welcomeText.setFillColor(sf::Color::White);

    sf::RectangleShape startButton(sf::Vector2f(150, 50));
    startButton.setPosition(175, 150);
    startButton.setFillColor(sf::Color(100, 150, 250));

    sf::Text startText("Start", font, 24);
    startText.setPosition(215, 160);
    startText.setFillColor(sf::Color::White);

    while (welcome.isOpen()) {
        sf::Event event;
        while (welcome.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                welcome.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mouse(sf::Mouse::getPosition(welcome));
                if (startButton.getGlobalBounds().contains(mouse)) {
                    welcome.close();  // עובר לחלון הבא
                }
            }
        }

        welcome.clear(sf::Color(20, 20, 20));
        welcome.draw(welcomeText);
        welcome.draw(startButton);
        welcome.draw(startText);
        welcome.display();
    }
}

/**
 * @brief Displays a screen to choose the number of players.
 * @param font The font to use for the text.
 * @return The number of players chosen (between 2 and 6).
 */
int choose_player_screen(sf::Font& font){
    sf::RenderWindow window(sf::VideoMode(600, 300), "Coup - Number of Players");

   

    sf::Text title("Enter number of players (2-6):", font, 24);
    title.setPosition(50, 50);
    title.setFillColor(sf::Color::White);

    sf::RectangleShape inputBox(sf::Vector2f(200, 40));
    inputBox.setPosition(50, 100);
    inputBox.setFillColor(sf::Color(50, 50, 50));
    inputBox.setOutlineThickness(2);
    inputBox.setOutlineColor(sf::Color::White);

    sf::Text inputText("", font, 22);
    inputText.setPosition(60, 105);
    inputText.setFillColor(sf::Color::White);

    sf::RectangleShape button(sf::Vector2f(120, 40));
    button.setPosition(50, 160);
    button.setFillColor(sf::Color(100, 100, 250));

    sf::Text buttonText("Start", font, 22);
    buttonText.setPosition(85, 167);
    buttonText.setFillColor(sf::Color::White);

    sf::Text errorMessage("", font, 18);
    errorMessage.setFillColor(sf::Color::Red);
    errorMessage.setPosition(50, 210);

    std::string input;
    bool selected = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::TextEntered && !selected) {
                if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                    if (input.size() < 1) { // רק ספרה אחת
                        input += static_cast<char>(event.text.unicode);
                        inputText.setString(input);
                        errorMessage.setString(""); // ניקוי הודעת שגיאה
                    }
                } else if (event.text.unicode == 8 && !input.empty()) { // Backspace
                    input.pop_back();
                    inputText.setString(input);
                    errorMessage.setString("");
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mouse(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                if (button.getGlobalBounds().contains(mouse)) {
                    if (!input.empty()) {
                        int numPlayers = std::stoi(input);
                        if (numPlayers >= 2 && numPlayers <= 6) {
                            selected = true;
                            window.close();  // להמשיך למשחק או לחלון הבא
                            return numPlayers;

                        } else {
                            errorMessage.setString("Invalid number! Must be between 2 and 6.");
                        }
                    } else {
                        errorMessage.setString("Please enter a number.");
                    }
                }
            }
        }

        window.clear(sf::Color(30, 30, 30));
        window.draw(title);
        window.draw(inputBox);
        window.draw(inputText);
        window.draw(button);
        window.draw(buttonText);
        window.draw(errorMessage);
        window.display();
    }
}

/**
 * @brief Displays a screen to enter player names.
 * @param font The font to use for the text.
 * @param numPlayers The number of players.
 * @return A vector containing the names of the players.
 */
std::vector<std::string> get_player_names_screen(sf::Font& font, int numPlayers) {
    std::vector<std::string> playerNames;
    sf::RenderWindow window(sf::VideoMode(500, 250), "Enter Player Names");

    sf::Text title("", font, 22);
    title.setPosition(50, 50);
    title.setFillColor(sf::Color::White);

    sf::RectangleShape inputBox(sf::Vector2f(300, 40));
    inputBox.setPosition(50, 100);
    inputBox.setFillColor(sf::Color(50, 50, 50));
    inputBox.setOutlineThickness(2);
    inputBox.setOutlineColor(sf::Color::White);

    sf::Text inputText("", font, 22);
    inputText.setPosition(60, 105);
    inputText.setFillColor(sf::Color::White);

    sf::RectangleShape button(sf::Vector2f(120, 40));
    button.setPosition(50, 160);
    button.setFillColor(sf::Color(100, 100, 250));

    sf::Text buttonText("Continue", font, 20);
    buttonText.setPosition(70, 167);
    buttonText.setFillColor(sf::Color::White);

    std::string input;
    int currentPlayerIndex = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 8 && !input.empty()) {
                    input.pop_back();
                    inputText.setString(input);
                } else if (event.text.unicode >= 32 && event.text.unicode < 127 && input.size() < 15) {
                    input += static_cast<char>(event.text.unicode);
                    inputText.setString(input);
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mouse(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                if (button.getGlobalBounds().contains(mouse)) {
                    if (!input.empty()) {
                        bool flag=false;
                        for(size_t i=0;i<playerNames.size();i++){
                            if(playerNames[i]==input)
                                flag=true;
                        }
                        if(!flag){
                            playerNames.push_back(input);
                            input.clear();
                            inputText.setString("");

                            currentPlayerIndex++;
                            if (currentPlayerIndex >= numPlayers) {
                                window.close();
                            }
                        }else{
                            sf::RenderWindow errorWindow(sf::VideoMode(400, 150), "Error");

                            sf::Text errorMsg("Name already exists. Try another.", font, 20);
                            errorMsg.setFillColor(sf::Color::Red);
                            errorMsg.setPosition(30, 50);

                            while (errorWindow.isOpen()) {
                                sf::Event errEvent;
                                while (errorWindow.pollEvent(errEvent)) {
                                    if (errEvent.type == sf::Event::Closed || errEvent.type == sf::Event::KeyPressed)
                                        errorWindow.close();
                                }

                                errorWindow.clear(sf::Color::Black);
                                errorWindow.draw(errorMsg);
                                errorWindow.display();
                            }
                            input = ""; // reset input
                            inputText.setString("");
                            continue; // let user try again
                        }
                        
                    }
                }
            }
        }

        title.setString("Enter name for Player " + std::to_string(currentPlayerIndex + 1) + ":");

        window.clear(sf::Color(30, 30, 30));
        window.draw(title);
        window.draw(inputBox);
        window.draw(inputText);
        window.draw(button);
        window.draw(buttonText);
        window.display();
    }

    return playerNames;
}

/**
 * @brief Starts the game by creating players with random roles.
 * @param playerNames The names of the players.
 * @param game The game instance.
 * @param playersList The vector to hold player pointers.
 */
void startGame(const std::vector<std::string>& playerNames,Game & game,vector<Player*> & playersList) {
    std::srand(std::time(nullptr));//initilaize the random
    std::vector<std::string> roles = {"Governor","Spy","Baron","General","Judge", "Merchant"};
    for(const std::string& name : playerNames) {
        int x=rand() % roles.size();
        std::string role = roles[x];
        CreatePlayer(game, name, role, playersList);
    }
}


void showPlayerTurn(Game& game) {
    sf::RenderWindow window(sf::VideoMode(1000, 750), "Player Turn");
    bool selectingTarget = false;
    std::vector<Player*> targets;

    std::vector<sf::RectangleShape> targetButtons;
    std::vector<sf::Text> targetButtonTexts;
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Could not load font\n";
        return;
    }

    sf::Text nameText("", font, 30);
    nameText.setPosition (50, 30);

    sf::Text roleText("", font, 30);
    roleText.setPosition(50, 80);

    sf::Text coinsText("", font, 30);
    coinsText.setPosition(50, 130);

    sf::Text errorText("", font, 24);
    errorText.setFillColor(sf::Color::Red);
    //I want to display the error text in the right side to make sure the buttons will not hide it
    float windowWidth = 1000.f;
    float marginRight = 0.f;

    float posX = windowWidth - marginRight - errorText.getLocalBounds().width;


    errorText.setPosition(posX, 0);
    sf::Text Special("",font,24);
    float specialX = windowWidth - marginRight - Special.getLocalBounds().width;
    Special.setPosition(specialX,700);

    sf::Clock errorClock;

    std::vector<std::string> actions;
    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> buttonTexts;

    Player* lastPlayer = nullptr;

    auto updatePlayerView = [&](Player* p) {
        nameText.setString("Name: " + p->getName());
        roleText.setString("Role: " + p->getRole());
        coinsText.setString("Coins: " + std::to_string(p->coins()));

        actions = p->getAvailableActions();
        buttons.clear();
        buttonTexts.clear();

        float y = 200;
        for (const std::string& action : actions) {
            sf::RectangleShape button(sf::Vector2f(200, 40));
            button.setFillColor(sf::Color(100, 100, 250));
            button.setPosition(50, y);

            sf::Text actionText(action, font, 24);
            actionText.setFillColor(sf::Color::White);
            actionText.setPosition(60, y + 5);

            buttons.push_back(button);
            buttonTexts.push_back(actionText);
            y += 60;
        }
        
    };
    string selectedAction;
    auto updateTargetList = [&]() {
        targetButtons.clear();
        targetButtonTexts.clear();

        float y = 200;
        float x = 300;

        for (Player* p : targets) {
            sf::RectangleShape button(sf::Vector2f(200, 40));
            button.setFillColor(sf::Color(100, 250, 100));
            button.setPosition(x, y);

            sf::Text txt(p->getName(), font, 24);
            txt.setFillColor(sf::Color::Black);
            txt.setPosition(x + 10, y + 5);

            targetButtons.push_back(button);
            targetButtonTexts.push_back(txt);

            y += 60;
        }
    };

    
    while (window.isOpen()) {
        try
        {
            string winnerName =game.winner();
            window.close(); // the game is came to the end
            showWinnerWindow(winnerName);  // open new window to announce who is the winner
            return;
        }
        catch(const std::exception& e)
        {
            
        }
        
        Player* currentPlayer = game.getCurrentPlayer();
        if (currentPlayer != lastPlayer) {
            lastPlayer = currentPlayer;
            specialX = windowWidth - marginRight - Special.getLocalBounds().width;
            Special.setPosition(specialX,700);
            updatePlayerView(currentPlayer);
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                for (size_t i = 0; i < buttons.size(); ++i) {
                    if (buttons[i].getGlobalBounds().contains(mousePos)) {
                        std::string action = actions[i];
                        try {
                            if (action == "tax") {
                                currentPlayer->tax();
                            } else if (action == "gather") {
                                currentPlayer->gather();
                            } else if (action == "bribe") {
                                currentPlayer->bribe();
                            } else if (action == "arrest" || action == "coup" || action=="sanction" || action=="undo" || action=="peek" || action=="blockArresting") {
                                selectingTarget = true;
                                selectedAction=action;
                                targets.clear();
                                for (Player* p : game.getPlayersList()) {
                                    if (p != currentPlayer && p->isStillAlive()) {
                                        targets.push_back(p);
                                    }
                                }
                                updateTargetList();
                            } else if (action == "invest"){
                                Baron* baron= dynamic_cast<Baron*>(currentPlayer);
                                if (baron){
                                    baron->invest();
                                } 
                            }
                            coinsText.setString("Coins: " + std::to_string(currentPlayer->coins()));

                        } catch (const std::exception& ex) {
                            errorText.setString(ex.what());
                            float posX = windowWidth - marginRight - errorText.getLocalBounds().width;
                            errorText.setPosition(posX, 0);
                            errorClock.restart();
                        }
                    }
                }
            }
        
            if (selectingTarget && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                for (size_t i = 0; i < targetButtons.size(); ++i) {
                    if (targetButtons[i].getGlobalBounds().contains(mousePos)) {
                        Player* target = targets[i];
                        try {
                            if (selectedAction == "arrest") {
                                currentPlayer->arrest(*target);
                            } else if (selectedAction == "coup") {
                                currentPlayer->coup(*target);
                            } else if (selectedAction == "sanction") {
                                currentPlayer->sanction(*target);
                            }else if (selectedAction == "undo") {
                                if (currentPlayer->getRole() == "Governor") {
                                    Governor* governor = dynamic_cast<Governor*>(currentPlayer);
                                    if (governor) governor->undo(*target);
                                } else if (currentPlayer->getRole() == "Judge") {
                                    Judge* judge = dynamic_cast<Judge*>(currentPlayer);
                                    if (judge) judge->undo(*target);
                                } else {
                                    throw std::runtime_error("This role cannot perform undo.");
                                }
                            }else if(selectedAction=="peek"){
                                Spy* spy=dynamic_cast<Spy*>(currentPlayer);
                                if (spy){
                                    int x = spy->peek(*target);
                                    Special.setString(target->getName()+" have "+std::to_string(x)+"coins");
                                    specialX = windowWidth - marginRight - Special.getLocalBounds().width;
                                    Special.setPosition(specialX,700);
                                } 
                            }else if(selectedAction=="blockArresting"){
                                Spy* spy=dynamic_cast<Spy*>(currentPlayer);
                                if (spy){
                                    spy->BlockArresting(*target);
                                }
                            }
                            coinsText.setString("Coins: " + std::to_string(currentPlayer->coins()));
                            selectingTarget = false;
                            selectedAction="";
                        } catch (const std::exception& ex) {
                            errorText.setString(ex.what());
                            float posX = windowWidth - marginRight - errorText.getLocalBounds().width;
                            errorText.setPosition(posX, 0);
                            errorClock.restart();
                            selectingTarget = false;
                        }
                        break;//we found a target, no need to check others
                    }
                }
                continue;
            }
        }
        if (!errorText.getString().isEmpty() && errorClock.getElapsedTime().asSeconds() > 3) {
            errorText.setString("");
        }

        window.clear();
        if (selectingTarget) {
            for (size_t i = 0; i < targetButtons.size(); ++i) {
                window.draw(targetButtons[i]);
                window.draw(targetButtonTexts[i]);
            }
        }
        window.draw(Special);
        window.draw(errorText);
        window.draw(nameText);
        window.draw(roleText);
        window.draw(coinsText);

        for (size_t i = 0; i < buttons.size(); ++i) {
            window.draw(buttons[i]);
            window.draw(buttonTexts[i]);
        }

        window.display();
    }
}


void showWinnerWindow(const std::string& winnerName) {
    sf::RenderWindow winWindow(sf::VideoMode(600, 200), "Winner!");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Could not load font for winner window\n";
        return;
    }

    sf::Text winText("Winner: " + winnerName, font, 40);
    winText.setFillColor(sf::Color::Green);
    winText.setPosition(50, 80);

    while (winWindow.isOpen()) {
        sf::Event event;
        while (winWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                winWindow.close();
            }
        }

        winWindow.clear(sf::Color::Black);
        winWindow.draw(winText);
        winWindow.display();
    }
}


int main() {
    
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Could not load font!" << std::endl;
        return 1;
    }
    showWelcomeScreen(font);
    int playerAmount = choose_player_screen(font);
    std::vector<std::string> playerNames = get_player_names_screen(font, playerAmount);
    std::vector<Player*> playersList; // Vector to hold player pointers
    Game game{}; // Create a new game instance
    startGame(playerNames,game,playersList);
    // בדיקה והדפסה
    std::cout << "Players in the game:" << std::endl;
    showPlayerTurn(game); // Show the first player's turn as an example
    return 0;
}
