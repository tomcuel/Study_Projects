#ifndef __PLAYER_H__
#define __PLAYER_H__


#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "Constants.h"
#include "Piece.h"


/////////////////////////////////////////////////////////////////////////////////////
// Piece Summary 
/**
 * Players is a structure that represents the players of the game and its parameters
 * 
 * A summary of the supported functions is given below:
 * 
 * Create_Players - to create the two players
 * Change_Player_that_is_Playing - to change the player that is playing
 * Destroy_Players - to destroy the two players
 * IA_Play - to make the IA play (a move will be returned) (will need special implementation in the code to make the move)
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Structure that represents the players and its parameters
/////////////////////////////////////////////////////////////////////////////////////
typedef struct Players{
    int is_player1_an_IA; // HUMAN or AI, to get the type of the player 1
    int player1_color; // WHITE or BLACK
    char* player1_name; // name of the player 1
    
    int is_player2_an_IA; // HUMAN or AI, to get the type of the player 2
    int player2_color; // WHITE or BLACK
    char* player2_name; // name of the player 2

    int is_playing; // Player1 or Player2
} Players;


/////////////////////////////////////////////////////////////////////////////////////
// Function to create the two players
/**
**/
/////////////////////////////////////////////////////////////////////////////////////
Players* Create_Players();


////////////////////////////////////////////////////////////////////////////////////
// Function to chnage the two players caracteristics
/**
 * @param players : the players
 * @param player1_name : the name of the player 1
 * @param player2_name : the name of the player 2
 * @param player1_color : the color of the player 1
 * @param player2_color : the color of the player 2
 * @param is_player1_IA : if the player 1 is an IA or not
 * @param is_player2_IA : if the player 2 is an IA or not
**/
/////////////////////////////////////////////////////////////////////////////////////
void Change_Players(Players* players, char* player1_name, char* player2_name, int player1_color, int player2_color, int is_player1_IA, int is_player2_IA);


/////////////////////////////////////////////////////////////////////////////////////
// Function to change the player that is playing
/**
 * @param players : the players
 * @param is_playing : the player that is playing
**/
/////////////////////////////////////////////////////////////////////////////////////
void Change_Player_that_is_Playing(Players* players, int is_playing);


/////////////////////////////////////////////////////////////////////////////////////
// Function to destroy the two players
/**
 * @param player : the players to destroy
**/
/////////////////////////////////////////////////////////////////////////////////////
void Destroy_Players(Players* player);


/////////////////////////////////////////////////////////////////////////////////////
// Function to make the IA play, it returns a move the IA will play
// We then have to implement the move made and what it does as for a human player, just the move will not be defined by the player, some things will change in the code
// on how it will be organised when for the IA to play
// AI is always the player2
/**
 * @param board : the board to play on
 * @param level : the level of the IA
 * @param IA_color : the color of the IA (to know which pieces to play)
**/
/////////////////////////////////////////////////////////////////////////////////////
Move* IA_Play(Piece*** board, int level, int IA_color);


#endif /* __PLAYER_H__ */