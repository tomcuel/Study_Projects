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



    // buttons for the difficulty choice menu



    // buttons for the time choice menu



    // buttons for the chessboard



    // buttons for the victory menu
    Buttons[NEW_GAME_BUTTON]->rect.x = 50;
    Buttons[NEW_GAME_BUTTON]->rect.y = 50;
    Buttons[NEW_GAME_BUTTON]->rect.w = 275;
    Buttons[NEW_GAME_BUTTON]->rect.h = 175;

    Buttons[RESTART_BUTTON]->rect.x = WINDOW_WIDTH-50-275;
    Buttons[RESTART_BUTTON]->rect.y = 50;
    Buttons[RESTART_BUTTON]->rect.w = 275;
    Buttons[RESTART_BUTTON]->rect.h = 175;

    Buttons[QUIT_BUTTON]->rect.x = WINDOW_WIDTH/2 - 150;
    Buttons[QUIT_BUTTON]->rect.y = 650;
    Buttons[QUIT_BUTTON]->rect.w = 300;
    Buttons[QUIT_BUTTON]->rect.h = 200;


    // return the array of buttons
    return Buttons;
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


void Show_Load_Menu(SDL_Renderer* renderer, int menu_type, Button** Buttons){

    /*
    will need to be made seriously
    here for the test, I'm just showing an image of one button for this type of menu
    */

   
    SDL_Rect rect;
    rect.w = SQUARE_SIZE;
    rect.h = SQUARE_SIZE;
    rect.x = 0;
    rect.y = 0;

    if (menu_type==GAMEPLAY_CHOICE){
        // brown color rectangle
        SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255);
        SDL_RenderFillRect(renderer, &rect);
    }

    else if (menu_type==DIFFICULTY_CHOICE){
        // grey color rectangle
        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
        SDL_RenderFillRect(renderer, &rect);
    }

    else if (menu_type==TIME_CHOICE){
        // brown color rectangle
        SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255);
        SDL_RenderFillRect(renderer, &rect);
    }

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

}


void Show_Log(SDL_Renderer* renderer, Move_Log_array* log){

}


void Show_Updated_Timer(SDL_Renderer* renderer, Uint32* time){

}


void Show_Menu_Button_in_Game(SDL_Renderer* renderer, Button** Buttons){

}


void Ask_Name(SDL_Renderer* renderer, Players* players){

}


void Show_Victory_Menu(SDL_Renderer* renderer, Button** Buttons, int looser_player, Players* players){
  
    // if there is a looser, we show the victory or defeat image
    if (looser_player != -1){
        SDL_Rect Rect_final_screen = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

        // when we play against the IA, we can add the images of victory and defeat, otherwise, bewteen two human players, we need to do diffent things
        if (looser_player == Player1 && players->is_player1_an_IA == HUMAN && players->is_player2_an_IA == AI){
            add_image_to_render("defeat.bmp", renderer, Rect_final_screen);
        }
        if (looser_player == Player2 && players->is_player1_an_IA == HUMAN && players->is_player2_an_IA == AI){
            add_image_to_render("victory.bmp", renderer, Rect_final_screen);
        }

        // we need to print a message to say which player won when it's between two human players

        // if the player 1 lost
        if (looser_player == Player1 && players->is_player1_an_IA == HUMAN && players->is_player2_an_IA == HUMAN){
            add_image_to_render("victory.bmp", renderer, Rect_final_screen);

            SDL_Rect Rect_pos = {WINDOW_WIDTH/2-200, 150, 400,200};
            // we show that the player 2 (and its corresponding color) won
            if (players->player2_color == WHITE){
                add_image_to_render("WHITE_PLAYER.bmp", renderer, Rect_pos);
            }
            else if (players->player2_color == BLACK){
                add_image_to_render("BLACK_PLAYER.bmp", renderer, Rect_pos);
            }
        }

        // if the player 2 lost
        if (looser_player == Player2 && players->is_player1_an_IA == HUMAN && players->is_player2_an_IA == HUMAN){
            add_image_to_render("victory.bmp", renderer, Rect_final_screen);

            SDL_Rect Rect_pos = {WINDOW_WIDTH/2-200, 150, 400,200};
            // we show that the player 1 (and its corresponding color) won
            if (players->player1_color == WHITE){
                add_image_to_render("WHITE_PLAYER.bmp", renderer, Rect_pos);
            }
            else if (players->player1_color == BLACK){
                add_image_to_render("BLACK_PLAYER.bmp", renderer, Rect_pos);
            }        
        }
    }

    // showing the buttons
    if (Buttons[QUIT_BUTTON]->state == UNACTIVE){
        add_image_to_render("quit_button.bmp", renderer, Buttons[QUIT_BUTTON]->rect);
    }
    else{
        add_image_to_render("quit_button_active.bmp", renderer, Buttons[QUIT_BUTTON]->rect);
    }

    if (Buttons[RESTART_BUTTON]->state == UNACTIVE){
        add_image_to_render("restart_button.bmp", renderer, Buttons[RESTART_BUTTON]->rect);
    }
    else{
        add_image_to_render("restart_button_active.bmp", renderer, Buttons[RESTART_BUTTON]->rect);
    }

    if (Buttons[NEW_GAME_BUTTON]->state == UNACTIVE){
        add_image_to_render("new_game_button.bmp", renderer, Buttons[NEW_GAME_BUTTON]->rect);
    }
    else{
        add_image_to_render("new_game_button_active.bmp", renderer, Buttons[NEW_GAME_BUTTON]->rect);
    }
}