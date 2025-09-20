#include "Piece.h"


Piece* Create_Piece(){
    Piece* piece = (Piece*)malloc(sizeof(Piece));
    // looking for a malloc error
    if (piece == NULL){
        printf("Error: malloc failed in Create_Piece\n");
        return NULL;
    }

    // setting the piece to 0 for each attribute
    piece->row = 0;
    piece->col = 0;
    piece->type = NOTHING;
    piece->color = NO_COLOR;
    piece->value = 0;
    piece->is_alive = false;
    piece->is_checked = false;
    piece->is_on_his_start_position = false;

    // return the piece
    return piece;
}


void Destroy_Piece(Piece* piece){
    // if the piece is not NULL, we can free it
    if (piece != NULL){
        free(piece);
    }
}


Piece* Get_Piece(int row, int col, Piece*** board){
    Piece* piece = Create_Piece();
    // looking for a malloc error
    if (piece == NULL){
        printf("Error: malloc failed in Get_Piece\n");
        return NULL;
    }

    // setting the piece to the one at the position given in parameters
    piece->row = row;
    piece->col = col;
    piece->type = board[row][col]->type;
    piece->color = board[row][col]->color;
    piece->value = board[row][col]->value;
    piece->is_alive = board[row][col]->is_alive;
    piece->is_checked = board[row][col]->is_checked;
    piece->is_on_his_start_position = board[row][col]->is_on_his_start_position;

    // return the piece
    return piece;
}


bool Is_Piece_on_its_start_position(Piece* piece){
    // if the piece is a pawn
    if (piece->type == PAWN){
        // if the piece is white
        if (piece->color == WHITE){
            // if the piece is on the 2nd row
            if (piece->row == 1){
                return true;
            }
        }
        // if the piece is black
        else if (piece->color == BLACK){
            // if the piece is on the 7th row
            if (piece->row == 6){
                return true;
            }
        }
    }

    // if the piece is a rook 
    else if (piece->type == ROOK){
        // if the piece is white
        if (piece->color == WHITE){
            // if the piece is on the 1st row and the 1st column or the 1st row and the 8th column
            if ((piece->row == 0 && piece->col == 0) || (piece->row == 0 && piece->col == 7)){
                return true;
            }
        }
        // if the piece is black
        else if (piece->color == BLACK){
            // if the piece is on the 8th row and the 1st column or the 8th row and the 8th column
            if ((piece->row == 7 && piece->col == 0) || (piece->row == 7 && piece->col == 7)){
                return true;
            }
        }
    }

    // if the piece is a knight
    else if (piece->type == KNIGHT){
        // if the piece is white
        if (piece->color == WHITE){
            // if the piece is on the 1st row and the 2nd column or the 1st row and the 7th column
            if ((piece->row == 0 && piece->col == 1) || (piece->row == 0 && piece->col == 6)){
                return true;
            }
        }
        // if the piece is black
        else if (piece->color == BLACK){
            // if the piece is on the 8th row and the 2nd column or the 8th row and the 7th column
            if ((piece->row == 7 && piece->col == 1) || (piece->row == 7 && piece->col == 6)){
                return true;
            }
        }
    }

    // if the piece is a bishop
    else if (piece->type == BISHOP){
        // if the piece is white
        if (piece->color == WHITE){
            // if the piece is on the 1st row and the 3rd column or the 1st row and the 6th column
            if ((piece->row == 0 && piece->col == 2) || (piece->row == 0 && piece->col == 5)){
                return true;
            }
        }
        // if the piece is black
        else if (piece->color == BLACK){
            // if the piece is on the 8th row and the 3rd column or the 8th row and the 6th column
            if ((piece->row == 7 && piece->col == 2) || (piece->row == 7 && piece->col == 5)){
                return true;
            }
        }
    }

    // if the piece is a queen
    else if (piece->type == QUEEN){
        // if the piece is white
        if (piece->color == WHITE){
            // if the piece is on the 1st row and the 4th column
            if (piece->row == 0 && piece->col == 3){
                return true;
            }
        }
        // if the piece is black
        else if (piece->color == BLACK){
            // if the piece is on the 8th row and the 4th column
            if (piece->row == 7 && piece->col == 3){
                return true;
            }
        }
    }

    // if the piece is a king
    else if (piece->type == KING){
        // if the piece is white
        if (piece->color == WHITE){
            // if the piece is on the 1st row and the 5th column
            if (piece->row == 0 && piece->col == 4){
                return true;
            }
        }
        // if the piece is black
        else if (piece->color == BLACK){
            // if the piece is on the 8th row and the 5th column
            if (piece->row == 7 && piece->col == 4){
                return true;
            }
        }
    }

    return false;
}



bool Is_Move_Valid(Move* move, Piece*** board){

}


bool Is_Move_Valid_Pawn(Move* move, Piece*** board){

}


bool Get_State_Of_Pawn(Piece* piece, Piece*** board){

}


Piece** Get_Pawn_Neighbors(Piece* piece, Piece*** board){

}


bool Is_Move_Valid_Knight(Move* move, Piece*** board){

}


bool Is_Move_Valid_Bishop(Move* move, Piece*** board){
    
    // if it's not a diagonal move
    if (abs(move->previous_row - move->destination_row) == abs(move->previous_col - move->destination_col)){
        return false;
    }

    // if the destination is a piece of the same color
    if (board[move->destination_row][move->destination_col]->color == board[move->previous_row][move->previous_col]->color){
        return false;
    }

    // otherwise making cases depending on the direction of the move (the diagonal direction)
    
    // moving to the right and down
    if (move->previous_row < move->destination_row && move->previous_col < move->destination_col){
        // going trough the diagonal
        for (int i = move->previous_row + 1, j = move->previous_col + 1; i < move->destination_row && j < move->destination_col; i++, j++){
            // if the bishop found a piece in the diagonal (it can be of any color)
            if (board[i][j]->type != NOTHING){
                return false;
            }
        }
        return true;
    }

    // moving to the left and down 
    else if (move->previous_row < move->destination_row && move->previous_col > move->destination_col){
        // going trough the diagonal
        for (int i = move->previous_row + 1, j = move->previous_col - 1; i < move->destination_row && j > move->destination_col; i++, j--){
            // if the bishop found a piece in the diagonal (it can be of any color)
            if (board[i][j]->type != NOTHING){
                return false;
            }
        }
        return true;
    }

    // moving to the right and up
    else if (move->previous_row > move->destination_row && move->previous_col < move->destination_col){
        // going trough the diagonal
        for (int i = move->previous_row - 1, j = move->previous_col + 1; i > move->destination_row && j < move->destination_col; i--, j++){
            // if the bishop found a piece in the diagonal (it can be of any color)
            if (board[i][j]->type != NOTHING){
                return false;
            }
        }
        return true;
    }

    // moving to the left and up 
    else if (move->previous_row > move->destination_row && move->previous_col > move->destination_col){
        // going trough the diagonal
        for (int i = move->previous_row - 1, j = move->previous_col - 1; i > move->destination_row && j > move->destination_col; i--, j--){
            // if the bishop found a piece in the diagonal (it can be of any color)
            if (board[i][j]->type != NOTHING){
                return false;
            }
        }
        return true;
    }

    
}


bool Is_Move_Valid_Rook(Move* move, Piece*** board){

}


bool Is_Move_Valid_Queen(Move* move, Piece*** board){

}


bool Is_Move_Valid_King(Move* move, Piece*** board){

}


State_Of_Rock_and_Check* Create_State_Of_Rock_and_Check(){
    State_Of_Rock_and_Check* state_of_rock_and_check = (State_Of_Rock_and_Check*)malloc(sizeof(State_Of_Rock_and_Check));
    // looking for a malloc error
    if (state_of_rock_and_check == NULL){
        printf("Error: malloc failed in Create_State_Of_Rock_and_Check\n");
        return NULL;
    }

    // setting the state of the rock and the check to false
    state_of_rock_and_check->white_rock_done = false;
    state_of_rock_and_check->white_king_moved = false;
    state_of_rock_and_check->white_left_rook_moved = false;
    state_of_rock_and_check->white_right_rook_moved = false;

    state_of_rock_and_check->is_white_king_checked = false;
                
    state_of_rock_and_check->black_rock_done = false;
    state_of_rock_and_check->black_king_moved = false;
    state_of_rock_and_check->black_left_rook_moved = false;
    state_of_rock_and_check->black_right_rook_moved = false;

    state_of_rock_and_check->is_black_king_checked = false;

    // return the state of the rock and the check
    return state_of_rock_and_check;
}


void Reset_State_Of_Rock_and_Check(State_Of_Rock_and_Check* State_Of_Rock_and_Check){
    // if the state of the rock and the check is not NULL, we can reset it
    if (State_Of_Rock_and_Check != NULL){
        // setting the state of the rock and the check to false
        State_Of_Rock_and_Check->white_rock_done = false;
        State_Of_Rock_and_Check->white_king_moved = false;
        State_Of_Rock_and_Check->white_left_rook_moved = false;
        State_Of_Rock_and_Check->white_right_rook_moved = false;

        State_Of_Rock_and_Check->is_white_king_checked = false;
                    
        State_Of_Rock_and_Check->black_rock_done = false;
        State_Of_Rock_and_Check->black_king_moved = false;
        State_Of_Rock_and_Check->black_left_rook_moved = false;
        State_Of_Rock_and_Check->black_right_rook_moved = false;

        State_Of_Rock_and_Check->is_black_king_checked = false;
    }
}


void Destroy_State_Of_Rock_and_Check(State_Of_Rock_and_Check* State_Of_Rock_and_Check){
    // if the state of the rock and the check is not NULL, we can free it
    if (State_Of_Rock_and_Check != NULL){
        free(State_Of_Rock_and_Check);
    }
}


bool Is_Rock_Possible(int color /* same as player */, State_Of_Rock_and_Check* State_Of_Rock_and_Check){

}


int Get_Type_Of_Rock(Move* move, Piece*** board){

}


Move* Create_Rook_Move_during_Rock(Move* move, Piece*** board){

}


Move* Create_King_Move_during_Rock(Move* move, Piece*** board){

}


void Undo_Rook_during_Rock(Move* move, Piece*** board, State_Of_Rock_and_Check* State_Of_Rock_and_Check, Move_Log_array* Move_Log){

}


bool Will_Capture(Move* move, Piece*** board){

}


Captured_Piece_and_Score* Create_Captured_Piece_and_Score(int max_number_of_pieces){
    Captured_Piece_and_Score* captured_piece_and_score = (Captured_Piece_and_Score*)malloc(sizeof(Captured_Piece_and_Score));
    // looking for a malloc error
    if (captured_piece_and_score == NULL){
        printf("Error: malloc failed in Create_Captured_Piece_and_Score\n");
        return NULL;
    }

    // allocating the memory for the array of white pieces captured
    captured_piece_and_score->white_pieces_captured = (Piece**)malloc(max_number_of_pieces * sizeof(Piece*));
    // looking for a malloc error
    if (captured_piece_and_score->white_pieces_captured == NULL){
        printf("Error: malloc failed in Create_Captured_Piece_and_Score\n");
        return NULL;
    }

    // allocating the memory for the array of black pieces captured
    captured_piece_and_score->black_pieces_captured = (Piece**)malloc(max_number_of_pieces * sizeof(Piece*));
    // looking for a malloc error
    if (captured_piece_and_score->black_pieces_captured == NULL){
        printf("Error: malloc failed in Create_Captured_Piece_and_Score\n");
        return NULL;
    }

    // setting the number of white pieces captured to 0
    captured_piece_and_score->number_of_white_pieces_captured = 0;
    // setting the number of black pieces captured to 0
    captured_piece_and_score->number_of_black_pieces_captured = 0;
    // setting the max number of pieces
    captured_piece_and_score->max_number_of_pieces = max_number_of_pieces;
    // setting the score to 0
    captured_piece_and_score->score = 0;
    // setting the player that is winning to Player1
    captured_piece_and_score->player_that_is_winning = NO_COLOR;

    // return the captured piece and score
    return captured_piece_and_score;
}


void Reset_Captured_Piece_and_Score(Captured_Piece_and_Score* captured_piece_and_score){
    // setting the number of white pieces captured to 0
    captured_piece_and_score->number_of_white_pieces_captured = 0;
    // setting the number of black pieces captured to 0
    captured_piece_and_score->number_of_black_pieces_captured = 0;

    // setting the score to 0
    captured_piece_and_score->score = 0;
    // setting the player that is winning to Player1
    captured_piece_and_score->player_that_is_winning = NO_COLOR;
}


void Destroy_Captured_Piece_and_Score(Captured_Piece_and_Score* captured_piece_and_score, int max_number_of_pieces){
    // if the captured piece and score is not NULL, we can free it
    if (captured_piece_and_score != NULL){
        // for each white piece captured, we free it
        for (int i = 0; i < max_number_of_pieces; i++){
            if (captured_piece_and_score->white_pieces_captured[i] != NULL){
                free(captured_piece_and_score->white_pieces_captured[i]);
            }
        }
        // free the array of white pieces captured
        if (captured_piece_and_score->white_pieces_captured != NULL){
            free(captured_piece_and_score->white_pieces_captured);
        }

        // for each black piece captured, we free it
        for (int i = 0; i < max_number_of_pieces; i++){
            if (captured_piece_and_score->black_pieces_captured[i] != NULL){
                free(captured_piece_and_score->black_pieces_captured[i]);
            }
        }
        // free the array of black pieces captured
        if (captured_piece_and_score->black_pieces_captured != NULL){
            free(captured_piece_and_score->black_pieces_captured);
        }

        // free the captured piece and score
        free(captured_piece_and_score);
    }
}



int Get_Value_Of_Piece(int piece_type){
    // if the piece is a pawn
    if (piece_type == PAWN){
        return PAWN_VALUE;
    }

    // if the piece is a rook
    else if (piece_type == ROOK){
        return ROOK_VALUE;
    }

    // if the piece is a knight
    else if (piece_type == KNIGHT){
        return KNIGHT_VALUE;
    }

    // if the piece is a bishop
    else if (piece_type == BISHOP){
        return BISHOP_VALUE;
    }

    // if the piece is a queen
    else if (piece_type == QUEEN){
        return QUEEN_VALUE;
    }

    // if the piece is a king
    else if (piece_type == KING){
        return KING_VALUE;
    }

    // if the piece is nothing
    return 0;
}


bool Is_Check(int color, Piece*** board, State_Of_Rock_and_Check* State_Of_Rock_and_Check, Move_Log_array* Move_Log){

}


int Is_Check_Mate(int color, Piece*** board, State_Of_Rock_and_Check* State_Of_Rock_and_Check, Move_Log_array* Move_Log){

}


Piece* Get_King(int color, Piece*** board){

}


Piece** Get_Pieces_That_Check_King(int color, Piece*** board, int* number_of_pieces_that_are_checking_king, Move_Log_array* Move_Log, State_Of_Rock_and_Check* state_of_rock_and_check){

}