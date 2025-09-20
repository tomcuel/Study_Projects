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


///////////////////////////////////////////////////////////////////////////////
// Global variables
///////////////////////////////////////////////////////////////////////////////
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
int is_running = false;
int last_frame_time = 0;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;


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
// Change the position of the block object
///////////////////////////////////////////////////////////////////////////////
void render(int color) {
    if (color == 0) {
        SDL_SetRenderDrawColor(renderer, 125, 125, 125, 255); // grey color
        SDL_RenderClear(renderer);
    } 
    else {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white color
        SDL_RenderClear(renderer);
    }

    SDL_RenderPresent(renderer);
}


///////////////////////////////////////////////////////////////////////////////
// Main function
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* args[]) {
    is_running = initialize_window();

    int seconds_remaining_color_0 = 5;
    int last_second_color_0 = 0;

    int seconds_remaining_color_1 = 5;
    int last_second_color_1 = 0;

    // color 0 begin to play 
    // both color 1 and color 0 have 5 seconds to play on the screen, after that it close the window and gave us the player that lose, made it
    int color=0;
    int loosing_color=-1;

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
                    case SDLK_j:
                        color=0;
                        break;
                    case SDLK_l:
                        color=1;
                        break;
                    
                }
            } 
           
        }

        render(color);

        // Countdown for each color 

        // for color 0
        if (color == 0) {
            if (seconds_remaining_color_0 > 0) {
                int current_time = SDL_GetTicks();
                int elapsed_time = current_time - last_frame_time;
                if (elapsed_time >= 1000) {
                    seconds_remaining_color_0--;
                    last_frame_time = current_time;
                    if (last_second_color_0 != seconds_remaining_color_0) {
                        printf("Current time remaining for color 2 : %d seconds\n", seconds_remaining_color_0);
                        last_second_color_0 = seconds_remaining_color_0;
                    }
                }
            } 
            else {
                is_running = false;
                loosing_color=0;
            }
        }
        
        // for color 1
        else {
            if (seconds_remaining_color_1 > 0) {
                int current_time = SDL_GetTicks();
                int elapsed_time = current_time - last_frame_time;
                if (elapsed_time >= 1000) {
                    seconds_remaining_color_1--;
                    last_frame_time = current_time;
                    if (last_second_color_1 != seconds_remaining_color_1) {
                        printf("Current time remaining for color 1 : %d seconds\n", seconds_remaining_color_1);
                        last_second_color_1 = seconds_remaining_color_1;
                    }
                }
            } 
            else {
                is_running = false;
                loosing_color=1;
            }
        }



    }

    if (loosing_color == 0){
        printf("Color grey looses\n");
    }
    else {
        printf("Color white looses\n");
    }


    destroy_window();

    return EXIT_SUCCESS;
}