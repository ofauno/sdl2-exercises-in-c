// Copyright 2016 fauno

#include <faudef.h>

// FONTS
TTF_Font* g_font = 0;
texture 	g_timer_texture = { .is_allocated = 0, 0 };

timer g_timer;
timer g_fps_timer;

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
		
		int counted_frames = 0;
		timer_start(&g_fps_timer);
		
		// the LOOP
		while	 ( !user_quit ) {
			process_events(&g_event);
			
			// FPS
			float avg_fps = counted_frames / ( timer_get_ticks(&g_fps_timer) / 1000.f );
			if( avg_fps > 2000000 )
			{
				avg_fps = 0; // avoid high fps at first
			}
			
			strcpy(g_timer_text, "");
			sprintf(g_timer_text, "fps: %f", avg_fps);

			if( !texture_load_font_string( &g_timer_texture, g_timer_text, g_text_color ) )
		  {
			  printf( "process_events: Unable to render time texture!\n" );
		  }

			// remove last committed color 
			SDL_SetRenderDrawColor(g_render, 0xFF, 0xFF, 0xFF, 0xFF);

			// Clear screen
			SDL_RenderClear(g_render);

			// texture_render(&g_start_prompt_texture,
			// 										( SCREEN_WIDTH - g_start_prompt_texture.w ) / 2, 
			// 										0 );
			// 										
			// 			texture_render(&g_pause_prompt_texture,
			// 										( SCREEN_WIDTH - g_pause_prompt_texture.w ) / 2, 
			// 										g_pause_prompt_texture.h );
										
			texture_render(&g_timer_texture,
										( SCREEN_WIDTH - g_timer_texture.w ) / 2, 
										( SCREEN_HEIGHT - g_timer_texture.h ) / 2);

			// Update screen
			SDL_RenderPresent(g_render);
			++counted_frames;
		}
	}
	
	/** closing **/

	// Deallocate textures
	texture_free(&g_timer_texture);
	// texture_free(&g_start_prompt_texture);
	// texture_free(&g_pause_prompt_texture);
	

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
