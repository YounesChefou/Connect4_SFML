#include "gtest/gtest.h"
#include "Connect4.hpp"
#include "Constants.hpp"


/*
 * Adding one token per column, expecting 1 for each.
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
 * Adding 3 tokens per column, expecting 3 for each.
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
 * Adding 8 tokens per column, expecting 6 for each.
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

TEST(Connect4Test, checkVictoryHorizontal) {
  Connect4 game;
  game.emptyGrid();

  // Setting up row of the same tokens
  game.addToken(0);
  game.addToken(1);
  game.addToken(2);
  game.addToken(3);
  EXPECT_TRUE(game.checkVictory()) << "checkVictory should return true";
}

TEST(Connect4Test, checkVictoryVertical) {
  Connect4 game;
  game.emptyGrid();

  // Setting up column of the same tokens
  game.addToken(0);
  game.addToken(0);
  game.addToken(0);
  game.addToken(0);
  EXPECT_TRUE(game.checkVictory()) << "checkVictory should return true";
}


TEST(Connect4Test, checkVictoryDiagonalTopToBottom) {
  Connect4 game;
  game.emptyGrid();

  // Setting up tokens on which the diagonal will appear
  game.addToken(0);
  game.addToken(0);
  game.addToken(0);

  game.addToken(1);
  game.addToken(1);
  
  game.addToken(2);
  
  // Adding winning diagonal
  game.changeCurrentPlayer();
  game.addToken(0);
  game.addToken(1);
  game.addToken(2);
  game.addToken(3);

  EXPECT_TRUE(game.checkVictory()) << "checkVictory should return true";  
}

TEST(Connect4Test, checkVictoryDiagonalBottomToTop) {
  Connect4 game;
  game.emptyGrid();

  // Setting up tokens on which the diagonal will appear
  game.addToken(1);
  
  game.addToken(2);
  game.addToken(2);

  game.addToken(3);
  game.addToken(3);
  game.addToken(3);

  // Adding winning diagonal
  game.changeCurrentPlayer();
  game.addToken(0);
  game.addToken(1);
  game.addToken(2);
  game.addToken(3);

  EXPECT_TRUE(game.checkVictory()) << "checkVictory should return true";  
}
