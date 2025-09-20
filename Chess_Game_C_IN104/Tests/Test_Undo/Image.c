#include "Image.h"


SDL_Surface* loadBMP(const char* filename) {
    // Load the image
    SDL_Surface* image = SDL_LoadBMP(filename);
    // Check if the image was loaded
    if (!image) {
        printf("Failed to load BMP image at %s: %s\n", filename, SDL_GetError());
    }
    return image;
}


void add_image_to_render (const char* filename, SDL_Renderer* renderer, SDL_Rect destRect){

    // Load the BMP image
    SDL_Surface* image = loadBMP(filename);
    if (!image) {
        goto Quit; // If the image failed to load, exit the function
    }

    // Create texture from surface 
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
    // Check if the texture was created successfully
    if (!texture) {
        printf("Texture creation failed: %s\n", SDL_GetError());
        SDL_DestroyTexture(texture);
        goto Quit;
    }
    
    // Copy the texture to the renderer with destination rectangle
    SDL_RenderCopy(renderer, texture, NULL, &destRect);

    // Free surface and texture
    SDL_DestroyTexture(texture);
Quit:
    SDL_FreeSurface(image);
}