#include <SDL_pixels.h>
#include <SDL_stdinc.h>
#include <SDL_surface.h>
#include <SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

int main() {
	FILE* fp = stdin;

	/* read in header values, ignoring comment lines */
	char** header = malloc(sizeof(char*)*3);
	int lc = 0;

	while (lc < 3) { 
		char* buff = malloc(256);

		if (fgets(buff, 256, fp) == NULL) {
			switch (lc) {
				case 0:
					printf("failed to read format\n");
				case 1: 
					printf("failed to read resolution\n");
				case 2: 
					printf("failed to read colours\n");
			}
			return 0;
		}

		if (buff[0] != '#') { // skip comment lines, freeing temp buffer
			header[lc++] = buff; 
		} else {
			free(buff);
		}
	}

	/* extrapolate width and height dimension*/
	int width, height;
	if (sscanf(header[1], "%d %d\n", &width, &height) != 2) { 
		printf("failed to read data format\n");
		return 0;
	}
	
	/* allocate space for binary blob and read in */
	Uint8* blob = malloc(width * height * 3); 
	if (fread(blob, 3, width * height, fp) < width * height) { 
		printf("binary read failed\n");
	}

	/* create window struct */
	SDL_Window *pwindow = SDL_CreateWindow("Image Viewer", 
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					width,
					height,
					0);  // no flags needed

	SDL_Surface *psurface = SDL_GetWindowSurface(pwindow); 
	
	/* render */
	SDL_Rect pixel = (SDL_Rect){0,0,1,1}; // compound literal and casting it to rect type
	Uint8 r,g,b;
	Uint32 colour; 

	int i = 0; // index in blob

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) { 
			colour = SDL_MapRGB(psurface->format,
		       				blob[i], // r
						blob[i+1], // g
		       				blob[i+2]); // b

			pixel.x = x; pixel.y = y;

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
