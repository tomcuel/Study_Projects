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


void Destroy_Players(Players* players){
    // if the players are not NULL, we can free them
    if (players != NULL){
        free(players);
    }
}


void IA_Play(Move* move, Piece*** board, int level, int IA_color){
        
    // a level EASY IA will play a random move
    if (level == EASY){
        move->previous_row = Random_Int(0, 7);
        move->previous_col = Random_Int(0, 7);
        move->destination_row = Random_Int(0, 7);
        move->destination_col = Random_Int(0, 7);
    }

    // a level MEDIUM IA will play a random move, but will try to capture a piece if it can
    if (level == MEDIUM){
        
    }

    // a level HARD is still to be implemented
    if (level == HARD){

    }

}