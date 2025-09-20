#include <SDL2/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FONT_WIDTH 20
#define FONT_HEIGHT 20

// Define a font for rendering digits
const int font[10][FONT_WIDTH] = {
    {0x00, 0x7E, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x7E}, // 0
    {0x00, 0x00, 0x42, 0x82, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00}, // 1
    {0x00, 0x42, 0x87, 0x89, 0x91, 0xA1, 0xC1, 0x42, 0x00, 0x00}, // 2
    {0x42, 0x81, 0x81, 0x91, 0x91, 0x91, 0x89, 0x76, 0x00, 0x00}, // 3
    {0x18, 0x28, 0x48, 0x88, 0xFF, 0xFF, 0x08, 0x08, 0x08, 0x00}, // 4
    {0xF2, 0x91, 0x91, 0x91, 0x91, 0x91, 0x89, 0x86, 0x00, 0x00}, // 5
    {0x7E, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x0E, 0x00, 0x00}, // 6
    {0x80, 0x80, 0x81, 0x82, 0x84, 0x88, 0x90, 0xE0, 0x00, 0x00}, // 7
    {0x76, 0x89, 0x91, 0x91, 0x91, 0x91, 0x89, 0x76, 0x00, 0x00}, // 8
    {0x72, 0x89, 0x91, 0x91, 0x91, 0x91, 0x89, 0x7E, 0x00, 0x00}  // 9
};

// Draw a digit on the screen at the specified position
void drawDigit(SDL_Renderer *renderer, int digit, int x, int y) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set color to white
    for (int i = 0; i < FONT_HEIGHT; i++) {
        for (int j = 0; j < FONT_WIDTH; j++) {
            if (font[digit][j] & (1 << (FONT_WIDTH - i - 1))) {
                SDL_RenderDrawPoint(renderer, x + j, y + i);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Renderer *renderer;

    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Create window and renderer
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);

    // Main loop
    int running = 1;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
        SDL_RenderClear(renderer);

        // Draw a number (e.g., 12345) at position (100, 100)
        int number = 12345;
        int x = 100;
        int y = 100;
        while (number > 0) {
            int digit = number % 10;
            drawDigit(renderer, digit, x, y);
            x -= FONT_WIDTH; // Move right for the next digit
            number /= 10;
        }

        // Present the rendered frame
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
