#include "Connect4.hpp"
#include "Constants.hpp"
#include <iostream>
#include <string>

/*
    Command line version of the game.
*/

int main() 
{
    Connect4 game;

    game.emptyGrid();
    game.printGame();

    while (!game.checkVictory()) {
        game.printGame();
        game.printNumberOfTokensInColumn();

        if(game.getCurrentPlayer() == 1) {
            std::cout << "Player 1's turn :" << std::endl;
        }
        else if (game.getCurrentPlayer() == -1) {
            std::cout << "Player 2's turn" << std::endl;
        }

        int column = COLUMNS;
        do {
            std::cout << "Please enter the column's number in which you want to put the token (between 0 and 6) => " << std::endl;
            std::cin >> column;

            if(game.filledColumn(column)) {
                std::cout << "Column already filled" << std::endl;
            }
        }
        while (column < 0 || column >= COLUMNS || game.filledColumn(column));

        game.addToken(column);
    }

    std::cout << "Game over" << std::endl;
}