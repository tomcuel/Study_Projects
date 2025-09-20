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
// Declare the block object : 
// it's a rectangle of coordinates [x,x+width]x[y,y+height]
///////////////////////////////////////////////////////////////////////////////
struct object {
    float x;
    float y;
    float width;
    float height;
   
} block;


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
// Setup function that runs once at the beginning of our program
///////////////////////////////////////////////////////////////////////////////
void setup(void) {
    // Initialize the block object
    block.width = 50;
    block.height = 50;
    block.x = WINDOW_WIDTH / 2 - block.width / 2;
    block.y = WINDOW_HEIGHT / 2 - block.height / 2;
    
}


///////////////////////////////////////////////////////////////////////////////
// Render function to draw game objects in the SDL window
// Change the position of the block object
///////////////////////////////////////////////////////////////////////////////
void render(void) {
    SDL_SetRenderDrawColor(renderer, 125, 125, 125, 255); // grey color
    SDL_RenderClear(renderer);

    // Draw a rectangle for the ball object
    SDL_Rect block_rect = {
        (int)block.x,
        (int)block.y,
        (int)block.width,
        (int)block.height
    };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white color
    SDL_RenderFillRect(renderer, &block_rect);

    SDL_RenderPresent(renderer);
}


///////////////////////////////////////////////////////////////////////////////
// Function to do SDL events and process keyboard and mouse input accordingly
// Also update the rendering
///////////////////////////////////////////////////////////////////////////////
void process_keyboard_mouse_input(void) {
    SDL_Event event;
    int quit = 0;
    while (!quit){
        while (SDL_PollEvent(&event)) {
            
            if (event.type == SDL_QUIT) {
                is_running = false;
                quit = 1;
            } 

            // there is the need for an else if to avoid the case where the event is both a keydown and a mousemotion
            // because mouse motion is always true, the block will always be moved by the mouse
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        is_running = false;
                        quit = 1;
                        break;
                    case SDLK_UP:
                        block.y -= 10;
                        break;
                    case SDLK_DOWN:
                        block.y += 10;
                        break;
                    case SDLK_LEFT:
                        block.x -= 10;
                        break;
                    case SDLK_RIGHT:
                        block.x += 10;
                        break;
                }
            } 

            // in the end, for our chess game, the get_state_mouse will be more useful than using the motion of the mouse, even if a cursor will be displayed and use this type of function 
            else if (event.type == SDL_MOUSEMOTION) {
                block.x = event.motion.x;
                block.y = event.motion.y;
            }
        }

        render();
    }
}


///////////////////////////////////////////////////////////////////////////////
// Main function
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* args[]) {
    is_running = initialize_window();

    setup();

    while (is_running) {
        process_keyboard_mouse_input();
    }

    destroy_window();

    return EXIT_SUCCESS;
}