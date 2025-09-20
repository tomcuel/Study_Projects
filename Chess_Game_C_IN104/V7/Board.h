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
 * Structure to get the log of the board (used to know if a draw is forced by the 3 repitition rule or by the 50 moves rule)
 * 
 * A summary of the supported functions is given below:
 * 
 * Init_Board - to initialize the board
 * Reverse_Board - to reverse the board
 * Reset_Board - to reset the board to the initial state
 * Create_Copy_Board - to create a copy of the board
 * Copy_Board_Into - to copy the board into another board
 * Clear_Board - to clear the board
 * Init_Board_Log - to init the board log
 * Create_Copy_Board_Log - to create a copy of the board log
 * Destroy_Board_Log - to destroy the board log
 * Add_Board_at_Last_Index_in_Array - to add a board at the last index in the array
 * 
 * Make_Move - to make a move on the board and update everything : the board, the state of rock and check, the captured pieces, and the players structure
 * Make_Rock_Move - to make a move on the board when a rock is done and update everything : the board, the state of rock and check, the captured pieces, and the players structure
 * Clear_En_Passant_Piece - to clear the pawn taken by the en passant
 * Change_Others_Structures - to update the others types of structures after the move is made
 * Change_Others_Structures_during_Rock - to update the others types of structures after the move is made when it is a rock
 * Make_IA_Global_Move_and_Udpate_structures - to make the IA play depending on the level and update the structures
 * Undo_Last_Move - to undo the last move made and update the board, the log, the captured pieces, the stateofrockandcheck, the players structure, the pawn tracking structure
 * 
 * Is_Check_Mate - to get know if the king is in check mate or not, or if it is in check or in draw
 * Are_They_Possibles_Moves - to get the number of possibles moves for a player at this state of the game
 * Get_Valid_Moves - to get the valid moves for a player at this state of the game
 * Get_Valid_Moves_that_Capture - to get the valid moves that can capture a piece 
 * 
 * Are_Board_Equal - to know if two boards are equal
 * Is_Draw_Forced_By_Log - to know if a draw happened because of the log of the moves (repitition of the same board (same log state) or 50 moves without capture or pawn move)
 * Is_Draw_Forced_By_50_Moves_Rule - to know if a draw happened because of the 50 moves rule
 * Is_Draw_Forced_By_3_Repitition_Rule - to know if a draw happened because of the 3 repitition rule
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Structure to get the log of the board (used to know if a draw is forced by the 3 repitition rule or by the 50 moves rule)
/////////////////////////////////////////////////////////////////////////////////////
typedef struct {
    Piece**** board_log; // the log of the board
    int max_size; // the max size of the log (to allocate the memory)
    int actual_size; // the actual size of the log
} Board_Log_array;


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
Piece*** Create_Copy_Board(Piece*** board);


/////////////////////////////////////////////////////////////////////////////////////
// Function to copy the board into another board
/**
 * @param board : the board to copy
 * @param board_copy : the board to copy into
**/
/////////////////////////////////////////////////////////////////////////////////////
void Copy_Board_Into(Piece*** board, Piece*** board_copy);


/////////////////////////////////////////////////////////////////////////////////////
// Function to clear the board
/**
 * @param board : the board to clear
**/
/////////////////////////////////////////////////////////////////////////////////////
void Clear_Board(Piece*** board);


/////////////////////////////////////////////////////////////////////////////////////
// Function to init the board log
/**
 * @param Max_Size : the max size of the log
 * @return Board_Log_array* : the board log initialized
**/
/////////////////////////////////////////////////////////////////////////////////////
Board_Log_array* Init_Board_Log(int Max_Size);


/////////////////////////////////////////////////////////////////////////////////////
// Function to create a copy of the board log
/**
 * @param board_log_array : the board log to copy
 * @return Board_Log_array* : the copy of the board log
**/
/////////////////////////////////////////////////////////////////////////////////////
Board_Log_array* Create_Copy_Board_Log(Board_Log_array* board_log_array);


/////////////////////////////////////////////////////////////////////////////////////
// Function to destroy the board log
/**
 * @param board_log_array : the board log to destroy
**/
/////////////////////////////////////////////////////////////////////////////////////
void Destroy_Board_Log(Board_Log_array* board_log_array);


/////////////////////////////////////////////////////////////////////////////////////
// Function to add a board at the last index in the array
/**
 * @param Board_Log : the board log
 * @param board : the board to add
 * @return MESSAGE_TYPE : the message type
**/
/////////////////////////////////////////////////////////////////////////////////////
Move_Log_array_MESSAGE_TYPE Add_Board_at_Last_Index_in_Array(Board_Log_array* Board_Log, Piece*** board);


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
// Function to make the IA play depending on the level
/**
 * @param move : the move to play
 * @param board : the board
 * @param players : the players
 * @param Log : the log of the moves
 * @param Log_Board : the log of the board
 * @param State_Of_RockandCheck : the state of rock and check
 * @param Pawn_Move_State : the state of the pawn move
 * @param Captured_Pieces_and_Score : the captured pieces and the score
 * @param IA_color : the color of the IA
 * @param level_IA : the level of the IA
**/
/////////////////////////////////////////////////////////////////////////////////////
void Make_IA_Global_Move_and_Udpate_structures(Move* move, Piece*** board, Players* players, Move_Log_array* Log, Board_Log_array* Log_Board, State_Of_Rock_and_Check* State_Of_RockandCheck, Tiles_Pawn* Pawn_Move_State, Captured_Piece_and_Score* Captured_Pieces_and_Score, int IA_color, int level_IA);


/////////////////////////////////////////////////////////////////////////////////////
// Function that returns a random number between two numbers
/**
 * @param min : the minimum number
 * @param max : the maximum number
 * @return int : the random number generated
**/
/////////////////////////////////////////////////////////////////////////////////////
int Random_Int(int min, int max);


/////////////////////////////////////////////////////////////////////////////////////
// Function to make the pawn promotion for the IA
/**
 * @param move : the move to play
 * @param board : the board
 * @param Log : the log of the moves
 * @param IA_level : the level of the IA
**/
/////////////////////////////////////////////////////////////////////////////////////
void Make_Pawn_Promotion_for_IA(Move* move, Piece*** board, Move_Log_array* Log, int level_IA);


/////////////////////////////////////////////////////////////////////////////////////
// Function to make the pawn promotion for the IA (in the level HARD)
// If a knight can be sure to take a piece after the promotion, the IA will choose to promote the pawn to a knight
// It need to threaten more than one piece and not to be threatened by any piece itself
/**
 * @param board : the board
 * @param row : the row of the pawn
 * @param col : the column of the pawn
**/
/////////////////////////////////////////////////////////////////////////////////////
bool Can_Fork_Knight_Promotion(Piece*** board, int row, int col);


/////////////////////////////////////////////////////////////////////////////////////
// Function to undo the last move made and that update the board, the log, the captured pieces, the stateofrockandcheck, the players structure, the pawn tracking structure
/**
 * @param board : the board
 * @param log : the log of the moves
 * @param log_board : the log of the board
 * @param captured_piece_and_score : the captured pieces and the score
 * @param state_of_rock_and_check : the state of rock and check
 * @param players : the players
 * @param Pawn_Move_State : the state of the pawn move
**/
/////////////////////////////////////////////////////////////////////////////////////
void Undo_Last_Move(Piece*** board, Move_Log_array* log, Board_Log_array* log_board, Captured_Piece_and_Score* captured_piece_and_score, State_Of_Rock_and_Check* state_of_rock_and_check, Players* players, Tiles_Pawn* Pawn_Move_State);


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
 * @param Board_Log_init - the log of the board
 * @param Pawn_Move_State_init - the state of the pawn to know if it has moved 2 squares or not
 * @param Captured_Pieces_and_Score_init - the structure that contains the captured pieces and the score
 * @param players_init - the players
 * @param type_promoted_pawn - the type of the piece that the pawn will be promoted to
 * @return int - BLACK_CHECKMATE, WHITE_CHECKMATE, DRAW or NO_CHECK, BLACK_CHECK, WHITE_CHECK
 * // it can be use as a shortcut to use the is check function at the start of our loop to make a move and see if it can be done and if the game is ending
**/
/////////////////////////////////////////////////////////////////////////////////////
int Is_Check_Mate(int color, Piece*** board_init, State_Of_Rock_and_Check* State_Of_Rock_and_Check_init, Move_Log_array* Move_Log_init, Board_Log_array* Board_Log_init, Tiles_Pawn* Pawn_Move_State_init, Captured_Piece_and_Score* Captured_Pieces_and_Score_init, Players* players_init, int type_promoted_pawn);


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the number of possibles moves for a player at this state of the game
/**
 * @param color - the color of the player
 * @param board_init - the board where we're currently playing
 * @param State_Of_Rock_and_Check_init - the state of the rock and check state
 * @param Move_Log_init - the log of the moves that have been made
 * @param Pawn_Move_State_init - the state of the pawn to know if it has moved 2 squares or not
 * @param Pawn_Move_State_init - the state of the pawn to know if it has moved 2 squares or not
 * @param Captured_Pieces_and_Score_init - the structure that contains the captured pieces and the score
 * @param players_init - the players
 * @param type_promoted_pawn - the type of the piece that the pawn will be promoted to
 * @return bool - true if there is at least one possible move, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool Are_They_Possibles_Moves(int color, Piece*** board_init, State_Of_Rock_and_Check* State_Of_Rock_and_Check_init, Move_Log_array* Move_Log_init, Board_Log_array* Board_Log_init, Tiles_Pawn* Pawn_Move_State_init, Captured_Piece_and_Score* Captured_Pieces_and_Score_init, Players* players_init, int type_promoted_pawn);


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the valid moves for a player at this state of the game
/**
 * @param number_of_moves - the number of valid moves
 * @param color_playing - the color of the player playing
 * @param board_init - the board where we're currently playing
 * @param State_Of_Rock_and_Check_init - the state of the rock and check state
 * @param Move_Log_init - the log of the moves that have been made
 * @param Board_Log_init - the log of the board
 * @param Pawn_Move_State_init - the state of the pawn to know if it has moved 2 squares or not
 * @param Captured_Pieces_and_Score_init - the structure that contains the captured pieces and the score
 * @param players_init - the players
 * @return Move** - the valid moves array
**/
/////////////////////////////////////////////////////////////////////////////////////
Move** Get_Valid_Moves(int* number_of_moves, int color_playing, Piece*** board_init, State_Of_Rock_and_Check* State_Of_Rock_and_Check_init, Move_Log_array* Move_Log_init, Board_Log_array* Board_Log_init, Tiles_Pawn* Pawn_Move_State_init, Captured_Piece_and_Score* Captured_Pieces_and_Score_init, Players* players_init);


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the valid moves that can capture a piece 
// (will be used in the IA alpha-beta function to determine if a move is valuable even if it's not a capture)
/**
 * @param number_of_moves - the number of valid moves
 * @param color_playing - the color of the player playing
 * @param board_init - the board where we're currently playing
 * @param State_Of_Rock_and_Check_init - the state of the rock and check state
 * @param Move_Log_init - the log of the moves that have been made
 * @param Board_Log_init - the log of the board
 * @param Pawn_Move_State_init - the state of the pawn to know if it has moved 2 squares or not
 * @param Captured_Pieces_and_Score_init - the structure that contains the captured pieces and the score
 * @param players_init - the players
 * @return Move** - the valid moves array
**/
/////////////////////////////////////////////////////////////////////////////////////
Move** Get_Valid_Moves_that_Capture(int* number_of_moves, int color_playing, Piece*** board_init, State_Of_Rock_and_Check* State_Of_Rock_and_Check_init, Move_Log_array* Move_Log_init, Board_Log_array* Board_Log_init, Tiles_Pawn* Pawn_Move_State_init, Captured_Piece_and_Score* Captured_Pieces_and_Score_init, Players* players_init);


/////////////////////////////////////////////////////////////////////////////////////
// Function to know if two boards are equal
/**
 * @param board1 - the first board
 * @param board2 - the second board
 * @return bool - true if the boards are equal, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool Are_Board_Equal(Piece*** board1, Piece*** board2);


/////////////////////////////////////////////////////////////////////////////////////
// Function to know if a draw happened because of the log of the moves (repitition of the same board (same log state) or 50 moves without capture or pawn move)
/**
 * @param move_log - the log of the moves
 * @param board_log_array - the log of the board
 * @return bool - true if a draw is forced by the log, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool Is_Draw_Forced_By_Log(Move_Log_array* move_log, Board_Log_array* board_log_array);


/////////////////////////////////////////////////////////////////////////////////////
// Function to know if a draw happened because of the 50 moves rule
/**
 * @param log - the log of the moves
 * @return bool - true if a draw is forced by the 50 moves rule, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool Is_Draw_Forced_By_50_Moves_Rule(Move_Log_array* log);


/////////////////////////////////////////////////////////////////////////////////////
// Function to know if a draw happened because of the 3 repitition rule
/**
 * @param board_log_array - the log of the board
 * @return bool - true if a draw is forced by the 3 repitition rule, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool Is_Draw_Forced_By_3_Repitition_Rule(Board_Log_array* board_log_array);


#endif /* __BOARD_H__ */