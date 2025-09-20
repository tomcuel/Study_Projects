#ifndef __AUDIO_H__
#define __AUDIO_H__


#include <SDL2/SDL.h>
#include "Constants.h"
#include <stdio.h>
#include <stdlib.h>


/////////////////////////////////////////////////////////////////////////////////////
// Audio Summary :
/**
 * play_sound - play a sound
 * 
 * The audio will be used to play a sound when a piece is taken, when a piece is moved, when the game is won, or when the game is lost
 * It will be useful to give a better experience to the player, and to make the game more enjoyable
 **/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Play a sound
/**
 * @param filename - the name of the file to play
 **/
/////////////////////////////////////////////////////////////////////////////////////
void play_sound(const char* filename);


#endif /* __AUDIO_H__ */