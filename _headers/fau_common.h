#ifndef FAU_COMMON_H
#define FAU_COMMON_H
	
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#include <SDL2/SDL_ttf.h>
	#include <SDL2/SDL_mixer.h>
	
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
	
	#ifndef __cplusplus
	    typedef char bool;
	    #define true 1;
	    #define false 0;
	#endif

	/** constants **/
	#define JOYSTICK_DEAD_ZONE 8000
	#define WALKING_FRAMES 4
	#define TOTAL_BUTTONS 4
	
	bool load_media();
	bool is_window_created();
	int game_update();
	s_surface* load_image(char* path);
	int process_events(s_event* event);
	bool init_render();

#endif
