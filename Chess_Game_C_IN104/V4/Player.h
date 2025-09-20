#ifndef __PLAYER_H__
#define __PLAYER_H__


#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
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
 * Reset_Players - to reset the two players structure
 * Setup_Players - to change the two players caracteristics
 * Change_Player_that_is_Playing - to change the player that is playing
 * Copy_Players - to copy the two players
 * Destroy_Players - to destroy the two players
 * IA_Play - to make the IA play (a move will be returned) (will need special implementation in the code to make the move)
 * Make_Pawn_Promotion_for_IA - to make the pawn promotion for the IA (it replace the pawn promoted by the piece chosen by the IA)
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Structure that represents the players and its parameters
/////////////////////////////////////////////////////////////////////////////////////
typedef struct Players{
    int is_player1_an_IA; // HUMAN or AI, to get the type of the player 1
    int player1_color; // WHITE
    
    int is_player2_an_IA; // HUMAN or AI, to get the type of the player 2
    int player2_color; // BLACK

    int is_playing; // Player1 or Player2
    int color_player_that_is_playing; // WHITE or BLACK
} Players;


/////////////////////////////////////////////////////////////////////////////////////
// Function to generate a random number between two numbers
/**
 * @param min : the minimum number
 * @param max : the maximum number
 * @return int : the random number generated
**/
/////////////////////////////////////////////////////////////////////////////////////
int Random_Int(int min, int max);


/////////////////////////////////////////////////////////////////////////////////////
// Function to create the two players
/**
**/
/////////////////////////////////////////////////////////////////////////////////////
Players* Create_Players();


/////////////////////////////////////////////////////////////////////////////////////   
// Function to reset the two players structure
/**
 * @param players : the players to reset
**/
/////////////////////////////////////////////////////////////////////////////////////
void Reset_Players(Players* players);


////////////////////////////////////////////////////////////////////////////////////
// Function to chnage the two players caracteristics
/**
 * @param players : the players
 * @param player1_color : the color of the player 1
 * @param player2_color : the color of the player 2
 * @param is_player1_IA : if the player 1 is an IA or not
 * @param is_player2_IA : if the player 2 is an IA or not
**/
/////////////////////////////////////////////////////////////////////////////////////
void Setup_Players(Players* players, int player1_color, int player2_color, int is_player1_IA, int is_player2_IA);


/////////////////////////////////////////////////////////////////////////////////////
// Function to change the player that is playing
/**
 * @param players : the players
**/
/////////////////////////////////////////////////////////////////////////////////////
void Change_Players_that_is_Playing(Players* players);


/////////////////////////////////////////////////////////////////////////////////////
// Function to copy the two players
/**
 * @param players : the players to copy
 * @return Players* : the copy of the players
**/
/////////////////////////////////////////////////////////////////////////////////////
Players* Copy_Players(Players* players);


/////////////////////////////////////////////////////////////////////////////////////
// Function to destroy the two players
/**
 * @param player : the players to destroy
**/
/////////////////////////////////////////////////////////////////////////////////////
void Destroy_Players(Players* player);


/////////////////////////////////////////////////////////////////////////////////////
// Function to make the IA play, it chnages a move the IA will play
// We then have to implement the move made and what it does as for a human player, just the move will not be defined by the player, some things will change in the code
// on how it will be organised when for the IA to play
// AI is always the player2
/**
 * @param move : the move to play
 * @param board : the board to play on
 * @param level : the level of the IA
 * @param IA_color : the color of the IA (to know which pieces to play)
 * @param state_of_rock_and_check : the state of the rock and check
 * @param Pawn_Move_State : the state of the pawns
**/
/////////////////////////////////////////////////////////////////////////////////////
void IA_Play(Move* move, Piece*** board, int level, int IA_color, State_Of_Rock_and_Check* state_of_rock_and_check, Tiles_Pawn* Pawn_Move_State);


/////////////////////////////////////////////////////////////////////////////////////
// Function to make the pawn promotion for the IA (it replace the pawn promoted by the piece chosen by the IA)
/**
 * @param move : the move to play
 * @param board : the board to play on
 * @param Log : the log of the moves
 * @param IA_level : the level of the IA
**/
/////////////////////////////////////////////////////////////////////////////////////
void Make_Pawn_Promotion_for_IA(Move* move, Piece*** board, Move_Log_array* Log, int level_IA);



#endif /* __PLAYER_H__ */