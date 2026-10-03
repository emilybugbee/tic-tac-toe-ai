// Copyright (c) 2025 Nathan Greenfield. All rights reserved
#pragma once

#include <vector>

#include "tttgamedata.h"

struct GTNode
{
	// Current state of game
	GameState mState;

	// Children nodes with future states
	std::vector<GTNode*> mChildren;
};

// Function: GenStates
// Purpose: Generates the game tree starting at the inputted root
// Input: A GTNode pointer with the 1st state completed
//		A boolean to indicate who's turn it is (true means it's X's turn)
// Returns: Nothing
// Note: Be sure to generate the child classes in order,
//		So given the board from lecture, the child at index 0 should be the board
//		where X moved to 2. The second item in the vector should be where X moved
//		to 8, etc.
void GenStates(GTNode* root, bool xPlayer);

// Function: GetScore
// Purpose: Examines the inputted game board to determine a winner
// Input: A game state representing a game board
// Returns: Everything is relative to O, so...
//		1.0 to indicate O wins on this board
//		0.0 to indicate tie game
//		-1.0 to indicate X wins on this board
float GetScore(const GameState& state);

// Function: MinPlayer
// Purpose: Determines the minimum score this branch (or leaf) can yield
// Input: A GameTree node
// Returns: The game score meaning...
//		1.0 to indicate O wins on this board
//		0.0 to indicate tie game
//		-1.0 to indicate X wins on this board
float MinPlayer(const GTNode* node);

// Function: MaxPlayer
// Purpose: Determines the maximum score this branch (or leaf) can yield
// Input: A GameTree node
// Returns: The game score meaning...
//		1.0 to indicate O wins on this board
//		0.0 to indicate tie game
//		-1.0 to indicate X wins on this board
float MaxPlayer(const GTNode* node);

// Function: MinimaxDecide
// Purpose: Determines which subtree leads to O winning
// Input: A GameTree node
// Returns: The GTNode* with the winning game state
const GTNode* MinimaxDecide(const GTNode* root);

// Function: pickMove
// Purpose: Decides which square the AI should select
// Input: A game state with the current board's state
// Returns: The square number (1 through 9) the AI selects
unsigned pickMove(const GameState& board);

// Function: isBoardFull
// Purpose: Determines whether all squares in the board are taken
// Input: A game state with the current board's state
// Returns: A boolean, true if the board is full
bool isBoardFull(const GameState& board);

// Function: isSquareEmpty
// Purpose: Determines whether the square is set to empty
// Input: A game state with the current board's state and the square to check
// Returns: A boolean, true if the square is empty
bool isSquareEmpty(const GameState& board, unsigned short square);

// Function: changedSquare
// Purpose: Locates the changed square between two boards
// Input: A game state with the current board's state and a GTNode* to compare to
// Returns: An unsigned corresponding to the changed square
unsigned changedSquare(const GameState& board, const GTNode* idealMove);