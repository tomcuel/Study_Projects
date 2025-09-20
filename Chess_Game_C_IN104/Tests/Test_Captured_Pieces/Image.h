#ifndef __IMAGE_H__
#define __IMAGE_H__


#include <SDL2/SDL.h>


////////////////////////////////////////////////////////////////
// Function to load a BMP image
/**
 * @param filename - the path to the image file
 * @return the SDL_Surface containing the image
**/
////////////////////////////////////////////////////////////////
SDL_Surface* loadBMP(const char* filename);


////////////////////////////////////////////////////////////////
// Function to add an image to the renderer
/**
 * @param filename - the path to the image file
 * @param renderer - it's modified to include the image
 * @param destRect - the destination rectangle for the image
**/
////////////////////////////////////////////////////////////////
void add_image_to_render (const char* filename, SDL_Renderer* renderer, SDL_Rect destRect);


#endif /* __IMAGE_H__ */