#ifndef __CONVERSIONS_H__
#define __CONVERSIONS_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

/////////////////////////////////////////////////////////////////////////////////////
// Conversion Summary :
/**
 * Convert_Letter_to_Number - converts a letter to a number
 * Convert_Number_to_Letter_Min - converts a number to a letter in minuscule
 * Convert_Number_to_Letter_Maj - converts a number to a letter in majuscule
 * 
 * Will be use in the chessboard rendering, to show the row (number) and the column (letter) of the pieces
 * since it's displayed like that on the chessboard
 * if it's possible to use TTF but It doesn't seem to be the case for now
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Function that converts a letter to a number (don't know if it will be useful, but it's here just in case)
/**
 * @param letter - the letter to convert
 * @return int - the number corresponding to the letter
 * -1, if the letter is not a valid letter
**/
/////////////////////////////////////////////////////////////////////////////////////
int Convert_Letter_to_Number(char letter);


/////////////////////////////////////////////////////////////////////////////////////
// Function that converts a number to a letter in minuscule (will be used to print the move and the log)
/**
 * @param number - the number to convert
 * @return char - the letter corresponding to the number
 * -1, if the number is not a valid number
**/
/////////////////////////////////////////////////////////////////////////////////////
char Convert_Number_to_Letter_Min(int number);


/////////////////////////////////////////////////////////////////////////////////////
// Function that converts a number to a letter (will be used to search for the letter to print on the board)
/**
 * @param number - the number to convert
 * @return char - the letter corresponding to the number
 * -1, if the number is not a valid number
**/
/////////////////////////////////////////////////////////////////////////////////////
char Convert_Number_to_Letter_Maj(int number);


/////////////////////////////////////////////////////////////////////////////////////
// Function to draw the letter 'A' using rectangles within a specified rectangle
/**
 * @param renderer - the renderer to draw the letter
 * @param x - the x position of the rectangle
 * @param y - the y position of the rectangle
 * @param width - the width of the rectangle
 * @param height - the height of the rectangle
**/
/////////////////////////////////////////////////////////////////////////////////////
void drawLetterA(SDL_Renderer *renderer, int x, int y, int width, int height);


/////////////////////////////////////////////////////////////////////////////////////
// Function to draw the letter 'B' using rectangles within a specified rectangle
/**
 * @param renderer - the renderer to draw the letter
 * @param x - the x position of the rectangle
 * @param y - the y position of the rectangle
 * @param width - the width of the rectangle
 * @param height - the height of the rectangle
**/
/////////////////////////////////////////////////////////////////////////////////////
void drawLetterB(SDL_Renderer *renderer, int x, int y, int width, int height);


/////////////////////////////////////////////////////////////////////////////////////
// Function to draw the letter 'C' using rectangles within a specified rectangle
/**
 * @param renderer - the renderer to draw the letter
 * @param x - the x position of the rectangle
 * @param y - the y position of the rectangle
 * @param width - the width of the rectangle
 * @param height - the height of the rectangle
**/
/////////////////////////////////////////////////////////////////////////////////////
void drawLetterC(SDL_Renderer *renderer, int x, int y, int width, int height);


/////////////////////////////////////////////////////////////////////////////////////
// Function to draw the letter 'D' using rectangles within a specified rectangle
/**
 * @param renderer - the renderer to draw the letter
 * @param x - the x position of the rectangle
 * @param y - the y position of the rectangle
 * @param width - the width of the rectangle
 * @param height - the height of the rectangle
**/
/////////////////////////////////////////////////////////////////////////////////////
void drawLetterD(SDL_Renderer *renderer, int x, int y, int width, int height);


/////////////////////////////////////////////////////////////////////////////////////
// Function to draw the letter 'E' using rectangles within a specified rectangle
/**
 * @param renderer - the renderer to draw the letter
 * @param x - the x position of the rectangle
 * @param y - the y position of the rectangle
 * @param width - the width of the rectangle
 * @param height - the height of the rectangle
**/
/////////////////////////////////////////////////////////////////////////////////////
void drawLetterE(SDL_Renderer *renderer, int x, int y, int width, int height);


/////////////////////////////////////////////////////////////////////////////////////
// Function to draw the letter 'F' using rectangles within a specified rectangle
/**
 * @param renderer - the renderer to draw the letter
 * @param x - the x position of the rectangle
 * @param y - the y position of the rectangle
 * @param width - the width of the rectangle
 * @param height - the height of the rectangle
**/
/////////////////////////////////////////////////////////////////////////////////////
void drawLetterF(SDL_Renderer *renderer, int x, int y, int width, int height);


/////////////////////////////////////////////////////////////////////////////////////
// Function to draw the letter 'G' using rectangles within a specified rectangle
/**
 * @param renderer - the renderer to draw the letter
 * @param x - the x position of the rectangle
 * @param y - the y position of the rectangle
 * @param width - the width of the rectangle
 * @param height - the height of the rectangle
**/
/////////////////////////////////////////////////////////////////////////////////////
void drawLetterG(SDL_Renderer *renderer, int x, int y, int width, int height);


/////////////////////////////////////////////////////////////////////////////////////
// Function to draw the letter 'H' using rectangles within a specified rectangle
/**
 * @param renderer - the renderer to draw the letter
 * @param x - the x position of the rectangle
 * @param y - the y position of the rectangle
 * @param width - the width of the rectangle
 * @param height - the height of the rectangle
**/
/////////////////////////////////////////////////////////////////////////////////////
void drawLetterH(SDL_Renderer *renderer, int x, int y, int width, int height);


/////////////////////////////////////////////////////////////////////////////////////
// Function to draw the number '1' using rectangles within a specified rectangle
/**
 * @param renderer - the renderer to draw the number
 * @param x - the x position of the rectangle
 * @param y - the y position of the rectangle
 * @param width - the width of the rectangle
 * @param height - the height of the rectangle
**/
/////////////////////////////////////////////////////////////////////////////////////
void drawNumber1(SDL_Renderer *renderer, int x, int y, int width, int height);


/////////////////////////////////////////////////////////////////////////////////////
// Function to draw the number '2' using rectangles within a specified rectangle
/**
 * @param renderer - the renderer to draw the number
 * @param x - the x position of the rectangle
 * @param y - the y position of the rectangle
 * @param width - the width of the rectangle
 * @param height - the height of the rectangle
**/
/////////////////////////////////////////////////////////////////////////////////////
void drawNumber2(SDL_Renderer *renderer, int x, int y, int width, int height);


/////////////////////////////////////////////////////////////////////////////////////
// Function to draw the number '3' using rectangles within a specified rectangle
/**
 * @param renderer - the renderer to draw the number
 * @param x - the x position of the rectangle
 * @param y - the y position of the rectangle
 * @param width - the width of the rectangle
 * @param height - the height of the rectangle
**/
/////////////////////////////////////////////////////////////////////////////////////
void drawNumber3(SDL_Renderer *renderer, int x, int y, int width, int height);


/////////////////////////////////////////////////////////////////////////////////////
// Function to draw the number '4' using rectangles within a specified rectangle
/**
 * @param renderer - the renderer to draw the number
 * @param x - the x position of the rectangle
 * @param y - the y position of the rectangle
 * @param width - the width of the rectangle
 * @param height - the height of the rectangle
**/
/////////////////////////////////////////////////////////////////////////////////////
void drawNumber4(SDL_Renderer *renderer, int x, int y, int width, int height);


/////////////////////////////////////////////////////////////////////////////////////
// Function to draw the number '5' using rectangles within a specified rectangle
/**
 * @param renderer - the renderer to draw the number
 * @param x - the x position of the rectangle
 * @param y - the y position of the rectangle
 * @param width - the width of the rectangle
 * @param height - the height of the rectangle
**/
/////////////////////////////////////////////////////////////////////////////////////
void drawNumber5(SDL_Renderer *renderer, int x, int y, int width, int height);


/////////////////////////////////////////////////////////////////////////////////////
// Function to draw the number '6' using rectangles within a specified rectangle
/**
 * @param renderer - the renderer to draw the number
 * @param x - the x position of the rectangle
 * @param y - the y position of the rectangle
 * @param width - the width of the rectangle
 * @param height - the height of the rectangle
**/
/////////////////////////////////////////////////////////////////////////////////////
void drawNumber6(SDL_Renderer *renderer, int x, int y, int width, int height);


/////////////////////////////////////////////////////////////////////////////////////
// Function to draw the number '7' using rectangles within a specified rectangle
/**
 * @param renderer - the renderer to draw the number
 * @param x - the x position of the rectangle
 * @param y - the y position of the rectangle
 * @param width - the width of the rectangle
 * @param height - the height of the rectangle
**/
/////////////////////////////////////////////////////////////////////////////////////
void drawNumber7(SDL_Renderer *renderer, int x, int y, int width, int height);


/////////////////////////////////////////////////////////////////////////////////////
// Function to draw the number '8' using rectangles within a specified rectangle
/**
 * @param renderer - the renderer to draw the number
 * @param x - the x position of the rectangle
 * @param y - the y position of the rectangle
 * @param width - the width of the rectangle
 * @param height - the height of the rectangle
**/
/////////////////////////////////////////////////////////////////////////////////////
void drawNumber8(SDL_Renderer *renderer, int x, int y, int width, int height);


#endif /* __CONVERSIONS_H__ */