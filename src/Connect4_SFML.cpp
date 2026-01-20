#include "Connect4_SFML.hpp"

Connect4_SFML::Connect4_SFML() {

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
    cursorTexture.loadFromFile("assets/malachite.png");
    playerSelection.cursor.setTexture(&cursorTexture);

    sf::Vector2f firstColumnPosition = columnShapes[0].getPosition();
    playerSelection.cursor.setPosition(firstColumnPosition.x, firstColumnPosition.y + BOARD_HEIGHT + 10.f); // Set position under first column
    playerSelection.columnSelected = 0; // Select first column

}

bool Connect4_SFML::addTokenToColumn(sf::RenderWindow* window)
{
    int columnNumber = playerSelection.columnSelected;

    if(game.filledColumn(columnNumber)){
        // TODO: Add message on window
        return false; // Column already full
    }

    
    // Adding token in the 2D-array representing the grid
    game.addToken(columnNumber);

    // Display token in window
    sf::Vector2f columnPosition = columnShapes[columnNumber].getPosition();
    int numberOfTokensInColumn = game.getNumberOfTokensInColumn(columnNumber);
    sf::CircleShape token(BOARD_COLUMN_WIDTH/2); // Un Token de rayon BOARD_COLUMN_WIDTH/2)

    if(game.getCurrentPlayer() == PLAYER_1) {
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

    return true;
}

void Connect4_SFML::drawGridOnWindow(sf::RenderWindow* window) {
    for(int i = 0; i < COLUMNS; i++) {
        window->draw(columnShapes[i]);
    }
}

void Connect4_SFML::drawCursorOnWindow(sf::RenderWindow* window) {
    window->draw(playerSelection.cursor);
}

void Connect4_SFML::drawTokensOnGrid(sf::RenderWindow* window) {
    for(sf::CircleShape token : displayedTokens) {
        window->draw(token);
    }
}

void Connect4_SFML::moveCursorToNextColumn(bool right) {
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

void Connect4_SFML::drawInfoOnScreen(sf::RenderWindow* window) {
    sf::Text infoText;

    // Set up infoText
    infoText.setString("Column is filled !");
    infoText.setCharacterSize(35);
    infoText.setFillColor(sf::Color::White);

    sf::Font myFont;
    myFont.loadFromFile("assets/UbuntuMono-B.ttf");
    infoText.setFont(myFont);

    sf::FloatRect textRect = infoText.getLocalBounds();

    // Put text origin at the center of the string
    infoText.setOrigin(textRect.left + textRect.width / 2.0f,
    textRect.top + textRect.height / 2.0f);

    // Put text on top right corner of screen
    infoText.setPosition(WIDTH * 0.85, HEIGHT * 0.05);

    window->draw(infoText);
}

void Connect4_SFML::clearGrid() {

    // Empty the grid
    game.emptyGrid();
    
    // Clear the vectors of all tokens currently displayed on screen
    displayedTokens.clear();

}