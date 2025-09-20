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
 * - the piece will not be restricted in their moves, it's just some coding, here we're focusing on the architecture of the code 
 * - an effort has been made here to use the log, the state of the rock, the captured pieces (we have checked yet if it works correctly, but it should work in theory, so we will test that in the future)
 * - the part (V2) will focus on the implementation of the differents menus during the game
 * - the timer_showing isn't implemented yet, a first step is made to know how it works in the tests_SDL_basics directory, but not being able to download the SDL2_ttf library, we can't show it for now
 * - but we can print it in the terminal, even if it's not the best way to show it, and to the way we would have want it to be shown
 * - the IA isn't implemented yet, we will need to do it in the future (it will change a big part of the code since it will skip a big part of the loop concerning what the code need to go through when a player is playing)
 * - We will not show the captured pieces and score yet, we will need to do it in the future, the same issue has been encountered as for the timer function 
 * - The same for the Move_Log 
 * - we can't ask yet the player names, we will need to do it in the future if possible
 * 
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
// Main function of the game
///////////////////////////////////////////////////////////////////////////////
int main (){

    // initialize the window and the renderer, is_running_game is a global variable that is 0 if the initialization is successful, -1 otherwise
    is_running_game= initialize_SDL();

    // intialize the board
    Piece*** board = Init_Board();

    
    // initialize the move log array
    Move_Log_array* Log = Create_Move_Log_array(max_size_log_array);

    // initialize the captured pieces array
    int max_size_captured_pieces_array = NUMBER_OF_PIECES/2;
    Captured_Piece_and_Score* Captured_Pieces_and_Score = Create_Captured_Piece_and_Score(max_size_captured_pieces_array);

    // initialize the structure to have the state of the game concerning rock and check
    State_Of_Rock_and_Check* State_Of_RockandCheck = Create_State_Of_Rock_and_Check();

    // initialize the players
    Players* players = Create_Players();
    
    // initialize the buttons
    Button** Buttons = Create_Buttons(NUMBER_OF_BUTTONS);


    





    /*
    need to make the basics setup of everything that hasnn't been done yet 
    */


    /*
        doing the game loop

        getting the SDL event 

        make what need to be done on the chess board depending on numerous conditions


        count the timer for each player as in double_timer 


    */

    // making the timer for each player, the time mode will be asked after so this constant here will have no effect later 
    int timer_game_mode=5;

    // time remaining for each player
    int seconds_remaining_player_2 = timer_game_mode;
    int last_second_player_2 = 0;

    int seconds_remaining_player_1 = timer_game_mode;
    int last_second_player_1 = 0;

    // player 0 begin to play 
    // both player 1 and player 2 have 5 seconds to play on the screen, after that it close the window and gave us the player that lose, made it
    int loosing_player=-1;

    // making int variable to know if the first clicked is done and the second clicked is done
    int is_clicked_1 = 0;
    int is_clicked_2 = 0;
    // later there will be more, but here we don't care about the other clicks for buttons, etc, …

    // preparing a move implementation
    Move* move = Create_Move(0, 0, 0, 0);

    // SDL_rect to draw the red boundary when we move a piece to know it's the piece that is selected
    SDL_Rect draw_red_boundary_move={0, 0, SQUARE_SIZE, SQUARE_SIZE};

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

                    // here in this part, touching on the v key will make the game change it's load menu
                    case SDLK_RETURN:
                        if (is_running_game != CHESSBOARD_RENDER){
                            is_running_game+=1;
                            printf("The game is now in the load menu %d\n", is_running_game);
                        }
                        break;

                    // for this part, if we're in the game, pressing the x key will make the game go back to the load menu
                    case SDLK_x:
                        is_running_game=GAMEPLAY_CHOICE;
                        break;
                }
            }

            // taking the mouse event, here it's the mouse button down, so we've pressed the mouse button
            else if (event.type == SDL_MOUSEBUTTONDOWN){
                
                // when we're in the game, pressing the mouse button do things differently than in the menu
                if (is_running_game == CHESSBOARD_RENDER){
                    // making the translation of the mouse click to the row and the column of the board
                    int row = (event.button.y-WINDOW_TOP_MARGIN) / SQUARE_SIZE;
                    int col = (event.button.x-WINDOW_LEFT_MARGIN) / SQUARE_SIZE;
                    
                    // it need to be in the board
                    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE){

                        // if no piece has been selected
                        // it marked the first piece as selected if it's a piece of the player that is playing (looking at its color), and if it's not a nothing piece, so it's a piece that can be moved
                        // then it's the first coordinate of the move
                        if (is_clicked_1 ==0 && board[row][col]->type != NOTHING && board[row][col]->color == players->color_player_that_is_playing && board[row][col]->is_alive) {
                            // update the click, of the source piece here
                            is_clicked_1 = 1;
                            // start the move
                            move->previous_row = row;
                            move->previous_col = col;

                            // draw the red boundary here since it's the first click and the destination is not yet selected
                            draw_red_boundary_move.x = col * SQUARE_SIZE+WINDOW_LEFT_MARGIN;
                            draw_red_boundary_move.y = row * SQUARE_SIZE+WINDOW_TOP_MARGIN;
                        }

                        // if a piece has been selected, but not its destination yet, we searched for its heading
                        // the destination is the second coordinate of the move, it need not to be one of the player's piece
                        else if (is_clicked_1 == 1 && is_clicked_2 ==0 && board[row][col]->color != players->color_player_that_is_playing){
                            // update the position of the destination with the position of the mouse
                            move->destination_row = row;
                            move->destination_col = col;

                            // the second click has been made
                            is_clicked_2 = 1;

                        }

                    }
                
                }

            }

            if (is_clicked_1 == 1 && is_clicked_2 == 1) {
                // reseting the selected piece
                is_clicked_1 = 0;
                is_clicked_2 = 0;

                // making the move log update that is crucial for Make_Move to work since we go searching for an index actual_size-1 and only adding an element to Move_Log will make actual_size-1 positive, not to have a segmentation fault
                Move_Log_Element* element = Create_Element_Move_Log();
                Change_Move_Log_Element(element, move->previous_row, move->previous_col, move->destination_row, move->destination_col, NO_CHECK, NOTHING, NO_COLOR, NO_ROCK);
                Move_Log_array_MESSAGE_TYPE message = Add_Element_to_the_end_of_Move_Log_array(Log, element);
                if (message != LOG_LIST_SUCCESS){
                    printf("Error: the log is full\n");
                    is_running_game = -1;
                }
                Destroy_Move_Log_Element(element);

                // if you touch the piece once, as in the real game, you're forced to play this piece, there isn't any way to cancel the move
                // making the move
                Make_Move(board, move, Log, Captured_Pieces_and_Score, State_Of_RockandCheck, players);
                // changing the player that is playing is included in the Make_Move function
               
            }
        
        }

        // the timer is also present when we're in the game
        if (is_running_game == CHESSBOARD_RENDER){

            // Countdown for each player at the end of the event that happened
            // for player 2
            if (players->is_playing == Player2) {
                if (seconds_remaining_player_2 > 0) {
                    int current_time = SDL_GetTicks();
                    int elapsed_time = current_time - last_frame_time;
                    if (elapsed_time >= 1000) {
                        seconds_remaining_player_2--;
                        last_frame_time = current_time;
                        if (last_second_player_2 != seconds_remaining_player_2) {
                            printf("Current time remaining for player 2 : %d seconds\n", seconds_remaining_player_2);
                            last_second_player_2 = seconds_remaining_player_2;
                        }
                    }
                } 
                else {
                    loosing_player=Player2;
                }
            }
            
            // for player 1
            else if (players->is_playing == Player1) {
                if (seconds_remaining_player_1 > 0) {
                    int current_time = SDL_GetTicks();
                    int elapsed_time = current_time - last_frame_time;
                    if (elapsed_time >= 1000) {
                        seconds_remaining_player_1--;
                        last_frame_time = current_time;
                        if (last_second_player_1 != seconds_remaining_player_1) {
                            printf("Current time remaining for player 1 : %d seconds\n", seconds_remaining_player_1);
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
        if (is_running_game == GAMEPLAY_CHOICE || is_running_game == DIFFICULTY_CHOICE || is_running_game == TIME_CHOICE){
            // reset the renderer, the screen of the graphic card
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            // show the load menu
            Show_Load_Menu(renderer, is_running_game, Buttons);

            // update the renderer by presenting the new screen
            SDL_RenderPresent(renderer);


            // in the menu, we reset the game parameters
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

            // reset the players
            Reset_Players(players);
        }

        // if we're in the game, we show the chess board
        if (is_running_game == CHESSBOARD_RENDER){
            // reset the renderer, the screen of the graphic card
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

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
            Show_Victory_Menu(renderer, Buttons, loosing_player);

            // update the renderer by presenting the new screen
            SDL_RenderPresent(renderer);
        }
        

        

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

    // clear the captured pieces
    Destroy_Captured_Piece_and_Score(Captured_Pieces_and_Score, max_size_captured_pieces_array);

    // clear the state of the rock and check
    Destroy_State_Of_Rock_and_Check(State_Of_RockandCheck);

    // clear the graphics and quit the SDL
    clear_graphics(window, renderer);

    // end the code
    return EXIT_SUCCESS;
}