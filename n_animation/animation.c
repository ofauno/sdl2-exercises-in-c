// Copyright 2016 fauno

#include <stdio.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#ifndef __cplusplus
    typedef char bool;
    #define true 1;
    #define false 0;
#endif

#define WALKING_FRAMES 4

// aliases
typedef SDL_Event s_event;
typedef SDL_Surface s_surface;
typedef SDL_Window s_window;
typedef SDL_Texture s_texture;
typedef SDL_Rect s_rect;

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
int process_events(s_event event);
bool init_render();

// texture api
int texture_load(texture* img, char* path);
int texture_free(texture* img);
int texture_render(texture* img, int x, int y);
int texture_render_with_clip(texture* img, int x, int y, s_rect* clip);
int texture_set_color(texture* img, Uint8 red, Uint8 green, Uint8 blue); // color modulation
// SDL_BlendModes: 
// SDL_BLENDMODE_NONE
// SDL_BLENDMODE_BLEND
// SDL_BLENDMODE_ADD
// SDL_BLENDMODE_MOD
int texture_set_blend_mode(texture* img, SDL_BlendMode blending);
int texture_set_alpha(texture* img, Uint8 alpha);

// initializations
s_window* g_window = 0;
SDL_Renderer* g_render = 0;
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

// walking animation
s_rect g_walking_frames[ WALKING_FRAMES ];
texture g_spritesheet = { .path = "foo.png", .is_allocated = 0, .x = 0, .y = 0, .w = 0, .h = 0, .ref = 0 };
int g_current_frame = 0;

// Modulation components
Uint8 r = 255;
Uint8 g = 255;
Uint8 b = 255;

bool user_quit = 0;
s_event event;

int main(int argc, char* args[]) {
	if ( is_window_created() ) {
		
		// load sdl2_image
		int image_flags = IMG_INIT_PNG;
		if ( !(IMG_Init(image_flags) & image_flags) ) {
			printf("sdl2_image err: %s\n", IMG_GetError() );
		}

		if ( !load_media() ) {
			user_quit = true;
		}
		
		// the LOOP
		while	 ( !user_quit ) {
			process_events(event);
			game_update();
		}
	}
	
	// closing...
	// Deallocate textures
	texture_free(&g_spritesheet);

	SDL_DestroyRenderer(g_render);
	SDL_DestroyWindow(g_window);
	g_window = 0;
	g_render = 0;

	IMG_Quit();
	SDL_Quit();
	return 0;
}

bool init_render() {
	bool success = true;
	// g_render = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
	// VSync allows the rendering to update at the same time 
	// as when your monitor updates during vertical refresh
	g_render = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if ( !g_render ) {
		printf("err render: %s\n", SDL_GetError());
		success = false;
	} else {
		
		// Initialize renderer color
		SDL_SetRenderDrawColor(g_render, 0xFF, 0xFF, 0xFF, 0xFF);
	}
	
	return success;
}

int process_events(s_event event) {
	// getting events
	while ( SDL_PollEvent(&event) != 0 ) {
		
		// handling events
		if ( event.type == SDL_QUIT ) {
			user_quit = true;
		} else if (event.type == SDL_KEYDOWN) {
			printf("key!\n");
			switch (event.key.keysym.sym) {
				case SDLK_q:
        b += 32;
				break;

        case SDLK_w:
        b -= 32;
        break;

				case SDLK_UP:
				r += 32;
				break;

				case SDLK_DOWN:
				r -= 32;
				break;

				case SDLK_LEFT:
				g += 32;
				break;

				case SDLK_RIGHT:
				g -= 32;
				break;

				default:
				break;
			}
		}	 // end handling events
	}
	
	return 0;
}

int texture_set_blend_mode(texture* img, SDL_BlendMode blending) {
	if (SDL_SetTextureBlendMode(img->ref, blending) < 0) {
		printf("blending err: %s\n", SDL_GetError());
	}
	return 0;
}

int texture_set_alpha(texture* img, Uint8 alpha) {
	if (SDL_SetTextureAlphaMod(img->ref, alpha) < 0) {
		printf("alpha err: %s\n", SDL_GetError());
	}
	return 0;
}

int texture_set_color(texture* img, Uint8 red, Uint8 green, Uint8 blue) {
	// http://wiki.libsdl.org/SDL_SetTextureColorMod
	if ( SDL_SetTextureColorMod(img->ref, red, green, blue) < 0 ) {
		printf("color modulation err: %s\n", SDL_GetError());
	}
	return 0;
}

int texture_render_with_clip(texture* img, int x, int y, s_rect* clip) {
	s_rect renderQuad = { x, y, img->w, img->h };
	
	// cliping
	if ( clip ) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
		// printf("w: %d, h: %d\n", clip->w, clip->h);
	}
	
  SDL_RenderCopy(g_render, img->ref, clip, &renderQuad);
	return 0;
}

int texture_render(texture* img, int x, int y) {
	s_rect renderQuad = { x, y, img->w, img->h };	
  SDL_RenderCopy(g_render, img->ref, 0, &renderQuad);
	return 0;
}

int texture_free(texture* img) {
	
	if ( !img->ref ) {
		SDL_DestroyTexture(img->ref);
		img->ref = 0;
		img->w = 0;
		img->h = 0;
	}
	
	return 0;
}

bool load_media() {
	bool success = true;

	if ( !texture_load(&g_spritesheet, g_spritesheet.path) ) {
		printf("Failed to load spritesheet texture image!\n");
		success = false;
	} else {
    g_walking_frames[ 0 ].x =   0;
    g_walking_frames[ 0 ].y =   0;
    g_walking_frames[ 0 ].w =  64;
    g_walking_frames[ 0 ].h = 205;

    g_walking_frames[ 1 ].x =  64;
    g_walking_frames[ 1 ].y =   0;
    g_walking_frames[ 1 ].w =  64;
    g_walking_frames[ 1 ].h = 205;

    g_walking_frames[ 2 ].x = 128;
    g_walking_frames[ 2 ].y =   0;
    g_walking_frames[ 2 ].w =  64;
    g_walking_frames[ 2 ].h = 205;

    g_walking_frames[ 3 ].x = 196;
    g_walking_frames[ 3 ].y = 	0;
    g_walking_frames[ 3 ].w =  64;
    g_walking_frames[ 3 ].h = 205;
	}
	
	return success;
}

int texture_load(texture* img, char* path) {
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
	bool success = true;

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
			success = init_render();
		}
	}
	return success;
}

int game_update() {
	
	// remove last committed color 
	SDL_SetRenderDrawColor(g_render, 0xFF, 0xFF, 0xFF, 0xFF);
			
	// Clear screen
	SDL_RenderClear(g_render);
	
	s_rect* _current_clip = &g_walking_frames[ g_current_frame / 4 ];

	// texture_set_color(&g_spritesheet, r, g, b);
	texture_render_with_clip(&g_spritesheet, 
													 (SCREEN_WIDTH - _current_clip->w) / 2, 
													 (SCREEN_HEIGHT - _current_clip->h) / 2, 
													 _current_clip);
													
	++g_current_frame;
	
	if (g_current_frame / 4 >= WALKING_FRAMES) {
		g_current_frame = 0;
	}
	
	// Update screen
	SDL_RenderPresent(g_render);
	return 0;
}
