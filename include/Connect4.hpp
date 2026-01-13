#include <iostream>
#include "Constants.hpp"

class Connect4 
{
	public:
		Connect4() {emptyGrid();};
    	void printGame();
		void addToken (int column);
    	void addToken (int row, int column, int token);
    	bool filledColumn(int column) {return tokensInColumns[column] == ROWS;};
		int getNumberOfTokensInColumn(int column) {return tokensInColumns[column];};
    	bool checkVictory();
    	bool checkVictoryFromPosition(int row, int column);
    	void emptyGrid();
    	int getCurrentPlayer() {return currentPlayer;}
    	void changeCurrentPlayer() {currentPlayer *= -1;};
    	void printNumberOfTokensInColumn();

    private:
	    int grid[ROWS][COLUMNS];
	    int tokensInColumns[COLUMNS] = {0}; // Indicates tokens already in columns
	    int currentPlayer = PLAYER_1;

};