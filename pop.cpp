#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Jeu.hpp"

/*
Compiler avec
g++ -c pop.cpp => pour compiler sans linker => resulte en fichier .o
g++ -o yousuke pop.o -lsfml-graphics -lsfml-window -lsfml-system
*/

enum class GameState {
    START, RUNNING, VICTORY
};

struct Selection {
    sf::CircleShape cursor;
    int columnSelected;
    int lastRowPlayed;
    int lastColumnPlayed;
};

class GraphicalJeu
{
    public:
        GraphicalJeu();
        void addTokenToColumn(sf::RenderWindow* window);
        void drawGridOnWindow(sf::RenderWindow* window);
        void drawCursorOnWindow(sf::RenderWindow* window);
        void drawTokensOnGrid(sf::RenderWindow* window);
        void moveCursorToNextColumn(bool right);
        bool checkVictory() {return puissance4.checkVictory();};
        bool checkVictoryFromPosition(int row, int column) {return puissance4.checkVictoryFromPosition(row, column);};
        int getCurrentPlayer() {return puissance4.getCurrentPlayer();};
        void changeCurrentPlayer() {puissance4.changeCurrentPlayer();};
        void testJeuFini() {
            puissance4.addToken(5,0,1);
            puissance4.addToken(5,1,1);
            puissance4.addToken(5,2,1);
        };
        GameState getGameState() { return state;};
        void setGameState(GameState newState) {state = newState;};
        void clearGrid();
    private:
        GameState state; 
        Jeu puissance4;
        sf::RectangleShape columnShapes[COLUMNS];
        Selection playerSelection;
        std::vector<sf::CircleShape> displayedTokens;
};

 GraphicalJeu::GraphicalJeu() {

    // Default State
    state = GameState::RUNNING;

    // Grid
    for(int i = 0; i < COLUMNS; i++) {
        this->columnShapes[i].setSize(sf::Vector2f(BOARD_COLUMN_WIDTH, BOARD_HEIGHT));
        this->columnShapes[i].setFillColor(sf::Color::Blue);
        this->columnShapes[i].setPosition(WIDTH/5 + (BOARD_COLUMN_WIDTH + BOARD_COLUMN_MARGIN) * i, HEIGHT/8);
    }

    // Player Cursor to select in which column the token must be
    playerSelection.cursor.setRadius(20);
    playerSelection.cursor.setPointCount(3);

    sf::Texture cursorTexture;
    cursorTexture.loadFromFile("malachite.png");
    playerSelection.cursor.setTexture(&cursorTexture);

    sf::Vector2f firstColumnPosition = columnShapes[0].getPosition();
    playerSelection.cursor.setPosition(firstColumnPosition.x, firstColumnPosition.y + BOARD_HEIGHT + 10.f); // Set position under first column
    playerSelection.columnSelected = 0; // Select first column
}

void GraphicalJeu::addTokenToColumn(sf::RenderWindow* window)
{
    int columnNumber = playerSelection.columnSelected;

    if(puissance4.filledColumn(columnNumber)){
        std::cout << "Colonne déjà remplie" << std::endl;
        return; // Column already full
    }

    
    // Adding token in the 2D-array representing the grid
    puissance4.addToken(columnNumber);

    puissance4.printJeu();

    // Display token in window
    sf::Vector2f columnPosition = columnShapes[columnNumber].getPosition();
    int numberOfTokensInColumn = puissance4.getNumberOfTokensInColumn(columnNumber);
    sf::CircleShape token(BOARD_COLUMN_WIDTH/2); // Un Token de rayon BOARD_COLUMN_WIDTH/2)

    if(puissance4.getCurrentPlayer() == PLAYER_1) {
        token.setFillColor(sf::Color::Red);
    }
    else { // JOUEUR 2
       token.setFillColor(sf::Color::Yellow);
    }

    // Token position is based on the number of tokens already in column
    // if 0, put a token at the bottom = columnPosition.y + BOARD_HEIGHT
    // if 1, put a token right above = columnPosition.y + BOARD_HEIGHT - BOARD_COLUMN_WIDTH
    // if 5, put it at the top
    token.setPosition(columnPosition.x, columnPosition.y + BOARD_HEIGHT - BOARD_COLUMN_WIDTH * numberOfTokensInColumn);

    displayedTokens.push_back(token);
}

void GraphicalJeu::drawGridOnWindow(sf::RenderWindow* window) {
    for(int i = 0; i < COLUMNS; i++) {
        window->draw(columnShapes[i]);
    }
}

void GraphicalJeu::drawCursorOnWindow(sf::RenderWindow* window) {
    window->draw(playerSelection.cursor);
}

void GraphicalJeu::drawTokensOnGrid(sf::RenderWindow* window) {
    for(sf::CircleShape token : displayedTokens) {
        window->draw(token);
    }
}

void GraphicalJeu::moveCursorToNextColumn(bool right) {
    if(right) { // move cursor to right
        if(playerSelection.columnSelected == COLUMNS - 1) {
            return; // Cursor at the far right of the grid
        }
        playerSelection.cursor.move((BOARD_COLUMN_WIDTH + BOARD_COLUMN_MARGIN), 0);
        playerSelection.columnSelected += 1; 
    }
    else { // move cursor to left
        if(playerSelection.columnSelected == 0) {
            return; // Cursor at the far left of the grid
        }
        playerSelection.cursor.move(-(BOARD_COLUMN_WIDTH + BOARD_COLUMN_MARGIN), 0);
        playerSelection.columnSelected -= 1;
    }
}

void GraphicalJeu::clearGrid() {

    // Empty the grid
    puissance4.emptyGrid();
    
    // Clear the vectors of all tokens currently displayed on screen
    displayedTokens.clear();

}

int main()
{
    // Window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Connect4", sf::Style::Close | sf::Style::Resize);

    // Background
    sf::Texture textureBackground;
    if(!textureBackground.loadFromFile("background.png")){
        std::cout << "Background not properly loaded" << std::endl;
        return -1;
    }

    sf::Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);

    // Game
    GraphicalJeu videoGame;
    videoGame.clearGrid();

    // Add Tokens in columns

    // Cursor speed
    float cursor1Speed = 0;

    sf::Clock clock;

    // Track if the game is running or not
    bool paused = true;

    sf::Text victoryText;
    victoryText.setString("PLAYER X WON !\nPress Enter to restart the game.");
    victoryText.setCharacterSize(70);
    victoryText.setFillColor(sf::Color::Cyan);

    sf::Font myFont;
    myFont.loadFromFile("UbuntuMono-B.ttf");

    victoryText.setFont(myFont);

    sf::FloatRect textRect = victoryText.getLocalBounds();
    victoryText.setOrigin(textRect.left + textRect.width / 2.0f,
    textRect.top + textRect.height / 2.0f);
    victoryText.setPosition(WIDTH / 2.0f, HEIGHT / 2.0f);
    //victoryText.setPosition(0, 0);
    while(window.isOpen())
    {
        /*
        *************************
        Players input
        *************************
        */

        // Keyboard controls

        // Close the window
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
            window.close();
        }

        // Start the game
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)){
            paused = !paused;
        }

        // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)){
        //     player.move(0, -0.1f);
        // }
        // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
        //     player.move(0, 0.1f);
        // }

        // Each column are spaced BOARD_COLUMN_WIDTH
        // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)){
        // //     videoGame..move(-BOARD_COLUMN_WIDTH, 0);
        //        videoGame.moveCursorToNextColumn(false);
        // }
        // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)){
        // //     playerCursor.move(BOARD_COLUMN_WIDTH, 0);
        //         videoGame.moveCursorToNextColumn(true);
        // }

        /*
        *************************
        Update the scene
        *************************
        */
    //    if(paused == false) {
    //         // Measure time
    //         sf::Time dt = clock.restart();

    //         // Moving cursor
            
    //         // how fast
    //         //srand((int)time(0));
    //         cursor1Speed = 100;

    //         // how high 
    //         //srand((int)time(0) * 10);
    //         float height = playerCursor.getPosition().y + (cursor1Speed * dt.asSeconds());
    //         playerCursor.setPosition(playerCursor.getPosition().x, height);

    //         if(playerCursor.getPosition().y > HEIGHT) {
    //             playerCursor.setPosition(playerCursor.getPosition().x, -20);
    //         }
    //     }

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();

                case sf::Event::KeyPressed:
                    // Commands
                    if(event.key.code == sf::Keyboard::Key::Left) {
                        videoGame.moveCursorToNextColumn(false);
                    }
                    else if(event.key.code == sf::Keyboard::Key::Right) {
                        videoGame.moveCursorToNextColumn(true);
                    }
                    else if(event.key.code == sf::Keyboard::Return) {

                        if(videoGame.getGameState() == GameState::RUNNING) {
                            videoGame.addTokenToColumn(&window);

                            if(videoGame.checkVictory()) {
                                if(videoGame.getCurrentPlayer() == PLAYER_1) {
                                    victoryText.setString("PLAYER 1 WON !\nPress Enter to restart the game.");
                                }
                                else {
                                    victoryText.setString("PLAYER 2 WON !\nPress Enter to restart the game.");
                                }

                                videoGame.setGameState(GameState::VICTORY);
                            }
                            else {
                                // Change current player
                                videoGame.changeCurrentPlayer();
                            }
                        }
                        else if(videoGame.getGameState() == GameState::VICTORY) {
                            videoGame.clearGrid();
                            videoGame.setGameState(GameState::RUNNING);
                        }
                        
                        
                    }

        //         case sf::Event::MouseButtonPressed:
        //             window.clear();
        //             window.draw(shape2);
        //             window.display();

        //         case sf::Event::TextEntered:
        //             std::cout << event.text.unicode << std::endl;
                    
            }
        }

        /*
        *************************
        Draw the scene
        *************************
        */
        
        // Token position is based on the number of tokens already in column
        // if 0, put a token at the bottom
        // if 5, put it at the top
        // if 6, don't do anything
                
        // if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

        //     sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        //     player.setPosition((float) mousePos.x, (float) mousePos.y);
        // }


        // Clear everything from the last frame
        window.clear();

        // Draw the background
        window.draw(spriteBackground);

        switch (videoGame.getGameState())
        {
            case GameState::START:
                break;
            
            case GameState::RUNNING:
                // Draw the grid
                videoGame.drawGridOnWindow(&window);

                // Draw the cursor
                videoGame.drawCursorOnWindow(&window);

                // Draw tokens
                videoGame.drawTokensOnGrid(&window);
                break;

            case GameState::VICTORY:
                // Draw victory text
                window.draw(victoryText);
                break;
                
            default:
                break;
        }

        window.display();
    }
    return EXIT_SUCCESS;
}