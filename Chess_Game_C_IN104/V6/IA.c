#include "IA.h"


#define DEPTH 2
#define CHECKMATE 1000
#define STALEMATE 0


// arrays that defines the preferencial position of each type of piece
int knightScores[BOARD_SIZE][BOARD_SIZE] = {{0, 1, 2, 2, 2, 2, 1, 0},
                                            {1, 2, 3, 3, 3, 3, 2, 1},
                                            {2, 3, 4, 4, 4, 4, 3, 2},
                                            {2, 3, 4, 5, 5, 4, 3, 2},
                                            {2, 3, 4, 5, 5, 4, 3, 2},
                                            {2, 3, 4, 4, 4, 4, 3, 2},
                                            {1, 2, 3, 3, 3, 3, 2, 1},
                                            {0, 1, 2, 2, 2, 2, 1, 0}};

int whiteBishopScores[BOARD_SIZE][BOARD_SIZE] = {{0, 1, 1, 1, 1, 1, 1, 0},
                                                {1, 2, 2, 2, 2, 2, 2, 1},
                                                {1, 2, 3, 4, 4, 3, 2, 1},
                                                {1, 3, 3, 4, 4, 3, 3, 1},
                                                {1, 2, 5, 4, 4, 5, 2, 1},
                                                {1, 4, 4, 4, 4, 4, 4, 1},
                                                {1, 4, 2, 2, 2, 2, 4, 1},
                                                {2, 1, 1, 1, 1, 1, 1, 2}};

int blackBishopScores[BOARD_SIZE][BOARD_SIZE] = {{2, 1, 1, 1, 1, 1, 1, 2},
                                                {1, 4, 2, 2, 2, 2, 4, 1},
                                                {1, 4, 4, 4, 4, 4, 4, 1},
                                                {1, 2, 5, 4, 4, 5, 2, 1},
                                                {1, 3, 3, 4, 4, 3, 3, 1},
                                                {1, 2, 3, 4, 4, 3, 2, 1},
                                                {1, 2, 2, 2, 2, 2, 2, 1},
                                                {0, 1, 1, 1, 1, 1, 1, 0}};

int whiteRookScores[BOARD_SIZE][BOARD_SIZE] = {{2, 2, 2, 2, 2, 2, 2, 2},
                                                {3, 5, 5, 5, 5, 5, 5, 3},
                                                {0, 1, 1, 1, 1, 1, 1, 0},
                                                {0, 1, 1, 1, 1, 1, 1, 0},
                                                {0, 1, 1, 1, 1, 1, 1, 0},
                                                {0, 1, 1, 1, 1, 1, 1, 0},
                                                {0, 1, 1, 1, 1, 1, 1, 0},
                                                {1, 1, 2, 3, 3, 2, 1, 1}};

int blackRookScores[BOARD_SIZE][BOARD_SIZE] = {{1, 1, 2, 3, 3, 2, 1, 1},
                                                {0, 1, 1, 1, 1, 1, 1, 0},
                                                {0, 1, 1, 1, 1, 1, 1, 0},
                                                {0, 1, 1, 1, 1, 1, 1, 0},
                                                {0, 1, 1, 1, 1, 1, 1, 0},
                                                {0, 1, 1, 1, 1, 1, 1, 0},
                                                {3, 5, 5, 5, 5, 5, 5, 3},
                                                {2, 2, 2, 2, 2, 2, 2, 2}};

int whiteQueenScores[BOARD_SIZE][BOARD_SIZE] = {{0, 1, 1, 2, 2, 1, 1, 0},
                                                {1, 3, 3, 3, 3, 3, 3, 1},
                                                {1, 3, 5, 5, 5, 5, 3, 1},
                                                {2, 3, 5, 5, 5, 5, 3, 2},
                                                {3, 3, 5, 5, 5, 5, 3, 2},
                                                {1, 5, 5, 5, 5, 5, 3, 1},
                                                {1, 3, 5, 5, 5, 3, 3, 1},
                                                {0, 1, 1, 0, 0, 1, 1, 0}};

int blackQueenScores[BOARD_SIZE][BOARD_SIZE] = {{0, 1, 1, 0, 0, 1, 1, 0},
                                                {1, 3, 5, 5, 5, 3, 3, 1},
                                                {1, 5, 5, 5, 5, 5, 3, 1},
                                                {3, 3, 5, 5, 5, 5, 3, 2},
                                                {2, 3, 5, 5, 5, 5, 3, 2},
                                                {1, 3, 5, 5, 5, 5, 3, 1},
                                                {1, 3, 3, 3, 3, 3, 3, 1},
                                                {0, 1, 1, 2, 2, 1, 1, 0}};

int whiteKingScores[BOARD_SIZE][BOARD_SIZE] = {{2, 1, 1, 0, 0, 1, 2, 2},
                                                {2, 1, 1, 0, 0, 1, 2, 2},
                                                {3, 2, 2, 0, 0, 2, 2, 3},
                                                {3, 2, 2, 0, 0, 2, 2, 3},
                                                {3, 3, 2, 1, 1, 2, 3, 3},
                                                {3, 3, 3, 3, 3, 3, 3, 3},
                                                {4, 4, 3, 3, 3, 3, 3, 3},
                                                {4, 5, 4, 3, 3, 4, 5, 4}};

int blackKingScores[BOARD_SIZE][BOARD_SIZE] = {{4, 5, 4, 3, 3, 4, 5, 4},
                                                {4, 4, 3, 3, 3, 3, 3, 3},
                                                {3, 3, 3, 3, 3, 3, 3, 3},
                                                {3, 3, 2, 1, 1, 2, 3, 3},
                                                {3, 2, 2, 0, 0, 2, 2, 3},
                                                {3, 2, 2, 0, 0, 2, 2, 3},
                                                {2, 1, 1, 0, 0, 1, 2, 2},
                                                {2, 1, 1, 0, 0, 1, 2, 2}};

int whitePawnScores[BOARD_SIZE][BOARD_SIZE] = {{1, 1, 1, 1, 1, 1, 1, 1},
                                                {5, 5, 5, 5, 5, 5, 5, 5},
                                                {2, 2, 3, 3, 3, 3, 2, 2},
                                                {2, 2, 2, 3, 3, 2, 2, 2},
                                                {2, 2, 2, 3, 3, 2, 2, 2},
                                                {1, 2, 0, 2, 2, 0, 2, 1},
                                                {1, 2, 2, 0, 0, 2, 2, 1},
                                                {1, 1, 1, 1, 1, 1, 1, 1}};

int blackPawnScores[BOARD_SIZE][BOARD_SIZE] = {{1, 1, 1, 1, 1, 1, 1, 1},
                                                {1, 2, 2, 0, 0, 2, 2, 1},
                                                {1, 2, 0, 2, 2, 0, 2, 1},
                                                {2, 2, 2, 3, 3, 2, 2, 2},
                                                {2, 2, 2, 3, 3, 2, 2, 2},
                                                {2, 2, 3, 3, 3, 3, 2, 2},
                                                {5, 5, 5, 5, 5, 5, 5, 5},
                                                {1, 1, 1, 1, 1, 1, 1, 1}};


int Evaluate_Board(Piece*** board){
 
    // getting a score of the board 
    // a positive score means that it's good for the white player
    // a negative score means that it's good for the black player
    int Score_Board = 0;
    for (int i=0; i< BOARD_SIZE; i++){
        for (int j=0; j< BOARD_SIZE; j++){
            // getting a score for each piece on the board
            // a piece will have a postion score if it's white, a negative one if it's black
            int piece_position_score = 0;
            // we want it to be different from nothing and king (there are of no interest to evaluate the board)
            if (board[i][j]->type != NOTHING){

                if (board[i][j]->color == WHITE){
                    switch (board[i][j]->type){
                        case PAWN:
                            piece_position_score = whitePawnScores[i][j];
                            break;
                        case KNIGHT:
                            piece_position_score = knightScores[i][j];
                            break;
                        case BISHOP:
                            piece_position_score = whiteBishopScores[i][j];
                            break;
                        case ROOK:
                            piece_position_score = whiteRookScores[i][j];
                            break;
                        case QUEEN:
                            piece_position_score = whiteQueenScores[i][j];
                            break;
                        case KING:
                            piece_position_score = whiteKingScores[i][j];
                            break;
                    }
                    Score_Board += board[i][j]->value*10 + piece_position_score;
                }
                else if (board[i][j]->color == BLACK){
                    switch (board[i][j]->type){
                        case PAWN:
                            piece_position_score = blackPawnScores[i][j];
                            break;
                        case KNIGHT:
                            piece_position_score = knightScores[i][j];
                            break;
                        case BISHOP:
                            piece_position_score = blackBishopScores[i][j];
                            break;
                        case ROOK:
                            piece_position_score = blackRookScores[i][j];
                            break;
                        case QUEEN:
                            piece_position_score = blackQueenScores[i][j];
                            break;
                        case KING:
                            piece_position_score = blackKingScores[i][j];
                            break;
                    }
                    Score_Board -= board[i][j]->value*10 + piece_position_score;
                }
            }
        }
    }
    return Score_Board;
}


int Nega_Max_Alpha_Beta_Search(Move* move, Piece*** board, Move_Log_array* Move_Log, Board_Log_array* Board_Log, State_Of_Rock_and_Check* state_of_rock_and_check, Tiles_Pawn* Pawn_Move_State, Captured_Piece_and_Score* Captured_Pieces_and_Score, Players* players, int depth, int alpha, int beta){
    
    if (depth == 0){
        // first version
        int turncolor = 0;
        if (players->color_player_that_is_playing == WHITE){
            turncolor = 1;
        }
        else if (players->color_player_that_is_playing == BLACK){
            turncolor = -1;
        }
        return turncolor * Evaluate_Board(board);
    }

    // getting the next valid moves
    int number_of_valid_moves = 0;
    Move** Valid_Moves = Get_Valid_Moves(&number_of_valid_moves, players->color_player_that_is_playing, board, state_of_rock_and_check, Move_Log, Board_Log, Pawn_Move_State, Captured_Pieces_and_Score, players);
    /*
    // printing all the valid moves for the player playing (there are correct)
    for (int i=0; i<number_of_valid_moves; i++){
        printf("Move %d : %d %d %d %d\n", i, Valid_Moves[i]->previous_row, Valid_Moves[i]->previous_col, Valid_Moves[i]->destination_row, Valid_Moves[i]->destination_col);
    }
    */

    // if there are no valid moves
    if (number_of_valid_moves == 0){
        // if the player is in check 
        if (Is_Check(players->color_player_that_is_playing, board) == true){
            // free the memory of the valid moves
            if (Valid_Moves != NULL){
                for (int i=0; i<8*8*8*8; i++){
                    Destroy_Move(Valid_Moves[i]);
                }
                free(Valid_Moves);
            }
            return -CHECKMATE;
        }
        // free the memory of the valid moves
        if (Valid_Moves != NULL){
            for (int i=0; i<8*8*8*8; i++){
                Destroy_Move(Valid_Moves[i]);
            }
            free(Valid_Moves);
        }
        return STALEMATE;
    }

    // going through all the valid moves
    for (int i=0; i<number_of_valid_moves; i++){

        // make the move on the board
        Make_IA_Global_Move_and_Udpate_structures(Valid_Moves[i], board, players, Move_Log, Board_Log, state_of_rock_and_check, Pawn_Move_State, Captured_Pieces_and_Score, players->color_player_that_is_playing, HARD);

        // recursive call
        int score = 0;
        int color_that_was_playing = NO_COLOR;
        if (players->color_player_that_is_playing == WHITE){
            color_that_was_playing = BLACK;
        }
        else if (players->color_player_that_is_playing == BLACK){
            color_that_was_playing = WHITE;
        }
        if (Is_Check(color_that_was_playing, board) == false){
            score = - Nega_Max_Alpha_Beta_Search(move, board, Move_Log, Board_Log, state_of_rock_and_check, Pawn_Move_State, Captured_Pieces_and_Score, players, depth - 1, -beta, -alpha);
            // printf("Score of the move (%d,%d) --> (%d,%d) : %d\n", Valid_Moves[i]->previous_row, Valid_Moves[i]->previous_col, Valid_Moves[i]->destination_row, Valid_Moves[i]->destination_col, score);
        }

        // Undo the last Move made 
        Undo_Last_Move(board, Move_Log, Board_Log, Captured_Pieces_and_Score, state_of_rock_and_check, players, Pawn_Move_State);

        if (score > alpha){
            alpha = score;
            if (depth == DEPTH){
                move->previous_row = Valid_Moves[i]->previous_row;
                move->previous_col = Valid_Moves[i]->previous_col;
                move->destination_row = Valid_Moves[i]->destination_row;
                move->destination_col = Valid_Moves[i]->destination_col;
                // printf("Move chosen : %d %d %d %d / of score : %d\n", move->previous_row, move->previous_col, move->destination_row, move->destination_col, score);
            }
        }
        if (score > beta){
            
            // free the memory of the valid moves
            if (Valid_Moves != NULL){
                for (int i=0; i<8*8*8*8; i++){
                    Destroy_Move(Valid_Moves[i]);
                }
                free(Valid_Moves);
            }

            // printf("score return : %d\n", beta);
            return beta;
        }

    }

    // free the memory of the valid moves
    if (Valid_Moves != NULL){
        for (int i=0; i<8*8*8*8; i++){
            Destroy_Move(Valid_Moves[i]);
        }
        free(Valid_Moves);
    }

    // printf("alpha return : %d\n", alpha);
    return alpha;
}


void IA_Play(Move* move, Piece*** board, int level, int IA_color, Move_Log_array* Move_Log, Board_Log_array* Board_Log, State_Of_Rock_and_Check* state_of_rock_and_check, Tiles_Pawn* Pawn_Move_State, Captured_Piece_and_Score* Captured_Pieces_and_Score, Players* players){
    
    // a level EASY IA will play a random move, but will try to capture a piece if it can (and don't make it self in check)
    if (level == EASY){
        bool is_move_correct = false;  
        // getting the random move 
        while (is_move_correct == false){
            move->previous_row = Random_Int(0, 7);
            move->previous_col = Random_Int(0, 7);
            move->destination_row = Random_Int(0, 7);
            move->destination_col = Random_Int(0, 7);
            if (Is_Move_Valid(move, board, state_of_rock_and_check, Pawn_Move_State) == true && board[move->previous_row][move->previous_col]->color == IA_color){
                is_move_correct = true;
            }
        }
        // creating the temporary move
        Move* move_temp = Create_Move(-1, -1, -1, -1);
        // integer to track the value of the piece captured
        int value_of_piece_captured = 0;
        // if a piece can be captured, the IA will capture it by changing the move accoordingly
        // going through the starting position of the IA pieces
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                // we check if it's a valid starting position for the piece
                if (board[i][j]->type != NOTHING && board[i][j]->color == IA_color){
                    // going through the destination position of the IA pieces
                    for (int k = 0; k < 8; k++){
                        for (int l = 0; l < 8; l++){
                            move_temp->previous_row = i;
                            move_temp->previous_col = j;
                            move_temp->destination_row = k;
                            move_temp->destination_col = l;
                            // here : a white piece of the IA color can capture a black piece
                            if (IA_color == WHITE && board[k][l]->color == BLACK && Is_Move_Valid(move_temp, board, state_of_rock_and_check, Pawn_Move_State) == true){
                                // the move need not to put the king in check
                                Make_IA_Global_Move_and_Udpate_structures(move_temp, board, players, Move_Log, Board_Log, state_of_rock_and_check, Pawn_Move_State, Captured_Pieces_and_Score, players->color_player_that_is_playing, MEDIUM);
                                // if after the move made by the IA, it's in check, we need to undo the move and make another one
                                int color_we_are_checking_IA = NO_COLOR;
                                if (players->color_player_that_is_playing == WHITE){
                                    color_we_are_checking_IA = BLACK;
                                }
                                else if (players->color_player_that_is_playing == BLACK){
                                    color_we_are_checking_IA = WHITE;
                                }
                                // get the check state of the player that was playing the last move
                                bool check_state = Is_Check(color_we_are_checking_IA, board);
                                // if the king of the color is in check after making a move, we need to remove the move, since it cannot be check after playing
                                if (check_state == false){

                                    // we check if the value of the piece captured is higher than the one we already have
                                    if (value_of_piece_captured < board[k][l]->value){
                                        move->previous_row = i;
                                        move->previous_col = j;
                                        move->destination_row = k;
                                        move->destination_col = l;
                                        value_of_piece_captured = board[k][l]->value;
                                    }

                                }
                                Undo_Last_Move(board, Move_Log, Board_Log, Captured_Pieces_and_Score, state_of_rock_and_check, players, Pawn_Move_State);
                                   
                            }
                            // here : a black piece of the IA color can capture a white piece
                            else if (IA_color == BLACK && board[k][l]->color == WHITE && Is_Move_Valid(move_temp, board, state_of_rock_and_check, Pawn_Move_State) == true){
                                // the move need not to put the king in check
                                Make_IA_Global_Move_and_Udpate_structures(move_temp, board, players, Move_Log, Board_Log, state_of_rock_and_check, Pawn_Move_State, Captured_Pieces_and_Score, players->color_player_that_is_playing, MEDIUM);
                                // if after the move made by the IA, it's in check, we need to undo the move and make another one
                                int color_we_are_checking_IA = NO_COLOR;
                                if (players->color_player_that_is_playing == WHITE){
                                    color_we_are_checking_IA = BLACK;
                                }
                                else if (players->color_player_that_is_playing == BLACK){
                                    color_we_are_checking_IA = WHITE;
                                }
                                // get the check state of the player that was playing the last move
                                bool check_state = Is_Check(color_we_are_checking_IA, board);
                                // if the king of the color is in check after making a move, we need to remove the move, since it cannot be check after playing
                                if (check_state == false){

                                    // we check if the value of the piece captured is higher than the one we already have
                                    if (value_of_piece_captured < board[k][l]->value){
                                        move->previous_row = i;
                                        move->previous_col = j;
                                        move->destination_row = k;
                                        move->destination_col = l;
                                        value_of_piece_captured = board[k][l]->value;
                                    }

                                }
                                Undo_Last_Move(board, Move_Log, Board_Log, Captured_Pieces_and_Score, state_of_rock_and_check, players, Pawn_Move_State);
                                   
                            }
                        }
                    }
                }
            }
        }
        // Destroying the temporary move
        Destroy_Move(move_temp);
    }

    // a level HARD IA will play depending on a first version of the Alpha-Beta algorithm
    if (level == MEDIUM){
        
        // getting the best move possible for the IA given our functions 
        Move* best_move = Create_Move(-1, -1, -1, -1);

        // find the best move according to the Alpha-Beta algorithm
        int score = Nega_Max_Alpha_Beta_Search(best_move, board, Move_Log, Board_Log, state_of_rock_and_check, Pawn_Move_State, Captured_Pieces_and_Score, players, DEPTH, -CHECKMATE, CHECKMATE);

        // the move need not to put the king in check
        Make_IA_Global_Move_and_Udpate_structures(best_move, board, players, Move_Log, Board_Log, state_of_rock_and_check, Pawn_Move_State, Captured_Pieces_and_Score, players->color_player_that_is_playing, HARD);
        // if after the move made by the IA, it's in check, we need to undo the move and make another one
        int color_we_are_checking_IA = NO_COLOR;
        if (players->color_player_that_is_playing == WHITE){
            color_we_are_checking_IA = BLACK;
        }
        else if (players->color_player_that_is_playing == BLACK){
            color_we_are_checking_IA = WHITE;
        }
        // get the check state of the player that was playing the last move
        bool check_state = Is_Check(color_we_are_checking_IA, board);
        // if the king of the color is in check after making a move, we need to remove the move, since it cannot be check after playing
        if (check_state == false){

            move->previous_row = best_move->previous_row;
            move->previous_col = best_move->previous_col;
            move->destination_row = best_move->destination_row;
            move->destination_col = best_move->destination_col;

        }
        Undo_Last_Move(board, Move_Log, Board_Log, Captured_Pieces_and_Score, state_of_rock_and_check, players, Pawn_Move_State);
       
        Destroy_Move(best_move);
    }

    // a level HARD IA will play depending on a second version of the Alpha-Beta algorithm with moves suggestions concerning captures and rock moves, pawn promotion
    if (level == HARD){
        
    }

    // a level MASTER IA will play depending on a second version of the Alpha-Beta algorithm, with iterative deepening to manage the time of play of the IA 
    if (level == MASTER){
        
    }

    // a level GRANDMASTER IA will play depending on a third version of the Alpha-Beta algorithm, with iterative deepening, but also a log of the most famous openings, how to make checkmate fast, ……
    if (level == GRANDMASTER){
        
    }

}