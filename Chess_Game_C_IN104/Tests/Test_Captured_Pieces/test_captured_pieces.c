#include <SDL2/SDL.h>
#include "Constants.h"
#include "Board.h"
#include "Player.h"
#include "Piece.h"
#include "Graphics.h"


// code that see if the state of rock and check is correctly updated after each move 
// it does also look at the captured pieces and the score for the same reason


// initialize the window and the renderer
#define max_size_log_array 1000
int is_running_game = -1; // setup to -1 for false before the initialization of the game
int last_frame_time = 0;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
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
void clear_graphics(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


// function to print the captured pieces and the state of the rock and check
void print_everything(Captured_Piece_and_Score* captured_piece_and_score, State_Of_Rock_and_Check* state_of_rock_and_check){

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


int main (){
    // initializing things 
    is_running_game = initialize_SDL();
    
    // intialize the board
    Piece*** board = Init_Board();

    // we will modify the board so the move we do can be shown on the board
    // we will need to be in a configuration that is not the initial one, where a rock is possible
    // we will do a basic configuration by cleaning the cases (0,5) (0,6) (1,4) (1,5) (1,7) and adding a white pawn in (4,5)
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

    board[1][4]->type = NOTHING;
    board[1][4]->color = NO_COLOR;
    board[1][4]->value = 0;
    board[1][4]->is_alive = false;
    board[1][4]->is_checked = false;
    board[1][4]->is_on_his_start_position = false;

    board[1][5]->type = NOTHING;
    board[1][5]->color = NO_COLOR;
    board[1][5]->value = 0;
    board[1][5]->is_alive = false;
    board[1][5]->is_checked = false;
    board[1][5]->is_on_his_start_position = false;

    board[1][7]->type = NOTHING;
    board[1][7]->color = NO_COLOR;
    board[1][7]->value = 0;
    board[1][7]->is_alive = false;
    board[1][7]->is_checked = false;
    board[1][7]->is_on_his_start_position = false;

    board[4][5]->type = PAWN;
    board[4][5]->color = WHITE;
    board[4][5]->value = PAWN_VALUE;
    board[4][5]->is_alive = true;
    board[4][5]->is_checked = false;
    board[4][5]->is_on_his_start_position = false;

    
    // initialize the move log array
    Move_Log_array* Log = Create_Move_Log_array(max_size_log_array);

    // initialize the captured pieces array
    int max_size_captured_pieces_array = 30;
    Captured_Piece_and_Score* Captured_Pieces_and_Score = Create_Captured_Piece_and_Score(max_size_captured_pieces_array);

    // initialize the structure to have the state of the game concerning rock and check
    State_Of_Rock_and_Check* State_Of_RockandCheck = Create_State_Of_Rock_and_Check();

    // initialize the structure concerning the last play, but only for pawn that moved two squares (for the en passant)
    Tiles_Pawn* Pawn_Move_State = Create_Tiles_Pawn();

    // initialize the players
    Players* players = Create_Players();

    SDL_Rect rect_test = {0, 0, SQUARE_SIZE, SQUARE_SIZE};


    // Creating an event so we can visualize the board and the move made
    // after we can see if everything is working correctly by printing in the terminal the captured pieces and scores as well as the rock state

    SDL_Event event;
    while (is_running_game != -1){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                is_running_game = -1;
            }
            if (event.type == SDL_KEYDOWN){
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    is_running_game = -1;
                }
                // this key make the next move in the game when pressed
                else if (event.key.keysym.sym == SDLK_SPACE){
                    Move_Log_Element* element_of_the_log = Create_Element_Move_Log();
                    // we make the different moves
                    // Creating 5 moves that will need to be implemented in the captured pieces with the make move function
                    // print the captured pieces array after each move to see the progression and where things were added and removed
                    // those will not be check because wde don't have the function for it yet
                    switch (is_running_game){
                        
                        // the first one will be a white pawn moving one square
                        case 0:
                            // create the move in the log
                            Change_Move_Log_Element(element_of_the_log, 4, 5, 3, 5, NO_CHECK, NOTHING, NO_COLOR, NO_ROCK, NO_EN_PASSANT);
                            Move_Log_array_MESSAGE_TYPE message = Add_Element_to_the_end_of_Move_Log_array(Log, element_of_the_log);
                            if (message != LOG_LIST_SUCCESS){
                                printf("Error: the log is full\n");
                                is_running_game = -1;
                            }
                            // make the move on the board
                            Fill_Tile_Pawn(element_of_the_log->move, board, Pawn_Move_State);
                            Make_Move(board, element_of_the_log->move, players);
                            Change_Others_Structures(Log, Captured_Pieces_and_Score, State_Of_RockandCheck, players, board);

                            break;

                        // the second one will be a black pawn moving two squares
                        case 1:
                            // create the move in the log
                            Change_Move_Log_Element(element_of_the_log, 1, 6, 3, 6, NO_CHECK, NOTHING, NO_COLOR, NO_ROCK, NO_EN_PASSANT);
                            Move_Log_array_MESSAGE_TYPE message1 = Add_Element_to_the_end_of_Move_Log_array(Log, element_of_the_log);
                            if (message1 != LOG_LIST_SUCCESS){
                                printf("Error: the log is full\n");
                                is_running_game = -1;
                            }
                            // make the move on the board
                            Fill_Tile_Pawn(element_of_the_log->move, board, Pawn_Move_State);
                            Make_Move(board, element_of_the_log->move, players);
                            Change_Others_Structures(Log, Captured_Pieces_and_Score, State_Of_RockandCheck, players, board);
                            break;
                        
                        // the third one will be the en passant of the black pawn by the white pawn
                        case 2:
                            // create the move in the log
                            Change_Move_Log_Element(element_of_the_log, 3, 5, 2, 6, NO_CHECK, PAWN, BLACK, NO_ROCK, RIGHT_EN_PASSANT);
                            Move_Log_array_MESSAGE_TYPE message2 = Add_Element_to_the_end_of_Move_Log_array(Log, element_of_the_log);
                            if (message2 != LOG_LIST_SUCCESS){
                                printf("Error: the log is full\n");
                                is_running_game = -1;
                            }
                            // make the move on the board
                            Clear_En_Passant_Piece(element_of_the_log->move, board, Pawn_Move_State);
                            Make_Move(board, element_of_the_log->move, players);
                            Change_Others_Structures(Log, Captured_Pieces_and_Score, State_Of_RockandCheck, players, board);
                            Reset_Tiles_Pawn(Pawn_Move_State);
                            break;

                        // the fourth one will be a black rock 
                        case 3:
                            // create the move in the log
                            Change_Move_Log_Element(element_of_the_log, 0, 4, 0, 7, NO_CHECK, NOTHING, NO_COLOR, SHORT_ROCK, NO_EN_PASSANT);
                            Move_Log_array_MESSAGE_TYPE message3 = Add_Element_to_the_end_of_Move_Log_array(Log, element_of_the_log);
                            if (message3 != LOG_LIST_SUCCESS){
                                printf("Error: the log is full\n");
                                is_running_game = -1;
                            }
                            // make the move on the board
                            Move* king_move_during_rock=Create_King_Move_during_Rock(element_of_the_log->move, board, State_Of_RockandCheck);
                            Move* rook_move_during_rock=Create_Rook_Move_during_Rock(element_of_the_log->move, board, State_Of_RockandCheck);
                            Make_Rock_Move(board, element_of_the_log->move, king_move_during_rock, rook_move_during_rock, players);
                            Change_Others_Structures_during_Rock(Log, Captured_Pieces_and_Score, State_Of_RockandCheck, players, board);
                            Destroy_Move(king_move_during_rock);
                            Destroy_Move(rook_move_during_rock);
                            Reset_Tiles_Pawn(Pawn_Move_State);
                            break;
                        
                        // the fifth one will take a white pawn moving one square higher than the black rock
                        case 4:
                            // create the move in the log
                            Change_Move_Log_Element(element_of_the_log, 2, 6, 1, 6, NO_CHECK, NOTHING, NO_COLOR, NO_ROCK, NO_EN_PASSANT);
                            Move_Log_array_MESSAGE_TYPE message4 = Add_Element_to_the_end_of_Move_Log_array(Log, element_of_the_log);
                            if (message4 != LOG_LIST_SUCCESS){
                                printf("Error: the log is full\n");
                                is_running_game = -1;
                            }
                            // make the move on the board
                            Fill_Tile_Pawn(element_of_the_log->move, board, Pawn_Move_State);
                            Make_Move(board, element_of_the_log->move, players);
                            Change_Others_Structures(Log, Captured_Pieces_and_Score, State_Of_RockandCheck, players, board);
                            break;
                    }
                    Destroy_Move_Log_Element(element_of_the_log);
                    is_running_game = is_running_game + 1;
                    if (is_running_game < 6){
                        printf("\n\n\nAfter the %dth move : \n", is_running_game);
                        print_everything(Captured_Pieces_and_Score, State_Of_RockandCheck);
                    }
                }
            }

        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        Show_Chess_Board(renderer, board, 0, 0, rect_test);
        SDL_RenderPresent(renderer);
    }


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

    return EXIT_SUCCESS;
}