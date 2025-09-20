#include "Player.h"

// Function to generate a random integer between min and max (inclusive)
int Random_Int(int min, int max) {
    return min + rand() % (max - min + 1);
}


Players* Create_Players() {
    Players* players = (Players*)malloc(sizeof(Players));
    // looking for a malloc error
    if (players == NULL){
        printf("Error: malloc failed in Create_Players\n");
        return NULL;
    }

    // setting the players, to be able to be played by two humans

    players->is_player1_an_IA = HUMAN;
    players->player1_color = WHITE;
    
    players->is_player2_an_IA = HUMAN;
    players->player2_color = BLACK;

    // the first player to play is the player 1, the one who has the white pieces
    players->is_playing = Player1;
    players->color_player_that_is_playing = WHITE;

    // return the players
    return players;
}


void Reset_Players(Players* players){
    // we can't reset the players if the players are not created
    if (players == NULL){
        printf("Error: the players are not created\n");
        return;
    }

    // resetting the players caracteristics to the ones that are set by default
    players->is_player1_an_IA = HUMAN;
    players->player1_color = WHITE;
    
    players->is_player2_an_IA = HUMAN;
    players->player2_color = BLACK;

    // the first player to play is the player 1, the one who has the white pieces
    players->is_playing = Player1;
    players->color_player_that_is_playing = WHITE;
}


void Setup_Players(Players* players, int player1_color, int player2_color, int is_player1_IA, int is_player2_IA){
    // we can't change the players if the players are not created
    if (players == NULL){
        printf("Error: the players are not created\n");
        return;
    }

    // changing the players caracteristics to the ones given in parameters
    players->player1_color = player1_color;
    players->player2_color = player2_color;
    players->is_player1_an_IA = is_player1_IA;
    players->is_player2_an_IA = is_player2_IA;
}


void Change_Players_that_is_Playing(Players* players){
    // we can't change the player that is playing if the players are not created
    if (players == NULL){
        printf("Error: the players are not created\n");
        return;
    }

    // changing the player that is playing by taking the opposite of the one that is playing currently, using the players structure
    if (players->is_playing == Player1){
        players->is_playing = Player2;
        players->color_player_that_is_playing = players->player2_color;
    } 
    else {
        players->is_playing = Player1;
        players->color_player_that_is_playing = players->player1_color;
    }
}


Players* Copy_Players(Players* players){
    // if the players are not created, we can't copy them
    if (players == NULL){
        printf("Error: the players are not created\n");
        return NULL;
    }

    // creating a new players structure
    Players* players_copy = Create_Players();
    // looking for a malloc error
    if (players_copy == NULL){
        printf("Error: malloc failed in Copy_Players\n");
        return NULL;
    }

    // copying the players caracteristics
    players_copy->is_player1_an_IA = players->is_player1_an_IA;
    players_copy->player1_color = players->player1_color;
    players_copy->is_player2_an_IA = players->is_player2_an_IA;
    players_copy->player2_color = players->player2_color;
    players_copy->is_playing = players->is_playing;
    players_copy->color_player_that_is_playing = players->color_player_that_is_playing;

    // returning the copy of the players
    return players_copy;
}


void Destroy_Players(Players* players){
    // if the players are not NULL, we can free them
    if (players != NULL){
        free(players);
    }
}


void IA_Play(Move* move, Piece*** board, int level, int IA_color, State_Of_Rock_and_Check* state_of_rock_and_check, Tiles_Pawn* Pawn_Move_State){
    bool is_move_correct = false;  
    // a level EASY IA will play a random move
    if (level == EASY){
        while (is_move_correct == false){
            move->previous_row = Random_Int(0, 7);
            move->previous_col = Random_Int(0, 7);
            move->destination_row = Random_Int(0, 7);
            move->destination_col = Random_Int(0, 7);
            if (Is_Move_Valid(move, board, state_of_rock_and_check, Pawn_Move_State) == true && board[move->previous_row][move->previous_col]->color == IA_color){
                is_move_correct = true;
            }
        }
    }

    // a level MEDIUM IA will play a random move, but will try to capture a piece if it can
    if (level == MEDIUM){
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
                            // if the move is valid and the colors are the good ones
                            // here : a white piece of the IA color can capture a black piece
                            if (IA_color == WHITE && board[k][l]->color == BLACK && Is_Move_Valid(move_temp, board, state_of_rock_and_check, Pawn_Move_State) == true){
                                // we check if the value of the piece captured is higher than the one we already have
                                if (value_of_piece_captured < board[k][l]->value){
                                    move->previous_row = i;
                                    move->previous_col = j;
                                    move->destination_row = k;
                                    move->destination_col = l;
                                    value_of_piece_captured = board[k][l]->value;
                                }
                            }
                            // here : a black piece of the IA color can capture a white piece
                            else if (IA_color == BLACK && board[k][l]->color == WHITE && Is_Move_Valid(move_temp, board, state_of_rock_and_check, Pawn_Move_State) == true){
                                // we check if the value of the piece captured is higher than the one we already have
                                if (value_of_piece_captured < board[k][l]->value){
                                    move->previous_row = i;
                                    move->previous_col = j;
                                    move->destination_row = k;
                                    move->destination_col = l;
                                    value_of_piece_captured = board[k][l]->value;
                                }
                            }
                        }
                    }
                }
            }
        }
        // Destroying the temporary move
        Destroy_Move(move_temp);
    }

    // a level HARD is still to be implemented
    if (level == HARD){

    }

    // we might need to also do others levels of IA, if it's possible
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
    }

    // we might need to also do others levels of IA, if it's possible
}