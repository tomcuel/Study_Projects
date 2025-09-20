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
 * Make_Rock_Move - to make a move on the board when a rock is done and update everything : the board, the state of rock and check, the captured pieces, and the players structure
 * Clear_En_Passant_Piece - to clear the pawn taken by the en passant
 * Change_Others_Structures - to update the others types of structures after the move is made
 * Change_Others_Structures_during_Rock - to update the others types of structures after the move is made when it is a rock
 * Undo_Last_Move - to undo the last move made and update the board, the log, the captured pieces, the stateofrockandcheck, the players structure, the pawn tracking structure
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
 * @param players : the players
**/
/////////////////////////////////////////////////////////////////////////////////////
void Make_Move(Piece*** board, Move* move, Players* players);


/////////////////////////////////////////////////////////////////////////////////////
// Function similar to Make_Move, but it is used to make a move when a rock is done
// It modifies the board, the log and the captured pieces, and the players structure, to change the player that is playing
/**
 * @param board : the board to make the move
 * @param move : the move to make
 * @param king_move_during_rock : the move of the king during the rock
 * @param rook_move_during_rock : the move of the rook during the rock
 * @param players : the players
**/
/////////////////////////////////////////////////////////////////////////////////////
void Make_Rock_Move(Piece*** board, Move* move, Move* king_move_during_rock, Move* rook_move_during_rock, Players* players);


/////////////////////////////////////////////////////////////////////////////////////
// Function to clear the pawn taken by the en passant
// suppose that en passant is possible and the move is done
/**
 * @param move : the move to make
 * @param board : the board to make the move
 * @param Pawn_Move_State : the state of the pawn move
*/
void Clear_En_Passant_Piece(Move* move, Piece*** board, Tiles_Pawn* Pawn_Move_State);


/////////////////////////////////////////////////////////////////////////////////////
// Function to update the others types of structures after the move is made
/**
 * @param log : the log of the moves
 * @param captured_piece_and_score : the captured pieces and the score
 * @param state_of_rock_and_check : the state of rock and check
 * @param players : the players
 * @param board : the board
**/
/////////////////////////////////////////////////////////////////////////////////////
void Change_Others_Structures(Move_Log_array* log, Captured_Piece_and_Score* captured_piece_and_score, State_Of_Rock_and_Check* state_of_rock_and_check, Players* players, Piece*** board);


/////////////////////////////////////////////////////////////////////////////////////
// Function to update the others types of structures after the move is made when it is a rock
/**
 * @param log : the log of the moves
 * @param captured_piece_and_score : the captured pieces and the score
 * @param state_of_rock_and_check : the state of rock and check
 * @param players : the players
 * @param board : the board
**/
/////////////////////////////////////////////////////////////////////////////////////
void Change_Others_Structures_during_Rock(Move_Log_array* log, Captured_Piece_and_Score* captured_piece_and_score, State_Of_Rock_and_Check* state_of_rock_and_check, Players* players, Piece*** board);


/////////////////////////////////////////////////////////////////////////////////////
// Function to undo the last move made and that update the board, the log, the captured pieces, the stateofrockandcheck, the players structure, the pawn tracking structure
/**
 * @param board : the board
 * @param log : the log of the moves
 * @param captured_piece_and_score : the captured pieces and the score
 * @param state_of_rock_and_check : the state of rock and check
 * @param players : the players
 * @param Pawn_Move_State : the state of the pawn move
**/
/////////////////////////////////////////////////////////////////////////////////////
void Undo_Last_Move(Piece*** board, Move_Log_array* log, Captured_Piece_and_Score* captured_piece_and_score, State_Of_Rock_and_Check* state_of_rock_and_check, Players* players, Tiles_Pawn* Pawn_Move_State);



#endif /* __BOARD_H__ */