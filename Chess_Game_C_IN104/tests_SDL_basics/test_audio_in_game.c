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
// Function to play a sound
///////////////////////////////////////////////////////////////////////////////
void play_sound(const char* filename) {
	// local variables
	static Uint32 wav_length; // length of our sample
	static Uint8 *wav_buffer; // buffer containing our audio file
	static SDL_AudioSpec wav_spec; // the specs of our piece of music
	
	// Load the WAV
	// the specs, length and buffer of our wav are filled
    // check if the file is loaded
	if( SDL_LoadWAV(filename, &wav_spec, &wav_buffer, &wav_length) == NULL ){
        printf("Failed to load wav file: %s\n", SDL_GetError());
	    SDL_FreeWAV(wav_buffer);
	}
	
    // open audio device
    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0);
    // play audio
    int success = SDL_QueueAudio(deviceId, wav_buffer, wav_length);
    if (success != 0) {
        fprintf(stderr, "Failed to queue audio: %s\n", SDL_GetError());
        SDL_FreeWAV(wav_buffer);
    }
    SDL_PauseAudioDevice(deviceId, 0);
    // keep application running long enough to hear the sound
    
    // wait for sound to finish
    SDL_Delay(300);

    // clean up
    SDL_CloseAudioDevice(deviceId);
	SDL_FreeWAV(wav_buffer);
}


///////////////////////////////////////////////////////////////////////////////
// main to play a sound in game
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]){
    
    is_running = initialize_window();

    SDL_Event event;
    while (is_running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                is_running = false;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        is_running = false;
                        break;
                    case SDLK_SPACE:
                        play_sound("take.wav");
                        break;
                    default:
                        break;
                }
            }
        }
    }

    destroy_window();

    return EXIT_SUCCESS;
}