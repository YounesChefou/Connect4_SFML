#include <SFML/Graphics.hpp>
#include <iostream>
/*
Compiler avec
g++ -c pop.cpp => pour compiler sans linker => resulte en fichier .o
g++ -o yousuke pop.o -lsfml-graphics -lsfml-window -lsfml-system
*/

const int WIDTH = 1280;
const int HEIGHT = 720;

int main()
{
    // Window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Connect4", sf::Style::Close | sf::Style::Resize);

    //Background
    sf::Texture background;
    background.create(20.f, 20.f);

    // Connect4 board
    sf::Image board;
    board.loadFromFile("Connect4_Empty.png");

    // Player character
    sf::RectangleShape player(sf::Vector2f(100.f, 100.f));
    //shape.setFillColor(sf::Color::Green);
    player.setOrigin(50.0f, 50.f);

    sf::CircleShape player2(50.f);
    player2.setFillColor(sf::Color::Blue);
    
    sf::Texture playerTexture;
    playerTexture.loadFromFile("malachite.png");
    
    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();

                // case sf::Event::MouseButtonPressed:
                //     window.clear();
                //     window.draw(shape2);
                //     window.display();

                // case sf::Event::TextEntered:
                //     std::cout << event.text.unicode << std::endl;
                    
            }
        }

        // Keyboard controls
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)){
            player.move(0, -0.1f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
            player.move(0, 0.1f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)){
            player.move(-0.1f, 0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
            player.move(0.1f, 0);
        }
        
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            player.setPosition((float) mousePos.x, (float) mousePos.y);
        }


        window.clear();
        window.draw(player);
        window.display();
    }
    return EXIT_SUCCESS;
}