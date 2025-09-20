#ifndef __IA_H__
#define __IA_H__

#include "Player.h"
#include "Board.h"
#include "Move.h"
#include "Move_Log.h"
#include "Piece.h"
#include "Player.h"
#include "Constants.h"


/////////////////////////////////////////////////////////////////////////////////////
// IA summary:
/**
 * A summary of the supported functions is given below:
 * Evaluate_Board : function that evaluates the board score
 * Nega_Max_Alpha_Beta_Search : function that returns the best move for the IA following a Alpha-Beta algorithm (minimax with alpha-beta pruning)
 * Find_Best_Move : function that finds the best move for the IA (using the Alpha-Beta algorithm)
 * IA_Play : function that makes the IA play depending on the level
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
//  function that evaluates the board score
/**
 * @param board : the board
 * @param Checkmate : the checkmate
 * @return int : the score of the board
**/
/////////////////////////////////////////////////////////////////////////////////////
int Evaluate_Board(Piece*** board, int Checkmate);


/////////////////////////////////////////////////////////////////////////////////////
// Function that returns the best move for the IA following a Alpha-Beta algorithm (minimax with alpha-beta pruning)
// It's a recursive function that will call itself to find the best move (used in finding the best move for the IA)
/**
 * @param move : the move to play
 * @param Valid_Moves : the valid moves
 * @param number_of_valid_moves : the number of valid moves
 * @param board : the board
 * @param Move_Log : the log of the moves
 * @param Board_Log : the log of the board
 * @param state_of_rock_and_check : the state of rock and check
 * @param Pawn_Move_State : the state of the pawns
 * @param Captured_Pieces_and_Score : the captured pieces and the score
 * @param players : the players
 * @param depth : the depth of the search
 * @param alpha : the alpha value
 * @param beta : the beta value
 * @return int : the score of the best move (modify directly the move parameter)
**/
/////////////////////////////////////////////////////////////////////////////////////
int Nega_Max_Alpha_Beta_Search(Move* move, Piece*** board, Move_Log_array* Move_Log, Board_Log_array* Board_Log, State_Of_Rock_and_Check* state_of_rock_and_check, Tiles_Pawn* Pawn_Move_State, Captured_Piece_and_Score* Captured_Pieces_and_Score, Players* players, int depth, int alpha, int beta);


/////////////////////////////////////////////////////////////////////////////////////
// Function that makes the IA play depending on the level
/**
 * @param move : the move to play
 * @param board : the board
 * @param level : the level of the IA
 * @param IA_color : the color of the IA
 * @param Move_Log : the log of the moves
 * @param Board_Log : the log of the board
 * @param state_of_rock_and_check : the state of rock and check
 * @param Pawn_Move_State : the state of the pawns
 * @param Captured_Pieces_and_Score : the captured pieces and the score
 * @param players : the players
**/
/////////////////////////////////////////////////////////////////////////////////////
void IA_Play(Move* move, Piece*** board, int level, int IA_color, Move_Log_array* Move_Log, Board_Log_array* Board_Log, State_Of_Rock_and_Check* state_of_rock_and_check, Tiles_Pawn* Pawn_Move_State, Captured_Piece_and_Score* Captured_Pieces_and_Score, Players* players);


#endif /* __IA_H__ */