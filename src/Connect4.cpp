#include "Connect4.hpp"

/*
* Print the current grid in terminal.
*/
void Connect4::printGame() {

        for(int i = 0; i < ROWS; i++) {
            std::cout << "| ";
            for(int j = 0; j < COLUMNS; j++) {
                if (grid[i][j] >= 0) {
                    std::cout << " ";
                }
                std::cout << grid[i][j] << " | ";
            }
            std::cout << std::endl;
        }
        for(int j = 0; j < COLUMNS; j++) {
            std::cout << "  (" << j << ")";
        }
        std::cout << std::endl;
    }

/*
* Adds token to the current game's grid.
* @param row, the number of the row the token will be on after being added, is between 0 and (ROWS - 1)
* @param column, the number of the selected column in the grid, is between 0 and (COLUMNS - 1)
* @param token, 1 if the current player is PLAYER_1, -1 if PLAYER_2.
*/
void Connect4::addToken (int row, int column, int token) {
        if (this->tokensInColumns[column] < ROWS) {
            this->grid[row][column] = token;
            this->tokensInColumns[column] += 1;
        }
        else {
            std::cout << " Column is  " << std::endl;
        }
            
    }


void Connect4::addToken (int column) {
/*        std::cout << "Coordonnees : ";
       	 std::cout << "Ligne = " << LIGNES - jetonsParColonnes[colonne] << std::endl;
        std::cout << "Colonne = " << colonne << std::endl;*/
    addToken (ROWS - tokensInColumns[column] - 1, column, currentPlayer);
 }

     // Conditions de victoire
    /*
    1/ Vertical
        | 1 | 0 | 0 | 0 | 0 | 0 | 0 |
        | 1 | 0 | 0 | 0 | 0 | 0 | 0 |
        | 1 | 0 | 0 | 0 | 0 | 0 | 0 |
        | 1 | 0 | 0 | 0 | 0 | 0 | 0 |
    
        qd victoire => grille[0][0] + grille[1][0] + grille[2][0] + grille[3][0] = 4
    2/ Horizontal
        | 1 | 1 | 1 | 1 | 0 | 0 | 0 |
        | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
        | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
        | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
        qd victoire => grille[0][0] + grille[0][1] + grille[0][2] + grille[0][3] = 4
    3/ Diagonale
        | 1 | 0 | 0 | 1 | 0 | 0 | 0 |
        | 0 | 1 | 1 | 0 | 0 | 0 | 0 |
        | 0 | 1 | 1 | 0 | 0 | 0 | 0 |
        | 1 | 0 | 0 | 1 | 0 | 0 | 0 |


        v1 : on verifie toutes les cases
    * Goes through the entire grid to find if there's a winning combination of the same four tokens in a row.
    */
bool Connect4::checkVictory() {
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLUMNS; j++) {
            // Vertical
            if ((i+3) < ROWS && abs(grid[i][j] + grid[i+1][j] + grid[i+2][j] + grid[i+3][j]) == 4) {
                return true;
            }
            // Horizontal
            if ((j+3) < COLUMNS && abs(grid[i][j] + grid[i][j+1] + grid[i][j+2] + grid[i][j+3]) == 4) {
                return true;
            }

            // Diagonal
            if ((i+3) < ROWS && (j+3) < COLUMNS && abs(grid[i][j] + grid[i+1][j+1] + grid[i+2][j+2] + grid[i+3][i+3]) == 4) {
                return true;
            }

            if ((i+3) > ROWS && (j-3) >= 0 && abs(grid[i][j] + grid[i+1][j-1] + grid[i+2][j-2] + grid[i+3][i-3]) == 4) {
                return true;
            }
        }
    }
    return false;
}

/*
* From the last played token position, checks if there's a winning combination of the same four tokens in a row.
*/
bool Connect4::checkVictoryFromPosition(int row, int column) {
    
    // Vertical
    if((row + 3) < ROWS) {
        return abs(grid[row][column] + grid[row+1][column] + grid[row+2][column] + grid[row+3][column]) == 4;
    }   

    // Horizontal
    if((column - 3) >= 0 && abs(grid[row][column - 3] + grid[row][column - 2] + grid[row][column - 1] + grid[row][column]) == 4) {
        return true;
    }

    if((column - 2) >= 0 && (column + 1) < COLUMNS && abs(grid[row][column - 2] + grid[row][column - 1] + grid[row][column] + grid[row][column + 1]) == 4) {
        return true;
    }

    if((column - 1) >= 0 && (column + 2) < COLUMNS && abs(grid[row][column - 1] + grid[row][column] + grid[row][column + 1] + grid[row][column + 2]) == 4) {
        return true;
    }

    if((column + 3) < COLUMNS && abs(grid[row][column] + grid[row][column + 1] + grid[row][column + 2] + grid[row][column + 3]) == 4) {
        return true;
    }

    // Diagonal

    // From top to bottom diagonal
    if((row - 3) >= 0 && (column - 3) >= 0 
    && abs(grid[row - 3][column - 3] + grid[row - 2][column - 2] + grid[row - 1][column - 1] + grid[row][column]) == 4) {
        return true;
    }

    if((row - 2) >= 0 && (column - 2) >= 0 
    && (row + 1) < ROWS && (column + 1) < COLUMNS 
    && abs(grid[row - 2][column - 2] + grid[row - 1][column - 1] + grid[row][column] + grid[row + 1][column + 1]) == 4) {
        return true;
    }

    if((row - 1) >= 0 && (column - 1) >= 0 
    && (row + 2) < ROWS && (column + 2) < COLUMNS 
    && abs(grid[row - 1][column - 1] + grid[row][column] + grid[row + 1][column + 1] + grid[row + 2][column + 2]) == 4) {
        return true;
    }

    if((row + 3) < ROWS && (column + 3) < COLUMNS
    && abs(grid[row][column] + grid[row + 1][column + 1] + grid[row + 2][column + 2] + grid[row + 3][column + 3]) == 4) {
        return true;
    }

    // From bottom to top diagonal
    if((row + 3) < ROWS && (column - 3) >= 0 
    && abs(grid[row + 3][column - 3] + grid[row + 2][column - 2] + grid[row + 1][column - 1] + grid[row][column]) == 4) {
        return true;
    }

    if((row - 1) >= 0 && (column - 2) >= 0 
    && (row + 2) < ROWS && (column + 1) < COLUMNS 
    && abs(grid[row + 2][column - 2] + grid[row + 1][column - 1] + grid[row][column] + grid[row - 1][column + 1]) == 4) {
        return true;
    }

    if((row - 2) >= 0 && (column - 1) >= 0 
    && (row + 1) < ROWS && (column + 2) < COLUMNS 
    && abs(grid[row + 1][column - 1] + grid[row][column] + grid[row - 1][column + 1] + grid[row - 2][column + 2]) == 4) {
        return true;
    }

    if((row - 3) >= 0 && (column + 3) < COLUMNS
    && abs(grid[row][column] + grid[row - 1][column + 1] + grid[row - 2][column + 2] + grid[row - 3][column + 3]) == 4) {
        return true;
    }

    return false;
}

void Connect4::emptyGrid() {
        for(int i = 0; i < ROWS; i++) {
            this->tokensInColumns[i] = 0;
            for(int j = 0; j < COLUMNS; j++) {
                this->grid[i][j] = 0;
            }
        }
}

void Connect4::printNumberOfTokensInColumn() {
    for(int i = 0; i < COLUMNS; i++) {
        std::cout << "(" << tokensInColumns[i] << ") ";
    }
    std::cout << std::endl;
}