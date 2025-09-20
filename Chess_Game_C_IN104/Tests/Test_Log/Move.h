#ifndef __MOVE_H__
#define __MOVE_H__


#include <stdio.h>
#include <stdlib.h>


/////////////////////////////////////////////////////////////////////////////////////
// Move Summary : 
/**
 * Move - a structure that represents a chess game move, concerning the positions of the pieces
 * CreateMove - creates a chess game move
 * Change_Move - change the given chess game move (by using a pointer) to a move struct
 * CopyMove - creates a copy of a chess game move
 * DestroyMove - frees all memory allocation associated with a given chess game move
 * 
 * Move will be used in the game, when taking the coordinates from the Mouse, but also in the log of the game, to store the moves made, with others informations
 * It will be useful to change the board by supressing the previous piece and putting the piece in the new position with only one structure
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Structure that represents a chess game move, concerning the positions of the pieces
/////////////////////////////////////////////////////////////////////////////////////
typedef struct Move {
	int previous_row; // the row position it's coming from
	int previous_col; // the column position it's coming from
	int destination_row; // the row position it's going to
	int destination_col; // the column position it's going to
} Move;


/////////////////////////////////////////////////////////////////////////////////////
// Creates a chess game move 
/**
 * @param previous_row - the row position it's coming from
 * @param previous_col - the column position it's coming from
 * @param destination_row -the row position it's going to
 * @param destination_col - the column position it's going to
 * @return Move* - a pointer to the created chess game move.
 * NULL, if an allocation error occurred.
**/ 
/////////////////////////////////////////////////////////////////////////////////////
Move* Create_Move(int previous_row, int previous_col, int destination_row, int destination_col);


/////////////////////////////////////////////////////////////////////////////////////
// Change the given chess game move (by using a pointer) to a move struct
/**
 * The usage of the function implies that the position given are correct
 * @param move - the move to set
 * @param previous_row - the row position it's coming from
 * @param previous_col - the column position it's coming from
 * @param destination_row - the row position it's going to
 * @param destination_col - the column position it's going to
**/
/////////////////////////////////////////////////////////////////////////////////////
void Change_Move(Move* move, int previous_row, int previous_col, int destination_row, int destination_col);


/////////////////////////////////////////////////////////////////////////////////////
// Creates a copy of a chess game move.
/**
 * @param move - the source chess game move to copy.
 * @return Move* - a copy of the move given in parameter.
 * NULL if either an allocation error occurs or move == NULL.
 */
/////////////////////////////////////////////////////////////////////////////////////
Move* Copy_Move(Move* move);


/////////////////////////////////////////////////////////////////////////////////////
// Frees all memory allocation associated with a given chess game move
// if the source move is NULL, then the function does nothing.
/**
 * @param move - the chess game move we want to free
**/
/////////////////////////////////////////////////////////////////////////////////////
void Destroy_Move(Move* move);


#endif /* __MOVE_H__ */
