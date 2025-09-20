#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main() {
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Create the window
    SDL_Window* window = SDL_CreateWindow("Affichage SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

    // Create the renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Set the background color
    SDL_SetRenderDrawColor(renderer, 245, 245, 220, 255); // Beige clair

    // Clear the screen with the background color
    SDL_RenderClear(renderer);

    // Load the image
    SDL_Surface* surface = IMG_Load("black_bishop.bmp");
    if (!surface) {
        printf("Failed to load image: %s\n", IMG_GetError());
        return 1;
    }

    // Create a texture from the surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    // Set the destination rectangle
    SDL_Rect destRect;
    destRect.x = 100;  // X position of the image
    destRect.y = 100;  // Y position of the image
    destRect.w = 200;  // Width of the image
    destRect.h = 200;  // Height of the image

    // Render the texture onto the renderer
    SDL_RenderCopy(renderer, texture, NULL, &destRect);

    // Update the display
    SDL_RenderPresent(renderer);

    // Main loop
    SDL_Event event;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }

    // Free resources
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
