#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

int main() {
	printf("Hello world");

	SDL_Window *pwindow = SDL_CreateWindow("Image Viewer",
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					900,
					600,
					0);

	SDL_Event e;
	int running = 1;

	while (running) {
	    while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) running = 0;
	    }
	    // render here
	}
}

