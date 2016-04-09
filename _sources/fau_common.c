#include <faudef.h>

bool 
init_render() {
	
	bool success = true;
	// g_render = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
	// VSync allows the rendering to update at the same time 
	// as when your monitor updates during vertical refresh
	// g_render = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	// g_render = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
	g_render = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_PRESENTVSYNC);

	if ( !g_render ) {
		printf("init_render: err render: %s\n", SDL_GetError());
		success = false;
	} else {
		
		// Initialize renderer color
		SDL_SetRenderDrawColor(g_render, 0xFF, 0xFF, 0xFF, 0xFF);
	}
	
	return success;
}



bool 
load_media() {
	
	bool success = true;
	
	g_font = TTF_OpenFont("../_media/lazy.ttf", 28);
	
	if ( !g_font )
	{
		printf("load_media: failed to load\n");
		success = false;
	}
	else
	{
		// Set text color as black
    // SDL_Color text__color = { 0, 0, 0, 255 };
    // 		if ( !texture_load_font_string(&g_start_prompt_texture, "Press S to Start or Stop the Timer", text__color))
    // 		{
    // 			printf( "load_media: Unable to render prompt texture!\n" );
    // 			success = false;
    // 		}
    // 		
    // 		if ( !texture_load_font_string(&g_pause_prompt_texture, "Press P to Pause or Unpause the Timer", text__color))
    // 		{
    // 			printf( "load_media: Unable to render prompt texture!\n" );
    // 			success = false;
    // 		}
	}
	
	return success;
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

int game_update() {
	
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
	}
	return 0;
}
