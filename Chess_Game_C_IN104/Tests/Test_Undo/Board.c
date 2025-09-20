#include "Board.h"


Piece*** Init_Board(){
    Piece*** board = (Piece***)malloc(BOARD_SIZE * sizeof(Piece**));
    for (int i = 0; i < BOARD_SIZE; i++){
        board[i] = (Piece**)malloc(BOARD_SIZE * sizeof(Piece*));
        for (int j = 0; j < BOARD_SIZE; j++){
            board[i][j] = Create_Piece();
        }
    }

    // looking for a malloc error 
    if (board == NULL){
        printf("Error: malloc failed in Init_Board\n");
        return NULL;
        for (int i = 0; i < BOARD_SIZE; i++){
            if (board[i] == NULL){
                printf("Error: malloc failed in Init_Board\n");
                return NULL;
            }
            for (int j = 0; j < BOARD_SIZE; j++){
                if (board[i][j] == NULL){
                    printf("Error: malloc failed in Init_Board\n");
                    return NULL;
                }
            }
        }
    }

    // setting the pieces on the board
    // the first two rows are for the black pieces
    // the last two rows are for the white pieces
    // the others for piece that will be initialized with everything to 0 but it's already done with the Create_Piece function
    
    // the only thing to do is to set the row and the col of the piece upto date
    // we can do that for each piece in the board, without having to do that separately for each piece
    // those will not changed for the rest of the game, but will be useful to have a shortcuts to know if a certain type of piece is still on its start position or not
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            board[i][j]->row = i;
            board[i][j]->col = j;
        }
    }

    // placing all the piece 
    // black pieces
    // rooks
    board[0][0]->type = ROOK;
    board[0][0]->color = BLACK;
    board[0][0]->value = ROOK_VALUE;
    board[0][0]->is_alive = true;
    board[0][0]->is_checked = false;
    board[0][0]->is_on_his_start_position = true;

    board[0][7]->type = ROOK;
    board[0][7]->color = BLACK;
    board[0][7]->value = ROOK_VALUE;
    board[0][7]->is_alive = true;
    board[0][7]->is_checked = false;
    board[0][7]->is_on_his_start_position = true;

    // knights
    board[0][1]->type = KNIGHT;
    board[0][1]->color = BLACK;
    board[0][1]->value = KNIGHT_VALUE;
    board[0][1]->is_alive = true;
    board[0][1]->is_checked = false;
    board[0][1]->is_on_his_start_position = true;

    board[0][6]->type = KNIGHT;
    board[0][6]->color = BLACK;
    board[0][6]->value = KNIGHT_VALUE;
    board[0][6]->is_alive = true;
    board[0][6]->is_checked = false;
    board[0][6]->is_on_his_start_position = true;

    // bishops
    board[0][2]->type = BISHOP;
    board[0][2]->color = BLACK;
    board[0][2]->value = BISHOP_VALUE;
    board[0][2]->is_alive = true;
    board[0][2]->is_checked = false;
    board[0][2]->is_on_his_start_position = true;

    board[0][5]->type = BISHOP;
    board[0][5]->color = BLACK;
    board[0][5]->value = BISHOP_VALUE;
    board[0][5]->is_alive = true;
    board[0][5]->is_checked = false;
    board[0][5]->is_on_his_start_position = true;

    // queen
    board[0][3]->type = QUEEN;
    board[0][3]->color = BLACK;
    board[0][3]->value = QUEEN_VALUE;
    board[0][3]->is_alive = true;
    board[0][3]->is_checked = false;
    board[0][3]->is_on_his_start_position = true;

    // king
    board[0][4]->type = KING;
    board[0][4]->color = BLACK;
    board[0][4]->value = KING_VALUE;
    board[0][4]->is_alive = true;
    board[0][4]->is_checked = false;
    board[0][4]->is_on_his_start_position = true;

    // pawns
    for (int i = 0; i < BOARD_SIZE; i++){
        board[1][i]->type = PAWN;
        board[1][i]->color = BLACK;
        board[1][i]->value = PAWN_VALUE;
        board[1][i]->is_alive = true;
        board[1][i]->is_checked = false;
        board[1][i]->is_on_his_start_position = true;
    }


    // white pieces
    // rooks
    board[7][0]->type = ROOK;
    board[7][0]->color = WHITE;
    board[7][0]->value = ROOK_VALUE;
    board[7][0]->is_alive = true;
    board[7][0]->is_checked = false;
    board[7][0]->is_on_his_start_position = true;

    board[7][7]->type = ROOK;
    board[7][7]->color = WHITE;
    board[7][7]->value = ROOK_VALUE;
    board[7][7]->is_alive = true;
    board[7][7]->is_checked = false;
    board[7][7]->is_on_his_start_position = true;

    // knights
    board[7][1]->type = KNIGHT;
    board[7][1]->color = WHITE;
    board[7][1]->value = KNIGHT_VALUE;
    board[7][1]->is_alive = true;
    board[7][1]->is_checked = false;
    board[7][1]->is_on_his_start_position = true;

    board[7][6]->type = KNIGHT;
    board[7][6]->color = WHITE;
    board[7][6]->value = KNIGHT_VALUE;
    board[7][6]->is_alive = true;
    board[7][6]->is_checked = false;
    board[7][6]->is_on_his_start_position = true;

    // bishops
    board[7][2]->type = BISHOP;
    board[7][2]->color = WHITE;
    board[7][2]->value = BISHOP_VALUE;
    board[7][2]->is_alive = true;
    board[7][2]->is_checked = false;
    board[7][2]->is_on_his_start_position = true;

    board[7][5]->type = BISHOP;
    board[7][5]->color = WHITE;
    board[7][5]->value = BISHOP_VALUE;
    board[7][5]->is_alive = true;
    board[7][5]->is_checked = false;
    board[7][5]->is_on_his_start_position = true;

    // queen
    board[7][3]->type = QUEEN;
    board[7][3]->color = WHITE;
    board[7][3]->value = QUEEN_VALUE;
    board[7][3]->is_alive = true;
    board[7][3]->is_checked = false;
    board[7][3]->is_on_his_start_position = true;

    // king
    board[7][4]->type = KING;
    board[7][4]->color = WHITE;
    board[7][4]->value = KING_VALUE;
    board[7][4]->is_alive = true;
    board[7][4]->is_checked = false;
    board[7][4]->is_on_his_start_position = true;

    // pawns
    for (int i = 0; i < BOARD_SIZE; i++){
        board[6][i]->type = PAWN;
        board[6][i]->color = WHITE;
        board[6][i]->value = PAWN_VALUE;
        board[6][i]->is_alive = true;
        board[6][i]->is_checked = false;
        board[6][i]->is_on_his_start_position = true;
    }

    // completing the board with the other pieces
    for (int i = 2; i < 6; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            board[i][j]->type = NOTHING;
            board[i][j]->color = NO_COLOR;
            board[i][j]->value = 0;
            board[i][j]->is_alive = false;
            board[i][j]->is_checked = false;
            board[i][j]->is_on_his_start_position = false;
        }
    }

    // finally, we can return the board
    return board;
}


void Reset_Board(Piece*** board){
     for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            board[i][j]->row = i;
            board[i][j]->col = j;
        }
    }

    // placing all the piece 
    // black pieces
    // rooks
    board[0][0]->type = ROOK;
    board[0][0]->color = BLACK;
    board[0][0]->value = ROOK_VALUE;
    board[0][0]->is_alive = true;
    board[0][0]->is_checked = false;
    board[0][0]->is_on_his_start_position = true;

    board[0][7]->type = ROOK;
    board[0][7]->color = BLACK;
    board[0][7]->value = ROOK_VALUE;
    board[0][7]->is_alive = true;
    board[0][7]->is_checked = false;
    board[0][7]->is_on_his_start_position = true;

    // knights
    board[0][1]->type = KNIGHT;
    board[0][1]->color = BLACK;
    board[0][1]->value = KNIGHT_VALUE;
    board[0][1]->is_alive = true;
    board[0][1]->is_checked = false;
    board[0][1]->is_on_his_start_position = true;

    board[0][6]->type = KNIGHT;
    board[0][6]->color = BLACK;
    board[0][6]->value = KNIGHT_VALUE;
    board[0][6]->is_alive = true;
    board[0][6]->is_checked = false;
    board[0][6]->is_on_his_start_position = true;

    // bishops
    board[0][2]->type = BISHOP;
    board[0][2]->color = BLACK;
    board[0][2]->value = BISHOP_VALUE;
    board[0][2]->is_alive = true;
    board[0][2]->is_checked = false;
    board[0][2]->is_on_his_start_position = true;

    board[0][5]->type = BISHOP;
    board[0][5]->color = BLACK;
    board[0][5]->value = BISHOP_VALUE;
    board[0][5]->is_alive = true;
    board[0][5]->is_checked = false;
    board[0][5]->is_on_his_start_position = true;

    // queen
    board[0][3]->type = QUEEN;
    board[0][3]->color = BLACK;
    board[0][3]->value = QUEEN_VALUE;
    board[0][3]->is_alive = true;
    board[0][3]->is_checked = false;
    board[0][3]->is_on_his_start_position = true;

    // king
    board[0][4]->type = KING;
    board[0][4]->color = BLACK;
    board[0][4]->value = KING_VALUE;
    board[0][4]->is_alive = true;
    board[0][4]->is_checked = false;
    board[0][4]->is_on_his_start_position = true;

    // pawns
    for (int i = 0; i < BOARD_SIZE; i++){
        board[1][i]->type = PAWN;
        board[1][i]->color = BLACK;
        board[1][i]->value = PAWN_VALUE;
        board[1][i]->is_alive = true;
        board[1][i]->is_checked = false;
        board[1][i]->is_on_his_start_position = true;
    }


    // white pieces
    // rooks
    board[7][0]->type = ROOK;
    board[7][0]->color = WHITE;
    board[7][0]->value = ROOK_VALUE;
    board[7][0]->is_alive = true;
    board[7][0]->is_checked = false;
    board[7][0]->is_on_his_start_position = true;

    board[7][7]->type = ROOK;
    board[7][7]->color = WHITE;
    board[7][7]->value = ROOK_VALUE;
    board[7][7]->is_alive = true;
    board[7][7]->is_checked = false;
    board[7][7]->is_on_his_start_position = true;

    // knights
    board[7][1]->type = KNIGHT;
    board[7][1]->color = WHITE;
    board[7][1]->value = KNIGHT_VALUE;
    board[7][1]->is_alive = true;
    board[7][1]->is_checked = false;
    board[7][1]->is_on_his_start_position = true;

    board[7][6]->type = KNIGHT;
    board[7][6]->color = WHITE;
    board[7][6]->value = KNIGHT_VALUE;
    board[7][6]->is_alive = true;
    board[7][6]->is_checked = false;
    board[7][6]->is_on_his_start_position = true;

    // bishops
    board[7][2]->type = BISHOP;
    board[7][2]->color = WHITE;
    board[7][2]->value = BISHOP_VALUE;
    board[7][2]->is_alive = true;
    board[7][2]->is_checked = false;
    board[7][2]->is_on_his_start_position = true;

    board[7][5]->type = BISHOP;
    board[7][5]->color = WHITE;
    board[7][5]->value = BISHOP_VALUE;
    board[7][5]->is_alive = true;
    board[7][5]->is_checked = false;
    board[7][5]->is_on_his_start_position = true;

    // queen
    board[7][3]->type = QUEEN;
    board[7][3]->color = WHITE;
    board[7][3]->value = QUEEN_VALUE;
    board[7][3]->is_alive = true;
    board[7][3]->is_checked = false;
    board[7][3]->is_on_his_start_position = true;

    // king
    board[7][4]->type = KING;
    board[7][4]->color = WHITE;
    board[7][4]->value = KING_VALUE;
    board[7][4]->is_alive = true;
    board[7][4]->is_checked = false;
    board[7][4]->is_on_his_start_position = true;

    // pawns
    for (int i = 0; i < BOARD_SIZE; i++){
        board[6][i]->type = PAWN;
        board[6][i]->color = WHITE;
        board[6][i]->value = PAWN_VALUE;
        board[6][i]->is_alive = true;
        board[6][i]->is_checked = false;
        board[6][i]->is_on_his_start_position = true;
    }

    // completing the board with the other pieces
    for (int i = 2; i < 6; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            board[i][j]->type = NOTHING;
            board[i][j]->color = NO_COLOR;
            board[i][j]->value = 0;
            board[i][j]->is_alive = false;
            board[i][j]->is_checked = false;
            board[i][j]->is_on_his_start_position = false;
        }
    }
}


void Clear_Board(Piece*** board){
    // if the board is not NULL (malloc error), we can free it
    if (board != NULL){
        for (int i = 0; i < BOARD_SIZE; i++){
            for (int j = 0; j < BOARD_SIZE; j++){
                Destroy_Piece(board[i][j]);
            }
            free(board[i]);
        }
        free(board);
    }
}


void Make_Move(Piece*** board, Move* move, Players* players){
    // we suppose that the log is updated before calling this function
    // we suppose that the move is valid
    // that the piece that will move will have it's parameters updated 
    // - for example : if a pawn got out of his start position, we will update the is_on_his_start_position attribute before calling this function
    // we can move the piece
    // first we update the destination piece with the source piece, before suppressing the source piece on the board by reinitializing it
    
    // udpating the destination piece
    board[move->destination_row][move->destination_col]->type = board[move->previous_row][move->previous_col]->type;
    board[move->destination_row][move->destination_col]->color = board[move->previous_row][move->previous_col]->color;
    board[move->destination_row][move->destination_col]->value = board[move->previous_row][move->previous_col]->value;
    board[move->destination_row][move->destination_col]->is_alive = board[move->previous_row][move->previous_col]->is_alive;
    board[move->destination_row][move->destination_col]->is_checked = board[move->previous_row][move->previous_col]->is_checked;
    board[move->destination_row][move->destination_col]->is_on_his_start_position = Is_Piece_on_its_start_position(board[move->destination_row][move->destination_col]); // here we don't have any others choice than to check if the piece is on its start position or not, not with a smart way
    
    // suppressing the source piece
    board[move->previous_row][move->previous_col]->type = NOTHING;
    board[move->previous_row][move->previous_col]->color = NO_COLOR;
    board[move->previous_row][move->previous_col]->value = 0;
    board[move->previous_row][move->previous_col]->is_alive = false;
    board[move->previous_row][move->previous_col]->is_checked = false;
    board[move->previous_row][move->previous_col]->is_on_his_start_position = false;


    // updating the players that be the next to play
    Change_Players_that_is_Playing(players);

}


void Make_Rock_Move(Piece*** board, Move* move, Move* king_move_during_rock, Move* rook_move_during_rock, Players* players){
    // we suppose that the log is updated before calling this function
    // we suppose that the move is valid
    // that the piece that will move will have it's parameters updated 
    // - for example : if a pawn got out of his start position, we will update the is_on_his_start_position attribute before calling this function
    // we can move the piece


    // updating the rook 
    // first we update the destination piece with the source piece, before suppressing the source piece on the board by reinitializing it
    board[rook_move_during_rock->destination_row][rook_move_during_rock->destination_col]->type = board[rook_move_during_rock->previous_row][rook_move_during_rock->previous_col]->type;
    board[rook_move_during_rock->destination_row][rook_move_during_rock->destination_col]->color = board[rook_move_during_rock->previous_row][rook_move_during_rock->previous_col]->color;
    board[rook_move_during_rock->destination_row][rook_move_during_rock->destination_col]->value = board[rook_move_during_rock->previous_row][rook_move_during_rock->previous_col]->value;
    board[rook_move_during_rock->destination_row][rook_move_during_rock->destination_col]->is_alive = board[rook_move_during_rock->previous_row][rook_move_during_rock->previous_col]->is_alive;
    board[rook_move_during_rock->destination_row][rook_move_during_rock->destination_col]->is_checked = board[rook_move_during_rock->previous_row][rook_move_during_rock->previous_col]->is_checked;
    board[rook_move_during_rock->destination_row][rook_move_during_rock->destination_col]->is_on_his_start_position = Is_Piece_on_its_start_position(board[rook_move_during_rock->destination_col][rook_move_during_rock->destination_col]); // here we don't have any others choice than to check if the piece is on its start position or not, not with a smart way

    board[rook_move_during_rock->previous_row][rook_move_during_rock->previous_col]->type = NOTHING;
    board[rook_move_during_rock->previous_row][rook_move_during_rock->previous_col]->color = NO_COLOR;
    board[rook_move_during_rock->previous_row][rook_move_during_rock->previous_col]->value = 0;
    board[rook_move_during_rock->previous_row][rook_move_during_rock->previous_col]->is_alive = false;
    board[rook_move_during_rock->previous_row][rook_move_during_rock->previous_col]->is_checked = false;
    board[rook_move_during_rock->previous_row][rook_move_during_rock->previous_col]->is_on_his_start_position = false;

    // updating the king
    // first we update the destination piece with the source piece, before suppressing the source piece on the board by reinitializing it
    board[king_move_during_rock->destination_row][king_move_during_rock->destination_col]->type = board[king_move_during_rock->previous_row][king_move_during_rock->previous_col]->type;
    board[king_move_during_rock->destination_row][king_move_during_rock->destination_col]->color = board[king_move_during_rock->previous_row][king_move_during_rock->previous_col]->color;
    board[king_move_during_rock->destination_row][king_move_during_rock->destination_col]->value = board[king_move_during_rock->previous_row][king_move_during_rock->previous_col]->value;
    board[king_move_during_rock->destination_row][king_move_during_rock->destination_col]->is_alive = board[king_move_during_rock->previous_row][king_move_during_rock->previous_col]->is_alive;
    board[king_move_during_rock->destination_row][king_move_during_rock->destination_col]->is_checked = board[king_move_during_rock->previous_row][king_move_during_rock->previous_col]->is_checked;
    board[king_move_during_rock->destination_row][king_move_during_rock->destination_col]->is_on_his_start_position = Is_Piece_on_its_start_position(board[king_move_during_rock->destination_col][king_move_during_rock->destination_col]); // here we don't have any others choice than to check if the piece is on its start position or not, not with a smart way

    board[king_move_during_rock->previous_row][king_move_during_rock->previous_col]->type = NOTHING;
    board[king_move_during_rock->previous_row][king_move_during_rock->previous_col]->color = NO_COLOR;
    board[king_move_during_rock->previous_row][king_move_during_rock->previous_col]->value = 0;
    board[king_move_during_rock->previous_row][king_move_during_rock->previous_col]->is_alive = false;
    board[king_move_during_rock->previous_row][king_move_during_rock->previous_col]->is_checked = false;
    board[king_move_during_rock->previous_row][king_move_during_rock->previous_col]->is_on_his_start_position = false;
    

    // updating the players that be the next to play
    Change_Players_that_is_Playing(players);

}


void Clear_En_Passant_Piece(Move* move, Piece*** board, Tiles_Pawn* Pawn_Move_State){

    // depinding on the color of the piece that moved, we need to clear the en_passant piece
    // if it's white
    if (board[move->previous_row][move->previous_col]->color == WHITE){
        
        // we need to clear the en_passant piece that is on the left of the pawn
        board[move->destination_row +1][move->destination_col]->type = NOTHING;
        board[move->destination_row +1][move->destination_col]->color = NO_COLOR;
        board[move->destination_row +1][move->destination_col]->value = 0;
        board[move->destination_row +1][move->destination_col]->is_alive = false;
        board[move->destination_row +1][move->destination_col]->is_checked = false;
        board[move->destination_row +1][move->destination_col]->is_on_his_start_position = false;
          
    }

    // if it's black
    else if (board[move->previous_row][move->previous_col]->color == BLACK){
        
        // we need to clear the en_passant piece that is on the left of the pawn
        board[move->destination_row -1][move->destination_col]->type = NOTHING;
        board[move->destination_row -1][move->destination_col]->color = NO_COLOR;
        board[move->destination_row -1][move->destination_col]->value = 0;
        board[move->destination_row -1][move->destination_col]->is_alive = false;
        board[move->destination_row -1][move->destination_col]->is_checked = false;
        board[move->destination_row -1][move->destination_col]->is_on_his_start_position = false;
          
    }
}


void Change_Others_Structures(Move_Log_array* log, Captured_Piece_and_Score* captured_piece_and_score, State_Of_Rock_and_Check* state_of_rock_and_check, Players* players, Piece*** board){
    
    // updating the captured pieces and the score

    // if the piece in the updated log at the last index (for the last move) is not NOTHING, then we have a captured piece
    if (log->Move_Log[log->actual_size-1]->taken_piece_type != NOTHING){
        // it then depend on the color of the piece to know which player captured it
        // if it's white : 
        if (log->Move_Log[log->actual_size-1]->taken_piece_color == WHITE){
            // updating the captured piece by its coordinates
            captured_piece_and_score->white_pieces_captured[captured_piece_and_score->number_of_white_pieces_captured]->col = log->Move_Log[log->actual_size-1]->move->destination_col;
            captured_piece_and_score->white_pieces_captured[captured_piece_and_score->number_of_white_pieces_captured]->row = log->Move_Log[log->actual_size-1]->move->destination_row;
            
            // updating the other attributes of the piece
            captured_piece_and_score->white_pieces_captured[captured_piece_and_score->number_of_white_pieces_captured]->type = log->Move_Log[log->actual_size-1]->taken_piece_type;
            captured_piece_and_score->white_pieces_captured[captured_piece_and_score->number_of_white_pieces_captured]->color = log->Move_Log[log->actual_size-1]->taken_piece_color;
            captured_piece_and_score->white_pieces_captured[captured_piece_and_score->number_of_white_pieces_captured]->value = Get_Value_Of_Piece(log->Move_Log[log->actual_size-1]->taken_piece_type);
            
            // in reality, we don't care about it, but we can update it not to let it to false (NULL here)
            captured_piece_and_score->white_pieces_captured[captured_piece_and_score->number_of_white_pieces_captured]->is_alive = false;
            captured_piece_and_score->white_pieces_captured[captured_piece_and_score->number_of_white_pieces_captured]->is_checked = false;
            captured_piece_and_score->white_pieces_captured[captured_piece_and_score->number_of_white_pieces_captured]->is_on_his_start_position = false;

            // incrementing the number of white pieces captured
            captured_piece_and_score->number_of_white_pieces_captured++;
        }
    
        // if it's black : 
        else if (log->Move_Log[log->actual_size-1]->taken_piece_color == BLACK){
            // updating the captured piece by its coordinates
            captured_piece_and_score->black_pieces_captured[captured_piece_and_score->number_of_black_pieces_captured]->col = log->Move_Log[log->actual_size-1]->move->destination_col;
            captured_piece_and_score->black_pieces_captured[captured_piece_and_score->number_of_black_pieces_captured]->row = log->Move_Log[log->actual_size-1]->move->destination_row;

            // updating the other attributes of the piece
            captured_piece_and_score->black_pieces_captured[captured_piece_and_score->number_of_black_pieces_captured]->type = log->Move_Log[log->actual_size-1]->taken_piece_type;
            captured_piece_and_score->black_pieces_captured[captured_piece_and_score->number_of_black_pieces_captured]->color = log->Move_Log[log->actual_size-1]->taken_piece_color;
            captured_piece_and_score->black_pieces_captured[captured_piece_and_score->number_of_black_pieces_captured]->value = Get_Value_Of_Piece(log->Move_Log[log->actual_size-1]->taken_piece_type);

            // in reality, we don't care about it, but we can update it not to let it to false (NULL here)
            captured_piece_and_score->black_pieces_captured[captured_piece_and_score->number_of_black_pieces_captured]->is_alive = false;
            captured_piece_and_score->black_pieces_captured[captured_piece_and_score->number_of_black_pieces_captured]->is_checked = false;
            captured_piece_and_score->black_pieces_captured[captured_piece_and_score->number_of_black_pieces_captured]->is_on_his_start_position = false;

            // incrementing the number of black pieces captured
            captured_piece_and_score->number_of_black_pieces_captured++;
        }
    }

    // updating the score
    // getting the total score of the white captured pieces
    int score_white_captured = 0;
    for (int i = 0; i < captured_piece_and_score->number_of_white_pieces_captured; i++){
        score_white_captured += captured_piece_and_score->white_pieces_captured[i]->value;
    }

    // getting the total score of the black captured pieces
    int score_black_captured = 0;
    for (int i = 0; i < captured_piece_and_score->number_of_black_pieces_captured; i++){
        score_black_captured += captured_piece_and_score->black_pieces_captured[i]->value;
    }

    // updating the score of the players and the player that is winning depending on the score
    if (score_white_captured > score_black_captured){
        captured_piece_and_score->score = score_white_captured - score_black_captured;
        captured_piece_and_score->player_that_is_winning = BLACK;
    }
    else if (score_white_captured < score_black_captured){
        captured_piece_and_score->score = score_black_captured - score_white_captured;
        captured_piece_and_score->player_that_is_winning = WHITE;
    }
    else {
        captured_piece_and_score->score = 0;
        captured_piece_and_score->player_that_is_winning = WHITE;
    }
   

    // updating the state of the rock and the check 
    // we go through this function if no rock is done 
    // but we need to update some paramters in the structure : if a rook moved, if a king is checked
    
    // for the move of the different rooks we look on the board if on the corners, the rooks are still on their start position
    // if not, we update the structure to say that the rock is not possible anymore
    // black left rook
    if (board[0][0]->type == ROOK && board[0][0]->color == BLACK){
        state_of_rock_and_check->black_left_rook_moved = false;
    }
    else {
        state_of_rock_and_check->black_left_rook_moved = true;
    }
    // black right rook
    if (board[0][7]->type == ROOK && board[0][7]->color == BLACK){
        state_of_rock_and_check->black_right_rook_moved = false;
    }
    else {
        state_of_rock_and_check->black_right_rook_moved = true;
    }
    // white left rook
    if (board[7][0]->type == ROOK && board[7][0]->color == WHITE){
        state_of_rock_and_check->white_left_rook_moved = false;
    }
    else {
        state_of_rock_and_check->white_left_rook_moved = true;
    }
    // white right rook
    if (board[7][7]->type == ROOK && board[7][7]->color == WHITE){
        state_of_rock_and_check->white_right_rook_moved = false;
    }
    else {
        state_of_rock_and_check->white_right_rook_moved = true;
    }
    // white king
    if (board[7][4]->type == KING && board[7][4]->color == WHITE){
        state_of_rock_and_check->white_king_moved = false;
    }
    else {
        state_of_rock_and_check->white_king_moved = true;
    }
    // black king
    if (board[0][4]->type == KING && board[0][4]->color == BLACK){
        state_of_rock_and_check->black_king_moved = false;
    }
    else {
        state_of_rock_and_check->black_king_moved = true;
    }


    // for the check, we need to look if the king is checked, if we are here the king of the other color is not checked
    if (log->Move_Log[log->actual_size-1]->check_state == WHITE_CHECK){
        state_of_rock_and_check->is_white_king_checked = true;
        state_of_rock_and_check->is_black_king_checked = false;
    }
    else if (log->Move_Log[log->actual_size-1]->check_state == BLACK_CHECK){
        state_of_rock_and_check->is_white_king_checked = false;
        state_of_rock_and_check->is_black_king_checked = true;
    }
    else if (log->Move_Log[log->actual_size-1]->check_state == NO_CHECK){
        state_of_rock_and_check->is_white_king_checked = false;
        state_of_rock_and_check->is_black_king_checked = false;
    }

    // don't need to change if the rock has already been done

}


void Change_Others_Structures_during_Rock(Move_Log_array* log, Captured_Piece_and_Score* captured_piece_and_score, State_Of_Rock_and_Check* state_of_rock_and_check, Players* players, Piece*** board){

    // updating the captured pieces and the score
    // no need, the rock doesn't capture any piece

    // updating the state of the rock and the check 
    // we go through this function if no rock is done 
    // but we need to update some paramters in the structure : if a rook moved, if a king is checked
    
    // for the move of the different rooks we look on the board if on the corners, the rooks are still on their start position
    // if not, we update the structure to say that the rock is not possible anymore
     // black left rook
    if (board[0][0]->type == ROOK && board[0][0]->color == BLACK){
        state_of_rock_and_check->black_left_rook_moved = false;
    }
    else {
        state_of_rock_and_check->black_left_rook_moved = true;
    }
    // black right rook
    if (board[0][7]->type == ROOK && board[0][7]->color == BLACK){
        state_of_rock_and_check->black_right_rook_moved = false;
    }
    else {
        state_of_rock_and_check->black_right_rook_moved = true;
    }
    // white left rook
    if (board[7][0]->type == ROOK && board[7][0]->color == WHITE){
        state_of_rock_and_check->white_left_rook_moved = false;
    }
    else {
        state_of_rock_and_check->white_left_rook_moved = true;
    }
    // white right rook
    if (board[7][7]->type == ROOK && board[7][7]->color == WHITE){
        state_of_rock_and_check->white_right_rook_moved = false;
    }
    else {
        state_of_rock_and_check->white_right_rook_moved = true;
    }
    // white king
    if (board[7][4]->type == KING && board[7][4]->color == WHITE){
        state_of_rock_and_check->white_king_moved = false;
    }
    else {
        state_of_rock_and_check->white_king_moved = true;
    }
    // black king
    if (board[0][4]->type == KING && board[0][4]->color == BLACK){
        state_of_rock_and_check->black_king_moved = false;
    }
    else {
        state_of_rock_and_check->black_king_moved = true;
    }

    // for the check, we put them to false since no checl can be done after a rock
    state_of_rock_and_check->is_white_king_checked = false;
    state_of_rock_and_check->is_black_king_checked = false;

    // changing the fact that one of the player has done a rock
    // the players that is playing is the one to play oafter the one that did the rock, since we change the player after making the move
    if (players->color_player_that_is_playing == WHITE){
        state_of_rock_and_check->black_rock_done = true;
    }
    else if (players->color_player_that_is_playing == BLACK){
        state_of_rock_and_check->white_rock_done = true;
    }
}


void Undo_Last_Move(Piece*** board, Move_Log_array* log, Captured_Piece_and_Score* captured_piece_and_score, State_Of_Rock_and_Check* state_of_rock_and_check, Players* players, Tiles_Pawn* Pawn_Move_State){

    // we undo the move on the board first before updating the others stuctures 

    // if there was a pawn promotion, we need to suppress the promoted piece and replace it by the pawn
    if (log->Move_Log[log->actual_size-1]->type_of_pawn_promoted != NOTHING) {
        board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->type = PAWN;
    }
    // for a short rock 
    if (log->Move_Log[log->actual_size-1]->rock_type == SHORT_ROCK) {
        // for the black player
        if (board[0][6]->type == KING){

            // putting back to the original places before the rock was done
            board[0][4]->type = KING;
            board[0][4]->color = BLACK;
            board[0][4]->value = KING_VALUE;
            board[0][4]->is_alive = true;
            board[0][4]->is_checked = false;
            board[0][4]->is_on_his_start_position = true;
            
            board[0][7]->type = ROOK;
            board[0][7]->color = BLACK;
            board[0][7]->value = KING_VALUE;
            board[0][7]->is_alive = true;
            board[0][7]->is_checked = false;
            board[0][7]->is_on_his_start_position = true;

            // making this cases empty as before the rock was done 
            board[0][5]->type = NOTHING;
            board[0][5]->color = NO_COLOR;
            board[0][5]->value = 0;
            board[0][5]->is_alive = false;
            board[0][5]->is_checked = false;
            board[0][5]->is_on_his_start_position = false;

            board[0][6]->type = NOTHING;
            board[0][6]->color = NO_COLOR;
            board[0][6]->value = 0;
            board[0][6]->is_alive = false;
            board[0][6]->is_checked = false;
            board[0][6]->is_on_his_start_position = false;

        }
        // for the white player
        else if (board[7][6]->type == KING){

            // putting back to the original places before the rock was done
            board[7][4]->type = KING;
            board[7][4]->color = WHITE;
            board[7][4]->value = KING_VALUE;
            board[7][4]->is_alive = true;
            board[7][4]->is_checked = false;
            board[7][4]->is_on_his_start_position = true;
            
            board[7][7]->type = ROOK;
            board[7][7]->color = WHITE;
            board[7][7]->value = KING_VALUE;
            board[7][7]->is_alive = true;
            board[7][7]->is_checked = false;
            board[7][7]->is_on_his_start_position = true;

            // making this cases empty as before the rock was done 
            board[7][5]->type = NOTHING;
            board[7][5]->color = NO_COLOR;
            board[7][5]->value = 0;
            board[7][5]->is_alive = false;
            board[7][5]->is_checked = false;
            board[7][5]->is_on_his_start_position = false;

            board[7][6]->type = NOTHING;
            board[7][6]->color = NO_COLOR;
            board[7][6]->value = 0;
            board[7][6]->is_alive = false;
            board[7][6]->is_checked = false;
            board[7][6]->is_on_his_start_position = false;

        }
    } 
    // for a long rock 
    else if (log->Move_Log[log->actual_size-1]->rock_type == LONG_ROCK){
        // for the black player 
        if (board[0][2]->type == KING){
            
            // putting back to the original places before the rock was done
            board[0][4]->type = KING;
            board[0][4]->color = BLACK;
            board[0][4]->value = KING_VALUE;
            board[0][4]->is_alive = true;
            board[0][4]->is_checked = false;
            board[0][4]->is_on_his_start_position = true;
            
            board[0][0]->type = ROOK;
            board[0][0]->color = BLACK;
            board[0][0]->value = KING_VALUE;
            board[0][0]->is_alive = true;
            board[0][0]->is_checked = false;
            board[0][0]->is_on_his_start_position = true;

            // making this cases empty as before the rock was done 
            board[0][1]->type = NOTHING;
            board[0][1]->color = NO_COLOR;
            board[0][1]->value = 0;
            board[0][1]->is_alive = false;
            board[0][1]->is_checked = false;
            board[0][1]->is_on_his_start_position = false;

            board[0][2]->type = NOTHING;
            board[0][2]->color = NO_COLOR;
            board[0][2]->value = 0;
            board[0][2]->is_alive = false;
            board[0][2]->is_checked = false;
            board[0][2]->is_on_his_start_position = false;

            board[0][3]->type = NOTHING;
            board[0][3]->color = NO_COLOR;
            board[0][3]->value = 0;
            board[0][3]->is_alive = false;
            board[0][3]->is_checked = false;
            board[0][3]->is_on_his_start_position = false;

        }
        // for the white player
        else if (board[7][2]->type == KING){

            // putting back to the original places before the rock was done
            board[7][4]->type = KING;
            board[7][4]->color = WHITE;
            board[7][4]->value = KING_VALUE;
            board[7][4]->is_alive = true;
            board[7][4]->is_checked = false;
            board[7][4]->is_on_his_start_position = true;
            
            board[7][0]->type = ROOK;
            board[7][0]->color = WHITE;
            board[7][0]->value = KING_VALUE;
            board[7][0]->is_alive = true;
            board[7][0]->is_checked = false;
            board[7][0]->is_on_his_start_position = true;

            // making this cases empty as before the rock was done 
            board[7][1]->type = NOTHING;
            board[7][1]->color = NO_COLOR;
            board[7][1]->value = 0;
            board[7][1]->is_alive = false;
            board[7][1]->is_checked = false;
            board[7][1]->is_on_his_start_position = false;

            board[7][2]->type = NOTHING;
            board[7][2]->color = NO_COLOR;
            board[7][2]->value = 0;
            board[7][2]->is_alive = false;
            board[7][2]->is_checked = false;
            board[7][2]->is_on_his_start_position = false;

            board[7][3]->type = NOTHING;
            board[7][3]->color = NO_COLOR;
            board[7][3]->value = 0;
            board[7][3]->is_alive = false;
            board[7][3]->is_checked = false;
            board[7][3]->is_on_his_start_position = false;

        }
    }
    // undoing the en passant move
    else if (log->Move_Log[log->actual_size-1]->en_passant_type_done == EN_PASSANT) {
        
        // if we go to the left : prev_col - dest_col = 1
        if (log->Move_Log[log->actual_size-1]->move->previous_col - log->Move_Log[log->actual_size-1]->move->destination_col == 1){

            // for the black player making an en passant 
            if (log->Move_Log[log->actual_size-1]->move->destination_row == 5){
                
                // putting back the moved pawn into its original place
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]->type = PAWN;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]->color = BLACK;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]->value = PAWN_VALUE;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]->is_alive = true;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]->is_checked = false;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]->is_on_his_start_position = Is_Piece_on_its_start_position(board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]);

                // putting back the eaten piece 
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col-1]->type = PAWN;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col-1]->color = WHITE;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col-1]->value = PAWN_VALUE;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col-1]->is_alive = true;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col-1]->is_checked = false;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col-1]->is_on_his_start_position = Is_Piece_on_its_start_position(board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]);

                // deleting the created pawn linked to the movement from the original place of the pawn
                board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->type = NOTHING;
                board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->color = NO_COLOR;
                board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->value = 0;
                board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->is_alive = false;
                board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->is_checked = false;
                board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->is_on_his_start_position = false;

            }

            // for the white player making an en passant 
            if (log->Move_Log[log->actual_size-1]->move->destination_row == 2){
                
                // putting back the moved pawn into its original place
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]->type = PAWN;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]->color = WHITE;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]->value = PAWN_VALUE;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]->is_alive = true;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]->is_checked = false;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]->is_on_his_start_position = Is_Piece_on_its_start_position(board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]);

                // putting back the eaten piece 
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col-1]->type = PAWN;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col-1]->color = BLACK;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col-1]->value = PAWN_VALUE;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col-1]->is_alive = true;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col-1]->is_checked = false;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col-1]->is_on_his_start_position = Is_Piece_on_its_start_position(board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]);

                // deleting the created pawn linked to the movement from the original place of the pawn
                board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->type = NOTHING;
                board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->color = NO_COLOR;
                board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->value = 0;
                board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->is_alive = false;
                board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->is_checked = false;
                board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->is_on_his_start_position = false;

            }

        }

        // if we go to the left : dest_col - prev_col = 1
        if (log->Move_Log[log->actual_size-1]->move->destination_col - log->Move_Log[log->actual_size-1]->move->previous_col == 1){
            
           // for the black player making an en passant 
            if (log->Move_Log[log->actual_size-1]->move->destination_row == 5){
                
                // putting back the moved pawn into its original place
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]->type = PAWN;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]->color = BLACK;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]->value = PAWN_VALUE;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]->is_alive = true;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]->is_checked = false;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]->is_on_his_start_position = Is_Piece_on_its_start_position(board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]);

                // putting back the eaten piece 
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col+1]->type = PAWN;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col+1]->color = WHITE;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col+1]->value = PAWN_VALUE;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col+1]->is_alive = true;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col+1]->is_checked = false;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col+1]->is_on_his_start_position = Is_Piece_on_its_start_position(board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]);

                // deleting the created pawn linked to the movement from the original place of the pawn
                board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->type = NOTHING;
                board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->color = NO_COLOR;
                board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->value = 0;
                board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->is_alive = false;
                board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->is_checked = false;
                board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->is_on_his_start_position = false;

            }

            // for the white player making an en passant 
            if (log->Move_Log[log->actual_size-1]->move->destination_row == 2){
                
                // putting back the moved pawn into its original place
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]->type = PAWN;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]->color = WHITE;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]->value = PAWN_VALUE;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]->is_alive = true;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]->is_checked = false;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]->is_on_his_start_position = Is_Piece_on_its_start_position(board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]);

                // putting back the eaten piece 
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col+1]->type = PAWN;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col+1]->color = BLACK;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col+1]->value = PAWN_VALUE;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col+1]->is_alive = true;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col+1]->is_checked = false;
                board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col+1]->is_on_his_start_position = Is_Piece_on_its_start_position(board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]);

                // deleting the created pawn linked to the movement from the original place of the pawn
                board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->type = NOTHING;
                board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->color = NO_COLOR;
                board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->value = 0;
                board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->is_alive = false;
                board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->is_checked = false;
                board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->is_on_his_start_position = false;

            }

        }

    }
    // when there is no special moves made 
    else {
        board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]->type = board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->type;
        board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]->color = board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->color;
        board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]->value = board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->value;
        board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]->is_alive = board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->is_alive;
        board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]->is_checked = board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->is_checked;
        board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]->is_on_his_start_position = Is_Piece_on_its_start_position(board[log->Move_Log[log->actual_size-1]->move->previous_row][log->Move_Log[log->actual_size-1]->move->previous_col]);

        // we need to suppress the piece that was moved unless it was another piece that was captured when the move was done
        if (log->Move_Log[log->actual_size-1]->taken_piece_type != NOTHING){
            board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->type = log->Move_Log[log->actual_size-1]->taken_piece_type;
            board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->color = log->Move_Log[log->actual_size-1]->taken_piece_color;
            board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->value = Get_Value_Of_Piece(log->Move_Log[log->actual_size-1]->taken_piece_type);
            board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->is_alive = true;
            board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->is_checked = false;
            board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->is_on_his_start_position = Is_Piece_on_its_start_position(board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]);
        }     
        else {
            board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->type = NOTHING;
            board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->color = NO_COLOR;
            board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->value = 0;
            board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->is_alive = false;
            board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->is_checked = false;
            board[log->Move_Log[log->actual_size-1]->move->destination_row][log->Move_Log[log->actual_size-1]->move->destination_col]->is_on_his_start_position = false;
        }        
    }
    

    // now, to be able to do again a rock, an en passant, make a pawn move 2 cases, we need to udpate the structures
    // the undo move for most of the things above depends on the player that was playing (so the opposite of the player that is playing now)

    // if a rock was done, we need to update the structure to say that the rock is possible again
    if (log->Move_Log[log->actual_size-1]->rock_type != NO_ROCK){
        
        // if the rock was done by the black player
        if (players->color_player_that_is_playing == WHITE){
            state_of_rock_and_check->black_rock_done = false;
            state_of_rock_and_check->black_king_moved = false;
            if (log->Move_Log[log->actual_size-1]->rock_type == SHORT_ROCK){
                state_of_rock_and_check->black_right_rook_moved = false;
            }
            else if (log->Move_Log[log->actual_size-1]->rock_type == LONG_ROCK){
                state_of_rock_and_check->black_left_rook_moved = false;
            }
            
        }

        // if the rock was done by the white player
        else if (players->color_player_that_is_playing == BLACK){
            state_of_rock_and_check->white_rock_done = false;
            state_of_rock_and_check->white_king_moved = false;
            if (log->Move_Log[log->actual_size-1]->rock_type == SHORT_ROCK){
                state_of_rock_and_check->white_right_rook_moved = false;
            }
            else if (log->Move_Log[log->actual_size-1]->rock_type == LONG_ROCK){
                state_of_rock_and_check->white_left_rook_moved = false;
            }
        }
    }
    
    // things to do when an en passant was done, to go back to the previous state, to be able to do it again
    // udpating the move with the log 
    Pawn_Move_State->move_made->previous_row = log->Move_Log[log->actual_size-1]->move->previous_row;
    Pawn_Move_State->move_made->previous_col = log->Move_Log[log->actual_size-1]->move->previous_col;
    Pawn_Move_State->move_made->destination_row = log->Move_Log[log->actual_size-1]->move->destination_row;
    Pawn_Move_State->move_made->destination_col = log->Move_Log[log->actual_size-1]->move->destination_col;
    // we now need to tell if there was a pawn move 2 cases done for a black pawn, or a white pawn
    if (log->Move_Log[log->actual_size-1]->en_passant_type_done == EN_PASSANT){
        // if the player that is currently playing is the white player, then before it was the black player that made the en passant move on a tile pawn update for the white player
        if (players->color_player_that_is_playing == WHITE){
            Pawn_Move_State->has_moved_2_squares = true;
            Pawn_Move_State->color = WHITE;
        }
        // if the player that is currently playing is the black player, then before it was the white player that made the en passant move on a tile pawn update for the black player
        else if (players->color_player_that_is_playing == BLACK){
            Pawn_Move_State->has_moved_2_squares = true;
            Pawn_Move_State->color = BLACK;
        }
    }
    else {
        Pawn_Move_State->has_moved_2_squares= false;
        Pawn_Move_State->color = NO_COLOR;
    }

    // updating the captured piece and score thanks to the log
    /* 
    need to change the captured piece and score thanks to the log 
    --> decreasing the sizes of the array we want depending on the log parameters
    --> calculating the score again as made in the function that updates the score (Change Structures)
    */
    
    // if we supress the last move that was done, we need to change the players that is playing
    Change_Players_that_is_Playing(players);

    // we suppress the last element in the log by decreasing its actual size
    log->actual_size=log->actual_size-1;
    
}