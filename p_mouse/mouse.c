// Copyright 2016 fauno

#include <stdio.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
// #include <SDL2/SDL_ttf.h>

#ifndef __cplusplus
    typedef char bool;
    #define true 1;
    #define false 0;
#endif

#define WALKING_FRAMES 4
#define TOTAL_BUTTONS 4

// aliases
typedef SDL_Event 	s_event;
typedef SDL_Surface s_surface;
typedef SDL_Window 	s_window;
typedef SDL_Texture s_texture;
typedef SDL_Rect 		s_rect;
typedef SDL_Point 	s_point;

enum
ButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};

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

typedef struct {
	s_point position;
	enum ButtonSprite current_sprite;
} btn;

// declarations
bool 
load_media();

bool 
is_window_created();

int 
game_update();

s_surface* 
load_image(char* path);

int 
process_events(s_event* event);

bool 
init_render();

// texture api
int 
texture_load(texture* img, char* path);

int 
texture_free(texture* img);

int 
texture_render(texture* img, int x, int y);

int 
texture_render_with_clip(texture* img, int x, int y, s_rect* clip);

int 
texture_render_with_clip_and_rotation(
	texture* img, int x, int y, s_rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);

int 
texture_set_color(texture* img, Uint8 red, Uint8 green, Uint8 blue); // color modulation

int // BlendModes { SDL_BLENDMODE_NONE, SDL_BLENDMODE_BLEND, SDL_BLENDMODE_ADD, SDL_BLENDMODE_MOD }
texture_set_blend_mode(texture* img, SDL_BlendMode blending);

int 
texture_set_alpha(texture* img, Uint8 alpha);

#ifdef _SDL_TTF_H
bool 
texture_load_font_string(texture* img, char* text, SDL_Color text_color);
#endif


// button api
int
btn_init(btn* btn);

int
btn_set_position(btn* btn, int x, int y);

int
btn_handle_event(btn* btn, s_event* event);

int
btn_render(btn* btn);

// initializations
s_window* 
g_window = 0;

SDL_Renderer* 
g_render = 0;

// screen
int 
SCREEN_WIDTH = 640;

int 
SCREEN_HEIGHT = 480;

// font
// TTF_Font* 
// g_font = 0;

// texture 
// g_text_texture = { .path = "foo.png", .is_allocated = 0, .x = 0, .y = 0, .w = 0, .h = 0, .ref = 0 };

// user
bool 
user_quit = 0;

// event
s_event 
g_event = { 0 };

// buttons
int 
BUTTON_WIDTH = 300;

int 
BUTTON_HEIGHT = 200;


//Mouse button sprites
s_rect
g_spriteclips[ BUTTON_SPRITE_TOTAL ];

texture g_spritesheet = { .path = "button.png", .is_allocated = 0, .x = 0, .y = 0, .w = 0, .h = 0, .ref = 0 };

//Buttons objects
btn 
g_buttons[ TOTAL_BUTTONS ];

bool 
init_render() {
	
	bool success = true;
	// g_render = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
	// VSync allows the rendering to update at the same time 
	// as when your monitor updates during vertical refresh
	g_render = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if ( !g_render ) {
		printf("init_render: err render: %s\n", SDL_GetError());
		success = false;
	} else {
		
		// Initialize renderer color
		SDL_SetRenderDrawColor(g_render, 0xFF, 0xFF, 0xFF, 0xFF);
	}
	
	return success;
}

int 
texture_set_blend_mode(texture* img, SDL_BlendMode blending) {
	
	if (SDL_SetTextureBlendMode(img->ref, blending) < 0) {
		printf("texture_set_blend_mode: blending err: %s\n", SDL_GetError());
	}
	
	return 0;
}

int 
texture_set_alpha(texture* img, Uint8 alpha) {
	
	if (SDL_SetTextureAlphaMod(img->ref, alpha) < 0) {
		printf("texture_set_alpha: alpha err: %s\n", SDL_GetError());
	}
	
	return 0;
}

int 
texture_set_color(texture* img, Uint8 red, Uint8 green, Uint8 blue) {
	
	// http://wiki.libsdl.org/SDL_SetTextureColorMod
	if ( SDL_SetTextureColorMod(img->ref, red, green, blue) < 0 ) {
		printf("texture_set_color: color modulation err: %s\n", SDL_GetError());
	}
	
	return 0;
}

int 
texture_render_with_clip_and_rotation(
	texture* img, int x, int y, s_rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
																						
	s_rect renderQuad = { x, y, img->w, img->h };
	
	// cliping
	if ( clip ) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
		// printf("w: %d, h: %d\n", clip->w, clip->h);
	}
	
	if ( SDL_RenderCopyEx(g_render, img->ref, clip, &renderQuad, angle, center, flip) < 0 ) {
		printf("texture_render_with_clip_and_rotation: render err: %s\n", SDL_GetError());
	}
	
	return 0;
}

int 
texture_render_with_clip(texture* img, int x, int y, s_rect* clip) {
	
	s_rect renderQuad = { x, y, img->w, img->h };
	
	// cliping
	if ( clip ) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
		// printf("w: %d, h: %d\n", clip->w, clip->h);
	}
	
  if ( SDL_RenderCopy(g_render, img->ref, clip, &renderQuad) < 0 ) {
		printf("texture_render_with_clip: render err: %s\n", SDL_GetError());
	}
	
	return 0;
}

int 
texture_render(texture* img, int x, int y) {
	
	s_rect renderQuad = { x, y, img->w, img->h };	
	
  if ( SDL_RenderCopy(g_render, img->ref, 0, &renderQuad) < 0 ) {
		printf("texture_render: render err: %s\n", SDL_GetError());
	}
	
	return 0;
}

int 
texture_free(texture* img) {
	
	if ( !img->ref ) {
		SDL_DestroyTexture(img->ref);
		img->ref = 0;
		img->w = 0;
		img->h = 0;
	}
	
	return 0;
}

bool 
load_media() {
	
	bool success = true;
	
	// https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf_14.html
	// g_font = TTF_OpenFont("lazy.ttf", 28);
	// 	
	// 	if ( !g_font ) {
	// 		printf("load_media: failed to load font, err: %s\n", TTF_GetError());
	// 		success = false;
	// 	} else {
	// 		
	// 		// render text
	// 		SDL_Color text_color = { 0, 0, 0, 0 };
	// 		
	// 		if ( !texture_load_font_string(&g_text_texture, "jamon", text_color) ) {
	// 			printf("load_media: failed to render texture\n");
	// 			success = false;
	// 		}
	// 		
	// 	}
	
	if ( !texture_load(&g_spritesheet, "button.png") )
	{
		printf("load_media: failed to load\n");
		success = false;
	}
	else
	{
		// set sprites buttons
		for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i) {
			g_spriteclips[ i ].x = 0;
			g_spriteclips[ i ].y = i * 200;
			g_spriteclips[ i ].w = BUTTON_WIDTH;
			g_spriteclips[ i ].h = BUTTON_HEIGHT;
		}
		
		// set buttons position
		btn_set_position(&g_buttons[ 0 ], 0 , 0);
		btn_set_position(&g_buttons[ 1 ], SCREEN_WIDTH - BUTTON_WIDTH, 0);
		btn_set_position(&g_buttons[ 2 ], 0, SCREEN_HEIGHT - BUTTON_HEIGHT);
		btn_set_position(&g_buttons[ 3 ], SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT);
	}
	
	return success;
}

int 
texture_load(texture* img, char* path) {
	
	// The final texture
	s_texture* newTexture = 0;

	// Load image at specified path
	s_surface* loadedSurface = IMG_Load(path);
	
	if ( !loadedSurface ) {
		printf("texture_load: Unable to load %s! Error: %s\n", path, IMG_GetError());
	} else {
		printf("texture_load: color keying cyan\n");
		// color key cyan 0, 255, 255
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		
		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(g_render, loadedSurface);
		
		if ( !newTexture ) {
			printf("texture_load: texture %s! Error: %s\n", path, SDL_GetError());
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

bool 
is_window_created() {
	
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("is_window_created: err %s\n", SDL_GetError());
		success = false;
	} else {
		
		// Set texture filtering to linear
		if ( !SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") ) {
			printf("is_window_created: Warning: Linear texture filtering not enabled!");
		}

		g_window = SDL_CreateWindow(
			"sdl mouse",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		if ( !g_window ) {
			printf("is_window_created: err %s\n", SDL_GetError());
			success = false;
		} else {
			success = init_render();
		}
		
	} /* end init */
	
	return success;
}

#ifdef _SDL_TTF_H
bool 
texture_load_font_string(texture* img, char* text, SDL_Color text_color) {
	
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
#endif

int
btn_init(btn* btn) {
	btn->position.x = 0;
	btn->position.y = 0;
	btn->current_sprite = BUTTON_SPRITE_MOUSE_OUT;
	
	return 0;
}

int
btn_set_position(btn* btn, int x, int y) {
	btn->position.x = x;
	btn->position.y = y;
	
	return 0;
}

int
btn_handle_event(btn* btn, s_event* event) {
		
	if ( event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP ) {
		// get mouse position
		int x = 0;
		int y = 0;
		
		// http://wiki.libsdl.org/SDL_GetMouseState
		SDL_GetMouseState(&x, &y);
		
		bool is_inside_btn = true;
		
		if( x < btn->position.x ) 
		{
			is_inside_btn = false; // on left
		} 
		else if ( x > btn->position.x + BUTTON_WIDTH ) 
		{
			is_inside_btn = false; // on right
		}
		else if( y < btn->position.y )
		{
			is_inside_btn = false; // above
		}
		else if( y > btn->position.y + BUTTON_HEIGHT )
		{
			is_inside_btn = false; // below
		}
		
		if( !is_inside_btn )
		{
			btn->current_sprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		else
		{
			switch(event->type)
			{
				case SDL_MOUSEMOTION:
				btn->current_sprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;
				
				case SDL_MOUSEBUTTONDOWN:
				btn->current_sprite = BUTTON_SPRITE_MOUSE_DOWN;
				break;
				
				case SDL_MOUSEBUTTONUP:
				btn->current_sprite = BUTTON_SPRITE_MOUSE_UP;
				break;
			}
		}
		
	}
	return 0;
}

int
btn_render(btn* btn) {
	texture_render_with_clip(&g_spritesheet, btn->position.x, btn->position.y, &g_spriteclips[ btn->current_sprite ]);
	
	return 0;
}

int 
main(int argc, char* args[]) {
	
	if ( is_window_created() ) {
		
		// for "libpng warning: iCCP: known incorrect sRGB profile"	
		// http://stackoverflow.com/questions/22745076/libpng-warning-iccp-known-incorrect-srgb-profile
		// load sdl2_image
		int image_flags = IMG_INIT_PNG;
		
		if ( !(IMG_Init(image_flags) & image_flags) ) {
			printf("main: sdl2_image err: %s\n", IMG_GetError());
			return 1;
		}
		
		// load sdl ttf: https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf_8.html
		// if ( TTF_Init() == -1 ) {
		// 			printf("sdl2_ttf err: %s\n", TTF_GetError());
		// 			return 1;
		// 		}

		if ( !load_media() ) {
			user_quit = true;
		}
		
		// the LOOP
		while	 ( !user_quit ) {
			process_events(&g_event);
			game_update();
		}
	}
	
	// closing...
	// Deallocate textures
	texture_free(&g_spritesheet);
	
	// free g_font: https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf_18.html
	// TTF_CloseFont(g_font);
	// g_font = 0;

	SDL_DestroyRenderer(g_render);
	SDL_DestroyWindow(g_window);
	g_window = 0;
	g_render = 0;

	// https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf_10.html
	// TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
}

int game_update() {
	
	// remove last committed color 
	SDL_SetRenderDrawColor(g_render, 0xFF, 0xFF, 0xFF, 0xFF);
	// Clear screen
	SDL_RenderClear(g_render);
	
	// render buttons
	for (int i = 0; i < TOTAL_BUTTONS; ++i) {
		btn_render(&g_buttons[ i ]);
	}
		
	// Update screen
	SDL_RenderPresent(g_render);
	return 0;
}

int 
process_events(s_event* event) {
	
	// getting events
	while ( SDL_PollEvent(event) != 0 ) {
		
		// handling events
		if ( event->type == SDL_QUIT ) {
			user_quit = true;
		}
		
		for (int i = 0; i < TOTAL_BUTTONS; ++i) {
			btn_handle_event(&g_buttons[ i ], event);
		}
		
	}
	
	return 0;
}
