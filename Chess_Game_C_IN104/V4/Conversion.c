#include "Conversion.h"


int Convert_Letter_to_Number(char letter){
	// Check if the letter is a valid letter (A-H or a-h)

	// Majuscule
	if (letter >= 'A' && letter <= 'H')
		return letter - 'A';

	// Minuscule
	if (letter >= 'a' && letter <= 'h')
		return letter - 'a';
	return -1;
}


char Convert_Number_to_Letter_Min(int number){
	// Check if the number is a valid number (0-7)
	if (number >= 0 && number <= 7)
		// translate the number to a letter
		return number + 'a';
	return -1;
}


char Convert_Number_to_Letter_Maj(int number){
	// Check if the number is a valid number (0-7)
	if (number >= 0 && number <= 7)
		// translate the number to a letter
		return number + 'A';
	return -1;
}


void drawLetterA(SDL_Renderer *renderer, int x, int y, int width, int height) {
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


void drawLetterB(SDL_Renderer *renderer, int x, int y, int width, int height) {
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


void drawLetterC(SDL_Renderer *renderer, int x, int y, int width, int height) {
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


void drawLetterD(SDL_Renderer *renderer, int x, int y, int width, int height) {
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


void drawLetterE(SDL_Renderer *renderer, int x, int y, int width, int height) {
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


void drawLetterF(SDL_Renderer *renderer, int x, int y, int width, int height) {
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


void drawLetterG(SDL_Renderer *renderer, int x, int y, int width, int height) {
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


void drawLetterH(SDL_Renderer *renderer, int x, int y, int width, int height) {
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


void drawNumber1(SDL_Renderer *renderer, int x, int y, int width, int height) {
    int barWidth = width / 10;
    SDL_Rect rects[] = {
        { x + width / 2 - barWidth / 2, y, barWidth, height } // Vertical bar
    };
    for (int i = 0; i < 1; ++i) {
        SDL_RenderFillRect(renderer, &rects[i]);
    }
}


void drawNumber2(SDL_Renderer *renderer, int x, int y, int width, int height) {
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


void drawNumber3(SDL_Renderer *renderer, int x, int y, int width, int height) {
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


void drawNumber4(SDL_Renderer *renderer, int x, int y, int width, int height) {
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


void drawNumber5(SDL_Renderer *renderer, int x, int y, int width, int height) {
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


void drawNumber6(SDL_Renderer *renderer, int x, int y, int width, int height) {
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


void drawNumber7(SDL_Renderer *renderer, int x, int y, int width, int height) {
    int barWidth = width / 10;
    SDL_Rect rects[] = {
        { x, y, width, barWidth },               // Top horizontal bar
        { x + width - barWidth, y, barWidth, height } // Right vertical bar
    };
    for (int i = 0; i < 2; ++i) {
        SDL_RenderFillRect(renderer, &rects[i]);
    }
}


void drawNumber8(SDL_Renderer *renderer, int x, int y, int width, int height) {
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