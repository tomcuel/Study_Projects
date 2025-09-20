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
        // setting the state to UNACTIVE
        Buttons[i]->state = UNACTIVE;
    }

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

}   


void Show_Chess_Board(SDL_Renderer* renderer, Piece*** board, int is_clicked_1, int is_clicked_2, SDL_Rect draw_red_boundary_move){

    // reset the renderer, the screen of the graphic card
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

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

    // update the renderer by presenting the new screen
    SDL_RenderPresent(renderer);
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