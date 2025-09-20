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
 * Copy_Board - to create a copy of the board
 * Clear_Board - to clear the board
 * Make_Move - to make a move on the board and update everything : the board, the state of rock and check, the captured pieces, and the players structure
 * Make_Rock_Move - to make a move on the board when a rock is done and update everything : the board, the state of rock and check, the captured pieces, and the players structure
 * Clear_En_Passant_Piece - to clear the pawn taken by the en passant
 * Change_Others_Structures - to update the others types of structures after the move is made
 * Change_Others_Structures_during_Rock - to update the others types of structures after the move is made when it is a rock
 * Undo_Last_Move - to undo the last move made and update the board, the log, the captured pieces, the stateofrockandcheck, the players structure, the pawn tracking structure
 * 
 * Is_Check_Mate - to get know if the king is in check mate or not, or if it is in check or in draw
 * Are_They_Possibles_Moves - to get the number of possibles moves for a player at this state of the game
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
// Function to create a copy of the board
/**
 * @param board : the board to copy
 * @return Piece*** : the copy of the board
**/
/////////////////////////////////////////////////////////////////////////////////////
Piece*** Copy_Board(Piece*** board);


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


/////////////////////////////////////////////////////////////////////////////////////
// function to get know if the king is in check mate or not 
// will use Is_Check and Is_Move_Valid_King in every direction to know if the king can move or not
// or if it can capture the piece that is putting it in check or not (without being in Check there : some recursive function there with two floors)
// need to use the function Get_Pieces_That_Check_King to know the pieces that are checking the king
// or if another piece can capture it
/**
 * @param color - the color of the king
 * @param board_init - the board where we're currently playing
 * @param State_Of_Rock_and_Check_init - the state of the rock and check state
 * @param Move_Log_init - the log of the moves that have been made
 * @param Pawn_Move_State_init - the state of the pawn to know if it has moved 2 squares or not
 * @param Captured_Pieces_and_Score_init - the structure that contains the captured pieces and the score
 * @param players_init - the players
 * @param type_promoted_pawn - the type of the piece that the pawn will be promoted to
 * @return int - BLACK_CHECKMATE, WHITE_CHECKMATE, DRAW or NO_CHECK, BLACK_CHECK, WHITE_CHECK
 * // it can be use as a shortcut to use the is check function at the start of our loop to make a move and see if it can be done and if the game is ending
**/
/////////////////////////////////////////////////////////////////////////////////////
int Is_Check_Mate(int color, Piece*** board_init, State_Of_Rock_and_Check* State_Of_Rock_and_Check_init, Move_Log_array* Move_Log_init, Tiles_Pawn* Pawn_Move_State_init, Captured_Piece_and_Score* Captured_Pieces_and_Score_init, Players* players_init, int type_promoted_pawn);


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the number of possibles moves for a player at this state of the game
/**
 * @param color - the color of the player
 * @param board_init - the board where we're currently playing
 * @param State_Of_Rock_and_Check_init - the state of the rock and check state
 * @param Move_Log_init - the log of the moves that have been made
 * @param Pawn_Move_State_init - the state of the pawn to know if it has moved 2 squares or not
 * @param Captured_Pieces_and_Score_init - the structure that contains the captured pieces and the score
 * @param players_init - the players
 * @param type_promoted_pawn - the type of the piece that the pawn will be promoted to
 * @return bool - true if there is at least one possible move, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool Are_They_Possibles_Moves(int color, Piece*** board_init, State_Of_Rock_and_Check* State_Of_Rock_and_Check_init, Move_Log_array* Move_Log_init, Tiles_Pawn* Pawn_Move_State_init, Captured_Piece_and_Score* Captured_Pieces_and_Score_init, Players* players_init, int type_promoted_pawn);


#endif /* __BOARD_H__ */