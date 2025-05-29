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
    sf::RenderWindow welcome(sf::VideoMode(480, 720), "Welcome to Coup");
    
     // load the pictuures
    sf::Texture imageTexture;
    if (!imageTexture.loadFromFile("GUI/welcome_background.png")) {
        std::cerr << "Failed to load image coup_picture.png" << std::endl;
    }
    sf::Sprite imageSprite(imageTexture);
    imageSprite.setPosition(0, 0);



    sf::RectangleShape startButton(sf::Vector2f(150, 50));
    startButton.setPosition(165, 640);
    startButton.setFillColor(sf::Color(171, 153, 123));
    // startButton.setFillColor(sf::Color::White);

    sf::Text startText("Start", font, 24);
    startText.setPosition(205, 665);
    startText.setFillColor(sf::Color::White);

    while (welcome.isOpen()) {
        sf::Event event;
        while (welcome.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                welcome.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mouse(sf::Mouse::getPosition(welcome));
                if (startButton.getGlobalBounds().contains(mouse)) {
                    welcome.close();
                }
            }
        }
        welcome.clear(sf::Color(20, 20, 20));
        welcome.draw(imageSprite);
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
    sf::RenderWindow window(sf::VideoMode(512, 512), "Coup - Number of Players");
    sf::Texture imageTexture;
    if (!imageTexture.loadFromFile("GUI/playersNumber.jpg")) {
        std::cerr << "Failed to load image coup_picture.png" << std::endl;
    }
    sf::Sprite imageSprite(imageTexture);
    imageSprite.setPosition(0, 0);
   

    sf::RectangleShape button2(sf::Vector2f(60, 60));
    button2.setPosition(60, 350);
    button2.setFillColor(sf::Color(0,0,0,0));

    sf::RectangleShape button3(sf::Vector2f(60, 60));
    button3.setPosition(140, 350);
    button3.setFillColor(sf::Color(0,0,0,0));

    sf::RectangleShape button4(sf::Vector2f(60, 60));
    button4.setPosition(220, 350);
    button4.setFillColor(sf::Color(0,0,0,0));

    sf::RectangleShape button5(sf::Vector2f(60, 60));
    button5.setPosition(300, 350);
    button5.setFillColor(sf::Color(0,0,0,0));

    sf::RectangleShape button6(sf::Vector2f(60, 60));
    button6.setPosition(380, 350);
    button6.setFillColor(sf::Color(0,0,0,0));


    std::string input;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();


            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mouse(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                if (button2.getGlobalBounds().contains(mouse)) {
                    return 2;
                }
                if (button3.getGlobalBounds().contains(mouse)) {
                    return 3;
                }
                if (button4.getGlobalBounds().contains(mouse)) {
                    return 4;
                }
                if (button5.getGlobalBounds().contains(mouse)) {
                    return 5;
                }
                if (button6.getGlobalBounds().contains(mouse)) {
                    return 6;
                }
            }
        }

        window.clear(sf::Color(30, 30, 30));
        window.draw(imageSprite);
        window.draw(button2);
        window.draw(button3);
        window.draw(button4);
        window.draw(button5);
        window.draw(button6);
        window.display();
    }
    return 0;//i will not reach this line but this is to avoid warning in the make file
}

/**
 * @brief Displays a screen to enter player names.
 * @param font The font to use for the text.
 * @param numPlayers The number of players.
 * @return A vector containing the names of the players.
 */
std::vector<std::string> get_player_names_screen(sf::Font& font, int numPlayers) {
    std::vector<std::string> playerNames;
    sf::RenderWindow window(sf::VideoMode(400, 400), "Enter Player Names");
    sf::Texture imageTexture;
    if (!imageTexture.loadFromFile("GUI/names.jpg")) {
        std::cerr << "Failed to load image coup_picture.png" << std::endl;
    }
    sf::Sprite imageSprite(imageTexture);
    imageSprite.setPosition(0, 0);
    sf::Text title("", font, 30);
    title.setPosition(30, 100);
    title.setFillColor(sf::Color::White);

    sf::RectangleShape inputBox(sf::Vector2f(300, 60));
    inputBox.setPosition(50, 150);
    inputBox.setFillColor(sf::Color(91,55,29));
    inputBox.setOutlineThickness(2);
    inputBox.setOutlineColor(sf::Color::White);

    sf::Text inputText("", font, 40);
    inputText.setPosition(60, 155);
    inputText.setFillColor(sf::Color(181,148,107));
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

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            
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

        title.setString("Enter name for Player " + std::to_string(currentPlayerIndex + 1) + ":");

        window.clear(sf::Color(30, 30, 30));
        window.draw(imageSprite);
        window.draw(title);
        window.draw(inputBox);
        window.draw(inputText);
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
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "Player Turn");
    sf::Texture imageTexture;
    if (!imageTexture.loadFromFile("GUI/players.jpeg")) {
        std::cerr << "Failed to load image coup_picture.png" << std::endl;
    }
    sf::Sprite imageSprite(imageTexture);
    imageSprite.setPosition(0, 0);
    bool selectingTarget = false;
    std::vector<Player*> targets;
    bool showCancel=false;
    std::vector<sf::RectangleShape> targetButtons;
    std::vector<sf::Text> targetButtonTexts;
    sf::Font font;
    if (!font.loadFromFile("GUI/PTSerif-Bold.ttf")) {
        std::cerr << "Could not load font\n";
        return;
    }

    sf::Text nameText("", font, 40);
    nameText.setPosition (50, 200);
    nameText.setFillColor(sf::Color(85,51,23));

    sf::Text roleText("", font, 40);
    roleText.setFillColor(sf::Color(85,51,23));
    roleText.setPosition(50, 250);

    sf::Text coinsText("", font, 40);
    coinsText.setPosition(50, 300);
    coinsText.setFillColor(sf::Color(85,51,23));

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
    string answer;
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

        float y = 370;
        for (const std::string& action : actions) {
            sf::RectangleShape button(sf::Vector2f(300, 60));
            button.setFillColor(sf::Color(85, 51, 23));
            button.setPosition(362, y);

            sf::Text actionText(action, font, 36);
            actionText.setFillColor(sf::Color(180,148,107));
            actionText.setPosition(400, y + 5);

            buttons.push_back(button);
            buttonTexts.push_back(actionText);
            y += 70;
        }
        
    };
    string selectedAction;
    auto updateTargetList = [&]() {
        targetButtons.clear();
        targetButtonTexts.clear();

        float y = 370;
        float x = 700;

        for (Player* p : targets) {
            sf::RectangleShape button(sf::Vector2f(200, 40));
            button.setFillColor(sf::Color(85, 51, 23));
            button.setPosition(x, y);

            sf::Text txt(p->getName(), font, 24);
            txt.setFillColor(sf::Color(180,148,107));
            txt.setPosition(x + 10, y + 5);

            targetButtons.push_back(button);
            targetButtonTexts.push_back(txt);

            y += 60;
        }
    };

    
    while (window.isOpen()) {
        
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
                                selectingTarget=false;
                                for(Player* p:game.getPlayersList()){
                                    if(p->getRole()=="Governor" && p->isStillAlive() && p->getName()!=currentPlayer->getName()){
                                        showCancel=true;
                                        answer=showCancelConfirmation(window,font,p->getName());
                                        std::cout<<answer<<std::endl;
                                        if(answer=="yes"){
                                            Governor* governor = dynamic_cast<Governor*>(p);
                                            if (governor){
                                                governor->undo(*currentPlayer);
                                                break;
                                            };
                                        }
                                        showCancel=false;
                                    }
                                }
                            } else if (action == "gather") {
                                currentPlayer->gather();
                                showCancel=false;
                                selectingTarget=false;
                            } else if (action == "bribe") {
                                currentPlayer->bribe();
                                showCancel=true;
                                selectingTarget=false;
                                for(Player* p:game.getPlayersList()){
                                    if(p->getRole()=="Judge" && p->isStillAlive()){
                                        showCancel=true;
                                        answer=showCancelConfirmation(window,font,p->getName());
                                        std::cout<<answer<<std::endl;
                                        if(answer=="yes"){
                                            Judge* judge = dynamic_cast<Judge*>(p);
                                            if (judge){
                                                judge->undo(*currentPlayer);
                                               
                                                break;
                                            }
                                        }
                                        showCancel=false;
                                    }
                                }
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
                                for(Player* p:game.getPlayersList()){
                                    if(p->getRole()=="General" && (p->isStillAlive() || p->getName()==target->getName()) && p->coins()>=5){
                                        showCancel=true;
                                        answer=showCancelConfirmation(window,font,p->getName());
                                        std::cout<<answer<<std::endl;
                                        if(answer=="yes"){
                                            General* general = dynamic_cast<General*>(p);
                                            if (general){
                                                general->undo(*target);
                                                break;
                                            };
                                        }
                                        showCancel=false;
                                    }
                                }

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
        window.draw(imageSprite);
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
        if(!showCancel){
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
        }
        window.display();
    }
}

string showCancelConfirmation(sf::RenderWindow& mainWindow, sf::Font& font, string name) {
    // Create overlay background
    sf::RectangleShape overlay(sf::Vector2f(mainWindow.getSize().x, mainWindow.getSize().y));
    overlay.setFillColor(sf::Color(0, 0, 0, 180)); // Semi-transparent black

    // Create popup background
    sf::RectangleShape popup(sf::Vector2f(400, 200));
    popup.setPosition(
        (mainWindow.getSize().x - 400) / 2.0f,
        (mainWindow.getSize().y - 200) / 2.0f
    );
    popup.setFillColor(sf::Color(50, 50, 50));
    popup.setOutlineThickness(2);
    popup.setOutlineColor(sf::Color::White);

    // Setup text and buttons
    sf::Text questionText(name + " Do you want to cancel the last action?", font, 18);
    questionText.setFillColor(sf::Color::White);
    questionText.setPosition(
        popup.getPosition().x + 30,
        popup.getPosition().y + 40
    );

    // Yes button
    sf::RectangleShape yesButton(sf::Vector2f(100, 40));
    yesButton.setPosition(
        popup.getPosition().x + 60,
        popup.getPosition().y + 120
    );
    yesButton.setFillColor(sf::Color(70, 200, 70));

    sf::Text yesText("Yes", font, 20);
    yesText.setFillColor(sf::Color::Black);
    yesText.setPosition(
        yesButton.getPosition().x + 35,
        yesButton.getPosition().y + 5
    );

    // No button
    sf::RectangleShape noButton(sf::Vector2f(100, 40));
    noButton.setPosition(
        popup.getPosition().x + 240,
        popup.getPosition().y + 120
    );
    noButton.setFillColor(sf::Color(200, 70, 70));

    sf::Text noText("No", font, 20);
    noText.setFillColor(sf::Color::Black);
    noText.setPosition(
        noButton.getPosition().x + 35,
        noButton.getPosition().y + 5
    );

    while (true) {
        sf::Event event;
        while (mainWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                mainWindow.close();
                return "no";
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(mainWindow);
                
                if (yesButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    return "yes";
                }
                else if (noButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    return "no";
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    return "no2";
                }
            }
        }

        // Draw confirmation dialog over the main window
        mainWindow.draw(overlay);
        mainWindow.draw(popup);
        mainWindow.draw(questionText);
        mainWindow.draw(yesButton);
        mainWindow.draw(yesText);
        mainWindow.draw(noButton);
        mainWindow.draw(noText);
        mainWindow.display();
    }
}


void showWinnerWindow(const std::string& winnerName) {
    sf::RenderWindow winWindow(sf::VideoMode(780, 780), "Winner!");    
     // load the pictuures
    sf::Texture imageTexture;
    if (!imageTexture.loadFromFile("GUI/winner.jpeg")) {
        std::cerr << "Failed to load image coup_picture.png" << std::endl;
    }
    sf::Sprite imageSprite(imageTexture);
    imageSprite.setPosition(0, 0);
    sf::Font font;
    if (!font.loadFromFile("GUI/PTSerif-Bold.ttf")) {
        std::cerr << "Could not load font for winner window\n";
        return;
    }

    sf::Text winText(winnerName, font, 80);
    winText.setFillColor(sf::Color(85,51,23));
    winText.setPosition(370, 550);

    while (winWindow.isOpen()) {
        sf::Event event;
        while (winWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                winWindow.close();
            }
        }

        winWindow.clear(sf::Color::Black);
        winWindow.draw(imageSprite);
        winWindow.draw(winText);
        winWindow.display();
    }
}


int main() {
    
    sf::Font font;
    if (!font.loadFromFile("GUI/PTSerif-Bold.ttf")) {
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