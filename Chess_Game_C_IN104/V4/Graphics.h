#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__


#include <SDL2/SDL.h>
#include "Constants.h"
#include "Piece.h"
#include "Move_Log.h"
#include "Player.h"
#include "Board.h"
#include "Image.h"
#include "Conversion.h"


/////////////////////////////////////////////////////////////////////////////////////
// Graphics Summary 
/**
 * Button is a structure that represents the buttons (the one to naviguate through the menus) and their states
 * 
 * A summary of the supported functions is given below:
 * 
 * Create_Buttons - to create the array of buttons and initialize them also, since no special initialization needs to be done
 * Destroy_Buttons - to destroy the array of buttons
 * Show_Load_Menu - to show the menu rendering (clearing it and showing it)
 * Show_Chess_Board - to show the chess board
 * Show_Captured_Pieces - to show the captured pieces of the players
 * Show_Log - to show the log of the moves
 * Show_Updated_Timer - to show the timer, remaining for each player
 * Show_Menu_Button_in_Game - to show the menu / parameters button during the game
 * Show_Victory_Menu - to show the victory menu
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Structure that represents the buttons (the one to naviguate through the menus) and their states
/////////////////////////////////////////////////////////////////////////////////////
typedef struct Button{
    SDL_Rect rect; // the rectangle of the button
    int state; // the state of the button : UNACTIVE or ACTIVE
    // the type will be given by the position in the enum of buttons
    // for example Buttons[5] correspond to the button "LOAD_BUTTON" since in the enum LOAD_BUTTON=5
} Button;


/////////////////////////////////////////////////////////////////////////////////////
// Function to create the array of buttons and initialize them also, since no special initialization needs to be done 
/**
 * @param number_of_buttons - the number of buttons, ie the size of the array
 * @return Button** - a pointer to the array of buttons created
**/
/////////////////////////////////////////////////////////////////////////////////////
Button** Create_Buttons(int number_of_buttons);


/////////////////////////////////////////////////////////////////////////////////////
// Function to reset the buttons state to UNACTIVE
/**
 * @param Buttons - the array of Buttons
**/
/////////////////////////////////////////////////////////////////////////////////////
void Reset_Buttons_State(Button** Buttons);


/////////////////////////////////////////////////////////////////////////////////////
// Function to destroy the array of buttons
/**
 * @param number_of_buttons - the number of buttons, ie the size of the array
 * @param Buttons - the array of Buttons
**/
/////////////////////////////////////////////////////////////////////////////////////
void Destroy_Buttons(int number_of_buttons, Button** Buttons);


/////////////////////////////////////////////////////////////////////////////////////
// Function to show the menu rendering (clearing it and showing it)
// not all the buttons will be shown, only the ones that are needed, depending on the menu_type and if the button is used for a menu or for the game
// the state in the button will be used to show the button in a different color if it is active or not (we have different pictures)
/**
 * @param renderer : the renderer to show the menu
 * @param menu_type : the menu_type to show : GAMEMPLAY_CHOICE, DIFFICULTY_CHOICE, TIME_CHOICE
 * @param Buttons : the buttons to show
 * @param is_clicked_1 : if the first button is clicked
 * @param is_clicked_2 : if the second button is clicked
 * @param draw_red_boundary_move : the red boundary to draw around a piece when it's selected to make a move
**/
/////////////////////////////////////////////////////////////////////////////////////
void Show_Load_Menu(SDL_Renderer* renderer, int menu_type, Button** Buttons, int is_clicked_1, int is_clicked_2, SDL_Rect draw_red_boundary_move);


/////////////////////////////////////////////////////////////////////////////////////
// Function to show the chess board
/**
 * @param renderer : the renderer to show the board
 * @param board : the board to show
 * @param Move_Log_Array : the log of the moves
 * @param is_clicked_1 : if the first square is clicked
 * @param is_clicked_2 : if the second square is clicked
 * @param draw_red_boundary_move : the red boundary to draw around a piece when it's selected to make a move
**/
/////////////////////////////////////////////////////////////////////////////////////
void Show_Chess_Board(SDL_Renderer* renderer, Piece*** board, Move_Log_array* Move_Log_Array, int is_clicked_1, int is_clicked_2, SDL_Rect draw_red_boundary_move);


/////////////////////////////////////////////////////////////////////////////////////
// Function to show the captured pieces of the players
// One for the player 1 and one for the player 2, on the top of the screen for the white captured pieces and on the bottom for the black captured pieces
/**
 * @param renderer : the renderer to show the captured pieces
 * @param captured_pieces : the captured pieces to show
**/
/////////////////////////////////////////////////////////////////////////////////////
void Show_Captured_Pieces(SDL_Renderer* renderer, Captured_Piece_and_Score* captured_pieces);


/////////////////////////////////////////////////////////////////////////////////////
// Function to show the log of the moves
/**
 * @param renderer : the renderer to show the log
 * @param log : the log to show
**/
/////////////////////////////////////////////////////////////////////////////////////
void Show_Log(SDL_Renderer* renderer, Move_Log_array* log);


/////////////////////////////////////////////////////////////////////////////////////
// Function to show the timer, remaining for each player
// It will not be inplemented in the first version of the game, but it will be implemented in the second version
// Since we don't have ttf, it might need time to do it (either by showing it pixel by pixel or by using the terminal)
/**
 * @param renderer : the renderer to show the timer
 * @param time_player_white : the time remaining for the player white
 * @param time_player_black : the time remaining for the player black
 * @param player_playing : the player playing (player 1 or player 2) (for white and black player respectively)
**/
/////////////////////////////////////////////////////////////////////////////////////
void Show_Updated_Timer(SDL_Renderer* renderer, int time_player_white, int time_player_black, int player_playing);


/////////////////////////////////////////////////////////////////////////////////////
// Function to show the menu / parameters button during the game 
/**
 * @param renderer : the renderer to show the menu button
 * @param Buttons : the buttons to show
 * @param is_pawn_promotion_happening : if the pawn promotion is happening : will show different buttons in this case
 * @param color_promoted_pawn : the color of the promoted pawn
**/
/////////////////////////////////////////////////////////////////////////////////////
void Show_Menu_Button_in_Game(SDL_Renderer* renderer, Button** Buttons, bool is_pawn_promotion_happening, int color_promoted_pawn);


/////////////////////////////////////////////////////////////////////////////////////
// Function to draw a filled red circle on the screen at the specified position and radius
/**
 * @param renderer : the renderer to show the circle
 * @param centerX : the x position of the center of the circle
 * @param centerY : the y position of the center of the circle
 * @param radius : the radius of the circle
**/
/////////////////////////////////////////////////////////////////////////////////////
void Draw_Filled_Circle(SDL_Renderer *renderer, int centerX, int centerY, int radius);


/////////////////////////////////////////////////////////////////////////////////////
// Function to draw the possible place where a piece can go to 
/**
 * @param renderer : the renderer to show the trajectory
 * @param board : the board to show
 * @param move : the move to show
 * @param State_Of_Rock_and_Check : the state of the rock and check
 * @param Pawn_Move_State : the state of the pawn move
 * @param is_clicked_1 : if the first square is clicked
 * @param is_clicked_2 : if the second square is clicked
 * @param is_click_board : if the board is clicked
**/
/////////////////////////////////////////////////////////////////////////////////////
void Show_Trajectory(SDL_Renderer* renderer, Piece*** board, Move* move, State_Of_Rock_and_Check* State_Of_Rock_and_Check, Tiles_Pawn* Pawn_Move_State, int is_clicked_1, int is_clicked_2, bool is_click_board);


/////////////////////////////////////////////////////////////////////////////////////
// Function to show the victory menu
/**
 * @param renderer : the renderer to show the victory menu
 * @param Buttons : the buttons to show
 * @param looser_player : the looser player
 * @param players : the players
**/
/////////////////////////////////////////////////////////////////////////////////////
void Show_Victory_Menu(SDL_Renderer* renderer, Button** Buttons, int looser_player, Players* players);



#endif /* __GRAPHICS_H__ */