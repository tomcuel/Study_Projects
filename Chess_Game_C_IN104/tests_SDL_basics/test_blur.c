#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

// Function to load a BMP image
SDL_Surface* loadBMP(const char* filename) {
    // Load the image
    SDL_Surface* image = SDL_LoadBMP(filename);
    // Check if the image was loaded
    if (!image) {
        printf("Failed to load BMP image at %s: %s\n", filename, SDL_GetError());
    }
    return image;
}

// Function to apply a simple box blur to a texture
void applyBlur(SDL_Texture* texture, SDL_Renderer* renderer, int width, int height) {
    SDL_SetRenderTarget(renderer, texture);

    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);
    SDL_RenderReadPixels(renderer, NULL, surface->format->format, surface->pixels, surface->pitch);

    Uint32* pixels = (Uint32*)surface->pixels;
    Uint32* blurredPixels = (Uint32*)malloc(width * height * sizeof(Uint32));

    int blurSize = 5;  // Adjust this value to change the strength of the blur

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int r = 0, g = 0, b = 0, a = 0;
            int count = 0;

            for (int ky = -blurSize; ky <= blurSize; ++ky) {
                for (int kx = -blurSize; kx <= blurSize; ++kx) {
                    int nx = x + kx;
                    int ny = y + ky;

                    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                        Uint32 pixel = pixels[ny * width + nx];
                        SDL_Color color;
                        SDL_GetRGBA(pixel, surface->format, &color.r, &color.g, &color.b, &color.a);

                        r += color.r;
                        g += color.g;
                        b += color.b;
                        a += color.a;
                        count++;
                    }
                }
            }

            r /= count;
            g /= count;
            b /= count;
            a /= count;

            blurredPixels[y * width + x] = SDL_MapRGBA(surface->format, r, g, b, a);
        }
    }

    SDL_UpdateTexture(texture, NULL, blurredPixels, width * sizeof(Uint32));

    free(blurredPixels);
    SDL_FreeSurface(surface);
    SDL_SetRenderTarget(renderer, NULL);
}

// Function to add an image to the renderer
// Here it has been changed by only adding a blur parameter
void add_image_to_render(const char* filename, SDL_Renderer* renderer, SDL_Rect destRect, bool blur) {
    // Load the BMP image
    SDL_Surface* image = loadBMP(filename);
    if (!image) {
        return; // If the image failed to load, exit the function
    }

    // Create texture from surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
    // Check if the texture was created successfully
    if (!texture) {
        printf("Texture creation failed: %s\n", SDL_GetError());
        SDL_FreeSurface(image);
        return;
    }

    if (blur == true) {
        // Create a texture to hold the blurred image
        int width = destRect.w;
        int height = destRect.h;
        SDL_Texture* blurredTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, width, height);
        if (!blurredTexture) {
            printf("Blurred texture creation failed: %s\n", SDL_GetError());
            SDL_DestroyTexture(texture);
            SDL_FreeSurface(image);
            return;
        }

        // Render the original texture to the blurred texture
        SDL_SetRenderTarget(renderer, blurredTexture);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_SetRenderTarget(renderer, NULL);

        // Apply the blur effect to the blurred texture
        applyBlur(blurredTexture, renderer, width, height);

        // Copy the blurred texture to the renderer with destination rectangle
        SDL_RenderCopy(renderer, blurredTexture, NULL, &destRect);

        // Destroy the blurred texture
        SDL_DestroyTexture(blurredTexture);
    } 
    else {
        // Copy the texture to the renderer with destination rectangle
        SDL_RenderCopy(renderer, texture, NULL, &destRect);
    }

    // Free surface and texture
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
}


int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL Blur Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // Create a texture to hold the background (chessboard)
    SDL_Texture* backgroundTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 800, 600);
    if (!backgroundTexture) {
        printf("Background texture creation failed: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Main loop
    int running = 1;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = 0;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    running = 0;
                }
            }
        }

        // Render the background (chessboard) to the background texture
        SDL_SetRenderTarget(renderer, backgroundTexture);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_Rect rect;
        rect.w = 100;
        rect.h = 100;

        // Making the empty chessboard
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 8; j++) {
                rect.x = j * 100;
                rect.y = i * 100;
                if ((i + j) % 2 == 0) {
                    // Case light square
                    SDL_SetRenderDrawColor(renderer, 238, 238, 210, 255); // Light square color
                } else {
                    // Case dark square
                    SDL_SetRenderDrawColor(renderer, 118, 150, 86, 255); // Dark square color
                }
                SDL_RenderFillRect(renderer, &rect);
            }
        }

        // Apply the blur effect to the background texture
        applyBlur(backgroundTexture, renderer, 800, 600);

        // Set the render target back to the default
        SDL_SetRenderTarget(renderer, NULL);

        // Render the blurred background texture
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        // Render the image on top of the blurred background
        add_image_to_render("black_king.bmp", renderer, (SDL_Rect){200, 150, 400, 300}, false);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}