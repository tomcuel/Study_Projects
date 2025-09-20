#ifndef __BOARD_H__
#define __BOARD_H__


#include "Constants.h"
#include "Piece.h"
#include "Move.h"
#include "Move_Log.h"
#include "Player.h"


/////////////////////////////////////////////////////////////////////////////////////
// Board summary:
/**
 * No special structure is needed for the board, since it is a 2D array of pieces
 * 
 * A summary of the supported functions is given below:
 * 
 * Init_Board - to initialize the board
 * Reset_Board - to reset the board to the initial state
 * Clear_Board - to clear the board
 * Make_Move - to make a move on the board and update everything : the board, the state of rock and check, the captured pieces, and the players structure
 * Undo_Move - to undo a move on the board and update everything : the board, the state of rock and check, the captured pieces, and the players structure
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Function to initialize the board
/**
 * @return Piece*** : the board initialized
**/
/////////////////////////////////////////////////////////////////////////////////////
Piece*** Init_Board();


/////////////////////////////////////////////////////////////////////////////////////
// Function to reset the board to the initial state
/**
 * @param board : the board to reset
**/
/////////////////////////////////////////////////////////////////////////////////////
void Reset_Board(Piece*** board);


/////////////////////////////////////////////////////////////////////////////////////
// Function to clear the board
/**
 * @param board : the board to clear
**/
/////////////////////////////////////////////////////////////////////////////////////
void Clear_Board(Piece*** board);


/////////////////////////////////////////////////////////////////////////////////////
// Function to make a move on the board
// It modifies the board, the log and the captured pieces, and the players structure, to change the player that is playing
/**
 * @param board : the board to make the move
 * @param move : the move to make
 * @param log : the log of the moves
 * @param captured_piece_and_score : the captured pieces of the players with the score
 * @param state_of_rock_and_check : the state of the rock and the check
 * @param players : the players
**/
/////////////////////////////////////////////////////////////////////////////////////
void Make_Move(Piece*** board, Move* move, Move_Log_array* log, Captured_Piece_and_Score* captured_piece_and_score, State_Of_Rock_and_Check* state_of_rock_and_check, Players* players);


/////////////////////////////////////////////////////////////////////////////////////
// There will be the need to undo the move, if is_check after the move and tell to make the move again
// once we past this stage we can update the states of the board, the log, the captured pieces and the players
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Function to undo a move on the board
// It modifies the board, the log and the captured pieces, and the players structure, to change the player that is playing
/**
 * @param board : the board to make the move
 * @param move : the move to make
 * @param log : the log of the moves
 * @param captured_piece_and_score : the captured pieces of the players
 * @param state_of_rock_and_check : the state of the rock and the check
 * @param players : the players
**/
/////////////////////////////////////////////////////////////////////////////////////
void Undo_Move(Piece*** board, Move* move, Move_Log_array* log, Captured_Piece_and_Score* captured_piece_and_score, State_Of_Rock_and_Check* state_of_rock_and_check, Players* players);


#endif /* __BOARD_H__ */