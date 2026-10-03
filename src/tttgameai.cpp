// Copyright (c) 2025 Nathan Greenfield. All rights reserved

#include "tttgameai.h"
#include <iostream>

bool IsGameOver(const GameState& state)
{
	// If X or O won, game over
	if (GetScore(state) != 0)
	{
		return true;
	}
	// If the board is full, game over
	else if (isBoardFull(state) == true)
	{
		return true;
	}
	// Game is not over
	return false;
}

void GenStates(GTNode* root, bool xPlayer)
{
	// Stop if the game is over
	if (IsGameOver(root->mState) == true)
	{
		return;
	}
	// Iterates through all 9 squares
	for (unsigned short i = 1; i < 10; i++)
	{
		// Checks if square is empty
		if (isSquareEmpty(root->mState, i) == true)
		{
			// 1. Generate a new child node
			GTNode* newChild = new GTNode;
			// 2. Set child’s board to the root’s board
			newChild->mState = root->mState;
			// 3. Set the empty position to the X (or the player’s symbol)
			unsigned short row = (i - 1) / 3;
			unsigned short col = (i - 1) % 3;
			// If it's X's turn
			if (xPlayer == true)
			{
				// Set empty square to X
				newChild->mState.mBoard[row][col] = GameState::X;
			}
			// If it's O's turn
			else
			{
				// Set empty square to O
				newChild->mState.mBoard[row][col] = GameState::O;
			}
			// 4. Add the node as a child to root
			root->mChildren.push_back(newChild);
			// 5. Generate the child nodes for this new node (call the function recursively)
			GenStates(newChild, !xPlayer);
		}
	}
}

float GetScore(const GameState& state)
{
	// Iterates down rows/across columns
	for (int i = 0; i < 3; i++)
	{
		// Checks if all the states in a row are the same
		if (state.mBoard[i][0] == state.mBoard[i][1] && state.mBoard[i][0] == state.mBoard[i][2])
		{
			// Returns -1 if the row is Xs
			if (state.mBoard[i][0] == GameState::X)
			{
				return -1;
			}
			// Returns 1 if the row is Os
			else if (state.mBoard[i][0] == GameState::O)
			{
				return 1;
			}
		}
		else if (state.mBoard[0][i] == state.mBoard[1][i] && state.mBoard[0][i] == state.mBoard[2][i])
		{
			// Returns -1 if the column is Xs
			if (state.mBoard[0][i] == GameState::X)
			{
				return -1;
			}
			// Returns 1 if the column is Os
			else if (state.mBoard[0][i] == GameState::O)
			{
				return 1;
			}
		}
	}
	if (state.mBoard[0][0] == state.mBoard[1][1] && state.mBoard[0][0] == state.mBoard[2][2])
	{
		// Returns -1 if the diagonal is Xs
		if (state.mBoard[0][0] == GameState::X)
		{
			return -1;
		}
		// Returns 1 if the diagonal is Os
		else if (state.mBoard[0][0] == GameState::O)
		{
			return 1;
		}
	}
	else if (state.mBoard[0][2] == state.mBoard[1][1] && state.mBoard[0][2] == state.mBoard[2][0])
	{
		// Returns -1 if the diagonal is Xs
		if (state.mBoard[0][2] == GameState::X)
		{
			return -1;
		}
		// Returns 1 if the diagonal is Os
		else if (state.mBoard[0][2] == GameState::O)
		{
			return 1;
		}
	}
	// Returns 0 if no one won
	return 0;
}

float MinPlayer(const GTNode* node)
{
	// 1. If the node is a leaf node, return its score
	if (node->mChildren.empty() == true)
	{
		return GetScore(node->mState);
	}
	// 2. Otherwise return the smallest maximum score of all the child nodes (that means
	// calling the MaxPlayer function on all the children)
	else
	{
		// Initializes minScore to high value
		float minScore = 99;
		// Iterates through all child nodes
		for (int i = 0; i < node->mChildren.size(); i++)
		{
			// Finds max score obtainable from the current child
			float childScore = MaxPlayer(node->mChildren[i]);
			// If the child's max score is less than current minScore it becomes the minScore
			if (minScore > childScore)
			{
				minScore = childScore;
			}
		}
		return minScore;
	}
}

float MaxPlayer(const GTNode* node)
{
	// 1. If the node is a leaf node, return its score
	if (node->mChildren.empty() == true)
	{
		return GetScore(node->mState);
	}
	// 2. Otherwise return the largest minimum score of all the child nodes (that means
	// calling the MinPlayer function on all the children)
	else
	{
		// Initializes maxScore to low value
		float maxScore = -99;
		// Iterates through all child nodes
		for (int i = 0; i < node->mChildren.size(); i++)
		{
			// Finds min score obtainable from the current child
			float childScore = MinPlayer(node->mChildren[i]);
			// If the child's min score is greater than current maxScore it becomes the maxScore
			if (maxScore < childScore)
			{
				maxScore = childScore;
			}
		}
		return maxScore;
	}
}

const GTNode* MinimaxDecide(const GTNode* root)
{
	// Starting with a given (or “root”) node – this will be the “current state” of the game
	int largestScoreIndex = 0;
	// Initializes largestMinScore to low value
	float largestMinScore = -99;
	// Go through each child node of the root
	for (int i = 0; i < root->mChildren.size(); i++)
	{
		// Obtains minScore from the current child
		float childMinScore = MinPlayer(root->mChildren[i]);
		// Find the node with the largest MinPlayer score
		if (childMinScore > largestMinScore)
		{
			largestScoreIndex = i;
			largestMinScore = childMinScore;
		}
	}
	// Make the move to yield the state found above
	return root->mChildren[largestScoreIndex];
}

unsigned pickMove(const GameState& board)
{
	// Make a new root
	GTNode* root = new GTNode;
	// Set the root's board
	root->mState = board;
	// Generate the tree for the root
	GenStates(root, false);
	// Call MinimaxDecide() which gives the next move to make
	const GTNode* idealMove = MinimaxDecide(root);
	// Figure out which spot changed
	return changedSquare(board, idealMove);
}

bool isBoardFull(const GameState& board)
{
	// Iterates down rows
	for (int i = 0; i < 3; i++)
	{
		// Iterates across columns
		for (int j = 0; j < 3; j++)
		{
			// Returns false if any square is empty
			if (board.mBoard[i][j] == GameState::Empty)
			{
				return false;
			}
		}
	}
	// Returns true if no squares are empty
	return true;
}

bool isSquareEmpty(const GameState& board, unsigned short square)
{
	// Obtains row from square
	unsigned short row = (square - 1) / 3;
	// Obtains column from square
	unsigned short col = (square - 1) % 3;
	// Returns true if square is empty
	if (board.mBoard[row][col] == GameState::Empty)
	{
		return true;
	}
	// Returns false if square is occupied
	return false;
}

unsigned changedSquare(const GameState& board, const GTNode* idealMove)
{
	// Iterates through every square
	for (unsigned i = 1; i < 10; i++)
	{
		// Obtains row from square number
		unsigned short row = (i - 1) / 3;
		// Obtains column from square number
		unsigned short col = (i - 1) % 3;
		// Compares the squares on each board for a change
		if (board.mBoard[row][col] != idealMove->mState.mBoard[row][col])
		{
			return i;
		}
	}
}