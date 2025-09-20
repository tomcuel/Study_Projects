///////////////////////////////////////////////////////////////////////////////
// Chess_Game.c : main file of the chess game
//  
/**
 * initialize the window and the renderer, is_running_game (global variable to make the game run)
 * 
 * A summary of the supported functions is given below:
 * 
 * initialize_SDL - to initialize the window and the renderer
 * clear_graphics - to clear the graphics
 * main - main function of the game with the game loop
 * 
 * A bit of comments to explain the code of this V1 to will remain incomplete :
 * 
 * - the game loop should work fine here 
 * - the game isn't finished at this state 
 * - by adding the en passant to the pawn movement possibilities, in this version th goal is to use the buttons on the menu and do the move only (not considering en passant, the check things)
 * - the goal here is that the rock is working fine (without just the check things)
 * - an effort has been made here to use the log, the state of the rock, the captured pieces (we have checked yet if it works correctly, but it should work in theory, so we will test that in the future)
 * - this part will focus on the implementation of the differents menus during the game and what it implies to the game
 * - the IA is working, but for now, it's really a simple one that just makes a random move, we will need to improve it in the future, but the framework is here
 * - The Move_Log is not shown since it's really a difficult thing to do, because it implies to write a lot of letters, It could be possible to do it in the future (with many screen shots of the caracters we want to print and then do a parsing to print them), but it's not the priority for now
 * - we can't ask yet the player names, we will need to do it in the future if possible
 * 
 * - What is missing : 
 * - an intelligent AI (the different levels have to be implemented, others than the random)(maybe buttons will be to be updated if we want to have more levels of IA)
 * - the pawn promotion (and its visual to choose things, will not be difficult we think, but it will take time)
 * - he check (we think really difficult) and it's implentation in the code, it relies also on making the undo work, since a move that makes the king chekcs must be deleted and the board reinstated as it was before the move to ensure that no check occurs after the move
 * - otherwise if there is not valid moves, the checkmates might be the answer
 * - For now, everything is set up to make the game work, but it's not finished yet, things have not really been tested before being put here because it's just a draft 
 * - It will not be the case for the next versions, we will need to test everything before putting it in the main file
**/
///////////////////////////////////////////////////////////////////////////////


#include <stdio.h> // pour le printf
#include <stdlib.h> // pour le scanf
#include <math.h> // pour les fonctions mathématiques 
#include <string.h> // pour les chaînes de caractères, strlen par exemple
#include <stdbool.h> // pour les booléens 
#include <time.h> // pour les randint 
#include <limits.h> // pour les limites
#include <ctype.h> // pour isalpha 
#include <unistd.h> // pour getpid 


#include "SDL2/SDL.h"


#include "Constants.h"
#include "Player.h"
#include "Board.h"
#include "Piece.h"
#include "Move.h"
#include "Graphics.h"


// initialize the window and the renderer
#define max_size_log_array 1000
int is_running_game = -1; // setup to -1 for false before the initialization of the game
int last_frame_time = 0;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;


///////////////////////////////////////////////////////////////////////////////
// function to print the captured pieces and the state of the rock and check
/**
 * @param *captured_piece_and_score : the structure that contains the captured pieces and the score
 * @param *state_of_rock_and_check : the structure that contains the state of the rock and check
**/
///////////////////////////////////////////////////////////////////////////////
void print_rock_state_and_captured_pieces(Captured_Piece_and_Score* captured_piece_and_score, State_Of_Rock_and_Check* state_of_rock_and_check){

    // printing the state of the rock and check
    // printing if a rock is possible for each player
    printf("\n     The state of the rock and check currently is : \n");
    if (state_of_rock_and_check->white_rock_done == false){
        printf("The white player can still do the rock\n");
    }
    else {
        printf("The white player can't do the rock anymore\n");
    }
    if (state_of_rock_and_check->black_rock_done == false){
        printf("The black player can still do the rock\n");
    }
    else {
        printf("The black player can't do the rock anymore\n");
    }

    // printing if a piece has moved for each player
    printf("The pieces that moved from their starting position concerning rock for white players are : ");
    if (state_of_rock_and_check->white_king_moved == true){
        printf("The white king moved, ");
    }
    if (state_of_rock_and_check->white_left_rook_moved == true){
        printf("The white left rook moved, ");
    }
    if (state_of_rock_and_check->white_right_rook_moved == true){
        printf("The white right rook moved, ");
    }
    printf("\n");
    printf("The pieces that moved from their starting position concerning rock for black players are : ");
    if (state_of_rock_and_check->black_king_moved == true){
        printf("The black king moved, ");
    }
    if (state_of_rock_and_check->black_left_rook_moved == true){
        printf("The black left rook moved, ");
    }
    if (state_of_rock_and_check->black_right_rook_moved == true){
        printf("The black right rook moved,");
    }
    printf("\n");


    // priting the captured pieces
    printf("\n     The captured pieces are : \n");
    printf("There are %d white captured pieces\nhere is the list : ", captured_piece_and_score->number_of_white_pieces_captured);
    for (int i = 0; i < captured_piece_and_score->number_of_white_pieces_captured; i++){
        switch (captured_piece_and_score->white_pieces_captured[i]->type){
            case PAWN:
                printf("pawn, ");
                break;
            case KNIGHT:
                printf("knight, ");
                break;
            case BISHOP:
                printf("bishop, ");
                break;
            case ROOK:
                printf("rook, ");
                break;
            case QUEEN:
                printf("queen, ");
                break;
            case KING:
                printf("king, ");
                break;
            default:
                printf("nothing, ");
                break;
        }
    }
    printf("\n");


    printf("There are %d black captured pieces\nhere is the list : ", captured_piece_and_score->number_of_black_pieces_captured);
    for (int i = 0; i < captured_piece_and_score->number_of_black_pieces_captured; i++){
        switch (captured_piece_and_score->black_pieces_captured[i]->type){
            case PAWN:
                printf("pawn, ");
                break;
            case KNIGHT:
                printf("knight, ");
                break;
            case BISHOP:
                printf("bishop, ");
                break;
            case ROOK:
                printf("rook, ");
                break;
            case QUEEN:
                printf("queen, ");
                break;
            case KING:
                printf("king, ");
                break;
            default:
                printf("nothing, ");
                break;
        }
    }
    printf("\n");


    // printing the score 
    printf("\n     The score is : \n");
    if (captured_piece_and_score->player_that_is_winning == WHITE){
        printf("The white player is winning with a score of %d\n", captured_piece_and_score->score);
    }
    else if (captured_piece_and_score->player_that_is_winning == BLACK){
        printf("The black player is winning with a score of %d\n", captured_piece_and_score->score);
    }
    else {
        printf("The two players are equal on score\n");
    }

}


///////////////////////////////////////////////////////////////////////////////
// Define a font for rendering digits
///////////////////////////////////////////////////////////////////////////////
const int font[10][FONT_WIDTH] = {
    {0x00, 0x7E, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x7E}, // 0
    {0x00, 0x00, 0x42, 0x82, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00}, // 1
    {0x00, 0x42, 0x87, 0x89, 0x91, 0xA1, 0xC1, 0x42, 0x00, 0x00}, // 2
    {0x42, 0x81, 0x81, 0x91, 0x91, 0x91, 0x89, 0x76, 0x00, 0x00}, // 3
    {0x18, 0x28, 0x48, 0x88, 0xFF, 0xFF, 0x08, 0x08, 0x08, 0x00}, // 4
    {0xF2, 0x91, 0x91, 0x91, 0x91, 0x91, 0x89, 0x86, 0x00, 0x00}, // 5
    {0x7E, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x0E, 0x00, 0x00}, // 6
    {0x80, 0x80, 0x81, 0x82, 0x84, 0x88, 0x90, 0xE0, 0x00, 0x00}, // 7
    {0x76, 0x89, 0x91, 0x91, 0x91, 0x91, 0x89, 0x76, 0x00, 0x00}, // 8
    {0x72, 0x89, 0x91, 0x91, 0x91, 0x91, 0x89, 0x7E, 0x00, 0x00}  // 9
};


///////////////////////////////////////////////////////////////////////////////
// Function to initialize our SDL window
/**
 * @param **window : the window to initialize that is a global variable
 * @param **renderer : the renderer to initialize that is a global variable
 * @return true (1) if the initialization is successful, false (0) otherwise
**/
///////////////////////////////////////////////////////////////////////////////
int initialize_SDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return -1;
    }
    window = SDL_CreateWindow(
        "A simple game loop using C & SDL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_FULLSCREEN // SDL_WINDOW_FULLSCREEN can be used to make the window fullscreen, if we've the timer on it thanks to tff
        // otherwise, we will need to print it in the terminal
    );
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        return -1;
    }

    // create the renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        return -1;
    }

    // if everything is ok, we return true
    return GAMEPLAY_CHOICE;
}


///////////////////////////////////////////////////////////////////////////////
// Function to clear the graphics
/**
 * @param *window : the window to destroy
 * @param *renderer : the renderer to destroy 
**/
///////////////////////////////////////////////////////////////////////////////
void clear_graphics(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


///////////////////////////////////////////////////////////////////////////////
// Function to know if a point (x,y) is in a rectangle  
/**
 * @param x : the x coordinate of the point
 * @param y : the y coordinate of the point
 * @param rect : the rectangle to check
 * @return bool : true if the point is in the rectangle, false otherwise
**/
///////////////////////////////////////////////////////////////////////////////
bool is_point_in_rect(int x, int y, SDL_Rect rect) {
    return x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h;
}


///////////////////////////////////////////////////////////////////////////////
// Main function of the game
///////////////////////////////////////////////////////////////////////////////
int main (){

    /*
    // some variables to first test the IA
    int test_IA = 0;
    */

    // initialize the window and the renderer, is_running_game is a global variable that is 0 if the initialization is successful, -1 otherwise
    is_running_game = initialize_SDL();

    // intialize the board
    Piece*** board = Init_Board();
    
    // initialize the move log array
    Move_Log_array* Log = Create_Move_Log_array(max_size_log_array);

    // initialize the captured pieces array
    int max_size_captured_pieces_array = NUMBER_OF_PIECES/2;
    Captured_Piece_and_Score* Captured_Pieces_and_Score = Create_Captured_Piece_and_Score(max_size_captured_pieces_array);

    // initialize the structure to have the state of the game concerning rock and check
    State_Of_Rock_and_Check* State_Of_RockandCheck = Create_State_Of_Rock_and_Check();

    // initialize the structure concerning the last play, but only for pawn that moved two squares (for the en passant)
    Tiles_Pawn* Pawn_Move_State = Create_Tiles_Pawn();

    // initialize the players
    Players* players = Create_Players();

    // initialize the buttons
    Button** Buttons = Create_Buttons(NUMBER_OF_BUTTONS);

    bool has_match_started = false; // boolean to make the timer start; -1 for false, 1 for true

    // making the timer for each player, the time mode will be asked after so this constant here will have no effect later 
    int timer_game_mode=5;
    // making the time of the blitz mode, it will be asked after so this constant here will have no effect later
    // it define how many time a player win by making a move
    int time_of_blitz_mode=0;

    // time remaining for each player
    int seconds_remaining_player_2 = timer_game_mode;
    int last_second_player_2 = 0;

    int seconds_remaining_player_1 = timer_game_mode;
    int last_second_player_1 = 0;

    // player 0 begin to play 
    // both player 1 and player 2 have 5 seconds to play on the screen, after that it close the window and gave us the player that lose, made it
    int loosing_player=-1;

    // parameters to get the IA level
    int level_IA = NONE;

    // making int variable to know if the first clicked is done and the second clicked is done
    int is_clicked_1 = 0;
    int is_clicked_2 = 0;
    bool is_clicked_on_board = false; // to track if a click (and only one) has been done on the board or not
    // later there will be more, but here we don't care about the other clicks for buttons, etc, …

    // preparing a move implementation
    Move* move = Create_Move(0, 0, 0, 0);

    // SDL_rect to draw the red boundary when we move a piece to know it's the piece that is selected
    SDL_Rect draw_red_boundary_move={0, 0, 0, 0};

    SDL_Event event;
    // playing the game while we don't quit it :
    while (is_running_game != -1) {
        
        // gestion of the events
        while (SDL_PollEvent(&event)) {
            // condition to quit the game
            if (event.type == SDL_QUIT) {
                is_running_game = -1;
            } 
            // what happens when a key is pressed (the escape key to quit the game)
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        is_running_game = -1;
                        break;
                }
            }

            // taking the mouse event, here it's the mouse button down, so we've pressed the mouse button
            else if (event.type == SDL_MOUSEBUTTONDOWN){
                
                // when we choose the game mode
                // the part (color_choice or difficulty_choice) will be skipped otherwise
                if (is_running_game == GAMEPLAY_CHOICE){

                    // if the button to seleect a 1v1 game is clicked
                    if (is_point_in_rect(event.button.x, event.button.y, Buttons[PLAYER_VS_PLAYER_BUTTON]->rect)){
                    
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[PLAYER_VS_PLAYER_BUTTON]->rect.x;
                            draw_red_boundary_move.y = Buttons[PLAYER_VS_PLAYER_BUTTON]->rect.y;
                            draw_red_boundary_move.w = Buttons[PLAYER_VS_PLAYER_BUTTON]->rect.w;
                            draw_red_boundary_move.h = Buttons[PLAYER_VS_PLAYER_BUTTON]->rect.h;
                            Buttons[PLAYER_VS_PLAYER_BUTTON]->state = ACTIVE;
                            Setup_Players(players, WHITE, BLACK, HUMAN, HUMAN);
                            level_IA = NONE;
                        }

                        // if another click is done, we cancel the selection
                        else if (is_clicked_1 ==1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                        }

                        // if two clicks have been done, we cancel the selection
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                    }

                    // if the button to seleect a 1vAI game is clicked
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[PLAYER_VS_AI_BUTTON]->rect)){
                    
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[PLAYER_VS_AI_BUTTON]->rect.x;
                            draw_red_boundary_move.y = Buttons[PLAYER_VS_AI_BUTTON]->rect.y;
                            draw_red_boundary_move.w = Buttons[PLAYER_VS_AI_BUTTON]->rect.w;
                            draw_red_boundary_move.h = Buttons[PLAYER_VS_AI_BUTTON]->rect.h;
                            Buttons[PLAYER_VS_AI_BUTTON]->state = ACTIVE;
                            Setup_Players(players, WHITE, BLACK, IA, IA);
                        }

                        // if another click is done, we cancel the selection
                        else if (is_clicked_1 ==1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                        }

                        // if two clicks have been done, we cancel the selection
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                    }

                    // if we click on the next button, but it can only be a second click
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[NEXT_BUTTON_GAME_CHOICE]->rect)){

                        // if the two clicks have be done, we load the game by changing the type of part we're in, we go to CHESSBOARD_RENDER
                        if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            if (players->is_player1_an_IA == IA && players->is_player2_an_IA == IA){
                                is_running_game = COLOR_CHOICE;
                            }
                            else {
                                is_running_game = TIME_CHOICE;
                            }
                            Reset_Buttons_State(Buttons);
                        }
                    }
                    
                    // if we click on the quit menu 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[QUIT_BUTTON_GAME_CHOICE]->rect) && Buttons[PLAYER_VS_PLAYER_BUTTON]->state == UNACTIVE && Buttons[PLAYER_VS_AI_BUTTON]->state == UNACTIVE){
                        
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[QUIT_BUTTON_GAME_CHOICE]->rect.x;
                            draw_red_boundary_move.y = Buttons[QUIT_BUTTON_GAME_CHOICE]->rect.y;
                            draw_red_boundary_move.w = Buttons[QUIT_BUTTON_GAME_CHOICE]->rect.w;
                            draw_red_boundary_move.h = Buttons[QUIT_BUTTON_GAME_CHOICE]->rect.h;
                        }

                        // a second click 
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                        }

                        // if the two clicks have be done, we quit the game
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_running_game = -1;
                        }
                    }

                    // when we don't click on anything, we reset the buttons state
                    else {
                    is_clicked_1 = 0;
                    is_clicked_2 = 0;
                    Reset_Buttons_State(Buttons);
                }

                }

                // when we choose the color we want to have against the IA
                else if (is_running_game == COLOR_CHOICE){
                    
                    // if we click on the black button
                    if (is_point_in_rect(event.button.x, event.button.y, Buttons[BLACK_COLOR_BUTTON]->rect)){
                        
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[BLACK_COLOR_BUTTON]->rect.x;
                            draw_red_boundary_move.y = Buttons[BLACK_COLOR_BUTTON]->rect.y;
                            draw_red_boundary_move.w = Buttons[BLACK_COLOR_BUTTON]->rect.w;
                            draw_red_boundary_move.h = Buttons[BLACK_COLOR_BUTTON]->rect.h;
                            Buttons[BLACK_COLOR_BUTTON]->state = ACTIVE;
                            Setup_Players(players, WHITE, BLACK, IA, HUMAN);
                        }

                        // if another click is done, we cancel the selection
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                            Reset_Buttons_State(Buttons);
                        }

                        // if two clicks have been done, we cancel the selection
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                    }

                    // if we click on the white button 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[WHITE_COLOR_BUTTON]->rect)){
                        
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[WHITE_COLOR_BUTTON]->rect.x;
                            draw_red_boundary_move.y = Buttons[WHITE_COLOR_BUTTON]->rect.y;
                            draw_red_boundary_move.w = Buttons[WHITE_COLOR_BUTTON]->rect.w;
                            draw_red_boundary_move.h = Buttons[WHITE_COLOR_BUTTON]->rect.h;
                            Buttons[WHITE_COLOR_BUTTON]->state = ACTIVE;
                            Setup_Players(players, WHITE, BLACK, HUMAN, IA);
                        }

                        // if another click is done, we cancel the selection
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                            Reset_Buttons_State(Buttons);
                        }

                        // if two clicks have been done, we cancel the selection
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                    }
               
                    // if we click on the quit button, we go out of the game 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[QUIT_BUTTON_COLOR_CHOICE]->rect) && Buttons[BLACK_COLOR_BUTTON]->state == UNACTIVE && Buttons[WHITE_COLOR_BUTTON]->state == UNACTIVE){
                        
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[QUIT_BUTTON_COLOR_CHOICE]->rect.x;
                            draw_red_boundary_move.y = Buttons[QUIT_BUTTON_COLOR_CHOICE]->rect.y;
                            draw_red_boundary_move.w = Buttons[QUIT_BUTTON_COLOR_CHOICE]->rect.w;
                            draw_red_boundary_move.h = Buttons[QUIT_BUTTON_COLOR_CHOICE]->rect.h;
                        }

                        // a second click 
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                        }

                        // if the two clicks have be done, we quit the game
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_running_game = -1;
                        }

                    }
                
                    // if we click on the main menu button, we go back to the first menu
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect) && Buttons[BLACK_COLOR_BUTTON]->state == UNACTIVE && Buttons[WHITE_COLOR_BUTTON]->state == UNACTIVE){
                    
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect.x;
                            draw_red_boundary_move.y = Buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect.y;
                            draw_red_boundary_move.w = Buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect.w;
                            draw_red_boundary_move.h = Buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect.h;
                            Buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->state = ACTIVE;
                        }

                        // a second click 
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                        }

                        // if the two clicks have be done, we go back to the first menu
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_running_game = GAMEPLAY_CHOICE;
                            has_match_started = false;
                            level_IA = NONE;
                            Reset_Buttons_State(Buttons);
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                        }

                    }

                    // if we click on the back button, we go back to the IA_type choice
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[BACK_BUTTON_COLOR_CHOICE]->rect) && Buttons[BLACK_COLOR_BUTTON]->state == UNACTIVE && Buttons[WHITE_COLOR_BUTTON]->state == UNACTIVE){
                    
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[BACK_BUTTON_COLOR_CHOICE]->rect.x;
                            draw_red_boundary_move.y = Buttons[BACK_BUTTON_COLOR_CHOICE]->rect.y;
                            draw_red_boundary_move.w = Buttons[BACK_BUTTON_COLOR_CHOICE]->rect.w;
                            draw_red_boundary_move.h = Buttons[BACK_BUTTON_COLOR_CHOICE]->rect.h;
                            Buttons[BACK_BUTTON_COLOR_CHOICE]->state = ACTIVE;
                        }

                        // a second click 
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                        }

                        // if the two clicks have be done, we go back to the IA_type choice
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_running_game = GAMEPLAY_CHOICE;
                            has_match_started = false;
                            level_IA = NONE;
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                    }

                    // if we click on the next button, we go to the difficulty choice menu, but it's only a second click 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[NEXT_BUTTON_COLOR_CHOICE]->rect)){
                    
                        // a second click 
                        if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                        }

                        // if the two clicks have be done, we load the game by changing the type of part we're in, we go to CHESSBOARD_RENDER
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            is_running_game = DIFFICULTY_CHOICE;
                            has_match_started = false;
                            Reset_Buttons_State(Buttons);
                        }

                    }

                    // when we don't click on anything, we reset the buttons state
                    else {
                        is_clicked_1 = 0;
                        is_clicked_2 = 0;
                        Reset_Buttons_State(Buttons);
                    }

                }

                // when we choose the difficulty of the AI, but only if we're playing against the AI
                else if (is_running_game == DIFFICULTY_CHOICE){

                    // for the easy difficulty button
                    if (is_point_in_rect(event.button.x, event.button.y, Buttons[EASY_DIFFICULTY_BUTTON]->rect)){
                        
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[EASY_DIFFICULTY_BUTTON]->rect.x;
                            draw_red_boundary_move.y = Buttons[EASY_DIFFICULTY_BUTTON]->rect.y;
                            draw_red_boundary_move.w = Buttons[EASY_DIFFICULTY_BUTTON]->rect.w;
                            draw_red_boundary_move.h = Buttons[EASY_DIFFICULTY_BUTTON]->rect.h;
                            Buttons[EASY_DIFFICULTY_BUTTON]->state = ACTIVE;
                            level_IA = EASY;
                        }

                        // if another click is done, we cancel the selection
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                            Reset_Buttons_State(Buttons);
                        }

                        // if two clicks have been done, we cancel the selection
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                    }

                    // for the moderate difficulty button
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[MODERATE_DIFFICULTY_BUTTON]->rect)){
                    
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[MODERATE_DIFFICULTY_BUTTON]->rect.x;
                            draw_red_boundary_move.y = Buttons[MODERATE_DIFFICULTY_BUTTON]->rect.y;
                            draw_red_boundary_move.w = Buttons[MODERATE_DIFFICULTY_BUTTON]->rect.w;
                            draw_red_boundary_move.h = Buttons[MODERATE_DIFFICULTY_BUTTON]->rect.h;
                            Buttons[MODERATE_DIFFICULTY_BUTTON]->state = ACTIVE;
                            level_IA = MEDIUM;
                        }

                        // if another click is done, we cancel the selection
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                            Reset_Buttons_State(Buttons);
                        }

                        // if two clicks have been done, we cancel the selection
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                    }

                    // for the hard difficulty button
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[HARD_DIFFICULTY_BUTTON]->rect)){
                        
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[HARD_DIFFICULTY_BUTTON]->rect.x;
                            draw_red_boundary_move.y = Buttons[HARD_DIFFICULTY_BUTTON]->rect.y;
                            draw_red_boundary_move.w = Buttons[HARD_DIFFICULTY_BUTTON]->rect.w;
                            draw_red_boundary_move.h = Buttons[HARD_DIFFICULTY_BUTTON]->rect.h;
                            Buttons[HARD_DIFFICULTY_BUTTON]->state = ACTIVE;
                            level_IA = HARD;
                        }

                        // if another click is done, we cancel the selection
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                            Reset_Buttons_State(Buttons);
                        }

                        // if two clicks have been done, we cancel the selection
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                    }

                    // for the quit button 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[QUIT_BUTTON_IA_CHOICE]->rect) && Buttons[EASY_DIFFICULTY_BUTTON]->state == UNACTIVE && Buttons[MODERATE_DIFFICULTY_BUTTON]->state == UNACTIVE && Buttons[HARD_DIFFICULTY_BUTTON]->state == UNACTIVE){
                        
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[QUIT_BUTTON_IA_CHOICE]->rect.x;
                            draw_red_boundary_move.y = Buttons[QUIT_BUTTON_IA_CHOICE]->rect.y;
                            draw_red_boundary_move.w = Buttons[QUIT_BUTTON_IA_CHOICE]->rect.w;
                            draw_red_boundary_move.h = Buttons[QUIT_BUTTON_IA_CHOICE]->rect.h;
                        }

                        // a second click 
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                        }

                        // if the two clicks have be done, we quit the game
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_running_game = -1;
                        }

                    }

                    // for the menu button 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[MAIN_MENU_BUTTON_IA_CHOICE]->rect) && Buttons[EASY_DIFFICULTY_BUTTON]->state == UNACTIVE && Buttons[MODERATE_DIFFICULTY_BUTTON]->state == UNACTIVE && Buttons[HARD_DIFFICULTY_BUTTON]->state == UNACTIVE){
                        
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[MAIN_MENU_BUTTON_IA_CHOICE]->rect.x;
                            draw_red_boundary_move.y = Buttons[MAIN_MENU_BUTTON_IA_CHOICE]->rect.y;
                            draw_red_boundary_move.w = Buttons[MAIN_MENU_BUTTON_IA_CHOICE]->rect.w;
                            draw_red_boundary_move.h = Buttons[MAIN_MENU_BUTTON_IA_CHOICE]->rect.h;
                            Buttons[MAIN_MENU_BUTTON_IA_CHOICE]->state = ACTIVE;
                        }

                        // a second click 
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                        }

                        // if the two clicks have be done, we go back to the first menu
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_running_game = GAMEPLAY_CHOICE;
                            has_match_started = false;
                            level_IA = NONE;
                            Reset_Buttons_State(Buttons);
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                        }
                    }

                    // for the back button 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[BACK_BUTTON_IA_CHOICE]->rect) && Buttons[EASY_DIFFICULTY_BUTTON]->state == UNACTIVE && Buttons[MODERATE_DIFFICULTY_BUTTON]->state == UNACTIVE && Buttons[HARD_DIFFICULTY_BUTTON]->state == UNACTIVE){
                        
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[BACK_BUTTON_TIME_CHOICE]->rect.x;
                            draw_red_boundary_move.y = Buttons[BACK_BUTTON_TIME_CHOICE]->rect.y;
                            draw_red_boundary_move.w = Buttons[BACK_BUTTON_TIME_CHOICE]->rect.w;
                            draw_red_boundary_move.h = Buttons[BACK_BUTTON_TIME_CHOICE]->rect.h;
                            Buttons[BACK_BUTTON_TIME_CHOICE]->state = ACTIVE;
                        }

                        // a second click 
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                        }

                        // if the two clicks have be done, we go back to the IA_type choice
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_running_game = COLOR_CHOICE;
                            has_match_started = false;
                            level_IA = NONE;
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                    }

                    // for the next button 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[NEXT_BUTTON_IA_CHOICE]->rect)){
                        
                        // a second click 
                        if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                        }

                        // if the two clicks have be done, we go to the time choice menu
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            is_running_game = TIME_CHOICE;
                            has_match_started = false;
                            Reset_Buttons_State(Buttons);
                        }
                    }

                    // when we don't click on anything, we reset the buttons state
                    else {
                        is_clicked_1 = 0;
                        is_clicked_2 = 0;
                        Reset_Buttons_State(Buttons);
                    }
                    
                }

                // then we choose the time mode of the game
                else if (is_running_game == TIME_CHOICE){
                    
                    // if we clicked on the short blitz button 
                    if (is_point_in_rect(event.button.x, event.button.y, Buttons[SHORT_BLITZ_BUTTON]->rect)){
                    
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[SHORT_BLITZ_BUTTON]->rect.x;
                            draw_red_boundary_move.y = Buttons[SHORT_BLITZ_BUTTON]->rect.y;
                            draw_red_boundary_move.w = Buttons[SHORT_BLITZ_BUTTON]->rect.w;
                            draw_red_boundary_move.h = Buttons[SHORT_BLITZ_BUTTON]->rect.h;
                            Buttons[SHORT_BLITZ_BUTTON]->state = ACTIVE;
                            timer_game_mode = 3*60;
                            time_of_blitz_mode = 5;
                        }

                        // if another click is done, we cancel the selection
                        else if (is_clicked_1 ==1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                            Reset_Buttons_State(Buttons);
                        }

                        // if two clicks have been done, we cancel the selection
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                        }
                    }

                    // if we click on the long blitz button 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[LONG_BLITZ_BUTTON]->rect)){
                    
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[LONG_BLITZ_BUTTON]->rect.x;
                            draw_red_boundary_move.y = Buttons[LONG_BLITZ_BUTTON]->rect.y;
                            draw_red_boundary_move.w = Buttons[LONG_BLITZ_BUTTON]->rect.w;
                            draw_red_boundary_move.h = Buttons[LONG_BLITZ_BUTTON]->rect.h;
                            Buttons[LONG_BLITZ_BUTTON]->state = ACTIVE;
                            timer_game_mode = 5*60;
                            time_of_blitz_mode = 3;
                        }

                        // if another click is done, we cancel the selection
                        else if (is_clicked_1 ==1 && is_clicked_2 == 0){
                            is_clicked_1 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                        // if two clicks have been done, we cancel the selection
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                    }

                    // if we click on the short time mode game 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[SHORT_BUTTON]->rect)){
                    
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[SHORT_BUTTON]->rect.x;
                            draw_red_boundary_move.y = Buttons[SHORT_BUTTON]->rect.y;
                            draw_red_boundary_move.w = Buttons[SHORT_BUTTON]->rect.w;
                            draw_red_boundary_move.h = Buttons[SHORT_BUTTON]->rect.h;
                            Buttons[SHORT_BUTTON]->state = ACTIVE;
                            timer_game_mode = 10*60;
                            time_of_blitz_mode = 0;
                        }

                        // if another click is done, we cancel the selection
                        else if (is_clicked_1 ==1 && is_clicked_2 == 0){
                            is_clicked_1 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                        // if two clicks have been done, we cancel the selection
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);   
                        }

                    }

                    // if we click on the medium time mode game 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[MODERATE_BUTTON]->rect)){
                    
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[MODERATE_BUTTON]->rect.x;
                            draw_red_boundary_move.y = Buttons[MODERATE_BUTTON]->rect.y;
                            draw_red_boundary_move.w = Buttons[MODERATE_BUTTON]->rect.w;
                            draw_red_boundary_move.h = Buttons[MODERATE_BUTTON]->rect.h;
                            Buttons[MODERATE_BUTTON]->state = ACTIVE;
                            timer_game_mode = 30*60;
                            time_of_blitz_mode = 0;
                        }

                        // if another click is done, we cancel the selection
                        else if (is_clicked_1 ==1 && is_clicked_2 == 0){
                            is_clicked_1 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                        // if two clicks have been done, we cancel the selection
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                    }

                    // if we click on the long time mode game 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[LONG_BUTTON]->rect)){
                    
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[LONG_BUTTON]->rect.x;
                            draw_red_boundary_move.y = Buttons[LONG_BUTTON]->rect.y;
                            draw_red_boundary_move.w = Buttons[LONG_BUTTON]->rect.w;
                            draw_red_boundary_move.h = Buttons[LONG_BUTTON]->rect.h;
                            Buttons[LONG_BUTTON]->state = ACTIVE;
                            timer_game_mode = 60*60;
                            time_of_blitz_mode = 0;
                        }

                        // if another click is done, we cancel the selection
                        else if (is_clicked_1 ==1 && is_clicked_2 == 0){
                            is_clicked_1 = 0;
                            Reset_Buttons_State(Buttons);   
                        }

                        // if two clicks have been done, we cancel the selection
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                    }

                    // if we click on the quit button, we go out of the game 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[QUIT_BUTTON_TIME_CHOICE]->rect) && Buttons[SHORT_BLITZ_BUTTON]->state == UNACTIVE && Buttons[LONG_BLITZ_BUTTON]->state == UNACTIVE && Buttons[SHORT_BUTTON]->state == UNACTIVE && Buttons[MODERATE_BUTTON]->state == UNACTIVE && Buttons[LONG_BUTTON]->state == UNACTIVE){
                        
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[QUIT_BUTTON_TIME_CHOICE]->rect.x;
                            draw_red_boundary_move.y = Buttons[QUIT_BUTTON_TIME_CHOICE]->rect.y;
                            draw_red_boundary_move.w = Buttons[QUIT_BUTTON_TIME_CHOICE]->rect.w;
                            draw_red_boundary_move.h = Buttons[QUIT_BUTTON_TIME_CHOICE]->rect.h;
                        }

                        // a second click 
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                        }

                        // if the two clicks have be done, we quit the game
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_running_game = -1;
                        }

                    }
                
                    // if we click on the main menu button, we go back to the first menu
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect) && Buttons[SHORT_BLITZ_BUTTON]->state == UNACTIVE && Buttons[LONG_BLITZ_BUTTON]->state == UNACTIVE && Buttons[SHORT_BUTTON]->state == UNACTIVE && Buttons[MODERATE_BUTTON]->state == UNACTIVE && Buttons[LONG_BUTTON]->state == UNACTIVE){
                    
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect.x;
                            draw_red_boundary_move.y = Buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect.y;
                            draw_red_boundary_move.w = Buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect.w;
                            draw_red_boundary_move.h = Buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect.h;
                            Buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->state = ACTIVE;
                        }

                        // a second click 
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                        }

                        // if the two clicks have be done, we go back to the first menu
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_running_game = GAMEPLAY_CHOICE;
                            has_match_started = false;
                            level_IA = NONE;
                            Reset_Buttons_State(Buttons);
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                        }

                    }

                    // if we click on the back button, we go back to the IA_type choice
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[BACK_BUTTON_TIME_CHOICE]->rect) && Buttons[SHORT_BLITZ_BUTTON]->state == UNACTIVE && Buttons[LONG_BLITZ_BUTTON]->state == UNACTIVE && Buttons[SHORT_BUTTON]->state == UNACTIVE && Buttons[MODERATE_BUTTON]->state == UNACTIVE && Buttons[LONG_BUTTON]->state == UNACTIVE){
                    
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[BACK_BUTTON_TIME_CHOICE]->rect.x;
                            draw_red_boundary_move.y = Buttons[BACK_BUTTON_TIME_CHOICE]->rect.y;
                            draw_red_boundary_move.w = Buttons[BACK_BUTTON_TIME_CHOICE]->rect.w;
                            draw_red_boundary_move.h = Buttons[BACK_BUTTON_TIME_CHOICE]->rect.h;
                            Buttons[BACK_BUTTON_TIME_CHOICE]->state = ACTIVE;
                        }

                        // a second click 
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                        }

                        // if the two clicks have be done, we go back to the IA_type choice
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_running_game = DIFFICULTY_CHOICE;
                            has_match_started = false;
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                    }

                    // if we click on the load button, we go to the game, but it's only a second click 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[LOAD_BUTTON]->rect)){
                    
                        // a second click 
                        if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                        }

                        // if the two clicks have be done, we load the game by changing the type of part we're in, we go to CHESSBOARD_RENDER
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            is_running_game = CHESSBOARD_RENDER;
                            has_match_started = false;
                            Reset_Buttons_State(Buttons);
                        }

                    }

                    // when we don't click on anything, we reset the buttons state
                    else {
                        is_clicked_1 = 0;
                        is_clicked_2 = 0;
                        Reset_Buttons_State(Buttons);
                    }

                }

                // when we're in the game, pressing the mouse button do things differently than in the menu
                else if (is_running_game == CHESSBOARD_RENDER){

                    // making the translation of the mouse click to the row and the column of the board
                    int row = (event.button.y-WINDOW_TOP_MARGIN) / SQUARE_SIZE;
                    int col = (event.button.x-WINDOW_LEFT_MARGIN) / SQUARE_SIZE;
                    
                    bool is_player_playing_human = true;
                    if (players->is_playing == Player1 && players->is_player1_an_IA == IA){
                        is_player_playing_human = false;
                    }
                    else if (players->is_playing == Player2 && players->is_player2_an_IA == IA){
                        is_player_playing_human = false;
                    }
                    /*
                    if (is_player_playing_human == false){
                        printf("the player that is playing is an IA\n");
                    }
                    else if (is_player_playing_human == true){
                        printf("the player that is playing is a human\n");
                    }
                    */
                    /*
                    if (is_player_playing_human == false){

                        Move* move_test_IA = Create_Move(0, 0, 0, 0);  

                        if (test_IA == 0){
                            test_IA = 1;

                            // moving a pawn
                            move->previous_row = 1;
                            move->previous_col = 1;
                            move->destination_row = 3;
                            move->destination_col = 1;
                            Make_Move(board, move, players);

                        }
                        else if (test_IA == 1){
                            test_IA = 2;

                            // moving a knight
                            move->previous_row = 0;
                            move->previous_col = 6;
                            move->destination_row = 2;
                            move->destination_col = 7;
                            Make_Move(board, move, players);

                        }
                        else if (test_IA == 2){
                            test_IA = 3;

                            // moving a pawn 
                            move->previous_row = 1;
                            move->previous_col = 0;
                            move->destination_row = 3;
                            move->destination_col = 0;
                            Make_Move(board, move, players);

                        }
                        else if (test_IA == 3){
                            test_IA = 4;

                            // moving a pawn
                            move->previous_row = 1;
                            move->previous_col = 2;
                            move->destination_row = 3;
                            move->destination_col = 2;
                            Make_Move(board, move, players);

                        }

                        // free the test move of the IA
                        Destroy_Move(move_test_IA);

                        continue;
                    }
                    */

                    // if we click on the screen but it's IA play, we make it play 
                    if (is_player_playing_human == false && has_match_started == true){
                        int IA_color = players->color_player_that_is_playing;
                        bool is_move_done = false;
                        while (is_move_done == false){
                            IA_Play(move, board, level_IA, IA_color);
                            // printf("IA_color : %d\n", IA_color);

                            // getting if a rock was done
                            int is_rock_possible_type_IA = Is_Rock_Possible(move, State_Of_RockandCheck, board);
                            // getting if an en passant was done
                            bool is_en_passant_possible_IA = Is_En_Passant_Possible(move, board, Pawn_Move_State);

                            // if a piece is taken, we need to know what type and what color it is, in case we want to undo it later, we can track the piece that has been taken to reinstall it on the board
                            int piece_taken_type_IA = NOTHING;
                            int piece_taken_color_IA = NO_COLOR;
                            // if a move is valid, then we can also ask if a piece is taken, and if it's the case, we can know what type and what color it is
                            if (Will_Capture(move, board) == true && Is_Move_Valid(move, board, State_Of_RockandCheck, Pawn_Move_State) == true){
                                piece_taken_type_IA = board[move->destination_row][move->destination_col]->type;
                                piece_taken_color_IA = board[move->destination_row][move->destination_col]->color;
                            }
                            if (is_en_passant_possible_IA == true){
                                if (board[move->previous_row][move->previous_col]->color == WHITE){
                                    piece_taken_type_IA = PAWN;
                                    piece_taken_color_IA = BLACK;
                                }
                                else if (board[move->previous_row][move->previous_col]->color == BLACK){
                                    piece_taken_type_IA = PAWN;
                                    piece_taken_color_IA = WHITE;
                                }
                            }
                            // if you touch the piece once, as in the real game, you're forced to play this piece, there isn't any way to cancel the move
                            // making the move if it's valid, here we don't care about the special moves and what it does to other pieces
                            // we will need to do it in the future, here we also don't care about the check
                            if (Is_Move_Valid(move, board, State_Of_RockandCheck, Pawn_Move_State) == true && board[move->previous_row][move->previous_col]->color == IA_color){

                                // making the move log update that is crucial for Make_Move to work since we go searching for an index actual_size-1 and only adding an element to Move_Log will make actual_size-1 positive, not to have a segmentation fault
                                // but only a valid move will be added to the log
                                Move_Log_Element* element = Create_Element_Move_Log();
                                Change_Move_Log_Element(element, move->previous_row, move->previous_col, move->destination_row, move->destination_col, NO_CHECK, piece_taken_type_IA, piece_taken_color_IA, is_rock_possible_type_IA, is_en_passant_possible_IA);
                                Move_Log_array_MESSAGE_TYPE message = Add_Element_to_the_end_of_Move_Log_array(Log, element);
                                if (message != LOG_LIST_SUCCESS){
                                    printf("Error: the log is full\n");
                                    is_running_game = -1;
                                }

                                Destroy_Move_Log_Element(element);
                                    
                                // if we're in a blitz mode, the time of the player that is playing is increased by the time of the blitz mode after each move he makes
                                if (players->is_playing == Player1){
                                    seconds_remaining_player_1 = seconds_remaining_player_1 + time_of_blitz_mode;
                                }
                                else if (players->is_playing == Player2){
                                    seconds_remaining_player_2 = seconds_remaining_player_2 + time_of_blitz_mode;
                                }

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
                                else if (is_en_passant_possible_IA == true){

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
                                is_move_done = true;
                            }
                        }
                    }

                    // it need to be in the board
                    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && has_match_started == true && is_player_playing_human == true){
                        
                        // moves that suppose that we're the white player and the IA is the black player
       

                        // if no piece has been selected
                        // it marked the first piece as selected if it's a piece of the player that is playing (looking at its color), and if it's not a nothing piece, so it's a piece that can be moved
                        // then it's the first coordinate of the move
                        if (is_clicked_1==0 && board[row][col]->type != NOTHING && board[row][col]->color == players->color_player_that_is_playing) {
                            // update the click, of the source piece here
                            is_clicked_1 = 1;
                            // start the move
                            move->previous_row = row;
                            move->previous_col = col;

                            // draw the red boundary here since it's the first click and the destination is not yet selected
                            draw_red_boundary_move.x = col * SQUARE_SIZE+WINDOW_LEFT_MARGIN;
                            draw_red_boundary_move.y = row * SQUARE_SIZE+WINDOW_TOP_MARGIN;
                            draw_red_boundary_move.w = SQUARE_SIZE;
                            draw_red_boundary_move.h = SQUARE_SIZE;
                            is_clicked_on_board = true;
                        }

                        // if a piece has been selected, but not its destination yet, we searched for its heading
                        // the destination is the second coordinate of the move, it need not to be one of the player's piece
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            // update the position of the destination with the position of the mouse
                            move->destination_row = row;
                            move->destination_col = col;

                            // the second click has been made
                            is_clicked_2 = 1;

                        }

                        if (is_clicked_1 == 1 && is_clicked_2 == 1) {
                            // reseting the selected piece
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            is_clicked_on_board = false;

                            // getting if a rock was done
                            int is_rock_possible_type = Is_Rock_Possible(move, State_Of_RockandCheck, board);
                            // getting if an en passant was done
                            bool is_en_passant_possible = Is_En_Passant_Possible(move, board, Pawn_Move_State);

                            // if a piece is taken, we need to know what type and what color it is, in case we want to undo it later, we can track the piece that has been taken to reinstall it on the board
                            int piece_taken_type = NOTHING;
                            int piece_taken_color = NO_COLOR;
                            // if a move is valid, then we can also ask if a piece is taken, and if it's the case, we can know what type and what color it is
                            if (Will_Capture(move, board) == true && Is_Move_Valid(move, board, State_Of_RockandCheck, Pawn_Move_State) == true){
                                piece_taken_type = board[move->destination_row][move->destination_col]->type;
                                piece_taken_color = board[move->destination_row][move->destination_col]->color;
                            }
                            if (is_en_passant_possible == true){
                                if (board[move->previous_row][move->previous_col]->color == WHITE){
                                    piece_taken_type = PAWN;
                                    piece_taken_color = BLACK;
                                }
                                else if (board[move->previous_row][move->previous_col]->color == BLACK){
                                    piece_taken_type = PAWN;
                                    piece_taken_color = WHITE;
                                }
                            }

                            /*
                            printf("\nplayer that was playing : %d\n", players->is_playing);
                            printf("was the rock possible ? %d\n", is_rock_possible_type);
                            printf("the move that has been made : (%d,%d) --> (%d,%d)\n", move->previous_row, move->previous_col, move->destination_row, move->destination_col);
                            printf("state of the rock and check :\n");
                            printf("for the white player :\n");
                            printf("left_rook_moved : %d, right_rook_moved : %d, king_moved : %d, , king checked %d, rock_done : %d\n", State_Of_RockandCheck->white_left_rook_moved, State_Of_RockandCheck->white_right_rook_moved, State_Of_RockandCheck->white_king_moved, State_Of_RockandCheck->is_white_king_checked, State_Of_RockandCheck->white_rock_done);
                            printf("for the black player :\n");
                            printf("left_rook_moved : %d, right_rook_moved : %d, king_moved : %d, , king checked %d, rock_done : %d\n", State_Of_RockandCheck->black_left_rook_moved, State_Of_RockandCheck->black_right_rook_moved, State_Of_RockandCheck->black_king_moved, State_Of_RockandCheck->is_black_king_checked, State_Of_RockandCheck->black_rock_done);
                            */

                            // if you touch the piece once, as in the real game, you're forced to play this piece, there isn't any way to cancel the move
                            // making the move if it's valid, here we don't care about the special moves and what it does to other pieces
                            // we will need to do it in the future, here we also don't care about the check
                            if (Is_Move_Valid(move, board, State_Of_RockandCheck, Pawn_Move_State) == true){

                                // making the move log update that is crucial for Make_Move to work since we go searching for an index actual_size-1 and only adding an element to Move_Log will make actual_size-1 positive, not to have a segmentation fault
                                // but only a valid move will be added to the log
                                Move_Log_Element* element = Create_Element_Move_Log();
                                Change_Move_Log_Element(element, move->previous_row, move->previous_col, move->destination_row, move->destination_col, NO_CHECK, piece_taken_type, piece_taken_color, is_rock_possible_type, is_en_passant_possible);
                                Move_Log_array_MESSAGE_TYPE message = Add_Element_to_the_end_of_Move_Log_array(Log, element);
                                if (message != LOG_LIST_SUCCESS){
                                    printf("Error: the log is full\n");
                                    is_running_game = -1;
                                }

                                Destroy_Move_Log_Element(element);
                                
                                // if we're in a blitz mode, the time of the player that is playing is increased by the time of the blitz mode after each move he makes
                                if (players->is_playing == Player1){
                                    seconds_remaining_player_1 = seconds_remaining_player_1 + time_of_blitz_mode;
                                }
                                else if (players->is_playing == Player2){
                                    seconds_remaining_player_2 = seconds_remaining_player_2 + time_of_blitz_mode;
                                }

                                // trying to make the rock effective by getting the real moves linked to the rock that has been made
                                if (is_rock_possible_type != NO_ROCK){
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
                                else if (is_en_passant_possible == true){

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

                            /*
                            printf("\npawn move state :\n");
                            printf("move of the last pawn (%d,%d) --> (%d,%d)\n", Pawn_Move_State->move_made->previous_row, Pawn_Move_State->move_made->previous_col, Pawn_Move_State->move_made->destination_row, Pawn_Move_State->move_made->destination_col);
                            if (Pawn_Move_State->has_moved_2_squares == true){
                                printf("the last pawn has moved two squares\n");
                            }
                            else {
                                printf("the last pawn has not moved two squares\n");
                            }
                            */
                            // print_rock_state_and_captured_pieces(Captured_Pieces_and_Score, State_Of_RockandCheck);
                        
                        }

                    }
                        
                    // otherwise it can be on some buttons that are on the right side of the window
                    // for the start button 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[START_BUTTON]->rect)){
                        
                        Buttons[START_BUTTON]->state = ACTIVE;
                        has_match_started = true;
                    
                    }

                    // for the restart button 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[RESTART_BUTTON_IN_GAME]->rect)&& Buttons[NEW_GAME_BUTTON_IN_GAME]->state == UNACTIVE && Buttons[QUIT_BUTTON_IN_GAME]->state == UNACTIVE && Buttons[UNDO_BUTTON]->state == UNACTIVE){
                        
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[RESTART_BUTTON_IN_GAME]->rect.x;
                            draw_red_boundary_move.y = Buttons[RESTART_BUTTON_IN_GAME]->rect.y;
                            draw_red_boundary_move.w = Buttons[RESTART_BUTTON_IN_GAME]->rect.w;
                            draw_red_boundary_move.h = Buttons[RESTART_BUTTON_IN_GAME]->rect.h;
                            Buttons[RESTART_BUTTON_IN_GAME]->state = ACTIVE;
                        }

                        // a second click 
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            if (is_clicked_on_board == false){
                                is_clicked_2 = 1;
                            }
                            else {
                                is_clicked_1 = 0;
                                is_clicked_2 = 0;
                                is_clicked_on_board = false;
                            }
                        }

                        // if the two clicks have be done, we reset the game to its original parameters
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_running_game = CHESSBOARD_RENDER;
                            has_match_started = false;
                            // reset the players, the board, the log, the captured pieces, the state of the rock and the check, the timer
                            
                            players->is_playing = Player1;
                            loosing_player = -1;
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                            seconds_remaining_player_1 = timer_game_mode;
                            seconds_remaining_player_2 = timer_game_mode;

                            // reset the board
                            Reset_Board(board);

                            // reset the log (putting the size to 0 is enough)
                            Log->actual_size = 0;

                            // reset the captured pieces
                            Reset_Captured_Piece_and_Score(Captured_Pieces_and_Score);

                            // reset the state of the rock and the check
                            Reset_State_Of_Rock_and_Check(State_Of_RockandCheck);

                            // reset the tiles pawn structures
                            Reset_Tiles_Pawn(Pawn_Move_State);

                            // reset the players, but since the parameters are the same, we don't need to reset everything from the beginning concerning the player type, the color, the name, etc
                            players->is_playing = Player1;
                            players->color_player_that_is_playing = WHITE;
                        }
                    }

                    // for the new_game button 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[NEW_GAME_BUTTON_IN_GAME]->rect) && Buttons[RESTART_BUTTON_IN_GAME]->state == UNACTIVE && Buttons[QUIT_BUTTON_IN_GAME]->state == UNACTIVE && Buttons[UNDO_BUTTON]->state == UNACTIVE){
                        
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[NEW_GAME_BUTTON_IN_GAME]->rect.x;
                            draw_red_boundary_move.y = Buttons[NEW_GAME_BUTTON_IN_GAME]->rect.y;
                            draw_red_boundary_move.w = Buttons[NEW_GAME_BUTTON_IN_GAME]->rect.w;
                            draw_red_boundary_move.h = Buttons[NEW_GAME_BUTTON_IN_GAME]->rect.h;
                            Buttons[NEW_GAME_BUTTON_IN_GAME]->state = ACTIVE;
                        }

                        // a second click 
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            if (is_clicked_on_board == false){
                                is_clicked_2 = 1;
                            }
                            else {
                                is_clicked_1 = 0;
                                is_clicked_2 = 0;
                                is_clicked_on_board = false;
                            }
                        }

                        // if the two clicks have be done, we go back to the first load menu
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_running_game = GAMEPLAY_CHOICE;
                            has_match_started = false;
                            Reset_Buttons_State(Buttons);
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                        }
                    }

                    // for the quit button 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[QUIT_BUTTON_IN_GAME]->rect) && Buttons[RESTART_BUTTON_IN_GAME]->state == UNACTIVE && Buttons[NEW_GAME_BUTTON_IN_GAME]->state == UNACTIVE && Buttons[UNDO_BUTTON]->state == UNACTIVE){
                        
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[QUIT_BUTTON_IN_GAME]->rect.x;
                            draw_red_boundary_move.y = Buttons[QUIT_BUTTON_IN_GAME]->rect.y;
                            draw_red_boundary_move.w = Buttons[QUIT_BUTTON_IN_GAME]->rect.w;
                            draw_red_boundary_move.h = Buttons[QUIT_BUTTON_IN_GAME]->rect.h;
                        }

                        // a second click 
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            if (is_clicked_on_board == false){
                                is_clicked_2 = 1;
                            }
                            else {
                                is_clicked_1 = 0;
                                is_clicked_2 = 0;
                                is_clicked_on_board = false;
                            }
                        }

                        // if the two clicks have be done, we quit the game
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_running_game = -1;
                        }
                    }

                    // for the undo button 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[UNDO_BUTTON]->rect) && Buttons[RESTART_BUTTON_IN_GAME]->state == UNACTIVE && Buttons[NEW_GAME_BUTTON_IN_GAME]->state == UNACTIVE && Buttons[QUIT_BUTTON_IN_GAME]->state == UNACTIVE){
                        
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[UNDO_BUTTON]->rect.x;
                            draw_red_boundary_move.y = Buttons[UNDO_BUTTON]->rect.y;
                            draw_red_boundary_move.w = Buttons[UNDO_BUTTON]->rect.w;
                            draw_red_boundary_move.h = Buttons[UNDO_BUTTON]->rect.h;
                            Buttons[UNDO_BUTTON]->state = ACTIVE;
                        }

                        // a second click 
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            if (is_clicked_on_board == false){
                                is_clicked_2 = 1;
                            }
                            else {
                                is_clicked_1 = 0;
                                is_clicked_2 = 0;
                                is_clicked_on_board = false;
                            }
                        }

                        // if the two clicks have be done, we undo the last move
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                            
                            /*
                            there is a lot to do here to undo the last move and reinstate every parameters as they were before the move
                            */

                        }
                    }

                    // when we don't click on anything, we reset the buttons state
                    else {
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                }

                // if we're in the victory menu
                else if (is_running_game == VICTORY_MENU){
                    // if we're in the victory menu, we need to check if a button has been clicked to quit the game or to go play again

                    // if we click on the new game button, we go back to the first load menu
                    if (is_point_in_rect(event.button.x, event.button.y, Buttons[NEW_GAME_BUTTON_VICTORY_MENU]->rect)){
                        is_running_game = GAMEPLAY_CHOICE;
                        has_match_started = false;
                        Buttons[START_BUTTON]->state = UNACTIVE;
                    }

                    // if we click on the restart button, we restart the game back to with the same parameters
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[RESTART_BUTTON_VICTORY_MENU]->rect)){
                        is_running_game = CHESSBOARD_RENDER;
                        has_match_started = false;
                        Buttons[START_BUTTON]->state = UNACTIVE;
                        // reset the players, the board, the log, the captured pieces, the state of the rock and the check, the timer
                        
                        players->is_playing = Player1;
                        loosing_player = -1;
                        is_clicked_1 = 0;
                        is_clicked_2 = 0;
                        seconds_remaining_player_1 = timer_game_mode;
                        seconds_remaining_player_2 = timer_game_mode;

                        // reset the board
                        Reset_Board(board);

                        // reset the log (putting the size to 0 is enough)
                        Log->actual_size = 0;

                        // reset the captured pieces
                        Reset_Captured_Piece_and_Score(Captured_Pieces_and_Score);

                        // reset the state of the rock and the check
                        Reset_State_Of_Rock_and_Check(State_Of_RockandCheck);

                        // reset the tiles pawn structures
                        Reset_Tiles_Pawn(Pawn_Move_State);

                        // reset the players, but since the parameters are the same, we don't need to reset everything from the beginning concerning the player type, the color, the name, etc
                        players->is_playing = Player1;
                        players->color_player_that_is_playing = WHITE;

                    }

                    // if we click on the quit button, we quit the game
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[QUIT_BUTTON_VICTORY_MENU]->rect)){
                        is_running_game = -1;
                    }

                }

            }
        }

        // the timer is also present when we're in the game 
        // the game need to be running
        if (is_running_game == CHESSBOARD_RENDER && has_match_started == true){

            // Countdown for each player at the end of the event that happened
            // for player 2
            if (players->is_playing == Player2 && players->is_player2_an_IA == HUMAN) {
                if (seconds_remaining_player_2 > 0) {
                    int current_time = SDL_GetTicks();
                    int elapsed_time = current_time - last_frame_time;
                    if (elapsed_time >= 1000) {
                        seconds_remaining_player_2--;
                        last_frame_time = current_time;
                        if (last_second_player_2 != seconds_remaining_player_2) {
                            // printf("Current time remaining for player 2 : %d seconds\n", seconds_remaining_player_2);
                            last_second_player_2 = seconds_remaining_player_2;
                        }
                    }
                } 
                else {
                    loosing_player=Player2;
                }
            }
            
            // for player 1
            else if (players->is_playing == Player1 && players->is_player1_an_IA == HUMAN) {
                if (seconds_remaining_player_1 > 0) {
                    int current_time = SDL_GetTicks();
                    int elapsed_time = current_time - last_frame_time;
                    if (elapsed_time >= 1000) {
                        seconds_remaining_player_1--;
                        last_frame_time = current_time;
                        if (last_second_player_1 != seconds_remaining_player_1) {
                            // printf("Current time remaining for player 1 : %d seconds\n", seconds_remaining_player_1);
                            last_second_player_1 = seconds_remaining_player_1;
                        }
                    }
                } 
                else {
                    loosing_player=Player1;
                }
            }
        
        }


        // the render is not the same if we're in the game or in the menu
        if (is_running_game == GAMEPLAY_CHOICE || is_running_game == COLOR_CHOICE || is_running_game == DIFFICULTY_CHOICE || is_running_game == TIME_CHOICE ){
            // reset the renderer, the screen of the graphic card
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            // show the load menu
            Show_Load_Menu(renderer, is_running_game, Buttons, is_clicked_1, is_clicked_2, draw_red_boundary_move);

            // update the renderer by presenting the new screen
            SDL_RenderPresent(renderer);

            // in the menu, we reset the game parameters
            players->is_playing = Player1;
            loosing_player = -1;
            seconds_remaining_player_1 = timer_game_mode;
            seconds_remaining_player_2 = timer_game_mode;

            // reset the board
            Reset_Board(board);

            // reset the log (putting the size to 0 is enough)
            Log->actual_size = 0;

            // reset the captured pieces
            Reset_Captured_Piece_and_Score(Captured_Pieces_and_Score);

            // reset the state of the rock and the check
            Reset_State_Of_Rock_and_Check(State_Of_RockandCheck);
        }

        // if we're in the game, we show the chess board
        if (is_running_game == CHESSBOARD_RENDER){
            // reset the renderer, the screen of the graphic card
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            // show the buttons in the game
            Show_Menu_Button_in_Game(renderer, Buttons);

            // show the captured pieces
            Show_Captured_Pieces(renderer, Captured_Pieces_and_Score);

            // Draw the score of the game (drawing it next to the piece captured, on the winning side)
            int number = Captured_Pieces_and_Score->score;
            int x;
            int y;
            if (Captured_Pieces_and_Score->player_that_is_winning == WHITE){
                y=WINDOW_HEIGHT-WINDOW_TOP_MARGIN+20;
                x=WINDOW_LEFT_MARGIN + (2*SQUARE_SIZE/10-10)*Captured_Pieces_and_Score->number_of_black_pieces_captured+30;
            }
            else if (Captured_Pieces_and_Score->player_that_is_winning == BLACK){
                y=20;
                x=WINDOW_LEFT_MARGIN + (2*SQUARE_SIZE/10-10)*Captured_Pieces_and_Score->number_of_white_pieces_captured+30;
            }
            
            while (number > 0) {
                int digit = number % 10;
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set color to white
                for (int i = 0; i < FONT_HEIGHT; i++) {
                    for (int j = 0; j < FONT_WIDTH; j++) {
                        if (font[digit][j] & (1 << (FONT_WIDTH - i - 1))) {
                            SDL_RenderDrawPoint(renderer, x + j, y + i);
                        }
                    }
                }
                x -= FONT_WIDTH/3; // Move right for the next digit
                number /= 10;
            }

            // show the timer
            Show_Updated_Timer(renderer, seconds_remaining_player_1, seconds_remaining_player_2, players->is_playing);


            /* only the log is still missing here */


            // show the chess board
            Show_Chess_Board(renderer, board, is_clicked_1, is_clicked_2, draw_red_boundary_move);

            // update the renderer by presenting the new screen
            SDL_RenderPresent(renderer);

            if (loosing_player != -1){
                is_running_game = is_running_game+1;
            }
        }

        // if we're in the win menu screen 
        if (is_running_game == VICTORY_MENU){
            // reset the renderer, the screen of the graphic card
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            // show the victory menu
            Show_Victory_Menu(renderer, Buttons, loosing_player, players);

            // update the renderer by presenting the new screen
            SDL_RenderPresent(renderer);
        }
        
        
        /*
        // printing the players stucture state and the IA level if needed
        printf("\n");
        if (players->is_player1_an_IA == IA){
            printf("Player 1 is an IA of level : %d\n", level_IA);
        }
        else if (players->is_player1_an_IA == HUMAN){
            printf("Player 1 is a human\n");
        }
        if (players->is_player2_an_IA == IA){
            printf("Player 2 is an IA of level : %d\n", level_IA);
        }
        else if (players->is_player2_an_IA == HUMAN){
            printf("Player 2 is a human\n");
        }
        */
    }

    
    // free the move
    Destroy_Move(move);

    // clear the buttons
    Destroy_Buttons(NUMBER_OF_BUTTONS, Buttons);

    // clear the players
    Destroy_Players(players);

    // clear the board
    Clear_Board(board);

    // clear the log
    Destroy_Move_Log_array(Log);

    // clear the tiles pawn structures
    Destroy_Tiles_Pawn(Pawn_Move_State);

    // clear the captured pieces
    Destroy_Captured_Piece_and_Score(Captured_Pieces_and_Score, max_size_captured_pieces_array);

    // clear the state of the rock and check
    Destroy_State_Of_Rock_and_Check(State_Of_RockandCheck);

    // clear the graphics and quit the SDL
    clear_graphics(window, renderer);

    // end the code
    return EXIT_SUCCESS;
}