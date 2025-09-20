#ifndef __PIECE_H__
#define __PIECE_H__


#include <stdbool.h>
#include "Constants.h"
#include "Move.h"
#include "Move_Log.h"


/////////////////////////////////////////////////////////////////////////////////////
// Piece Summary 
/**
 * Piece - structure that define what a piece is
 * Captured_Piece_and_Score - structure that the array of the captured pieces, depending on the color
 * State_Of_Rock_and_Check - structure that get the state of the rock and check state (if it has already been done or not) (if it's still possible or not)
 * 
 * A summary of the supported functions is given below:
 * 
 * Create_Piece - create a piece
 * Destroy_Piece - destroy a piece
 * Get_Piece - get the piece that is on the board at the given position
 * 
 * Is_Move_Valid - look if the move is valid for a certain piece on the board
 * Is_Move_Valid_Pawn - look if the move is valid for a pawn on the board
 * Get_State_Of_Pawn - get the state of a pawn (if it is still on its start line or not)
 * Get_Pawn_Neighbors - get the neighbors of a pawn (the two squares in the diagonal, going up or down depending on it's color)
 * Is_Move_Valid_Knight - look if the move is valid for a knight on the board
 * Is_Move_Valid_Bishop - look if the move is valid for a bishop on the board
 * Is_Move_Valid_Rook - look if the move is valid for a rook on the board
 * Is_Move_Valid_Queen - look if the move is valid for a queen on the board
 * Is_Move_Valid_King - look if the move is valid for a king on the board (switch case with the rock)
 * 
 * Create_State_Of_Rock_and_Check - function to create a structure of the state of the rock and check state
 * Destroy_State_Of_Rock_and_Check - function to destroy a structure of the state of the rock and check state
 * Is_Rock_Possible - function to get if the rock is possible or not (if the first line is empty and if the king is not in check) (will be used in Is_Move_Valid_King)
 * Get_Type_Of_Rock - get the type of rock that is going to be made
 * Create_Rook_Move_during_Rock - function that creates during the rock the move of the rook (depending on the type of rock : inside the function by calling Get_Type_Of_Rock)
 * Create_King_Move_during_Rock - function that creates the move of the king during the rock
 * Undo_Rook_during_Rock - function to undo the rook during the rock (will be used in the undo move)(but since the move will be considered for the king, we need to know the type of rock and change again the rook affected by the rock)
 * 
 * Will_Capture - tell wether a move (that will be made, so we suppose it's valid, it will only be used in those cases) will capture a piece or not
 * Create_Captured_Piece_and_Score - create a structure of captured pieces
 * Destroy_Captured_Piece_and_Score - destroy a structure of captured pieces
 * Add_Piece_To_Captured_Pieces - add a piece to the list of captured pieces (will be used only when a piece is taken down by another one during a move) --> when Will_Capture is true
 * Update_Score - function to udpate the score of the game (will be used only when a piece is taken down by another one during a move) --> when Will_Capture is true
 * 
 * Is_Check - function to get know if the king is in check or not
 * Is_Check_Mate - function to get know if the king is in check mate or not
 * Get_Pieces_That_Check_King - function to get the array of the pieces that are checking the king
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Structure that define what a piece is 
// It's position on the board will be defined by the position in the array of the board
/////////////////////////////////////////////////////////////////////////////////////
typedef struct{
    int row; // the row position of the piece
    int col; // the column position of the piece

    int type; // NOTHING, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING
    int color; // NO_COLOR, WHITE, BLACK
    int value; // value of the piece, used to calculate the score
    bool is_alive; // true if the piece is still on the board, false if it has been taken down previously
    bool is_checked; // true if the piece is the king and is checked, false otherwise
    bool is_on_his_start_position; // true if the piece is a pawn and is on his start line, false otherwise
    // the last one is only for the pawn, to know if it can move two squares or not, 
    // the rook and the king, to know if the rock is possible, if I prefer this solution to the one with the strucuture that is dediced to the rock
} Piece;


/////////////////////////////////////////////////////////////////////////////////////
// Structure that the array of the captured pieces 
/////////////////////////////////////////////////////////////////////////////////////
typedef struct{
    Piece** white_pieces_captured; // array of the pieces that are captured and that are white
    Piece** black_pieces_captured; // array of the pieces that are captured and that are black
    int number_of_white_pieces_captured; // number of white pieces that have been captured yet 
    int number_of_black_pieces_captured; // number of black pieces that have been captured yet
    int max_number_of_pieces; // maximum number of pieces that can be captured, used to allocate the memory
    int score; // score difference 
    int player_that_is_winning; // Player1 or Player2, so we can print the score and the winning player
} Captured_Piece_and_Score;


/////////////////////////////////////////////////////////////////////////////////////
// Structure that get the state of the rock and check state (if it has already been done or not) (if it's still possible or not)
/////////////////////////////////////////////////////////////////////////////////////
typedef struct{
    bool white_rock_done; // true if the rock has already been done, false otherwise
    bool white_king_moved; // true if the king has already moved, false otherwise
    bool white_left_rook_moved; // true if the left rook has already moved, false otherwise
    bool white_right_rook_moved; // true if the right rook has already moved, false otherwise

    bool is_white_king_checked; // true if the white king is checked, false otherwise

    bool black_rock_done; // true if the rock has already been done, false otherwise
    bool black_king_moved; // true if the king has already moved, false otherwise
    bool black_left_rook_moved; // true if the left rook has already moved, false otherwise
    bool black_right_rook_moved; // true if the right rook has already moved, false otherwise

    bool is_black_king_checked; // true if the black king is checked, false otherwise
} State_Of_Rock_and_Check;


/////////////////////////////////////////////////////////////////////////////////////
// Create a piece
/**
 * @return Piece* - a pointer to the created piece.
 * NULL, if an allocation error occurred.
**/
/////////////////////////////////////////////////////////////////////////////////////
Piece* Create_Piece();

/////////////////////////////////////////////////////////////////////////////////////
// Destroy a piece
/**
 * @param piece - the piece to destroy
**/
/////////////////////////////////////////////////////////////////////////////////////
void Destroy_Piece(Piece* piece);


/////////////////////////////////////////////////////////////////////////////////////
// Get the piece that is on the board at the given position
/**
 * @param row - the row position of the piece
 * @param col - the column position of the piece
 * @param board - the board where the piece is
 * @return Piece* - a pointer to the piece that is on the board at the given position
 * NULL, if the position is out of the board or if there is no piece at this position
**/
/////////////////////////////////////////////////////////////////////////////////////
Piece* Get_Piece(int row, int col, Piece*** board);


/////////////////////////////////////////////////////////////////////////////////////
// Look if the move is valid for a certain piece on the board
// will be a huge switch case with all the pieces, but each piece will have its own function
// Is_move_valid will be the main function that will call the others and will also check if the move don't go over the bound of the board
/**
 * @param move - the move to check
 * @param piece - the piece that is going to move
 * @param board - the board where the piece is
 * @return bool - true if the move is valid, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool Is_Move_Valid(Move* move, Piece* piece, Piece*** board);


/////////////////////////////////////////////////////////////////////////////////////
// Look if the move is valid for a pawn on the board
/**
 * @param move - the move to check
 * @param piece - the piece that is going to move
 * @param board - the board where the piece is
 * @return bool - true if the move is valid, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool Is_Move_Valid_Pawn(Move* move, Piece* piece, Piece*** board);


/////////////////////////////////////////////////////////////////////////////////////
// Get the state of a pawn (if it is still on its start line or not), so I can help to know if it can move two squares or not (need an if else depending on the color)
/**
 * @param piece - the piece (pawn) that is going to be selected
 * @param board - the board where the piece is
 * @return bool - true if the pawn is still on its start line, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool Get_State_Of_Pawn(Piece* piece, Piece*** board);


/////////////////////////////////////////////////////////////////////////////////////
// Get the neighbors of a pawn (the two squares in the diagonal, going up or down depending on it's color), so it can help us to know if it can capture a piece or not
/**
 * @param piece - the piece that is going to move
 * @param board - the board where the piece is
 * @return Piece** - an array of the two neighbors of the pawn
**/
/////////////////////////////////////////////////////////////////////////////////////
Piece** Get_Pawn_Neighbors(Piece* piece, Piece*** board);


/////////////////////////////////////////////////////////////////////////////////////
// Look if the move is valid for a knight on the board
/**
 * @param move - the move to check
 * @param piece - the piece that is going to move
 * @param board - the board where the piece is
 * @return bool - true if the move is valid, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool Is_Move_Valid_Knight(Move* move, Piece* piece, Piece*** board);


/////////////////////////////////////////////////////////////////////////////////////
// Look if the move is valid for a bishop on the board
/**
 * @param move - the move to check
 * @param piece - the piece that is going to move
 * @param board - the board where the piece is
 * @return bool - true if the move is valid, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool Is_Move_Valid_Bishop(Move* move, Piece* piece, Piece*** board);


/////////////////////////////////////////////////////////////////////////////////////
// Look if the move is valid for a rook on the board
/**
 * @param move - the move to check
 * @param piece - the piece that is going to move
 * @param board - the board where the piece is
 * @return bool - true if the move is valid, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool Is_Move_Valid_Rook(Move* move, Piece* piece, Piece*** board);


/////////////////////////////////////////////////////////////////////////////////////
// Look if the move is valid for a queen on the board
/**
 * @param move - the move to check
 * @param piece - the piece that is going to move
 * @param board - the board where the piece is
 * @return bool - true if the move is valid, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool Is_Move_Valid_Queen(Move* move, Piece* piece, Piece*** board);


/////////////////////////////////////////////////////////////////////////////////////
// Look if the move is valid for a king on the board (switch case with the rock)
/**
 * @param move - the move to check
 * @param piece - the piece that is going to move
 * @param board - the board where the piece is
 * @return bool - true if the move is valid, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool Is_Move_Valid_King(Move* move, Piece* piece, Piece*** board);


/////////////////////////////////////////////////////////////////////////////////////
// function to create a structure of the state of the rock and check state
/**
 * @return State_Of_Rock_and_Check* - a pointer to the created structure.
 * NULL, if an allocation error occurred.
**/
/////////////////////////////////////////////////////////////////////////////////////
State_Of_Rock_and_Check* Create_State_Of_Rock_and_Check();


/////////////////////////////////////////////////////////////////////////////////////
// function to destroy a structure of the state of the rock and check state
/**
 * @param State_Of_Rock_and_Check - the structure to destroy
**/
/////////////////////////////////////////////////////////////////////////////////////
void Destroy_State_Of_Rock_and_Check(State_Of_Rock_and_Check* State_Of_Rock_and_Check);


/////////////////////////////////////////////////////////////////////////////////////
// function to get if the rock is possible or not (if the first line is empty and if the king is not in check) (will be used in Is_Move_Valid_King)
/**
 * @param color - the color of the piece that is going to move
 * @param State_Of_Rock_and_Check - the structure that contains the state of the rock and check state
 * @return bool - true if the rock is possible, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool Is_Rock_Possible(int color /* same as player */, State_Of_Rock_and_Check* State_Of_Rock_and_Check);


/////////////////////////////////////////////////////////////////////////////////////
// Get the type of rock that is going to be made
/**
 * @param move - the move that is going to be made (the one from the king)
 * @param board - the board where the move will be made
 * @return int - the type of rock that is going to be made (SHORT_ROCK or LONG_ROCK)
**/
/////////////////////////////////////////////////////////////////////////////////////
int Get_Type_Of_Rock(Move* move, Piece*** board);


/////////////////////////////////////////////////////////////////////////////////////
// function that creates during the rock the move of the rook (depending on the type of rock : inside the function by calling Get_Type_Of_Rock)
/**
 * @param Piece - the king that is going to move (we have the information on it)
 * @param move - the move that is going to be made (deplacement of the king)
 * @param board - the board where the move will be made
**/
/////////////////////////////////////////////////////////////////////////////////////
Move* Create_Rook_Move_during_Rock(Piece* piece, Move* move, Piece*** board);


/////////////////////////////////////////////////////////////////////////////////////
// function that creates the move of the king during the rock
/**
 * @param Piece - the king that is going to move (we have the information on it)
 * @param move - the move that is going to be made (deplacement of the king)
 * @param board - the board where the move will be made
**/
/////////////////////////////////////////////////////////////////////////////////////
Move* Create_King_Move_during_Rock(Piece* piece, Move* move, Piece*** board);


/////////////////////////////////////////////////////////////////////////////////////
// function to undo the rook during the rock (will be used in the undo move)(but since the move will be considered for the king, we need to know the type of rock and change again the rook affected by the rock)
/**
 * @param move - the move that is going to be undone
 * @param board - the board where the move will be undone
 * @param State_Of_Rock_and_Check - the structure that contains the state of the rock and check state
 * @param Move_Log - the log of the moves that have been made
**/
/////////////////////////////////////////////////////////////////////////////////////
void Undo_Rook_during_Rock(Move* move, Piece*** board, State_Of_Rock_and_Check* State_Of_Rock_and_Check, Move_Log_array* Move_Log);


/////////////////////////////////////////////////////////////////////////////////////
// Tell wether a move (that will be made, so we suppose it's valid, it will only be used in those cases) will capture a piece or not
/**
 * @param move - the move that will be made
 * @param board - the board where the move will be made
 * @return bool - true if the move will capture a piece, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool Will_Capture(Move* move, Piece*** board);


/////////////////////////////////////////////////////////////////////////////////////
// Create a structure of captured pieces
/**
 * @param max_number_of_pieces - the maximum number of pieces that can be captured
 * @return Captured_Piece_and_Score* - a pointer to the created structure.
 * NULL, if an allocation error occurred.
**/
/////////////////////////////////////////////////////////////////////////////////////
Captured_Piece_and_Score* Create_Captured_Piece_and_Score(int max_number_of_pieces);


/////////////////////////////////////////////////////////////////////////////////////
// Destroy a structure of captured pieces
/**
 * @param captured_piece_and_score - the structure to destroy
 * @param max_number_of_pieces - the maximum number of pieces that can be captured
**/
/////////////////////////////////////////////////////////////////////////////////////
void Destroy_Captured_Piece_and_Score(Captured_Piece_and_Score* captured_piece_and_score, int max_number_of_pieces);
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Add a piece to the list of captured pieces (will be used only when a piece is taken down by another one during a move) --> when Will_Capture is true
/**
 * @param piece - the piece that has been taken down
 * @param captured_piece_and_score - the structure that contains the list of captured pieces
**/
/////////////////////////////////////////////////////////////////////////////////////
void Add_Piece_To_Captured_Pieces(Piece* piece, Captured_Piece_and_Score* captured_piece_and_score);


/////////////////////////////////////////////////////////////////////////////////////
// function to udpate the score of the game (will be used only when a piece is taken down by another one during a move) --> when Will_Capture is true
/**
 * @param piece - the piece that has been taken down
 * @param captured_piece_and_score - the structure that contains the list of captured pieces
**/
/////////////////////////////////////////////////////////////////////////////////////
void Update_Score(Piece* piece, Captured_Piece_and_Score* captured_piece_and_score);


/////////////////////////////////////////////////////////////////////////////////////
// function to get know if the king is in check or not
// looking in diagonal (bishop, queen, pawn), in line (rook, queen), and in L (knight) to know if it's treated by a piece
// need to consider for diagonal and line if a piece is between the king and the piece that is treating it
/**
 * @param color - the color of the king
 * @param board - the board where the king is
 * @return bool - true if the king is in check, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool Is_Check(int color, Piece*** board);


/////////////////////////////////////////////////////////////////////////////////////
// function to get know if the king is in check mate or not 
// will use Is_Check and Is_Move_Valid_King in every direction to know if the king can move or not
// or if it can capture the piece that is putting it in check or not (without being in Check there : some recursive function there with two floors)
// need to use the function Get_Pieces_That_Check_King to know the pieces that are checking the king
// or if another piece can capture it
/**
 * @param color - the color of the king
 * @param board - the board where the king is
 * @return bool - true if the king is in check mate, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool Is_Check_Mate(int color, Piece*** board);


/////////////////////////////////////////////////////////////////////////////////////
// function to get the array of the pieces that are checking the king
/**
 * @param color - the color of the king
 * @param board - the board where the king is
 * @param number_of_pieces_that_are_checking_king - pointer on the size of the array that will be returned (-1 if a problem occured somewhere)
 * @return Piece** - an array of the pieces that are checking the king
**/
/////////////////////////////////////////////////////////////////////////////////////
Piece** Get_Pieces_That_Check_King(int color, Piece*** board, int* number_of_pieces_that_are_checking_king);


#endif /* __PIECE_H__ */