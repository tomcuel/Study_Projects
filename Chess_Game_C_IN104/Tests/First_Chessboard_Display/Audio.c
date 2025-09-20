#include "Audio.h"
    
    
void play_sound(const char* filename) {
	// local variables
	static Uint32 wav_length; // length of our sample
	static Uint8 *wav_buffer; // buffer containing our audio file
	static SDL_AudioSpec wav_spec; // the specs of our piece of music
	
	// Load the WAV
	// the specs, length and buffer of our wav are filled
    // check if the file is loaded
	if( SDL_LoadWAV(filename, &wav_spec, &wav_buffer, &wav_length) == NULL ){
        printf("Failed to load wav file: %s\n", SDL_GetError());
	    goto Quit;
	}
	
    // open audio device
    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0);
    // play audio
    int success = SDL_QueueAudio(deviceId, wav_buffer, wav_length);
    if (success != 0) {
        fprintf(stderr, "Failed to queue audio: %s\n", SDL_GetError());
        goto Quit;
    }
    SDL_PauseAudioDevice(deviceId, 0);
    // keep application running long enough to hear the sound
    
    // wait for sound to finish
    SDL_Delay(1000);

    // clean up
    SDL_CloseAudioDevice(deviceId);
Quit : 
    SDL_FreeWAV(wav_buffer);
}