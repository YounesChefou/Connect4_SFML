#include <SFML/Graphics.hpp>
#include <vector>
#include "Connect4.hpp"

/*
* SFML version of the game.
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

class Connect4_SFML
{
    public:
        Connect4_SFML();

        // TODO : add window as class parameter 
        bool addTokenToColumn(sf::RenderWindow* window);
        void drawGridOnWindow(sf::RenderWindow* window);
        void drawCursorOnWindow(sf::RenderWindow* window);
        void drawTokensOnGrid(sf::RenderWindow* window);
        void drawInfoOnScreen(sf::RenderWindow* window);

        void moveCursorToNextColumn(bool right);
        bool checkVictory() {return game.checkVictory();};
        bool checkVictoryFromPosition(int row, int column) {return game.checkVictoryFromPosition(row, column);};
        int getCurrentPlayer() {return game.getCurrentPlayer();};
        void changeCurrentPlayer() {game.changeCurrentPlayer();};
        GameState getGameState() { return state;};
        void setGameState(GameState newState) {state = newState;};
        void clearGrid();
    private:
        GameState state;
        Connect4 game;
        sf::RectangleShape columnShapes[COLUMNS];
        Selection playerSelection;
        std::vector<sf::CircleShape> displayedTokens;
};