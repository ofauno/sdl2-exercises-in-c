#ifndef FAU_BTN_H
#define FAU_BTN_H

	#include <fau_common.h>
	
	typedef struct {
		s_point position;
		enum ButtonSprite current_sprite;
	} btn;
	
	// button api
	int btn_init(btn* btn);
	int btn_set_position(btn* btn, int x, int y);
	int btn_handle_event(btn* btn, s_event* event);
	int btn_render(btn* btn);

#endif
