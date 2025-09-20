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
 * Evaluate_Board_Medium : function that evaluates the board score
 * Nega_Max_Alpha_Beta_Search_Medium : function that returns the best move for the IA following a Alpha-Beta algorithm (minimax with alpha-beta pruning)
 * Get_Material_Value : function that get the value of the material of the board for a color
 * Get_Position_Value : function that get the value of the board concerning preferential positions for the different pieces
 * Evaluate_Board_Hard : function that evaluates the board score
 * Order_Moves_Hard : function that sorts the moves in order to play the best move first (call when we can capture a piece)
 * Nega_Max_Alpha_Beta_Search_Captures_Hard : function that returns the best move for the IA following a Alpha-Beta algorithm (minimax with alpha-beta pruning) when the IA can capture a piece
 * Nega_Max_Alpha_Beta_Search_Hard : function to make the Alpha_beta pruning
 * IA_Play : function that makes the IA play depending on the level
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
//  function that evaluates the board score
/**
 * @param board : the board
 * @return int : the score of the board
**/
/////////////////////////////////////////////////////////////////////////////////////
int Evaluate_Board_Medium(Piece*** board);


/////////////////////////////////////////////////////////////////////////////////////
// Function that returns the best move for the IA following a Alpha-Beta algorithm (minimax with alpha-beta pruning)
// It's a recursive function that will call itself to find the best move (used in finding the best move for the IA)
/**
 * @param depth : the depth of the search
 * @param alpha : the alpha value
 * @param beta : the beta value
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
 * @return int : the score of the best move (modify directly the move parameter)
**/
/////////////////////////////////////////////////////////////////////////////////////
int Nega_Max_Alpha_Beta_Search_Medium(int depth, int alpha, int beta, Move* move, Piece*** board, Move_Log_array* Move_Log, Board_Log_array* Board_Log, State_Of_Rock_and_Check* state_of_rock_and_check, Tiles_Pawn* Pawn_Move_State, Captured_Piece_and_Score* Captured_Pieces_and_Score, Players* players);

/////////////////////////////////////////////////////////////////////////////////////
// Function that get the value of the material of the board for a color
/**
 * @param board : the board
 * @param color : the color
 * @return int : the value of the material
**/
/////////////////////////////////////////////////////////////////////////////////////
int Get_Material_Value(Piece*** board, int color);


/////////////////////////////////////////////////////////////////////////////////////
// Function that get the value of the board concerning preferential positions for the different pieces
/**
 * @param board : the board
 * @param white_material : the material of the white player
 * @param black_material : the material of the black player
 * @return int : the value of the position
**/
/////////////////////////////////////////////////////////////////////////////////////
int Get_Position_Value(Piece*** board, int white_material, int black_material);


/////////////////////////////////////////////////////////////////////////////////////
//  function that evaluates the board score
/**
 * @param board : the board
 * @param Move_Log : the log of the moves
 * @param Board_Log : the log of the board
 * @param state_of_rock_and_check : the state of rock and check
 * @param Pawn_Move_State : the state of the pawns
 * @param Captured_Pieces_and_Score : the captured pieces and the score
 * @param players : the players
 * @return int : the score of the board
**/
/////////////////////////////////////////////////////////////////////////////////////
int Evaluate_Board_Hard(Piece*** board, Move_Log_array* Move_Log, Board_Log_array* Board_Log, State_Of_Rock_and_Check* state_of_rock_and_check, Tiles_Pawn* Pawn_Move_State, Captured_Piece_and_Score* Captured_Pieces_and_Score, Players* players);


/////////////////////////////////////////////////////////////////////////////////////
// Function that sorts the moves in order to play the best move first (call when we can capture a piece)
/**
 * @param moves : the moves to order
 * @param number_of_moves : the number of moves
 * @param board : the board
 * @param state_of_rock_and_check : the state of rock and check
 * @param Move_Log : the log of the moves
 * @param Board_Log : the log of the board
 * @param Pawn_Move_State : the state of the pawns
 * @param Captured_Pieces_and_Score : the captured pieces and the score
 * @param players : the players
**/
/////////////////////////////////////////////////////////////////////////////////////
void Order_Moves_Hard(Move** moves, int number_of_moves, Piece*** board, State_Of_Rock_and_Check* state_of_rock_and_check, Move_Log_array* Move_Log, Board_Log_array* Board_Log, Tiles_Pawn* Pawn_Move_State, Captured_Piece_and_Score* Captured_Pieces_and_Score, Players* players);


// Function that returns the best move for the IA following a Alpha-Beta algorithm (minimax with alpha-beta pruning) when the IA can capture a piece
// It's a recursive function that will call itself to find the best move (used in finding the best move for the IA)
/**
 * @param alpha : the alpha value
 * @param beta : the beta value
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
 * @return int : the score of the best move (modify directly the move parameter)
**/
/////////////////////////////////////////////////////////////////////////////////////
int Nega_Max_Alpha_Beta_Search_Captures_Hard(int alpha, int beta, Piece*** board, Move_Log_array* Move_Log, Board_Log_array* Board_Log, State_Of_Rock_and_Check* state_of_rock_and_check, Tiles_Pawn* Pawn_Move_State, Captured_Piece_and_Score* Captured_Pieces_and_Score, Players* players);


/////////////////////////////////////////////////////////////////////////////////////
// Function to make the Alpha_beta pruning 
// It's a recursive function that will call itself to find the best move (used in finding the best move for the IA)
/**
 * @param depth : the depth of the search
 * @param alpha : the alpha value
 * @param beta : the beta value
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
 * @return int : the score of the best move (modify directly the move parameter)
**/
/////////////////////////////////////////////////////////////////////////////////////
int Nega_Max_Alpha_Beta_Search_Hard(int depth, int alpha, int beta, Move* move, Piece*** board, Move_Log_array* Move_Log, Board_Log_array* Board_Log, State_Of_Rock_and_Check* state_of_rock_and_check, Tiles_Pawn* Pawn_Move_State, Captured_Piece_and_Score* Captured_Pieces_and_Score, Players* players);

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