#include <stdio.h> // pour le printf
#include <stdlib.h> // pour le scanf
#include <math.h> // pour les fonctions mathématiques 
#include <string.h> // pour les chaînes de caractères, strlen par exemple
#include <stdbool.h> // pour les booléens 
#include <time.h> // pour les randint 
#include <limits.h> // pour les limites
#include <ctype.h> // pour isalpha 
#include <unistd.h> // pour getpid 


#include <SDL2/SDL.h>
#include "Constants.h"
#include "Audio.h"
#include "Image.h"
#include "Piece.h"



// Function to draw a chessboard
void drawChessboard(SDL_Renderer *renderer, Piece* pieces, int nb_pieces) {
    SDL_Rect rect;
    rect.w = SQUARE_SIZE;
    rect.h = SQUARE_SIZE;
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

    for (int i = 0; i < nb_pieces; i++) {
        if (pieces[i].is_alive) {

            char * name_piece;

            switch (pieces[i].type) {
                case PAWN:
                    if (pieces[i].color == WHITE) {
                        name_piece = "white_pawn.bmp";
                    }
                    else {
                        name_piece = "black_pawn.bmp";
                    }
                    break;
                case KNIGHT:
                    if (pieces[i].color == WHITE) {
                        name_piece = "white_knight.bmp";
                    }
                    else {
                        name_piece = "black_knight.bmp";
                    }
                    break;
                case BISHOP:
                    if (pieces[i].color == WHITE) {
                        name_piece = "white_bishop.bmp";
                    }
                    else {
                        name_piece = "black_bishop.bmp";
                    }
                    break;
                case ROOK:
                    if (pieces[i].color == WHITE) {
                        name_piece = "white_rook.bmp";
                    }
                    else {
                        name_piece = "black_rook.bmp";
                    }
                    break;
                case QUEEN:
                    if (pieces[i].color == WHITE) {
                        name_piece = "white_queen.bmp";
                    }
                    else {
                        name_piece = "black_queen.bmp";
                    }
                    break;
                case KING:
                    if (pieces[i].color == WHITE) {
                        name_piece = "white_king.bmp";
                    }
                    else {
                        name_piece = "black_king.bmp";
                    }
                    break;
            }

            
            /* Define destination rectangle */
            SDL_Rect destRect = {pieces[i].row * SQUARE_SIZE+WINDOW_LEFT_MARGIN+SQUARE_SIZE/8, pieces[i].col * SQUARE_SIZE+WINDOW_TOP_MARGIN+SQUARE_SIZE/8, SQUARE_SIZE*3/4, SQUARE_SIZE*3/4}; // Adjust the coordinates and size as needed

            /* Add image to renderer */
            add_image_to_render(name_piece, renderer, destRect);

        }
    }

}





int main (){

    SDL_Init(SDL_INIT_EVERYTHING);

    // Initialisation of the SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        goto Quit;
    }

    // Creation of the window
    SDL_Window* window = SDL_CreateWindow("Jeu SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (window == NULL) {
        fprintf(stderr, "Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        goto Quit;
    }

    // Creation of the renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "Erreur lors de la création du renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        goto Quit;
    }

    // Creation of the pieces
    Piece pieces[32];
    for (int i = 0; i < 8; i++) {
        pieces[i].row = i;
        pieces[i].col = 1;
        pieces[i].type = PAWN;
        pieces[i].color = WHITE;
        pieces[i].is_alive = true;
    }
    for (int i = 8; i < 16; i++) {
        pieces[i].row = i-8;
        pieces[i].col = 6;
        pieces[i].type = PAWN;
        pieces[i].color = BLACK;
        pieces[i].is_alive = true;
    }
    for (int i=0; i<1; i++){
        pieces[16].row = 0;
        pieces[16].col = 0;
        pieces[16].type = ROOK;
        pieces[16].color = WHITE;
        pieces[16].is_alive = true;

        pieces[17].row = 7;
        pieces[17].col = 0;
        pieces[17].type = ROOK;
        pieces[17].color = WHITE;
        pieces[17].is_alive = true;

        pieces[18].row = 1;
        pieces[18].col = 0;
        pieces[18].type = KNIGHT;
        pieces[18].color = WHITE;
        pieces[18].is_alive = true;

        pieces[19].row = 6;
        pieces[19].col = 0;
        pieces[19].type = KNIGHT;
        pieces[19].color = WHITE;
        pieces[19].is_alive = true;

        pieces[20].row = 2;
        pieces[20].col = 0;
        pieces[20].type = BISHOP;
        pieces[20].color = WHITE;
        pieces[20].is_alive = true;

        pieces[21].row = 5;
        pieces[21].col = 0;
        pieces[21].type = BISHOP;
        pieces[21].color = WHITE;
        pieces[21].is_alive = true;

        pieces[22].row = 3;
        pieces[22].col = 0;
        pieces[22].type = QUEEN;
        pieces[22].color = WHITE;
        pieces[22].is_alive = true;

        pieces[23].row = 4;
        pieces[23].col = 0;
        pieces[23].type = KING;
        pieces[23].color = WHITE;
        pieces[23].is_alive = true;

        pieces[24].row = 0;
        pieces[24].col = 7;
        pieces[24].type = ROOK;
        pieces[24].color = BLACK;
        pieces[24].is_alive = true;

        pieces[25].row = 7;
        pieces[25].col = 7;
        pieces[25].type = ROOK;
        pieces[25].color = BLACK;
        pieces[25].is_alive = true;

        pieces[26].row = 1;
        pieces[26].col = 7;
        pieces[26].type = KNIGHT;
        pieces[26].color = BLACK;
        pieces[26].is_alive = true;
        
        pieces[27].row = 6;
        pieces[27].col = 7;
        pieces[27].type = KNIGHT;
        pieces[27].color = BLACK;
        pieces[27].is_alive = true;

        pieces[28].row = 2;
        pieces[28].col = 7;
        pieces[28].type = BISHOP;
        pieces[28].color = BLACK;
        pieces[28].is_alive = true;

        pieces[29].row = 5;
        pieces[29].col = 7;
        pieces[29].type = BISHOP;
        pieces[29].color = BLACK;
        pieces[29].is_alive = true;

        pieces[30].row = 3;
        pieces[30].col = 7;
        pieces[30].type = QUEEN;
        pieces[30].color = BLACK;
        pieces[30].is_alive = true;

        pieces[31].row = 4;
        pieces[31].col = 7;
        pieces[31].type = KING;
        pieces[31].color = BLACK;
        pieces[31].is_alive = true;
    }

   

	play_sound("chess.wav");

    // Creating an event to check some implementations of the board
    SDL_Event event;
    int quit = 0;
    while (!quit) {
        // gestion of the events
        while (SDL_PollEvent(&event)) {
            // condition to quit the game
            if (event.type == SDL_QUIT) {
                quit = 1;
            } 
            // what happens when a key is pressed (the escape key to quit the game)
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        quit = 1;
                        break;
                }
            }
        }

        // reset the renderer, the screen of the graphic card
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // draw the chessboard
        const char* image_path = "480-360-sample.bmp";
        drawChessboard(renderer, pieces, 32);

        // show the renderer
        SDL_RenderPresent(renderer);

        // Wait for 16 ms to aim for 60 FPS
        SDL_Delay(16);
    }

   


    // free the memory and quit the program
Quit :
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}