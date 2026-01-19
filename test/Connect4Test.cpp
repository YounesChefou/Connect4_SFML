#include "gtest/gtest.h"
#include "Connect4.hpp"
#include "Constants.hpp"

void settingUpDiagonalTopToBottom(Connect4* game) {
  game->addToken(0);
  game->addToken(0);
  game->addToken(0);

  game->addToken(1);
  game->addToken(1);
  
  game->addToken(2);

  // Adding winning diagonal
  game->changeCurrentPlayer();
  game->addToken(0);
  game->addToken(1);
  game->addToken(2);
  game->addToken(3);
}

void settingUpDiagonalBottomToTop(Connect4* game) {
  game->addToken(1);
  
  game->addToken(2);
  game->addToken(2);

  game->addToken(3);
  game->addToken(3);
  game->addToken(3);

  // Adding winning diagonal
  game->changeCurrentPlayer();
  game->addToken(0);
  game->addToken(1);
  game->addToken(2);
  game->addToken(3);
}

/*
*  Adding one token per column, expecting 1 for each.
*/
TEST(Connect4Test, AddOneToken) {
  Connect4 game;
  game.emptyGrid();
  for(int i = 0; i < COLUMNS; i++) {
    game.addToken(i);
    EXPECT_EQ(game.getNumberOfTokensInColumn(i), 1)  << "Column " << i << " should have 1 token, not " << game.getNumberOfTokensInColumn(i);
  }
}

/*
*  Adding 3 tokens per column, expecting 3 for each.
*/
TEST(Connect4Test, AddThreeTokens) {
  Connect4 game;
  game.emptyGrid();

  // 
  for(int i = 0; i < COLUMNS; i++) {
    game.addToken(i);
    game.addToken(i);
    game.addToken(i);
    EXPECT_EQ(game.getNumberOfTokensInColumn(i), 3) << "Column " << i << " should have 3 tokens, not " << game.getNumberOfTokensInColumn(i);
  }
}

/*
*  Adding 8 tokens per column, expecting 6 for each.
*/
TEST(Connect4Test, AddEightTokens) {
  Connect4 game;
  game.emptyGrid();
  
  for(int i = 0; i < COLUMNS; i++) {
    game.addToken(i);
    game.addToken(i);
    game.addToken(i);
    game.addToken(i);
    game.addToken(i);
    game.addToken(i);
    game.addToken(i);
    game.addToken(i);
    EXPECT_EQ(game.getNumberOfTokensInColumn(i), 6) << "Column " << i << " should have 6 tokens, not " << game.getNumberOfTokensInColumn(i);
    EXPECT_TRUE(game.filledColumn(i)) << "Column " << i << " should be filled.";
  }
}

/*
* Checks detection of a winning row of tokens, horizontal.
*/
TEST(Connect4Test, checkVictoryHorizontal) {
  Connect4 game;
  game.emptyGrid();

  // Setting up row of the same tokens
  game.addToken(0);
  game.addToken(1);
  game.addToken(2);
  game.addToken(3);

  // Grid => 
  // |  0 |  0 |  0 |  0 |  0 |  0 |  0 | 
  // |  0 |  0 |  0 |  0 |  0 |  0 |  0 | 
  // |  0 |  0 |  0 |  0 |  0 |  0 |  0 | 
  // |  0 |  0 |  0 |  0 |  0 |  0 |  0 | 
  // |  0 |  0 |  0 |  0 |  0 |  0 |  0 | 
  // |  1 |  1 |  1 |  1 |  0 |  0 |  0 | 
  //   (0)  (1)  (2)  (3)  (4)  (5)  (6)

  EXPECT_TRUE(game.checkVictory()) << "checkVictory should return true";
}

/*
* Checks detection of a winning column of tokens.
*/
TEST(Connect4Test, checkVictoryVertical) {
  Connect4 game;
  game.emptyGrid();

  // Setting up column of the same tokens
  game.addToken(0);
  game.addToken(0);
  game.addToken(0);
  game.addToken(0);

  // Grid => 
  // |  0 |  0 |  0 |  0 |  0 |  0 |  0 | 
  // |  0 |  0 |  0 |  0 |  0 |  0 |  0 | 
  // |  1 |  0 |  0 |  0 |  0 |  0 |  0 | 
  // |  1 |  0 |  0 |  0 |  0 |  0 |  0 | 
  // |  1 |  0 |  0 |  0 |  0 |  0 |  0 | 
  // |  1 |  0 |  0 |  0 |  0 |  0 |  0 | 
  //   (0)  (1)  (2)  (3)  (4)  (5)  (6)

  EXPECT_TRUE(game.checkVictory()) << "checkVictory should return true";
}

/*
* Checks detection of a winning diagonal row of tokens, with the first token higher than the last one.
*/
TEST(Connect4Test, checkVictoryDiagonalTopToBottom) {
  Connect4 game;
  game.emptyGrid();

  // Setting up tokens on which the diagonal will appear
  settingUpDiagonalTopToBottom(&game);

  // Grid => 
  // |  0 |  0 |  0 |  0 |  0 |  0 |  0 | 
  // |  0 |  0 |  0 |  0 |  0 |  0 |  0 | 
  // | -1 |  0 |  0 |  0 |  0 |  0 |  0 | 
  // |  1 | -1 |  0 |  0 |  0 |  0 |  0 | 
  // |  1 |  1 | -1 |  0 |  0 |  0 |  0 | 
  // |  1 |  1 |  1 | -1 |  0 |  0 |  0 | 
  //   (0)  (1)  (2)  (3)  (4)  (5)  (6)
  
  EXPECT_TRUE(game.checkVictory()) << "checkVictory should return true";  
}

/*
* Checks detection of a winning diagonal row of tokens, with the first token lower than the last one.
*/
TEST(Connect4Test, checkVictoryDiagonalBottomToTop) {
  Connect4 game;
  game.emptyGrid();

  // Setting up tokens on which the diagonal will appear
  settingUpDiagonalBottomToTop(&game);

  // Grid => 
  // |  0 |  0 |  0 |  0 |  0 |  0 |  0 | 
  // |  0 |  0 |  0 |  0 |  0 |  0 |  0 | 
  // |  0 |  0 |  0 | -1 |  0 |  0 |  0 | 
  // |  0 |  0 | -1 |  1 |  0 |  0 |  0 | 
  // |  0 | -1 |  1 |  1 |  0 |  0 |  0 | 
  // | -1 |  1 |  1 |  1 |  0 |  0 |  0 | 
  //   (0)  (1)  (2)  (3)  (4)  (5)  (6)
  EXPECT_TRUE(game.checkVictory()) << "checkVictory should return true";  
}

/*
* Checks detection of a winning row of tokens from a given position, horizontal.
*/
TEST(Connect4Test, checkVictoryFromPositionHorizontal) {
  Connect4 game;
  game.emptyGrid();

  //Setting up grid
  game.addToken(0);
  game.addToken(0);
  game.addToken(0);
  game.addToken(1);
  game.addToken(2);

  game.changeCurrentPlayer();
  game.addToken(1);
  game.addToken(2);
  game.addToken(3);
  game.addToken(3);
  game.addToken(4);
  game.addToken(4);

  // Grid => 
  // |  0 |  0 |  0 |  0  |  0 |  0 |  0 | 
  // |  0 |  0 |  0 |  0  |  0 |  0 |  0 | 
  // |  0 |  0 |  0 |  0  |  0 |  0 |  0 | 
  // |  1 |  0 |  0 |  0  |  0 |  0 |  0 | 
  // |  1 | -1 | -1 | -1 | -1 |  0 |  0 | 
  // |  1 |  1 |  1 | -1  | -1 |  0 |  0 | 
  //   (0)  (1)  (2)  (3)  (4)  (5)  (6)

  EXPECT_TRUE(game.checkVictoryFromPositionHorizontal(4, 1)) << "checkVictoryFromPosition should return true on position(4, 1)"; 
  EXPECT_TRUE(game.checkVictoryFromPositionHorizontal(4, 2)) << "checkVictoryFromPosition should return true on position(4, 2)"; 
  EXPECT_TRUE(game.checkVictoryFromPositionHorizontal(4, 3)) << "checkVictoryFromPosition should return true on position(4, 3)"; 
  EXPECT_TRUE(game.checkVictoryFromPositionHorizontal(4, 4)) << "checkVictoryFromPosition should return true on position(4, 4)"; 
}


/*
* Checks detection of a winning row of tokens from a given position, vertical.
*/
TEST(Connect4Test, checkVictoryFromPositionVertical) {
  Connect4 game;
  game.emptyGrid();

  // Adding 4 tokens in column (2)
  for(int i = 0; i < 4; i++) game.addToken(2);

  // Grid => 
  // -1x being the last token added in grid and the position
  // from which the winning row must be found
  // |  0 |  0 |  0 |  0  |  0 |  0 |  0 | 
  // |  0 |  0 |  0 |  0  |  0 |  0 |  0 | 
  // |  0 |  0 | 1x |  0  |  0 |  0 |  0 | 
  // |  0 |  0 |  1 |  0  |  0 |  0 |  0 | 
  // |  0 |  0 |  1 |  0  |  0 |  0 |  0 | 
  // |  0 |  0 |  1 |  0  |  0 |  0 |  0 | 
  //   (0)  (1)  (2)  (3)  (4)  (5)  (6)

  EXPECT_TRUE(game.checkVictoryFromPositionVertical(2, 2)) << "checkVictoryFromPosition should return true on position(2, 2)";
}

/*
* Checks detection of a winning row of tokens from a given position, diagonal, top to bottom.
*/
TEST(Connect4Test, checkVictoryFromPositionDiagonalTopToBottom) {
  Connect4 game;
  game.emptyGrid();

  // Setting Diagonal
  settingUpDiagonalTopToBottom(&game);

  // Grid => 
  // |  0 |  0 |  0 |  0 |  0 |  0 |  0 | 
  // |  0 |  0 |  0 |  0 |  0 |  0 |  0 | 
  // | -1 |  0 |  0 |  0 |  0 |  0 |  0 | 
  // |  1 | -1 |  0 |  0 |  0 |  0 |  0 | 
  // |  1 |  1 | -1 |  0 |  0 |  0 |  0 | 
  // |  1 |  1 |  1 | -1 |  0 |  0 |  0 | 
  //   (0)  (1)  (2)  (3)  (4)  (5)  (6)

  EXPECT_TRUE(game.checkVictoryFromPositionDiagonalTopToBottom(2, 0)) << "checkVictoryFromPosition should return true on position(2, 0)";
  EXPECT_TRUE(game.checkVictoryFromPositionDiagonalTopToBottom(3, 1)) << "checkVictoryFromPosition should return true on position(3, 1)";
  EXPECT_TRUE(game.checkVictoryFromPositionDiagonalTopToBottom(4, 2)) << "checkVictoryFromPosition should return true on position(4, 2)";
  EXPECT_TRUE(game.checkVictoryFromPositionDiagonalTopToBottom(5, 3)) << "checkVictoryFromPosition should return true on position(5, 3)"; 
}

/*
* Checks detection of a winning row of tokens from a given position, diagonal, bottom to top.
*/
TEST(Connect4Test, checkVictoryFromPositionDiagonalBottomToTop) {
  Connect4 game;
  game.emptyGrid();

  // Setting Diagonal
  settingUpDiagonalBottomToTop(&game);

  // Grid => 
  // |  0 |  0 |  0 |  0 |  0 |  0 |  0 | 
  // |  0 |  0 |  0 |  0 |  0 |  0 |  0 | 
  // |  0 |  0 |  0 | -1 |  0 |  0 |  0 | 
  // |  0 |  0 | -1 |  1 |  0 |  0 |  0 | 
  // |  0 | -1 |  1 |  1 |  0 |  0 |  0 | 
  // | -1 |  1 |  1 |  1 |  0 |  0 |  0 | 
  //   (0)  (1)  (2)  (3)  (4)  (5)  (6)

  game.printGame();

  EXPECT_TRUE(game.checkVictoryFromPositionDiagonalBottomToTop(5, 0)) << "checkVictoryFromPosition should return true on position(5, 0)";
  EXPECT_TRUE(game.checkVictoryFromPositionDiagonalBottomToTop(4, 1)) << "checkVictoryFromPosition should return true on position(4, 1)";
  EXPECT_TRUE(game.checkVictoryFromPositionDiagonalBottomToTop(3, 2)) << "checkVictoryFromPosition should return true on position(3, 2)";  
  EXPECT_TRUE(game.checkVictoryFromPositionDiagonalBottomToTop(2, 3)) << "checkVictoryFromPosition should return true on position(2, 3)";
}