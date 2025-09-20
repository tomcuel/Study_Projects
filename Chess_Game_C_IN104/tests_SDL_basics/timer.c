#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define COUNTDOWN_SECONDS 5


bool timer_sdl(int* seconds_remaining, int timer_interval){
    bool quit = false;
    printf("Countdown: %d\n", *seconds_remaining);
    while (!quit) {
        
        SDL_Delay(timer_interval);
        (*seconds_remaining)--;

        // If countdown reaches 0, exit the loop
        if (*seconds_remaining == 0)
            quit = true;

        // Print the current countdown value
        printf("Countdown: %d\n", *seconds_remaining);
        fflush(stdout);
    }
    return quit;
}

int main() {
    if (SDL_Init(SDL_INIT_TIMER) != 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    int seconds = COUNTDOWN_SECONDS;
    int timer_interval=1000;

    bool quit = timer_sdl(&seconds, timer_interval);
    if (quit)
        printf("Countdown reached 0\n");
    

    SDL_Quit();
    return 0;
}
