#include <iostream>
#include "Connect4_SFML.hpp"

int main()
{
    // Window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Connect4", sf::Style::Close | sf::Style::Resize);

    // Background
    sf::Texture textureBackground;
    if(!textureBackground.loadFromFile("assets/background.png")){
        std::cout << "Background not properly loaded" << std::endl;
        return -1;
    }

    sf::Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);

    // Game
    Connect4_SFML videoGame;
    videoGame.clearGrid();

    // Add Tokens in columns

    // // Cursor speed
    // float cursor1Speed = 0;

    sf::Clock clock;

    // Track if the game is running or not
    bool paused = true;

    sf::Text victoryText;
    victoryText.setString("PLAYER X WON !\nPress Enter to restart the game.");
    victoryText.setCharacterSize(70);
    victoryText.setFillColor(sf::Color::Cyan);

    sf::Font myFont;
    myFont.loadFromFile("assets/UbuntuMono-B.ttf");

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