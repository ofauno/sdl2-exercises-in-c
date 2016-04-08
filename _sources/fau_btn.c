#include <faudef.h>

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
