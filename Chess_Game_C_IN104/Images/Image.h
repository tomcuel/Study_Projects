#ifndef __IMAGE_H__
#define __IMAGE_H__


#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>


////////////////////////////////////////////////////////////////
// Function to load a BMP image
/**
 * @param filename - the path to the image file
 * @return the SDL_Surface containing the image
**/
////////////////////////////////////////////////////////////////
SDL_Surface* loadBMP(const char* filename);


////////////////////////////////////////////////////////////////
// Function to apply a simple box blur to a texture
/**
 * @param texture - the texture to apply the blur to
 * @param renderer - the renderer to apply the blur with
 * @param width - the width of the texture
 * @param height - the height of the texture
**/
////////////////////////////////////////////////////////////////
void applyBlur(SDL_Texture* texture, SDL_Renderer* renderer, int width, int height);


////////////////////////////////////////////////////////////////
// Function to add an image to the renderer
/**
 * @param filename - the path to the image file
 * @param renderer - it's modified to include the image
 * @param destRect - the destination rectangle for the image
 * @param blur - a boolean to determine if the image should be blurred
**/
////////////////////////////////////////////////////////////////
void add_image_to_render (const char* filename, SDL_Renderer* renderer, SDL_Rect destRect, bool blur);


#endif /* __IMAGE_H__ */