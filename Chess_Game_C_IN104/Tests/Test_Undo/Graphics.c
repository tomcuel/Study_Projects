#include "Graphics.h"
#include "Image.h"


Button** Create_Buttons(int number_of_buttons){
    Button** Buttons = (Button**)malloc(number_of_buttons * sizeof(Button*));
    // looking for a malloc error
    if (Buttons == NULL){
        printf("Error: malloc failed in Create_Buttons\n");
        return NULL;
    }

    // for each button, we create it
    for (int i = 0; i < number_of_buttons; i++){
        Buttons[i] = (Button*)malloc(sizeof(Button));
        // looking for a malloc error
        if (Buttons[i] == NULL){
            printf("Error: malloc failed in Create_Buttons\n");
            return NULL;
        }
        // setting the state to UNACTIVE for every button
        Buttons[i]->state = UNACTIVE;
    }

    // buttons for the load menu : game play choice
    Buttons[GAMEPLAY_CHOICE_BUTTON]->rect.x = WINDOW_WIDTH/2 - 150;
    Buttons[GAMEPLAY_CHOICE_BUTTON]->rect.y = 50;
    Buttons[GAMEPLAY_CHOICE_BUTTON]->rect.w = 300;
    Buttons[GAMEPLAY_CHOICE_BUTTON]->rect.h = 200;

    Buttons[PLAYER_VS_PLAYER_BUTTON]->rect.x = 250;
    Buttons[PLAYER_VS_PLAYER_BUTTON]->rect.y = 300;
    Buttons[PLAYER_VS_PLAYER_BUTTON]->rect.w = 300;
    Buttons[PLAYER_VS_PLAYER_BUTTON]->rect.h = 200;

    Buttons[PLAYER_VS_AI_BUTTON]->rect.x = WINDOW_WIDTH-250-300;
    Buttons[PLAYER_VS_AI_BUTTON]->rect.y = 300;
    Buttons[PLAYER_VS_AI_BUTTON]->rect.w = 300;
    Buttons[PLAYER_VS_AI_BUTTON]->rect.h = 200;

    Buttons[QUIT_BUTTON_GAME_CHOICE]->rect.x = 250;
    Buttons[QUIT_BUTTON_GAME_CHOICE]->rect.y = 650;
    Buttons[QUIT_BUTTON_GAME_CHOICE]->rect.w = 300;
    Buttons[QUIT_BUTTON_GAME_CHOICE]->rect.h = 200;

    Buttons[NEXT_BUTTON_GAME_CHOICE]->rect.x = WINDOW_WIDTH-250-300;
    Buttons[NEXT_BUTTON_GAME_CHOICE]->rect.y = 650;
    Buttons[NEXT_BUTTON_GAME_CHOICE]->rect.w = 300;
    Buttons[NEXT_BUTTON_GAME_CHOICE]->rect.h = 200;


    // buttons for the color choice menu
    Buttons[COLOR_CHOICE_BUTTON]->rect.x = WINDOW_WIDTH/2 - 150;
    Buttons[COLOR_CHOICE_BUTTON]->rect.y = 50;
    Buttons[COLOR_CHOICE_BUTTON]->rect.w = 300;
    Buttons[COLOR_CHOICE_BUTTON]->rect.h = 200;

    Buttons[BLACK_COLOR_BUTTON]->rect.x = 250;
    Buttons[BLACK_COLOR_BUTTON]->rect.y = 300;
    Buttons[BLACK_COLOR_BUTTON]->rect.w = 300;
    Buttons[BLACK_COLOR_BUTTON]->rect.h = 200;

    Buttons[WHITE_COLOR_BUTTON]->rect.x = WINDOW_WIDTH-550;
    Buttons[WHITE_COLOR_BUTTON]->rect.y = 300;
    Buttons[WHITE_COLOR_BUTTON]->rect.w = 300;
    Buttons[WHITE_COLOR_BUTTON]->rect.h = 200;
    
    Buttons[QUIT_BUTTON_COLOR_CHOICE]->rect.x = 50;
    Buttons[QUIT_BUTTON_COLOR_CHOICE]->rect.y = 650;
    Buttons[QUIT_BUTTON_COLOR_CHOICE]->rect.w = 225;
    Buttons[QUIT_BUTTON_COLOR_CHOICE]->rect.h = 150;

    Buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect.x = WINDOW_WIDTH/2 - 70 - 225;
    Buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect.y = 650;
    Buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect.w = 225;
    Buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect.h = 150;

    Buttons[BACK_BUTTON_COLOR_CHOICE]->rect.x = WINDOW_WIDTH/2 + 70;
    Buttons[BACK_BUTTON_COLOR_CHOICE]->rect.y = 650;
    Buttons[BACK_BUTTON_COLOR_CHOICE]->rect.w = 225;
    Buttons[BACK_BUTTON_COLOR_CHOICE]->rect.h = 150;

    Buttons[NEXT_BUTTON_COLOR_CHOICE]->rect.x = WINDOW_WIDTH - 50 - 225;
    Buttons[NEXT_BUTTON_COLOR_CHOICE]->rect.y = 650;
    Buttons[NEXT_BUTTON_COLOR_CHOICE]->rect.w = 225;
    Buttons[NEXT_BUTTON_COLOR_CHOICE]->rect.h = 150;


    // buttons for the difficulty choice menu
    Buttons[DIFFICULTY_CHOICE_BUTTON]->rect.x = WINDOW_WIDTH/2 - 150;
    Buttons[DIFFICULTY_CHOICE_BUTTON]->rect.y = 50;
    Buttons[DIFFICULTY_CHOICE_BUTTON]->rect.w = 300;
    Buttons[DIFFICULTY_CHOICE_BUTTON]->rect.h = 200;

    Buttons[EASY_DIFFICULTY_BUTTON]->rect.x = 100;
    Buttons[EASY_DIFFICULTY_BUTTON]->rect.y = 300;
    Buttons[EASY_DIFFICULTY_BUTTON]->rect.w = 300;
    Buttons[EASY_DIFFICULTY_BUTTON]->rect.h = 200;

    Buttons[MODERATE_DIFFICULTY_BUTTON]->rect.x = WINDOW_WIDTH/2 - 150;
    Buttons[MODERATE_DIFFICULTY_BUTTON]->rect.y = 300;
    Buttons[MODERATE_DIFFICULTY_BUTTON]->rect.w = 300;
    Buttons[MODERATE_DIFFICULTY_BUTTON]->rect.h = 200;

    Buttons[HARD_DIFFICULTY_BUTTON]->rect.x = WINDOW_WIDTH-400;
    Buttons[HARD_DIFFICULTY_BUTTON]->rect.y = 300;
    Buttons[HARD_DIFFICULTY_BUTTON]->rect.w = 300;
    Buttons[HARD_DIFFICULTY_BUTTON]->rect.h = 200;

    Buttons[QUIT_BUTTON_IA_CHOICE]->rect.x = 50;
    Buttons[QUIT_BUTTON_IA_CHOICE]->rect.y = 650;
    Buttons[QUIT_BUTTON_IA_CHOICE]->rect.w = 225;
    Buttons[QUIT_BUTTON_IA_CHOICE]->rect.h = 150;

    Buttons[MAIN_MENU_BUTTON_IA_CHOICE]->rect.x = WINDOW_WIDTH/2 - 70 - 225;
    Buttons[MAIN_MENU_BUTTON_IA_CHOICE]->rect.y = 650;
    Buttons[MAIN_MENU_BUTTON_IA_CHOICE]->rect.w = 225;
    Buttons[MAIN_MENU_BUTTON_IA_CHOICE]->rect.h = 150;

    Buttons[BACK_BUTTON_IA_CHOICE]->rect.x = WINDOW_WIDTH/2 + 70;
    Buttons[BACK_BUTTON_IA_CHOICE]->rect.y = 650;
    Buttons[BACK_BUTTON_IA_CHOICE]->rect.w = 225;
    Buttons[BACK_BUTTON_IA_CHOICE]->rect.h = 150;

    Buttons[NEXT_BUTTON_IA_CHOICE]->rect.x = WINDOW_WIDTH - 50 - 225;
    Buttons[NEXT_BUTTON_IA_CHOICE]->rect.y = 650;
    Buttons[NEXT_BUTTON_IA_CHOICE]->rect.w = 225;
    Buttons[NEXT_BUTTON_IA_CHOICE]->rect.h = 150;


    // buttons for the time choice menu
    Buttons[TIME_CHOICE_BUTTON]->rect.x = WINDOW_WIDTH/2 - 150;
    Buttons[TIME_CHOICE_BUTTON]->rect.y = 50;
    Buttons[TIME_CHOICE_BUTTON]->rect.w = 300;
    Buttons[TIME_CHOICE_BUTTON]->rect.h = 200;

    Buttons[SHORT_BLITZ_BUTTON]->rect.x = 100;
    Buttons[SHORT_BLITZ_BUTTON]->rect.y = 50;
    Buttons[SHORT_BLITZ_BUTTON]->rect.w = 300;
    Buttons[SHORT_BLITZ_BUTTON]->rect.h = 200;

    Buttons[LONG_BLITZ_BUTTON]->rect.x = WINDOW_WIDTH-300-100;
    Buttons[LONG_BLITZ_BUTTON]->rect.y = 50;
    Buttons[LONG_BLITZ_BUTTON]->rect.w = 300;
    Buttons[LONG_BLITZ_BUTTON]->rect.h = 200;

    Buttons[SHORT_BUTTON]->rect.x = 100;
    Buttons[SHORT_BUTTON]->rect.y = 300;
    Buttons[SHORT_BUTTON]->rect.w = 300;
    Buttons[SHORT_BUTTON]->rect.h = 200;

    Buttons[MODERATE_BUTTON]->rect.x = WINDOW_WIDTH/2 - 150;
    Buttons[MODERATE_BUTTON]->rect.y = 300;
    Buttons[MODERATE_BUTTON]->rect.w = 300;
    Buttons[MODERATE_BUTTON]->rect.h = 200;

    Buttons[LONG_BUTTON]->rect.x = WINDOW_WIDTH-400;
    Buttons[LONG_BUTTON]->rect.y = 300;
    Buttons[LONG_BUTTON]->rect.w = 300;
    Buttons[LONG_BUTTON]->rect.h = 200;

    Buttons[QUIT_BUTTON_TIME_CHOICE]->rect.x = 50;
    Buttons[QUIT_BUTTON_TIME_CHOICE]->rect.y = 650;
    Buttons[QUIT_BUTTON_TIME_CHOICE]->rect.w = 225;
    Buttons[QUIT_BUTTON_TIME_CHOICE]->rect.h = 150;

    Buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect.x = WINDOW_WIDTH/2 - 70 - 225;
    Buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect.y = 650;
    Buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect.w = 225;
    Buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect.h = 150;

    Buttons[BACK_BUTTON_TIME_CHOICE]->rect.x = WINDOW_WIDTH/2 + 70;
    Buttons[BACK_BUTTON_TIME_CHOICE]->rect.y = 650;
    Buttons[BACK_BUTTON_TIME_CHOICE]->rect.w = 225;
    Buttons[BACK_BUTTON_TIME_CHOICE]->rect.h = 150;

    Buttons[LOAD_BUTTON]->rect.x = WINDOW_WIDTH - 50 - 225;
    Buttons[LOAD_BUTTON]->rect.y = 650;
    Buttons[LOAD_BUTTON]->rect.w = 225;
    Buttons[LOAD_BUTTON]->rect.h = 150;


    // buttons for the chessboard
    Buttons[START_BUTTON]->rect.x = WINDOW_WIDTH-25-170;
    Buttons[START_BUTTON]->rect.y = 50;
    Buttons[START_BUTTON]->rect.w = 170;
    Buttons[START_BUTTON]->rect.h = 100;

    Buttons[RESTART_BUTTON_IN_GAME]->rect.x = WINDOW_WIDTH-25-170;
    Buttons[RESTART_BUTTON_IN_GAME]->rect.y = 200;
    Buttons[RESTART_BUTTON_IN_GAME]->rect.w = 170;
    Buttons[RESTART_BUTTON_IN_GAME]->rect.h = 100;

    Buttons[NEW_GAME_BUTTON_IN_GAME]->rect.x = WINDOW_WIDTH-25-170;
    Buttons[NEW_GAME_BUTTON_IN_GAME]->rect.y = 350;
    Buttons[NEW_GAME_BUTTON_IN_GAME]->rect.w = 170;
    Buttons[NEW_GAME_BUTTON_IN_GAME]->rect.h = 100;

    Buttons[QUIT_BUTTON_IN_GAME]->rect.x = WINDOW_WIDTH-25-170;
    Buttons[QUIT_BUTTON_IN_GAME]->rect.y = 500;
    Buttons[QUIT_BUTTON_IN_GAME]->rect.w = 170;
    Buttons[QUIT_BUTTON_IN_GAME]->rect.h = 100;

    Buttons[UNDO_BUTTON]->rect.x = WINDOW_WIDTH-25-170;
    Buttons[UNDO_BUTTON]->rect.y = 750;
    Buttons[UNDO_BUTTON]->rect.w = 170;
    Buttons[UNDO_BUTTON]->rect.h = 100;

    Buttons[PAWN_PROMOTION_BUTTON]->rect.x = 850+355/2-170/2;
    Buttons[PAWN_PROMOTION_BUTTON]->rect.y = 50;
    Buttons[PAWN_PROMOTION_BUTTON]->rect.w = 170;
    Buttons[PAWN_PROMOTION_BUTTON]->rect.h = 100;

    Buttons[QUEEN_BUTTON]->rect.x = 850+355/2-170/2;
    Buttons[QUEEN_BUTTON]->rect.y = 250;
    Buttons[QUEEN_BUTTON]->rect.w = 170;
    Buttons[QUEEN_BUTTON]->rect.h = 100;

    Buttons[ROOK_BUTTON]->rect.x = 850+355/2-170/2;
    Buttons[ROOK_BUTTON]->rect.y = 400;
    Buttons[ROOK_BUTTON]->rect.w = 170;
    Buttons[ROOK_BUTTON]->rect.h = 100;

    Buttons[BISHOP_BUTTON]->rect.x = 850+355/2-170/2;
    Buttons[BISHOP_BUTTON]->rect.y = 550;
    Buttons[BISHOP_BUTTON]->rect.w = 170;
    Buttons[BISHOP_BUTTON]->rect.h = 100;

    Buttons[KNIGHT_BUTTON]->rect.x = 850+355/2-170/2;
    Buttons[KNIGHT_BUTTON]->rect.y = 700;
    Buttons[KNIGHT_BUTTON]->rect.w = 170;
    Buttons[KNIGHT_BUTTON]->rect.h = 100;


    // buttons for the victory menu
    Buttons[NEW_GAME_BUTTON_VICTORY_MENU]->rect.x = 50;
    Buttons[NEW_GAME_BUTTON_VICTORY_MENU]->rect.y = 50;
    Buttons[NEW_GAME_BUTTON_VICTORY_MENU]->rect.w = 275;
    Buttons[NEW_GAME_BUTTON_VICTORY_MENU]->rect.h = 175;

    Buttons[RESTART_BUTTON_VICTORY_MENU]->rect.x = WINDOW_WIDTH-50-275;
    Buttons[RESTART_BUTTON_VICTORY_MENU]->rect.y = 50;
    Buttons[RESTART_BUTTON_VICTORY_MENU]->rect.w = 275;
    Buttons[RESTART_BUTTON_VICTORY_MENU]->rect.h = 175;

    Buttons[QUIT_BUTTON_VICTORY_MENU]->rect.x = WINDOW_WIDTH/2 - 150;
    Buttons[QUIT_BUTTON_VICTORY_MENU]->rect.y = 650;
    Buttons[QUIT_BUTTON_VICTORY_MENU]->rect.w = 300;
    Buttons[QUIT_BUTTON_VICTORY_MENU]->rect.h = 200;


    // return the array of buttons
    return Buttons;
}


void Reset_Buttons_State(Button** Buttons){
    // for each button, we set the state to UNACTIVE
    for (int i = 0; i < NUMBER_OF_BUTTONS; i++){
        Buttons[i]->state = UNACTIVE;
    }
}


void Destroy_Buttons(int number_of_buttons, Button** Buttons){
    // for each button, we free it
    for (int i = 0; i < number_of_buttons; i++){
        if (Buttons[i] != NULL){
            free(Buttons[i]);
        }
    }

    // free the array of buttons
    if (Buttons != NULL){
        free(Buttons);
    }
}


void Show_Load_Menu(SDL_Renderer* renderer, int menu_type, Button** Buttons, int is_clicked_1, int is_clicked_2, SDL_Rect draw_red_boundary_move){
   
}   


void Show_Chess_Board(SDL_Renderer* renderer, Piece*** board, int is_clicked_1, int is_clicked_2, SDL_Rect draw_red_boundary_move){


    SDL_Rect rect;
    rect.w = SQUARE_SIZE;
    rect.h = SQUARE_SIZE;

    // making the empty chessboard
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            rect.x = j * SQUARE_SIZE+WINDOW_LEFT_MARGIN;
            rect.y = i * SQUARE_SIZE+WINDOW_TOP_MARGIN;
            if ((i + j) % 2 == 0) {
                SDL_SetRenderDrawColor(renderer, 222, 184, 135, 255); // beige
            }
            else {
                SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255); // marron
            }
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    // making the pieces
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j]->is_alive) {

                char* name_piece;

                switch (board[i][j]->type) {
                    case PAWN:
                        if (board[i][j]->color == WHITE) {
                            name_piece = "white_pawn.bmp";
                        }
                        else {
                            name_piece = "black_pawn.bmp";
                        }
                        break;
                    case KNIGHT:
                        if (board[i][j]->color == WHITE) {
                            name_piece = "white_knight.bmp";
                        }
                        else {
                            name_piece = "black_knight.bmp";
                        }
                        break;
                    case BISHOP:
                        if (board[i][j]->color == WHITE) {
                            name_piece = "white_bishop.bmp";
                        }
                        else {
                            name_piece = "black_bishop.bmp";
                        }
                        break;
                    case ROOK:
                        if (board[i][j]->color == WHITE) {
                            name_piece = "white_rook.bmp";
                        }
                        else {
                            name_piece = "black_rook.bmp";
                        }
                        break;
                    case QUEEN:
                        if (board[i][j]->color == WHITE) {
                            name_piece = "white_queen.bmp";
                        }
                        else {
                            name_piece = "black_queen.bmp";
                        }
                        break;
                    case KING:
                        if (board[i][j]->color == WHITE) {
                            name_piece = "white_king.bmp";
                        }
                        else {
                            name_piece = "black_king.bmp";
                        }
                        break;
                }

                /* Define destination rectangle */
                SDL_Rect destRect = {board[i][j]->col * SQUARE_SIZE+WINDOW_LEFT_MARGIN+SQUARE_SIZE/8, board[i][j]->row * SQUARE_SIZE+WINDOW_TOP_MARGIN+SQUARE_SIZE/8, SQUARE_SIZE*3/4, SQUARE_SIZE*3/4}; // Adjust the coordinates and size as needed

                /* Add image to renderer */
                add_image_to_render(name_piece, renderer, destRect);
            }      
        }
    }

    // if a piece is clicked, we draw a red boundary around it
    if (is_clicked_1 == 1 && is_clicked_2 == 0){
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red
        SDL_RenderDrawRect(renderer, &draw_red_boundary_move); 
        // we draw the line around the piece 
        // we wanted to make it thicker so here is a way to do it, don't know if it's the best way

        // Draw top line
        for (int i = 0; i < 5; ++i) {
            SDL_RenderDrawLine(renderer, draw_red_boundary_move.x, draw_red_boundary_move.y + i, draw_red_boundary_move.x + draw_red_boundary_move.w, draw_red_boundary_move.y + i);
        }

        // Draw right line
        for (int i = 0; i < 5; ++i) {
            SDL_RenderDrawLine(renderer, draw_red_boundary_move.x + draw_red_boundary_move.w - i, draw_red_boundary_move.y, draw_red_boundary_move.x + draw_red_boundary_move.w - i, draw_red_boundary_move.y + draw_red_boundary_move.h);
        }

        // Draw bottom line
        for (int i = 0; i < 5; ++i) {
            SDL_RenderDrawLine(renderer, draw_red_boundary_move.x, draw_red_boundary_move.y + draw_red_boundary_move.h - i, draw_red_boundary_move.x + draw_red_boundary_move.w, draw_red_boundary_move.y + draw_red_boundary_move.h - i);
        }

        // Draw left line
        for (int i = 0; i < 5; ++i) {
            SDL_RenderDrawLine(renderer, draw_red_boundary_move.x + i, draw_red_boundary_move.y, draw_red_boundary_move.x + i, draw_red_boundary_move.y + draw_red_boundary_move.h);
        }
    }

}


void Show_Captured_Pieces(SDL_Renderer* renderer, Captured_Piece_and_Score* captured_pieces){
    
    SDL_Rect rect;
    rect.w = 2*SQUARE_SIZE/10;
    rect.h = 2*SQUARE_SIZE/10;

    // showing the white piece captured piece above the chessboard
    for (int i=0; i<captured_pieces->number_of_white_pieces_captured; i++){
        rect.x = WINDOW_LEFT_MARGIN + i*(2*SQUARE_SIZE/10-10);
        rect.y = 3*SQUARE_SIZE/10/2;
        switch (captured_pieces->white_pieces_captured[i]->type){
            case PAWN:
                add_image_to_render("white_pawn.bmp", renderer, rect);
                break;
            case KNIGHT:
                add_image_to_render("white_knight.bmp", renderer, rect);
                break;
            case BISHOP:
                add_image_to_render("white_bishop.bmp", renderer, rect);
                break;
            case ROOK:
                add_image_to_render("white_rook.bmp", renderer, rect);
                break;
            case QUEEN:
                add_image_to_render("white_queen.bmp", renderer, rect);
                break;
        }
    }

    // showing the black piece captured under the chessboard
    for (int i=0; i<captured_pieces->number_of_black_pieces_captured; i++){
        rect.x = WINDOW_LEFT_MARGIN + i*(2*SQUARE_SIZE/10-10);
        rect.y = WINDOW_HEIGHT-WINDOW_TOP_MARGIN + 3*SQUARE_SIZE/10/2;
        switch (captured_pieces->black_pieces_captured[i]->type){
            case PAWN:
                add_image_to_render("black_pawn.bmp", renderer, rect);
                break;
            case KNIGHT:
                add_image_to_render("black_knight.bmp", renderer, rect);
                break;
            case BISHOP:
                add_image_to_render("black_bishop.bmp", renderer, rect);
                break;
            case ROOK:
                add_image_to_render("black_rook.bmp", renderer, rect);
                break;
            case QUEEN:
                add_image_to_render("black_queen.bmp", renderer, rect);
                break;
        }
    }

    // the show of the score is still to be done 
}


void Show_Log(SDL_Renderer* renderer, Move_Log_array* log){

}


void Show_Updated_Timer(SDL_Renderer* renderer, int time_player_white, int time_player_black, int player_playing){

    // the area where we will show the timer will be on the right side of the board, the active timer will have a white background, the other will have a light grey background
    // both timer will be print in black in the same area
    SDL_Rect dest_rect_playing;
    dest_rect_playing.x = WINDOW_LEFT_MARGIN + 6*SQUARE_SIZE;
    dest_rect_playing.w = 200;
    dest_rect_playing.h = 50;
    SDL_Rect dest_rect_not_playing;
    dest_rect_not_playing.x = WINDOW_LEFT_MARGIN + 6*SQUARE_SIZE;
    dest_rect_not_playing.w = 200;
    dest_rect_not_playing.h = 50;

    // for the printing of the timer, we will use the font array
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

    // Define the colon character
    const int colon[FONT_HEIGHT_COLON] = {
        0x00, // .....
        0x00, // .....
        0x00, // .....
        0x18, // ...xx
        0x18, // ...xx
        0x00, // .....
        0x18, // ...xx
        0x18  // ...xx
    };

    // if the player that is playing is the player 1, so the white player
    if (player_playing == Player1){

        // we set the color of the renderer to white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        // we draw the rectangle for the timer of the player 1 in white 
        dest_rect_playing.y = WINDOW_HEIGHT - 50;
        SDL_RenderFillRect(renderer, &dest_rect_playing);

        // we set the color of the renderer to dark grey
        SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
        // we draw the rectangle for the timer of the player 2 in dark grey
        dest_rect_not_playing.y = 0;
        SDL_RenderFillRect(renderer, &dest_rect_not_playing);
        

        int number;
        int x;
        int y;
        int x_colon;
        int y_colon;
        int number_digits_done;

        // we print the timer of the player 1 in black in the rectangle that is white, because he is playing
        // we first print the seconds with this function 
        number = time_player_white % 60;
        number_digits_done = 0;
        x = dest_rect_playing.x + dest_rect_playing.w - FONT_WIDTH/2;
        y = dest_rect_playing.y+ 15;
        // we still need to print the number if it's equal to zero 
        if (number == 0){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
            for (int i = 0; i < FONT_HEIGHT; i++) {
                for (int j = 0; j < FONT_WIDTH; j++) {
                    if (font[0][j] & (1 << (FONT_WIDTH - i - 1))) {
                        SDL_RenderDrawPoint(renderer, x + j, y + i);
                    }
                }
            }
            x -= FONT_WIDTH; // Move right for the next digit
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
            for (int i = 0; i < FONT_HEIGHT; i++) {
                for (int j = 0; j < FONT_WIDTH; j++) {
                    if (font[0][j] & (1 << (FONT_WIDTH - i - 1))) {
                        SDL_RenderDrawPoint(renderer, x + j, y + i);
                    }
                }
            }
            x -= FONT_WIDTH; // Move right for the next digit
        }
        while (number > 0) {
            int digit = number % 10;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
            for (int i = 0; i < FONT_HEIGHT; i++) {
                for (int j = 0; j < FONT_WIDTH; j++) {
                    if (font[digit][j] & (1 << (FONT_WIDTH - i - 1))) {
                        SDL_RenderDrawPoint(renderer, x + j, y + i);
                    }
                }
            }
            x -= FONT_WIDTH; // Move right for the next digit
            if (number/10 == 0 && number_digits_done < 1){
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
                for (int i = 0; i < FONT_HEIGHT; i++) {
                    for (int j = 0; j < FONT_WIDTH; j++) {
                        if (font[0][j] & (1 << (FONT_WIDTH - i - 1))) {
                            SDL_RenderDrawPoint(renderer, x + j, y + i);
                        }
                    }
                }
                x -= FONT_WIDTH; // Move right for the next digit
            }
            number_digits_done = number_digits_done +1;
            number /= 10;
        }

        // printing the ":" symbols bewteen the two numbers
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
        x_colon=x+FONT_HEIGHT/2;
        y_colon=y+10;
        for (int i = 0; i < FONT_HEIGHT_COLON; i++) {
            for (int j = 0; j < FONT_WIDTH_COLON; j++) {
                if (colon[i] & (1 << (FONT_WIDTH_COLON - j - 1))) {
                    SDL_RenderDrawPoint(renderer, x_colon + j, y_colon + i);
                }
            }
        }

        // we then print the minutes with this function, it's pratical since the shifting has already be done
        number = time_player_white / 60;
        number_digits_done = 0;
        // we still need to print the number if it's equal to zero 
        if (number == 0){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
            for (int i = 0; i < FONT_HEIGHT; i++) {
                for (int j = 0; j < FONT_WIDTH; j++) {
                    if (font[0][j] & (1 << (FONT_WIDTH - i - 1))) {
                        SDL_RenderDrawPoint(renderer, x + j, y + i);
                    }
                }
            }
            x -= FONT_WIDTH; // Move right for the next digit
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
            for (int i = 0; i < FONT_HEIGHT; i++) {
                for (int j = 0; j < FONT_WIDTH; j++) {
                    if (font[0][j] & (1 << (FONT_WIDTH - i - 1))) {
                        SDL_RenderDrawPoint(renderer, x + j, y + i);
                    }
                }
            }
            x -= FONT_WIDTH; // Move right for the next digit
        }
        while (number > 0) {
            int digit = number % 10;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
            for (int i = 0; i < FONT_HEIGHT; i++) {
                for (int j = 0; j < FONT_WIDTH; j++) {
                    if (font[digit][j] & (1 << (FONT_WIDTH - i - 1))) {
                        SDL_RenderDrawPoint(renderer, x + j, y + i);
                    }
                }
            }
            x -= FONT_WIDTH; // Move right for the next digit
            if (number/10 == 0 && number_digits_done < 1){
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
                for (int i = 0; i < FONT_HEIGHT; i++) {
                    for (int j = 0; j < FONT_WIDTH; j++) {
                        if (font[0][j] & (1 << (FONT_WIDTH - i - 1))) {
                            SDL_RenderDrawPoint(renderer, x + j, y + i);
                        }
                    }
                }
                x -= FONT_WIDTH; // Move right for the next digit
            }
            number_digits_done = number_digits_done +1;
            number /= 10;
        }


        // we print the timer of the player 2 in black in the rectangle that is grey, because he is not playing
        // we first print the seconds with this function 
        number = time_player_black % 60;
        number_digits_done = 0;
        x = dest_rect_not_playing.x + dest_rect_not_playing.w - FONT_WIDTH/2;
        y = dest_rect_not_playing.y+ 15;
        // we still need to print the number if it's equal to zero 
        if (number == 0){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
            for (int i = 0; i < FONT_HEIGHT; i++) {
                for (int j = 0; j < FONT_WIDTH; j++) {
                    if (font[0][j] & (1 << (FONT_WIDTH - i - 1))) {
                        SDL_RenderDrawPoint(renderer, x + j, y + i);
                    }
                }
            }
            x -= FONT_WIDTH; // Move right for the next digit
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
            for (int i = 0; i < FONT_HEIGHT; i++) {
                for (int j = 0; j < FONT_WIDTH; j++) {
                    if (font[0][j] & (1 << (FONT_WIDTH - i - 1))) {
                        SDL_RenderDrawPoint(renderer, x + j, y + i);
                    }
                }
            }
            x -= FONT_WIDTH; // Move right for the next digit
        }
        while (number > 0) {
            int digit = number % 10;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
            for (int i = 0; i < FONT_HEIGHT; i++) {
                for (int j = 0; j < FONT_WIDTH; j++) {
                    if (font[digit][j] & (1 << (FONT_WIDTH - i - 1))) {
                        SDL_RenderDrawPoint(renderer, x + j, y + i);
                    }
                }
            }
            x -= FONT_WIDTH; // Move right for the next digit
            if (number/10 == 0 && number_digits_done < 1){
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
                for (int i = 0; i < FONT_HEIGHT; i++) {
                    for (int j = 0; j < FONT_WIDTH; j++) {
                        if (font[0][j] & (1 << (FONT_WIDTH - i - 1))) {
                            SDL_RenderDrawPoint(renderer, x + j, y + i);
                        }
                    }
                }
                x -= FONT_WIDTH; // Move right for the next digit
            }
            number_digits_done = number_digits_done +1;
            number /= 10;
        }

        // printing the ":" symbols bewteen the two numbers
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
        x_colon=x+FONT_HEIGHT/2;
        y_colon=y+10;
        for (int i = 0; i < FONT_HEIGHT_COLON; i++) {
            for (int j = 0; j < FONT_WIDTH_COLON; j++) {
                if (colon[i] & (1 << (FONT_WIDTH_COLON - j - 1))) {
                    SDL_RenderDrawPoint(renderer, x_colon + j, y_colon + i);
                }
            }
        }

        // we then print the minutes with this function, it's pratical since the shifting has already be done
        number = time_player_black / 60;
        number_digits_done = 0;
        // we still need to print the number if it's equal to zero 
        if (number == 0){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
            for (int i = 0; i < FONT_HEIGHT; i++) {
                for (int j = 0; j < FONT_WIDTH; j++) {
                    if (font[0][j] & (1 << (FONT_WIDTH - i - 1))) {
                        SDL_RenderDrawPoint(renderer, x + j, y + i);
                    }
                }
            }
            x -= FONT_WIDTH; // Move right for the next digit
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
            for (int i = 0; i < FONT_HEIGHT; i++) {
                for (int j = 0; j < FONT_WIDTH; j++) {
                    if (font[0][j] & (1 << (FONT_WIDTH - i - 1))) {
                        SDL_RenderDrawPoint(renderer, x + j, y + i);
                    }
                }
            }
            x -= FONT_WIDTH; // Move right for the next digit
        }
        while (number > 0) {
            int digit = number % 10;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
            for (int i = 0; i < FONT_HEIGHT; i++) {
                for (int j = 0; j < FONT_WIDTH; j++) {
                    if (font[digit][j] & (1 << (FONT_WIDTH - i - 1))) {
                        SDL_RenderDrawPoint(renderer, x + j, y + i);
                    }
                }
            }
            x -= FONT_WIDTH; // Move right for the next digit
            if (number/10 == 0 && number_digits_done < 1){
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
                for (int i = 0; i < FONT_HEIGHT; i++) {
                    for (int j = 0; j < FONT_WIDTH; j++) {
                        if (font[0][j] & (1 << (FONT_WIDTH - i - 1))) {
                            SDL_RenderDrawPoint(renderer, x + j, y + i);
                        }
                    }
                }
                x -= FONT_WIDTH; // Move right for the next digit
            }
            number_digits_done = number_digits_done +1;
            number /= 10;
        }


    }
    // if the player that is playing is the player 2, so the black player
    else if (player_playing == Player2){

        // we set the color of the renderer to white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        // we draw the rectangle for the timer of the player 2 in white 
        dest_rect_playing.y = 0;
        SDL_RenderFillRect(renderer, &dest_rect_playing);

        // we set the color of the renderer to dark grey
        SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
        // we draw the rectangle for the timer of the player 1 in dark grey
        dest_rect_not_playing.y = WINDOW_HEIGHT - 50;
        SDL_RenderFillRect(renderer, &dest_rect_not_playing);

        int number;
        int x;
        int y;
        int x_colon;
        int y_colon;
        int number_digits_done;

        // we print the timer of the player 1 in black in the rectangle that is grey, because he is not playing
        // we first print the seconds with this function 
        number = time_player_white % 60;
        number_digits_done = 0;
        x = dest_rect_not_playing.x + dest_rect_not_playing.w - FONT_WIDTH/2;
        y = dest_rect_not_playing.y+ 15;
        // we still need to print the number if it's equal to zero 
        if (number == 0){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
            for (int i = 0; i < FONT_HEIGHT; i++) {
                for (int j = 0; j < FONT_WIDTH; j++) {
                    if (font[0][j] & (1 << (FONT_WIDTH - i - 1))) {
                        SDL_RenderDrawPoint(renderer, x + j, y + i);
                    }
                }
            }
            x -= FONT_WIDTH; // Move right for the next digit
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
            for (int i = 0; i < FONT_HEIGHT; i++) {
                for (int j = 0; j < FONT_WIDTH; j++) {
                    if (font[0][j] & (1 << (FONT_WIDTH - i - 1))) {
                        SDL_RenderDrawPoint(renderer, x + j, y + i);
                    }
                }
            }
            x -= FONT_WIDTH; // Move right for the next digit
        }
        while (number > 0) {
            int digit = number % 10;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
            for (int i = 0; i < FONT_HEIGHT; i++) {
                for (int j = 0; j < FONT_WIDTH; j++) {
                    if (font[digit][j] & (1 << (FONT_WIDTH - i - 1))) {
                        SDL_RenderDrawPoint(renderer, x + j, y + i);
                    }
                }
            }
            x -= FONT_WIDTH; // Move right for the next digit
            if (number/10 == 0 && number_digits_done < 1){
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
                for (int i = 0; i < FONT_HEIGHT; i++) {
                    for (int j = 0; j < FONT_WIDTH; j++) {
                        if (font[0][j] & (1 << (FONT_WIDTH - i - 1))) {
                            SDL_RenderDrawPoint(renderer, x + j, y + i);
                        }
                    }
                }
                x -= FONT_WIDTH; // Move right for the next digit
            }
            number_digits_done = number_digits_done +1;
            number /= 10;
        }

        // printing the ":" symbols bewteen the two numbers
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
        x_colon=x+FONT_HEIGHT/2;
        y_colon=y+10;
        for (int i = 0; i < FONT_HEIGHT_COLON; i++) {
            for (int j = 0; j < FONT_WIDTH_COLON; j++) {
                if (colon[i] & (1 << (FONT_WIDTH_COLON - j - 1))) {
                    SDL_RenderDrawPoint(renderer, x_colon + j, y_colon + i);
                }
            }
        }

        // we then print the minutes with this function, it's pratical since the shifting has already be done
        number = time_player_white / 60;
        number_digits_done = 0;
        // we still need to print the number if it's equal to zero 
        if (number == 0){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
            for (int i = 0; i < FONT_HEIGHT; i++) {
                for (int j = 0; j < FONT_WIDTH; j++) {
                    if (font[0][j] & (1 << (FONT_WIDTH - i - 1))) {
                        SDL_RenderDrawPoint(renderer, x + j, y + i);
                    }
                }
            }
            x -= FONT_WIDTH; // Move right for the next digit
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
            for (int i = 0; i < FONT_HEIGHT; i++) {
                for (int j = 0; j < FONT_WIDTH; j++) {
                    if (font[0][j] & (1 << (FONT_WIDTH - i - 1))) {
                        SDL_RenderDrawPoint(renderer, x + j, y + i);
                    }
                }
            }
            x -= FONT_WIDTH; // Move right for the next digit
        }
        while (number > 0) {
            int digit = number % 10;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
            for (int i = 0; i < FONT_HEIGHT; i++) {
                for (int j = 0; j < FONT_WIDTH; j++) {
                    if (font[digit][j] & (1 << (FONT_WIDTH - i - 1))) {
                        SDL_RenderDrawPoint(renderer, x + j, y + i);
                    }
                }
            }
            x -= FONT_WIDTH; // Move right for the next digit
            if (number/10 == 0 && number_digits_done < 1){
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
                for (int i = 0; i < FONT_HEIGHT; i++) {
                    for (int j = 0; j < FONT_WIDTH; j++) {
                        if (font[0][j] & (1 << (FONT_WIDTH - i - 1))) {
                            SDL_RenderDrawPoint(renderer, x + j, y + i);
                        }
                    }
                }
                x -= FONT_WIDTH; // Move right for the next digit
            }
            number_digits_done = number_digits_done +1;
            number /= 10;
        }


        // we print the timer of the player 2 in black in the rectangle that is white, because he is playing
        // we first print the seconds with this function 
        number = time_player_black % 60;
        number_digits_done = 0;
        x = dest_rect_playing.x + dest_rect_playing.w - FONT_WIDTH/2;
        y = dest_rect_playing.y+ 15;
        // we still need to print the number if it's equal to zero 
        if (number == 0){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
            for (int i = 0; i < FONT_HEIGHT; i++) {
                for (int j = 0; j < FONT_WIDTH; j++) {
                    if (font[0][j] & (1 << (FONT_WIDTH - i - 1))) {
                        SDL_RenderDrawPoint(renderer, x + j, y + i);
                    }
                }
            }
            x -= FONT_WIDTH; // Move right for the next digit
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
            for (int i = 0; i < FONT_HEIGHT; i++) {
                for (int j = 0; j < FONT_WIDTH; j++) {
                    if (font[0][j] & (1 << (FONT_WIDTH - i - 1))) {
                        SDL_RenderDrawPoint(renderer, x + j, y + i);
                    }
                }
            }
            x -= FONT_WIDTH; // Move right for the next digit
        }
        while (number > 0) {
            int digit = number % 10;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
            for (int i = 0; i < FONT_HEIGHT; i++) {
                for (int j = 0; j < FONT_WIDTH; j++) {
                    if (font[digit][j] & (1 << (FONT_WIDTH - i - 1))) {
                        SDL_RenderDrawPoint(renderer, x + j, y + i);
                    }
                }
            }
            x -= FONT_WIDTH; // Move right for the next digit
            if (number/10 == 0 && number_digits_done < 1){
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
                for (int i = 0; i < FONT_HEIGHT; i++) {
                    for (int j = 0; j < FONT_WIDTH; j++) {
                        if (font[0][j] & (1 << (FONT_WIDTH - i - 1))) {
                            SDL_RenderDrawPoint(renderer, x + j, y + i);
                        }
                    }
                }
                x -= FONT_WIDTH; // Move right for the next digit
            }
            number_digits_done = number_digits_done +1;
            number /= 10;
        }

        // printing the ":" symbols bewteen the two numbers
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
        x_colon=x+FONT_HEIGHT/2;
        y_colon=y+10;
        for (int i = 0; i < FONT_HEIGHT_COLON; i++) {
            for (int j = 0; j < FONT_WIDTH_COLON; j++) {
                if (colon[i] & (1 << (FONT_WIDTH_COLON - j - 1))) {
                    SDL_RenderDrawPoint(renderer, x_colon + j, y_colon + i);
                }
            }
        }

        // we then print the minutes with this function, it's pratical since the shifting has already be done
        number = time_player_black / 60;
        number_digits_done = 0;
        // we still need to print the number if it's equal to zero 
        if (number == 0){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
            for (int i = 0; i < FONT_HEIGHT; i++) {
                for (int j = 0; j < FONT_WIDTH; j++) {
                    if (font[0][j] & (1 << (FONT_WIDTH - i - 1))) {
                        SDL_RenderDrawPoint(renderer, x + j, y + i);
                    }
                }
            }
            x -= FONT_WIDTH; // Move right for the next digit
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
            for (int i = 0; i < FONT_HEIGHT; i++) {
                for (int j = 0; j < FONT_WIDTH; j++) {
                    if (font[0][j] & (1 << (FONT_WIDTH - i - 1))) {
                        SDL_RenderDrawPoint(renderer, x + j, y + i);
                    }
                }
            }
            x -= FONT_WIDTH; // Move right for the next digit
        }
        while (number > 0) {
            int digit = number % 10;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
            for (int i = 0; i < FONT_HEIGHT; i++) {
                for (int j = 0; j < FONT_WIDTH; j++) {
                    if (font[digit][j] & (1 << (FONT_WIDTH - i - 1))) {
                        SDL_RenderDrawPoint(renderer, x + j, y + i);
                    }
                }
            }
            x -= FONT_WIDTH; // Move right for the next digit
            if (number/10 == 0 && number_digits_done < 1){
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
                for (int i = 0; i < FONT_HEIGHT; i++) {
                    for (int j = 0; j < FONT_WIDTH; j++) {
                        if (font[0][j] & (1 << (FONT_WIDTH - i - 1))) {
                            SDL_RenderDrawPoint(renderer, x + j, y + i);
                        }
                    }
                }
                x -= FONT_WIDTH; // Move right for the next digit
            }
            number_digits_done = number_digits_done +1;
            number /= 10;
        }

    }

}


void Show_Menu_Button_in_Game(SDL_Renderer* renderer, Button** Buttons, bool is_pawn_promotion_happening, int color_promoted_pawn){
    
    // display the start buttons
    if (Buttons[START_BUTTON]->state == UNACTIVE){
        add_image_to_render("Unactive_Start_Button.bmp", renderer, Buttons[START_BUTTON]->rect);
    }
    else if (Buttons[START_BUTTON]->state == ACTIVE){
        add_image_to_render("Active_Start_Button.bmp", renderer, Buttons[START_BUTTON]->rect);
    }

    // display others buttons
    add_image_to_render("Restart_Button.bmp", renderer, Buttons[RESTART_BUTTON_IN_GAME]->rect);
    add_image_to_render("New_Game_Button.bmp", renderer, Buttons[NEW_GAME_BUTTON_IN_GAME]->rect);
    add_image_to_render("Quit_Button.bmp", renderer, Buttons[QUIT_BUTTON_IN_GAME]->rect);

    // display the undo button 
    if (Buttons[UNDO_BUTTON]->state == UNACTIVE){
        add_image_to_render("Unactive_Undo_Button.bmp", renderer, Buttons[UNDO_BUTTON]->rect);
    }
    else if (Buttons[UNDO_BUTTON]->state == ACTIVE){
        add_image_to_render("Active_Undo_Button.bmp", renderer, Buttons[UNDO_BUTTON]->rect);
    }

    // we display the pawn promotion buttons : always but active or unactive 
    if (is_pawn_promotion_happening == false){
        add_image_to_render("Unactive_Pawn_Promotion_Button.bmp", renderer, Buttons[PAWN_PROMOTION_BUTTON]->rect);
    }
    else if (is_pawn_promotion_happening == true){
        add_image_to_render("Active_Pawn_Promotion_Button.bmp", renderer, Buttons[PAWN_PROMOTION_BUTTON]->rect);
    }

    // we then print at the place of the log on the render, the differents buttons concerning the pawn promotion
    if (is_pawn_promotion_happening == true){
        // if the color of the pawn that is promoted is white
        if (color_promoted_pawn == WHITE){
            add_image_to_render("white_queen.bmp", renderer, Buttons[QUEEN_BUTTON]->rect);
            add_image_to_render("white_rook.bmp", renderer, Buttons[ROOK_BUTTON]->rect);
            add_image_to_render("white_bishop.bmp", renderer, Buttons[BISHOP_BUTTON]->rect);
            add_image_to_render("white_knight.bmp", renderer, Buttons[KNIGHT_BUTTON]->rect);
        }
        // if the color of the pawn that is promoted is black
        else if (color_promoted_pawn == BLACK){
            add_image_to_render("black_queen.bmp", renderer, Buttons[QUEEN_BUTTON]->rect);
            add_image_to_render("black_rook.bmp", renderer, Buttons[ROOK_BUTTON]->rect);
            add_image_to_render("black_bishop.bmp", renderer, Buttons[BISHOP_BUTTON]->rect);
            add_image_to_render("black_knight.bmp", renderer, Buttons[KNIGHT_BUTTON]->rect);
        }
      
    }

}


void Show_Victory_Menu(SDL_Renderer* renderer, Button** Buttons, int looser_player, Players* players){
  
}