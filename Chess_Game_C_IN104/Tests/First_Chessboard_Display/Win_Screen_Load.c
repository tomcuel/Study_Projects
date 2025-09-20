#include <SDL2/SDL.h>
#include "Image.h"


int main() {
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur lors de l'initialisation de la SDL : %s\n", SDL_GetError());
        return 1;
    }

    // Création de la fenêtre
    SDL_Window* window = SDL_CreateWindow("Beige Screen", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Création du renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Erreur lors de la création du renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Remplissage de l'écran avec la couleur beige
    SDL_SetRenderDrawColor(renderer, 245, 245, 220, 255);
    SDL_RenderClear(renderer);

    //Ajouter image victoire.bmp

    SDL_Rect destRect;
    destRect.x = 0;
    destRect.y = 0;
    destRect.w = 800;
    destRect.h = 600;

    

    //Victoire : result = 1
    //Défaite : result = 2
    int result = 1;
    if (result == 1)
        {add_image_to_render("victory.bmp", renderer, destRect);}
    else
        {add_image_to_render("defeat.bmp", renderer, destRect);}


    SDL_RenderPresent(renderer);

    // Boucle principale
    SDL_Event event;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }


    // Libération des ressources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}