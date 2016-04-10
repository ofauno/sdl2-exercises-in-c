#ifndef FAU_DOT_H
#define	FAU_DOT_H

	#include <fau_common.h>

	typedef struct 
	{
		int w;
		int h;
		int v; // velocity
		int posX;
		int posY;
		int velX;
		int velY;
	} fau_dot;

	int dot_init(fau_dot* dot);
	int dot_handle_events(fau_dot* dot, s_event* event);
	int dot_move(fau_dot* dot);
	int dot_render(fau_dot* dot, texture* dot_texture);

#endif
