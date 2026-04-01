#include <SDL_pixels.h>
#include <SDL_stdinc.h>
#include <SDL_surface.h>
#include <SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
// TODO: currently does not support comments hahaha

int main() {
	FILE* fp = stdin;

	char** header = malloc(sizeof(char*)*3);
	int lc = 0;

	while (lc < 3) { // this section reads in the header ignoring comment lines
		char* buff = malloc(256);

		if (fgets(buff, 256, fp) == NULL) {
			switch (lc) {
				case 0:
					printf("failed to read format");
				case 1: 
					printf("failed to read resolution");
				case 2: 
					printf("failed to read colours");
			}
			return 0;
		}

		if (buff[0] != '#') {
			header[lc++] = buff; // if its not a commented line then add it to header
		} else {
			free(buff);
		}
	}
	
	for (int i = 0; i < 3; i++) {
		printf("%s\n", header[i]);
	}

	// read in width and height of photo
	int width, height;
	if (sscanf(header[1], "%d %d\n", &width, &height) != 2) { // parse resolution values
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

	int i = 0; // index in blob

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) { 
			colour = SDL_MapRGB(psurface->format,
		       				blob[i+2], // rgb
						blob[i+2],
		       				blob[i+2]); 

			pixel.x = x; // updates x,y each pixel
			pixel.y = y;
			SDL_FillRect(psurface, &pixel, colour); 
			i += 3;
		}
	}

	SDL_UpdateWindowSurface(pwindow);

	// MacOS requires program to poll the UI loop to stay visible
	SDL_Event e;
	int running = 1;
	while (running) {
		while (SDL_PollEvent(&e)) { 
			if (e.type == SDL_QUIT) running = 0;
		}
	}
}
