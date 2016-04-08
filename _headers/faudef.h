#ifndef FAU_DEF_H
#define FAU_DEF_H

	#include <stdio.h>

	#include <fau_common.h>
	#include <fau_timer.h>
	#include <fau_texture.h>
	#include <fau_btn.h>

	// FONTS
	extern TTF_Font* 	g_font;
	extern texture 		g_timer_texture;

	extern timer g_timer;
	extern timer g_fps_timer;

	extern s_window* 			g_window;
	extern SDL_Renderer* 	g_render;

	// screen
	extern int SCREEN_WIDTH;
	extern int SCREEN_HEIGHT;

	// user
	extern bool user_quit;

	// event
	extern s_event 		g_event;
	extern SDL_Color 	g_text_color;
	extern Uint32 		g_start_time;
	extern char	 			g_timer_text[20];

	// buttons
	extern int BUTTON_WIDTH;
	extern int BUTTON_HEIGHT;
#endif
