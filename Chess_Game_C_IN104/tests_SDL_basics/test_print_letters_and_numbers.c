#include <SDL2/SDL.h>
#include <stdio.h>

// Function to draw the letter 'A' using rectangles within a specified rectangle
void drawLetterA(SDL_Renderer *renderer, int x, int y, int width, int height) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int barWidth = width / 10;
    SDL_Rect rects[] = {
        { x, y, barWidth, height },                          // Left vertical bar
        { x + width - barWidth, y, barWidth, height },       // Right vertical bar
        { x + barWidth, y, width - 2 * barWidth, barWidth }, // Top horizontal bar
        { x + barWidth, y + height / 2 - barWidth / 2, width - 2 * barWidth, barWidth } // Middle horizontal bar
    };
    for (int i = 0; i < 4; ++i) {
        SDL_RenderFillRect(renderer, &rects[i]);
    }
}

// Function to draw the letter 'B'
void drawLetterB(SDL_Renderer *renderer, int x, int y, int width, int height) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int barWidth = width / 10;
    int halfHeight = height / 2;
    SDL_Rect rects[] = {
        { x, y, barWidth, height },                         // Left vertical bar
        { x + width - barWidth, y, barWidth, halfHeight },  // Top right vertical bar
        { x + width - barWidth, y + halfHeight, barWidth, halfHeight }, // Bottom right vertical bar
        { x + barWidth, y, width - barWidth, barWidth },    // Top horizontal bar
        { x + barWidth, y + halfHeight - barWidth / 2, width - barWidth, barWidth }, // Middle horizontal bar
        { x + barWidth, y + height - barWidth, width - barWidth, barWidth } // Bottom horizontal bar
    };
    for (int i = 0; i < 6; ++i) {
        SDL_RenderFillRect(renderer, &rects[i]);
    }
}

// Function to draw the letter 'C'
void drawLetterC(SDL_Renderer *renderer, int x, int y, int width, int height) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int barWidth = width / 10;
    SDL_Rect rects[] = {
        { x, y, width, barWidth },           // Top horizontal bar
        { x, y + height - barWidth, width, barWidth }, // Bottom horizontal bar
        { x, y, barWidth, height }           // Left vertical bar
    };
    for (int i = 0; i < 3; ++i) {
        SDL_RenderFillRect(renderer, &rects[i]);
    }
}

// Function to draw the letter 'D'
void drawLetterD(SDL_Renderer *renderer, int x, int y, int width, int height) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int barWidth = width / 10;
    SDL_Rect rects[] = {
        { x, y, barWidth, height },                       // Left vertical bar
        { x + width - barWidth, y, barWidth, height },    // Right vertical bar
        { x, y, width - barWidth, barWidth },             // Top horizontal bar
        { x, y + height - barWidth, width - barWidth, barWidth } // Bottom horizontal bar
    };
    for (int i = 0; i < 4; ++i) {
        SDL_RenderFillRect(renderer, &rects[i]);
    }
}

// Function to draw the letter 'E'
void drawLetterE(SDL_Renderer *renderer, int x, int y, int width, int height) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int barWidth = width / 10;
    SDL_Rect rects[] = {
        { x, y, barWidth, height },              // Left vertical bar
        { x, y, width, barWidth },               // Top horizontal bar
        { x, y + height / 2 - barWidth / 2, width, barWidth }, // Middle horizontal bar
        { x, y + height - barWidth, width, barWidth } // Bottom horizontal bar
    };
    for (int i = 0; i < 4; ++i) {
        SDL_RenderFillRect(renderer, &rects[i]);
    }
}

// Function to draw the letter 'F'
void drawLetterF(SDL_Renderer *renderer, int x, int y, int width, int height) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int barWidth = width / 10;
    SDL_Rect rects[] = {
        { x, y, barWidth, height },              // Left vertical bar
        { x, y, width, barWidth },               // Top horizontal bar
        { x, y + height / 2 - barWidth / 2, width, barWidth } // Middle horizontal bar
    };
    for (int i = 0; i < 3; ++i) {
        SDL_RenderFillRect(renderer, &rects[i]);
    }
}

// Function to draw the letter 'G'
void drawLetterG(SDL_Renderer *renderer, int x, int y, int width, int height) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int barWidth = width / 10;
    SDL_Rect rects[] = {
        { x, y, width, barWidth },               // Top horizontal bar
        { x, y + height - barWidth, width, barWidth }, // Bottom horizontal bar
        { x, y, barWidth, height },              // Left vertical bar
        { x + width - barWidth, y + height / 2, barWidth, height / 2 }, // Bottom right vertical bar
        { x + width / 2, y + height / 2, width / 2, barWidth } // Middle horizontal bar
    };
    for (int i = 0; i < 5; ++i) {
        SDL_RenderFillRect(renderer, &rects[i]);
    }
}

// Function to draw the letter 'H'
void drawLetterH(SDL_Renderer *renderer, int x, int y, int width, int height) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int barWidth = width / 10;
    SDL_Rect rects[] = {
        { x, y, barWidth, height },                       // Left vertical bar
        { x + width - barWidth, y, barWidth, height },    // Right vertical bar
        { x, y + height / 2 - barWidth / 2, width, barWidth } // Middle horizontal bar
    };
    for (int i = 0; i < 3; ++i) {
        SDL_RenderFillRect(renderer, &rects[i]);
    }
}

// Function to draw the number '1'
void drawNumber1(SDL_Renderer *renderer, int x, int y, int width, int height) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int barWidth = width / 10;
    SDL_Rect rects[] = {
        { x + width / 2 - barWidth / 2, y, barWidth, height } // Vertical bar
    };
    for (int i = 0; i < 1; ++i) {
        SDL_RenderFillRect(renderer, &rects[i]);
    }
}

// Function to draw the number '2'
void drawNumber2(SDL_Renderer *renderer, int x, int y, int width, int height) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int barWidth = width / 10;
    SDL_Rect rects[] = {
        { x, y, width, barWidth },           // Top horizontal bar
        { x + width - barWidth, y, barWidth, height / 2 }, // Top right vertical bar
        { x, y + height / 2 - barWidth / 2, width, barWidth }, // Middle horizontal bar
        { x, y + height / 2, barWidth, height / 2 }, // Bottom left vertical bar
        { x, y + height - barWidth, width, barWidth } // Bottom horizontal bar
    };
    for (int i = 0; i < 5; ++i) {
        SDL_RenderFillRect(renderer, &rects[i]);
    }
}

// Function to draw the number '3'
void drawNumber3(SDL_Renderer *renderer, int x, int y, int width, int height) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int barWidth = width / 10;
    SDL_Rect rects[] = {
        { x, y, width, barWidth },           // Top horizontal bar
        { x + width - barWidth, y, barWidth, height }, // Right vertical bar
        { x, y + height / 2 - barWidth / 2, width, barWidth }, // Middle horizontal bar
        { x, y + height - barWidth, width, barWidth } // Bottom horizontal bar
    };
    for (int i = 0; i < 4; ++i) {
        SDL_RenderFillRect(renderer, &rects[i]);
    }
}

// Function to draw the number '4'
void drawNumber4(SDL_Renderer *renderer, int x, int y, int width, int height) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int barWidth = width / 10;
    SDL_Rect rects[] = {
        { x, y, barWidth, height / 2 },                   // Top left vertical bar
        { x + width - barWidth, y, barWidth, height },    // Right vertical bar
        { x, y + height / 2 - barWidth / 2, width, barWidth } // Middle horizontal bar
    };
    for (int i = 0; i < 3; ++i) {
        SDL_RenderFillRect(renderer, &rects[i]);
    }
}

// Function to draw the number '5'
void drawNumber5(SDL_Renderer *renderer, int x, int y, int width, int height) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int barWidth = width / 10;
    SDL_Rect rects[] = {
        { x, y, width, barWidth },           // Top horizontal bar
        { x, y, barWidth, height / 2 },      // Top left vertical bar
        { x, y + height / 2 - barWidth / 2, width, barWidth }, // Middle horizontal bar
        { x + width - barWidth, y + height / 2, barWidth, height / 2 }, // Bottom right vertical bar
        { x, y + height - barWidth, width, barWidth } // Bottom horizontal bar
    };
    for (int i = 0; i < 5; ++i) {
        SDL_RenderFillRect(renderer, &rects[i]);
    }
}

// Function to draw the number '6'
void drawNumber6(SDL_Renderer *renderer, int x, int y, int width, int height) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int barWidth = width / 10;
    SDL_Rect rects[] = {
        { x, y, width, barWidth },               // Top horizontal bar
        { x, y, barWidth, height },              // Left vertical bar
        { x + width - barWidth, y + height / 2, barWidth, height / 2 }, // Bottom right vertical bar
        { x, y + height / 2 - barWidth / 2, width, barWidth }, // Middle horizontal bar
        { x, y + height - barWidth, width, barWidth } // Bottom horizontal bar
    };
    for (int i = 0; i < 5; ++i) {
        SDL_RenderFillRect(renderer, &rects[i]);
    }
}

// Function to draw the number '7'
void drawNumber7(SDL_Renderer *renderer, int x, int y, int width, int height) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int barWidth = width / 10;
    SDL_Rect rects[] = {
        { x, y, width, barWidth },               // Top horizontal bar
        { x + width - barWidth, y, barWidth, height } // Right vertical bar
    };
    for (int i = 0; i < 2; ++i) {
        SDL_RenderFillRect(renderer, &rects[i]);
    }
}

// Function to draw the number '8'
void drawNumber8(SDL_Renderer *renderer, int x, int y, int width, int height) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int barWidth = width / 10;
    SDL_Rect rects[] = {
        { x, y, width, barWidth },               // Top horizontal bar
        { x, y + height - barWidth, width, barWidth }, // Bottom horizontal bar
        { x, y + height / 2 - barWidth / 2, width, barWidth }, // Middle horizontal bar
        { x, y, barWidth, height },              // Left vertical bar
        { x + width - barWidth, y, barWidth, height } // Right vertical bar
    };
    for (int i = 0; i < 5; ++i) {
        SDL_RenderFillRect(renderer, &rects[i]);
    }
}

// Main function
int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window *win = SDL_CreateWindow("Draw Letters and Numbers", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
    if (win == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_DestroyWindow(win);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Set render color to black (background color)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw letters and numbers in specified rectangles
        drawLetterA(renderer, 50, 50, 50, 100);
        drawLetterB(renderer, 150, 50, 50, 100);
        drawLetterC(renderer, 250, 50, 50, 100);
        drawLetterD(renderer, 350, 50, 50, 100);
        drawLetterE(renderer, 450, 50, 50, 100);
        drawLetterF(renderer, 550, 50, 50, 100);
        drawLetterG(renderer, 650, 50, 50, 100);
        drawLetterH(renderer, 750, 50, 50, 100);
    
        drawNumber1(renderer, 50, 200, 50, 100);
        drawNumber2(renderer, 150, 200, 50, 100);
        drawNumber3(renderer, 250, 200, 50, 100);
        drawNumber4(renderer, 350, 200, 50, 100);
        drawNumber5(renderer, 450, 200, 50, 100);
        drawNumber6(renderer, 550, 200, 50, 100);
        drawNumber7(renderer, 650, 200, 50, 100);
        drawNumber8(renderer, 750, 200, 50, 100);

        // Present the renderer
        SDL_RenderPresent(renderer);
    }

    // Cleanup and close
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}