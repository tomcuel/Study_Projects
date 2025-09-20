#include <stdio.h> // pour le printf
#include <stdlib.h> // pour le scanf
#include <math.h> // pour les fonctions mathématiques 
#include <string.h> // pour les chaînes de caractères, strlen par exemple
#include <stdbool.h> // pour les booléens 
#include <time.h> // pour les randint 
#include <limits.h> // pour les limites
#include <ctype.h> // pour isalpha 
#include <unistd.h> // pour getpid 


///////////////////////////////////////////////////////////////////////////////
// this code will be used to control the mouse input during the chess game
///////////////////////////////////////////////////////////////////////////////


#include <SDL2/SDL.h>


///////////////////////////////////////////////////////////////////////////////
// Global variables
///////////////////////////////////////////////////////////////////////////////
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
int is_running = false;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
// initialize the rectangle to be drawn, the one we will click on (src_rect) to move it to the other one (dest_rect)
SDL_Rect src_rect = {400, 200, 100, 100};
SDL_Rect dst_rect = {0, 0, 100, 100};

///////////////////////////////////////////////////////////////////////////////
// Function to initialize our SDL window
///////////////////////////////////////////////////////////////////////////////
int initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }
    window = SDL_CreateWindow(
        "A simple game loop using C & SDL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_FULLSCREEN
    );
    if (!window) {
        fprintf(stderr, "Error creating SDL Window.\n");
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Error creating SDL Renderer.\n");
        return false;
    }
    return true;
}


///////////////////////////////////////////////////////////////////////////////
// Function to destroy SDL window and renderer
///////////////////////////////////////////////////////////////////////////////
void destroy_window(void) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


///////////////////////////////////////////////////////////////////////////////
// Render function to draw game objects in the SDL window
// the render function 
///////////////////////////////////////////////////////////////////////////////
void render(int is_clicked_1, int is_clicked_2, SDL_Rect rectangle1, SDL_Rect rectangle2) {
    // make a black background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // clear the window
    SDL_RenderClear(renderer);
    // draw the rectangle 2 in white
    if (is_clicked_1 == 1 && is_clicked_2 ==1) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rectangle2);
    } 
    // draw the rectangle 1 in white 
    else if ( is_clicked_2 != 1) {
        // if the rectangle 1 is clicked, draw it in white and add the rectangle 1 in red 
        if (is_clicked_1 == 0) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &rectangle1);
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        }
        // if nothing has been clicked on yet, draw the rectangle 1 in white
        else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &rectangle1);

            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            // Drawing the red boundary around the rectangle 1 to show the selected rectangle

            // Draw top line
            for (int i = 0; i < 5; ++i) {
                SDL_RenderDrawLine(renderer, rectangle1.x, rectangle1.y + i, rectangle1.x + rectangle1.w, rectangle1.y + i);
            }

            // Draw right line
            for (int i = 0; i < 5; ++i) {
                SDL_RenderDrawLine(renderer, rectangle1.x + rectangle1.w - i, rectangle1.y, rectangle1.x + rectangle1.w - i, rectangle1.y + rectangle1.h);
            }

            // Draw bottom line
            for (int i = 0; i < 5; ++i) {
                SDL_RenderDrawLine(renderer, rectangle1.x, rectangle1.y + rectangle1.h - i, rectangle1.x + rectangle1.w, rectangle1.y + rectangle1.h - i);
            }

            // Draw left line
            for (int i = 0; i < 5; ++i) {
                SDL_RenderDrawLine(renderer, rectangle1.x + i, rectangle1.y, rectangle1.x + i, rectangle1.y + rectangle1.h);
            }

        }
    }

    SDL_RenderPresent(renderer);
}


// function to check if a point is in a rectangle
bool is_in_rectangle(int x, int y, SDL_Rect rect) {
    return (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h);
}


///////////////////////////////////////////////////////////////////////////////
// Main function
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* args[]) {
    is_running = initialize_window();

    int is_clicked_1 = 0;
    int is_clicked_2 = 0;

    SDL_Event event;
    while (is_running){
        while (SDL_PollEvent(&event)) {
            
            if (event.type == SDL_QUIT) {
                is_running = false;
            } 

            // there is the need for an else if to avoid the case where the event is both a keydown and a mousemotion
            // because mouse motion is always true, the block will always be moved by the mouse
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        is_running = false;
                        break;
                }
            } 

            else if (event.type == SDL_MOUSEBUTTONDOWN){
                if (is_clicked_1 ==0 && is_in_rectangle(event.button.x, event.button.y, src_rect)) {
                    is_clicked_1 = 1;
                }
                else if (is_clicked_1 == 1 && is_clicked_2 ==0){
                    // update the position of the dst_rect with the position of the mouse
                    dst_rect.x = event.button.x /100 * 100;
                    dst_rect.y = event.button.y /100 * 100;

                    if (is_in_rectangle(event.button.x, event.button.y, dst_rect)) {
                        is_clicked_2 = 1;
                    }
                }
            }
        
            if (is_clicked_1 == 1 && is_clicked_2 == 1) {
                is_clicked_1 = 0;
                is_clicked_2 = 0;
                // updating the source rectangle to the destination rectangle
                src_rect.x = dst_rect.x;
                src_rect.y = dst_rect.y;
            }

           
        }

        render(is_clicked_1, is_clicked_2, src_rect, dst_rect);

    } 


    destroy_window();

    return EXIT_SUCCESS;
}