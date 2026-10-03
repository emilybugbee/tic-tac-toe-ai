// Copyright (c) 2025 Nathan Greenfield. All rights reserved

#include "tttgame.h"
#include "tttgameai.h"

TicTacToeGame::TicTacToeGame()
{
	// Iterates down rows
	for (int i = 0; i < 3; i++)
	{
		// Iterates across columns
		for (int j = 0; j < 3; j++)
		{
			// Sets state to empty
			currentState.mBoard[i][j] = GameState::Empty;
		}
	}
}

GameState TicTacToeGame::getBoard() const
{
	return currentState;
}

bool TicTacToeGame::setSquareState(unsigned short row, unsigned short col, GameState::SquareState state)
{
	// If square is empty, change to inputted state and return true
	if (currentState.mBoard[row][col] == GameState::Empty)
	{
		currentState.mBoard[row][col] = state;
		return true;
	}
	// Return false if square is occupied
	else
	{
		return false;
	}
}

bool TicTacToeGame::setSquareState(unsigned short square, GameState::SquareState state)
{
	// Obtains row from square
	unsigned short row = (square - 1) / 3;
	// Obtains column from square
	unsigned short col = (square - 1) % 3;
	// Calls setSquareState with 3 inputs
	return setSquareState(row, col, state);
}

char TicTacToeGame::getWinner()
{
	// Sets default retval (no winners and there are empty spaces)
	char retval = ' ';
	// Obtains the board's current score
	float score = GetScore(currentState);
	// If score = -1, X won
	if (score == -1)
	{
		retval = 'X';
	}
	// If score = 1, O won
	else if (score == 1)
	{
		retval = 'O';
	}
	// Otherwise there are no winners
	else
	{
		// If the board is full the game is tied
		if (isBoardFull(currentState) == true)
		{
			retval = 'N';
		}
	}
	return retval;
}
