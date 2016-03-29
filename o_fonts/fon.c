// Copyright 2016 fauno

#include <stdio.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <SDL2/SDL_ttf.h>

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
s_surface* load_image(char* path);
int process_events(s_event event);
bool init_render();

// texture api
int texture_load(texture* img, char* path);
int texture_free(texture* img);
int texture_render(texture* img, int x, int y);
int texture_render_with_clip(texture* img, int x, int y, s_rect* clip);
int texture_render_with_clip_and_rotation(texture* img, int x, int y, s_rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);
int texture_set_color(texture* img, Uint8 red, Uint8 green, Uint8 blue); // color modulation
// BlendModes { SDL_BLENDMODE_NONE, SDL_BLENDMODE_BLEND, SDL_BLENDMODE_ADD, SDL_BLENDMODE_MOD }
int texture_set_blend_mode(texture* img, SDL_BlendMode blending);
int texture_set_alpha(texture* img, Uint8 alpha);
bool texture_load_font_string(texture* img, char* text, SDL_Color text_color);

// initializations
s_window* g_window = 0;
SDL_Renderer* g_render = 0;
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

TTF_Font* g_font = 0;

// walking animation
// s_rect g_walking_frames[ WALKING_FRAMES ];
texture g_text_texture = { .path = "foo.png", .is_allocated = 0, .x = 0, .y = 0, .w = 0, .h = 0, .ref = 0 };
// int g_current_frame = 0;

// Modulation components
// Uint8 r = 255;
// Uint8 g = 255;
// Uint8 b = 255;

bool user_quit = 0;
s_event event = { 0 };

// Angle of rotation
// double g_degrees = 0;

// Flip type
// SDL_RendererFlip g_flipType = SDL_FLIP_NONE;

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
				// case SDLK_q:
				//         g_flipType = SDL_FLIP_HORIZONTAL;
				// 				break;
				// 
				//         case SDLK_w:
				//         g_flipType = SDL_FLIP_NONE;
				//         break;
				// 
				// 				case SDLK_e:
				//         g_flipType = SDL_FLIP_VERTICAL;
				//         break;

				// case SDLK_UP:
				// 				r += 32;
				// 				break;
				// 
				// 				case SDLK_DOWN:
				// 				r -= 32;
				// 				break;

				// case SDLK_LEFT:
				// 				g_degrees -= 60;
				// 				break;
				// 
				// 				case SDLK_RIGHT:
				// 				g_degrees += 60;				
				// 				break;

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

int texture_render_with_clip_and_rotation(texture* img, 
																					int x, 
																					int y, 
																					s_rect* clip, 
																					double angle, 
																					SDL_Point* center, 
																					SDL_RendererFlip flip) {
																						
	s_rect renderQuad = { x, y, img->w, img->h };
	
	// cliping
	if ( clip ) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
		// printf("w: %d, h: %d\n", clip->w, clip->h);
	}
	
	if ( SDL_RenderCopyEx(g_render, img->ref, clip, &renderQuad, angle, center, flip) < 0 ) {
		printf("render err: %s\n", SDL_GetError());
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
	
  if ( SDL_RenderCopy(g_render, img->ref, clip, &renderQuad) < 0 ) {
		printf("render err: %s\n", SDL_GetError());
	}
	return 0;
}

int texture_render(texture* img, int x, int y) {
	
	s_rect renderQuad = { x, y, img->w, img->h };	
	
  if ( SDL_RenderCopy(g_render, img->ref, 0, &renderQuad) < 0 ) {
		printf("render err: %s\n", SDL_GetError());
	}
	
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
	
	// https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf_14.html
	g_font = TTF_OpenFont("lazy.ttf", 28);
	
	if ( !g_font ) {
		printf("load_media: failed to load font, err: %s\n", TTF_GetError());
		success = false;
	} else {
		
		// render text
		SDL_Color text_color = { 0, 0, 0, 0 };
		
		if ( !texture_load_font_string(&g_text_texture, "jamon", text_color) ) {
			printf("load_media: failed to render texture\n");
			success = false;
		}
	}
	
	// if ( !texture_load(&g_spritesheet, g_spritesheet.path) ) {
	// 		printf("load_media: Failed to load spritesheet texture image!\n");
	// 		success = false;
	// 	} else {
	// 		
	// 	}
	
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
		
	} /* end init */
	
	return success;
}

bool texture_load_font_string(texture* img, char* text, SDL_Color text_color) {
	
	// rm preexisting texture
	texture_free(img);
	
	// https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf_43.html
	s_surface* text_surface = TTF_RenderText_Solid(g_font, text, text_color);
	
	if ( !text_surface ) {
		printf("texture_load_font_string: unable to render text, ttf err: %s\n", TTF_GetError());
	} else {
		
		// create texture
		img->ref = SDL_CreateTextureFromSurface(g_render, text_surface);
		
		if ( !img->ref ) {
			printf("texture_load_font_string: unable to create text texture, err: %s\n", SDL_GetError());
		} else {
			
			// get image dimensions
			img->w = text_surface->w;
			img->h = text_surface->h;
		}
		
		// flush surface
		SDL_FreeSurface(text_surface);
	}
	
	return img->ref != 0;
}

int main(int argc, char* args[]) {
	
	if ( is_window_created() ) {
		
		// load sdl2_image
		int image_flags = IMG_INIT_PNG;
		
		if ( !(IMG_Init(image_flags) & image_flags) ) {
			printf("sdl2_image err: %s\n", IMG_GetError());
			return 1;
		}
		
		// load sdl ttf: https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf_8.html
		if ( TTF_Init() == -1 ) {
			printf("sdl2_ttf err: %s\n", TTF_GetError());
			return 1;
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
	texture_free(&g_text_texture);
	
	// free g_font: https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf_18.html
	TTF_CloseFont(g_font);
	g_font = 0;

	SDL_DestroyRenderer(g_render);
	SDL_DestroyWindow(g_window);
	g_window = 0;
	g_render = 0;

	// https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf_10.html
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
}

int game_update() {
	
	// remove last committed color 
	SDL_SetRenderDrawColor(g_render, 0xFF, 0xFF, 0xFF, 0xFF);
	// Clear screen
	SDL_RenderClear(g_render);
	
	// texture_render_with_clip_and_rotation(
	// 		&g_spritesheet,
	// 		( SCREEN_WIDTH - g_spritesheet.w ) / 2,
	// 		( SCREEN_HEIGHT - g_spritesheet.h ) / 2,
	// 		0, 
	// 		g_degrees, 
	// 		0, 
	// 		g_flipType);
	
	texture_render(
		&g_text_texture,
		( SCREEN_WIDTH - g_text_texture.w ) / 2,
		( SCREEN_HEIGHT - g_text_texture.h ) / 2 );
		
	// Update screen
	SDL_RenderPresent(g_render);
	return 0;
}
