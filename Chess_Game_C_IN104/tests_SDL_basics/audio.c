#include <SDL2/SDL.h>

#define FILENAME "take.wav"

int main(int argc, char* argv[]){

	// Initialize SDL.
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
			goto cleanup;

	// local variables
	static Uint32 wav_length; // length of our sample
	static Uint8 *wav_buffer; // buffer containing our audio file
	static SDL_AudioSpec wav_spec; // the specs of our piece of music
	
	/* Load the WAV */
	// the specs, length and buffer of our wav are filled
	if( SDL_LoadWAV(FILENAME, &wav_spec, &wav_buffer, &wav_length) == NULL ){
        printf("Failed to load wav file: %s\n", SDL_GetError());
        SDL_FreeWAV(wav_buffer);
	    goto cleanup;
	}
	
    // open audio device
    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0);
    // play audio
    int success = SDL_QueueAudio(deviceId, wav_buffer, wav_length);
    if (success != 0) {
        fprintf(stderr, "Failed to queue audio: %s\n", SDL_GetError());
        SDL_FreeWAV(wav_buffer);
        goto cleanup;
    }
    SDL_PauseAudioDevice(deviceId, 0);
    // keep application running long enough to hear the sound
    
    SDL_Delay(300);
    // clean up
    
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wav_buffer);

cleanup:
    SDL_Quit();
    return EXIT_SUCCESS;
}