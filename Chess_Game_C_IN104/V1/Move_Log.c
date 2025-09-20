#include "Move_Log.h"


Move_Log_Element* Create_Element_Move_Log(){

	Move_Log_Element* elem = (Move_Log_Element*)malloc(sizeof(Move_Log_Element)); // initializes structure for the log of moves by allocating memory
	if (elem==NULL){ // malloc error
		return NULL;
	}

	// initializes fields
	elem->move = Create_Move(0,0,0,0); // creates move
	if (elem->move==NULL){ // malloc error
		Destroy_Move_Log_Element(elem);
		return NULL;
	}

	elem->check_state = NO_CHECK; // initializes check_state to NO_CHECK (since no check has been made yet)
	elem->taken_piece_type = NOTHING; // initializes taken to NOTHING (since no piece has been taken yet)
	elem->taken_piece_color = NO_COLOR; // initializes taken to NO_COLOR (since no piece has been taken yet)
	elem->rock_type = NO_ROCK; // initializes rock_type to NO_ROCK (since no rock has been made yet)

	return elem;
}


void Destroy_Move_Log_Element(Move_Log_Element* elem){
	if (elem!=NULL){ // if the element is NULL, nothing to be done
		Destroy_Move(elem->move);
		free(elem);
	}
}


Move_Log_Element* Copy_Move_Log_Element(Move_Log_Element* elem){

	if (elem == NULL){ // if the given element is NULL, the copy is also NULL, also nothing more is to be done
		return NULL;
	}

	Move_Log_Element* copy = Create_Element_Move_Log(); // creates copy, initializes fields

	if (copy == NULL){ // malloc error
		return NULL;
	}

	//initializes copy fields to be the same as in the given element 
	Change_Move(copy->move, elem->move->previous_row, elem->move->previous_col, elem->move->destination_row, elem->move->destination_col); // changes the coordinates of the move 
	// copy the others parameters
	copy->check_state = elem->check_state;
	copy->taken_piece_type = elem->taken_piece_type;
	copy->taken_piece_color = elem->taken_piece_color;
	copy->rock_type = elem->rock_type;

	// returns the copy
	return copy;
}


void Change_Move_Log_Element(Move_Log_Element* elem, int previous_row, int previous_col, int destination_row, int destination_col, int check_state, int taken_piece_type, int taken_piece_color, int rock_type){
	
	// Change the move, and the others parameters
	Change_Move(elem->move, previous_row, previous_col, destination_row, destination_col);
	elem->check_state = check_state;
	elem->taken_piece_type = taken_piece_type;
	elem->taken_piece_color = taken_piece_color;
	elem->rock_type = rock_type;
}


Move_Log_Element* Get_Move_Log_Element_at_Index(Move_Log_array* Moves_Log, int index){
	if (Moves_Log==NULL || index<0 || index >= Moves_Log->actual_size){ // if index is out of bounds or Move_Log==NULL returns NULL
		return NULL;
	}

	Move_Log_Element* result=Create_Element_Move_Log(); // creates a new element to store the result

	// completes the result with the element at the given index
	Change_Move_Log_Element(result, Moves_Log->Move_Log[index]->move->previous_row, Moves_Log->Move_Log[index]->move->previous_col, Moves_Log->Move_Log[index]->move->destination_row, Moves_Log->Move_Log[index]->move->destination_col, Moves_Log->Move_Log[index]->check_state, Moves_Log->Move_Log[index]->taken_piece_type, Moves_Log->Move_Log[index]->taken_piece_color, Moves_Log->Move_Log[index]->rock_type);

	return result; // returns the element at the given index
}


Move_Log_Element* Get_First_Element_of_Move_Log_array(Move_Log_array* Moves_Log){
	return Get_Move_Log_Element_at_Index(Moves_Log, 0); // gets the first element by Get_Move_Log_Element_at_Index on index 0 (It can be NULL if the Move_Log is NULL)
}


Move_Log_Element* Get_Last_Element_of_Move_Log_array(Move_Log_array* Moves_Log){
	if (Moves_Log == NULL) { // if Move_Log is NULL, the last element is also NULL
		return NULL;
	}
	return Get_Move_Log_Element_at_Index(Moves_Log, Moves_Log->actual_size-1); // gets the last element by Get_Move_Log_Element_at_Index on index actual_size-1
}


Move_Log_array* Create_Move_Log_array(int Max_Size){

	if (Max_Size <= 0 ){ // invalid Max_Size (the size of the array must be positive)
		return NULL;
	}

	Move_Log_array* history = (Move_Log_array*)malloc(sizeof(Move_Log_array)); // initializes structure for the log of moves
	if (history == NULL){ // malloc error
		return NULL;
	}

	history->Move_Log = (Move_Log_Element**)malloc(Max_Size*sizeof(Move_Log_Element*)); // initializes array list of Move_Log
	if (history->Move_Log==NULL){ // malloc error
		free(history);
		return NULL;
	}

	for (int i=0;i<Max_Size;i++){
		history->Move_Log[i] = Create_Element_Move_Log(); // initializes each element of the Move_Log array
	}

	history->actual_size = 0; // initializes arrayLists actual_size to zero (since no move has been made yet)
	history->max_size = Max_Size; // initializes arrayLists max_size according to given argument
	return history; // returns the created Move_Log array
}


Move_Log_array* Copy_Move_Log_array(Move_Log_array* Moves_Log){
	if (Moves_Log == NULL){ // if Move_Log is NULL, the copy is also NULL
		return NULL;
	}
	
	Move_Log_Element* elem; // will be used to copy each element of the given Move_Log array

	Move_Log_array* copy = Create_Move_Log_array(Moves_Log->max_size); //creates an arrayList with the same max_size as the given arrayList
	
	if (copy == NULL){ // malloc error
		return NULL;
	}

	// makes a copy of each element in the given Move_Log_array copy
	for (int i=0;i<Moves_Log->actual_size;i++){
		elem = Copy_Move_Log_Element(Get_Move_Log_Element_at_Index(Moves_Log, i));
		
		if (elem == NULL){ // malloc error
			Destroy_Move_Log_array(copy);
			return NULL;
		}
		// adds the copied element to the end of the new Move_Log array
		Add_Element_to_the_end_of_Move_Log_array(copy, elem);
	}

	// updates the actual_size of the new Move_Log array
	copy->actual_size = Moves_Log->actual_size;

	return copy;
}


void Destroy_Move_Log_array(Move_Log_array* Moves_Log){

	if (Moves_Log==NULL){ // nothing to be done if it's already NULL
		return;
	}

	if (Moves_Log->Move_Log != NULL){ // if Move_Log is not NULL, other wise nothing to be done
		// frees all Move_Log in Move_Log
		for (int i=0;i<Moves_Log->actual_size;i++) 
			Destroy_Move_Log_Element(Moves_Log->Move_Log[i]);
		free(Moves_Log->Move_Log);
	}
	free(Moves_Log);
}


int Get_Move_Log_array_Max_Size(Move_Log_array* Moves_Log){
	if(Moves_Log == NULL){ // if Move_Log is NULL returns -1, -1 represents an error
		return -1;
	}
	return Moves_Log->max_size; //returns max_size
}


int Get_Move_Log_array_Size(Move_Log_array* Moves_Log){
	if(Moves_Log == NULL){ // if Move_Log is NULL returns -1, -1 represents an error
		return -1;
	}
	return Moves_Log->actual_size; //returns actual_size
}


bool Is_Move_Log_array_Full(Move_Log_array* Moves_Log){
	if (Moves_Log == NULL){ // if Move_Log is NULL returns false, since it's empty because it doesn't represent anything
		return false;
	}
	return (Moves_Log->actual_size==Moves_Log->max_size);//returns true if full, else false
}


bool Is_Move_Log_array_Empty(Move_Log_array* Moves_Log){
	if (Moves_Log == NULL){ // if Move_Log is NULL returns false, since it's empty because it doesn't represent anything
		return false;
	}
	return (Moves_Log->actual_size==0); //returns true if empty, else false
}


Move_Log_array_MESSAGE_TYPE Move_Log_array_Clear(Move_Log_array* Moves_Log){
	if (Moves_Log==NULL){ // if Move_Log is NULL returns an "invalid" message, since there isn't nothing to clear
		return LOG_LIST_INVALID_ARGUMENT;
	}

	if (Moves_Log->Move_Log != NULL){ // clears list's Move_Log
		for (int i=0;i<Moves_Log->actual_size;i++){ // frees all Move_Log in Move_Log
			Destroy_Move_Log_Element(Moves_Log->Move_Log[i]);
		}
	}

	Moves_Log->actual_size = 0; // changing actual_size to 0, since there isn't any Move_Log in the list

	return LOG_LIST_SUCCESS; // returns "success" message
}


Move_Log_array_MESSAGE_TYPE Add_Element_in_Move_Log_array_at_Index(Move_Log_array* Moves_Log, Move_Log_Element* elem, int index){
	
	// if index is out of bound, elem==NULL or Move_Log==NULL returns an "invalid" message
	if (Moves_Log==NULL || elem==NULL || index<0 || index > Moves_Log->actual_size){
		return LOG_LIST_INVALID_ARGUMENT;
	}

	if (Is_Move_Log_array_Full(Moves_Log)){ //if arrayList is full returns "full" message
			return LOG_LIST_FULL;
	}
	Moves_Log->actual_size++; // increase actual size by 1

	if (index < Moves_Log->actual_size){// if index is less then actual_size
		for (int i=Moves_Log->actual_size-1; i>=index; i--){ // shifts all other Move_Log accordingly by one position to the right, the loop is in this order to avoid not overwriting the previous element
			Moves_Log->Move_Log[i+1]->check_state = Moves_Log->Move_Log[i]->check_state;
			Moves_Log->Move_Log[i+1]->taken_piece_type = Moves_Log->Move_Log[i]->taken_piece_type;
			Moves_Log->Move_Log[i+1]->taken_piece_color = Moves_Log->Move_Log[i]->taken_piece_color;
			Moves_Log->Move_Log[i+1]->rock_type = Moves_Log->Move_Log[i]->rock_type;
			Change_Move(Moves_Log->Move_Log[i+1]->move, Moves_Log->Move_Log[i]->move->previous_row, Moves_Log->Move_Log[i]->move->previous_col, Moves_Log->Move_Log[i]->move->destination_row, Moves_Log->Move_Log[i]->move->destination_col);
		}
	// adds new element in given index
	Change_Move_Log_Element(Moves_Log->Move_Log[index], elem->move->previous_row, elem->move->previous_col, elem->move->destination_row, elem->move->destination_col, elem->check_state, elem->taken_piece_type, elem->taken_piece_color, elem->rock_type);
	}

	return LOG_LIST_SUCCESS; // returns "success" message
}


Move_Log_array_MESSAGE_TYPE Add_Element_to_the_beggining_of_Move_Log_array(Move_Log_array* Moves_Log, Move_Log_Element* elem){
	return Add_Element_in_Move_Log_array_at_Index(Moves_Log, elem, 0); // adds to first position by Add_Element_in_Move_Log_array_at_Index on index 0
}


Move_Log_array_MESSAGE_TYPE Add_Element_to_the_end_of_Move_Log_array(Move_Log_array* Moves_Log, Move_Log_Element* elem){
	if (Moves_Log == NULL || elem == NULL){ // if Move_Log or elem is NULL returns an "invalid" message
		return LOG_LIST_INVALID_ARGUMENT;
	}

	return Add_Element_in_Move_Log_array_at_Index(Moves_Log, elem, Moves_Log->actual_size); // adds to last position by Add_Element_in_Move_Log_array_at_Index on index actual_size
}


Move_Log_array_MESSAGE_TYPE Remove_Element_in_Move_Log_array_at_Index(Move_Log_array* Moves_Log, int index){
	if (Moves_Log==NULL){ // if Move_Log is NULL returns an "invalid" message
		return LOG_LIST_INVALID_ARGUMENT;
	}

	if (Is_Move_Log_array_Empty(Moves_Log)){ // if arrayList is empty returns "empty" message
		return LOG_LIST_EMPTY;
	}

	if (index<0 || index >= Moves_Log->actual_size){ // if index is out of bound returns an "invalid" message (if it's after the last index)
		return LOG_LIST_INVALID_ARGUMENT;
	}

	Destroy_Move_Log_Element(Moves_Log->Move_Log[index]); // "removes" element in index by destroying the element
	if (index < Moves_Log->actual_size-1){ // index is less then actual_size
		for (int i=index; i<Moves_Log->actual_size-1; i++){ // shifts all other Move_Log accordingly by one position to the right, the loop is in this order to avoid not overwriting the previous element
			Moves_Log->Move_Log[i] = Moves_Log->Move_Log[i+1];
		}
	}

	Moves_Log->Move_Log[Moves_Log->actual_size-1] = NULL; // resets the last index
	Moves_Log->actual_size--;// reduces actual_size by 1

	return LOG_LIST_SUCCESS;// returns "success" message
}


Move_Log_array_MESSAGE_TYPE Remove_First_Element_in_Move_Log_array(Move_Log_array* Moves_Log){
	return Remove_Element_in_Move_Log_array_at_Index(Moves_Log, 0); // removes from first position by Remove_Element_in_Move_Log_array_at_Index on index 0
}


Move_Log_array_MESSAGE_TYPE Remove_Last_Element_in_Move_Log_array(Move_Log_array* Moves_Log){
	if (Moves_Log == NULL){ // if Move_Log is NULL returns an "invalid" message
		return LOG_LIST_INVALID_ARGUMENT;
	}

	return Remove_Element_in_Move_Log_array_at_Index(Moves_Log, Moves_Log->actual_size-1); // removes from last position by Remove_Element_in_Move_Log_array_at_Index on index actual_size-1
}