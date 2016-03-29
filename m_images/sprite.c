// Copyright 2016 fauno

#include <stdio.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#ifndef __cplusplus
    typedef char bool;
    #define true 1;
    #define false 0;
#endif

// aliases
typedef SDL_Event s_event;
typedef SDL_Surface s_surface;
typedef SDL_Window s_window;
typedef SDL_Texture s_texture;

typedef struct
{
	char* path;
	bool is_allocated; // not sure if this make sense by now
	int x;
	int y;
	int w;
	int h;
	s_texture* ref;
} texture;

// declarations
bool load_media();
bool is_window_created();
int game_update();
s_surface * load_image(char* path);
int load_texture(texture* img, char* path);
int free_texture(texture* img);
int render_texture(texture* img, int x, int y);
int render_texture_with_clip(texture* img, int x, int y, SDL_Rect* clip);

// initializations
s_window* g_window = 0;
SDL_Renderer* g_render = 0;
// texture g_user_texture = { .path = "foo.png", .is_allocated = 0, .x = 0, .y = 0, .w = 0, .h = 0, .ref = 0 };
// texture g_bg_texture = { .path = "background.png", .is_allocated = 0, .x = 0, .y = 0, .w = 0, .h = 0, .ref = 0 };
SDL_Rect g_images[4];
texture g_spritesheet = { .path = "dots.png", .is_allocated = 0, .x = 0, .y = 0, .w = 0, .h = 0, .ref = 0 };
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]) {
	if ( is_window_created() ) {
		
		// load sdl2_image
		int image_flags = IMG_INIT_PNG;
		if ( !(IMG_Init(image_flags) & image_flags) ) {
			printf("sdl2_image err: %s\n", IMG_GetError() );
		}

		bool user_quit = false;
		s_event event;

		if ( !load_media() ) {
			user_quit = true;
		}
		
		// the LOOP
		while	 ( !user_quit ) {
			
			// getting events
			while ( SDL_PollEvent(&event) != 0 ) {
				
				// handling events
				if ( event.type == SDL_QUIT ) {
					user_quit = true;
				} else if (event.type == SDL_KEYDOWN) {
					printf("key!\n");
					switch (event.key.keysym.sym) {
						case SDLK_UP:
						break;

						case SDLK_DOWN:
						break;

						case SDLK_LEFT:
						break;

						case SDLK_RIGHT:
						break;

						default:
						break;
					}
				}	 // end handling events
			}
			game_update();
		}
	}
	
	// closing...
	// Deallocate textures
	free_texture(&g_spritesheet);
	// free_texture(&g_user_texture);
	// free_texture(&g_bg_texture);

	SDL_DestroyRenderer(g_render);
	SDL_DestroyWindow(g_window);
	g_window = 0;
	g_render = 0;

	IMG_Quit();
	SDL_Quit();
	return 0;
}

int render_texture_with_clip(texture* img, int x, int y, SDL_Rect* clip) {
	SDL_Rect renderQuad = { x, y, img->w, img->h };
	
	// cliping
	if ( clip ) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
		printf("w: %d, h: %d\n", clip->w, clip->h);
	}
	
  SDL_RenderCopy(g_render, img->ref, clip, &renderQuad);
	return 0;
}

int render_texture(texture* img, int x, int y) {
	SDL_Rect renderQuad = { x, y, img->w, img->h };	
  SDL_RenderCopy(g_render, img->ref, 0, &renderQuad);
	return 0;
}

int free_texture(texture* img) {
	
	if ( !img->ref ) {
		SDL_DestroyTexture(img->ref);
		img->ref = 0;
		img->w = 0;
		img->h = 0;
	}
	
	return 0;
}

bool load_media() {
	int success = true;

	if ( !load_texture(&g_spritesheet, g_spritesheet.path) ) {
		printf("Failed to load spritesheet texture image!\n");
		success = false;
	} else {
		//Set top left sprite
    g_images[ 0 ].x =   0;
    g_images[ 0 ].y =   0;
    g_images[ 0 ].w = 100;
    g_images[ 0 ].h = 100;

    //Set top right sprite
    g_images[ 1 ].x = 100;
    g_images[ 1 ].y =   0;
    g_images[ 1 ].w = 100;
    g_images[ 1 ].h = 100;

    //Set bottom left sprite
    g_images[ 2 ].x =   0;
    g_images[ 2 ].y = 100;
    g_images[ 2 ].w = 100;
    g_images[ 2 ].h = 100;

    //Set bottom right sprite
    g_images[ 3 ].x = 100;
    g_images[ 3 ].y = 100;
    g_images[ 3 ].w = 100;
    g_images[ 3 ].h = 100;
	}
	
	return success;
}

int load_texture(texture* img, char* path) {
	// The final texture
	s_texture* newTexture = 0;

	// Load image at specified path
	s_surface* loadedSurface = IMG_Load(path);
	if ( !loadedSurface ) {
		printf("Unable to load %s! Error: %s\n", path, IMG_GetError());
	} else {
		printf("color keying cyan\n");
		// color key cyan 0, 255, 255
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		
		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(g_render, loadedSurface);
		if ( !newTexture ) {
			printf("texture %s! Error: %s\n", path, SDL_GetError());
		} else {
			img->w = loadedSurface->w;
			img->h = loadedSurface->h;
			img->path = path;
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	
	img->ref = newTexture;
	return img->ref != 0;
}

bool is_window_created() {
	int success = true;

	// init
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("err %s\n", SDL_GetError());
		success = false;
	} else {
		
		// Set texture filtering to linear
		if ( !SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") ) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		g_window = SDL_CreateWindow(
			"sdl key",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		if ( !g_window ) {
			printf("err %s\n", SDL_GetError());
			success = false;
		} else {
			g_render = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

			if ( !g_render ) {
				printf("err render: %s\n", SDL_GetError());
				success = false;
			} else {
				
				// Initialize renderer color
				SDL_SetRenderDrawColor(g_render, 0xFF, 0xFF, 0xFF, 0xFF);
			}
		}
	}
	return success;
}

int game_update() {
	
	// remove last committed color 
	SDL_SetRenderDrawColor(g_render, 0xFF, 0xFF, 0xFF, 0xFF);
			
	// Clear screen
	SDL_RenderClear(g_render);

	render_texture_with_clip(&g_spritesheet, 0, 0, &g_images[0]);
	render_texture_with_clip(&g_spritesheet, SCREEN_WIDTH - g_images[1].w, 0, &g_images[1]);
	render_texture_with_clip(&g_spritesheet, 0, SCREEN_HEIGHT - g_images[2].h, &g_images[2]);
	render_texture_with_clip(&g_spritesheet, SCREEN_WIDTH - g_images[3].w, SCREEN_HEIGHT - g_images[3].h, &g_images[3]);
	// render_texture(&g_bg_texture, 0, 0);
	// render_texture(&g_user_texture, 240, 190);
	
	// Update screen
	SDL_RenderPresent(g_render);
	return 0;
}
