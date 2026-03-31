#include <SDL_pixels.h>
#include <SDL_stdinc.h>
#include <SDL_surface.h>
#include <SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
//
// TODO: currently does not support comments hahaha

int main() {
	FILE* fp = stdin;

	char* bin = malloc(256);
	if (fgets(bin, 256, fp) == NULL) {
		printf("failed to read data format");
		return 0;
	}

	char* resolution = malloc(256);
	if (fgets(resolution, 256, fp) == NULL) {
		fprintf(stderr, "failed to read resolution");
		return 0;
	}

	if (fgets(bin, 256, fp) == NULL) { 
		printf("failed to read data format");
		return 0;
	}

	// header read in
	int width, height;
	if (sscanf(resolution, "%d %d\n", &width, &height) != 2) { // parse resolution values
		printf("failed to read data format");
		return 0;
	}
	
	Uint8* blob = malloc(width * height * 3); // extrapolate binary blob size
	fread(blob, 3, width * height, fp); // read in the bin blob

	SDL_Window *pwindow = SDL_CreateWindow("Image Viewer", // creates window struct returns point to it 
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					height,
					width,
					0);  // no flags needed

	SDL_Surface *psurface = SDL_GetWindowSurface(pwindow); // from window struct returns p to surface area 
	SDL_Rect pixel = (SDL_Rect){0,0,1,1}; // compound literal and casting it to rect type

	Uint8 r,g,b;
	Uint32 colour; 
	int i = 0; // index of blob

	for (int x = 0; x < height; x++) {
		for (int y = 0; y < width; y++) { // each pixel has rgb value therfore offset should be 3
			r = blob[i];
			g = blob[i+1];
			b = blob[i+2];

			colour = SDL_MapRGB(psurface->format,r,g,b); 

			pixel.x = x; // updates x,y each pixel
			pixel.y = y;

			SDL_FillRect(psurface, &pixel, colour); 
			i += 3;
		}
	}


	SDL_UpdateWindowSurface(pwindow);

	SDL_Event e;
	int running = 1;
	while (running) {
		while (SDL_PollEvent(&e)) { // each loop see if event has occured
			if (e.type == SDL_QUIT) running = 0;
		}

	}
}
