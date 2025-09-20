#ifndef __MOVE_LOG_H__
#define __MOVE_LOG_H__


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "Constants.h"
#include "Move.h"


/////////////////////////////////////////////////////////////////////////////////////
// Move_Log summary:
/**
 * A container that represents a fixed size linked list. Each list's element contains the move that has been done
 * (source/previous and destination), the captured piece if exists (NOTHING and NO_COLOR otherwise), and check state.
 * The capacity of the list is specified at the creation. The container supports typical list
 * functionalities with the addition of random access as in arrays.
 * Upon insertion, if the maximum capacity is reached then an error message is
 * returned and the list is not affected. 
 * 
 * A summary of the supported functions is given below:
 *
 * Move_Log_Element - a structure that represents an element in the history log
 * Move_Log_array - a structure that represents the history log of each move in the game (it's an array of moves)
 * Move_Log_array_MESSAGE_TYPE - a type used for errors or success messages
 * 
 * Create_Element_Move_Log - creates a move log element
 * Destroy_Move_Log_Element - destroys a move log element
 * Copy_Move_Log_Element - copies a move log element
 * Change_Move_Log_Element - changes the move log element according to the given parameters
 * Get_Move_Log_Element_at_Index - returns the element at the specified index in the Move_Log_array
 * Get_First_Element_of_Move_Log_array - returns the element at the beginning of the list
 * Get_Last_Element_of_Move_Log_array - returns the element at the end of the list
 * 
 * Create_Move_Log_array - creates an empty array list with the specified maximum capacity
 * Copy_Move_Log_array - copies the given array list
 * Destroy_Move_Log_array - destroys the given array list
 * Get_Move_Log_array_Max_Size - gets the maximum capacity of the given array list
 * Get_Move_Log_array_Size - gets the actual size of the given array list
 * Is_Move_Log_array_Full - checks if the given array list is full
 * Is_Move_Log_array_Empty - checks if the given array list is empty
 * Move_Log_array_Clear - function that reset the given array list to zero, in all parameters
 * Add_Element_in_Move_Log_array_at_Index - adds a new element at the end of the given array list
 * Add_Element_to_the_beggining_of_Move_Log_array - adds a new element at the beggining of the given array list
 * Add_Element_to_the_end_of_Move_Log_array - adds a new element at the end of the given array list
 * Remove_Element_in_Move_Log_array_at_Index - removes the element at the specified index in the given array list
 * Remove_First_Element_in_Move_Log_array - removes the element at the beginning of the given array list (the first element)
 * Remove_Last_Element_in_Move_Log_array - removes the element at the end of the given array list (the last element) 
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Structure that represents an element in the history log
/////////////////////////////////////////////////////////////////////////////////////
typedef struct {
	Move* move; // the move that has been done, a pointer to a move structure
	int taken_piece_type; // the captured piece type : NOTHING, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING
	int taken_piece_color; // the captured piece color : WHITE or BLACK
	int check_state; //check state before move is done : NO_CHECK for no check, BLACK_CHECK for black check, WHITE_CHECK for white check
	int rock_type; // the type of the rock move : NOROCK or SHORT_ROCK or LONG_ROCK (allows to know if the rock has been done to be able to undo it)
} Move_Log_Element;


/////////////////////////////////////////////////////////////////////////////////////
// Structure that represents the history log of each move in the game (it's an array of moves)
/////////////////////////////////////////////////////////////////////////////////////
typedef struct {
	Move_Log_Element** Move_Log; //an array of history's elements, a pointer to it
	int actual_size;
	int max_size;
} Move_Log_array;
// don't need to get the color of the piece, since we just have to go the index of the piece in the board (%2==0 for white, %2==1 for black)


/////////////////////////////////////////////////////////////////////////////////////
// A type used for errors
/////////////////////////////////////////////////////////////////////////////////////
typedef enum {
	LOG_LIST_SUCCESS,
	LOG_LIST_INVALID_ARGUMENT,
	LOG_LIST_FULL,
	LOG_LIST_EMPTY
} Move_Log_array_MESSAGE_TYPE;


/////////////////////////////////////////////////////////////////////////////////////
// Creates a move log element
/**
 * @return
 * NULL, if an allocation error occurred.
 * An instant of an array list element otherwise.
**/
/////////////////////////////////////////////////////////////////////////////////////
Move_Log_Element* Create_Element_Move_Log();


/////////////////////////////////////////////////////////////////////////////////////
// Destroys a move log element
/**
 * @param elem - the element to destroy
**/
/////////////////////////////////////////////////////////////////////////////////////
void Destroy_Move_Log_Element(Move_Log_Element* elem);


/////////////////////////////////////////////////////////////////////////////////////
// Copies a move log element
/**
 * @param elem - the element to copy
 * @return
 * NULL, if an allocation error occurred or elem == NULL.
 * A new copy of the element otherwise.
**/
/////////////////////////////////////////////////////////////////////////////////////
Move_Log_Element* Copy_Move_Log_Element(Move_Log_Element* elem);


/////////////////////////////////////////////////////////////////////////////////////
// Changes the move log element according to the given parameters
/**
 * @param elem - the element to change
 * @param previous_row - the row position it's coming from
 * @param previous_col - the column position it's coming from
 * @param destination_row - the row position it's going to
 * @param destination_col - the column position it's going to
 * @param check_state - the check state before move is done : NO_CHECK for no check, BLACK_CHECK for black check, WHITE_CHECK for white check
 * @param taken_piece_type - the captured piece type : NOTHING, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING
 * @param taken_piece_color - the captured piece color : WHITE or BLACK
 * @param rock_type - the type of the rock move : NOROCK or SHORT_ROCK or LONG_ROCK (allows to know if the rock has been done to be able to undo it)
**/
/////////////////////////////////////////////////////////////////////////////////////
void Change_Move_Log_Element(Move_Log_Element* elem, int previous_row, int previous_col, int destination_row, int destination_col, int check_state, int taken_piece_type, int taken_piece_color, int rock_type);


/////////////////////////////////////////////////////////////////////////////////////
// Returns the element at the specified index in the Move_Log_array
/**
 * @param Moves_Log - the array of moves
 * @param index - the index of the element to return
 * @return
 * NULL, if an allocation error occurred or index is out of bounds.
 * The element at the specified index otherwise.
**/
/////////////////////////////////////////////////////////////////////////////////////
Move_Log_Element* Get_Move_Log_Element_at_Index(Move_Log_array* Moves_Log, int index);


/////////////////////////////////////////////////////////////////////////////////////
// Returns the element at the beginning of the list
/**
 * @param Moves_log - the source array list
 * @return
 * NULL if either src == NULL or the list is empty
 * Otherwise, the element at the beginning of the list is returned.
**/
/////////////////////////////////////////////////////////////////////////////////////
Move_Log_Element* Get_First_Element_of_Move_Log_array(Move_Log_array* Moves_log);


/////////////////////////////////////////////////////////////////////////////////////
// Returns the element at the end of the list
/**
 * @param Moves_log - the source array list
 * @return
 * NULL if either src == NULL or the list is empty
 * Otherwise, the element at the end of the list is returned.
**/
/////////////////////////////////////////////////////////////////////////////////////
Move_Log_Element* Get_Last_Element_of_Move_Log_array(Move_Log_array* Moves_log);


/////////////////////////////////////////////////////////////////////////////////////
// Creates an empty array list with the specified maximum capacity.
/**
 * @param Max_Size - the maximum capacity of the target array list.
 * @return - an array of moves that consistute the history / log of the game
 * NULL, if an allocation error occurred or max_size  <= 0.
**/
/////////////////////////////////////////////////////////////////////////////////////
Move_Log_array* Create_Move_Log_array(int Max_Size);


/////////////////////////////////////////////////////////////////////////////////////
// Copies the given array list
/**
 * @param Moves_Log - the array list to copy
 * @return
 * NULL, if an allocation error occurred or Moves_Log == NULL.
 * A new copy of the array list otherwise.
**/
/////////////////////////////////////////////////////////////////////////////////////
Move_Log_array* Copy_Move_Log_array(Move_Log_array* Moves_Log);


/////////////////////////////////////////////////////////////////////////////////////
// Destroys the given array list
/**
 * @param Moves_Log - the array list to destroy
**/
/////////////////////////////////////////////////////////////////////////////////////
void Destroy_Move_Log_array(Move_Log_array* Moves_Log);


/////////////////////////////////////////////////////////////////////////////////////
// Gets the maximum capacity of the given array list
/**
 * @param Moves_Log - the source array list
 * @return
 * -1, if Moves_Log == NULL.
 * The maximum capacity of the array list otherwise.
**/
/////////////////////////////////////////////////////////////////////////////////////
int Get_Move_Log_array_Max_Size(Move_Log_array* Moves_Log);


/////////////////////////////////////////////////////////////////////////////////////
// Gets the actual size of the given array list
/**
 * @param Moves_Log - the source array list
 * @return
 * -1, if Moves_Log == NULL.
 * The actual size of the array list otherwise.
**/
/////////////////////////////////////////////////////////////////////////////////////
int Get_Move_Log_array_Size(Move_Log_array* Moves_Log);


/////////////////////////////////////////////////////////////////////////////////////
// Checks if the given array list is full
/**
 * @param Moves_Log - the source array list
 * @return
 * false, if Moves_Log == NULL or the list is not full.
 * true, if the list is full.
**/
/////////////////////////////////////////////////////////////////////////////////////
bool Is_Move_Log_array_Full(Move_Log_array* Moves_Log);


/////////////////////////////////////////////////////////////////////////////////////
// Checks if the given array list is empty
/**
 * @param Moves_Log - the source array list
 * @return
 * false, if Moves_Log == NULL or the list is not empty.
 * true, if the list is empty.
**/
/////////////////////////////////////////////////////////////////////////////////////
bool Is_Move_Log_array_Empty(Move_Log_array* Moves_Log);


/////////////////////////////////////////////////////////////////////////////////////
// Function that reset the given array list to zero, in all parameters
/**
 * @param Moves_Log - the array list to reset
 * @return
 * LOG_LIST_INVALID_ARGUMENT, if Moves_Log == NULL.
 * LOG_LIST_SUCCESS, otherwise.
**/
/////////////////////////////////////////////////////////////////////////////////////
Move_Log_array_MESSAGE_TYPE Move_Log_array_Clear(Move_Log_array* Moves_Log);


/////////////////////////////////////////////////////////////////////////////////////
// Adds a new element at the end of the given array list
/**
 * @param Moves_Log - the array list to which we want to add an element
 * @param elem - the element to add
 * @return
 * LOG_LIST_INVALID_ARGUMENT, if Moves_Log == NULL or elem == NULL.
 * LOG_LIST_FULL, if the list is full.
 * LOG_LIST_SUCCESS, otherwise.
**/
/////////////////////////////////////////////////////////////////////////////////////
Move_Log_array_MESSAGE_TYPE Add_Element_in_Move_Log_array_at_Index(Move_Log_array* Moves_Log, Move_Log_Element* elem, int index);

/////////////////////////////////////////////////////////////////////////////////////
// Adds a new element at the beggining of the given array list
/**
 * @param Moves_Log - the array list to which we want to add an element
 * @param elem - the element to add
 * @return
 * LOG_LIST_INVALID_ARGUMENT, if Moves_Log == NULL or elem == NULL.
 * LOG_LIST_FULL, if the list is full.
 * LOG_LIST_SUCCESS, otherwise.
**/
/////////////////////////////////////////////////////////////////////////////////////
Move_Log_array_MESSAGE_TYPE Add_Element_to_the_beggining_of_Move_Log_array(Move_Log_array* Moves_Log, Move_Log_Element* elem);

/////////////////////////////////////////////////////////////////////////////////////
// Adds a new element at the end of the given array list
/**
 * @param Moves_Log - the array list to which we want to add an element
 * @param elem - the element to add
 * @return
 * LOG_LIST_INVALID_ARGUMENT, if Moves_Log == NULL or elem == NULL.
 * LOG_LIST_FULL, if the list is full.
 * LOG_LIST_SUCCESS, otherwise.
**/
Move_Log_array_MESSAGE_TYPE Add_Element_to_the_end_of_Move_Log_array(Move_Log_array* Moves_Log, Move_Log_Element* elem);


/////////////////////////////////////////////////////////////////////////////////////
// Removes the element at the specified index in the given array list
/**
 * @param Moves_Log - the array list from which we want to remove an element
 * @param index - the index of the element to remove
 * @return
 * LOG_LIST_INVALID_ARGUMENT, if Moves_Log == NULL or index is out of bounds.
 * LOG_LIST_EMPTY, if the list is empty.
 * LOG_LIST_SUCCESS, otherwise.
**/
/////////////////////////////////////////////////////////////////////////////////////
Move_Log_array_MESSAGE_TYPE Remove_Element_in_Move_Log_array_at_Index(Move_Log_array* Moves_Log, int index);


/////////////////////////////////////////////////////////////////////////////////////
// Removes the element at the beginning of the given array list (the first element)
/**
 * @param Moves_Log - the array list from which we want to remove an element
 * @return
 * LOG_LIST_INVALID_ARGUMENT, if Moves_Log == NULL.
 * LOG_LIST_EMPTY, if the list is empty.
 * LOG_LIST_SUCCESS, otherwise.
**/
/////////////////////////////////////////////////////////////////////////////////////
Move_Log_array_MESSAGE_TYPE Remove_First_Element_in_Move_Log_array(Move_Log_array* Moves_Log);


/////////////////////////////////////////////////////////////////////////////////////
// Removes the element at the end of the given array list (the last element)
/**
 * @param Moves_Log - the array list from which we want to remove an element
 * @return
 * LOG_LIST_INVALID_ARGUMENT, if Moves_Log == NULL.
 * LOG_LIST_EMPTY, if the list is empty.
 * LOG_LIST_SUCCESS, otherwise.
**/
/////////////////////////////////////////////////////////////////////////////////////
Move_Log_array_MESSAGE_TYPE Remove_Last_Element_in_Move_Log_array(Move_Log_array* Moves_Log);


#endif /* __MOVE_LOG_H__ */