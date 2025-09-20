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


Piece*** Create_Copy_Board(Piece*** board){

    Piece*** board_copy = (Piece***)malloc(BOARD_SIZE * sizeof(Piece**));
    for (int i = 0; i < BOARD_SIZE; i++){
        board_copy[i] = (Piece**)malloc(BOARD_SIZE * sizeof(Piece*));
        for (int j = 0; j < BOARD_SIZE; j++){
            board_copy[i][j] = Create_Piece();
        }
    }

    // looking for a malloc error 
    if (board_copy == NULL){
        printf("Error: malloc failed in Init_Board\n");
        return NULL;
        for (int i = 0; i < BOARD_SIZE; i++){
            if (board_copy[i] == NULL){
                printf("Error: malloc failed in Init_Board\n");
                return NULL;
            }
            for (int j = 0; j < BOARD_SIZE; j++){
                if (board_copy[i][j] == NULL){
                    printf("Error: malloc failed in Init_Board\n");
                    return NULL;
                }
            }
        }
    }

    // copying the pieces
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            board_copy[i][j]->row = board[i][j]->row;
            board_copy[i][j]->col = board[i][j]->col;
            board_copy[i][j]->type = board[i][j]->type;
            board_copy[i][j]->color = board[i][j]->color;
            board_copy[i][j]->value = board[i][j]->value;
            board_copy[i][j]->is_alive = board[i][j]->is_alive;
            board_copy[i][j]->is_checked = board[i][j]->is_checked;
            board_copy[i][j]->is_on_his_start_position = board[i][j]->is_on_his_start_position;
        }
    }
    
    return board_copy;
}


void Copy_Board_Into(Piece*** board, Piece*** board_copy){
    // copying the pieces
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            board_copy[i][j]->row = board[i][j]->row;
            board_copy[i][j]->col = board[i][j]->col;
            board_copy[i][j]->type = board[i][j]->type;
            board_copy[i][j]->color = board[i][j]->color;
            board_copy[i][j]->value = board[i][j]->value;
            board_copy[i][j]->is_alive = board[i][j]->is_alive;
            board_copy[i][j]->is_checked = board[i][j]->is_checked;
            board_copy[i][j]->is_on_his_start_position = board[i][j]->is_on_his_start_position;
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


Board_Log_array* Init_Board_Log(int Max_Size){

    if (Max_Size <= 0){
        printf("Error: max_size must be greater than 0 in Init_Board_Log\n");
        return NULL;
    }

    Board_Log_array* Board_Log = (Board_Log_array*)malloc(sizeof(Board_Log_array));
    // looking for a malloc error
    if (Board_Log == NULL){
        printf("Error: malloc failed in Init_Board_Log\n");
        return NULL;
    }

    Board_Log->board_log = (Piece****)malloc(Max_Size * sizeof(Piece***));
    // looking for a malloc error
    if (Board_Log->board_log == NULL){
        printf("Error: malloc failed in Init_Board_Log\n");
        return NULL;
    }
    for (int i = 0; i < Max_Size; i++){
        Board_Log->board_log[i] = Init_Board();
        // looking for a malloc error
        if (Board_Log->board_log[i] == NULL){
            printf("Error: malloc failed in Init_Board_Log\n");
            return NULL;
        }
    }

    Board_Log->max_size = Max_Size;
    Board_Log->actual_size = 0;
    return Board_Log;
}


Board_Log_array* Create_Copy_Board_Log(Board_Log_array* board_log_array){
    Board_Log_array* board_log_array_copy = Init_Board_Log(board_log_array->max_size);
    // looking for malloc error
    if (board_log_array_copy == NULL){
        printf("Error: malloc failed in Create_Copy_Board_Log\n");
        return NULL;
    }
    // looking for a malloc error in the boards
    for (int i = 0; i < board_log_array->max_size; i++){
        if (board_log_array_copy->board_log[i] == NULL){
            printf("Error: malloc failed in Create_Copy_Board_Log\n");
            return NULL;
        }
    }

    for (int i = 0; i < board_log_array->actual_size; i++){
        Copy_Board_Into(board_log_array->board_log[i], board_log_array_copy->board_log[i]);
    }
    board_log_array_copy->actual_size = board_log_array->actual_size;
    return board_log_array_copy;

}


void Destroy_Board_Log(Board_Log_array* Board_Log){
    if (Board_Log == NULL){
        return;
    }
    if (Board_Log->board_log != NULL){
        for (int i = 0; i < Board_Log->max_size; i++){
            Clear_Board(Board_Log->board_log[i]);
        }
        free(Board_Log->board_log);
    }
    free(Board_Log);
}


Move_Log_array_MESSAGE_TYPE Add_Board_at_Last_Index_in_Array(Board_Log_array* Board_Log, Piece*** board){
    
    // everything needs not to be NULL
    if (Board_Log == NULL || board == NULL){
        return LOG_LIST_INVALID_ARGUMENT;
    }
    
    // if the board log is full, we need to remove the first element
    if (Board_Log->actual_size == Board_Log->max_size){
		return LOG_LIST_FULL;
    }
    Board_Log->actual_size++;

    // then we can add the board at the last index
    Copy_Board_Into(board, Board_Log->board_log[Board_Log->actual_size-1]);
    // incrementing the actual size
    return LOG_LIST_SUCCESS;
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


void Make_IA_Global_Move_and_Udpate_structures(Move* move, Piece*** board, Players* players, Move_Log_array* Log, Board_Log_array* Log_Board, State_Of_Rock_and_Check* State_Of_RockandCheck, Tiles_Pawn* Pawn_Move_State, Captured_Piece_and_Score* Captured_Pieces_and_Score, int IA_color, int level_IA){
    // getting if a rock was done
    int is_rock_possible_type_IA = Is_Rock_Possible(move, State_Of_RockandCheck, board);
    // getting if an en passant was done
    bool is_en_passant_done_IA = Is_En_Passant_Possible(move, board, Pawn_Move_State);
    int en_passant_type_IA = NO_EN_PASSANT;
    // if we have an en passant, we need to get the corresponding int
    if (is_en_passant_done_IA == true){
        en_passant_type_IA = EN_PASSANT;
    }

    // if a piece is taken, we need to know what type and what color it is, in case we want to undo it later, we can track the piece that has been taken to reinstall it on the board
    int piece_taken_type_IA = NOTHING;
    int piece_taken_color_IA = NO_COLOR;
    // if a move is valid, then we can also ask if a piece is taken, and if it's the case, we can know what type and what color it is
    bool will_capture_a_piece = Will_Capture(move, board);
    if (will_capture_a_piece == true && Is_Move_Valid(move, board, State_Of_RockandCheck, Pawn_Move_State) == true){
        piece_taken_type_IA = board[move->destination_row][move->destination_col]->type;
        piece_taken_color_IA = board[move->destination_row][move->destination_col]->color;
    }
    if (is_en_passant_done_IA == true){
        if (board[move->previous_row][move->previous_col]->color == WHITE){
            piece_taken_type_IA = PAWN;
            piece_taken_color_IA = BLACK;
        }
        else if (board[move->previous_row][move->previous_col]->color == BLACK){
            piece_taken_type_IA = PAWN;
            piece_taken_color_IA = WHITE;
        }
    }

    // concerning the pawn promotion fro the IA
    bool is_IA_pawn_promotion_happening = Is_Pawn_Promotion_Possible(move, board);
    int color_IA_promoted_paxwn = NO_COLOR;
    int type_IA_promoted_pawn = NOTHING;
    if (is_IA_pawn_promotion_happening == true){
        color_IA_promoted_paxwn = board[move->previous_row][move->previous_col]->color;
    }

    // getting the check state of the game before the move is made 
    bool check_state_before_move_bool_IA = Is_Check(players->color_player_that_is_playing, board);
    int check_state_before_move_IA = NO_COLOR;
    if (check_state_before_move_bool_IA == true){
        if (players->color_player_that_is_playing == WHITE){
            check_state_before_move_IA = WHITE_CHECK;
        }
        else if (players->color_player_that_is_playing == BLACK){
            check_state_before_move_IA = BLACK_CHECK;
        }
    }

    // getting if the move is about a pawn 
    bool pawn_move_done_IA = false;
    if (board[move->previous_row][move->previous_col]->type == PAWN){
        pawn_move_done_IA = true;
    }

    // if you touch the piece once, as in the real game, you're forced to play this piece, there isn't any way to cancel the move
    // making the move if it's valid, here we don't care about the special moves and what it does to other pieces
    // we will need to do it in the future, here we also don't care about the check
    if (Is_Move_Valid(move, board, State_Of_RockandCheck, Pawn_Move_State) == true && board[move->previous_row][move->previous_col]->color == IA_color){

        // making the move log update that is crucial for Make_Move to work since we go searching for an index actual_size-1 and only adding an element to Move_Log will make actual_size-1 positive, not to have a segmentation fault
        // but only a valid move will be added to the log
        Move_Log_Element* element = Create_Element_Move_Log();
        Change_Move_Log_Element(element, move->previous_row, move->previous_col, move->destination_row, move->destination_col, check_state_before_move_IA, piece_taken_type_IA, piece_taken_color_IA, is_rock_possible_type_IA, en_passant_type_IA, color_IA_promoted_paxwn, type_IA_promoted_pawn, pawn_move_done_IA);
        Move_Log_array_MESSAGE_TYPE message_IA = Add_Element_to_the_end_of_Move_Log_array(Log, element);
        if (message_IA != LOG_LIST_SUCCESS){
            printf("Error: the log is full\n");
        }

        Destroy_Move_Log_Element(element);
        
        // trying to make the rock effective by getting the real moves linked to the rock that has been made
        if (is_rock_possible_type_IA != NO_ROCK){
            Move* king_move_during_rock=Create_King_Move_during_Rock(move, board, State_Of_RockandCheck);
            Move* rook_move_during_rock=Create_Rook_Move_during_Rock(move, board, State_Of_RockandCheck);
            // we need to make the two moves, the king and the rock, and put the places there were to zero 
            // but also udpating the parameters others than the log, to keep track of the state of the game
            Make_Rock_Move(board, move, king_move_during_rock, rook_move_during_rock, players);
            Change_Others_Structures_during_Rock(Log, Captured_Pieces_and_Score, State_Of_RockandCheck, players, board);

            // free the memory
            Destroy_Move(king_move_during_rock);
            Destroy_Move(rook_move_during_rock);

            // since it's a rock, we can reset the tile pawn structure for the next turn
            Reset_Tiles_Pawn(Pawn_Move_State);
        }
        // en passant move
        else if (is_en_passant_done_IA == true){

            // we need to clear the piece that has been eaten by the en passant on the board, before making the move, because we need the initial position of the pawn to know where to clear the piece
            Clear_En_Passant_Piece(move, board, Pawn_Move_State);
            
            // making the move and updating the parameters others than the log, to keep track of the state of the game
            Make_Move(board, move, players);
            Change_Others_Structures(Log, Captured_Pieces_and_Score, State_Of_RockandCheck, players, board);
            
            // en passant mean that we can reset the tile pawn structure for the next turn
            Reset_Tiles_Pawn(Pawn_Move_State);
        }
        // classic move
        else {
            // we need to file the tile pawn structure for the next turn, before making the move, because we need the initial position of the pawn to know if it can move two squares
            Fill_Tile_Pawn(move, board, Pawn_Move_State);

            // making the move and updating the parameters others than the log, to keep track of the state of the game
            Make_Move(board, move, players);
            Change_Others_Structures(Log, Captured_Pieces_and_Score, State_Of_RockandCheck, players, board);
        }
        // changing the player that is playing is included in the Make_Move function
    }

    // now we need to do the pawn promotion for the IA
    if (is_IA_pawn_promotion_happening == true){
        Make_Pawn_Promotion_for_IA(move, board, Log, level_IA);
        type_IA_promoted_pawn = board[move->destination_row][move->destination_col]->type;
        Log->Move_Log[Log->actual_size-1]->type_of_pawn_promoted = type_IA_promoted_pawn;
    }

    // adding the board to the board log
    Move_Log_array_MESSAGE_TYPE adding_board_to_board_log_IA = Add_Board_at_Last_Index_in_Array(Log_Board, board);
    if (adding_board_to_board_log_IA != LOG_LIST_SUCCESS){
        printf("Error: the log is full\n");
    }

}


int Random_Int(int min, int max) {
    return min + rand() % (max - min + 1);
}


void Make_Pawn_Promotion_for_IA(Move* move, Piece*** board, Move_Log_array* Log, int level_IA){
     // a level EASY IA will play a random move
    if (level_IA == EASY){
        int random_piece = Random_Int(1, 4);
        switch (random_piece){
            case 1:
                board[move->destination_row][move->destination_col]->type = QUEEN;
                break;
            case 2:
                board[move->destination_row][move->destination_col]->type = ROOK;
                break;
            case 3:
                board[move->destination_row][move->destination_col]->type = BISHOP;
                break;
            case 4:
                board[move->destination_row][move->destination_col]->type = KNIGHT;
                break;
        }
    }

    // a level MEDIUM IA will play a random move, but will try to capture a piece if it can
    if (level_IA == MEDIUM){
        // this level suppose that making a queen will be the best thing to do
        board[move->destination_row][move->destination_col]->type = QUEEN;
    }

    // a level HARD is still to be implemented
    if (level_IA == HARD){
        // here it might depend if we treathe a king, if we can take more than one piece by making a fork, …
        // it's bewteen a queen and a knight
        // we take the knight if it can fork the king and another piece, fork two pieces without being taken without losses
        if (Can_Fork_Knight_Promotion(board, move->destination_row, move->destination_col) == true){
            board[move->destination_row][move->destination_col]->type = KNIGHT;
        }
        else{
            board[move->destination_row][move->destination_col]->type = QUEEN;
        }
    }
}


bool Can_Fork_Knight_Promotion(Piece*** board, int row, int col){

    if (Is_Case_threatened(board[row][col]->color, row, col, board) == true){
        return false;
    }
    int number_of_pieces_threatened_by_possible_knight = 0;
    // going through all the destination possible for the knight

    // going up (2 cases) and right (1 case)
    if (row - 2 >= 0 && col + 1 < 8){
        // if we have a piece of the other color at the destination, we threaten it
        if (board[row - 2][col + 1]->color != board[row][col]->color && board[row - 2][col + 1]->type != NOTHING){
            number_of_pieces_threatened_by_possible_knight++;
        }
    }
    // going up (1 case) and right (2 cases)
    if (row - 1 >= 0 && col + 2 < 8){
        // if we have a piece of the other color at the destination, we threaten it
        if (board[row - 1][col + 2]->color != board[row][col]->color && board[row - 1][col + 2]->type != NOTHING){
            number_of_pieces_threatened_by_possible_knight++;
        }
    }
    // going up (1 case) and left (2 cases)
    if (row - 1 >= 0 && col - 2 >= 0){
        // if we have a piece of the other color at the destination, we threaten it
        if (board[row - 1][col - 2]->color != board[row][col]->color && board[row - 1][col - 2]->type != NOTHING){
            number_of_pieces_threatened_by_possible_knight++;
        }
    }
    // going up (2 cases) and left (1 case)
    if (row - 2 >= 0 && col - 1 >= 0){
        // if we have a piece of the other color at the destination, we threaten it
        if (board[row - 2][col - 1]->color != board[row][col]->color && board[row - 2][col - 1]->type != NOTHING){
            number_of_pieces_threatened_by_possible_knight++;
        }
    }
    // going down (2 cases) and right (1 case)
    if (row + 2 < 8 && col + 1 < 8){
        // if we have a piece of the other color at the destination, we threaten it
        if (board[row + 2][col + 1]->color != board[row][col]->color && board[row + 2][col + 1]->type != NOTHING){
            number_of_pieces_threatened_by_possible_knight++;
        }
    }
    // going down (1 case) and right (2 cases)
    if (row + 1 < 8 && col + 2 < 8){
        // if we have a piece of the other color at the destination, we threaten it
        if (board[row + 1][col + 2]->color != board[row][col]->color && board[row + 1][col + 2]->type != NOTHING){
            number_of_pieces_threatened_by_possible_knight++;
        }
    }
    // going down (1 case) and left (2 cases)
    if (row + 1 < 8 && col - 2 >= 0){
        // if we have a piece of the other color at the destination, we threaten it
        if (board[row + 1][col - 2]->color != board[row][col]->color && board[row + 1][col - 2]->type != NOTHING){
            number_of_pieces_threatened_by_possible_knight++;
        }
    }
    // going down (2 cases) and left (1 case)
    if (row + 2 < 8 && col - 1 >= 0){
        // if we have a piece of the other color at the destination, we threaten it
        if (board[row + 2][col - 1]->color != board[row][col]->color && board[row + 2][col - 1]->type != NOTHING){
            number_of_pieces_threatened_by_possible_knight++;
        }
    }

    // if we threaten at least two pieces, we can fork them
    if (number_of_pieces_threatened_by_possible_knight >= 2){
        return true; // here it's a basic idea but it doesn't take into account the fact that moving our promotted knight can be dangerous for our king, we take the principle that our king is far from the promotion area
    }

    // if we don't threaten at least two pieces, we can't fork them
    return false;
}


void Undo_Last_Move(Piece*** board, Move_Log_array* log, Board_Log_array* log_board, Captured_Piece_and_Score* captured_piece_and_score, State_Of_Rock_and_Check* state_of_rock_and_check, Players* players, Tiles_Pawn* Pawn_Move_State){

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
            state_of_rock_and_check->is_black_king_checked = false;
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
            state_of_rock_and_check->is_white_king_checked = false;
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
    // if a place has been captured before, we decrease the sizes of the array we want depending on the log parameters
    // and udpate the score 
    if (log->Move_Log[log->actual_size-1]->taken_piece_type != NOTHING){
        // if the piece taken is white 
        if (log->Move_Log[log->actual_size-1]->taken_piece_color == WHITE){
            captured_piece_and_score->number_of_white_pieces_captured = captured_piece_and_score->number_of_white_pieces_captured - 1;
        }
        // if the piece taken is black
        else if (log->Move_Log[log->actual_size-1]->taken_piece_color == BLACK){
            captured_piece_and_score->number_of_black_pieces_captured = captured_piece_and_score->number_of_black_pieces_captured - 1;
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
    
    // if we supress the last move that was done, we need to change the players that is playing
    Change_Players_that_is_Playing(players);

    // we suppress the last element in the log by decreasing its actual size
    log->actual_size=log->actual_size-1;
    log_board->actual_size = log_board->actual_size - 1;
    
}


int Is_Check_Mate(int color, Piece*** board_init, State_Of_Rock_and_Check* State_Of_Rock_and_Check_init, Move_Log_array* Move_Log_init, Board_Log_array* Board_Log_init, Tiles_Pawn* Pawn_Move_State_init, Captured_Piece_and_Score* Captured_Pieces_and_Score_init, Players* players_init, int type_promoted_pawn){


    // getting a number of moves posssible for the given color in the current situation of the game 
    bool are_they_moves_possible = Are_They_Possibles_Moves(color, board_init, State_Of_Rock_and_Check_init, Move_Log_init, Board_Log_init, Pawn_Move_State_init, Captured_Pieces_and_Score_init, players_init, type_promoted_pawn);

    // if the king is not checked
    if (Is_Check(color, board_init) == false){
        // if no move is possible on the board for the given color, then it's a stalemate (DRAW)
        if (are_they_moves_possible == false){
            return DRAW;
        }
        else if (are_they_moves_possible == true){
            return NO_CHECK;
        }
    }
    // if the king is checked, we need to see if it's a check mate 
    else if (Is_Check(color, board_init) == true){
        // if no move is possible on the board for the given color, then it's a check mate
        if (are_they_moves_possible == false){
            if (color == WHITE){
                return WHITE_CHECKMATE;
            }
            else if (color == BLACK){
                return BLACK_CHECKMATE;
            }
        }
        // if a move is possible, then it's only a check
        else if (are_they_moves_possible == true){
            return NO_CHECK_MATE;
        }
    }

    // return a default value
    return NO_CHECK;
}


bool Are_They_Possibles_Moves(int color, Piece*** board_init, State_Of_Rock_and_Check* State_Of_Rock_and_Check_init, Move_Log_array* Move_Log_init, Board_Log_array* Board_Log_init, Tiles_Pawn* Pawn_Move_State_init, Captured_Piece_and_Score* Captured_Pieces_and_Score_init, Players* players_init, int type_promoted_pawn){

    // creating a copy of each structure to be able to modify them without changing the original ones
    Piece*** board = Create_Copy_Board(board_init);
    
    State_Of_Rock_and_Check* State_Of_Rock_and_Check = Copy_State_Of_Rock_and_Check(State_Of_Rock_and_Check_init);
    
    Move_Log_array* Move_Log = Copy_Move_Log_array(Move_Log_init);

    Board_Log_array* Board_Log = Create_Copy_Board_Log(Board_Log_init);
    
    Tiles_Pawn* Pawn_Move_State = Copy_Tiles_Pawn(Pawn_Move_State_init);
    
    Captured_Piece_and_Score* Captured_Pieces_and_Score = Copy_Captured_Piece_and_Score(Captured_Pieces_and_Score_init);
    
    Players* players = Copy_Players(players_init);

    // Creating a move
    Move* move_possible = Create_Move(0, 0, 0, 0);

    // going through all the possible moves 
    for (int i=0; i<BOARD_SIZE; i++){
        for (int j=0; j<BOARD_SIZE; j++){
            // if the piece is of the given color
            if (board[i][j]->color == color){
                for (int k=0; k<BOARD_SIZE; k++){
                    for (int l=0; l<BOARD_SIZE; l++){
                        // the move now is like that
                        Change_Move(move_possible, i, j, k, l);

                        // getting if a rock was done
                        int is_rock_possible_type = Is_Rock_Possible(move_possible, State_Of_Rock_and_Check, board);
                        // getting if an en passant was done
                        bool is_en_passant_done = Is_En_Passant_Possible(move_possible, board, Pawn_Move_State);
                        int en_passant_type = NO_EN_PASSANT;
                        // if we have an en passant, we need to get the corresponding int
                        if (is_en_passant_done == true){
                            en_passant_type = EN_PASSANT;
                        }
                        
                        // if a piece is taken, we need to know what type and what color it is, in case we want to undo it later, we can track the piece that has been taken to reinstall it on the board
                        int piece_taken_type = NOTHING;
                        int piece_taken_color = NO_COLOR;
                        // if a move is valid, then we can also ask if a piece is taken, and if it's the case, we can know what type and what color it is
                        if (Will_Capture(move_possible, board) == true && Is_Move_Valid(move_possible, board, State_Of_Rock_and_Check, Pawn_Move_State) == true){
                            piece_taken_type = board[move_possible->destination_row][move_possible->destination_col]->type;
                            piece_taken_color = board[move_possible->destination_row][move_possible->destination_col]->color;
                        }
                        // udpating the datas concerning the en passant move, so the log can be able to undo it, because techincally, the piece is not taken, it's just removed from the board
                        if (is_en_passant_done == true){
                            if (board[move_possible->previous_row][move_possible->previous_col]->color == WHITE){
                                piece_taken_type = PAWN;
                                piece_taken_color = BLACK;
                            }
                            else if (board[move_possible->previous_row][move_possible->previous_col]->color == BLACK){
                                piece_taken_type = PAWN;
                                piece_taken_color = WHITE;
                            }
                        }

                        // concerning the pawn promotion
                        bool is_pawn_promotion_happening = Is_Pawn_Promotion_Possible(move_possible, board);
                        int color_promoted_pawn = NO_COLOR;
                        int type_promoted_pawn_real = NOTHING;
                        if (is_pawn_promotion_happening == true){
                            color_promoted_pawn = board[move_possible->previous_row][move_possible->previous_col]->color;
                            type_promoted_pawn_real = QUEEN;
                        }

                        // getting the check state of the game before the move is made 
                        bool check_state_before_move_bool = Is_Check(players->color_player_that_is_playing, board);
                        int check_state_before_move = NO_COLOR;
                        if (check_state_before_move_bool == true){
                            if (players->color_player_that_is_playing == WHITE){
                                check_state_before_move = WHITE_CHECK;
                            }
                            else if (players->color_player_that_is_playing == BLACK){
                                check_state_before_move = BLACK_CHECK;
                            }
                        }

                        // getting if the move is about a pawn 
                        bool pawn_move_done = false;
                        if (board[move_possible->previous_row][move_possible->previous_col]->type == PAWN){
                            pawn_move_done = true;
                        }

                        if (Is_Move_Valid(move_possible, board, State_Of_Rock_and_Check, Pawn_Move_State) == true){

                            // making the move log update that is crucial for Make_Move to work since we go searching for an index actual_size-1 and only adding an element to Move_Log will make actual_size-1 positive, not to have a segmentation fault
                            // but only a valid move will be added to the log
                            Move_Log_Element* element = Create_Element_Move_Log();
                            Change_Move_Log_Element(element, move_possible->previous_row, move_possible->previous_col, move_possible->destination_row, move_possible->destination_col, check_state_before_move, piece_taken_type, piece_taken_color, is_rock_possible_type, en_passant_type, color_promoted_pawn, type_promoted_pawn_real, pawn_move_done);
                            // printf("en passant done ? : %d\n", element->en_passant_type_done);
                            // printf("rock type : %d\n",element->rock_type);
                            Move_Log_array_MESSAGE_TYPE message = Add_Element_to_the_end_of_Move_Log_array(Move_Log, element);
                            if (message != LOG_LIST_SUCCESS){
                                printf("Error: the log is full\n");
                            }

                            Destroy_Move_Log_Element(element);

                            // trying to make the rock effective by getting the real moves linked to the rock that has been made
                            if (is_rock_possible_type != NO_ROCK){
                                Move* king_move_during_rock=Create_King_Move_during_Rock(move_possible, board, State_Of_Rock_and_Check);
                                Move* rook_move_during_rock=Create_Rook_Move_during_Rock(move_possible, board, State_Of_Rock_and_Check);
                                // we need to make the two moves, the king and the rock, and put the places there were to zero 
                                // but also udpating the parameters others than the log, to keep track of the state of the game
                                Make_Rock_Move(board, move_possible, king_move_during_rock, rook_move_during_rock, players);
                                Change_Others_Structures_during_Rock(Move_Log, Captured_Pieces_and_Score, State_Of_Rock_and_Check, players, board);

                                // free the memory
                                Destroy_Move(king_move_during_rock);
                                Destroy_Move(rook_move_during_rock);

                                // since it's a rock, we can reset the tile pawn structure for the next turn
                                Reset_Tiles_Pawn(Pawn_Move_State);

                            }
                            // en passant move
                            else if (is_en_passant_done == true){

                                // we need to clear the piece that has been eaten by the en passant on the board, before making the move, because we need the initial position of the pawn to know where to clear the piece
                                Clear_En_Passant_Piece(move_possible, board, Pawn_Move_State);
                                
                                // making the move and updating the parameters others than the log, to keep track of the state of the game
                                Make_Move(board, move_possible, players);
                                Change_Others_Structures(Move_Log, Captured_Pieces_and_Score, State_Of_Rock_and_Check, players, board);
                                
                                // en passant mean that we can reset the tile pawn structure for the next turn
                                Reset_Tiles_Pawn(Pawn_Move_State);

                            }
                            // classic move
                            else if (is_rock_possible_type == NO_ROCK && is_en_passant_done == false){
                                // we need to file the tile pawn structure for the next turn, before making the move, because we need the initial position of the pawn to know if it can move two squares
                                Fill_Tile_Pawn(move_possible, board, Pawn_Move_State);

                                // making the move and updating the parameters others than the log, to keep track of the state of the game
                                Make_Move(board, move_possible, players);
                                Change_Others_Structures(Move_Log, Captured_Pieces_and_Score, State_Of_Rock_and_Check, players, board);

                            }
                            // changing the player that is playing is included in the Make_Move function

                            // adding the board to the board log
                            Move_Log_array_MESSAGE_TYPE adding_board_to_board_log = Add_Board_at_Last_Index_in_Array(Board_Log, board);
                            if (adding_board_to_board_log != LOG_LIST_SUCCESS){
                                printf("Error: the log is full\n");
                            }

                            // get the check state of the game
                            bool check_state = Is_Check(color, board);
                            // if the king is not checked, we can make the move
                            if (check_state == false){

                                // free the memory
                                Destroy_Move(move_possible);
                                Clear_Board(board);
                                Destroy_State_Of_Rock_and_Check(State_Of_Rock_and_Check);
                                Destroy_Move_Log_array(Move_Log);
                                Destroy_Board_Log(Board_Log);
                                Destroy_Tiles_Pawn(Pawn_Move_State);
                                Destroy_Captured_Piece_and_Score(Captured_Pieces_and_Score, Captured_Pieces_and_Score->max_number_of_pieces);
                                Destroy_Players(players);

                                return true;
                            }
                            // we need to undo the move since it's just a test
                            Undo_Last_Move(board, Move_Log, Board_Log, Captured_Pieces_and_Score, State_Of_Rock_and_Check, players, Pawn_Move_State);

                        }
                    }
                }
            }
        }
    }

    // free the memory
    Destroy_Move(move_possible);
    Clear_Board(board);
    Destroy_State_Of_Rock_and_Check(State_Of_Rock_and_Check);
    Destroy_Move_Log_array(Move_Log);
    Destroy_Board_Log(Board_Log);
    Destroy_Tiles_Pawn(Pawn_Move_State);
    Destroy_Captured_Piece_and_Score(Captured_Pieces_and_Score, Captured_Pieces_and_Score->max_number_of_pieces);
    Destroy_Players(players);

    // returning false if no valid move was found
    return false;
}


Move** Get_Valid_Moves(int* number_of_moves, int color_playing, Piece*** board_init, State_Of_Rock_and_Check* State_Of_Rock_and_Check_init, Move_Log_array* Move_Log_init, Board_Log_array* Board_Log_init, Tiles_Pawn* Pawn_Move_State_init, Captured_Piece_and_Score* Captured_Pieces_and_Score_init, Players* players_init){

    int max_number_of_moves = 8*8*8*8; // this represents the maximum number of moves possible, but we will return an array of moves that will be smaller than this number, I could have optimized this by getting the number of possible moves before, it's more memory efficient but costs more time
    // getting an array of moves that will be returned
    Move** valid_moves = (Move**)malloc(max_number_of_moves*sizeof(Move*));
    // if the memory allocation failed
    if (valid_moves == NULL){
        printf("Error: memory allocation failed\n");
        exit(1);
    }
    for (int i=0; i<max_number_of_moves; i++){
        valid_moves[i] = Create_Move(-1, -1, -1, -1);
        // if the memory allocation failed
        if (valid_moves[i] == NULL){
            printf("Error: memory allocation failed\n");
            exit(1);
        }
    }

    // creating a copy of each structure to be able to modify them without changing the original ones
    Piece*** board = Create_Copy_Board(board_init);
    
    State_Of_Rock_and_Check* State_Of_Rock_and_Check = Copy_State_Of_Rock_and_Check(State_Of_Rock_and_Check_init);
    
    Move_Log_array* Move_Log = Copy_Move_Log_array(Move_Log_init);

    Board_Log_array* Board_Log = Create_Copy_Board_Log(Board_Log_init);
    
    Tiles_Pawn* Pawn_Move_State = Copy_Tiles_Pawn(Pawn_Move_State_init);
    
    Captured_Piece_and_Score* Captured_Pieces_and_Score = Copy_Captured_Piece_and_Score(Captured_Pieces_and_Score_init);
    
    Players* players = Copy_Players(players_init);

    // creating the temporary move
    Move* move_temp = Create_Move(-1, -1, -1, -1);
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            // we check if it's a valid starting position for the piece
            if (board[i][j]->type != NOTHING && board[i][j]->color == color_playing){
                // going through the destination position of the IA pieces
                for (int k = 0; k < 8; k++){
                    for (int l = 0; l < 8; l++){
                        Change_Move(move_temp, i, j, k, l);
                        // if the move is valid, we add it to the array of valid moves

                        // getting if a rock was done
                        int is_rock_possible_type = Is_Rock_Possible(move_temp, State_Of_Rock_and_Check, board);
                        // getting if an en passant was done
                        bool is_en_passant_done = Is_En_Passant_Possible(move_temp, board, Pawn_Move_State);
                        int en_passant_type = NO_EN_PASSANT;
                        // if we have an en passant, we need to get the corresponding int
                        if (is_en_passant_done == true){
                            en_passant_type = EN_PASSANT;
                        }
                        
                        // if a piece is taken, we need to know what type and what color it is, in case we want to undo it later, we can track the piece that has been taken to reinstall it on the board
                        int piece_taken_type = NOTHING;
                        int piece_taken_color = NO_COLOR;
                        // if a move is valid, then we can also ask if a piece is taken, and if it's the case, we can know what type and what color it is
                        if (Will_Capture(move_temp, board) == true && Is_Move_Valid(move_temp, board, State_Of_Rock_and_Check, Pawn_Move_State) == true){
                            piece_taken_type = board[move_temp->destination_row][move_temp->destination_col]->type;
                            piece_taken_color = board[move_temp->destination_row][move_temp->destination_col]->color;
                        }
                        // udpating the datas concerning the en passant move, so the log can be able to undo it, because techincally, the piece is not taken, it's just removed from the board
                        if (is_en_passant_done == true){
                            if (board[move_temp->previous_row][move_temp->previous_col]->color == WHITE){
                                piece_taken_type = PAWN;
                                piece_taken_color = BLACK;
                            }
                            else if (board[move_temp->previous_row][move_temp->previous_col]->color == BLACK){
                                piece_taken_type = PAWN;
                                piece_taken_color = WHITE;
                            }
                        }

                        // concerning the pawn promotion
                        bool is_pawn_promotion_happening = Is_Pawn_Promotion_Possible(move_temp, board);
                        int color_promoted_pawn = NO_COLOR;
                        int type_promoted_pawn_real = NOTHING;
                        if (is_pawn_promotion_happening == true){
                            color_promoted_pawn = board[move_temp->previous_row][move_temp->previous_col]->color;
                            type_promoted_pawn_real = QUEEN;
                        }

                        // getting the check state of the game before the move is made 
                        bool check_state_before_move_bool = Is_Check(players->color_player_that_is_playing, board);
                        int check_state_before_move = NO_COLOR;
                        if (check_state_before_move_bool == true){
                            if (players->color_player_that_is_playing == WHITE){
                                check_state_before_move = WHITE_CHECK;
                            }
                            else if (players->color_player_that_is_playing == BLACK){
                                check_state_before_move = BLACK_CHECK;
                            }
                        }

                        // getting if the move is about a pawn 
                        bool pawn_move_done = false;
                        if (board[move_temp->previous_row][move_temp->previous_col]->type == PAWN){
                            pawn_move_done = true;
                        }

                        if (Is_Move_Valid(move_temp, board, State_Of_Rock_and_Check, Pawn_Move_State) == true){

                            // making the move log update that is crucial for Make_Move to work since we go searching for an index actual_size-1 and only adding an element to Move_Log will make actual_size-1 positive, not to have a segmentation fault
                            // but only a valid move will be added to the log
                            Move_Log_Element* element = Create_Element_Move_Log();
                            Change_Move_Log_Element(element, move_temp->previous_row, move_temp->previous_col, move_temp->destination_row, move_temp->destination_col, check_state_before_move, piece_taken_type, piece_taken_color, is_rock_possible_type, en_passant_type, color_promoted_pawn, type_promoted_pawn_real, pawn_move_done);
                            // printf("en passant done ? : %d\n", element->en_passant_type_done);
                            // printf("rock type : %d\n",element->rock_type);
                            Move_Log_array_MESSAGE_TYPE message = Add_Element_to_the_end_of_Move_Log_array(Move_Log, element);
                            if (message != LOG_LIST_SUCCESS){
                                printf("Error: the log is full\n");
                            }

                            Destroy_Move_Log_Element(element);

                            // trying to make the rock effective by getting the real moves linked to the rock that has been made
                            if (is_rock_possible_type != NO_ROCK){
                                Move* king_move_during_rock=Create_King_Move_during_Rock(move_temp, board, State_Of_Rock_and_Check);
                                Move* rook_move_during_rock=Create_Rook_Move_during_Rock(move_temp, board, State_Of_Rock_and_Check);
                                // we need to make the two moves, the king and the rock, and put the places there were to zero 
                                // but also udpating the parameters others than the log, to keep track of the state of the game
                                Make_Rock_Move(board, move_temp, king_move_during_rock, rook_move_during_rock, players);
                                Change_Others_Structures_during_Rock(Move_Log, Captured_Pieces_and_Score, State_Of_Rock_and_Check, players, board);

                                // free the memory
                                Destroy_Move(king_move_during_rock);
                                Destroy_Move(rook_move_during_rock);

                                // since it's a rock, we can reset the tile pawn structure for the next turn
                                Reset_Tiles_Pawn(Pawn_Move_State);

                            }
                            // en passant move
                            else if (is_en_passant_done == true){

                                // we need to clear the piece that has been eaten by the en passant on the board, before making the move, because we need the initial position of the pawn to know where to clear the piece
                                Clear_En_Passant_Piece(move_temp, board, Pawn_Move_State);
                                
                                // making the move and updating the parameters others than the log, to keep track of the state of the game
                                Make_Move(board, move_temp, players);
                                Change_Others_Structures(Move_Log, Captured_Pieces_and_Score, State_Of_Rock_and_Check, players, board);
                                
                                // en passant mean that we can reset the tile pawn structure for the next turn
                                Reset_Tiles_Pawn(Pawn_Move_State);

                            }
                            // classic move
                            else if (is_rock_possible_type == NO_ROCK && is_en_passant_done == false){
                                // we need to file the tile pawn structure for the next turn, before making the move, because we need the initial position of the pawn to know if it can move two squares
                                Fill_Tile_Pawn(move_temp, board, Pawn_Move_State);

                                // making the move and updating the parameters others than the log, to keep track of the state of the game
                                Make_Move(board, move_temp, players);
                                Change_Others_Structures(Move_Log, Captured_Pieces_and_Score, State_Of_Rock_and_Check, players, board);

                            }
                            // changing the player that is playing is included in the Make_Move function

                            // adding the board to the board log
                            Move_Log_array_MESSAGE_TYPE adding_board_to_board_log = Add_Board_at_Last_Index_in_Array(Board_Log, board);
                            if (adding_board_to_board_log != LOG_LIST_SUCCESS){
                                printf("Error: the log is full\n");
                            }

                            // get the check state of the game
                            bool check_state = Is_Check(color_playing, board);
                            // if the king is not checked, we can make the move
                            if (check_state == false){
                                
                                // adding the move to the array of valid moves
                                valid_moves[*number_of_moves]->previous_row = move_temp->previous_row;
                                valid_moves[*number_of_moves]->previous_col = move_temp->previous_col;
                                valid_moves[*number_of_moves]->destination_row = move_temp->destination_row;
                                valid_moves[*number_of_moves]->destination_col = move_temp->destination_col;
                                *number_of_moves = *number_of_moves + 1;
                                
                            }
                            // we need to undo the move since it's just a test
                            Undo_Last_Move(board, Move_Log, Board_Log, Captured_Pieces_and_Score, State_Of_Rock_and_Check, players, Pawn_Move_State);

                        }                        

                    }
                }
            }
        }
    }
    // destroying the temporary move
    Destroy_Move(move_temp);
    // free the memory
    Clear_Board(board);
    Destroy_State_Of_Rock_and_Check(State_Of_Rock_and_Check);
    Destroy_Move_Log_array(Move_Log);
    Destroy_Board_Log(Board_Log);
    Destroy_Tiles_Pawn(Pawn_Move_State);
    Destroy_Captured_Piece_and_Score(Captured_Pieces_and_Score, Captured_Pieces_and_Score->max_number_of_pieces);
    Destroy_Players(players);
    // returning the array of valid moves
    return valid_moves;
}


bool Are_Board_Equal(Piece*** board1, Piece*** board2){

    // going through all the tiles of the board
    for (int i=0; i<BOARD_SIZE; i++){
        for (int j=0; j<BOARD_SIZE; j++){
            // if the type or the color of the piece are different, then the boards are not equal
            if (board1[i][j]->type != board2[i][j]->type || board1[i][j]->color != board2[i][j]->color){
                return false;
            }
        }
    }

    // if all the tiles are the same, then the boards are equal
    return true;

}


bool Is_Draw_Forced_By_Log(Move_Log_array* move_log, Board_Log_array* board_log_array){

    // we first need to look if during the last 50 moves, there was no pawn move or no piece taken
    bool is_draw_forced_by_50_moves_rule = Is_Draw_Forced_By_50_Moves_Rule(move_log);

    // then we need to look if during the last 3 moves, the same position was repeated 3 times
    bool is_draw_forced_by_3_moves_rule = Is_Draw_Forced_By_3_Repitition_Rule(board_log_array);

    // if one of the two rules is forcing a draw, then we return true
    if (is_draw_forced_by_50_moves_rule == true || is_draw_forced_by_3_moves_rule == true){
        return true;
    }
    // otherwise, we return false
    return false;
}


bool Is_Draw_Forced_By_50_Moves_Rule(Move_Log_array* log){

    // the last 50 moves for each player are stored in the log, so we need to look at the last 100 moves
    if (log->actual_size < 100){
        return false;
    }

    // we need to look at the last 100 moves, and see if there was no piece taken
    for (int i=log->actual_size-100; i<log->actual_size; i++){
        if (log->Move_Log[i]->taken_piece_type != NOTHING || log->Move_Log[i]->pawn_move_made == true){
            return false;
        }
    }

    // if no piece was taken during the last 50 moves for each players, then we return true
    return true;
}


bool Is_Draw_Forced_By_3_Repitition_Rule(Board_Log_array* board_log_array){

    // the last 3 moves are stored in the log, so we need to look at the last 3 moves
    if (board_log_array->actual_size < 3){
        return false;
    }

    // we need to look at each board we have gone through and see if the same position was repeated 3 times
    for (int i=0; i<board_log_array->actual_size-2; i++){
        for (int j=i+1; j<board_log_array->actual_size-1; j++){
            for (int k=j+1; k<board_log_array->actual_size; k++){
                // if the same position was repeated 3 times, then we return true
                if (Are_Board_Equal(board_log_array->board_log[i], board_log_array->board_log[j]) == true && Are_Board_Equal(board_log_array->board_log[j], board_log_array->board_log[k]) == true){
                    return true;
                }
            }
        }
    }

    // if the same position was repeated 3 times, then we return true
    return false;
}