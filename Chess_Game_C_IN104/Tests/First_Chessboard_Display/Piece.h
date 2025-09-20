#ifndef __PIECE_H__
#define __PIECE_H__


#include <stdbool.h>


/////////////////////////////////////////////////////////////////////////////////////
// Piece Summary 
/**
 * Piece - structure that define what a piece is
 * 
 * 
 * 
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Structure that define what a piece is 
/////////////////////////////////////////////////////////////////////////////////////
typedef struct Piece {
    int row; // position on the board, concerning the rows (from 0 to 7)
    int col; // position on the board, concerning the columns (from 0 to 7) (or A to H)
    int type; // NOTHING, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING
    int color; // NO_COLOR, WHITE, BLACK
    bool is_alive; // true if the piece is still on the board, false if it has been taken down previously
    bool is_checked; // true if the piece is the king and is checked, false otherwise
} Piece;


/////////////////////////////////////////////////////////////////////////////////////
// Structure that the array of the captured pieces 
/////////////////////////////////////////////////////////////////////////////////////
typedef struct Captured_Piece_and_Score {
    Piece* pieces_captured; // array of the pieces that are captured
    int number_of_pieces_captured; // number of pieces that have been captured yet 
    int score; // score difference 
    int player_that_is_winning; // Player1 or Player2, so we can print the score and the winning player
} Captured_Piece_and_Score;








#endif /* __PIECE_H__ */