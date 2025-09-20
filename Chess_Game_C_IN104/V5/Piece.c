#include "Piece.h"


Tiles_Pawn* Create_Tiles_Pawn(){
    Tiles_Pawn* tiles_pawn = (Tiles_Pawn*)malloc(sizeof(Tiles_Pawn));
    // looking for a malloc error
    if (tiles_pawn == NULL){
        printf("Error: malloc failed in Create_Tiles_Pawn\n");
        return NULL;
    }

    tiles_pawn->color = NO_COLOR;
    tiles_pawn->move_made = Create_Move(0, 0, 0, 0);
    tiles_pawn->has_moved_2_squares = false;

    // return the tiles of the pawn
    return tiles_pawn;
}


void Reset_Tiles_Pawn(Tiles_Pawn* tiles_pawn){
    // if the tiles of the pawn is not NULL, we can reset it
    if (tiles_pawn != NULL){
        tiles_pawn->color = NO_COLOR;
        tiles_pawn->move_made->previous_row = 0;
        tiles_pawn->move_made->previous_col = 0;
        tiles_pawn->move_made->destination_row = 0;
        tiles_pawn->move_made->destination_col = 0;
        tiles_pawn->has_moved_2_squares = false;
    }
}


Tiles_Pawn* Copy_Tiles_Pawn(Tiles_Pawn* tiles_pawn){
    Tiles_Pawn* tiles_pawn_copy = Create_Tiles_Pawn();
    // looking for a malloc error
    if (tiles_pawn_copy == NULL){
        printf("Error: malloc failed in Copy_Tiles_Pawn\n");
        return NULL;
    }

    // copying the tiles of the pawn
    tiles_pawn_copy->color = tiles_pawn->color;
    tiles_pawn_copy->move_made->previous_row = tiles_pawn->move_made->previous_row;
    tiles_pawn_copy->move_made->previous_col = tiles_pawn->move_made->previous_col;
    tiles_pawn_copy->move_made->destination_row = tiles_pawn->move_made->destination_row;
    tiles_pawn_copy->move_made->destination_col = tiles_pawn->move_made->destination_col;
    tiles_pawn_copy->has_moved_2_squares = tiles_pawn->has_moved_2_squares;

    // return the copy of the tiles of the pawn
    return tiles_pawn_copy;
}


void Fill_Tile_Pawn(Move* move, Piece*** board, Tiles_Pawn* tiles_pawn){
   
    // copy the move made by the pawn
    tiles_pawn->move_made->previous_row = move->previous_row;
    tiles_pawn->move_made->previous_col = move->previous_col;
    tiles_pawn->move_made->destination_row = move->destination_row;
    tiles_pawn->move_made->destination_col = move->destination_col;
   
    // if the move is a pawn move
    if (board[move->previous_row][move->previous_col]->type == PAWN){
        
        // if the pawn is white
        if (board[move->previous_row][move->previous_col]->color == WHITE){
            
            tiles_pawn->color = WHITE;
            // if the pawn is moving up two squares
            if (move->previous_row - move->destination_row == 2){
                tiles_pawn->has_moved_2_squares = true;
            }
            else {
                tiles_pawn->has_moved_2_squares = false;
            }
        }

        // if the pawn is black
        else if (board[move->previous_row][move->previous_col]->color == BLACK){
            
            tiles_pawn->color = BLACK;
            // if the pawn is moving down two squares
            if (move->destination_row - move->previous_row == 2){
                tiles_pawn->has_moved_2_squares = true;
            }
            else {
                tiles_pawn->has_moved_2_squares = false;
            }
        }

    }

    else if (board[move->previous_row][move->previous_col]->type != PAWN){
        tiles_pawn->has_moved_2_squares = false;
    }

}


void Destroy_Tiles_Pawn(Tiles_Pawn* tiles_pawn){
    // if the tiles of the pawn is not NULL, we can free it
    if (tiles_pawn != NULL){
        free(tiles_pawn);
    }
}


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


bool Is_Move_Valid(Move* move, Piece*** board, State_Of_Rock_and_Check* State_Of_Rock_and_Check, Tiles_Pawn* Pawn_Move_State){

    // if the move is making no move, since it's an empty position at the beggining
    if (move->previous_row == move->destination_row && move->previous_col == move->destination_col){
        return false;
    }

    // if the move is out of the board
    if (move->previous_row < 0 || move->previous_row > BOARD_SIZE-1 || move->previous_col < 0 || move->previous_col > BOARD_SIZE-1 || move->destination_row < 0 || move->destination_row > BOARD_SIZE-1 || move->destination_col < 0 || move->destination_col > BOARD_SIZE-1){
        return false;
    }

    // if this place on the board is empty
    if (board[move->previous_row][move->previous_col]->type == NOTHING){
        return false;
    }

    else if (board[move->previous_row][move->previous_col]->type == PAWN){
        return Is_Move_Valid_Pawn(move, board, Pawn_Move_State);
    }

    else if (board[move->previous_row][move->previous_col]->type == KNIGHT){
        return Is_Move_Valid_Knight(move, board);
    }

    else if (board[move->previous_row][move->previous_col]->type == BISHOP){
        return Is_Move_Valid_Bishop(move, board);
    }

    else if (board[move->previous_row][move->previous_col]->type == ROOK){
        return Is_Move_Valid_Rook(move, board);
    }

    else if (board[move->previous_row][move->previous_col]->type == QUEEN){
        return Is_Move_Valid_Queen(move, board);
    }

    else if (board[move->previous_row][move->previous_col]->type == KING){
        return Is_Move_Valid_King(move, board, State_Of_Rock_and_Check);
    }

    return false;

}


bool Is_Move_Valid_Pawn(Move* move, Piece*** board, Tiles_Pawn* Pawn_Move_State){

    // if the destination is a piece of the same color
    if (board[move->destination_row][move->destination_col]->color == board[move->previous_row][move->previous_col]->color){
        return false;
    }

    // depending on the color of the pawn we want to move, different cases are to be considered

    // if it's a white pawn
    if (board[move->previous_row][move->previous_col]->color == WHITE){
        // if the pawn if moving forward (up for a white pawn)
        // if it's one case 
        if (move->previous_col == move->destination_col && move->previous_row-1 == move->destination_row){
            // if the destination is empty
            if (board[move->destination_row][move->destination_col]->type == NOTHING){
                return true;
            }
        }
        // if it want to go up two cases (It need to be one its starting line) and the destination need to be empty, as well as the cases bewteen the pawn and the destination
        else if (move->previous_col == move->destination_col && move->previous_row-2 == move->destination_row && move->previous_row == 6){
            if (board[move->destination_row][move->destination_col]->type == NOTHING && board[move->previous_row-1][move->previous_col]->type == NOTHING){
                return true;
            }
        }

        // now we need to consider the diagonal moves
        // if the pawn is moving to the right (up and right)
        if (move->previous_row-1 == move->destination_row && move->previous_col+1 == move->destination_col){
            // if the destination is not empty and the piece is of the opposite color
            if (board[move->destination_row][move->destination_col]->type != NOTHING && board[move->destination_row][move->destination_col]->color != board[move->previous_row][move->previous_col]->color){
                return true;
            }
        }
        // if the pawn is moving to the left (up and left)
        if (move->previous_row-1 == move->destination_row && move->previous_col-1 == move->destination_col){
            // if the destination is not empty and the piece is of the opposite color
            if (board[move->destination_row][move->destination_col]->type != NOTHING && board[move->destination_row][move->destination_col]->color != board[move->previous_row][move->previous_col]->color){
                return true;
            }
        }
    }

    // if it's a black pawn 
    if (board[move->previous_row][move->previous_col]->color == BLACK){
        // if the pawn if moving forward (down for a black pawn)
        // if it's one case
        if (move->previous_col == move->destination_col && move->previous_row+1 == move->destination_row){
            // if the destination is empty
            if (board[move->destination_row][move->destination_col]->type == NOTHING){
                return true;
            }
        }
        // if it want to go down two cases (It need to be one its starting line) and the destination need to be empty, as well as the cases bewteen the pawn and the destination
        else if (move->previous_col == move->destination_col && move->previous_row+2 == move->destination_row && move->previous_row == 1){
            if (board[move->destination_row][move->destination_col]->type == NOTHING && board[move->previous_row+1][move->previous_col]->type == NOTHING){
                return true;
            }
        }

        // now we need to consider the diagonal moves
        // if the pawn is moving to the right (down and right)
        if (move->previous_row+1 == move->destination_row && move->previous_col+1 == move->destination_col){
            // if the destination is not empty and the piece is of the opposite color
            if (board[move->destination_row][move->destination_col]->type != NOTHING && board[move->destination_row][move->destination_col]->color != board[move->previous_row][move->previous_col]->color){
                return true;
            }
        }
        // if the pawn is moving to the left (down and left)
        if (move->previous_row+1 == move->destination_row && move->previous_col-1 == move->destination_col){
            // if the destination is not empty and the piece is of the opposite color
            if (board[move->destination_row][move->destination_col]->type != NOTHING && board[move->destination_row][move->destination_col]->color != board[move->previous_row][move->previous_col]->color){
                return true;
            }
        }
    }

    // en passant
    if (Is_En_Passant_Possible(move, board, Pawn_Move_State)){
        return true;
    }


    // return false by default
    return false;
}


bool Is_En_Passant_Possible(Move* move, Piece*** board, Tiles_Pawn* Pawn_Move_State){

    // if the pawn is white, it also need to be before the move is made on the 4th row
    if (board[move->previous_row][move->previous_col]->color == WHITE && move->previous_row == 3){
        
        // if the pawn is moving to the right (up and right)
        if (move->destination_row == move->previous_row-1 && move->destination_col == move->previous_col+1){
            // if the destination is empty and the piece on the right of the previous position is a black pawn that just moved two cases
            if (board[move->destination_row][move->destination_col]->type == NOTHING && board[move->previous_row][move->previous_col+1]->type == PAWN && board[move->previous_row][move->previous_col+1]->color == BLACK && Pawn_Move_State->has_moved_2_squares == true && Pawn_Move_State->color == BLACK){
                return true;
            }
        }

        // if the pawn is moving to the left (up and left)
        if (move->destination_row == move->previous_row-1 && move->destination_col == move->previous_col-1){
            // if the destination is empty and the piece on the left of the previous position is a black pawn that just moved two cases
            if (board[move->destination_row][move->destination_col]->type == NOTHING && board[move->previous_row][move->previous_col-1]->type == PAWN && board[move->previous_row][move->previous_col-1]->color == BLACK && Pawn_Move_State->has_moved_2_squares == true && Pawn_Move_State->color == BLACK){
                return true;
            }
        }

    }

    // if the pawn is black, it also need to be before the move is made on the 5th row
    if (board[move->previous_row][move->previous_col]->color == BLACK && move->previous_row == 4){
        
        // if the pawn is moving to the right (down and right)
        if (move->destination_row == move->previous_row+1 && move->destination_col == move->previous_col+1){
            // if the destination is empty and the piece on the right of the previous position is a white pawn that just moved two cases
            if (board[move->destination_row][move->destination_col]->type == NOTHING && board[move->previous_row][move->previous_col+1]->type == PAWN && board[move->previous_row][move->previous_col+1]->color == WHITE && Pawn_Move_State->has_moved_2_squares == true && Pawn_Move_State->color == WHITE){
                return true;
            }
        }
    
        // if the pawn is moving to the left (down and left)
        if (move->destination_row == move->previous_row+1 && move->destination_col == move->previous_col-1){
            // if the destination is empty and the piece on the left of the previous position is a white pawn that just moved two cases
            if (board[move->destination_row][move->destination_col]->type == NOTHING && board[move->previous_row][move->previous_col-1]->type == PAWN && board[move->previous_row][move->previous_col-1]->color == WHITE && Pawn_Move_State->has_moved_2_squares == true && Pawn_Move_State->color == WHITE){
                return true;
            }
        }
    
    }

    // default
    return false;
}


bool Is_Pawn_Promotion_Possible(Move* move, Piece*** board){

    // if the pawn is white and it's on the 1th row
    if (board[move->previous_row][move->previous_col]->color == WHITE && board[move->previous_row][move->previous_col]->type == PAWN && move->destination_row == 0){
        return true;
    }

    // if the pawn is black and it's on the 8st row
    if (board[move->previous_row][move->previous_col]->color == BLACK && board[move->previous_row][move->previous_col]->type == PAWN && move->destination_row == 7){
        return true;
    }

    // default
    return false;
}


bool Is_Move_Valid_Knight(Move* move, Piece*** board){

    // if the destination is a piece of the same color as the piece we want to move
    if (board[move->destination_row][move->destination_col]->color == board[move->previous_row][move->previous_col]->color){
        return false;
    }
    
    // Calculate differences in row and column positions
    int row_diff = abs(move->destination_row - move->previous_row);
    int col_diff = abs(move->destination_col - move->previous_col);

    // Check if the move forms an "L" shape (2 squares in one direction and 1 square in another)
    if ((row_diff == 2 && col_diff == 1) || (row_diff == 1 && col_diff == 2)){
        // Check if the destination square is empty or contains a piece of a different color
        if (board[move->destination_row][move->destination_col]->type == NOTHING || board[move->destination_row][move->destination_col]->color != board[move->previous_row][move->previous_col]->color){
            return true;
        }
    }

    return false;
}


bool Is_Move_Valid_Bishop(Move* move, Piece*** board){
    
    // if it's a not a diagonal move
    if (abs(move->previous_row - move->destination_row) != abs(move->previous_col - move->destination_col)){
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

    // default 
    return false;
    
}


bool Is_Move_Valid_Rook(Move* move, Piece*** board){

    // check if the move is not horizontal or vertical
    if (move->previous_row != move->destination_row && move->previous_col != move->destination_col){
        return false;
    }

    // check if the destination is a piece of the same color
    if (board[move->destination_row][move->destination_col]->color == board[move->previous_row][move->previous_col]->color){
        return false;
    }

    // move to the right horizontally
    if (move->previous_row == move->destination_row && move->previous_col < move->destination_col){
        for (int j = move->previous_col + 1; j < move->destination_col; j++){
            // if the rook found a piece in the line to the right (it can be of any color)
            if (board[move->previous_row][j]->type != NOTHING){
                return false;
            }
        }
        return true;
    }


    // move to the left horizontally
    else if (move->previous_row == move->destination_row && move->previous_col > move->destination_col){
        for (int j = move->previous_col - 1; j > move->destination_col; j--){
            // if the rook found a piece in the line to the left (it can be of any color)
            if (board[move->previous_row][j]->type != NOTHING){
                return false;
            }
        }
        return true;
    }

    // move vertically down
    else if (move->previous_row < move->destination_row && move->previous_col == move->destination_col){
        for (int i = move->previous_row + 1; i < move->destination_row; i++){
            // if the rook found a piece in the line down (it can be of any color)
            if (board[i][move->previous_col]->type != NOTHING){
                return false;
            }
        }
        return true;
    }

    // move vertically up
    else if (move->previous_row > move->destination_row && move->previous_col == move->destination_col){
        for (int i = move->previous_row - 1; i > move->destination_row; i--){
            // if the rook found a piece in the line up (it can be of any color)
            if (board[i][move->previous_col]->type != NOTHING){
                return false;
            }
        }
        return true;
    }
    
    // if the move is not horizontal or vertical
    return false; 
}


bool Is_Move_Valid_Queen(Move* move, Piece*** board){

    // Check if the destination is occupied by a piece of the same color
    if (board[move->destination_row][move->destination_col]->color == board[move->previous_row][move->previous_col]->color){
        return false;
    }

    // a queen is both a rook and a bishop 
    // so we can use the functions we already implemented for the rook and the bishop
    if (Is_Move_Valid_Rook(move, board) || Is_Move_Valid_Bishop(move, board)){
        return true;
    }
    else {
        return false;
    }

    // default 
    return false;

}


bool Is_Move_Valid_King(Move* move, Piece*** board, State_Of_Rock_and_Check* State_Of_Rock_and_Check){

    // the king is a bit of a queen but restricted to one square (both a rock and a bishop restricted to one square)
    if (abs(move->previous_row - move->destination_row) <= 1 && abs(move->previous_col - move->destination_col) <= 1){
        // we don't want the move to go on a place occupied by a piece of the same color
        if (board[move->destination_row][move->destination_col]->type != NOTHING && board[move->destination_row][move->destination_col]->color == board[move->previous_row][move->previous_col]->color){
            return false;
        }
        // otherwise it needs to look like a queen move, just here it's restricted to one square (we might have not needed it since we already checked for the distances)
        if (Is_Move_Valid_Rook(move, board) || Is_Move_Valid_Bishop(move, board)){
            return true;
        }
    }


    // the rock move of the king : 
    if (Is_Rock_Possible(move, State_Of_Rock_and_Check, board) != NO_ROCK){
        return true;
    }
            
    // if the move is not horizontal, vertical or diagonal and not a rock
    return false; 
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


State_Of_Rock_and_Check* Copy_State_Of_Rock_and_Check(State_Of_Rock_and_Check* state_of_rock_and_check){
    
    // if the state of the rock and the check is NULL, we can't copy it
    if (state_of_rock_and_check == NULL){
        return NULL;
    }

    State_Of_Rock_and_Check* new_state_of_rock_and_check = Create_State_Of_Rock_and_Check();
    // looking for a malloc error
    if (new_state_of_rock_and_check == NULL){
        printf("Error: malloc failed in Copy_State_Of_Rock_and_Check\n");
        return NULL;
    }

    // setting the new state of the rock and the check to the one given in parameters
    new_state_of_rock_and_check->white_rock_done = state_of_rock_and_check->white_rock_done;
    new_state_of_rock_and_check->white_king_moved = state_of_rock_and_check->white_king_moved;
    new_state_of_rock_and_check->white_left_rook_moved = state_of_rock_and_check->white_left_rook_moved;
    new_state_of_rock_and_check->white_right_rook_moved = state_of_rock_and_check->white_right_rook_moved;
    new_state_of_rock_and_check->is_white_king_checked = state_of_rock_and_check->is_white_king_checked;

    new_state_of_rock_and_check->black_rock_done = state_of_rock_and_check->black_rock_done;
    new_state_of_rock_and_check->black_king_moved = state_of_rock_and_check->black_king_moved;
    new_state_of_rock_and_check->black_left_rook_moved = state_of_rock_and_check->black_left_rook_moved;
    new_state_of_rock_and_check->black_right_rook_moved = state_of_rock_and_check->black_right_rook_moved;
    new_state_of_rock_and_check->is_black_king_checked = state_of_rock_and_check->is_black_king_checked;

    // return the new state of the rock and the check
    return new_state_of_rock_and_check;
}


void Destroy_State_Of_Rock_and_Check(State_Of_Rock_and_Check* State_Of_Rock_and_Check){
    // if the state of the rock and the check is not NULL, we can free it
    if (State_Of_Rock_and_Check != NULL){
        free(State_Of_Rock_and_Check);
    }
}


int Is_Rock_Possible(Move* move, State_Of_Rock_and_Check* State_Of_Rock_and_Check, Piece*** board){

    // if the king is white and on its start position and is not checked, and the rock is not done
    if (board[move->previous_row][move->previous_col]->type == KING && board[move->previous_row][move->previous_col]->color == WHITE 
    && State_Of_Rock_and_Check->is_white_king_checked == false && State_Of_Rock_and_Check->white_king_moved == false && State_Of_Rock_and_Check->white_rock_done == false){
           
        // if the king is moving to the left, for a possible long rock, the left rook needs to be on its start position and not moved
        if (move->previous_col == 4 && move->destination_col == 0 && State_Of_Rock_and_Check->white_left_rook_moved == false){
            // the case bewteen the king and the rook needs to be empty of pieces 
            for (int j = 1; j < 4; j++){
                if (board[7][j]->type != NOTHING || Is_Case_threatened(WHITE, 7, j, board) == true){
                    return NO_ROCK;
                }
            }
            // the case on xhich the king is travelling needs not to be threaten by an opponent piece
            // to be implemented
            return LONG_ROCK;
        }

        // if the king is moving to the right, the right rook needs to be on its start position and not moved
        else if (move->destination_col == 7 && move->previous_col == 4 && State_Of_Rock_and_Check->white_right_rook_moved == false){
                
            // the case bewteen the king and the rook needs to be empty of pieces
            for (int j = 5; j < 7; j++){
                if (board[7][j]->type != NOTHING || Is_Case_threatened(WHITE, 7, j, board) == true){
                    return NO_ROCK;
                }
            }
            // the case on xhich the king is travelling needs not to be threaten by an opponent piece
            // to be implemented
            return SHORT_ROCK;
        }

    }

    // if the king is black and on its start position and is not checked, and the rock is not done
    if (board[move->previous_row][move->previous_col]->type == KING && board[move->previous_row][move->previous_col]->color == BLACK
    && State_Of_Rock_and_Check->is_black_king_checked == false && State_Of_Rock_and_Check->black_king_moved == false && State_Of_Rock_and_Check->black_rock_done == false){
        
        // if the king is moving to the left, the left rook needs to be on its start position and not moved
        if (move->previous_col == 4 && move->destination_col == 0 && State_Of_Rock_and_Check->black_left_rook_moved == false){
            // the case bewteen the king and the rook needs to be empty of pieces
            for (int j = 1; j < 4; j++){
                if (board[0][j]->type != NOTHING || Is_Case_threatened(BLACK, 0, j, board) == true){
                    return NO_ROCK;
                }
            }
            // the case on xhich the king is travelling needs not to be threaten by an opponent piece
            // to be implemented
            return LONG_ROCK;
        }

        // if the king is moving to the right, the right rook needs to be on its start position and not moved
        else if (move->destination_col == 7 && move->previous_col == 4 && State_Of_Rock_and_Check->black_right_rook_moved == false){
            // the case bewteen the king and the rook needs to be empty of pieces
            for (int j = 5; j < 7; j++){
                if (board[0][j]->type != NOTHING || Is_Case_threatened(BLACK, 0, j, board) == true){
                    return NO_ROCK;
                }
            }
            // the case on xhich the king is travelling needs not to be threaten by an opponent piece
            // to be implemented
            return SHORT_ROCK;
        }

    }
    
    // default case for every other caseq
    return NO_ROCK;
}


Move* Create_Rook_Move_during_Rock(Move* move, Piece*** board, State_Of_Rock_and_Check* State_Of_Rock_and_Check){

    // check if the rock is possible and get what type of rock it is
    int type_of_rock = Is_Rock_Possible(move, State_Of_Rock_and_Check, board);

    // if the rock is not possible
    if (type_of_rock == NO_ROCK){
        return NULL;
    }

    // if the rock is possible
    else if (type_of_rock == LONG_ROCK){
        // if it's a white rock
        if (board[move->previous_row][move->previous_col]->color == WHITE){
            // the rook is on the 8th row and the 1st column
            return Create_Move(7, 0, 7, 3);
        }
        // if it's a black rock
        else if (board[move->previous_row][move->previous_col]->color == BLACK){
            // the rook is on the 1st row and the 1st column
            return Create_Move(0, 0, 0, 3);
        }
    }

    // if the rock is possible
    else if (type_of_rock == SHORT_ROCK){
        // if it's a white rock
        if (board[move->previous_row][move->previous_col]->color == WHITE){
            // the rook is on the 8th row and the 8th column
            return Create_Move(7, 7, 7, 5);
        }
        // if it's a black rock
        else if (board[move->previous_row][move->previous_col]->color == BLACK){
            // the rook is on the 1st row and the 8th column
            return Create_Move(0, 7, 0, 5);
        }
    }

    // default
    return NULL;
}


Move* Create_King_Move_during_Rock(Move* move, Piece*** board, State_Of_Rock_and_Check* State_Of_Rock_and_Check){

    // check if the rock is possible and get what type of rock it is
    int type_of_rock = Is_Rock_Possible(move, State_Of_Rock_and_Check, board);

    // if the rock is not possible
    if (type_of_rock == NO_ROCK){
        return NULL;
    }

    // if the rock is possible
    else if (type_of_rock == LONG_ROCK){
        // if it's a white rock
        if (board[move->previous_row][move->previous_col]->color == WHITE){
            // the king is on the 8th row and the 4th column
            return Create_Move(7, 4, 7, 2);
        }
        // if it's a black rock
        else if (board[move->previous_row][move->previous_col]->color == BLACK){
            // the king is on the 1st row and the 4th column
            return Create_Move(0, 4, 0, 2);
        }
    }

    // if the rock is possible
    else if (type_of_rock == SHORT_ROCK){
        // if it's a white rock
        if (board[move->previous_row][move->previous_col]->color == WHITE){
            // the king is on the 8th row and the 4th column
            return Create_Move(7, 4, 7, 6);
        }
        // if it's a black rock
        else if (board[move->previous_row][move->previous_col]->color == BLACK){
            // the king is on the 1st row and the 4th column
            return Create_Move(0, 4, 0, 6);
        }
    }

    // default
    return NULL;

}


bool Will_Capture(Move* move, Piece*** board){
    // if the destination is a piece of the opposite color
    if (board[move->destination_row][move->destination_col]->color == WHITE && board[move->previous_row][move->previous_col]->color == BLACK){
        return true;
    }
    // if the destination is a piece of the opposite color
    else if (board[move->destination_row][move->destination_col]->color == BLACK && board[move->previous_row][move->previous_col]->color == WHITE){
        return true;
    }

    // otherwise
    return false;
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
    for (int i = 0; i < max_number_of_pieces; i++){
        captured_piece_and_score->white_pieces_captured[i] =  Create_Piece();
        // looking for a malloc error
        if (captured_piece_and_score->white_pieces_captured[i] == NULL){
            printf("Error: malloc failed in Create_Captured_Piece_and_Score\n");
            return NULL;
        }
    }

    // allocating the memory for the array of black pieces captured
    captured_piece_and_score->black_pieces_captured = (Piece**)malloc(max_number_of_pieces * sizeof(Piece*));
    // looking for a malloc error
    if (captured_piece_and_score->black_pieces_captured == NULL){
        printf("Error: malloc failed in Create_Captured_Piece_and_Score\n");
        return NULL;
    }
    for (int i = 0; i < max_number_of_pieces; i++){
        captured_piece_and_score->black_pieces_captured[i] =  Create_Piece();
        // looking for a malloc error
        if (captured_piece_and_score->black_pieces_captured[i] == NULL){
            printf("Error: malloc failed in Create_Captured_Piece_and_Score\n");
            return NULL;
        }
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
    captured_piece_and_score->player_that_is_winning = WHITE;

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


Captured_Piece_and_Score* Copy_Captured_Piece_and_Score(Captured_Piece_and_Score* captured_piece_and_score){
    // if the captured piece and score is not NULL, we can copy it
    if (captured_piece_and_score != NULL){
        Captured_Piece_and_Score* captured_piece_and_score_copy = Create_Captured_Piece_and_Score(captured_piece_and_score->max_number_of_pieces);
        // looking for a malloc error
        if (captured_piece_and_score_copy == NULL){
            printf("Error: malloc failed in Copy_Captured_Piece_and_Score\n");
            return NULL;
        }

        // copying the number of white pieces captured
        captured_piece_and_score_copy->number_of_white_pieces_captured = captured_piece_and_score->number_of_white_pieces_captured;
        // copying the number of black pieces captured
        captured_piece_and_score_copy->number_of_black_pieces_captured = captured_piece_and_score->number_of_black_pieces_captured;
        // copying the max number of pieces
        captured_piece_and_score_copy->max_number_of_pieces = captured_piece_and_score->max_number_of_pieces;
        // copying the score
        captured_piece_and_score_copy->score = captured_piece_and_score->score;
        // copying the player that is winning
        captured_piece_and_score_copy->player_that_is_winning = captured_piece_and_score->player_that_is_winning;

        // copying the white pieces captured
        for (int i = 0; i < captured_piece_and_score->max_number_of_pieces; i++){
            // copying the white piece captured
            captured_piece_and_score_copy->white_pieces_captured[i]->row = captured_piece_and_score->white_pieces_captured[i]->row;
            captured_piece_and_score_copy->white_pieces_captured[i]->col = captured_piece_and_score->white_pieces_captured[i]->col;
            captured_piece_and_score_copy->white_pieces_captured[i]->type = captured_piece_and_score->white_pieces_captured[i]->type;
            captured_piece_and_score_copy->white_pieces_captured[i]->color = captured_piece_and_score->white_pieces_captured[i]->color;
            captured_piece_and_score_copy->white_pieces_captured[i]->is_alive = captured_piece_and_score->white_pieces_captured[i]->is_alive;
            captured_piece_and_score_copy->white_pieces_captured[i]->value = captured_piece_and_score->white_pieces_captured[i]->value;
            captured_piece_and_score_copy->white_pieces_captured[i]->is_checked = captured_piece_and_score->white_pieces_captured[i]->is_checked;
            captured_piece_and_score_copy->white_pieces_captured[i]->is_on_his_start_position = captured_piece_and_score->white_pieces_captured[i]->is_on_his_start_position;
        }

        // copying the black pieces captured
        for (int i = 0; i < captured_piece_and_score->max_number_of_pieces; i++){
            // copying the black piece captured
            captured_piece_and_score_copy->black_pieces_captured[i]->row = captured_piece_and_score->black_pieces_captured[i]->row;
            captured_piece_and_score_copy->black_pieces_captured[i]->col = captured_piece_and_score->black_pieces_captured[i]->col;
            captured_piece_and_score_copy->black_pieces_captured[i]->type = captured_piece_and_score->black_pieces_captured[i]->type;
            captured_piece_and_score_copy->black_pieces_captured[i]->color = captured_piece_and_score->black_pieces_captured[i]->color;
            captured_piece_and_score_copy->black_pieces_captured[i]->is_alive = captured_piece_and_score->black_pieces_captured[i]->is_alive;
            captured_piece_and_score_copy->black_pieces_captured[i]->value = captured_piece_and_score->black_pieces_captured[i]->value;
            captured_piece_and_score_copy->black_pieces_captured[i]->is_checked = captured_piece_and_score->black_pieces_captured[i]->is_checked;
            captured_piece_and_score_copy->black_pieces_captured[i]->is_on_his_start_position = captured_piece_and_score->black_pieces_captured[i]->is_on_his_start_position;
        }

        // return the copied captured piece and score
        return captured_piece_and_score_copy;
    }

    // default
    return NULL;
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


bool Is_Case_threatened(int color, int row, int col, Piece*** board){

    // looking if a knight if threatening the king
    // looking for the 8 possible moves of the knight
    if (row - 2 >= 0 && col - 1 >= 0 && board[row - 2][col - 1]->type == KNIGHT && board[row - 2][col - 1]->color != color){
        return true;
    }
    if (row - 2 >= 0 && col + 1 < 8 && board[row - 2][col + 1]->type == KNIGHT && board[row - 2][col + 1]->color != color){
        return true;
    }
    if (row - 1 >= 0 && col - 2 >= 0 && board[row - 1][col - 2]->type == KNIGHT && board[row - 1][col - 2]->color != color){
        return true;
    }
    if (row - 1 >= 0 && col + 2 < 8 && board[row - 1][col + 2]->type == KNIGHT && board[row - 1][col + 2]->color != color){
        return true;
    }
    if (row + 1 < 8 && col - 2 >= 0 && board[row + 1][col - 2]->type == KNIGHT && board[row + 1][col - 2]->color != color){
        return true;
    }
    if (row + 1 < 8 && col + 2 < 8 && board[row + 1][col + 2]->type == KNIGHT && board[row + 1][col + 2]->color != color){
        return true;
    }
    if (row + 2 < 8 && col - 1 >= 0 && board[row + 2][col - 1]->type == KNIGHT && board[row + 2][col - 1]->color != color){
        return true;
    }
    if (row + 2 < 8 && col + 1 < 8 && board[row + 2][col + 1]->type == KNIGHT && board[row + 2][col + 1]->color != color){
        return true;
    }

    // looking if a pawn if threatening the king
    // if the king is white
    if (color == WHITE){
        // if the king is not on the first row
        if (row > 0){
            // if the king is not on the first column
            if (col > 0){
                // if there is a black pawn on the left and up
                if (board[row - 1][col - 1]->type == PAWN && board[row - 1][col - 1]->color == BLACK){
                    return true;
                }
            }
            // if the king is not on the last column
            if (col < 7){
                // if there is a black pawn on the right and up
                if (board[row - 1][col + 1]->type == PAWN && board[row - 1][col + 1]->color == BLACK){
                    return true;
                }
            }
        }
    }
    // if the king is black
    if (color == BLACK){
        // if the king is not on the last row
        if (row < 7){
            // if the king is not on the first column
            if (col > 0){
                // if there is a white pawn on the left and down
                if (board[row + 1][col - 1]->type == PAWN && board[row + 1][col - 1]->color == WHITE){
                    return true;
                }
            }
            // if the king is not on the last column
            if (col < 7){
                // if there is a white pawn on the right and down
                if (board[row + 1][col + 1]->type == PAWN && board[row + 1][col + 1]->color == WHITE){
                    return true;
                }
            }
        }
    }

    // the queen will be done with both the rook and the bishop

    // looking if a rook or a queen is threatening the king
    // looking for the 4 possible directions of the rook and the queen 
    // looking to the right
    if (col < 7){
        // if there is a king 
        if (board[row][col+1]->type == KING && board[row][col+1]->color != color){
            return true;
        }
        for (int j = col + 1; j < 8; j++){
            // if we found a piece in the line to the right
            if (board[row][j]->type != NOTHING){
                // if the piece is a rook or a queen of the opposite color
                if ((board[row][j]->type == ROOK || board[row][j]->type == QUEEN) && board[row][j]->color != color){
                    return true;
                }
                // if the piece is not a rook or a queen
                else {
                    break;
                }
            }
        }
    }
    // looking to the left
    if (col > 0){
        // if there is a king 
        if (board[row][col-1]->type == KING && board[row][col-1]->color != color){
            return true;
        }
        for (int j = col - 1; j >= 0; j--){
            // if we found a piece in the line to the left
            if (board[row][j]->type != NOTHING){
                // if the piece is a rook or a queen of the opposite color
                if ((board[row][j]->type == ROOK || board[row][j]->type == QUEEN) && board[row][j]->color != color){
                    return true;
                }
                // if the piece is not a rook or a queen
                else {
                    break;
                }
            }
        }
    }
    // looking up
    if (row > 0){
        // if there is a king 
        if (board[row-1][col]->type == KING && board[row-1][col]->color != color){
            return true;
        }
        for (int i = row - 1; i >= 0; i--){
            // if we found a piece in the line up
            if (board[i][col]->type != NOTHING){
                // if the piece is a rook or a queen of the opposite color
                if ((board[i][col]->type == ROOK || board[i][col]->type == QUEEN) && board[i][col]->color != color){
                    return true;
                }
                // if the piece is not a rook or a queen
                else {
                    break;
                }
            }
        }
    }
    // looking down
    if (row < 7){
        // if there is a king 
        if (board[row+1][col]->type == KING && board[row+1][col]->color != color){
            return true;
        }
        for (int i = row + 1; i < 8; i++){
            // if we found a piece in the line down
            if (board[i][col]->type != NOTHING){
                // if the piece is a rook or a queen of the opposite color
                if ((board[i][col]->type == ROOK || board[i][col]->type == QUEEN) && board[i][col]->color != color){
                    return true;
                }
                // if the piece is not a rook or a queen
                else {
                    break;
                }
            }
        }
    }

    // looking if a bishop or a queen is threatening the king
    // looking for the 4 possible directions of the bishop and the queen
    // looking to the right and down
    if (row < 7 && col < 7){
        // if there is a king 
        if (board[row+1][col+1]->type == KING && board[row+1][col+1]->color != color){
            return true;
        }
        for (int i = row + 1, j = col + 1; i < 8 && j < 8; i++, j++){
            // if we found a piece in the diagonal to the right and down
            if (board[i][j]->type != NOTHING){
                // if the piece is a bishop or a queen of the opposite color
                if ((board[i][j]->type == BISHOP || board[i][j]->type == QUEEN) && board[i][j]->color != color){
                    return true;
                }
                // if the piece is not a bishop or a queen
                else {
                    break;
                }
            }
        }
    }
    // looking to the left and down
    if (row < 7 && col > 0){
        // if there is a king 
        if (board[row+1][col-1]->type == KING && board[row+1][col-1]->color != color){
            return true;
        }
        for (int i = row + 1, j = col - 1; i < 8 && j >= 0; i++, j--){
            // if we found a piece in the diagonal to the left and down
            if (board[i][j]->type != NOTHING){
                // if the piece is a bishop or a queen of the opposite color
                if ((board[i][j]->type == BISHOP || board[i][j]->type == QUEEN) && board[i][j]->color != color){
                    return true;
                }
                // if the piece is not a bishop or a queen
                else {
                    break;
                }
            }
        }
    }
    // looking to the right and up
    if (row > 0 && col < 7){
        // if there is a king 
        if (board[row-1][col+1]->type == KING && board[row-1][col+1]->color != color){
            return true;
        }
        for (int i = row - 1, j = col + 1; i >= 0 && j < 8; i--, j++){
            // if we found a piece in the diagonal to the right and up
            if (board[i][j]->type != NOTHING){
                // if the piece is a bishop or a queen of the opposite color
                if ((board[i][j]->type == BISHOP || board[i][j]->type == QUEEN) && board[i][j]->color != color){
                    return true;
                }
                // if the piece is not a bishop or a queen
                else {
                    break;
                }
            }
        }
    }
    // looking to the left and up
    if (row > 0 && col > 0){
        // if there is a king 
        if (board[row-1][col-1]->type == KING && board[row-1][col-1]->color != color){
            return true;
        }
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--){
            // if we found a piece in the diagonal to the left and up
            if (board[i][j]->type != NOTHING){
                // if the piece is a bishop or a queen of the opposite color
                if ((board[i][j]->type == BISHOP || board[i][j]->type == QUEEN) && board[i][j]->color != color){
                    return true;
                }
                // if the piece is not a bishop or a queen
                else {
                    break;
                }
            }
        }
    }
    
    // default
    return false;
}


bool Is_Check(int color, Piece*** board){

    // Finding the piece corresponding to the king of the given color 
    Piece* king = Get_King(color, board);
    
    // looking if a knight if threatening the king
    // looking for the 8 possible moves of the knight
    if (king->row - 2 >= 0 && king->col - 1 >= 0 && board[king->row - 2][king->col - 1]->type == KNIGHT && board[king->row - 2][king->col - 1]->color != color){
        return true;
    }
    if (king->row - 2 >= 0 && king->col + 1 < 8 && board[king->row - 2][king->col + 1]->type == KNIGHT && board[king->row - 2][king->col + 1]->color != color){
        return true;
    }
    if (king->row - 1 >= 0 && king->col - 2 >= 0 && board[king->row - 1][king->col - 2]->type == KNIGHT && board[king->row - 1][king->col - 2]->color != color){
        return true;
    }
    if (king->row - 1 >= 0 && king->col + 2 < 8 && board[king->row - 1][king->col + 2]->type == KNIGHT && board[king->row - 1][king->col + 2]->color != color){
        return true;
    }
    if (king->row + 1 < 8 && king->col - 2 >= 0 && board[king->row + 1][king->col - 2]->type == KNIGHT && board[king->row + 1][king->col - 2]->color != color){
        return true;
    }
    if (king->row + 1 < 8 && king->col + 2 < 8 && board[king->row + 1][king->col + 2]->type == KNIGHT && board[king->row + 1][king->col + 2]->color != color){
        return true;
    }
    if (king->row + 2 < 8 && king->col - 1 >= 0 && board[king->row + 2][king->col - 1]->type == KNIGHT && board[king->row + 2][king->col - 1]->color != color){
        return true;
    }
    if (king->row + 2 < 8 && king->col + 1 < 8 && board[king->row + 2][king->col + 1]->type == KNIGHT && board[king->row + 2][king->col + 1]->color != color){
        return true;
    }

    // looking if a pawn if threatening the king
    // if the king is white
    if (color == WHITE){
        // if the king is not on the first row
        if (king->row > 0){
            // if the king is not on the first column
            if (king->col > 0){
                // if there is a black pawn on the left and up
                if (board[king->row - 1][king->col - 1]->type == PAWN && board[king->row - 1][king->col - 1]->color == BLACK){
                    return true;
                }
            }
            // if the king is not on the last column
            if (king->col < 7){
                // if there is a black pawn on the right and up
                if (board[king->row - 1][king->col + 1]->type == PAWN && board[king->row - 1][king->col + 1]->color == BLACK){
                    return true;
                }
            }
        }
    }
    // if the king is black
    if (color == BLACK){
        // if the king is not on the last row
        if (king->row < 7){
            // if the king is not on the first column
            if (king->col > 0){
                // if there is a white pawn on the left and down
                if (board[king->row + 1][king->col - 1]->type == PAWN && board[king->row + 1][king->col - 1]->color == WHITE){
                    return true;
                }
            }
            // if the king is not on the last column
            if (king->col < 7){
                // if there is a white pawn on the right and down
                if (board[king->row + 1][king->col + 1]->type == PAWN && board[king->row + 1][king->col + 1]->color == WHITE){
                    return true;
                }
            }
        }
    }

    // the queen will be done with both the rook and the bishop

    // looking if a rook or a queen if threatening the king
    // looking for the 4 possible directions of the rook and the queen 
    // looking to the right
    if (king->col < 7){
        // if there is a king 
        if (board[king->row][king->col+1]->type == KING && board[king->row][king->col+1]->color != color){
            return true;
        }
        for (int j = king->col + 1; j < 8; j++){
            // if we found a piece in the line to the right
            if (board[king->row][j]->type != NOTHING){
                // if the piece is a rook or a queen of the opposite color
                if ((board[king->row][j]->type == ROOK || board[king->row][j]->type == QUEEN) && board[king->row][j]->color != color){
                    return true;
                }
                // if the piece is not a rook or a queen
                else {
                    break;
                }
            }
        }
    }
    // looking to the left
    if (king->col > 0){
        // if there is a king 
        if (board[king->row][king->col-1]->type == KING && board[king->row][king->col-1]->color != color){
            return true;
        }
        for (int j = king->col - 1; j >= 0; j--){
            // if we found a piece in the line to the left
            if (board[king->row][j]->type != NOTHING){
                // if the piece is a rook or a queen of the opposite color
                if ((board[king->row][j]->type == ROOK || board[king->row][j]->type == QUEEN) && board[king->row][j]->color != color){
                    return true;
                }
                // if the piece is not a rook or a queen
                else {
                    break;
                }
            }
        }
    }
    // looking up
    if (king->row > 0){
        // if there is a king 
        if (board[king->row-1][king->col]->type == KING && board[king->row-1][king->col]->color != color){
            return true;
        }
        for (int i = king->row - 1; i >= 0; i--){
            // if we found a piece in the line up
            if (board[i][king->col]->type != NOTHING){
                // if the piece is a rook or a queen of the opposite color
                if ((board[i][king->col]->type == ROOK || board[i][king->col]->type == QUEEN) && board[i][king->col]->color != color){
                    return true;
                }
                // if the piece is not a rook or a queen
                else {
                    break;
                }
            }
        }
    }
    // looking down
    if (king->row < 7){
        // if there is a king 
        if (board[king->row+1][king->col]->type == KING && board[king->row+1][king->col]->color != color){
            return true;
        }
        for (int i = king->row + 1; i < 8; i++){
            // if we found a piece in the line down
            if (board[i][king->col]->type != NOTHING){
                // if the piece is a rook or a queen of the opposite color
                if ((board[i][king->col]->type == ROOK || board[i][king->col]->type == QUEEN) && board[i][king->col]->color != color){
                    return true;
                }
                // if the piece is not a rook or a queen
                else {
                    break;
                }
            }
        }
    }

    // looking if a bishop or a queen if threatening the king
    // looking for the 4 possible directions of the bishop and the queen
    // looking to the right and down
    if (king->row < 7 && king->col < 7){
        // if there is a king 
        if (board[king->row+1][king->col+1]->type == KING && board[king->row+1][king->col+1]->color != color){
            return true;
        }
        for (int i = king->row + 1, j = king->col + 1; i < 8 && j < 8; i++, j++){
            // if we found a piece in the diagonal to the right and down
            if (board[i][j]->type != NOTHING){
                // if the piece is a bishop or a queen of the opposite color
                if ((board[i][j]->type == BISHOP || board[i][j]->type == QUEEN) && board[i][j]->color != color){
                    return true;
                }
                // if the piece is not a bishop or a queen
                else {
                    break;
                }
            }
        }
    }
    // looking to the left and down
    if (king->row < 7 && king->col > 0){
        // if there is a king 
        if (board[king->row+1][king->col-1]->type == KING && board[king->row+1][king->col-1]->color != color){
            return true;
        }
        for (int i = king->row + 1, j = king->col - 1; i < 8 && j >= 0; i++, j--){
            // if we found a piece in the diagonal to the left and down
            if (board[i][j]->type != NOTHING){
                // if the piece is a bishop or a queen of the opposite color
                if ((board[i][j]->type == BISHOP || board[i][j]->type == QUEEN) && board[i][j]->color != color){
                    return true;
                }
                // if the piece is not a bishop or a queen
                else {
                    break;
                }
            }
        }
    }
    // looking to the right and up
    if (king->row > 0 && king->col < 7){
        // if there is a king 
        if (board[king->row-1][king->col+1]->type == KING && board[king->row-1][king->col+1]->color != color){
            return true;
        }
        for (int i = king->row - 1, j = king->col + 1; i >= 0 && j < 8; i--, j++){
            // if we found a piece in the diagonal to the right and up
            if (board[i][j]->type != NOTHING){
                // if the piece is a bishop or a queen of the opposite color
                if ((board[i][j]->type == BISHOP || board[i][j]->type == QUEEN) && board[i][j]->color != color){
                    return true;
                }
                // if the piece is not a bishop or a queen
                else {
                    break;
                }
            }
        }
    }
    // looking to the left and up
    if (king->row > 0 && king->col > 0){
        // if there is a king 
        if (board[king->row-1][king->col-1]->type == KING && board[king->row-1][king->col-1]->color != color){
            return true;
        }
        for (int i = king->row - 1, j = king->col - 1; i >= 0 && j >= 0; i--, j--){
            // if we found a piece in the diagonal to the left and up
            if (board[i][j]->type != NOTHING){
                // if the piece is a bishop or a queen of the opposite color
                if ((board[i][j]->type == BISHOP || board[i][j]->type == QUEEN) && board[i][j]->color != color){
                    return true;
                }
                // if the piece is not a bishop or a queen
                else {
                    break;
                }
            }
        }
    }

    // default
    return false;

}


Piece* Get_King(int color, Piece*** board){

    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            if (board[i][j]->type == KING && board[i][j]->color == color){
                return board[i][j];
            }
        }
    }

    // default
    return NULL;
}