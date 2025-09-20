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


void applyBlur(SDL_Texture* texture, SDL_Renderer* renderer, int width, int height) {
    // define how much to blur the image, depends on the time we want to consacre to blurring the image
    int radius = 3;
    
    SDL_SetRenderTarget(renderer, texture);

    // Gaussian kernel generation
    float kernel[2 * radius + 1][2 * radius + 1];
    float sigma = radius / 2.0f;
    float sigmaSq = 2.0f * sigma * sigma;
    float sum = 0.0f;

    for (int x = -radius; x <= radius; ++x) {
        for (int y = -radius; y <= radius; ++y) {
            float r = sqrt(x * x + y * y);
            kernel[x + radius][y + radius] = exp(-(r * r) / sigmaSq) / (M_PI * sigmaSq);
            sum += kernel[x + radius][y + radius];
        }
    }

    // Normalize the kernel
    for (int i = 0; i < 2 * radius + 1; ++i) {
        for (int j = 0; j < 2 * radius + 1; ++j) {
            kernel[i][j] /= sum;
        }
    }

    // Apply the Gaussian blur
    Uint32* pixels = (Uint32*)malloc(width * height * sizeof(Uint32));
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_RGBA32, pixels, width * sizeof(Uint32));

    Uint32* blurredPixels = (Uint32*)malloc(width * height * sizeof(Uint32));

    for (int x = radius; x < width - radius; ++x) {
        for (int y = radius; y < height - radius; ++y) {
            float r = 0, g = 0, b = 0, a = 0;

            for (int i = -radius; i <= radius; ++i) {
                for (int j = -radius; j <= radius; ++j) {
                    Uint32 pixel = pixels[(y + j) * width + (x + i)];
                    SDL_Color color;
                    SDL_GetRGBA(pixel, SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32), &color.r, &color.g, &color.b, &color.a);

                    float weight = kernel[j + radius][i + radius];

                    r += color.r * weight;
                    g += color.g * weight;
                    b += color.b * weight;
                    a += color.a * weight;
                }
            }

            Uint32 blurredPixel = SDL_MapRGBA(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32), r, g, b, a);
            blurredPixels[y * width + x] = blurredPixel;
        }
    }

    SDL_UpdateTexture(texture, NULL, blurredPixels, width * sizeof(Uint32));

    free(pixels);
    free(blurredPixels);
    SDL_SetRenderTarget(renderer, NULL);
}


void add_image_to_render(const char* filename, SDL_Renderer* renderer, SDL_Rect destRect, bool blur) {
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

    // if blur is true, apply the blur effect
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
    // otherwise, copy the texture to the renderer with destination rectangle (i.e. no blur effect)
    else {
        // Copy the texture to the renderer with destination rectangle
        SDL_RenderCopy(renderer, texture, NULL, &destRect);
    }

    // Free surface and texture
    SDL_DestroyTexture(texture);
Quit:
    SDL_FreeSurface(image);
}