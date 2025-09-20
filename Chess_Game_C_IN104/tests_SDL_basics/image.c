#include <stdio.h>
#include <SDL2/SDL.h>

SDL_Surface* loadBMP(const char* image_path) {
    SDL_Surface* image = SDL_LoadBMP(image_path);
    if (!image) {
        printf("Failed to load BMP image at %s: %s\n", image_path, SDL_GetError());
    }
    return image;
}

int main() {
    const char* image_path = "black_king.bmp";

    /* Initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    /* Create a window */
    SDL_Window* window = SDL_CreateWindow("BMP Image Viewer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    /* Create a renderer */
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    /* Load the BMP image */
    SDL_Surface* image = loadBMP(image_path);
    if (!image) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    /* Create texture from surface */
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
    if (!texture) {
        printf("Texture creation failed: %s\n", SDL_GetError());
        SDL_FreeSurface(image);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    /* Clear the renderer */
    SDL_RenderClear(renderer);

    /* Define destination rectangle */
    SDL_Rect destRect = {100, 100, 200, 200}; // Adjust the coordinates and size as needed

    /* Copy the texture to the renderer with destination rectangle */
    SDL_RenderCopy(renderer, texture, NULL, &destRect);

    /* Present the renderer */
    SDL_RenderPresent(renderer);

    /* Event loop */
    SDL_Event event;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }

    /* Cleanup */
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
