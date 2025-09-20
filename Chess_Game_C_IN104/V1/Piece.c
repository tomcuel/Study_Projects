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

}


bool Is_Move_Valid(Move* move, Piece* piece, Piece*** board){

}


bool Is_Move_Valid_Pawn(Move* move, Piece* piece, Piece*** board){

}


bool Get_State_Of_Pawn(Piece* piece, Piece*** board){

}


Piece** Get_Pawn_Neighbors(Piece* piece, Piece*** board){

}


bool Is_Move_Valid_Knight(Move* move, Piece* piece, Piece*** board){

}


bool Is_Move_Valid_Bishop(Move* move, Piece* piece, Piece*** board){
    
    // if it's not a diagonal move
    if (abs(move->previous_row - move->destination_row) == abs(move->previous_col - move->destination_col)){
        return false;
    }

    // if the destination is a piece of the same color
    if (board[move->destination_row][move->destination_col]->color == piece->color){
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


bool Is_Move_Valid_Rook(Move* move, Piece* piece, Piece*** board){

}


bool Is_Move_Valid_Queen(Move* move, Piece* piece, Piece*** board){

}


bool Is_Move_Valid_King(Move* move, Piece* piece, Piece*** board){

}


State_Of_Rock_and_Check* Create_State_Of_Rock_and_Check(){

}


void Destroy_State_Of_Rock_and_Check(State_Of_Rock_and_Check* State_Of_Rock_and_Check){

}


bool Is_Rock_Possible(int color /* same as player */, State_Of_Rock_and_Check* State_Of_Rock_and_Check){

}


int Get_Type_Of_Rock(Move* move, Piece*** board){

}


Move* Create_Rook_Move_during_Rock(Piece* piece, Move* move, Piece*** board){

}


Move* Create_King_Move_during_Rock(Piece* piece, Move* move, Piece*** board){

}


void Undo_Rook_during_Rock(Move* move, Piece*** board, State_Of_Rock_and_Check* State_Of_Rock_and_Check, Move_Log_array* Move_Log){

}


bool Will_Capture(Move* move, Piece*** board){

}


Captured_Piece_and_Score* Create_Captured_Piece_and_Score(int max_number_of_pieces){

}


void Destroy_Captured_Piece_and_Score(Captured_Piece_and_Score* captured_piece_and_score, int max_number_of_pieces){

}


void Add_Piece_To_Captured_Pieces(Piece* piece, Captured_Piece_and_Score* captured_piece_and_score){

}


void Update_Score(Piece* piece, Captured_Piece_and_Score* captured_piece_and_score){

}


bool Is_Check(int color, Piece*** board){

}


bool Is_Check_Mate(int color, Piece*** board){

}


Piece** Get_Pieces_That_Check_King(int color, Piece*** board, int* number_of_pieces_that_are_checking_king){

}