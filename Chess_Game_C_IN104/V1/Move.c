#include "Move.h"


Move* Create_Move(int previous_row, int previous_col, int destination_row, int destination_col){
	
	// Allocate memory for the move
	Move* move = (Move*)malloc(sizeof(Move));
	if (move==NULL){ // malloc error
		return NULL;
	}

	// Initialize the move with the given parameters
	move->previous_row = previous_row;
	move->previous_col = previous_col;
	move->destination_row = destination_row;
	move->destination_col = destination_col;

	// Return the move
	return move;
}


void Change_Move(Move* move, int previous_row, int previous_col, int destination_row, int destination_col){

	// Change the coordinates of the move with the given parameters
	move->previous_row = previous_row;
	move->previous_col = previous_col;
	move->destination_row = destination_row;
	move->destination_col = destination_col;
}


Move* Copy_Move(Move* move){

	// Allocate memory for the copy of the move
	Move* copy_move = (Move*)malloc(sizeof(Move));
	if (copy_move==NULL || move==NULL){
		return NULL; // malloc error
	}

	// Initialize the copy with the same parameters as the move we're copying
	copy_move->previous_row = move->previous_row;
	copy_move->previous_col = move->previous_col;
	copy_move->destination_row = move->destination_row;
	copy_move->destination_col = move->destination_col;

	// Return the copy
	return copy_move;
}


void Destroy_Move(Move* move){

	// Free the memory allocated for the move if it's not NULL (there's no need to free a NULL pointer)
	if (move!=NULL){
		free(move);
	}
}
