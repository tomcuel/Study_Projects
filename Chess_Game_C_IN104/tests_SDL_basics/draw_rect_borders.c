#include <SDL2/SDL.h>

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Cadre Rouge SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event event;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
                break;
            }

            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        quit = 1;
                        break;
                }
            }

            
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        // Définir la couleur du rendu sur rouge (R: 255, G: 0, B: 0, A: 255)
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        // Créer un rectangle rouge
        SDL_Rect rect = { 100, 100, 200, 100 };

        // Dessiner les contours du rectangle rouge
        SDL_RenderDrawLine(renderer, rect.x, rect.y, rect.x + rect.w, rect.y);
        SDL_RenderDrawLine(renderer, rect.x + rect.w, rect.y, rect.x + rect.w, rect.y + rect.h);
        SDL_RenderDrawLine(renderer, rect.x + rect.w, rect.y + rect.h, rect.x, rect.y + rect.h);
        SDL_RenderDrawLine(renderer, rect.x, rect.y + rect.h, rect.x, rect.y);

        // Mettre à jour l'affichage
        SDL_RenderPresent(renderer);
    }


    // Libérer les ressources et quitter SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
