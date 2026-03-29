#include <SDL_pixels.h>
#include <SDL_stdinc.h>
#include <SDL_surface.h>
#include <SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

int main() {
	SDL_Window *pwindow = SDL_CreateWindow("Image Viewer", // creates window struct returns point to it 
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					900,
					600,
					0);


	SDL_Surface *psurface = SDL_GetWindowSurface(pwindow); // from window struct returns p to surface area 

	Uint8 r,g,b;
	r = 0x00;
	g = b = 0;

	Uint32 colour = SDL_MapRGB(psurface->format,r,g,b); // the -> syntax is sugar for (*ptr).field
	
	SDL_FillRect(psurface, NULL, colour);


	
	SDL_Event e;
	int running = 1;

	while (running) {
		while (SDL_PollEvent(&e)) { // each loop see if event has occured
			if (e.type == SDL_QUIT) running = 0;
		}

		SDL_UpdateWindowSurface(pwindow);
	}
}

