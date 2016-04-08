// Copyright 2016 fauno

#include <stdio.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#ifndef __cplusplus
    typedef char bool;
    #define true 1;
    #define false 0;
#endif

/** constants **/
#define JOYSTICK_DEAD_ZONE 8000
#define WALKING_FRAMES 4
#define TOTAL_BUTTONS 4

// aliases
typedef SDL_Event 	s_event;
typedef SDL_Surface s_surface;
typedef SDL_Window 	s_window;
typedef SDL_Texture s_texture;
typedef SDL_Rect 		s_rect;
typedef SDL_Point 	s_point;
typedef Mix_Chunk		audio_sample;

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

/** declarations **/
bool load_media();
bool is_window_created();
int game_update();
s_surface* load_image(char* path);
int process_events(s_event* event);
bool init_render();

// texture api
int texture_load(texture* img, char* path);
int texture_free(texture* img);
int texture_render(texture* img, int x, int y);
int texture_render_with_clip(texture* img, int x, int y, s_rect* clip);
int texture_render_with_clip_and_rotation(
	texture* img, int x, int y, s_rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);
int texture_set_color(texture* img, Uint8 red, Uint8 green, Uint8 blue); // color modulation

// BlendModes { SDL_BLENDMODE_NONE, SDL_BLENDMODE_BLEND, SDL_BLENDMODE_ADD, SDL_BLENDMODE_MOD }
int texture_set_blend_mode(texture* img, SDL_BlendMode blending);
int texture_set_alpha(texture* img, Uint8 alpha);

#ifdef _SDL_TTF_H
bool texture_load_font_string(texture* img, char* text, SDL_Color text_color);
#endif

// button api
int btn_init(btn* btn);
int btn_set_position(btn* btn, int x, int y);
int btn_handle_event(btn* btn, s_event* event);
int btn_render(btn* btn);

/* initializations */

// FONTS
TTF_Font* g_font = 0;
texture 	g_prompt_texture = { .is_allocated = 0, 0 };
texture 	g_timer_texture = { .is_allocated = 0, 0 };

// AUDIO
// Mix_Music* g_music = 0;

// sfx
// audio_sample* g_scratch = 0;
// audio_sample*	g_hig = 0;
// audio_sample*	g_med = 0;
// audio_sample*	g_low = 0;	


s_window* 		g_window = 0;
SDL_Renderer* g_render = 0;

// screen
int SCREEN_WIDTH 	= 640;
int SCREEN_HEIGHT = 480;

// user
bool user_quit = 0;

// event
s_event 	g_event = { 0 };
SDL_Color g_text_color = { 0, 0, 0, 255 };
Uint32 		g_start_time = 0;
char	 		g_timer_text[20];

// buttons
int BUTTON_WIDTH 	= 300;
int BUTTON_HEIGHT = 200;

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
	if ( clip ) 
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
		// printf("w: %d, h: %d\n", clip->w, clip->h);
	}
	
	if ( SDL_RenderCopyEx(g_render, img->ref, clip, &renderQuad, angle, center, flip) < 0 ) 
	{
		printf("texture_render_with_clip_and_rotation: render err: %s\n", SDL_GetError());
	}
	
	return 0;
}

int 
texture_render_with_clip(texture* img, int x, int y, s_rect* clip) {
	
	s_rect renderQuad = { x, y, img->w, img->h };
	
	// cliping
	if ( clip ) 
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
		// printf("w: %d, h: %d\n", clip->w, clip->h);
	}
	
  if ( SDL_RenderCopy(g_render, img->ref, clip, &renderQuad) < 0 ) 
	{
		printf("texture_render_with_clip: render err: %s\n", SDL_GetError());
	}
	
	return 0;
}

int 
texture_render(texture* img, int x, int y) {
	
	s_rect renderQuad = { x, y, img->w, img->h };	
	
  if ( SDL_RenderCopy(g_render, img->ref, 0, &renderQuad) < 0 ) 
	{
		printf("texture_render: render err: %s\n", SDL_GetError());
	}
	
	return 0;
}

int 
texture_free(texture* img) {
	
	if ( img->ref != 0 ) 
	{
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
	
	g_font = TTF_OpenFont("lazy.ttf", 28);
	
	if ( !g_font )
	{
		printf("load_media: failed to load\n");
		success = false;
	}
	else
	{
		// Set text color as black
    SDL_Color text__color = { 0, 0, 0, 255 };
		if ( !texture_load_font_string(&g_prompt_texture, "ENTER to restart the timer", text__color))
		{
			printf( "load_media: Unable to render prompt texture!\n" );
			success = false;
		}
	}
	
	// if ( !texture_load(&g_current_texture, g_current_texture.path) )
	// 	{
	// 		printf("load_media: failed to load\n");
	// 		success = false;
	// 	}

  //Load music
	// http://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_55.html
  // g_music = Mix_LoadMUS( "beat.wav" );
  //   if( !g_music )
  //   {
  //       printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
  //       success = false;
  //   }
  // 
  //   // sfx
  // 	// http://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_19.html
  //   g_scratch = Mix_LoadWAV( "scratch.wav" );
  //   if( !g_scratch )
  //   {
  //       printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
  //       success = false;
  //   }
  // 
  //   g_hig = Mix_LoadWAV( "high.wav" );
  //   if( !g_hig )
  //   {
  //       printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
  //       success = false;
  //   }
  // 
  //   g_med = Mix_LoadWAV( "medium.wav" );
  //   if( !g_med )
  //   {
  //       printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
  //       success = false;
  //   }
  // 
  //   g_low = Mix_LoadWAV( "low.wav" );
  //   if( !g_low )
  //   {
  //       printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
  //       success = false;
  //   }

	return success;
}

int 
texture_load(texture* img, char* path) {
	
	// The final texture
	s_texture* newTexture = 0;

	// Load image at specified path
	s_surface* loadedSurface = IMG_Load(path);
	
	if ( !loadedSurface ) 
	{
		printf("texture_load: Unable to load %s! Error: %s\n", path, IMG_GetError());
	} 
	else 
	{
		printf("texture_load: color keying cyan\n");
		// color key cyan 0, 255, 255
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		
		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(g_render, loadedSurface);
		
		if ( !newTexture ) 
		{
			printf("texture_load: texture %s! Error: %s\n", path, SDL_GetError());
		} 
		else 
		{
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

	// if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	// if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK ) < 0 ) 
	if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 ) 
	{
		printf("is_window_created: err %s\n", SDL_GetError());
		success = false;
	} 
	else 
	{
		
		// Set texture filtering to linear
		if ( !SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") ) {
			printf("is_window_created: Warning: Linear texture filtering not enabled!");
		}

		// http://wiki.libsdl.org/SDL_NumJoysticks
		// if ( SDL_NumJoysticks() < 1 ) 
		// 		{
		// 			printf("is_window_created: no joystick connected\n");	
		// 		}
		// 		else // load joystick 
		// 		{
		// 			// http://wiki.libsdl.org/SDL_JoystickOpen
		// 			g_gamepad = SDL_JoystickOpen(0);
		// 			
		// 			if ( !g_gamepad )
		// 			{
		// 				printf("is_window_created: joystick err: %s\n", SDL_GetError());	
		// 			}
		// 			else
		// 			{
		// 				printf("Opened Joystick 0\n");
		// 				printf("Name: %s\n", SDL_JoystickNameForIndex(0));
		// 				printf("Number of Axes: %d\n", SDL_JoystickNumAxes(g_gamepad));
		// 				printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(g_gamepad));
		// 				printf("Number of Balls: %d\n", SDL_JoystickNumBalls(g_gamepad));
		// 			}
		// 		}

		g_window = SDL_CreateWindow(
			"sdl mouse",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		if ( !g_window ) 
		{
			printf("is_window_created: err %s\n", SDL_GetError());
			success = false;
		} 
		else 
		{
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
	
	if ( text_surface != 0 ) 
	{
		// create texture
		img->ref = SDL_CreateTextureFromSurface(g_render, text_surface);
		
		if ( !img->ref ) 
		{
			printf("texture_load_font_string: unable to create text texture, err: %s\n", SDL_GetError());
		} 
		else 
		{	
			// get image dimensions
			img->w = text_surface->w;
			img->h = text_surface->h;
		}
		
		// flush surface
		SDL_FreeSurface(text_surface);
	} 
	else 
	{
				printf("texture_load_font_string: unable to render text, ttf err: %s\n", TTF_GetError());
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
		
	if ( event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP ) 
	{
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

#if 0
int
btn_render(btn* btn) 
{
	texture_render_with_clip(
		&g_spritesheet, btn->position.x, btn->position.y, &g_spriteclips[ btn->current_sprite ]);
	
	return 0;
}
#endif

int 
main(int argc, char* args[]) {
	
	if ( is_window_created() ) 
	{
		
		// for "libpng warning: iCCP: known incorrect sRGB profile"	
		// http://stackoverflow.com/questions/22745076/libpng-warning-iccp-known-incorrect-srgb-profile
		// load sdl2_image
		int image_flags = IMG_INIT_PNG;
		
		if ( !(IMG_Init(image_flags) & image_flags) ) 
		{
			printf("main: sdl2_image err: %s\n", IMG_GetError());
			return 1;
		}
		
		// http://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_11.html
		if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
		{	
     	printf( "main: SDL_mixer Error: %s\n", Mix_GetError() );
			return 1;
    }
		
		// load sdl ttf: https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf_8.html
		if ( TTF_Init() == -1 ) {
			printf("sdl2_ttf err: %s\n", TTF_GetError());
			return 1;
		}
	
		if ( !load_media() ) 
		{
			user_quit = true;
		}
		
		// the LOOP
		while	 ( !user_quit ) {
			// process_events(&g_event);
			
			// getting events
			while ( SDL_PollEvent(&g_event) != 0 ) {

				// handling events
				if ( g_event.type == SDL_QUIT ) 
				{
					user_quit = true;
				}
				else if ( g_event.type == SDL_KEYDOWN && g_event.key.keysym.sym == SDLK_RETURN ) 
				{
					// http://wiki.libsdl.org/SDL_GetTicks
					g_start_time = SDL_GetTicks();
				}
			}
			// game_update();
			
			strcpy(g_timer_text, "");
			sprintf(g_timer_text, "Milliseconds %u", SDL_GetTicks() - g_start_time);

			if( !texture_load_font_string( &g_timer_texture, g_timer_text, g_text_color ) )
		  {
			  printf( "process_events: Unable to render time texture!\n" );
		  }

			// remove last committed color 
			SDL_SetRenderDrawColor(g_render, 0xFF, 0xFF, 0xFF, 0xFF);

			// Clear screen
			SDL_RenderClear(g_render);

			texture_render(&g_timer_texture,
										( SCREEN_WIDTH - g_timer_texture.w ) / 2, 
										0 );

			texture_render(&g_prompt_texture,
										( SCREEN_WIDTH - g_prompt_texture.w ) / 2, 
										( SCREEN_HEIGHT - g_prompt_texture.h ) / 2 );

			// Update screen
			SDL_RenderPresent(g_render);
		}
	}
	
	/** closing **/

	// Deallocate textures
	texture_free(&g_timer_texture);
	texture_free(&g_prompt_texture);
	

	SDL_DestroyRenderer(g_render);
	SDL_DestroyWindow(g_window);
	g_window = 0;
	g_render = 0;

	// https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf_10.html
	TTF_Quit();
	// Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
}

int game_update() {
	
	strcpy(g_timer_text, "");
	sprintf(g_timer_text, "Milliseconds %u", SDL_GetTicks() - g_start_time);
	
	if( !texture_load_font_string( &g_timer_texture, g_timer_text, g_text_color ) )
  {
	  printf( "process_events: Unable to render time texture!\n" );
  }

	// remove last committed color 
	SDL_SetRenderDrawColor(g_render, 0xFF, 0xFF, 0xFF, 0xFF);

	// Clear screen
	SDL_RenderClear(g_render);
	
	texture_render(&g_timer_texture,
								( SCREEN_WIDTH - g_timer_texture.w ) / 2, 
								0 );
								
	texture_render(&g_prompt_texture,
								( SCREEN_WIDTH - g_prompt_texture.w ) / 2, 
								( SCREEN_HEIGHT - g_prompt_texture.h ) / 2 );
	
	// Update screen
	SDL_RenderPresent(g_render);
	return 0;
}

int 
process_events(s_event* event) {

	// getting events
	while ( SDL_PollEvent(event) != 0 ) {

		// handling events
		if ( event->type == SDL_QUIT ) 
		{
			user_quit = true;
		}
		else if ( event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_RETURN ) 
		{
			// http://wiki.libsdl.org/SDL_GetTicks
			g_start_time = SDL_GetTicks();
		}
	}

	return 0;
}
