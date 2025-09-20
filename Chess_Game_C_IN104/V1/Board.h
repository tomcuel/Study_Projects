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
 * Clear_Board - to clear the board
 * Make_Move - to make a move on the board
 * Undo_Move - to undo a move on the board
 * Update_others_States - to update the states of the board, the log, the captured pieces and the players
 * Undo_Update_others_States - to undo the update of the states of the board, the log, the captured pieces and the players, when we go back
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
**/
/////////////////////////////////////////////////////////////////////////////////////
void Make_Move(Piece*** board, Move* move);


/////////////////////////////////////////////////////////////////////////////////////
// There will be the need to undo the move, if is_check after the move and tell to make the move again
// once we past this stage we can update the states of the board, the log, the captured pieces and the players
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Function to undo a move on the board
// It modifies the board, the log and the captured pieces, and the players structure, to change the player that is playing
/**
 * @param board : the board to undo the move
 * @param move : the move to make
**/
/////////////////////////////////////////////////////////////////////////////////////
void Undo_Move(Piece*** board, Move* move);


/////////////////////////////////////////////////////////////////////////////////////
// Function to update the states of the board, the log, the captured pieces and the players
/**
 * @param log : the log to update
 * @param captured_pieces : the captured pieces to update
 * @param player : the players (to get the player that is playing) to update
**/
/////////////////////////////////////////////////////////////////////////////////////
void Update_others_States(Move_Log_array* log, Captured_Piece_and_Score* captured_pieces, Players* player);


/////////////////////////////////////////////////////////////////////////////////////
// Function to undo the update of the states of the board, the log, the captured pieces and the players, when we go back 
/**
 * @param log : the log to update
 * @param captured_pieces : the captured pieces to update
 * @param player : the players (to get the player that is playing) to update
**/
/////////////////////////////////////////////////////////////////////////////////////
void Undo_Update_others_States(Move_Log_array* log, Captured_Piece_and_Score* captured_pieces, Players* player);


#endif /* __BOARD_H__ */